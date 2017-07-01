NVM
: @dif ( a -- n )  \ indirect delta of elements of value pairs
  dup 2+ 2+ @ swap @ - ;
: @inter ( n a -- n1 )  \ find value pairs and interpolate
  dup @ 1- >R 2+ dup begin 
    3 pick over @ < not while nip dup 2+ 2+ next 
      drop dup 
    else R> drop then
  over = if 
    2+ @ nip 
  else 
    dup rot over @ - over 2+ @dif rot @dif */ swap 2+ @ + then ;
RAM

