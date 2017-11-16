\ STM8S103 Timer1 PWM
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md

#include STARTTEMP

  \res MCU: STM8103
  \res export TIM1_PSCRH
  \res export TIM1_BKR
  \res export TIM1_CCMR1
  \res export TIM1_CCMR2 
  \res export TIM1_CCMR3 
  \res export TIM1_CCER1
  \res export TIM1_CCER2
  \res export TIM1_CR1
  \res export TIM1_ARRH
  \res export TIM1_CCR1H
  \res export TIM1_CCR2H
  \res export TIM1_CCR3

TARGET

\ Init Timer1 with prescaler ( n=15 -> 1 MHz), CC PWM1..PWM3
: T1PwmInit ( n -- )
  TIM1_PSCRH 2C!
  $80 TIM1_BKR C!
  $60 TIM1_CCMR1 C!
  $60 TIM1_CCMR2 C!
  $60 TIM1_CCMR3 C!
  $11 TIM1_CCER1 C!
  $01 TIM1_CCER2 C!
  1   TIM1_CR1 C!
;

\ Set Timer1 reload value
: T1Reload ( n -- )
  TIM1_ARRH 2C!
;

\ Set PWM1 compare value
: PWM1 ( n -- )
  TIM1_CCR1H 2C!
;

\ Set PWM2 compare value
: PWM2 ( n -- )
  TIM1_CCR2H 2C!
;

\ Set PWM3 compare value
: PWM3 ( n -- )
  TIM1_CCR3H 2C!
;

\ convert duty cycle [1/1000] to PWM reload value
: duty ( n -- n )
  TIM1_ARRH 2C@ 1000 */
;

ENDTEMP

\\ Example:

 15  initTIM1
 1000 relTIM1
 800 pwm1
 500 pwm2
 200 pwm3
