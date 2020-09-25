// STM8 eForth: interrupt vectors for RM0031 STM8L Low/Med/High Density devices
#define STM8L

#define INTVEC_TLI            0
#define INTVEC_FLASH          1
#define INTVEC_DMA1_01        2
#define INTVEC_DMA1_23        3
#define INTVEC_RTC            4
#define INTVEC_PVD            5
#define INTVEC_EXTIB          6
#define INTVEC_EXTID          7
#define INTVEC_EXTI0          8
#define INTVEC_EXTI1          9
#define INTVEC_EXTI2         10
#define INTVEC_EXTI3         11
#define INTVEC_EXTI4         12
#define INTVEC_EXTI5         13
#define INTVEC_EXTI6         14
#define INTVEC_EXTI7         15
#define INTVEC_LCD           16  // STM8L152
#define INTVEC_CLK           17
#define INTVEC_ADC1          18
#define INTVEC_TIM2_UPDATE   19
#define INTVEC_TIM2_CAPCOM   20
#define INTVEC_TIM3_UPDATE   21
#define INTVEC_TIM3_CAPCOM   22
#define INTVEC_RI            23  // STM8L051F3
#define INTVEC_TIM1_UPDATE   23  // STM8L151, STM8L152
#define INTVEC_TIM1_CAPCOM   24
#define INTVEC_TIM4          25
#define INTVEC_SPI1          26
#define INTVEC_USART1_TXD    27
#define INTVEC_USART1_RXD    28
#define INTVEC_I2C1          29
