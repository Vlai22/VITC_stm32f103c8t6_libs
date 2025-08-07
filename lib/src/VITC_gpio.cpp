#include "VITC_gpio.h"
#include <stdint.h>
#include "stm32f10x.h"
//функция возращает экземпляр структуры регистров gpio конкретного порта и влючает его тактирование
GPIO_TypeDef* gpio_get_struct_reg(char Port){
	switch(Port){
		case 'A':
					SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);
				return GPIOA;
			break;
		case 'B': 
					SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN);
				return GPIOB;
			break;
		case 'C': 
					SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN);
				return GPIOC;
			break;
		case 'D': 
					SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPDEN);
				return GPIOD;
			break;
		case 'E':
					SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPEEN);
				return GPIOE;
			break;
		default:
			return nullptr;
	}
}
//функция которая даёт маску битов конфигурации конкретного gpio 
uint32_t gpio_get_cnf_mask(uint8_t pinN) {
    return (pinN % 8) * 4;
}
//функция запуска какого либо порта
void GPIO::pinMode(uint8_t pinN, char Port, uint8_t mode, uint8_t speed){
	//проверяем пользователь ли не вышел за груницу stm32f10x серии количества gpio на одном порту
	if(pinN > 15) return;
	//получаем экземпляр структуры регистров gpio
	GPIO_TypeDef* gpio = gpio_get_struct_reg(Port);
	//проверяем есть ли такая структура вообще
	if(gpio == nullptr) return;
	//получаем маску конфигурационных битов конкретного пина
	uint32_t gpio_cnf = gpio_get_cnf_mask(pinN);
	//получаем ссылку на память где храниться настройка конкретного пина
	volatile uint32_t* gpio_HL = (pinN < 8) ? &gpio->CRL : &gpio->CRH;
	//очищаем биты памяти конфигурации
	*gpio_HL &= ~(0xF << gpio_cnf);
	//настраиваем биты конфигурации в необходимый режим работы
	switch(mode){
		case 1: //input pull up
				*gpio_HL |= (0x8) << gpio_cnf;
				gpio->ODR |= (1 << pinN); 
			break;
		case 2: //input pull down
				*gpio_HL |= (0x8) << gpio_cnf;
				gpio->ODR &= ~(1 << pinN); 
			break;
		case 3://input float
				*gpio_HL |= (0x4) << gpio_cnf;
			break;
		case 4://output general push pull
				*gpio_HL |= ((speed & 0x3) << gpio_cnf);
			break;
		case 5://output general open drain
				*gpio_HL |= ((0x4 | (speed & 0x3)) << gpio_cnf);
			break;
		case 6://output alternative function push pull
				SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);//обязательно включем тактирование альтернативной функции иначе не будет работать
				*gpio_HL |= ((0x8 | (speed & 0x3)) << gpio_cnf);
			break;
		case 7://output alternative function open drain
				SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);//обязательно включем тактирование альтернативной функции иначе не будет работать
				*gpio_HL |= ((0xC | (speed & 0x3)) << gpio_cnf);
			break;
	}
}
//функция записи в пин значений, работает в любом случаем несмотря на выбранный режим работы!!!!
void GPIO::WritePin(uint8_t pinN, char Port, bool value){
		//проверяем пользователь ли не вышел за груницу stm32f10x серии количества gpio на одном порту
	if(pinN > 15) return;
	//получаем экземпляр структуры регистров gpio
	GPIO_TypeDef* gpio = gpio_get_struct_reg(Port);
	//проверяем есть ли такая структура вообще
	if(gpio == nullptr) return;
	//устанавливаем выставленное значение в регистр ODR отвечающий за вывод данных на уровень установленный пользователем и пин который выбрал пользователь
	if(value){
		gpio->ODR |= (1 << pinN);
	}else{
		gpio->ODR &= ~(1 << pinN);
	}
}
bool GPIO::ReadPin(uint8_t pinN, char Port){
	//проверяем пользователь ли не вышел за груницу stm32f10x серии количества gpio на одном порту
	if(pinN > 15) return false;
	//получаем экземпляр структуры регистров gpio
	GPIO_TypeDef* gpio = gpio_get_struct_reg(Port);
	//проверяем есть ли такая структура вообще
	if(gpio == nullptr) return false;
	//читаем регистр IDR который отвечает за входные данные и проверяем его на соотвествие 1 выбранный номер бита
	if(gpio->IDR & (1 << pinN)){
		return true;
	}else{
		return false;
	}
}