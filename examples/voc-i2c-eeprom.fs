\ stm8ef : I2C Example, rudiments of an EEPROM Library                 MM-171129

#require i2c

RAM

#require CONSTANT

i2c DEFINITIONS

NVM

VOC eeprom  i2c eeprom DEFINITIONS

  $50 CONSTANT sid

  : C@ ( a -- c )  1 i2c eeprom sid i2c read ;

  : C! ( c a -- )  2 i2c eeprom sid i2c write ;

FORTH DEFINITIONS
