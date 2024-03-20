/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h UUUUUUUUU

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for D5 pin ***/
#define D5_Set()               (LATESET = (1U<<5))
#define D5_Clear()             (LATECLR = (1U<<5))
#define D5_Toggle()            (LATEINV= (1U<<5))
#define D5_OutputEnable()      (TRISECLR = (1U<<5))
#define D5_InputEnable()       (TRISESET = (1U<<5))
#define D5_Get()               ((PORTE >> 5) & 0x1U)
#define D5_PIN                  GPIO_PIN_RE5

/*** Macros for D6 pin ***/
#define D6_Set()               (LATESET = (1U<<6))
#define D6_Clear()             (LATECLR = (1U<<6))
#define D6_Toggle()            (LATEINV= (1U<<6))
#define D6_OutputEnable()      (TRISECLR = (1U<<6))
#define D6_InputEnable()       (TRISESET = (1U<<6))
#define D6_Get()               ((PORTE >> 6) & 0x1U)
#define D6_PIN                  GPIO_PIN_RE6

/*** Macros for D7 pin ***/
#define D7_Set()               (LATESET = (1U<<7))
#define D7_Clear()             (LATECLR = (1U<<7))
#define D7_Toggle()            (LATEINV= (1U<<7))
#define D7_OutputEnable()      (TRISECLR = (1U<<7))
#define D7_InputEnable()       (TRISESET = (1U<<7))
#define D7_Get()               ((PORTE >> 7) & 0x1U)
#define D7_PIN                  GPIO_PIN_RE7

/*** Macros for GPIO_RB8 pin ***/
#define GPIO_RB8_Set()               (LATBSET = (1U<<8))
#define GPIO_RB8_Clear()             (LATBCLR = (1U<<8))
#define GPIO_RB8_Toggle()            (LATBINV= (1U<<8))
#define GPIO_RB8_OutputEnable()      (TRISBCLR = (1U<<8))
#define GPIO_RB8_InputEnable()       (TRISBSET = (1U<<8))
#define GPIO_RB8_Get()               ((PORTB >> 8) & 0x1U)
#define GPIO_RB8_PIN                  GPIO_PIN_RB8

/*** Macros for GPIO_RB9 pin ***/
#define GPIO_RB9_Set()               (LATBSET = (1U<<9))
#define GPIO_RB9_Clear()             (LATBCLR = (1U<<9))
#define GPIO_RB9_Toggle()            (LATBINV= (1U<<9))
#define GPIO_RB9_OutputEnable()      (TRISBCLR = (1U<<9))
#define GPIO_RB9_InputEnable()       (TRISBSET = (1U<<9))
#define GPIO_RB9_Get()               ((PORTB >> 9) & 0x1U)
#define GPIO_RB9_PIN                  GPIO_PIN_RB9

/*** Macros for GPIO_RB14 pin ***/
#define GPIO_RB14_Set()               (LATBSET = (1U<<14))
#define GPIO_RB14_Clear()             (LATBCLR = (1U<<14))
#define GPIO_RB14_Toggle()            (LATBINV= (1U<<14))
#define GPIO_RB14_OutputEnable()      (TRISBCLR = (1U<<14))
#define GPIO_RB14_InputEnable()       (TRISBSET = (1U<<14))
#define GPIO_RB14_Get()               ((PORTB >> 14) & 0x1U)
#define GPIO_RB14_PIN                  GPIO_PIN_RB14

/*** Macros for GPIO_RB15 pin ***/
#define GPIO_RB15_Set()               (LATBSET = (1U<<15))
#define GPIO_RB15_Clear()             (LATBCLR = (1U<<15))
#define GPIO_RB15_Toggle()            (LATBINV= (1U<<15))
#define GPIO_RB15_OutputEnable()      (TRISBCLR = (1U<<15))
#define GPIO_RB15_InputEnable()       (TRISBSET = (1U<<15))
#define GPIO_RB15_Get()               ((PORTB >> 15) & 0x1U)
#define GPIO_RB15_PIN                  GPIO_PIN_RB15
#define GPIO_RB15_InterruptEnable()   (CNENBSET = (1U<<15))
#define GPIO_RB15_InterruptDisable()  (CNENBCLR = (1U<<15))

/*** Macros for RS pin ***/
#define RS_Set()               (LATDSET = (1U<<9))
#define RS_Clear()             (LATDCLR = (1U<<9))
#define RS_Toggle()            (LATDINV= (1U<<9))
#define RS_OutputEnable()      (TRISDCLR = (1U<<9))
#define RS_InputEnable()       (TRISDSET = (1U<<9))
#define RS_Get()               ((PORTD >> 9) & 0x1U)
#define RS_PIN                  GPIO_PIN_RD9

