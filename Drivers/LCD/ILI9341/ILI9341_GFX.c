//	MIT License
//
//	Copyright (c) 2017 Matej Artnak
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.
//
//
//
//-----------------------------------
//	ILI9341 GFX library for STM32
//-----------------------------------
//
//	Very simple GFX library built upon ILI9342_STM32_Driver library.
//	Adds basic shapes, image and font drawing capabilities to ILI9341
//
//	Library is written for STM32 HAL library and supports STM32CUBEMX. To use the library with Cube software
//	you need to tick the box that generates peripheral initialization code in their own respective .c and .h file
//
//
//-----------------------------------
//	How to use this library
//-----------------------------------
//
//	-If using MCUs other than STM32F7 you will have to change the #include "stm32f4xx_hal.h" in the ILI9341_GFX.h to your respective .h file
//
//	If using "ILI9341_STM32_Driver" then all other prequisites to use the library have allready been met
//	Simply include the library and it is ready to be used
//
//-----------------------------------


#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "5x5_font.h"
#include "config.h"
#include <stdbool.h>

//#include "spi.h"
extern RNG_HandleTypeDef hrng;
extern uint16_t LCD_HEIGHT;
extern uint16_t LCD_WIDTH;
extern bool transferComplete;
//_FB1 static lv_color_t buf[TFT_HOR_RES * 48];
//_FB1 static uint16_t FrameBuf[15360];
static uint16_t FrameBuf[15360];


uint16_t ILI9341_RandColor(void)
{
  uint32_t rand = 0;
  rand = Rnd(&hrng);
  return rand&0x0000FFFF;
}
uint32_t Rnd(RNG_HandleTypeDef *hrng)
{
	uint32_t rand = 0;
	while(hrng->State == HAL_RNG_STATE_BUSY)
	{

	}
	HAL_RNG_GenerateRandomNumber(hrng, &rand);
	while(hrng->State == HAL_RNG_STATE_BUSY)
	{

	}
	return rand;
}
void lcd_random_rectangles(void)
{
    ILI9341_Fill_Screen(BLACK);
    
  for(int i=0;i<5000;i++)
    {
      /*
		if(transferComplete) {
      ILI9341_FillRect_DMA(Rnd(&hrng)%LCD_WIDTH,
              Rnd(&hrng)%LCD_HEIGHT,
              Rnd(&hrng)%LCD_WIDTH,
              Rnd(&hrng)%LCD_HEIGHT,
              ILI9341_RandColor());
			  }
			  else
			  {
				  lcdDelay(1);
			  }
			  */
	
			  
	  ILI9341_Draw_Rectangle(Rnd(&hrng)%LCD_WIDTH,
              Rnd(&hrng)%LCD_HEIGHT,
              Rnd(&hrng)%LCD_WIDTH,
              Rnd(&hrng)%LCD_HEIGHT,
              ILI9341_RandColor());
			  
     //lcdDelay(1);
    }
    lcdDelay(500);
    ILI9341_Fill_Screen(BLACK);
}

void lcd_random_circles(void)
{
    uint32_t x;
    uint32_t y;
	ILI9341_Fill_Screen(BLACK);
    for(int i=0;i<2000;i++)
    {
        HAL_RNG_GenerateRandomNumber(&hrng, &x);
        HAL_RNG_GenerateRandomNumber(&hrng, &y);
      ILI9341_Draw_Hollow_Circle(x%(LCD_WIDTH-20)+20, y%(LCD_HEIGHT-20)+20,  20,ILI9341_RandColor());
      lcdDelay(1);
    }
    lcdDelay(500);
    ILI9341_Fill_Screen(BLACK);
}
void lcd_fill_rand_colors(void)
{	
	ILI9341_Fill_Screen(ILI9341_RandColor());
	lcdDelay(500);
}
void lcd_random_lines(void)
{
     ILI9341_Fill_Screen(BLACK);    

  for(int i=0;i<4000;i++)
    {

        ILI9341_DrawLine(Rnd(&hrng)%LCD_WIDTH,
                                            Rnd(&hrng)%LCD_HEIGHT,
                                           Rnd(&hrng)%LCD_WIDTH,
                                            Rnd(&hrng)%LCD_HEIGHT, ILI9341_RandColor());
    //  lcdDelay(10);
    }
    lcdDelay(500);
    ILI9341_Fill_Screen(BLACK);  
}

void lcd_random_points(void)
{

      for(int i=0;i<4000;i++)
    {
      for(int j=0;j<100;j++)
      {

         ILI9341_Draw_Pixel(Rnd(&hrng)%LCD_WIDTH, Rnd(&hrng)%LCD_HEIGHT, BLACK);
      }     

      ILI9341_Draw_Pixel(Rnd(&hrng)%LCD_WIDTH, Rnd(&hrng)%LCD_HEIGHT, ILI9341_RandColor());
     // DelayMicro(100);
    }
   // lcdDelay(500);

}


