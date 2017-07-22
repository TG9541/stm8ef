\ STM8EF temporary RAM dictionary
\ (c) TG9541, refer to licence at github.com/TG9541/stm8ef/

\ Mark current CP, LAST and CONTEXT in RAM mode
: RAMmark ( -- a a a )
  RAM last 2- @ last @  last 10 + @
;

\ Restore marked CP, LAST and CONTEXT in RAM mode
: RAMdrop ( a a a -- )
  RAM last 10 + ! last ! last 2- !
;