/*** Macros for CS pin ***/
#define CS_Set()               (LATDSET = (1U<<10))
#define CS_Clear()             (LATDCLR = (1U<<10))
#define CS_Toggle()            (LATDINV= (1U<<10))
#define CS_OutputEnable()      (TRISDCLR = (1U<<10))
#define CS_InputEnable()       (TRISDSET = (1U<<10))
#define CS_Get()               ((PORTD >> 10) & 0x1U)
#define CS_PIN                  GPIO_PIN_RD10

/*** Macros for GPIO_RD3 pin ***/
#define GPIO_RD3_Set()               (LATDSET = (1U<<3))
#define GPIO_RD3_Clear()             (LATDCLR = (1U<<3))
#define GPIO_RD3_Toggle()            (LATDINV= (1U<<3))
#define GPIO_RD3_OutputEnable()      (TRISDCLR = (1U<<3))
#define GPIO_RD3_InputEnable()       (TRISDSET = (1U<<3))
#define GPIO_RD3_Get()               ((PORTD >> 3) & 0x1U)
#define GPIO_RD3_PIN                  GPIO_PIN_RD3

/*** Macros for WR pin ***/
#define WR_Set()               (LATDSET = (1U<<4))
#define WR_Clear()             (LATDCLR = (1U<<4))
#define WR_Toggle()            (LATDINV= (1U<<4))
#define WR_OutputEnable()      (TRISDCLR = (1U<<4))
#define WR_InputEnable()       (TRISDSET = (1U<<4))
#define WR_Get()               ((PORTD >> 4) & 0x1U)
#define WR_PIN                  GPIO_PIN_RD4

/*** Macros for RD pin ***/
#define RD_Set()               (LATDSET = (1U<<5))
#define RD_Clear()             (LATDCLR = (1U<<5))
#define RD_Toggle()            (LATDINV= (1U<<5))
#define RD_OutputEnable()      (TRISDCLR = (1U<<5))
#define RD_InputEnable()       (TRISDSET = (1U<<5))
#define RD_Get()               ((PORTD >> 5) & 0x1U)
#define RD_PIN                  GPIO_PIN_RD5

/*** Macros for RST pin ***/
#define RST_Set()               (LATDSET = (1U<<7))
#define RST_Clear()             (LATDCLR = (1U<<7))
#define RST_Toggle()            (LATDINV= (1U<<7))
#define RST_OutputEnable()      (TRISDCLR = (1U<<7))
#define RST_InputEnable()       (TRISDSET = (1U<<7))
#define RST_Get()               ((PORTD >> 7) & 0x1U)
#define RST_PIN                  GPIO_PIN_RD7

/*** Macros for D0 pin ***/
#define D0_Set()               (LATESET = (1U<<0))
#define D0_Clear()             (LATECLR = (1U<<0))
#define D0_Toggle()            (LATEINV= (1U<<0))
#define D0_OutputEnable()      (TRISECLR = (1U<<0))
#define D0_InputEnable()       (TRISESET = (1U<<0))
#define D0_Get()               ((PORTE >> 0) & 0x1U)
#define D0_PIN                  GPIO_PIN_RE0

/*** Macros for D1 pin ***/
#define D1_Set()               (LATESET = (1U<<1))
#define D1_Clear()             (LATECLR = (1U<<1))
#define D1_Toggle()            (LATEINV= (1U<<1))
#define D1_OutputEnable()      (TRISECLR = (1U<<1))
#define D1_InputEnable()       (TRISESET = (1U<<1))
#define D1_Get()               ((PORTE >> 1) & 0x1U)
#define D1_PIN                  GPIO_PIN_RE1

/*** Macros for D2 pin ***/
#define D2_Set()               (LATESET = (1U<<2))
#define D2_Clear()             (LATECLR = (1U<<2))
#define D2_Toggle()            (LATEINV= (1U<<2))
#define D2_OutputEnable()      (TRISECLR = (1U<<2))
#define D2_InputEnable()       (TRISESET = (1U<<2))
#define D2_Get()               ((PORTE >> 2) & 0x1U)
#define D2_PIN                  GPIO_PIN_RE2

/*** Macros for D3 pin ***/
#define D3_Set()               (LATESET = (1U<<3))
#define D3_Clear()             (LATECLR = (1U<<3))
#define D3_Toggle()            (LATEINV= (1U<<3))
#define D3_OutputEnable()      (TRISECLR = (1U<<3))
#define D3_InputEnable()       (TRISESET = (1U<<3))
#define D3_Get()               ((PORTE >> 3) & 0x1U)
#define D3_PIN                  GPIO_PIN_RE3

