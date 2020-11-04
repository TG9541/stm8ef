// STM8S Low Density Device interrupt table - default configuration for STM8S

// A file with a matching name in the target configuration folder takes precedence.
// This means that this header file can be copied into a target configuration folders
// and changed to meet STM8S project requirements or replaced with a file for STM8L

#define INTVEC_TLI          0  // External top level interrupt
#define INTVEC_AWU          1  // Auto wake up from halt
#define INTVEC_CLK          2  // Clock controller
#define INTVEC_EXTI0        3  // Port A external interrupts
#define INTVEC_EXTI1        4  // Port B external interrupts
#define INTVEC_EXTI2        5  // Port C external interrupts
#define INTVEC_EXTI3        6  // Port D external interrupts
#define INTVEC_EXTI4        7  // Port E external interrupts
#define INTVEC_BECAN_RX     8  // beCAN RX interrupt
#define INTVEC_BECAN_TX     8  // beCAN TX/ER/SC interrupt
#define INTVEC_SPI         10  // End of transfer
#define INTVEC_TIM1_UPDATE 11  // TIM1 update/overflow/underflow/trigger/break
#define INTVEC_TIM1_CAPCOM 12  // TIM1 capture/compare
#define INTVEC_TIM2_UPDATE 13  // TIM2 update /overflow
#define INTVEC_TIM2_CAPCOM 14  // TIM2 capture/compare
#define INTVEC_TIM3_UPDATE 15  // TIM3 update /overflow
#define INTVEC_TIM3_CAPCOM 16  // TIM3 capture/compare
#define INTVEC_UART1_TXD   17  // 1st UART (LD/HD:UART1) Tx complete
#define INTVEC_UART1_RXD   18  // 1st UART (LD/HD:UART1) Receive register DATA FULL
#define INTVEC_I2C         19  // I2C interrupt
#define INTVEC_UART2_TXD   20  // 2nd UART (MD:UART2, HD:UART3) Tx complete
#define INTVEC_UART2_RXD   21  // 2nd UART (MD:UART2, HD:UART3) Receive register DATA FULL
#define INTVEC_ADC1        22  // ADC1 end of conversion/analog watchdog interrupt
#define INTVEC_TIM4        23  // TIM4 update/overflow
#define INTVEC_FLASH       24  // EOP/WR_PG_DIS

