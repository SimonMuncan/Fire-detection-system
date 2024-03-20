/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */
#include "flame.h"
#include "peripheral/gpio/plib_gpio.h"
#include <stdio.h>
#include <stdbool.h>

static uint8_t flame_state;




/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

// Function to configure flame sensor pins as input
void flame_cfg(void){
    
    TRISAbits . TRISA2 = 1;
    TRISBbits . TRISB2 = 1;
    
}

// Function to read flame sensor status
bool flame_read(void){
    static uint8_t flame_state_old = 0;
    flame_state = GPIO_PinRead(GPIO_PIN_RB8);
    
    if ( ( flame_state == 1 ) && ( flame_state_old == 0) ){
            
        printf("~~~ POZAR ~~~\n");
        flame_state_old = 1;
        
        return true;
    }
    else if ( ( flame_state == 0 ) && ( flame_state_old == 1 ) ){
    
        printf("~~~ NEMA POZARA ~~~\n");
        flame_state_old = 0;
        return false;
    }
    else if((flame_state_old == 1) && (flame_state ==1))
    {
        return true;
    }
    else{
        return false;
    }
    
}


/* *****************************************************************************
 End of File
 */
