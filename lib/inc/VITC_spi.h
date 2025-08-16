#ifndef VITC_SPI_H
#define VITC_SPI_H

#include <stdint.h>

#define SPI1_num 1
#define SPI2_num 2
#define SPI3_num 3
#define SPI_DOBLW_DUPLEX 1
#define SPI_DOBLW_MISO 2
#define SPI_ONEW_MISO 3
#define SPI_ONEW_MOSI 4
#define SPI_DEL_2 0
#define SPI_DEL_4 1
#define SPI_DEL_8 2
#define SPI_DEL_16 3
#define SPI_DEL_32 4
#define SPI_DEL_64 5
#define SPI_DEL_128 6
#define SPI_DEL_256 7

class SPI{
	public:
	uint8_t SPI_init(uint8_t SPI, uint8_t duplex, bool format, bool master, uint8_t CPxx, bool LSBF, uint8_t fre, bool NSS, bool crc);
	uint8_t SendData8bit(uint8_t* data, uint8_t SPI, , uint16_t lenght);
	uint8_t SendData16bit(uint16_t* data, uint8_t SPI, uint16_t lenght);
	uint8_t GetData8bit(uint8_t SPI);
	uint16_t GetData16bit(uint8_t SPI);
};
#endif
