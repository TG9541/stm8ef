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
  d- 2DUP OR 0= ( d f ) ROT ROT
  0< SWAP DROP OR NOT
;