void ILI9341_DrawLine( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
  int steep = abs(y2-y1)>abs(x2-x1);
  if(steep)
  {
    swap(x1,y1);
    swap(x2,y2);
  }
  if(x1>x2)
  {
    swap(x1,x2);
    swap(y1,y2);
  }
  int dx,dy;
  dx=x2-x1;
  dy=abs(y2-y1);
  int err=dx/2;
  int ystep;
  if(y1<y2) ystep=1;
  else ystep=-1;
  for(;x1<=x2;x1++)
  {
    if(steep) ILI9341_Draw_Pixel(y1,x1,color);
    else ILI9341_Draw_Pixel(x1,y1,color);
    err-=dy;
    if(err<0)
    {
      y1 += ystep;
      err+=dx;
    }
  }
}

/*Draw hollow circle at X,Y location with specified radius and Color. X and Y represent circles center */
void ILI9341_Draw_Hollow_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Color)
{
	int x = Radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (Radius << 1);

    while (x >= y)
    {
        ILI9341_Draw_Pixel(X + x, Y + y, Color);
        ILI9341_Draw_Pixel(X + y, Y + x, Color);
        ILI9341_Draw_Pixel(X - y, Y + x, Color);
        ILI9341_Draw_Pixel(X - x, Y + y, Color);
        ILI9341_Draw_Pixel(X - x, Y - y, Color);
        ILI9341_Draw_Pixel(X - y, Y - x, Color);
        ILI9341_Draw_Pixel(X + y, Y - x, Color);
        ILI9341_Draw_Pixel(X + x, Y - y, Color);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += (-Radius << 1) + dx;
        }
    }
}

/*Draw filled circle at X,Y location with specified radius and Color. X and Y represent circles center */
void ILI9341_Draw_Filled_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Color)
{
	
		int x = Radius;
    int y = 0;
    int xChange = 1 - (Radius << 1);
    int yChange = 0;
    int radiusError = 0;

    while (x >= y)
    {
        for (int i = X - x; i <= X + x; i++)
        {
            ILI9341_Draw_Pixel(i, Y + y,Color);
            ILI9341_Draw_Pixel(i, Y - y,Color);
        }
        for (int i = X - y; i <= X + y; i++)
        {
            ILI9341_Draw_Pixel(i, Y + x,Color);
            ILI9341_Draw_Pixel(i, Y - x,Color);
        }

        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
		//Really slow implementation, will require future overhaul
		//TODO:	https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles	
}

/*Draw a hollow rectangle between positions X0,Y0 and X1,Y1 with specified Color*/
void ILI9341_Draw_Hollow_Rectangle_Coord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t Color)
{
	uint16_t 	X_length = 0;
	uint16_t 	Y_length = 0;
	uint8_t		Negative_X = 0;
	uint8_t 	Negative_Y = 0;
	float 		Calc_Negative = 0;
	
	Calc_Negative = X1 - X0;
	if(Calc_Negative < 0) Negative_X = 1;
	Calc_Negative = 0;
	
	Calc_Negative = Y1 - Y0;
	if(Calc_Negative < 0) Negative_Y = 1;
	
	
	//DRAW HORIZONTAL!
	if(!Negative_X)
	{
		X_length = X1 - X0;		
	}
	else
	{
		X_length = X0 - X1;		
	}
	ILI9341_Draw_Horizontal_Line(X0, Y0, X_length, Color);
	ILI9341_Draw_Horizontal_Line(X0, Y1, X_length, Color);
	
	
	
	//DRAW VERTICAL!
	if(!Negative_Y)
	{
		Y_length = Y1 - Y0;		
	}
	else
	{
		Y_length = Y0 - Y1;		
	}
	ILI9341_Draw_Vertical_Line(X0, Y0, Y_length, Color);
	ILI9341_Draw_Vertical_Line(X1, Y0, Y_length, Color);
	
	if((X_length > 0)||(Y_length > 0)) 
	{
		ILI9341_Draw_Pixel(X1, Y1, Color);
	}
	
}

