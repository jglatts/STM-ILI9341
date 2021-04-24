#include "main.h"
#include "ILI9341_STM32_Driver.h"
#include "birds.h"	// think is is too much
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int size;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_SPI1_Init();
  ILI9341_Init();
  //LCD_Test_Image();
  LCD_Draw_Circles();
  while (1)
  {
	  // nothing for now xD
	  // add an interrupt just for fun xD
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_SPI1_Init(void)
{
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitStruct.Pin = LCD_DC_PIN|LCD_RST_PIN|LCD_CS_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = MOSI_PIN|SCK_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void LCD_Draw_Circles(void)
{
	  srand((unsigned)time(NULL));
	  ILI9341_Fill_Screen(CYAN);
	  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  uint16_t colors[] = {0x03E0, 0x780F, 0xFFE0, 0xAFE5, 0xF81F};
	  for (uint8_t i = 0; i < 200; ++i)
	  {
		  uint16_t x_pos = rand() % ILI9341_SCREEN_WIDTH;
		  uint16_t y_pos = rand() % ILI9341_SCREEN_HEIGHT;
		  uint16_t radius = (rand() % MAX_RADIUS) + 1;
		  uint8_t  color = rand() % 5;
		  // add some random color to use
		  ILI9341_Draw_Filled_Circle(x_pos, y_pos, radius, colors[color]);
	  }
	  ILI9341_Draw_Text("Ya Mate!", 50, 50, BLACK, 4, CYAN);
}

void LCD_Test_Image()
{
	ILI9341_Fill_Screen(WHITE);
	ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	ILI9341_Draw_Text("RGB Picture", 10, 10, BLACK, 1, WHITE);
	ILI9341_Draw_Text("SMILEY", 10, 20, BLACK, 1, WHITE);
	HAL_Delay(2000);
	ILI9341_Draw_Image((const char*)birds, SCREEN_HORIZONTAL_1);
	ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	HAL_Delay(10000);
}

void LCD_Test(void)
{
	  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
	  ILI9341_Fill_Screen(CYAN);
	  ILI9341_Draw_Text("Hello World!", 20, 50, BLACK, 3, CYAN);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {

  }
}
