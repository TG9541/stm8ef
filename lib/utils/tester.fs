\ eForth tester - inspired by forth2012-test-suite tester.fr
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md

\ (C) 1995 JOHNS HOPKINS UNIVERSITY/APPLIED PHYSICS LABORATORY
\     MAY BE DISTRIBUTED FREELY AS LONG AS THIS COPYRIGHT
\     NOTICE REMAINS.

VARIABLE #RESULTS
VARIABLE RESULTS 10 2* ALLOT

: SHOWRES   ( -- 1 )
   #RESULTS @ ?DUP IF
      1- DUP FOR DUP I - 2* RESULTS + ? NEXT DROP
   THEN 1 ;
: T{   ( -- ) ;
: ->   ( ... -- )
   \ save stack depth and result values
   DEPTH DUP #RESULTS !
   ?DUP IF
      1- FOR RESULTS I 2* + ! NEXT
   THEN ;
: }T   ( ... -- )
   \ compare saved results with expected values on stack
   DEPTH #RESULTS @ = IF
      DEPTH ?DUP IF
         1- FOR RESULTS I 2* + @ = WHILE NEXT
         ELSE R> DROP SHOWRES ABORT" INCORRECT RESULT" THEN
      THEN
   ELSE
      SHOWRES ABORT" WRONG NUMBER OF RESULTS"
   THEN ;

\ minimal output string test facility
\ tests (chars-count) (chars-sum mod 2^16)
\ usage e.g. T{e WORDS e-> 1005 1916 }T
VARIABLE Char#
VARIABLE CharSum
VARIABLE EmitV

: tEmit ( c -- )
   1 Char# +!  CharSum +! ;
: T{e ( -- )
   'EMIT @ EmitV !
   [ ' tEmit ] LITERAL 'EMIT !
   0 Char# ! 0 CharSum ! ;
: e-> ( -- n n )
   EmitV @ 'EMIT !
   Char# @ CharSum @ -> ;
