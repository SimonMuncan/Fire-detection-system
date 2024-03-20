#include "ESP8266.h"
#include "smoke.h"

// Required AT commands:
char WIFI_ST_MODE_CMD[] = "AT+CWMODE=1\r\n";    // Set Wi-Fi mode command
char JOIN_AN_AP_CMD[] = "AT+CWJAP=\"Simi\",\"4godisnjadoba\"\r\n";  // Join Wi-Fi network command
char START_TCP_CONNECTION_CMD[] = "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n";  // Start TCP connection command
char SEND_DATA_LENGTH_CMD[] = "AT+CIPSEND=77\r\n";   // Send data length command
char QUIT_AP_CMD[] = "AT+CWQAP";    // Quit access point command

smoke_t sensor; // Declare smoke sensor object


// Function to set Wi-Fi mode of ESP8266 module
STATUS_MSG_t ESP8266_set_mode(){
    char answ[128]; // Buffer for storing response
    
    // Send mode setting command
    UART2_Write((uint8_t*)WIFI_ST_MODE_CMD, strlen(WIFI_ST_MODE_CMD));        
    while(UART2_WriteCountGet()!=0);     // Wait for UART transmission to complete                                      
   
    CORETIMER_DelayMs(100);     // Delay for stability
    UART2_Read((uint8_t*)answ, sizeof(answ));      // Read response                             
    
    // Check if "OK" response is received
    char* find_ok = strstr(answ, "OK\r\n");                                  
    // If "OK" response found
    if(find_ok!=NULL){                                                          
        return MODE_OK;                      
    }
    else{
        return MODE_ERROR;                                                 
    }
}

// Function to connect ESP8266 module to Wi-Fi access point
STATUS_MSG_t ESP8266_connect_to_AP(){
    char answ[128]; // Buffer for storing response

    // Send join AP command
    UART2_Write((uint8_t*)JOIN_AN_AP_CMD, strlen(JOIN_AN_AP_CMD));             
    while(UART2_WriteCountGet()!=0);
    
    CORETIMER_DelayMs(500);
    UART2_Read((uint8_t*)answ, sizeof(answ));                                   
    
    // Check if there's an error in Wi-Fi connection
    char* find_error = strstr(answ, "+CWJAP=\r\n");                              
    
    if(find_error!=NULL){
        return WIFI_ERROR;
    }
    else{
        return WIFI_OK;
    }
}

// Function to establish TCP connection to ThingSpeak server
STATUS_MSG_t ESP8266_TCP_connection(){
    char answ[128];

    // Send TCP connection command
    UART2_Write((uint8_t*)START_TCP_CONNECTION_CMD, strlen(START_TCP_CONNECTION_CMD));  
    while(UART2_WriteCountGet()!=0);
    
    CORETIMER_DelayMs(100);
    UART2_Read((uint8_t*)answ, sizeof(answ));
    
    // Check TCP connection status
    char* find_ok = strstr(answ, "OK\r\n");                                     
    char* find_connected = strstr(answ, "ALREADY CONNECTED\r\n");               
    
    if(find_ok!=NULL){
        return TCP_OK;
    }
    else if(find_connected){
        return TCP_ALREADY_CONNECTED;
    }
    else{
        return TCP_CLOSED;                                                      
    }
}
STATUS_MSG_t ESP8266_cipsend(){
    char answ[128];
    
    UART2_Write((uint8_t*)SEND_DATA_LENGTH_CMD, strlen(SEND_DATA_LENGTH_CMD));  
    while(UART2_WriteCountGet()!=0);
    
    CORETIMER_DelayMs(100);
    UART2_Read((uint8_t*)answ, sizeof(answ));
    
    char* find_ok = strstr(answ, "OK\r\n");                                     
    if(find_ok!=NULL){
        return CIPSEND_OK;
    }
    else{
        return CIPSEND_CLOSED;
    }
}

// Function to send data to ThingSpeak channel (field1)
STATUS_MSG_t ESP8266_data_to_thingspeak(char* smoke_dioda){

    char answ[128];
    char write_a_channel_feed[80];  // Buffer for constructing HTTP request

    // Construct HTTP request for updating field1
    strcpy(write_a_channel_feed,"GET https://api.thingspeak.com/update?api_key=WA3W6XYL39FMDGCI&field1=");  
    strcat(write_a_channel_feed,smoke_dioda);
    strcat(write_a_channel_feed,"\r\n");                                        
    // Send HTTP request      
    UART2_Write((uint8_t*)write_a_channel_feed, strlen(write_a_channel_feed));  
    while(UART2_WriteCountGet()!=0);
    
    CORETIMER_DelayMs(100);
    UART2_Read((uint8_t*)answ, sizeof(answ));
    
    char* find_ok = strstr(answ, "Recv");   

    if(find_ok!=NULL){
        return SEND1_OK;
    }
    else{
        return SEND1_ERROR;
    }
}

// Function to send data to ThingSpeak channel (field2)
STATUS_MSG_t ESP8266_data_to_thingspeak2(char* smoke_ir_dioda){

    char answ[128];
    char write_a_channel_feed[80];
    
    // Construct HTTP request for updating field2
    strcpy(write_a_channel_feed,"GET https://api.thingspeak.com/update?api_key=WA3W6XYL39FMDGCI&field2=");  
    strcat(write_a_channel_feed,smoke_ir_dioda);                                 
    strcat(write_a_channel_feed,"\r\n");                                       
    // Send HTTP request
    UART2_Write((uint8_t*)write_a_channel_feed, strlen(write_a_channel_feed));  
    while(UART2_WriteCountGet()!=0);
    
    CORETIMER_DelayMs(100);
    UART2_Read((uint8_t*)answ, sizeof(answ));
    
    char* find_ok = strstr(answ, "Recv");                                       
    
    if(find_ok!=NULL){
        return SEND2_OK;
    }
    else{
        return SEND2_ERROR;
    }
}