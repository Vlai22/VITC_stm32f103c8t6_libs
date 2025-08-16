#include "VITC_spi.h"
#include "VITC_gpio.h"
#include <stdint.h>
#include "stm32f10x.h"


SPI_TypeDef* Selsct_spi(uint8_t SPI){
		switch(SPI){
			case 1: 
				SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);
				return SPI1;
				break;
			case 2: 
				SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);
				return SPI2;
				break;
			case 3: 
				//SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI3EN);
				return SPI3;
				break;
			default: return nullptr;
		}
}

uint8_t SPI::SPI_init(uint8_t SPI, uint8_t duplex, bool format, bool master, uint8_t CPxx, bool LSBF, uint8_t fre, bool NSS, bool crc){
	SPI_TypeDef* spi = Selsct_spi(SPI);
	spi->CR1 = 0;
	if(duplex == 2){
			SET_BIT(spi->CR1, SPI_CR1_RXONLY);
	}else if(duplex == 3){
			SET_BIT(spi->CR1, SPI_CR1_BIDIMODE);
	}else if(duplex == 4){
			SET_BIT(spi->CR1, SPI_CR1_BIDIMODE);
			SET_BIT(spi->CR1, SPI_CR1_BIDIOE);		
	}
	if(format){
		SET_BIT(spi->CR1, SPI_CR1_DFF);
	}
	if(CPxx == 2){
		SET_BIT(spi->CR1, SPI_CR1_CPOL);
	}else if(CPxx == 3){
		SET_BIT(spi->CR1, SPI_CR1_CPHA);
	}else if(CPxx == 4){
		SET_BIT(spi->CR1, SPI_CR1_CPOL);
		SET_BIT(spi->CR1, SPI_CR1_CPHA);
	}
	if(LSBF){
		SET_BIT(spi->CR1, SPI_CR1_LSBFIRST);
	}
	if(master){
		SET_BIT(spi->CR1, SPI_CR1_MSTR);
	}
	if(crc){
		SET_BIT(spi->CR1, SPI_CR1_CRCEN);
	}
	if(NSS){
		SET_BIT(spi->CR1, SPI_CR1_SSM);
	}
	spi->CR1 |= (fre << 3);
	SET_BIT(spi->CR1, SPI_CR1_SPE);
	return 0;
}
uint8_t SPI::SendData8bit(uint8_t* data, uint8_t SPI, uint16_t lenght){
	SPI_TypeDef* spi = Selsct_spi(SPI);
	while(spi->SR & SPI_SR_BSY){}
	for(int i = 0; i < lenght;i++){
		spi->DR = data[i];
		while(!(spi->SR & SPI_SR_TXE)){}
	}
	return 0;
}
uint8_t SPI::SendData16bit(uint16_t* data,uint8_t SPI, uint16_t lenght){
	SPI_TypeDef* spi = Selsct_spi(SPI);
	while(spi->SR & SPI_SR_BSY){}
	for(int i = 0; i < lenght;i++){
		spi->DR = data[i];
		while(!(spi->SR & SPI_SR_TXE)){}
	}
	return 0;
}
uint8_t SPI::GetData8bit(uint8_t SPI){
	SPI_TypeDef* spi = Selsct_spi(SPI);
	while(spi->SR & SPI_SR_BSY){}
	while(!(spi->SR & SPI_SR_RXNE)){}
	return spi->DR;
}
uint16_t SPI::GetData16bit(uint8_t SPI){
	SPI_TypeDef* spi = Selsct_spi(SPI);
	while(spi->SR & SPI_SR_BSY){}
	while(!(spi->SR & SPI_SR_RXNE)){}
	return spi->DR;
}



