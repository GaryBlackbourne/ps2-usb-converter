#include "pro_clock_config.h"

#include "stm32f070x6.h"
#include "system_stm32f0xx.h"

void init_clocks(){
    
    RCC->CR |= RCC_CR_HSEON;                 // enable external oscillator as clk source
    RCC->CR |= RCC_CR_CSSON;                 // enable clock security system
    while(!(RCC->CR & RCC_CR_HSERDY));       // wait for HSE to stabilize

    RCC->CFGR |= RCC_CFGR_PLLMUL3;           // PLL multiplies clk by 3
    RCC->CFGR |= RCC_CFGR_PLLSRC_HSE_PREDIV; // select HSE for PLL source 
    RCC->CFGR |= RCC_CFGR_SW_PLL;            // select PLL for sysclk source

    RCC->CFGR2 |= RCC_CFGR2_PREDIV_DIV2;     // PLL input clk divided by 2

    /*
     * 48 MHz clk is needed for FS USB communication. This is generated
     * from 32 MHz HSE, divided by two (16MHz) and multiplied by 3 with PLL.(48MHz)
     */

    // RCC->CFGR3 |= RCC_CFGR3_USBSW_PLLCLK;    // set USB clk to PLLCLK(48MHz)
    
    return;
}

