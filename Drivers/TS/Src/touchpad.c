/**
 * @file indev.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
//#include "hal_stm_lvgl/tft/tft.h"
#include "../lvgl/lvgl.h"
#include "../lvgl/src/lv_font/lv_symbol_def.h"
#include "XPT2046_lv.h"
#include "stm32f4xx_hal.h"

/*********************
 *      DEFINES
 *********************/
/**********************
 *      TYPEDEFS
 **********************/
extern SPI_HandleTypeDef hspi2;
/**********************
 *  STATIC PROTOTYPES
 **********************/
//static bool touchpad_read_cb(lv_indev_drv_t * drv, lv_indev_data_t *data);

/**********************
 *  STATIC VARIABLES
 **********************/
//static TS_StateTypeDef  TS_State;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize your input devices here
 */
lv_indev_t * indev_touchpad;
void lv_touchpad_init(void)
{

  xpt2046_lv_init();
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.read_cb = xpt2046_read;
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_touchpad = lv_indev_drv_register(&indev_drv);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/
/*
static bool touchpad_read_cb(lv_indev_drv_t * drv, lv_indev_data_t *data)
{
	static int16_t last_x = 0;
	static int16_t last_y = 0;
	BSP_TS_GetState(&TS_State);
	if(TS_State.touchDetected != 0) {
		data->point.x = TS_State.touchX[0];
		data->point.y = TS_State.touchY[0];
		last_x = data->point.x;
		last_y = data->point.y;
		data->state = LV_INDEV_STATE_PR;
	} else {
		data->point.x = last_x;
		data->point.y = last_y;
		data->state = LV_INDEV_STATE_REL;
	}

	return false;
}
*/