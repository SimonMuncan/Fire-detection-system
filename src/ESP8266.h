#ifndef ESP8266_H    /* Guard against multiple inclusion */
#define ESP8266_H



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include "definitions.h"                // SYS function prototypes
#include <string.h>
    

typedef enum{
    CWMODE,
    MODE_OK,
    MODE_ERROR,
    CWJAP,
    WIFI_ERROR,
    WIFI_OK,
    CIPSTART,
    TCP_OK,
    TCP_CLOSED,
    TCP_ALREADY_CONNECTED,
    CIPSEND,
    CIPSEND_OK,
    CIPSEND_CLOSED,
    SEND1,
    SEND1_OK,
    SEND1_ERROR,
    SEND2,
    SEND2_OK,
    SEND2_ERROR
}STATUS_MSG_t;


STATUS_MSG_t ESP8266_set_mode();
STATUS_MSG_t ESP8266_connect_to_AP();
STATUS_MSG_t ESP8266_TCP_connection();
STATUS_MSG_t ESP8266_cipsend();
STATUS_MSG_t ESP8266_data_to_thingspeak(char* smoke_dioda);
STATUS_MSG_t ESP8266_data_to_thingspeak2(char* smoke_ir_dioda);

#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
