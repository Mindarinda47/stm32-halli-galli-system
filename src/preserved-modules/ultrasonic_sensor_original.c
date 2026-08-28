/*
 * Preserved academic-project fragment.
 *
 * The original control flow is unchanged. Original comments were removed for
 * privacy/publication review. This is not the final integrated team source and
 * is not currently a standalone-buildable program.
 */

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "core_cm3.h"
#include "stm32f10x_exti.h"

#define PC_CRH *(volatile unsigned long *)0x40011004
#define PC_ODR *(volatile unsigned long *)0x4001100c
#define PC_IDR *(volatile unsigned long *)0x40011008

GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;

void delay_us(uint32_t us){
	if ( us > 1 ) {
		uint32_t count = us * 8 - 6;
		while(count--);
	}
	else{
		uint32_t count = 2;
		while(count--);
	}
}

void delay_ms(uint32_t ms){
	uint32_t us = 1000 * ms;
	delay_us(us);
}

void RCC_Configuration(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Configuration(void){

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t prescale = 0;

void setTIMER2() {
    prescale = (uint16_t) 7200 - 1;

    TIM_TimeBaseStructure.TIM_Period = 10000-1;
    TIM_TimeBaseStructure.TIM_Prescaler = prescale;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void trig_pulse(void)
{
    PC_ODR |= (1<<1);
    delay_us(11);
    PC_ODR &= ~(1<<1);
    delay_us(11);
}

unsigned long echo_time(void)
{
    unsigned long echo;
    trig_pulse();

    while((PC_IDR & 0x0000008) != 0x0000008);

    echo = TIM2->CNT;

    while((PC_IDR & 0x00000008) == 0x0000008);

    echo = TIM2->CNT - echo;

    return echo;
}

int main(void){
    SystemInit();

    RCC_Configuration();
    GPIO_Configuration();
    NVIC_Configuration();

    setTIMER2();

    unsigned long echo = 0;

    printf("\n\n HC-SR04 Test... \n\n");
    while(1)
    {
       echo = echo_time();

       printf("distance = %5d.%d mm\n",17*echo/100,(17*echo)%100);

       delay_ms(100);
    }
}

