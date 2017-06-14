file
RAM
\ need the following headers defined
\ OVERT branch 0 1 NAME> 
: OVERT [ $CC C, $8CEA , ] ;
: branch [ OVERT $CC C, $82FA ,
: 0 [ OVERT $CC C, $847A ,
: 1 [ OVERT $CC C, $847D ,
: NAME> [ OVERT $CC C, $8996 ,



\ constants needed only for compilation
\  so put them in ram 
\  ensure no links to these words

\ RAMBASE = 0
: UPP $60 ;
  \ UPP (user/system area) location for 1K RAM
: USRLAST 12 UPP + ; 
  \ currently last name in dictionary (init: to LASTN)
  



NVM \ make comment to just create in ram

\ the following words replicate the assembler versions 
\  in forth.asm for output and stack effects, 
\  but are not necessarily as efficient as might be 
\  coded without that constraint

:  (       \ -- ) 
  \ Ignore following string up to next ).
  \ A comment.
  $29 \ ")" ) 
  PARSE 2DROP ; IMMEDIATE

: .(      ( -- )
  \ Output following string up to next ) .
  $29 \ ")"
  PARSE TYPE ; IMMEDIATE

: [COMPILE]       ( -- ; <string> )
  \ Compile next word into code dictionary.
  ' CALL, ;
  IMMEDIATE
  
: EXIT    ( -- )
  \ Terminate a colon definition.
  [ OVERT
  $9085 , 		\ POPW    Y
  $81 C, 		\ RET

: IF      ( -- A )
  \ Begin a conditional branch.
  COMPILE ?branch HERE 0 , ;
  IMMEDIATE

: THEN    ( A -- )
  \ Terminate a conditional branch structure.
  HERE SWAP ! ;
  IMMEDIATE

: AHEAD   ( -- A )
  \ Compile a forward branch instruction.
  $CC ( BRAN_OPC ) C,  HERE  0 , ;
  IMMEDIATE

: ELSE    ( A -- A )
  \ Start the false clause in an IF-ELSE-THEN structure.
  [COMPILE] AHEAD SWAP [COMPILE] THEN ;
  IMMEDIATE

\ COMPILE bug: needs to handle CALLR as well as CALL
\  needs to be after IF ELSE THEN, but before FOR, NEXT
\ Expect Redef
: COMPILE ( -- )
  \ Compile next CALL (incl CALLR) in
  \  colon list to code dictionary.
  R> DUP C@ $CD - 0= IF \ CALL
    1+ DUP @ ELSE \ assume CALLR = $AD
    DUP 1+ C@ DUP $80 - 0< NOT IF $FF00 + THEN + 2+ THEN
  CALL, 2+ >R ;

: FOR     ( -- a )
  \ Start a FOR-NEXT loop structure in a colon definition.
  COMPILE >R HERE ;
  IMMEDIATE 
  
: NEXT    ( a -- )
  \ Terminate a FOR-NEXT loop.
 COMPILE donxt , ;
 IMMEDIATE 

: DO      ( -- a )
  \ Start a DO LOOP loop structure in a colon definition.
  \ LOOP address cell for usage by LEAVE at runtime
  0  [COMPILE] LITERAL
  \ any changes here require an offset adjustment in PLOOP
  COMPILE >R COMPILE SWAP COMPILE >R [COMPILE] FOR ;
  IMMEDIATE

\ The only reference to (+loop) is in +LOOP
\  so it can be removed from core
\ But, it is all in assembler!
\  Good news, the assembler code is relocatable
\   Well, nearly: got 3 external addresses to resolve
\  So, just stuff in the assembled byte codes
\ And we need LEAVE as well
: LEAVE   ( -- )
  \ Leave a DO .. LOOP/+LOOP loop.
  [ OVERT
	      \ LEAVE:
  $5B06 , 		\ ADDW    SP,#6
  $9085 , 		\ POPW    Y 
    \ DO leaves the address of +loop on the R-stack
  $90 C, $EC02 , 	\ JP      (2,Y)

: (+loop) ( +n -- )
  \ Add n to index R@ and test for lower than limit (R-CELL)@.
  [ OVERT
		\ DOPLOOP:
  $1605 , 		\ LDW     Y,(5,SP)
  $90 C, $BF7E ,	\ LDW     YTEMP,Y
  $9093 ,		\ LDW     Y,X
  $90FE , 		\ LDW     Y,(Y)
  $909E , 		\ LD      A,YH
  $5C C,		\ INCW    X
  $5C C,		\ INCW    X
  $72 C, $F903 , 	\ ADDW    Y,(3,SP)
  $90 C, $B37E , 	\ CPW     Y,YTEMP
  $8A C, 		\ PUSH    CC
  $4D C, 		\ TNZ     A
  $2B05 ,		\ JRMI    1$
  $86 C,		\ POP     CC
  $2E0A ,		\ JRSGE   LEAVELOC
  $2003 , 		\ JRA     2$
  $86 C, 	\ 1$:     POP     CC
  $2F05 , 		\ JRSLT   LEAVELOC
  $1703 , 	\ 2$:     LDW     (3,SP),Y
  $CC C, 
   ' branch ,		\ JP      BRAN
		\ LEAVELOC
  $CC C, ' LEAVE ,	\ JP      LEAVE
 
: +LOOP   ( a +n -- )
  \ Terminate a DO - +LOOP loop.
  COMPILE (+loop) 
  HERE OVER \ use mark from DO/FOR, apply negative offset
  $0E - ! \ patch DO runtime code for LEAVE
  , ;
  IMMEDIATE

: LOOP    ( a -- )
  \ Terminate a DO-LOOP loop.
  COMPILE  [COMPILE] 1 [COMPILE] +LOOP ;
  IMMEDIATE

\ Expect WORDS_EXTRACORE = 0 when BAREBONES = 1
\  but I is such a standard and useful word
: I  ( -- n )
  \ Get inner FOR-NEXT or DO-LOOP index value
  R@ ;
  
: BEGIN   ( -- a )
  \ Start an infinite or indefinite loop structure.
  HERE ;
  IMMEDIATE

: UNTIL   ( a -- )
  \ Terminate a BEGIN-UNTIL indefinite loop structure.
  COMPILE ?BRANCH , ;
  IMMEDIATE

: AGAIN   ( a -- )
  \ Terminate a BEGIN-AGAIN infinite loop structure.
  $CC ( BRAN_OPC ) C,  , ;
  IMMEDIATE

: WHILE   ( a -- A a )
  \ Conditional branch out of a BEGIN-WHILE-REPEAT loop.
  IF SWAP ;
  IMMEDIATE

: REPEAT  ( A a -- )
  \ Terminate a BEGIN-WHILE-REPEAT indefinite loop.
  [COMPILE] AGAIN [COMPILE] THEN ;
  IMMEDIATE

: AFT     ( a -- a A )
  \ Jump to THEN in a FOR-AFT-THEN-NEXT 
  \  loop the first time through.
  DROP [COMPILE] AHEAD HERE SWAP ;
  IMMEDIATE
  
: OR      ( w w -- w )    ( TOS STM8: -- immediate Y,Z,N )
  \ Bitwise inclusive OR.
  [ OVERT
  $E601 , 		\ LD      A,(1,X)         ; D=w
  $EA03 , 		\ OR      A,(3,X)
  $E703 , 		\ LD      (3,X),A
  $F6 C, 		\ LD      A,(X)
  $EA02 , 		\ OR      A,(2,X)
  $E702 , 		\ LD      (2,X),A
  $CC C, ' DROP , 	\ JP      DROP

: =       ( w w -- t )    ( TOS STM8: -- Y,Z,N )
  \ Return true if top two are equal.
  XOR 0= ;
  
: <       ( n1 n2 -- t )
  \ Signed compare of top two items.
  - 0< ;
  
: MIN     ( n n -- n )    ( TOS STM8: -- Y,Z,N )
  \ Return smaller of top two items.
  2DUP < NOT IF SWAP THEN DROP ;

: MAX     ( n n -- n )    ( TOS STM8: -- Y,Z,N )
  \ Return greater of two top items.
  2DUP < IF SWAP THEN DROP ;
  
: SPACES  ( +n -- )
  \ Send n spaces to output device.
 1- 0 MAX FOR SPACE NEXT ;

: U.      ( u -- )
  \ Display an unsigned integer in free format.
  <# #S #> SPACE TYPE ;  

: .       ( w -- )
  \ Display an integer in free
  \  format, preceeded by a space.
  BASE @ 10 = IF 
    STR SPACE TYPE ELSE 
    U. THEN
  ;

: .R      ( n +n -- )
  \ Display an integer in a field
  \  of n columns, right justified.
  >R STR R> OVER - SPACES TYPE ;

: U.R     ( u +n -- )
  \ Display an unsigned integer in n column, right justified
  >R <# #S #> R> OVER - SPACES TYPE ;

: ?       ( a -- )
  \ Display contents in memory cell.
  @ . ;

:  2!      ( d a -- )      ( TOS STM8: -- Y,Z,N )
  \ Store double integer to address a.
  swap over ! 2+ ! ;
 
: 2@      ( a -- d )
  \ Fetch double integer from address a.
  DUP 2+ @ SWAP @ ;

: UM+     ( u u -- udsum )
  \ Add two unsigned single
  \  and return a double sum.
  [ OVERT
  ' + CALL, 			\ CALLR   PLUS
  $2503	,			\ JRC 	  JPONE
  $CC C, ' 0 ,			\ JP	  ZERO
  $CC C, ' 1 ,		\ JPONE	  JP	  ONE

: D+  ( d1 d2 -- d )
  >R ROT UM+ ( h d ) ROT + ( d ) R> + ;
  
: DNEGATE ( d -- -d )     ( TOS STM8: -- Y,Z,N )
  \ Two's complement of top double.
  $FFFF XOR SWAP NEGATE SWAP OVER 0= - ;

: M/MOD   ( d n -- r q )
  \ Signed floored divide of double by
  \  single. Return mod and quotient.
  DUP >R DUP 0< IF
    NEGATE >R DNEGATE R> THEN
  >R DUP 0< IF 
    R@ + THEN
  R> UM/MOD R> 0< IF
    SWAP NEGATE SWAP THEN
  ;

: /MOD    ( n n -- r q )
  \ Signed divide. Return mod and quotient.
  OVER 0< SWAP M/MOD ;
        
: MOD     ( n n -- r )    ( TOS STM8: -- Y,Z,N )
  \ Signed divide. Return mod only.
  /MOD DROP ;

: /       ( n n -- q )    ( TOS STM8: -- Y,Z,N )
  \ Signed divide. Return quotient only.
  /MOD NIP ;

: M*      ( n n -- d )
  \ Signed multiply. Return double product.
  2DUP XOR 0< >R 
  ABS SWAP ABS UM* R> 
  IF 
    DNEGATE THEN
  ;

: */MOD   ( n1 n2 n3 -- r q )
  \ Multiply n1 and n2, then divide
  \  by n3. Return mod and quotient.
  >R M* R> M/MOD ;

: */      ( n1 n2 n3 -- q )    ( TOS STM8: -- Y,Z,N )
  \ Multiply n1 by n2, then divide
  \  by n3. Return quotient only.
  */MOD NIP ;
  
: 2/      ( n -- n )      ( TOS STM8: -- Y,Z,N )
  \ Divide tos by 2.
  2 / ;
        
: 2*      ( n -- n )      ( TOS STM8: -- Y,Z,N )
  \ Multiply tos by 2.
  2 * ;
  
: ."      ( -- ; <string> )
  \ Compile an inline string literal 
  \  to be typed out at run time.
  COMPILE ."| $," ;

:  ABORT"  ( -- ; <string> )
  \ Conditional abort with an error message.
  COMPILE aborq $," ;

: >CHAR   ( c -- c )      ( TOS STM8: -- A,Z,N )
  \ Filter non-printing characters.
  DUP $80 < NOT \ over top of ASCII range
  \ or non-printing ASCII
  OVER $20 < OR IF 
    DROP $5F ( '_' ) THEN ;
  
: _TYPE   ( a u -- )
  \ Display u characters starting at address a
  \ Filter non-printing characters.
  0 DO
    DUP I + C@ >CHAR EMIT LOOP DROP ;

: dm+     ( a u -- a+u )
  \ Display u bytes starting at address a
  OVER 4 U.R SPACE \ display address
  DUP >R
  0 DO 
    DUP I + C@  3 U.R  LOOP 
  R> + ;
  
: DUMP    ( a u -- )
  \ Display u bytes from a, both bytes and chars
  BASE @ >R  HEX \ save base and change to base 16
  BEGIN
    OVER 16  DUP >R ( a u a n ) \ always 16 bytes/line
    CR dm+ ( a u a+n ) ROT ROT ( a+n a u ) 
    SPACE SPACE SWAP R> _TYPE 
    16 - DUP 0< UNTIL
  2DROP
  R> BASE ! \ restore base
  ;
        
: .S ( -- )
  \ Display contents of stack.
  1 DEPTH 1- DO
    I PICK . -1 +LOOP
  SPACE ." <sp"
  ;
  
: .ID ( na -- )
  \ Display name at address.
  ?DUP IF
    COUNT $1F AND _TYPE ELSE
    ." noname" THEN
  ;

: >NAME   ( ca -- na | F )
  \ Convert code address to a name address.
  \ { may be headerless, 
  \  so just stepping back unguaranteed }
  CONTEXT BEGIN
    @ DUP IF \ not at end of context chain
      ( ca naX )
      2DUP NAME> XOR IF \ not identical
        2- ELSE \ identical 
          NIP EXIT THEN
      ELSE \ at end of context chain
        2DROP 0 EXIT THEN
    AGAIN
  ;
  
: NUF?    ( -- t )
  \ Return false if no input,
  \  else pause and if CR return true.
  \ actually only pause .ifne   HALF_DUPLEX
  \  by one of two methods
  \ So, maybe just ignore the pause for now
  ?KEY IF 
    KEY $0D =
    ELSE 0 \ return FALSE if no input
    THEN
  ;
  
: SEE ( -- ; <string> )
  \ A simple decompiler.
  \ Updated for byte machines.
  ' CR 1- BEGIN
      2+ DUP @ DUP IF
        >NAME THEN
      ?DUP IF
        SPACE .ID 1+ ELSE
        1- DUP C@ U. THEN
        NUF? UNTIL
  DROP
  ;

: WORDS ( -- )
  \ Display names in vocabulary.
  CR CONTEXT @ BEGIN
    DUP SPACE .ID 2- 
    @ DUP 0= UNTIL
  DROP
  ;

ram