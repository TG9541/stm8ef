\ Linear interpolation between closest x-sorted x/y pairs
\ Saturate to y(xmin), y(xmax).
\ (C) TG9541 2017
\ github.com/TG9541/stm8ef/blob/master/LICENSE.md
\ Example:
\   create iTab 3 , -100 , 200 , 0 , 100, 100, -1000 , ok
\   -150 iTab inter . 200 ok

: @dif ( a -- n )   \ delta of x1-x0 or y1-y0
  dup 2+ 2+ @ swap @ - ;

: inter ( n a -- n1 )
  dup @ 1- >r 2+ dup begin
    3 pick over @ < not while nip dup 2+ 2+ next
      drop dup
    else r> drop then
  over = if
    2+ @ nip
  else
    dup rot over @ - over 2+ @dif rot @dif */ swap 2+ @ +
  then ;
