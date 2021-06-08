#include "main.h"
#include "ILI9341_STM32_Driver.h"
#include "birds.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int size, val;
int check = 0;

uint16_t colors[] = {
	BLACK,
	NAVY,
	DARKGREEN,
	DARKCYAN,
	MAROON,
	PURPLE,
	OLIVE,
	LIGHTGREY,
	DARKGREY,
	BLUE,
	GREEN,
	RED,
	MAGENTA,
	YELLOW,
	WHITE,
	ORANGE,
	GREENYELLOW,
	PINK
};

const char* words[] = {
		"Gang Gang!",
		"Ya Mate!",
		"JDG 2021!",
		"Jim Croce!",
		"Maury!",
		"Fuck Ya!"
};

int main(void)
{
  HAL_Init();
  size = sizeof(birds) / sizeof(birds[0]);
  SystemClock_Config();
  MX_GPIO_Init();
  MX_SPI1_Init();
  ILI9341_Init();
  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
  ILI9341_Fill_Screen(CYAN);
  //LCD_Test_Image();
  //LCD_Draw_Circles();
  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
  LCD_Draw_Rand_Smiley();
  /*
  LCD_Draw_Smiley(10, 20);
  LCD_Draw_Smiley(30, 50);
  LCD_Draw_Smiley(50, 80);
  LCD_Draw_Smiley(70, 110);
  */
  while (1)
  {

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
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_8) // If The IT Source Is EXTI Line8 (A8 Pin)
    {
    	check = 1;
    	/*
    	// shorten this guy up
    	__HAL_GPIO_EXTI_CLEAR_IT(EXTI9_5_IRQn);
    	ILI9341_Fill_Screen(CYAN);
    	ILI9341_Draw_Text("INTERRUPTED!", 10, 10, BLACK, 1, CYAN);
    	for (int i = 0; i < 1000; i++) { } // wait a lil
    	//__HAL_GPIO_EXTI_CLEAR_IT(EXTI9_5_IRQn);
		*/
	}
}

void LCD_Draw_Circles(void)
{
	  srand((unsigned)time(NULL));
	  ILI9341_Fill_Screen(CYAN);
	  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  // replace these with the macro names
	  while (1)
	  {
		  for (uint8_t i = 0; i < 100; ++i)
		  {
			  int r = rand();
			  uint16_t x_pos = r % ILI9341_SCREEN_WIDTH;
			  uint16_t y_pos = r % ILI9341_SCREEN_HEIGHT;
			  uint16_t radius = (r % MAX_RADIUS) + 1;
			  uint8_t  color = r % 19;
			  uint8_t  msg = r % 6;
			  // add some random color to use
			  ILI9341_Draw_Filled_Circle(x_pos, y_pos, radius, colors[color]);
			  ILI9341_Draw_Text(words[msg], r % 300, r % 200, colors[color], (r % 6) + 1, CYAN);
		  }
		  ILI9341_Fill_Screen(CYAN);
		  //ILI9341_Draw_Text("Ya Mate!", 50, 50, BLACK, 4, CYAN);
	  }
}

void LCD_Test_Image()
{
	// get images working ;)
	ILI9341_Fill_Screen(WHITE);
	ILI9341_Set_Rotation(SCREEN_VERTICAL_1);
	ILI9341_Draw_Text("RGB Picture", 10, 10, BLACK, 1, WHITE);
	ILI9341_Draw_Text("SMILEY", 10, 20, BLACK, 1, WHITE);
	HAL_Delay(2000);
	//ILI9341_Fill_Screen(WHITE);
	ILI9341_Draw_Image((const char*)birds, SCREEN_VERTICAL_1);
	//ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	//HAL_Delay(10000);
}

void LCD_Draw_Smiley(int x_pos, int y_pos, uint16_t color)
{
	//ILI9341_Fill_Screen(CYAN);
	//ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	ILI9341_Draw_Filled_Circle(x_pos, y_pos, 5, color);
	ILI9341_Draw_Filled_Circle(x_pos + 15, y_pos, 5, color);
	ILI9341_Draw_Filled_Circle_Half(x_pos + 8, y_pos + 15, 9, color);
}

void LCD_Draw_Rand_Smiley() {
	while(1) {
		if (check) {
			ILI9341_Fill_Screen(CYAN);
			ILI9341_Draw_Text("INTERRUPTED!", 10, 10, BLACK, 1, CYAN);
			HAL_Delay(500);
			check = 0;
		}
		int c = rand() % 19;
		ILI9341_Fill_Screen(colors[c]);
		for (uint8_t i = 0; i < 30; ++i)
		{
			if (check) {
				ILI9341_Fill_Screen(CYAN);
				ILI9341_Draw_Text("INTERRUPTED!", 10, 10, BLACK, 1, CYAN);
				HAL_Delay(500);
				check = 0;
			}
			int r = rand();
			LCD_Draw_Smiley(r % 300, r % 200, colors[r % 19]);
			ILI9341_Draw_Text(words[r % 6], r % 300, r % 200, colors[r % 19], (r % 6) + 1, colors[c]);
		}
		ILI9341_Fill_Screen(colors[c]);
		check = 0;
	}
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