/*** Macros for D4 pin ***/
#define D4_Set()               (LATESET = (1U<<4))
#define D4_Clear()             (LATECLR = (1U<<4))
#define D4_Toggle()            (LATEINV= (1U<<4))
#define D4_OutputEnable()      (TRISECLR = (1U<<4))
#define D4_InputEnable()       (TRISESET = (1U<<4))
#define D4_Get()               ((PORTE >> 4) & 0x1U)
#define D4_PIN                  GPIO_PIN_RE4


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/


#define    GPIO_PORT_A  (0)
#define    GPIO_PORT_B  (1)
#define    GPIO_PORT_C  (2)
#define    GPIO_PORT_D  (3)
#define    GPIO_PORT_E  (4)
#define    GPIO_PORT_F  (5)
#define    GPIO_PORT_G  (6)
#define    GPIO_PORT_H  (7)
#define    GPIO_PORT_J  (8)
#define    GPIO_PORT_K  (9)
typedef uint32_t GPIO_PORT;

typedef enum
{
    GPIO_INTERRUPT_ON_MISMATCH,
    GPIO_INTERRUPT_ON_RISING_EDGE,
    GPIO_INTERRUPT_ON_FALLING_EDGE,
    GPIO_INTERRUPT_ON_BOTH_EDGES,
}GPIO_INTERRUPT_STYLE;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/


#define     GPIO_PIN_RA0  (0U)
#define     GPIO_PIN_RA1  (1U)
#define     GPIO_PIN_RA2  (2U)
#define     GPIO_PIN_RA3  (3U)
#define     GPIO_PIN_RA4  (4U)
#define     GPIO_PIN_RA5  (5U)
#define     GPIO_PIN_RA6  (6U)
#define     GPIO_PIN_RA7  (7U)
#define     GPIO_PIN_RA9  (9U)
#define     GPIO_PIN_RA10  (10U)
#define     GPIO_PIN_RA14  (14U)
#define     GPIO_PIN_RA15  (15U)
#define     GPIO_PIN_RB0  (16U)
#define     GPIO_PIN_RB1  (17U)
#define     GPIO_PIN_RB2  (18U)
#define     GPIO_PIN_RB3  (19U)
#define     GPIO_PIN_RB4  (20U)
#define     GPIO_PIN_RB5  (21U)
#define     GPIO_PIN_RB6  (22U)
#define     GPIO_PIN_RB7  (23U)
#define     GPIO_PIN_RB8  (24U)
#define     GPIO_PIN_RB9  (25U)
#define     GPIO_PIN_RB10  (26U)
#define     GPIO_PIN_RB11  (27U)
#define     GPIO_PIN_RB12  (28U)
#define     GPIO_PIN_RB13  (29U)
#define     GPIO_PIN_RB14  (30U)
#define     GPIO_PIN_RB15  (31U)
#define     GPIO_PIN_RC1  (33U)
#define     GPIO_PIN_RC2  (34U)
#define     GPIO_PIN_RC3  (35U)
#define     GPIO_PIN_RC4  (36U)
#define     GPIO_PIN_RC12  (44U)
#define     GPIO_PIN_RC13  (45U)
#define     GPIO_PIN_RC14  (46U)
#define     GPIO_PIN_RC15  (47U)
#define     GPIO_PIN_RD0  (48U)
#define     GPIO_PIN_RD1  (49U)
#define     GPIO_PIN_RD2  (50U)
#define     GPIO_PIN_RD3  (51U)
#define     GPIO_PIN_RD4  (52U)
#define     GPIO_PIN_RD5  (53U)
#define     GPIO_PIN_RD6  (54U)
#define     GPIO_PIN_RD7  (55U)
#define     GPIO_PIN_RD9  (57U)
#define     GPIO_PIN_RD10  (58U)
#define     GPIO_PIN_RD11  (59U)
#define     GPIO_PIN_RD12  (60U)
#define     GPIO_PIN_RD13  (61U)
#define     GPIO_PIN_RD14  (62U)
#define     GPIO_PIN_RD15  (63U)
#define     GPIO_PIN_RE0  (64U)
#define     GPIO_PIN_RE1  (65U)
#define     GPIO_PIN_RE2  (66U)
#define     GPIO_PIN_RE3  (67U)
#define     GPIO_PIN_RE4  (68U)
#define     GPIO_PIN_RE5  (69U)
#define     GPIO_PIN_RE6  (70U)
#define     GPIO_PIN_RE7  (71U)
#define     GPIO_PIN_RE8  (72U)
#define     GPIO_PIN_RE9  (73U)
#define     GPIO_PIN_RF0  (80U)
#define     GPIO_PIN_RF1  (81U)
#define     GPIO_PIN_RF2  (82U)
#define     GPIO_PIN_RF3  (83U)
#define     GPIO_PIN_RF4  (84U)
#define     GPIO_PIN_RF5  (85U)
#define     GPIO_PIN_RF8  (88U)
#define     GPIO_PIN_RF12  (92U)
#define     GPIO_PIN_RF13  (93U)
#define     GPIO_PIN_RG0  (96U)
#define     GPIO_PIN_RG1  (97U)
#define     GPIO_PIN_RG6  (102U)
#define     GPIO_PIN_RG7  (103U)
#define     GPIO_PIN_RG8  (104U)
#define     GPIO_PIN_RG9  (105U)
#define     GPIO_PIN_RG12  (108U)
#define     GPIO_PIN_RG13  (109U)
#define     GPIO_PIN_RG14  (110U)
#define     GPIO_PIN_RG15  (111U)
#define     GPIO_PIN_RH0  (112U)
#define     GPIO_PIN_RH1  (113U)
#define     GPIO_PIN_RH2  (114U)
#define     GPIO_PIN_RH3  (115U)
#define     GPIO_PIN_RH4  (116U)
#define     GPIO_PIN_RH5  (117U)
#define     GPIO_PIN_RH6  (118U)
#define     GPIO_PIN_RH7  (119U)
#define     GPIO_PIN_RH8  (120U)
#define     GPIO_PIN_RH9  (121U)
#define     GPIO_PIN_RH10  (122U)
#define     GPIO_PIN_RH11  (123U)
#define     GPIO_PIN_RH12  (124U)
#define     GPIO_PIN_RH13  (125U)
#define     GPIO_PIN_RH14  (126U)
#define     GPIO_PIN_RH15  (127U)
#define     GPIO_PIN_RJ0  (128U)
#define     GPIO_PIN_RJ1  (129U)
#define     GPIO_PIN_RJ2  (130U)
#define     GPIO_PIN_RJ3  (131U)
#define     GPIO_PIN_RJ4  (132U)
#define     GPIO_PIN_RJ5  (133U)
#define     GPIO_PIN_RJ6  (134U)
#define     GPIO_PIN_RJ7  (135U)
#define     GPIO_PIN_RJ8  (136U)
#define     GPIO_PIN_RJ9  (137U)
#define     GPIO_PIN_RJ10  (138U)
#define     GPIO_PIN_RJ11  (139U)
#define     GPIO_PIN_RJ12  (140U)
#define     GPIO_PIN_RJ13  (141U)
#define     GPIO_PIN_RJ14  (142U)
#define     GPIO_PIN_RJ15  (143U)
#define     GPIO_PIN_RK0  (144U)
#define     GPIO_PIN_RK1  (145U)
#define     GPIO_PIN_RK2  (146U)
#define     GPIO_PIN_RK3  (147U)
#define     GPIO_PIN_RK4  (148U)
#define     GPIO_PIN_RK5  (149U)
#define     GPIO_PIN_RK6  (150U)
#define     GPIO_PIN_RK7  (151U)

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
#define    GPIO_PIN_NONE   (-1)

