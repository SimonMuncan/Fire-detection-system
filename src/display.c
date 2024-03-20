

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"
#include "ili9341.h"
#include "pad.h"
#include "display.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
volatile bool flag = false;                         // Flag indicating touch event
uint8_t cnt = 0;                                    // Counter variable
uint8_t xdyd[6]={32, 120, 160, 24, 32, 24};         // Array with predefined values
uint16_t xtyt[2];                                   // Array for storing x, y coordinates
uint16_t xt[1], yt[1];                              // Arrays for storing x, y coordinates
uint8_t brojac = 0;                                 // Counter variable
uint8_t ukucana_sifra[4] = {0,0,0,0};               // Array for entered password
uint8_t prava_sifra[4] = {4, 2, 3, 7};              // Array for correct password



// Interrupt handler for GPIO pin RB15
void GPIO_RB15_IntHandler(GPIO_PIN pin, uintptr_t context){
    if(GPIO_PinRead(pin)==0){
        flag = true;                                // Set flag on touch event
    }
}


// Function to sort an array in ascending order
void sort(uint16_t* arr, int n){
    int16_t i, key, j;
    
    for(i=1;i<n;i++){
        key = arr[i];
        
        j = i-1;
        
        while(j>=0 && arr[j]>key){
            arr[j+1] = arr[j];
            j=j-1;
        }
        arr[j+1] = key;
    }
}

// Function to read x, y coordinates from touch screen
void readXY(uint16_t* x, uint16_t* y){
    uint16_t data[21];

    // Set up GPIO pins
    GPIO_PinInputEnable(GPIO_PIN_RB3);
    GPIO_PinIntDisable(GPIO_PIN_RB15);
    GPIO_RB15_InputEnable();                                
    GPIO_PinOutputEnable(GPIO_PIN_RB2);
    GPIO_PinSet(GPIO_PIN_RB2);

    // Read x coordinates
    for(uint8_t i=0; i<21; i++)                                               
    {
        ADCHS_ChannelConversionStart(ADCHS_CH3);
        while(!ADCHS_ChannelResultIsReady(ADCHS_CH3));
        data[i] = ADCHS_ChannelResultGet(ADCHS_CH3);                            
        CORETIMER_DelayUs(10);
    }
    // Sort and extract median value for x 
    sort(data, 21);                                                            
    x[0] = data[10];                                                            

    // Set up GPIO pins
    GPIO_PinInputEnable(GPIO_PIN_RB2);
    GPIO_PinOutputEnable(GPIO_PIN_RB3);
    GPIO_PinSet(GPIO_PIN_RB3);
    GPIO_RB14_InputEnable();
    GPIO_RB15_OutputEnable();
    GPIO_RB15_Clear();

    // Read y coordinates
    for(uint8_t i=0; i<21; i++)                                                 
    {
        ADCHS_ChannelConversionStart(ADCHS_CH2);
        while(!ADCHS_ChannelResultIsReady(ADCHS_CH2));
        data[i] = ADCHS_ChannelResultGet(ADCHS_CH2);                            
        CORETIMER_DelayUs(10);
    }
    // Sort and extract median value for y
    sort(data, 21);
    y[0] = data[10];

    // Disable GPIO pins and delay
    GPIO_RB14_OutputEnable();
    GPIO_RB14_Clear();
    GPIO_PinInputEnable(GPIO_PIN_RB2);
    GPIO_RB15_InputEnable();
    GPIO_PinInputEnable(GPIO_PIN_RB3);
    CORETIMER_DelayMs(1);
    GPIO_PinIntEnable(GPIO_PIN_RB15, GPIO_INTERRUPT_ON_MISMATCH);

}

