/*
 * Preserved academic-project fragment.
 *
 * The original control flow is unchanged. Original comments were removed for
 * privacy/publication review. This is not the final integrated team source and
 * is not currently a standalone-buildable program.
 */

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define TOUCH_SENSOR_PIN GPIO_Pin_0
#define TOUCH_SENSOR_PORT GPIOA

#define OUTPUT_PIN GPIO_Pin_3
#define OUTPUT_PORT GPIOD

void GPIO_InitT(void) {

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = TOUCH_SENSOR_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
GPIO_Init(TOUCH_SENSOR_PORT, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = OUTPUT_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(OUTPUT_PORT, &GPIO_InitStructure);
}

void Delay(){
for (int i = 0; i < 2000000; i++){}
}

int main(void) {

GPIO_InitT();

while (1) {

if (GPIO_ReadInputDataBit(TOUCH_SENSOR_PORT, TOUCH_SENSOR_PIN) != 0) {

OUTPUT_PORT->BSRR = OUTPUT_PIN;
Delay();
GPIOD->BSRR = ~GPIO_Pin_All;
}

}
}

