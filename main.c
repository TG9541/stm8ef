#include <stdint.h>
#include "forth.h"

// The following declarations are just to provide a placeholder
// so that mixing-in C code with own memory gets easier

volatile __at(0x50) uint8_t moduleData[0x10];

volatile __at(0x60) struct h {
  uint16_t sysBASE;     // BASE (BASEE)
  uint16_t sysEVAL;     // 'EVAL(INTER)
  uint16_t sysCONTEXT;  // CONTEXT pointer (LASTN)
  uint16_t sysCP;       // points to top of dictionary
  uint16_t sysULAST;    // ULAST (0)
  uint16_t sysTIB;      // TIB	(TIBB)
  uint16_t sysNTIB;     // #TIB	(0)
  uint16_t sysGtIN;     // >IN	(0)
  uint16_t sysHLD;      // HLD	(0)
  uint16_t sysTmp;      // tmp 	(0)
  uint16_t sysSP0;	    // initial data stack pointer
  uint16_t sysRP0;      // initial return stack pointer
  uint16_t sysXTEMP;    // scratchpad, also PROD1 for UM*
  uint16_t sysYTEMP;    // scratchpad, also PROD2 for UM*
  uint16_t sysPROD3;    // scratchpad for UM*
  uint16_t sysCARRY;    // scratchpad for UM*
} usrsysData;

volatile __at(0x0080) uint8_t ctopData[0x280];   // Start of user defined words, growing up
volatile __at(0x0300) uint8_t dstackData[0x80];  // Data stack, growing down
volatile __at(0x0380) uint8_t tibData[0x50];     // Terminal input buffer TIB, growing up
volatile __at(0x03D0) uint8_t rstackData[0x30];  // Return stack

// declare trap handler
void TRAP_Handler() __interrupt (1);

// declare interrupt handler for Port A external interrupts
void EXTI0_IRQHandler() __interrupt (3);

// declare interrupt handler for Port B external interrupts
void EXTI1_IRQHandler() __interrupt (4);

// declare interrupt handler for Port C external interrupts
void EXTI2_IRQHandler() __interrupt (5);

// declare interrupt handler for Port D external interrupts
void EXTI3_IRQHandler() __interrupt (6);

// declare interrupt handler for TIM2 update overflow
void TIM2_UO_IRQHandler() __interrupt (13);

// declare interrupt handler for TIM4 ticker
void TIM4_IRQHandler() __interrupt (23);

// main - just start Forth
void main(void)
{
  forth();
}