typedef uint32_t GPIO_PIN;

typedef  void (*GPIO_PIN_CALLBACK) ( GPIO_PIN pin, uintptr_t context);

void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortInterruptEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortInterruptDisable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: Local Data types and Prototypes
// *****************************************************************************
// *****************************************************************************

typedef struct {

    /* target pin */
    GPIO_PIN                 pin;

    /* Callback for event on target pin*/
    GPIO_PIN_CALLBACK        callback;

    /* Callback Context */
    uintptr_t               context;

} GPIO_PIN_CALLBACK_OBJ;

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
	 uint32_t xvalue = (uint32_t)value;
    GPIO_PortWrite((pin>>4U), (uint32_t)(0x1U) << (pin & 0xFU), (xvalue) << (pin & 0xFU));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return ((((GPIO_PortRead((GPIO_PORT)(pin>>4U))) >> (pin & 0xFU)) & 0x1U) != 0U);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (((GPIO_PortLatchRead((GPIO_PORT)(pin>>4U)) >> (pin & 0xFU)) & 0x1U) != 0U);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((pin>>4U), (uint32_t)0x1U << (pin & 0xFU));
}

#define GPIO_PinInterruptEnable(pin)       GPIO_PinIntEnable(pin, GPIO_INTERRUPT_ON_MISMATCH)
#define GPIO_PinInterruptDisable(pin)      GPIO_PinIntDisable(pin)

void GPIO_PinIntEnable(GPIO_PIN pin, GPIO_INTERRUPT_STYLE style);
void GPIO_PinIntDisable(GPIO_PIN pin);

bool GPIO_PinInterruptCallbackRegister(
    GPIO_PIN pin,
    const   GPIO_PIN_CALLBACK callBack,
    uintptr_t context
);

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
