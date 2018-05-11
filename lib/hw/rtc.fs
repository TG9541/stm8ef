\ STM8L internal RTC

\res MCU: STM8L051

\res export CLK_ECKCR
\res export CLK_CRTCR
\res export CLK_PCKENR2 
\res export RTC_WPR 
\res export RTC_ISR1
\res export RTC_TR1
\res export RTC_TR2
\res export RTC_TR3
\res export RTC_DR1
\res export RTC_DR2
\res export RTC_DR3

#require ]C!
#require ]B!

\ Print BCD byte with leading zero
: BCD. ( b -- )
    DUP
    [ $6E01 , ] \ Swap nibbles
    $0F AND $30 + EMIT \ MSD
    $0F AND $30 + EMIT \ LSD
;

\ Enable LSE generator
: LSE-INIT ( -- )
    [ 1 CLK_ECKCR 2 ]B! \ LSEON
    [ $7207 , $50C6 , $FB C, ] \ 1$:     BTJF    CLK_ECKCR,#3,1$   ; wait until LSERDY set
;

\ Initialize internal RTC with LSE
: RTC-INIT ( -- )
    LSE-INIT
    \ Use LSE generator for RTC
    [ $7200 , $50C1 , $FB C, ]  \ 2$:     BTJT    CLK_CRTCR,#0,2$   ; wait until RTCSWBSY reset
    [ $10 CLK_CRTCR ]C!         \ Select LSE for RTC
    \ Enable RTC
    [ 1 CLK_PCKENR2 2 ]B!       \ RTC[2]
;

\ Read RTC time registers
: RTC-TIME ( -- hh mm ss )
    RTC_TR1 c@ \ Seconds in BCD
    RTC_TR2 c@ \ Minutes in BCD
    RTC_TR3 c@ \ Hours in BCD
;

\ Output time hh:mm:ss
: RTC-TIME. ( -- )
    RTC-TIME
    BCD. $3A EMIT \ :
    BCD. $3A EMIT \ :
    BCD.
;

\ Read RTC time registers
: RTC-DATE ( -- YY MM DD dw )
    RTC_DR2 c@ \ Month in BCD
    DUP
    [ $6E01 , ] \ Swap nibbles in byte
    2/ $07 AND SWAP \ Week day to stack
    $1F AND \ Month to stack
    RTC_DR1 c@ \ Day in BCD
    SWAP \ Exchange day and month
    RTC_DR3 c@ \ Year in BCD
;

\ Output date YY-MM-DD
: RTC-DATE. ( -- )
    RTC-DATE
    BCD. $2D EMIT \ -
    BCD. $2D EMIT \ -
    BCD.
    DROP \ Skip week day
;

\ Enable edit RTC registers
: RTC-EDIT  ( -- )
    [ $CA RTC_WPR ]C!
    [ $53 RTC_WPR ]C!
    [ 1 RTC_ISR1 7 ]B!          \ Enter initialization mode
    [ $720D , $514C , $FB C, ]  \ 1$:     BTJF    RTC_ISR1,#6,1$   ; wait until enter init mode (bit INITF)
;

\ Disable edit RTC registers
: RTC-DONE ( -- )
    [ 0 RTC_ISR1 7 ]B!          \ Exit initialization mode
;

\ Set clock, BCD input
: RTC! ( YY MM DD DW hh mm ss -- )
    RTC-EDIT
    RTC_TR1 c! \ Seconds
    RTC_TR2 c! \ Minutes
    RTC_TR3 c! \ Hours
    SWAP RTC_DR1 c! \ Days
    [ $6E01 , ] \ Swap nibbles in byte
    2* $E0 AND \ Week day
    SWAP $1F AND OR \ Month
    RTC_DR2 c! \ Week day, Month
    RTC_DR3 c! \ Year
    RTC-DONE
;


\ ------------------------------------------------------------------------------
\\ Example:

\ Hardware requrements:
\ You need external low frequence crystall on 32768Hz.
\ Init LSE and enable internal RTC.
rtc-init 
hex
\ Set date/time
18 5 11 5 14 11 00 rtc-set \ may 11 2018, friday, 14:11:00

decimal
\ Print date and time. It is independet of radix.
cr rtc-date. space rtc-time. cr

