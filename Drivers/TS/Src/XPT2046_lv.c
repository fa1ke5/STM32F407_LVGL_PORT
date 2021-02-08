/**
 * @file XPT2046.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "XPT2046_lv.h"
#include "config.h"
#include "main.h"
#include "ILI9341_GFX.h"
#include "ILI9341_STM32_Driver.h"
#if USE_XPT2046

#include <stddef.h>
//#include LV_DRV_INDEV_INCLUDE
//#include LV_DRV_DELAY_INCLUDE

/*********************
 *      DEFINES
 *********************/
#define CMD_X_READ  0b10010000
#define CMD_Y_READ  0b11010000

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/
int16_t avg_buf_x[XPT2046_AVG];
int16_t avg_buf_y[XPT2046_AVG];
uint8_t avg_last;

     uint16_t last_x = 0;
     uint16_t last_y = 0;
     uint8_t last_state = 0;
static SPI_HandleTypeDef *_spi;
static SPI_HandleTypeDef hspi2;
uint8_t isTouched = 0;

//extern SPI_HandleTypeDef hspi2;

/* Параметры ориентации */
static touchOrienation _orient;
static uint16_t _width, _height;

static void _spi_init(void);
static void _XPT2046_TouchSelect(void);
static void _XPT2046_TouchUnselect(void);
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize the XPT2046
 */
void xpt2046_lv_init(void)
{
    //XPT2046_init(_spi, XPT2046_LANDSCAPE, XPT2046_HOR_RES, XPT2046_VER_RES);
    XPT2046_init(&hspi2, XPT2046_LANDSCAPE, XPT2046_HOR_RES, XPT2046_VER_RES);
}

/**
 * Get the current position and state of the touchpad
 * @param data store the read data here
 * @return false: because no ore data to be read
 */
#define READ_X 0x90
#define READ_Y 0xD0
	static const uint8_t _cmd_read_x[] = {READ_X};
	static const uint8_t _cmd_read_y[] = {READ_Y};
	static const uint8_t _zeroes_tx[] = {0x00, 0x00};

    static void _XPT2046_TouchSelect(void)
{
    HAL_GPIO_WritePin(XPT2046_CS_GPIO_Port, XPT2046_CS_Pin, GPIO_PIN_RESET);
}

static void _XPT2046_TouchUnselect(void)
{
    HAL_GPIO_WritePin(XPT2046_CS_GPIO_Port, XPT2046_CS_Pin, GPIO_PIN_SET);
}
void XPT2046_init(SPI_HandleTypeDef *spi, touchOrienation orientation, const uint16_t width, const uint16_t height) {
	_spi = spi;
	_orient = orientation;
	_width = width;
	_height = height;
}

