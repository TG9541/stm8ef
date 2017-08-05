\ Linear interpolation between closest x-sorted x/y pairs
\ Saturates to y(xmin), y(xmax).
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md

\ Example with 3 x/y pairs:
\   create iTab 3 , -100 , 200 , 0 , 100, 100, -1000 , ok
\   -150 iTab @inter . 200 ok

\ difference of two values two cells apart, helper for @inter
: @dif ( a -- n )   \ delta of x1-x0 or y1-y0
  dup 2+ 2+ @ swap @ -
;

\ find (X0,Y0)/(X1,Y1) in table, interpolate w/ saturation
: @inter ( n a -- n1 )
  dup @ 1- >r 2+ dup begin
    3 pick over @ < not while nip dup 2+ 2+ next
      drop dup
    else r> drop then
  over = if
    2+ @ nip
  else
    dup rot over @ - over 2+ @dif rot @dif */ swap 2+ @ +
  then
;
