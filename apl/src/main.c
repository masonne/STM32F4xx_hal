#include <stdbool.h>
#include "stm32f4xx_hal.h"

void SysTick_Handler(void)
{
  HAL_IncTick();
}

int main(void) {
  HAL_Init();

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin : PD12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

  while (true) {
    HAL_Delay(500);
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
  }

  return 0;
} 
