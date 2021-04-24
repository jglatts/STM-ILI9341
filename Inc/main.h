#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f1xx_hal.h"

#define LCD_DC_PIN GPIO_PIN_0
#define LCD_DC_PORT GPIOB
#define LCD_RST_PIN GPIO_PIN_1
#define LCD_RST_PORT GPIOB
#define LCD_CS_PIN GPIO_PIN_10
#define LCD_CS_PORT GPIOB
#define MOSI_PIN GPIO_PIN_7
#define MOSI_RST_PORT GPIOA
#define SCK_PIN GPIO_PIN_5
#define SCK_PORT GPIOA
#define MAX_RADIUS 9

SPI_HandleTypeDef hspi1;

static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
void SystemClock_Config(void);
void Error_Handler(void);
void LCD_Draw_Circles(void);
void LCD_Test_Image(void);
void LCD_Test(void);

#endif /* __MAIN_H */
