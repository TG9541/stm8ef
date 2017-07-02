\ Some double maths utility words (C) RigTig 2017
\ github.com/TG9541/stm8ef/blob/master/LICENSE.md

: ud+ ( ud ud -- ud )
  ( l h l h )
  >R ROT UM+ ( h d )
  ROT + ( d )   \ eForth + is u+
  R> +
;

: d- ( d d -- d )
  \ ToDo: ensure works on full range
  DNEGATE ud+
;

: d> ( d d -- f )
  d- 2dup or 0= ( d f ) rot rot
  0< swap drop or not
;

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
