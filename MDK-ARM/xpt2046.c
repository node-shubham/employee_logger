#include "xpt2046.h"

extern SPI_HandleTypeDef XPT2046_SPI;

static inline uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t getRaw(uint8_t address)      // static
{
	uint8_t data;
	uint16_t LSB, MSB;
	for(int dly = 0; dly < 10000; dly++);
	HAL_GPIO_WritePin(XPT2046_NSS_PORT, XPT2046_NSS_PIN, GPIO_PIN_RESET);    // if (XPT2046_NSS_SOFT)	
	HAL_SPI_Transmit(&hspi2, &address, 1, 1000);
	address = 0x00;
	HAL_SPI_TransmitReceive(&hspi2, &address, &data, sizeof(data), 1000);   
	MSB = data;   
	address = 0x00;
	HAL_SPI_TransmitReceive(&hspi2, &address, &data, sizeof(data), 1000);   
	LSB = data;
	HAL_GPIO_WritePin(XPT2046_NSS_PORT, XPT2046_NSS_PIN, GPIO_PIN_SET);      // if (XPT2046_NSS_SOFT)	
	return ((MSB << 8) | (LSB)) >> 3;
}

uint16_t getX(void)
{ 
	if (XPT2046_MIRROR_X)
	return map(getRaw(XPT2046_ADDR_X), RAW_MIN_X, RAW_MAX_X, OUT_MAX_X, OUT_MIN_X);
	else
	return map(getRaw(XPT2046_ADDR_X), RAW_MIN_X, RAW_MAX_X, OUT_MIN_X, OUT_MAX_X);
}

uint16_t getY(void)
{ 
	if (XPT2046_MIRROR_Y)
	return map(getRaw(XPT2046_ADDR_Y), RAW_MIN_Y, RAW_MAX_Y, OUT_MAX_Y, OUT_MIN_Y);
	else
	return map(getRaw(XPT2046_ADDR_Y), RAW_MIN_Y, RAW_MAX_Y, OUT_MIN_Y, OUT_MAX_Y);
}

void XPT2046_Init(void)
{
	uint8_t address = 0x00;
	HAL_GPIO_WritePin(XPT2046_NSS_PORT, XPT2046_NSS_PIN, GPIO_PIN_RESET);  // if (XPT2046_NSS_SOFT)
	HAL_SPI_Transmit(&hspi2, (uint8_t*)XPT2046_ADDR_I, 1, 1000);
	address = 0x00;
	HAL_SPI_Transmit(&hspi2, &address, 1, 1000);
	address = 0x00;
	HAL_SPI_Transmit(&hspi2, &address, 1, 1000);
	HAL_GPIO_WritePin(XPT2046_NSS_PORT, XPT2046_NSS_PIN, GPIO_PIN_SET);   // if (XPT2046_NSS_SOFT)
}