bool XPT2046_TouchPressed(void)
{
    return HAL_GPIO_ReadPin(TS_IRQ_GPIO_Port, TS_IRQ_Pin) == GPIO_PIN_RESET;
}
//XPT2046_AVG
bool xpt2046_getXY(uint16_t* x, uint16_t* y)
{
    last_state = LV_INDEV_STATE_PR;
            	//Если включен контроль скорости SPI, то сохранение параметров и установка правильных значений
	#ifdef XPT2046_SPI_PARAM_CONTROL
	SPI_HandleTypeDef old_spi =  *_spi;//Сохранение старых параметров SPI
	_spi_init(); //Инициализация с правильными параметрами
	#endif
        _XPT2046_TouchSelect();

            HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);    
   
    uint32_t avg_x = 0;
    uint32_t avg_y = 0;
    uint8_t nsamples = 0;

    for(uint8_t i = 0; i < XPT2046_AVG; i++)
    {
        if(!XPT2046_TouchPressed())
        {
            last_state = LV_INDEV_STATE_REL;
            break;
        }
            

        nsamples++;

        HAL_SPI_Transmit(_spi, (uint8_t*)_cmd_read_y, sizeof(_cmd_read_y), HAL_MAX_DELAY);
        uint8_t y_raw[2];
        HAL_SPI_TransmitReceive(_spi, (uint8_t*)_zeroes_tx, y_raw, sizeof(y_raw), HAL_MAX_DELAY);

        HAL_SPI_Transmit(_spi, (uint8_t*)_cmd_read_x, sizeof(_cmd_read_x), HAL_MAX_DELAY);
        uint8_t x_raw[2];
        HAL_SPI_TransmitReceive(_spi, (uint8_t*)_zeroes_tx, x_raw, sizeof(x_raw), HAL_MAX_DELAY);

        avg_x += (((uint16_t)x_raw[0]) << 8) | ((uint16_t)x_raw[1]);
        avg_y += (((uint16_t)y_raw[0]) << 8) | ((uint16_t)y_raw[1]);
    }

    _XPT2046_TouchUnselect();

        	//Восстановление старых параметров
            
	#ifdef XPT2046_SPI_PARAM_CONTROL
	*_spi = old_spi; 
	//Инициализация с старыми параметрами
  if (HAL_SPI_Init(_spi) != HAL_OK) Error_Handler();
	#endif  

    if(nsamples < XPT2046_AVG)
    {
        return false;
    }

    uint32_t raw_x = (avg_x / XPT2046_AVG);
    if(raw_x <  XPT2046_X_MIN) raw_x = XPT2046_X_MIN;
    if(raw_x >  XPT2046_X_MAX) raw_x = XPT2046_X_MAX;

    uint32_t raw_y = (avg_y / XPT2046_AVG);
    if(raw_y < XPT2046_Y_MIN) raw_y = XPT2046_Y_MIN;
    if(raw_y > XPT2046_Y_MAX) raw_y = XPT2046_Y_MAX;

    #if XPT2046_XY_SWAP != 0
    int16_t swap_tmp;
    swap_tmp = *x;
    *x = *y;
    *y = swap_tmp;
    #endif

    *x = (raw_x - XPT2046_X_MIN) * XPT2046_HOR_RES / (XPT2046_X_MAX - XPT2046_X_MIN);
    *y = (raw_y - XPT2046_Y_MIN) * XPT2046_VER_RES / (XPT2046_Y_MAX - XPT2046_Y_MIN);
    #if XPT2046_X_INV != 0
         (*x) =  XPT2046_HOR_RES - (*x);
    #endif
    #if XPT2046_Y_INV != 0
        (*y) =  XPT2046_VER_RES - (*y);
    #endif
 //   HAL_NVIC_DisableIRQ(CTP_INT_IRQn);
   last_x = (*x);
    last_y = (*y);
   //  ILI9341_Draw_Filled_Circle(last_x - 1, last_y - 1, 2, RED);
    
  //  HAL_NVIC_EnableIRQ(CTP_INT_IRQn);
    


   // last_state = LV_INDEV_STATE_PR;
    return true;

}


bool xpt2046_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
         if(!XPT2046_TouchPressed() )
         {
           last_state = LV_INDEV_STATE_REL;
         }  
    int16_t x = 0;
    int16_t y = 0;

        x = last_x;
        y = last_y;

    data->point.x = (lv_coord_t)x;
    data->point.y = (lv_coord_t)y;
    data->state = last_state;// ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

    return false;
}

#ifdef XPT2046_SPI_PARAM_CONTROL
static void _spi_init(void) {
  _spi->Instance = SPI2;
  _spi->Init.Mode = SPI_MODE_MASTER;
  _spi->Init.Direction = SPI_DIRECTION_2LINES;
  _spi->Init.DataSize = SPI_DATASIZE_8BIT;
  _spi->Init.CLKPolarity = SPI_POLARITY_LOW;
  _spi->Init.CLKPhase = SPI_PHASE_1EDGE;
  _spi->Init.NSS = SPI_NSS_SOFT;
	//Делитель частоты SPI. Установите безопасное значение в XPT2046.h
  _spi->Init.BaudRatePrescaler = XPT2046_SPI_PRESCALER;
  _spi->Init.FirstBit = SPI_FIRSTBIT_MSB;
  _spi->Init.TIMode = SPI_TIMODE_DISABLE;
  _spi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  _spi->Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(_spi) != HAL_OK) Error_Handler();
}
#endif

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif