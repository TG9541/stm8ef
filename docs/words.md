# STM8EF Words
```
;       COLD    ( -- )
;       The hilevel cold start sequence.
```

```
;       'BOOT   ( -- a )
;       The application startup vector and NVM USR setting array
```

```
;       hi      ( -- )
;       Display sign-on message.
```

```
;       ?RX     ( -- c T | F )  ( TOS STM8: -- Y,Z,N )
;       Return serial interface input char from and true, or false.
```

```
;       TX!     ( c -- )
;       Send character c to the serial interface.
```

```
;       ?KEY    ( -- c T | F )  ( TOS STM8: -- Y,Z,N )
;       Return input char and true, or false.
```

```
;       EMIT    ( c -- )
;       Send character c to output device.
```

```
;       PUSHLIT ( -- C )
;       Subroutine for DOLITC and CCOMMALIT
```

```
;       CCOMMALIT ( -- )
;       Compile inline literall byte into code dictionary.
```

```
;       DOLITC  ( -- C )
;       Push an inline literal character (8 bit).
```

```
;       doLit   ( -- w )
;       Push an inline literal.
```

```
;       (+loop) ( +n -- )
;       Add n to index R@ and test for lower than limit (R-CELL)@.
```

```
;       LEAVE   ( -- )
;       Leave a DO .. LOOP/+LOOP loop.
```

```
;       next    ( -- )
;       Code for single index loop.
```

```
;       QDQBRAN     ( n -- n )
;       QDUP QBRANCH phrase
```

```
;       ?branch ( f -- )
;       Branch if flag is zero.
```

```
;       branch  ( -- )
;       Branch to an inline address.
```

```
;       EXECUTE ( ca -- )
;       Execute word at ca.
```

```
;       EXIT    ( -- )
;       Terminate a colon definition.
```

```
;       2!      ( d a -- )      ( TOS STM8: -- Y,Z,N )
;       Store double integer to address a.
```

```
;       2@      ( a -- d )
;       Fetch double integer from address a.
```

```
;       2C!  ( n b -- )
;       Store word C-wise to 16 bit HW registers "MSB first"
```

```
;       2C@  ( a -- n )
;       Fetch word C-wise from 16 bit HW config. registers "MSB first"
```

```
;       B! ( t a u -- )
;       Set/reset bit #u (0..7) in the byte at address a to bool t
;       Note: creates/executes BSER/BRES + RET code on Data Stack
```

```
;       @       ( a -- w )      ( TOS STM8: -- Y,Z,N )
;       Push memory location to stack.
```

```
;       !       ( w a -- )      ( TOS STM8: -- Y,Z,N )
;       Pop data stack to memory.
```

```
;       C@      ( b -- c )      ( TOS STM8: -- A,Z,N )
;       Push byte in memory to stack.
;       STM8: Z,N
```

```
;       C!      ( c b -- )
;       Pop     data stack to byte memory.
```

```
;       R>      ( -- w )     ( TOS STM8: -- Y,Z,N )
;       Pop return stack to data stack.
```

```
;       doVARPTR core ( -- a )    ( TOS STM8: -- Y,Z,N )
```

```
;       doVAR   ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Code for VARIABLE and CREATE.
```

```
;       YSTOR core ( -- n )     ( TOS STM8: -- Y,Z,N )
;       push Y to stack
```

```
;       R@      ( -- w )        ( TOS STM8: -- Y,Z,N )
;       Copy top of return stack to stack (or the FOR - NEXT index value).
```

```
;       >R      ( w -- )      ( TOS STM8: -- Y,Z,N )
;       Push data stack to return stack.
```

```
;       NIP     ( n1 n2 -- n2 )
;       Drop 2nd item on the stack
```

```
;       DROP    ( w -- )        ( TOS STM8: -- Y,Z,N )
;       Discard top stack item.
```

```
;       2DROP   ( w w -- )       ( TOS STM8: -- Y,Z,N )
;       Discard two items on stack.
```

```
;       DUP     ( w -- w w )    ( TOS STM8: -- Y,Z,N )
;       Duplicate top stack item.
```

```
;       SWAP ( w1 w2 -- w2 w1 ) ( TOS STM8: -- Y,Z,N )
;       Exchange top two stack items.
```

```
;       OVER    ( w1 w2 -- w1 w2 w1 ) ( TOS STM8: -- Y,Z,N )
;       Copy second stack item to top.
```

```
;       I       ( -- n )     ( TOS STM8: -- Y,Z,N )
;       Get inner FOR-NEXT or DO-LOOP index value
```

```
;       UM+     ( u u -- udsum )
;       Add two unsigned single
;       and return a double sum.
```

```
;       +       ( w w -- sum ) ( TOS STM8: -- Y,Z,N )
;       Add top two items.
```

```
;       XOR     ( w w -- w )    ( TOS STM8: -- Y,Z,N )
;       Bitwise exclusive OR.
```

```
;       AND     ( w w -- w )    ( TOS STM8: -- Y,Z,N )
;       Bitwise AND.
```

```
;       OR      ( w w -- w )    ( TOS STM8: -- immediate Y,Z,N )
;       Bitwise inclusive OR.
```

```
;       0<      ( n -- t ) ( TOS STM8: -- A,Z )
;       Return true if n is negative.
```

```
;       -   ( n1 n2 -- n1-n2 )  ( TOS STM8: -- Y,Z,N )
;       Subtraction.
```

```
;       CONTEXT ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Start vocabulary search.
```

```
;       CP      ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Point to top of dictionary.
```

```
;       BASE    ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Radix base for numeric I/O.
```

```
;       >IN     ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Hold parsing pointer.
```

```
;       #TIB    ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Count in terminal input buffer.
```

```
;       'eval   ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Execution vector of EVAL.
```

```
;       HLD     ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Hold a pointer of output string.
```

```
;       'EMIT   ( -- a )     ( TOS STM8: -- A,Z,N )
;
```

```
;       '?KEY   ( -- a )     ( TOS STM8: -- A,Z,N )
;
```

```
;       LAST    ( -- a )        ( TOS STM8: -- Y,Z,N )
;       Point to last name in dictionary.
```

```
;       ASTOR core ( -- n )     ( TOS STM8: -- Y,Z,N )
;       push A to stack
```

```
;       ATOKEY core ( -- c T | f )    ( TOS STM8: -- Y,Z,N )
;       Return input char and true, or false.
```

```
;       TIB     ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Return address of terminal input buffer.
```

```
;       OUT     ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Return address of OUTPUTS register
```

```
;       BL      ( -- 32 )     ( TOS STM8: -- Y,Z,N )
;       Return 32, blank character.
```

```
;       0       ( -- 0)     ( TOS STM8: -- Y,Z,N )
;       Return 0.
```

```
;       1       ( -- 1)     ( TOS STM8: -- Y,Z,N )
;       Return 1.
```

```
;       -1      ( -- -1)     ( TOS STM8: -- Y,Z,N )
;       Return -1
```

```
;       TIM     ( -- T)     ( TOS STM8: -- Y,Z,N )
;       Return TICKCNT as timer
```

```
;       BG      ( -- a)     ( TOS STM8: -- Y,Z,N )
;       Return address of BGADDR vector
```

```
;       'PROMPT ( -- a)     ( TOS STM8: -- Y,Z,N )
;       Return address of PROMPT vector
```

```
;       HAND    ( -- )
;       set PROMPT vector to interactive mode
```

```
;       FILE    ( -- )
;       set PROMPT vector to file transfer mode
```

```
;       ?DUP    ( w -- w w | 0 )   ( TOS STM8: -- Y,Z,N )
;       Dup tos if its not zero.
```

```
;       ROT     ( w1 w2 w3 -- w2 w3 w1 ) ( TOS STM8: -- Y,Z,N )
;       Rot 3rd item to top.
```

```
;       2DUP    ( w1 w2 -- w1 w2 w1 w2 )
;       Duplicate top two items.
```

```
;       DNEGATE ( d -- -d )     ( TOS STM8: -- Y,Z,N )
;       Two's complement of top double.
```

```
;       =       ( w w -- t )    ( TOS STM8: -- Y,Z,N )
;       Return true if top two are equal.
```

```
;       U<      ( u u -- t )    ( TOS STM8: -- Y,Z,N )
;       Unsigned compare of top two items.
```

```
;       <       ( n1 n2 -- t )
;       Signed compare of top two items.
```

```
;       YTEMPCMP       ( n n -- n )      ( TOS STM8: -- Y,Z,N )
;       Load (TOS) to YTEMP and (TOS-1) to Y, DROP, CMP to STM8 flags
```

```
;       MAX     ( n n -- n )    ( TOS STM8: -- Y,Z,N )
;       Return greater of two top items.
```

```
;       MIN     ( n n -- n )    ( TOS STM8: -- Y,Z,N )
;       Return smaller of top two items.
```

```
;       WITHIN ( u ul uh -- t ) ( TOS STM8: -- Y,Z,N )
;       Return true if u is within
;       range of ul and uh. ( ul <= u < uh )
```

```
;       UM/MOD  ( udl udh un -- ur uq )
;       Unsigned divide of a double by a
;       single. Return mod and quotient.
```

```
;       M/MOD   ( d n -- r q )
;       Signed floored divide of double by
;       single. Return mod and quotient.
```

```
;       /MOD    ( n n -- r q )
;       Signed divide. Return mod and quotient.
```

```
;       MOD     ( n n -- r )    ( TOS STM8: -- Y,Z,N )
;       Signed divide. Return mod only.
```

```
;       /       ( n n -- q )    ( TOS STM8: -- Y,Z,N )
;       Signed divide. Return quotient only.
```

```
;       UM*     ( u u -- ud )
;       Unsigned multiply. Return double product.
```

```
;       *       ( n n -- n )    ( TOS STM8: -- Y,Z,N )
;       Signed multiply. Return single product.
```

```
;       M*      ( n n -- d )
;       Signed multiply. Return double product.
```

```
;       */MOD   ( n1 n2 n3 -- r q )
;       Multiply n1 and n2, then divide
;       by n3. Return mod and quotient.
```

```
;       */      ( n1 n2 n3 -- q )    ( TOS STM8: -- Y,Z,N )
;       Multiply n1 by n2, then divide
;       by n3. Return quotient only.
```

```
;       EXG      ( n -- n )      ( TOS STM8: -- Y,Z,N )
;       Exchange high with low byte of n.
```

```
;       2/      ( n -- n )      ( TOS STM8: -- Y,Z,N )
;       Divide tos by 2.
```

```
;       2*      ( n -- n )      ( TOS STM8: -- Y,Z,N )
;       Multiply tos by 2.
```

```
;       2-      ( a -- a )      ( TOS STM8: -- Y,Z,N )
;       Subtract 2 from tos.
```

```
;       2+      ( a -- a )      ( TOS STM8: -- Y,Z,N )
;       Add 2 to tos.
```

```
;       1-      ( n -- n )      ( TOS STM8: -- Y,Z,N )
;       Subtract 1 from tos.
```

```
;       1+      ( n -- n )      ( TOS STM8: -- Y,Z,N )
;       Add 1 to tos.
```

```
;       DOXCODE   ( n -- n )   ( TOS STM8: -- Y,Z,N )
;       DOXCODE precedes assembly code for a primitive word
;       In the assembly code: X=(TOS), YTEMP=TOS. (TOS)=X after RET
;       Caution: no other Forth word may be called from assembly!
```

```
;       NOT     ( w -- w )     ( TOS STM8: -- Y,Z,N )
;       One's complement of TOS.
```

```
;       NEGATE  ( n -- -n )     ( TOS STM8: -- Y,Z,N )
;       Two's complement of TOS.
```

```
;       ABS     ( n -- n )      ( TOS STM8: -- Y,Z,N )
;       Return  absolute value of n.
```

```
;       0=      ( n -- t )      ( TOS STM8: -- Y,Z,N ))
;       Return true if n is equal to 0
```

```
;       PICK    ( ... +n -- ... w )      ( TOS STM8: -- Y,Z,N )
;       Copy    nth stack item to tos.
```

```
;       >CHAR   ( c -- c )      ( TOS STM8: -- A,Z,N )
;       Filter non-printing characters.
```

```
;       DEPTH   ( -- n )      ( TOS STM8: -- Y,Z,N )
;       Return  depth of data stack.
```

```
;       +!      ( n a -- )      ( TOS STM8: -- Y,Z,N )
;       Add n to contents at address a.
```

```
;       COUNT   ( b -- b +n )      ( TOS STM8: -- A,Z,N )
;       Return count byte of a string
;       and add 1 to byte address.
```

```
;       HERE    ( -- a )      ( TOS STM8: -- Y,Z,N )
;       Return  top of  code dictionary.
```

```
;       PAD     ( -- a )  ( TOS STM8: invalid )
;       Return address of text buffer
;       above code dictionary.
```

```
;       @EXECUTE        ( a -- )  ( TOS STM8: undefined )
;       Execute vector stored in address a.
```

```
;       CMOVE   ( b1 b2 u -- )
;       Copy u bytes from b1 to b2.
```

```
;       FILL    ( b u c -- )
;       Fill u bytes of character c
;       to area beginning at b.
```

```
;       ERASE   ( b u -- )
;       Erase u bytes beginning at b.
```

```
;       PACK$   ( b u a -- a )
;       Build a counted string with
;       u characters from b. Null fill.
```

```
;       DIGIT   ( u -- c )      ( TOS STM8: -- Y,Z,N )
;       Convert digit u to a character.
```

```
;       EXTRACT ( n base -- n c )   ( TOS STM8: -- Y,Z,N )
;       Extract least significant digit from n.
```

```
;       #>      ( w -- b u )
;       Prepare output string.
```

```
;       #       ( u -- u )    ( TOS STM8: -- Y,Z,N )
;       Extract one digit from u and
;       append digit to output string.
```

```
;       #S      ( u -- 0 )
;       Convert u until all digits
;       are added to output string.
```

```
;       HOLD    ( c -- )    ( TOS STM8: -- Y,Z,N )
;       Insert a character into output string.
```

```
;       SIGN    ( n -- )
;       Add a minus sign to
;       numeric output string.
```

```
;       <#      ( -- )   ( TOS STM8: -- Y,Z,N )
;       Initiate numeric output process.
```

```
;       str     ( w -- b u )
;       Convert a signed integer
;       to a numeric string.
```

```
;       HEX     ( -- )
;       Use radix 16 as base for
;       numeric conversions.
```

```
;       DECIMAL ( -- )
;       Use radix 10 as base
;       for numeric conversions.
```

```
;       BASE@     ( -- u )
;       Get BASE value
```

```
;       NUMBER? ( a -- n T | a F )
;       Convert a number string to
;       integer. Push a flag on tos.
```

```
;       DIGIT?  ( c base -- u t )
;       Convert a character to its numeric
;       value. A flag indicates success.
```

```
;       KEY     ( -- c )
;       Wait for and return an
;       input character.
```

```
;       NUF?    ( -- t )
;       Return false if no input,
;       else pause and if CR return true.
```

```
;       SPACE   ( -- )
;       Send    blank character to
;       output device.
```

```
;       SPACES  ( +n -- )
;       Send n spaces to output device.
```

```
;       CR      ( -- )
;       Output a carriage return
;       and a line feed.
```

```
;       do$     ( -- a )
;       Return  address of a compiled
;       string.
```

```
;       $"|     ( -- a )
;       Run time routine compiled by $".
;       Return address of a compiled string.
```

```
;       ."|     ( -- )
;       Run time routine of ." .
;       Output a compiled string.
```

```
;       .R      ( n +n -- )
;       Display an integer in a field
;       of n columns, right justified.
```

```
;       U.R     ( u +n -- )
;       Display an unsigned integer
;       in n column, right justified.
```

```
;       TYPE    ( b u -- )
;       Output u characters from b.
```

```
;       U.      ( u -- )
;       Display an unsigned integer
;       in free format.
```

```
;       .       ( w -- )
;       Display an integer in free
;       format, preceeded by a space.
```

```
;       ?       ( a -- )
;       Display contents in memory cell.
```

```
;       YFLAGS  ( n -- )       ( TOS STM8: -- Y,Z,N )
;       Consume TOS to CPU Y and Flags
```

```
;       AFLAGS  ( c -- )       ( TOS STM8: -- A,Z,N )
;       Consume TOS to CPU A and Flags
```

```
;       parse   ( b u c -- b u delta ; <string> )
;       Scan string delimited by c.
;       Return found string and its offset.
```

```
;       PARSE   ( c -- b u ; <string> )
;       Scan input stream and return
;       counted string delimited by c.
```

```
;       .(      ( -- )
;       Output following string up to next ) .
```

```
;       (       ( -- )
;       Ignore following string up to next ).
;       A comment.
```

```
;       \       ( -- )
;       Ignore following text till
;       end of line.
```

```
;       TOKEN   ( -- a ; <string> )
;       Parse a word from input stream
;       and copy it to code dictionary or to RAM.
```

