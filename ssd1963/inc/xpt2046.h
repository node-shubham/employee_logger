#ifndef XPT2046_H_
#define XPT2046_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_rcc.h"
#include "main.h"

#define	XPT2046_SPI 			spi2
#define	XPT2046_NSS_SOFT	0
#define	XPT2046_NSS_PORT 	GPIOB
#define	XPT2046_NSS_PIN 	XPT_CS_Pin

#define	XPT2046_MIRROR_X 	0
#define	XPT2046_MIRROR_Y 	1

#define	XPT2046_ADDR_I 	0x80
#define	XPT2046_ADDR_X 	0xD0
#define	XPT2046_ADDR_Y 	0x90

#define RAW_MIN_X	200
#define RAW_MAX_X	4000
#define OUT_MIN_X	0
#define OUT_MAX_X	799

#define RAW_MIN_Y	200
#define RAW_MAX_Y	3800
#define OUT_MIN_Y	0
#define OUT_MAX_Y	479

uint16_t getX(void);
uint16_t getY(void);
void XPT2046_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* XPT2046_H_ */
