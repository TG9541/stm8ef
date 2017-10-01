#include utils/tester.fs

T{e WORDS e-> 978 -835 }T
T{e .( abc123) e-> 6 444 }T
: test-."" ." abc123" ;
T{e test-."" e-> 6 444 }T
: test-$"" $" abc123" ;
T{e test-$"" count type e-> 6 444 }T

T{ 2 3 + -> 5 }T
T{ 255 -3 - -> 258 }T
T{ 255 -3 * -> -765 }T
T{ -511 2 / -> -256 }T
T{ 511 -5 /MOD -> -4 -103 }T
