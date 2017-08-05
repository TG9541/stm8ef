\ Some integer square root (C) RigTig 2017
\ refer to github.com/TG9541/stm8ef/blob/master/LICENSE.md

\ require: math/double.fs

: isqrt ( d -- n )
  $8000 ( d c ) $8000 ( d c g )
  BEGIN
    DUP DUP UM* ( d c g g^2)
    6 PICK 6 PICK ( d c g g^2 d )
    d> IF ( d c g )
      OVER XOR
    THEN ( d c g )
    SWAP 2/ $7FFF AND ( d g c )
    DUP 0= IF
      DROP ROT ROT 2DROP -1 ( g true )
    ELSE
      SWAP OVER ( d c g c ) OR 0
    THEN
  UNTIL
;
