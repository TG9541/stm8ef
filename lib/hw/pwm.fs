
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

\ Example:
\   15  initTIM1
\   1000 relTIM1
\   800 pwm1
\   500 pwm2
\   200 pwm3

