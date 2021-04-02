NVM
#include utils/tester.fs
RAM

\ expected vocabulary (including tester.fs)
T{e WORDS e-> 946 -3945 }T

\ core: string with capured EMIT
: test-."" ." abc123" ;
: test-$"" $" abc123" ;
T{e test-."" e-> 6 444 }T
T{e test-$"" COUNT TYPE e-> 6 444 }T
T{e .( abc123) e-> 6 444 }T

\ core: numver output with capured EMIT
T{e -11 . e-> 4 175 }T
T{e -11 U. e-> 6 295 }T
T{e -11 5 .R e-> 5 207 }T
T{e -11 4 U.R e-> 5 263 }T
T{e 11 4 U.R e-> 4 162 }T

\ core: stack manipulation
T{ 1 2   OVER -> 1 2 1 }T
T{ 1 2   SWAP -> 2 1 }T
T{ 1 2 3 ROT  -> 2 3 1 }T
T{ 1 2 3 NIP  -> 1 3 }T
T{ 1 2 3 0 PICK -> 1 2 3 3 }T
T{ 1 2 3 2 PICK -> 1 2 3 1 }T
T{ 1 2 2DUP -> 1 2 1 2 }T
T{ 1 2 3 4 2DROP -> 1 2 }T

\ core: compare operations
T{ 10 -500 = -> 0 }T
T{ -500 -500 = -> -1 }T
T{ -500 0= -> 0 }T
T{ 0 0= -> -1 }T
T{ 10 -500 U< -> -1 }T
T{ -500 10 U< -> 0 }T
T{ 10 -500 < -> 0 }T
T{ -500 10 < -> -1 }T
T{ -500 0< -> -1 }T
T{ 0 0< -> 0 }T

\ core: 16 bit unary operations
T{ 32767 NEGATE -> -32767 }T
T{ -32767 ABS -> 32767 }T
T{ -1 1+ -> 0 }T
T{ 0 1- -> -1 }T
T{ -1 2+ -> 1 }T
T{ 1 2- -> -1 }T
T{ -1 2/ -> -1 }T
T{ 500 2/ -> 250 }T
T{ -1 2* -> -2 }T
T{ 500 2* -> 1000 }T

\ core: 16 bit binary operations
T{ 2 3 + -> 5 }T
T{ 255 -3 - -> 258 }T
T{ 255 -3 * -> -765 }T
T{ 767 3 / -> 255 }T
T{ 767 3 mod -> 2 }T
T{ 511 -5 /MOD -> -4 -103 }T
T{ -511 -5 /MOD -> -1 102 }T
T{ -511 5 /MOD -> 4 -103 }T

\ core: bit opperations
T{ 32767 NOT -> -32768 }T
T{ -1 $AA55 AND -1 XOR -> $55AA }T
T{ $55AA $0A05 OR -> $5FAF }T

\ core: double arithmetics
T{ 1 -1 UM+ -> 0 1 }T
T{ 1 -1 -2 M/MOD -> -1 32767 }T
T{ 1 -1 -2 UM/MOD -> 0 -1 }T
T{ 1000 -100 500 */ -> -200 }T
T{ -1000 55 101 */MOD -> 45 -545 }T
T{ -1 -1 UM* -> 1 -2 }T
T{ 31 -3010 M* -> -27774 -2 }T

\ core: test POSTPONE

: PIF POSTPONE IF ; IMMEDIATE
: PSWAP POSTPONE SWAP ; IMMEDIATE
: tpif PIF 123 ELSE 321 THEN ;
T{ -1 tpif -> 123 }T
T{ 0  tpif -> 321 }T
: tpswap PSWAP ;
T{ 1 -1  tpswap -> -1 1 }T

