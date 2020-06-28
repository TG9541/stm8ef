#include <stdint.h>
#include "stm8device.h"
#include "forth.h"

// The following declarations are just to provide a placeholder
// so that mixing-in C code with own memory gets easier

// When creating mixed C/Forth applications with Medium Density or
// High Density devices don't forget to adjust this address range!
volatile __at(0x30) uint8_t forthData[0x03FF-0x30];

// declare trap handler
void TRAP_Handler() __trap;

#ifdef STM8L
// Interrupt vectors for the simulated serial interface

// declare interrupt handler for Px.0 external interrupts
void EXTI0_IRQHandler() __interrupt (INTVEC_EXTI0);

// declare interrupt handler for Px.1 B external interrupts
void EXTI1_IRQHandler() __interrupt (INTVEC_EXTI1);

// declare interrupt handler for Px.2 external interrupts
void EXTI2_IRQHandler() __interrupt (INTVEC_EXTI2);

// declare interrupt handler for Px.3 external interrupts
void EXTI3_IRQHandler() __interrupt (INTVEC_EXTI3);

// declare interrupt handler for Px.4 external interrupts
void EXTI4_IRQHandler() __interrupt (INTVEC_EXTI4);

// declare interrupt handler for Px.5 external interrupts
void EXTI5_IRQHandler() __interrupt (INTVEC_EXTI5);

// declare interrupt handler for Px.6 external interrupts
void EXTI6_IRQHandler() __interrupt (INTVEC_EXTI6);

// declare interrupt handler for Px.7 external interrupts
void EXTI7_IRQHandler() __interrupt (INTVEC_EXTI7);

#else
// declare interrupt handler for Port A external interrupts
void EXTI0_IRQHandler() __interrupt (INTVEC_EXTI0);

// declare interrupt handler for Port B external interrupts
void EXTI1_IRQHandler() __interrupt (INTVEC_EXTI1);

// declare interrupt handler for Port C external interrupts
void EXTI2_IRQHandler() __interrupt (INTVEC_EXTI2);

// declare interrupt handler for Port D external interrupts
void EXTI3_IRQHandler() __interrupt (INTVEC_EXTI3);

// declare interrupt handler for Port E external interrupts
void EXTI4_IRQHandler() __interrupt (INTVEC_EXTI4);
#endif


#ifdef INTVEC_TIM1_UPDATE
// declare interrupt handler for TIM1 update overflow
void TIM1_IRQHandler() __interrupt (INTVEC_TIM1_UPDATE);
#endif

// declare interrupt handler for TIM2 update overflow
void TIM2_IRQHandler() __interrupt (INTVEC_TIM2_UPDATE);

// declare interrupt handler for TIM3 update overflow
void TIM3_IRQHandler() __interrupt (INTVEC_TIM3_UPDATE);

// declare interrupt handler for TIM4 ticker
void TIM4_IRQHandler() __interrupt (INTVEC_TIM4);

// main - start Forth
void main(void)
{
  forth();
}