```
;       WORD    ( c -- a ; <string> )
;       Parse a word from input stream
;       and copy it to code dictionary or to RAM.
```

```
;       TOKEN_$,n core ( <word> -- <dict header> )
;       copy token to the code dictionary
;       and build a new dictionary name
;       note: for defining words (e.g. :, CREATE)
```

```
;       NAME>   ( na -- ca )
;       Return a code address given
;       a name address.
```

```
;       SAME?   ( a a u -- a a f \ -0+ )
;       Compare u cells in two
;       strings. Return 0 if identical.
```

```
;       CUPPER  ( c -- c )
;       convert char to upper case
```

```
;       NAME?   ( a -- ca na | a F )
;       Search vocabularies for a string.
```

```
;       find    ( a va -- ca na | a F )
;       Search vocabulary for string.
;       Return ca and na if succeeded.
```

```
;       ^H      ( bot eot cur -- bot eot cur )
;       Backup cursor by one character.
```

```
;       TAP     ( bot eot cur c -- bot eot cur )
;       Accept and echo key stroke
;       and bump cursor.
```

```
;       kTAP    ( bot eot cur c -- bot eot cur )
;       Process a key stroke,
;       CR or backspace.
```

```
;       ACCEPT  ( b u -- b u )
;       Accept one line of characters to input
;       buffer. Return with actual count.
```

```
;       QUERY   ( -- )
;       Accept one line from input stream to
;       terminal input buffer.
```

```
;       ABORT   ( -- )
;       Reset data stack and
;       jump to QUIT.
```

```
;       abort"  ( f -- )
;       Run time routine of ABORT".
;       Abort with a message.
```

```
;       PRESET  ( -- )
;       Reset data stack pointer and
;       terminal input buffer.
```

```
;       $INTERPRET      ( a -- )
;       Interpret a word. If failed,
;       try to convert it to an integer.
```

```
;       [       ( -- )
;       Start   text interpreter.
```

```
;       .OK     ( -- )
;       Display 'ok' while interpreting.
```

```
;       ?STACK  ( -- )
;       Abort if stack underflows.
```

```
;       EVAL    ( -- )
;       Interpret input stream.
```

```
;       QUIT    ( -- )
;       Reset return stack pointer
;       and start text interpreter.
```

```
;       '       ( -- ca )
;       Search vocabularies for
;       next word in input stream.
```

```
;       ,       ( w -- )
;       Compile an integer into
;       code dictionary.
```

```
;       C,      ( c -- )
;       Compile a byte into code dictionary.
;       HEADER  CCOMMA "C,"
```

```
;       CALL,   ( ca -- )
;       Compile a subroutine call.
```

```
;       LITERAL ( w -- )
;       Compile tos to dictionary
;       as an integer literal.
```

```
;       [COMPILE]       ( -- ; <string> )
;       Compile next immediate
;       word into code dictionary.
```

```
;       COMPILE ( -- )
;       Compile next jsr in
;       colon list to code dictionary.
```

```
;       $,"     ( -- )
;       Compile a literal string
;       up to next " .
```

```
;       FOR     ( -- a )
;       Start a FOR-NEXT loop
;       structure in a colon definition.
```

```
;       NEXT    ( a -- )
;       Terminate a FOR-NEXT loop.
```

```
;       DO      ( -- a )
;       Start a DO LOOP loop
;       structure in a colon definition.
```

```
;       LOOP    ( a -- )
;       Terminate a DO-LOOP loop.
```

```
;       +LOOP   ( a +n -- )
;       Terminate a DO - +LOOP loop.
```

```
;       BEGIN   ( -- a )
;       Start an infinite or
;       indefinite loop structure.
```

```
;       UNTIL   ( a -- )
;       Terminate a BEGIN-UNTIL
;       indefinite loop structure.
```

```
;       AGAIN   ( a -- )
;       Terminate a BEGIN-AGAIN
;       infinite loop structure.
```

```
;       IF      ( -- A )
;       Begin a conditional branch.
```

```
;       THEN    ( A -- )
;       Terminate a conditional branch structure.
```

```
;       ELSE    ( A -- A )
;       Start the false clause in an IF-ELSE-THEN structure.
```

```
;       AHEAD   ( -- A )
;       Compile a forward branch instruction.
```

```
;       WHILE   ( a -- A a )
;       Conditional branch out of a BEGIN-WHILE-REPEAT loop.
```

