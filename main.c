#include <stdint.h>
#include "forth.h"


static struct h {
  uint8_t  sysDummy0;   //  0 (1 defined by linker)
  uint16_t sysDummy1;   //  2 (unknown)
  uint16_t sysDummy2;   //  4 (unknown)
  uint16_t sysBASE;     //  6 BASE (BASEE)
  uint16_t SysTmp;      //  8 tmp 	(0)
  uint16_t sysGtIN;     // 10 >IN	(0)
  uint16_t sysHsTIB;    // 12 #TIB	(0)
  uint16_t sysTIB;      // 14 TIB	(TIBB)
  uint16_t sysEVAL;     // 16 'EVAL(INTER)
  uint16_t sysHLD;      // 18 HLD	(0)
  uint16_t sysCONTEXT;  // 20 CONTEXT pointer (LASTN)
  uint16_t sysULAST;    // 22 ULAST (0)
  uint16_t sysDummy24;  // 24 (unknown)
  uint16_t sysXTEMP;    // 26 also PROD1 ; ??? address called by CREATE
  uint16_t sysYTEMP;    // 28 also PROD2 ; ??? address called by CREATE
  uint16_t sysPROD3;    // 30 PROD1 .. PROD3 space for UM*
  uint16_t sysCARRY;    // 32 space for UM*
  uint16_t sysSP0;	    // 34 initial data stack pointer
  uint16_t sysRP0;      // 36 initial return stack pointer 

} rambase;

uint8_t userram[90];  // $0-$7F User RAM memory, system variables
uint8_t ctop[0x280];  // $80 Start of user defined words, linked to ROM dictionary
uint8_t dstack[0x90]; // $380 Data stack, growing downward
uint8_t tib;          // $390 Terminal input buffer TIB
                        // $3FF Return stack, growing downward

void TIM4_IRQHandler() __interrupt (23);

void main(void)
{
  forth(); 
}
