# VITC_stm32f103c8t6_libs
These libraries are provided for smt32f103c8t6 and do not claim to compete with HAL, which gives the developer the opportunity to add and continue its work.

## GPIO
The first part of the library works with GPIO, at the moment only the possibility of setting the operating mode via pinMode is implemented, as well as reading and writing the level to different pins via the ReadPin and WritePin functions, respectively.
- pinMode(uint8_t pinN, char Port, uint8_t mode, uint8_t speed = 0)
- WritePin(uint8_t pinN, char Port, bool value)
- bool ReadPin(uint8_t pinN, char Port)

The value for pinN is selected from 0 to 15 depending on the selected microcontroller pin. The value for Port is selected by the port symbol you are using, they are located in the range from A to E for stm32f103.
