#include utils/tester.fs

\ expected vocabulary (uncluding tester.fs)
T{e WORDS e-> 978 -835 }T

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
\ uCsim seems to flip BASE to HEX in UM+ or M/MOD opertion!
T{ 1 -1 -2 M/MOD -> -1 32767 }T
T{ 1 -1 -2 UM/MOD -> 0 -1 }T
T{ 1000 -100 500 */ -> -200 }T
T{ -1000 55 101 */MOD -> 45 -545 }T
T{ -1 -1 UM* -> 1 -2 }T
T{ 31 -3010 M* -> -27774 -2 }T
T{ -27774 -2 DNEGATE -> 27774 1 }T

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

COLD

\ start over and check if words were persisted
#include utils/tester.fs
T{e startNVM e-> 4 260 }T
T{ varNVM -> 128 }T

\ test adding new words to NVM
NVM
\ extended: CREATE DOES>
T{ : CD>TEST CREATE 2* , DOES> @ ; -> }T
T{  -20 CD>TEST cdnvm -> }T
T{ cdnvm -> -40 }T
RAM

T{ 400 CD>TEST cdram -> }T
T{ cdram -> 800 }T

T{e WORDS e-> 1014 2266 }T
