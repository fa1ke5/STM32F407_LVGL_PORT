#ifndef __CONFIG_H
#define __CONFIG_H

//#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal.h"
//CHIP SELECT PIN AND PORT, STANDARD GPIO
#define LCD_CS_PORT								GPIOC
#define LCD_CS_PIN								CS_Pin

//DATA COMMAND PIN AND PORT, STANDARD GPIO
#define LCD_DC_PORT								GPIOC
#define LCD_DC_PIN								DC_Pin

//RESET PIN AND PORT, STANDARD GPIO
#define	LCD_RST_PORT							GPIOC
#define	LCD_RST_PIN								GPIO_PIN_0

#define	LCD_BL_PORT							    GPIOB
#define	LCD_BL_PIN                              GPIO_PIN_1

#define TS_INT_PORT                             
#define TS_INT_PIN

#define USERTOS                                 0

#define _FB __attribute__ ((section(".data-buff")))
#define _CCMC __attribute__ ((section(".ccmram")))
#define _CCMD __attribute__ ((section(".ccmram-data")))

#define FB_SIZE 32

#define USE_XPT2046 1
/* --------------
 * XPT2046
 * -------------- */
#ifndef USE_XPT2046
#define USE_XPT2046 0
#endif

#define XPT2046_CS_GPIO_Port        TS_CS_GPIO_Port
#define XPT2046_CS_Pin              TS_CS_Pin

#define XPT2046_IRQ_GPIO_Port       TS_IRQ_GPIO_Port
#define XPT2046_IRQ_Pin             TS_IRQ_Pin
#define CTP_INT_IRQn                EXTI9_5_IRQn

//#define TS_CS_Pin GPIO_PIN_12
//
//#define TS_CS_GPIO_Port GPIOB


#define LV_DRV_INDEV_INCLUDE     <stdint.h>             /*Dummy include by default*/
#define LV_DRV_INDEV_RST(val)    /*pin_x_set(val)*/     /*Set the reset pin to 'val'*/
#define LV_DRV_INDEV_IRQ_READ    (uint8_t)HAL_GPIO_ReadPin(TS_INT_PORT, TS_INT_PIN) /*pn_x_read()*/      /*Read the IRQ pin*/

#if USE_XPT2046
#define XPT2046_HOR_RES 320
#define XPT2046_VER_RES 240
#define XPT2046_X_MIN 1700 //200
#define XPT2046_Y_MIN 1700 //200
#define XPT2046_X_MAX 30200 //3800
#define XPT2046_Y_MAX 30400//3800
#define XPT2046_AVG 16
#define XPT2046_X_INV 1
#define XPT2046_Y_INV 1
#define XPT2046_XY_SWAP 0
#endif



#endif