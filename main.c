#include <stdint.h>
#include "forth.h"

#define CLK_DIVR	(*(volatile uint8_t *)0x50c6)
#define CLK_PCKENR1	(*(volatile uint8_t *)0x50c7)

#define UART1_SR	(*(volatile uint8_t *)0x5230)
#define UART1_DR	(*(volatile uint8_t *)0x5231)
#define UART1_BRR1	(*(volatile uint8_t *)0x5232)
#define UART1_BRR2	(*(volatile uint8_t *)0x5233)
#define UART1_CR2	(*(volatile uint8_t *)0x5235)
#define UART1_CR3	(*(volatile uint8_t *)0x5236)

#define UART_CR2_TEN (1 << 3)
#define UART_CR3_STOP2 (1 << 5)
#define UART_CR3_STOP1 (1 << 4)
#define UART_SR_TXE (1 << 7)

#define PB_ODR	(*(volatile uint8_t *)0x5005)
#define PB_DDR	(*(volatile uint8_t *)0x5007)
#define PB_CR1	(*(volatile uint8_t *)0x5008)

static struct h {
  uint8_t  sysLinker;   // (0)0x00  (1 defined by linker)
  uint16_t sysDummy1;   //  2 0x01 (unknown)
  uint16_t sysDummy2;   //  4 0x02 (unknown)
  uint16_t sysBASE;     //  6 0x03 BASE (BASEE)
  uint16_t SysTmp;      //  8 0x04 tmp 	(0)
  uint16_t sysGtIN;     // 10 0x05 >IN	(0)
  uint16_t sysHsTIB;    // 12 0x06 #TIB	(0)
  uint16_t sysTIB;      // 14 0x07 TIB	(TIBB)
  uint16_t sysEVAL;     // 16 0x08 'EVAL(INTER)
  uint16_t sysHLD;      // 18 0x09 HLD	(0)
  uint16_t sysCONTEXT;  // 20 0x0A CONTEXT pointer (LASTN)
  uint16_t sysULAST;    // 22 0x0B ULAST (0)
  uint16_t sysDummy24;  // 24 (unknown)
  uint16_t sysXTEMP;    // 26 also PROD1 ; ??? address called by CREATE
  uint16_t sysYTEMP;    // 28 also PROD2 ; ??? address called by CREATE
  uint16_t sysPROD3;    // 30 PROD1 .. PROD3 space for UM*
  uint16_t sysCARRY;    // 32 space for UM*
  uint16_t sysSP0;	// 34 initial data stack pointer
  uint16_t sysRP0;      // 36 initial return stack pointer 
} rambase;

uint8_t userram[90];  // $0-$7F User RAM memory, system variables
uint8_t ctop[0x280];  // $80 Start of user defined words, linked to ROM dictionary
uint8_t dstack[0x90]; // $380 Data stack, growing downward
uint8_t tib;          // $390 Terminal input buffer TIB
                        // $3FF Return stack, growing downward



void main(void)
{
	CLK_DIVR = 0x00; // Set the frequency to 16 MHz
	CLK_PCKENR1 = 0xFF; // Enable peripherals

	UART1_CR2 = UART_CR2_TEN; // Allow TX and RX
	UART1_CR3 &= ~(UART_CR3_STOP1 | UART_CR3_STOP2); // 1 stop bit
	UART1_BRR2 = 0x03; UART1_BRR1 = 0x68; // 9600 baud

	PB_DDR = 0x20;
	PB_CR1 = 0x20;
	PB_ODR = 0x20;

  for (;;)
    forth(); 
}