```
;       REPEAT  ( A a -- )
;       Terminate a BEGIN-WHILE-REPEAT indefinite loop.
```

```
;       AFT     ( a -- a A )
;       Jump to THEN in a FOR-AFT-THEN-NEXT loop the first time through.
```

```
;       ABORT"  ( -- ; <string> )
;       Conditional abort with an error message.
```

```
;       $"      ( -- ; <string> )
;       Compile an inline string literal.
```

```
;       ."      ( -- ; <string> )
;       Compile an inline string literal to be typed out at run time.
```

```
;       ?UNIQUE ( a -- a )
;       Display a warning message
;       if word already exists.
```

```
;       $,n     ( na -- )
;       Build a new dictionary name
;       using string at na.
```

```
;       $COMPILE        ( a -- )
;       Compile next word to
;       dictionary as a token or literal.
```

```
;       OVERT   ( -- )
;       Link a new word into vocabulary.
```

```
;       ;       ( -- )
;       Terminate a colon definition.
```

```
;       :       ( -- ; <string> )
;       Start a new colon definition
;       using next word as its name.
```

```
;       ]       ( -- )
;       Start compiling words in
;       input stream.
```

```
;       DOES>   ( -- )
;       Define action of defining words
```

```
;       dodoes  ( -- )
;       link action to words created by defining words
```

```
;       CREATE  ( -- ; <string> )
;       Compile a new array
;       without allocating space.
```

```
;       CONSTANT ( "name" n -- )
;       Create a named constant with state dependant action
```

```
;       docon ( -- )
;       state dependent action code of constant
```

```
;       VARIABLE        ( -- ; <string> )
;       Compile a new variable
;       initialized to 0.
```

```
;       ALLOT   ( n -- )
;       Allocate n bytes to code DICTIONARY.
```

```
;       IMMEDIATE       ( -- )
;       Make last compiled word
;       an immediate word.
```

```
;       _TYPE   ( b u -- )
;       Display a string. Filter
;       non-printing characters.
```

```
;       dm+     ( a u -- a )
;       Dump u bytes from ,
;       leaving a+u on  stack.
```

```
;       DUMP    ( a u -- )
;       Dump u bytes from a,
;       in a formatted manner.
```

```
;       .S      ( ... -- ... )
;       Display contents of stack.
```

```
;       .ID     ( na -- )
;       Display name at address.
```

```
;       >NAME   ( ca -- na | F )
;       Convert code address
;       to a name address.
```

```
;       WORDS   ( -- )
;       Display names in vocabulary.
```

```
;       E7S  ( c -- )
;       Convert char to 7-seg LED pattern, and insert it in display buffer
```

```
;       P7S  ( c -- )
;       Right aligned 7S-LED pattern output, rotates LED group buffer
```

```
;       ?KEYB   ( -- c T | F )  ( TOS STM8: -- Y,Z,N )
;       Return keyboard char and true, or false if no key pressed.
```

```
;       ADC!  ( c -- )
;       Init ADC, select channel for conversion
```

```
;       ADC@  ( -- w )
;       start ADC conversion, read result
```

```
;       SP!     ( a -- )
;       Set data stack pointer.
```

```
;       SP@     ( -- a )        ( TOS STM8: -- Y,Z,N )
;       Push current stack pointer.
```

```
;       RP@     ( -- a )     ( TOS STM8: -- Y,Z,N )
;       Push current RP to data stack.
```

```
;       RP!     ( a -- )
;       Set return stack pointer.
```

```
;       ULOCK  ( -- )
;       Unlock EEPROM (STM8S)
```

```
;       LOCK  ( -- )
;       Lock EEPROM (STM8S)
```

```
;       ULOCKF  ( -- )
;       Unlock Flash (STM8S)
```

```
;       LOCKF  ( -- )
;       Lock Flash (STM8S)
```

```
;       NVM  ( -- )
;       Compile to NVM (enter mode NVM)
```

```
;       RAM  ( -- )
;       Compile to RAM (enter mode RAM)
```

```
;       RESET  ( -- )
;       Reset Flash dictionary and 'BOOT to defaults and restart
```

```
;       SAVEC ( -- )
;       Minimal context switch for low level interrupt code
;       This should be the first word called in the interrupt handler
```

```
;       IRET ( -- )
;       Restore context and return from low level interrupt code
;       This should be the last word called in the interrupt handler
```

