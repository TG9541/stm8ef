\ STM8EF temporary RAM dictionary
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md

\ Mark current CP, LAST and CONTEXT in RAM mode
: RAMmark ( -- a a a )
  RAM last 2- @ last @  last 10 + @
;

\ Restore marked CP, LAST and CONTEXT in RAM mode
: RAMdrop ( a a a -- )
  RAM last 10 + ! last ! last 2- !
;

