file
nvm \ make comment to just create in ram


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