\ test background and idle tasks
#require 'IDLE
VARIABLE BGTEST  1 BGTEST !   \ flag: bgd not run
VARIABLE IDTEST  0 IDTEST !   \ flag: idl not run
: idl BGTEST @ IDTEST ! ;
' idl 'IDLE !  \ activate IDLE task
T{ 'IDLE @ -> ' idl }T
\ assumption: idl has been called at least once
T{ IDTEST @ -> 1 }T
: bgd -1 BGTEST ! ;
' bgd BG !     \ activate background task
T{ BG @ -> ' bgd }T
\ assumption bgd and idl have been called at least once
T{ IDTEST @ -> -1 }T

\ NVM features, 'BOOT vector, and COLD
NVM
VARIABLE varNVM
: startNVM   ( -- )   \ make cold respond with OK
   .OK ;
' startNVM 'BOOT !
RAM

\ extended: bit operations
T{ -511 EXG -> 510 }T
T{ 0 varNVM ! 1 varNVM 6 B! varNVM @ -> 16384 }T
T{ 258 varNVM ! 0 varNVM 1+ 1 B! varNVM @ -> 256 }T

\ extended: do leave +loop
T{ : GD2 DO I -1 +LOOP ; -> }T
T{ 1 4 GD2 -> 4 3 2 1 }T
T{ -1 2 GD2 -> 2 1 0 -1 }T

VARIABLE gditerations
VARIABLE gdincrement
: gd7 ( limit start increment -- )
   gdincrement !
   0 gditerations !
   DO
     1 gditerations +!
     I
     gditerations @ 6 = IF LEAVE THEN
     gdincrement @
   +LOOP gditerations @ ;
T{    4  4  -1 gd7 ->  4                  1  }T
T{    1  4  -1 gd7 ->  4  3  2  1         4  }T
\ 1 1 (limit) T{    4  1  -1 gd7 ->  1  0 -1 -2  -3  -4 6  }T
T{    4  1   0 gd7 ->  1  1  1  1   1   1 6  }T
\ 0 1 (limit)  T{    0  0   0 gd7 ->  0  0  0  0   0   0 6  }T
\ 4 1 (limit) T{    1  4   0 gd7 ->  4  4  4  4   4   4 6  }T
\ 4 1 (limit) T{    1  4   1 gd7 ->  4  5  6  7   8   9 6  }T
T{    4  1   1 gd7 ->  1  2  3            3  }T
\ 4 1 (limit) T{    4  4   1 gd7 ->  4  5  6  7   8   9 6  }T
\ 4 1 (limit) T{    2 -1  -1 gd7 -> -1 -2 -3 -4  -5  -6 6  }T
T{   -1  2  -1 gd7 ->  2  1  0 -1         4  }T
T{    2 -1   0 gd7 -> -1 -1 -1 -1  -1  -1 6  }T
\ 4 1 (limit) T{   -1  2   0 gd7 ->  2  2  2  2   2   2 6  }T
\ 4 1 (limit) T{   -1  2   1 gd7 ->  2  3  4  5   6   7 6  }T
T{    2 -1   1 gd7 -> -1 0 1              3  }T
T{  -20 30 -10 gd7 -> 30 20 10  0 -10 -20 6  }T
T{  -20 31 -10 gd7 -> 31 21 11  1  -9 -19 6  }T
T{  -20 29 -10 gd7 -> 29 19  9 -1 -11     5  }T

\ start over - we'll need some RAM
COLD

#require 2ROT
T{ 11 1 22 2 33 3 2ROT -> 22 2 33 3 11 1 }T
#require 2OVER
T{ 11 1 22 2 2OVER -> 11 1 22 2 11 1 }T
#require 2SWAP
T{ 11 1 22 2 2SWAP -> 22 2 11 1 }T

#require DNEGATE
#require DABS
#require D+
#require D-
#require D<
#require D=
T{ 27774 1 DNEGATE -> -27774 -2 }T
T{ -27774 -2 DABS -> 27774 1 }T
T{ -27774 1 DABS -> -27774 1 }T
T{ 1 -1 1 2 D+ -> 2 1 }T
T{ 2 1 1 2 D- -> 1 -1 }T
T{ 1 -1 2 -1 D< -> -1 }T
T{ 2 -1 1 -1 D< -> 0 }T
T{ 1 1 1 1 D< -> 0 }T
T{ 2 1 1 1 D< -> 0 }T
T{ 1 1 2 1 D< -> -1 }T
T{ 1 1 1 1 D= -> -1 }T

\ start over - we'll need some RAM
COLD

#require DSQRT
T{ 16960 15 DSQRT -> 1000 }T

\ start over and check if words were persisted
COLD

T{e startNVM e-> 4 260 }T
T{ varNVM -> 158 }T

\ test adding new words to NVM
NVM
\ extended: CREATE DOES>
T{ : CD>TEST CREATE 2* , DOES> @ ; -> }T
T{  -20 CD>TEST cdnvm -> }T
T{ cdnvm -> -40 }T
RAM

T{ 400 CD>TEST cdram -> }T
T{ cdram -> 800 }T

\ T{e WORDS e-> 973 -1508 }T


\ compile CURRENT and VOC as a test

#require CURRENT
#require VOC

T{ : a 1 ; -> }T
T{ : b 11 ; -> }T
T{ VOC abc -> }T
T{ abc DEFINITIONS -> }T
T{ : a 2 ; -> }T
T{ : b 22 ; -> }T
T{ FORTH DEFINITIONS -> }T
T{ a b -> 1 11 }T
T{ abc a abc b -> 2 22 }T
