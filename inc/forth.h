// When creating mixed C/Forth applications, especially with Medium density or
// High density devices, assign memory by matching forthData[] start and size
// with the range defined in target.inc

// *** The Forth system ***

#define FORTHRAM 0x30
#define UPPEND   0x7f
#define CTOPLOC  0x80
#define RAMEND   0x03FF

// Forth will take possession of the return stack and it won't return!
// C-code should be exposed as Forth words or operate through interrupts
void forth(void);

// declare trap handler for Forth literals
void TRAP_Handler() __trap;


// *** Any interrupt that can be used for the simulated serial interface ***

#ifdef INTVEC_EXTI0
// declare interrupt handler for external interrupts STM8L:Px.0 or STM8S:PA
void EXTI0_IRQHandler() __interrupt (INTVEC_EXTI0);
#endif

#ifdef INTVEC_EXTI1
// declare interrupt handler for external interrupts STM8L:Px.1 or STM8S:PB
void EXTI1_IRQHandler() __interrupt (INTVEC_EXTI1);
#endif

#ifdef INTVEC_EXTI2
// declare interrupt handler for external interrupts STM8L:Px.2 or STM8S:PC
void EXTI2_IRQHandler() __interrupt (INTVEC_EXTI2);
#endif

#ifdef INTVEC_EXTI3
// declare interrupt handler for external interrupts STM8L:Px.3 or STM8S:PD
void EXTI3_IRQHandler() __interrupt (INTVEC_EXTI3);
#endif

#ifdef INTVEC_EXTI4
// declare interrupt handler for external interrupts STM8L:Px.4 or STM8S:PE
void EXTI4_IRQHandler() __interrupt (INTVEC_EXTI4);
#endif

#ifdef INTVEC_EXTI5
// declare interrupt handler for external interrupts STM8L:Px.5
void EXTI5_IRQHandler() __interrupt (INTVEC_EXTI5);
#endif

#ifdef INTVEC_EXTI6
// declare interrupt handler for external interrupts STM8L:Px.6
void EXTI6_IRQHandler() __interrupt (INTVEC_EXTI6);
#endif

#ifdef INTVEC_EXTI7
// declare interrupt handler for external interrupts STM8L:Px.7
void EXTI7_IRQHandler() __interrupt (INTVEC_EXTI7);
#endif


// *** Timer Interrupt handler for the simulated serial interface ***

#ifdef INTVEC_TIM4
// declare interrupt handler for TIM4 ticker
void TIM4_IRQHandler() __interrupt (INTVEC_TIM4);
#endif


// *** Any interrupt vector that can be used for the background task ***

#ifdef INTVEC_TIM1_UPDATE
// declare interrupt handler for TIM1 update overflow
void TIM1_IRQHandler() __interrupt (INTVEC_TIM1_UPDATE);
#endif

#ifdef INTVEC_TIM2_UPDATE
// declare interrupt handler for TIM2 update overflow
void TIM2_IRQHandler() __interrupt (INTVEC_TIM2_UPDATE);
#endif

#ifdef INTVEC_TIM3_UPDATE
// declare interrupt handler for TIM3 update overflow
void TIM3_IRQHandler() __interrupt (INTVEC_TIM3_UPDATE);
#endif
