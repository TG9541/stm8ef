; STM8EF Global Configuration File
; HC-12 radio modem module with STM8S003P3 and Si4463

        STM8S003F3       = 1

        HAS_CPNVM        = 1    ; Can compile to Flash, always interpret to RAM
        BAREBONES        = 0    ; Remove or unlink some more: hi HERE .R U.R SPACES @EXECUTE AHEAD CALL, EXIT COMPILE [COMPILE]
        WORDS_EXTRACORE  = 1    ; Extra core words: =0 I
        TERM_LINUX       = 0

