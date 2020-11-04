// The STM8 eForth core is in assembler but C code can be added here
// default for stm8device.h is STM8S but an STM8L header in the board
// folder has precedence

#include <stdint.h>
#include "stm8device.h"
#include "forth.h"

// The following declarations are just to provide a placeholder
// so that mixing-in C code with own memory gets easier

// Reserve RAM for Forth (not available for C)
volatile __at(FORTHRAM) uint8_t forthUser[1+UPPEND-FORTHRAM];
volatile __at(CTOPLOC)  uint8_t forthData[1+RAMEND-CTOPLOC];

// main - start Forth
void main(void)
{
  // initializations in C go here

  forth();              // the Forth REPL never returns

  // C code can be exported as Forth words and called from IDLE or Background tasks
  // alternatively use independent interrupt routines
}
