/**
 * @file XPT2046.h
 *
 */

#ifndef XPT2046_H
#define XPT2046_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef LV_DRV_NO_CONF
#ifdef LV_CONF_INCLUDE_SIMPLE
//#include "lv_drv_conf.h"
#else
//#include "../../lv_drv_conf.h"
#endif
#endif
#include "config.h"
#if USE_XPT2046

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "../lvgl/lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/
#define XPT2046_SPI_PARAM_CONTROL
#define XPT2046_SPI_PRESCALER SPI_BAUDRATEPRESCALER_64 
/**********************
 *      TYPEDEFS
 **********************/
/* Ориентации дисплея */
typedef enum {
	XPT2046_LANDSCAPE,
	XPT2046_PORTRAIT,
	XPT2046_LANDSCAPE_180,
	XPT2046_PORTRAIT_180,
} touchOrienation;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

bool xpt2046_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
void XPT2046_init(SPI_HandleTypeDef *spi, touchOrienation orientation, const uint16_t width, const uint16_t height);
void xpt2046_lv_init(void);
bool xpt2046_getXY(uint16_t* x, uint16_t* y);
bool _xpt2046_getXY(void);
bool XPT2046_TouchPressed(void);

/**********************
 *      MACROS
 **********************/

#endif /* USE_XPT2046 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* XPT2046_H */