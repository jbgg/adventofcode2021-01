
#include <stdio.h>
#include <string.h>

#include "stm32l4xx_hal.h"

UART_HandleTypeDef UartHandle;

static void SystemClock_Config(void);
static void UART_Config(void);
static void GPIO_Config(void);

static void testpin(uint8_t v);

int main(void){

 HAL_Init();

 SystemClock_Config();

 GPIO_Config();
 UART_Config();

 HAL_UART_Transmit(&UartHandle,
   (uint8_t*)"XX\r\n",
   4, 0xffffffff);

 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
 HAL_Delay(250);
 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

 testpin(0);
 testpin(1);

 while(1)
  ;
}

static void testpin(uint8_t v){

 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 
   v ? GPIO_PIN_SET : GPIO_PIN_RESET);

 HAL_UART_Transmit(&UartHandle,
   (uint8_t*)"PB5: ",
   5, 0xffffffff);
 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)){
  HAL_UART_Transmit(&UartHandle,
    (uint8_t*)"ON!\r\n",
    5, 0xffffffff);
 }else{
  HAL_UART_Transmit(&UartHandle,
    (uint8_t*)"OFF!\r\n",
    6, 0xffffffff);
 }
 HAL_UART_Transmit(&UartHandle,
   (uint8_t*)"PB4: ",
   5, 0xffffffff);
 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)){
  HAL_UART_Transmit(&UartHandle,
    (uint8_t*)"ON!\r\n",
    5, 0xffffffff);
 }else{
  HAL_UART_Transmit(&UartHandle,
    (uint8_t*)"OFF!\r\n",
    6, 0xffffffff);
 }
}

static void GPIO_Config(void){

 GPIO_InitTypeDef  GPIO_InitStruct = {0};

 __HAL_RCC_GPIOA_CLK_ENABLE();
 __HAL_RCC_GPIOB_CLK_ENABLE();

 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4 | GPIO_PIN_5,
   GPIO_PIN_SET);
 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);

 /* LED */
 GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
 GPIO_InitStruct.Pull  = GPIO_NOPULL;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
 GPIO_InitStruct.Pin = GPIO_PIN_3;
 HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
 /* PB4 as input */
 GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
 GPIO_InitStruct.Pull  = GPIO_PULLUP;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
 GPIO_InitStruct.Pin = GPIO_PIN_4;
 HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
 /* PB5 as output opendrain */
 GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
 GPIO_InitStruct.Pull  = GPIO_PULLUP;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
 GPIO_InitStruct.Pin = GPIO_PIN_5;
 HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
 /* PA11 as output */
 GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
 GPIO_InitStruct.Pull  = GPIO_NOPULL;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
 GPIO_InitStruct.Pin = GPIO_PIN_11;
 HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void UART_Config(void){

 HAL_UART_MspInit(&UartHandle);

 __HAL_RCC_GPIOA_CLK_ENABLE();
 __HAL_RCC_GPIOB_CLK_ENABLE();
 __HAL_RCC_GPIOB_CLK_ENABLE();

 UartHandle.Instance        = USART2;
 UartHandle.Init.BaudRate     = 115200;
 UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
 UartHandle.Init.StopBits     = UART_STOPBITS_1;
 UartHandle.Init.Parity       = UART_PARITY_NONE;
 UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
 UartHandle.Init.Mode         = UART_MODE_TX_RX;
 UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
 UartHandle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;

 if(HAL_UART_DeInit(&UartHandle) != HAL_OK){
  while(1){
  }
 }
 if(HAL_UART_Init(&UartHandle) != HAL_OK){
  while(1){
  }
 }

}


static void SystemClock_Config(void)
{
 RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
 RCC_OscInitTypeDef RCC_OscInitStruct = {0};

 /* MSI is enabled after System reset, activate PLL with MSI as source */
 RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
 RCC_OscInitStruct.MSIState = RCC_MSI_ON;
 RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
 RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
 RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
 RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
 RCC_OscInitStruct.PLL.PLLM = 1;
 RCC_OscInitStruct.PLL.PLLN = 40;
 RCC_OscInitStruct.PLL.PLLR = 2;
 RCC_OscInitStruct.PLL.PLLP = 7;
 RCC_OscInitStruct.PLL.PLLQ = 4;
 if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
 {
  /* Initialization Error */
  while(1);
 }

 /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
  *      clocks dividers */
 RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
 RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
 RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
 RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
 RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
 if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
 {
  /* Initialization Error */
  while(1);
 }
}
