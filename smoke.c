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
#include <stdio.h>
#include <stdint.h>
#include "smoke.h"
#include "config/default/peripheral/i2c/master/plib_i2c2_master.h"
#include "peripheral/coretimer/plib_coretimer.h"

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

// Function to initialize the smoke sensor
void smoke_init(void){
    FIFO_Config();
    MODE_Config();
    SPO2_Config();
    LED_Amp();
}

// Function to configure mode
void MODE_Config(void){
    static uint8_t wr_data[2];
    wr_data[0] = SMOKE_REG_MODE_CONFIG;
    wr_data[1] = 0x03;
    I2C2_Write(SMOKE_I2C_ADDRESS, wr_data, 2);
    while(I2C2_IsBusy());
    
}

// Function to configure FIFO
void FIFO_Config(void){
    static uint8_t wr_data[2];
    wr_data[0] = SMOKE_REG_FIFO_CONFIG;
    wr_data[1] = 0xFF;
    I2C2_Write(SMOKE_I2C_ADDRESS, wr_data, 2);
    while(I2C2_IsBusy());
    
}


// Function to configure SPO2
void SPO2_Config(void){
    static uint8_t wr_data[2];
    wr_data[0] = SMOKE_REG_PARTICLE_CONFIG;
    wr_data[1] = 0x3F;
    I2C2_Write(SMOKE_I2C_ADDRESS, wr_data, 2);
    while(I2C2_IsBusy());

}

// Function to configure LED amplitude
void LED_Amp(void){
    static uint8_t wr_data[2];
    wr_data[0] = SMOKE_REG_LED_RED_PULSE_AMP;
    wr_data[1] = 0x4F;
    I2C2_Write(SMOKE_I2C_ADDRESS, wr_data, 2);
    while(I2C2_IsBusy());
    wr_data[0] = 0x00;
    wr_data[1] = 0x00;
    
    wr_data[0] = SMOKE_REG_LED_IR_PULSE_AMP;
    wr_data[1] = 0xFF;
    I2C2_Write(SMOKE_I2C_ADDRESS, wr_data, 2);
    while(I2C2_IsBusy());
    
}

// Function to clear FIFO
void FIFO_Clear(void){
    static uint8_t wr_data[2];
    wr_data[0] = SMOKE_FIFO_WRITE_PTR;
    wr_data[1] = 0x00;
    I2C2_Write(SMOKE_I2C_ADDRESS, wr_data, 2);
    while(I2C2_IsBusy());
    wr_data[0] = SMOKE_FIFO_READ_PTR;
    I2C2_Write(SMOKE_I2C_ADDRESS, wr_data, 2);
    while(I2C2_IsBusy());
    wr_data[0] = SMOKE_FIFO_DATA;
    I2C2_Write(SMOKE_I2C_ADDRESS, wr_data, 2);
    while(I2C2_IsBusy());
    
}


// Function to read from FIFO
void FIFO_read(smoke_t* sens){
    static uint8_t rd_data[6];
    static uint8_t wr_data;
    
    wr_data = SMOKE_FIFO_DATA;
    
    I2C2_WriteRead(SMOKE_I2C_ADDRESS, &wr_data, 1, rd_data, 6);
    while(I2C2_IsBusy());
    
    sens -> red_value = ((uint32_t)rd_data[0]<<16)|((uint32_t)rd_data[1]<<8)|(uint32_t)rd_data[2];
    
    sens -> ir_value = ((uint32_t)rd_data[3]<<16)|((uint32_t)rd_data[4]<<8)|(uint32_t)rd_data[5];
    
    
}
/* *****************************************************************************
 End of File
 */