/*Draw a filled rectangle between positions X0,Y0 and X1,Y1 with specified Color*/
void ILI9341_FillRect_DMA(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{


  uint32_t block_size;
	if(x1>x2) swap(x1,x2);
	if(y1>y2) swap(y1,y2);
   ILI9341_Set_Address(x1, y1, x2, y2);
  //buf_size = (x2-x1+1)*(y2-y1+1)*2;
  block_size = (x2-x1+1)*(y2-y1+1);
  /*
  if(n<=307200)
  {
    cnt = 1;
    buf_size = n;
  }
  else
  {
    cnt = n/2;
    buf_size = 2;
    for(i = 3; i < n/3; i++)
    {
      if(n%i == 0)
      {
        cnt = i;
        buf_size = n/i;
        break;
      }
    }
  }
  */
 // uint16_t * lcdBuf = (uint16_t *)LCD_CMD_ADDRESS; // буфер экрана = LCD_CMD_ADDRESS;
 //SCB_DisableDCache();
 // uint16_t lcdBuf = (uint16_t *)LCD_CMD_ADDRESS;
  int len = sizeof(FrameBuf)/2;
  int cntr = 0;
  for(int i = 0; i < block_size; i++)
  {
        FrameBuf[cntr] = color;
		cntr++;
		if(cntr == len - 1)
		{
			cntr = 0;
			transferComplete = false;
			HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t)&FrameBuf[0] , /*(uint32_t)LCD->LCD_RAM*/( uint32_t ) 0x60080000, len);
			
			while(transferComplete == false)
			{				
				lcdDelay(1);
			}
			
			continue;
		}		
  }
  //if(cntr != 0)
 // transferComplete = false;
  //  HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t)&FrameBuf[0] , /*(uint32_t)LCD->LCD_RAM */ ( uint32_t ) 0x60080000, cntr);
	/*
				while(transferComplete == false)
			{
				
				lcdDelay(1);
			}
 */
}
void ILI9341_Draw_Filled_Rectangle_Coord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t Color)
{
	uint16_t 	X_length = 0;
	uint16_t 	Y_length = 0;
	uint8_t		Negative_X = 0;
	uint8_t 	Negative_Y = 0;
	int32_t 	Calc_Negative = 0;
	
	uint16_t X0_true = 0;
	uint16_t Y0_true = 0;
	
	Calc_Negative = X1 - X0;
	if(Calc_Negative < 0) Negative_X = 1;
	Calc_Negative = 0;
	
	Calc_Negative = Y1 - Y0;
	if(Calc_Negative < 0) Negative_Y = 1;
	
	
	//DRAW HORIZONTAL!
	if(!Negative_X)
	{
		X_length = X1 - X0;
		X0_true = X0;
	}
	else
	{
		X_length = X0 - X1;
		X0_true = X1;
	}
	
	//DRAW VERTICAL!
	if(!Negative_Y)
	{
		Y_length = Y1 - Y0;
		Y0_true = Y0;		
	}
	else
	{
		Y_length = Y0 - Y1;
		Y0_true = Y1;	
	}
	
	ILI9341_Draw_Rectangle(X0_true, Y0_true, X_length, Y_length, Color);	
}

/*Draws a character (fonts imported from fonts.h) at X,Y location with specified font Color, size and Background Color*/
/*See fonts.h implementation of font on what is required for changing to a different font when switching fonts libraries*/
void ILI9341_Draw_Char(char Character, uint8_t X, uint8_t Y, uint16_t Color, uint16_t Size, uint16_t Background_Color) 
{
		uint8_t 	function_char;
    uint8_t 	i,j;
		
		function_char = Character;
		
    if (function_char < ' ') {
        Character = 0;
    } else {
        function_char -= 32;
		}
   	
		char temp[CHAR_WIDTH];
		for(uint8_t k = 0; k<CHAR_WIDTH; k++)
		{
		temp[k] = font[function_char][k];
		}
		
    // Draw pixels
		ILI9341_Draw_Rectangle(X, Y, CHAR_WIDTH*Size, CHAR_HEIGHT*Size, Background_Color);
    for (j=0; j<CHAR_WIDTH; j++) {
        for (i=0; i<CHAR_HEIGHT; i++) {
            if (temp[j] & (1<<i)) {			
							if(Size == 1)
							{
              ILI9341_Draw_Pixel(X+j, Y+i, Color);
							}
							else
							{
							ILI9341_Draw_Rectangle(X+(j*Size), Y+(i*Size), Size, Size, Color);
							}
            }						
        }
    }
}

/*Draws an array of characters (fonts imported from fonts.h) at X,Y location with specified font Color, size and Background Color*/
/*See fonts.h implementation of font on what is required for changing to a different font when switching fonts libraries*/
void ILI9341_Draw_Text(const char* Text, uint8_t X, uint8_t Y, uint16_t Color, uint16_t Size, uint16_t Background_Color)
{
    while (*Text) {
        ILI9341_Draw_Char(*Text++, X, Y, Color, Size, Background_Color);
        X += CHAR_WIDTH*Size;
    }
}

/*Draws a full screen picture from flash. Image converted from RGB .jpeg/other to C array using online converter*/
//USING CONVERTER: http://www.digole.com/tools/PicturetoC_Hex_converter.php
//65K Color (2Bytes / Pixel)
void ILI9341_Draw_Image(const char* Image_Array, uint8_t Orientation)
{
	

		ILI9341_Set_Rotation(Orientation);
		ILI9341_Set_Address(0,0, LCD_WIDTH, LCD_HEIGHT);


		for(uint32_t i = 0; i < LCD_HEIGHT*LCD_WIDTH*2; i+=2)
		{	
			uint16_t color = ((uint16_t)(Image_Array[i] << 8) + (uint16_t)Image_Array[i+1]);		
			
			ILI9341_WriteData_16Bit(color);			

		}
	
}