// Function to draw points on screen based on input
void tacka(int brojac){
    if(brojac-1 == 0){
        ili9341_draw_filled_circle(105,222,2,COLOR_BLACK);            
    }
    else if(brojac-1 == 1){
        ili9341_draw_filled_circle(140,222,2,COLOR_BLACK);            
    }
    else if(brojac-1 == 2){
        ili9341_draw_filled_circle(175,222,2,COLOR_BLACK);            
    }
    else if(brojac-1 == 3){
        ili9341_draw_filled_circle(210,222,2,COLOR_BLACK);            
    }

}

// Function to reset variables and clear display
void reset(void){
    ili9341_clear_display(COLOR_WHITE);                                        
    ili9341_draw_raw_image(0,0,pad,320,240);
    brojac = 0;
    ukucana_sifra[0] = 0;
    ukucana_sifra[1] = 0;
    ukucana_sifra[2] = 0;
    ukucana_sifra[3] = 0;
}

// Function to verify entered password
bool sifra( void )
{
    /* Initialize all modules */
    
    ili9341_draw_raw_image(0,0,pad,320,240);

    GPIO_RB14_Clear();
    GPIO_RB14_OutputEnable();
    
    GPIO_PinInterruptCallbackRegister(GPIO_PIN_RB15, GPIO_RB15_IntHandler, 0);  
    GPIO_PinIntEnable(GPIO_PIN_RB15, GPIO_INTERRUPT_ON_MISMATCH);                  
    

    float coeff[6]={0.103,0.001,-61.756,0.003,0.076,-37.112};

    // Main loop for password entry
    while ( brojac <= 4 ){
        // Check for touch event
        if(flag){                                                               
        flag = false;                                                            

        uint16_t x[1];
        uint16_t y[1];

        // Read x, y coordinates from touch screen
        readXY(x,y);                                                        
        x[0] = (uint16_t)(coeff[0]*x[0]+coeff[1]*y[0]+coeff[2]);            
        y[0] = (uint16_t)(coeff[3]*x[0]+coeff[4]*y[0]+coeff[5]);

        if(y[0]<195 && y[0]>146){  
            brojac++;
            tacka(brojac);
            if(x[0]<107){
                ukucana_sifra[brojac - 1] = 1;
            }
            else if(x[0]>107 && x[0]<214){

                ukucana_sifra[brojac - 1] = 2;
            }
            else if(x[0]>214){

                ukucana_sifra[brojac - 1] = 3;

            }


        }
        else if(y[0]<146 && y[0]>98){
            brojac++;
            tacka(brojac);
            if(x[0]<107){
                ukucana_sifra[brojac - 1] = 4;
            }
            else if(x[0]>107 && x[0]<214){
                    ukucana_sifra[brojac - 1] = 5;
            }
            else if(x[0]>214){
                ukucana_sifra[brojac - 1] = 6;
            }


        }
        else if(y[0]<98 && y[0]>50){
            brojac++;
            tacka(brojac);

            if(x[0]<107){
                ukucana_sifra[brojac - 1] = 7;
            }
            else if(x[0]>107 && x[0]<214){
                ukucana_sifra[brojac - 1] = 8;
            }
            else if(x[0]>214){
                ukucana_sifra[brojac - 1] = 9;
            }

        }
        else if(y[0]<50 && y[0]>0){
            if(x[0]<107){
                reset();
            }
            else if(x[0]>107 && x[0]<214){
                ukucana_sifra[brojac - 1] = 0;
            }
            else if(x[0]>214){                                                        
                    if(prava_sifra[0] == ukucana_sifra[0] && prava_sifra[1] == ukucana_sifra[1] && prava_sifra[2] == ukucana_sifra[2] && prava_sifra[3] == ukucana_sifra[3]){
                        reset();
                        ili9341_clear_display(COLOR_WHITE); 
                        return true;
                       
                    }
                    else{
                        reset();
                        return false;
                    }
                }
            }      
        }
    }
    // Check if password entry is complete
    if(brojac > 4)
    {
        reset();    // Reset variables and clear display
    }

    /* Execution should not come here during normal operation */
    return false;
}


/*******************************************************************************
 End of File
*/