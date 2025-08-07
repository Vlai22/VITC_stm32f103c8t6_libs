#ifndef VITC_GPIO_H
#define VITC_GPIO_H

#include <stdint.h>

#define INPUT_PULL_UP 1
#define INPUT_PULL_DOWN 2
#define INPUT_FLOATING 3
#define OUTPUT_PUSH_PULL 4
#define OUTPUT_OPEN_DRAIN 5
#define OUTPUT_PUSH_PULL_AF 6
#define OUTPUT_OPEN_DRAIN_AF 7
#define SPEED_10MHZ 1
#define SPEED_2MHZ 2
#define SPEED_50MHZ 3
//данная библиотека предоставляет настройку выходных каналов и управление цифровыми преобразованиями 
//данная библиотека не использует и не лезит в ШИМ преобразования и преобразования АЦП/ЦАП
//поскольку smt32 предоставляет большую гибкость данных преоброзователей и не знающий человек запутается или не получит гибкости
class GPIO{

	public:
		//функция выставления режима работа рызных портов
		void pinMode(uint8_t pinN, char Port, uint8_t mode, uint8_t speed = 0);
		//запись в пин значение ноль или один
		void WritePin(uint8_t pinN, char Port, bool value);
		//чтение порлученых данных из порта
		bool ReadPin(uint8_t pinN, char Port);
};
#endif
