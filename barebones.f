file
nvm \ make comment to just create in ram

\ the following words replicate the assembler versions in forth.asm
\  for output and stack effects, but are not necessarily as 
\  efficient as might be coded without that constraint

\ to see >CHAR, WORDS_LINKMISC = 1
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
  \ { may be headerless, so just stepping back unguaranteed }
  CONTEXT BEGIN
    @ DUP IF \ not at end of context chain
      ( ca naX ) .s
      2DUP NAME> XOR IF \ not identical
        2- ELSE \ identical 
          NIP EXIT THEN
      ELSE \ at end of context chain
        2DROP 0 EXIT THEN
    AGAIN
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

\ to see CONTEXT, WORDS_LINKINTER  = 1
: WORDS ( -- )
  \ Display names in vocabulary.
  CR CONTEXT @ BEGIN
    DUP SPACE .ID 2- 
    @ DUP 0= UNTIL
  DROP
  ;

ram