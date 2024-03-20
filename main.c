/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdio.h> 
#include <stddef.h>                     
#include <stdbool.h>                   
#include <stdlib.h>                    
#include <stdint.h>
#include "definitions.h"                
#include "flame.h"
#include "smoke.h"
#include "display.h"
#include "ili9341.h"
#include "ESP8266.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************



volatile bool tmr_flag = 0;             // Flag for timer interrupt
volatile uint16_t tmr_cnt = 0;          // Counter for timer interrupt

// Interrupt handler for Timer 2
void tmr2_IntHandle(uint32_t status, uintptr_t context){
    GPIO_PinToggle(GPIO_PIN_RD3);       // Toggle pin RD3
}

// Interrupt handler for Timer 3
void tmr3_IntHandle(uint32_t status, uintptr_t context){
    GPIO_PinClear(GPIO_PIN_RD3);        // Clear pin RD3
    CORETIMER_DelayMs(80);              // Delay for 80 milliseconds
}
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );                                    // Initialize system modules
    FIFO_Clear();                                               // Clear FIFO buffer
    ili9341_init();                                             // Initialize ILI9341 display
    ili9341_clear_display(COLOR_CYAN);                          // Clear display with cyan color
    smoke_init();                                               // Initialize smoke sensor
    char smoke_dioda[64]={0};                                   // Buffer for storing smoke sensor data
    char smoke_ir_dioda[64]={0};                                // Buffer for storing smoke IR sensor data
    smoke_t sensor;                                             // Structure to store smoke sensor data
    STATUS_MSG_t status = CWMODE;                               // Status variable for ESP8266 Wi-Fi module
    bool flag_send_1 = false;                                   // Flag to indicate the type of data sent
    flame_cfg();                                                // Configure flame sensor pins as input
    TMR2_CallbackRegister(tmr2_IntHandle, (uintptr_t)NULL);     // Register Timer 2 interrupt handler
    TMR3_CallbackRegister(tmr3_IntHandle, (uintptr_t)NULL);     // Register Timer 3 interrupt handler
    
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
       // SYS_Tasks ( );
        FIFO_read(&sensor);                                                 // Read data from smoke sensor
        CORETIMER_DelayMs(500);                                             // Delay for stability
        sprintf(smoke_dioda, "%u", sensor.red_value);                       // Convert red value to string
        sprintf(smoke_ir_dioda, "%u", sensor.ir_value);                     // Convert IR value to string
        printf("RED: %u, IR: %u\r\n", sensor.red_value, sensor.ir_value);   // Print sensor values

        // State machine for Wi-Fi module communication
        switch(status){
            case CWMODE:
                status = ESP8266_set_mode();                // Set Wi-Fi mode                           
                printf("CWMODE\r\n");
                
                if(status==MODE_OK){                        // If mode set successfully                 
                    status = CWJAP;                         // Move to next state
                    printf("CWMODE OK ----> CWJAP\r\n");
                }
                else{
                    status = CWMODE;                        // Retry setting mode                 
                    printf("CWMODE ERROR\r\n");
                }
                break;
            case CWJAP:
                CORETIMER_DelayMs(1000);
                status = ESP8266_connect_to_AP();           // Connect to Wi-Fi access point                 
                printf("CWJAP\r\n");
                if(status==WIFI_OK){                        // If connection successful                  
                    status = CIPSTART;                      // Move to next state
                    printf("CWJAP OK ----> CIPSTART\r\n");
                }
                else{
                    status = CWJAP;                         // Retry connection                  
                    printf("CWJAP ERROR\r\n");
                }
                break;
            case CIPSTART:
                status = ESP8266_TCP_connection();          // Establish TCP connection                  
                printf("CIPSTART\r\n");
                
                if(status==TCP_CLOSED){                     // If connection closed                  
                    status = CIPSTART;                      // Retry connection
                    printf("TCP CLOSED\r\n");
                }
                else{                                                           
                    status = CIPSEND;                       // Move to next state
                    printf("TCP ALREADY CONNECTED/TCP OK ----> CIPSEND\r\n");
                }
                break;
            case CIPSEND:
                status = ESP8266_cipsend();                     // Send data to server                      
                printf("CIPSEND\r\n");
                
                if(status==CIPSEND_OK && flag_send_1){          // If data sent successfully and second type of data
                    status = SEND2;                             // Move to sending second type of data
                    printf("CIPSEND OK ----> SEND\r\n");
                }
                else if(status==CIPSEND_OK && !flag_send_1){    // If data sent successfully and first type of data                                    
                    status = SEND1;                             // Move to sending first type of data
                    printf("CIPSEND OK ----> SEND\r\n");
                }
                else{                                                      
                    status = CIPSTART;                          // Retry connection
                    printf("CIPSEND CLOSED\r\n");
                }
                break;
            case SEND1:  
                flag_send_1 = true;                                 // Set flag for first type of data
                status = ESP8266_data_to_thingspeak(smoke_dioda);   // Send data to ThingSpeak
                printf("SEND1\r\n");
                CORETIMER_DelayMs(15000);                           // Delay for stability
                
                if(status==SEND1_OK){                               // If data sent successfully                   
                    printf("SEND1 OK\r\n");
                }
                else{                                                        
                    printf("SEND1 ERROR\r\n");                      // Print error message
                }
                status = CIPSTART;                                  // Move back to establishing connection
                break;
            case SEND2:             
                flag_send_1  = false;                                 // Set flag for second type of data
                status = ESP8266_data_to_thingspeak2(smoke_ir_dioda); // Send data to ThingSpeak
                printf("SEND2\r\n");
                CORETIMER_DelayMs(15000);
                
                if(status==SEND2_OK){                                           
                    printf("SEND2 OK\r\n");
                }
                else{                                                           
                    printf("SEND2 ERROR\r\n");
                }
                status = CIPSTART;
                break;
            default:
                status = CWMODE;                                        // Default to setting Wi-Fi mode
                printf("default\r\n");
                break;
        }
       
        // If flame is detected and sensor values are above threshold, start timers and wait for correct code entry
        if(flame_read() && sensor.red_value > 1000 && sensor.ir_value > 1000){
            TMR3_Start();               // Start Timer 3
            TMR2_Start();               // Start Timer 2
            
            while(sifra() == false){}   // Wait until correct code is entered
            
            TMR3_Stop();                // Stop Timer 3
            TMR2_Stop();                // Stop Timer 2
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

