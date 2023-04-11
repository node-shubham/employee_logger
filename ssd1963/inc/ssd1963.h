
#include <ssd1963_config.h>
#include "stm32f4xx.h"
#include "stdint.h"
#include "types.h"
#include "fonts.h"

#define HEIGHT 480
#define WIDTH 800
#define MIN_X 0
#define MIN_Y	0

#define SSD1963_DATAPORT	GPIOA
#define SSD1963_CTRLPORT1	GPIOC
#define SSD1963_CTRLPORT2	GPIOB

#define SSD1963_PIN_RD	(1 << 8)
#define SSD1963_PIN_WR	(1 << 13)
#define SSD1963_PIN_CS	(1 << 15)
#define SSD1963_PIN_RS	(1 << 14)
#define SSD1963_PIN_RST	(1 << 9)

#define swap(type, i, j) {type t = i; i = j; j = t;}
#define ABS(X)  ((X) > 0 ? (X) : -(X))

#define BLACK			0x000000     // color palette
#define WHITE			0xFFFFFF
#define RED				0xFF0000
#define GREEN			0x00FF00
#define BLUE			0x0000FF
#define YELLOW		0xFFE000
#define PURPLE		0x800010
#define GREY			0x000210
#define KEY_COLOR 0x8affe2//fbc1d6//d8ebf3//a9efed
#define KEY_EDGE	0xd4f7f6
#define KEY_SHADOW 0x009973
#define BTN_COLOR  0xb30015  //0x800010//0xffffff//0x666666//CCCCCC
#define KEYPAD_COLOR 0xd9d9d9//bfbfbf//0x5372ac
#define BLUE_2 0x33ffff

#define RED_2 0xff4d4d
#define RED_3 0xff6666

#define GREEN_2 0x4dff4d
#define GREEN_3 0x66ff66

#define YELLOW_2 0xffff4d
#define YELLOW_3 0xffff66





///////////////////////  APLLICATION SPECIFIC FUNCTIONS  /////////////////////////


void test_color(void);
void test_pixel(void);
void test_increment(u32 p, s16 q);
void symbol (u32 x, u32 y,s8 sym,u32 color);
void v_slider(u32 x, u32 y,u32 len, u32 color);
void h_slider(u32 x, u32 y,u32 len, u32 color);



//////////////////////////////  USER FUNCTIONS  /////////////////////////////////////

void ssd1963_setup(void);
void set_window(u16 x1, u16 x2, u16 y1, u16 y2);
void fill_screen(u32 color);
void fill_area(u32 sx, u32 ex, u32 sy, u32 ey, u32 color);
void clear_screen(void);
void set_pixel(u16 x, u16 y, u32 color);
void draw_hl(s16 x, s16 y, s16 l,u32 color);
void draw_vl(s16 x, s16 y, s16 l, u32 color);
void draw_rect(u32 x1, u32 x2,u32 y1, u32 y2,u32 color);
void draw_roundrect(u32 x1, u32 x2,u32 y1, u32 y2,u32 color);
void fill_roundrect(u32 x1, u32 x2,u32 y1, u32 y2,u32 fill_color, u32 edge_color);
//void fill_roundrect(u32 x1, u32 x2, u32 y1, u32 y2, u32 color);
void draw_line(u32 x1, u32 x2, u32 y1, u32 y2, u32 color);
void draw_circle(uint32_t x, uint32_t y, uint32_t r, uint32_t color);
void draw_thick_circle(uint32_t x, uint32_t y, uint32_t r, uint32_t t, uint32_t color);
void fill_circle(u32 x, u32 y, u32 r, u32 color);
void gradient_fill(u32 x1, u32 x2, u32 y1, u32 y2);
void gradient_roundrect(u32 x1, u32 x2,u32 y1, u32 y2, u32 edge_color);

void Set_Font (sFONT *fonts);
void draw_char(uint16_t x, uint16_t y, const uint16_t *c, u32 color);

void convert_float(char *buf, double num, int width, s8 prec);
void print_float(double num, s8 dec, int x, int y, char divider, int length, char filler,u32 color);
void print_int(s32 num, s32 x, s32 y, u32 length, char filler,u32 color);
void print_char(uint16_t x, uint16_t y, uint8_t c, u32 color);
void print_string(uint16_t x, uint16_t y, char *ptr,u32 color);
void print_image(u32 x, u32 y, u32 y_res, u32 x_res,const u32 *ptr_image);



//void thick_button(u32 x1,u32 x2,u32 y1,u32 y2, u32 width,u32 height);
void fill_roundrect2(u32 x1,u32 x2,u32 y1,u32 y2,u32 fill_color);
void button(u32 x1,u32 x2,u32 y1,u32 y2, u32 fill_color,u32 edge_color);

void button_2(u32 x1,u32 x2,u32 y1,u32 y2, u32 fill_color,u32 edge_color);


/////////////////////////////  DISPLAY COMMANDS  /////////////////////////////////

#define SSD1963_NOP						0x00
#define SSD1963_SOFT_RESET  			0x01
#define SSD1963_GET_POWER_MODE 			0x0A
#define SSD1963_GET_ADDRESS_MODE		0x0B
#define SSD1963_GET_DISPLAY_MODE		0x0D
#define SSD1963_GET_TEAR_EFFECT_STATUS 	0x0E
#define SSD1963_ENTER_SLEEP_MODE		0x10
#define SSD1963_EXIT_SLEEP_MODE			0x11
#define SSD1963_ENTER_PARTIAL_MODE		0x12
#define SSD1963_ENTER_NORMAL_MODE		0x13
#define SSD1963_EXIT_INVERT_MODE		0x20
#define SSD1963_ENTER_INVERT_MODE		0x21
#define SSD1963_SET_GAMMA_CURVE			0x26
#define SSD1963_SET_DISPLAY_OFF			0x28
#define SSD1963_SET_DISPLAY_ON			0x29
#define SSD1963_SET_COLUMN_ADDRESS		0x2A
#define SSD1963_SET_PAGE_ADDRESS		0x2B
#define SSD1963_WRITE_MEMORY_START		0x2C
#define SSD1963_READ_MEMORY_START		0x2E
#define SSD1963_SET_PARTIAL_AREA		0x30
#define SSD1963_SET_SCROLL_AREA			0x33
#define SSD1963_SET_TEAR_OFF			0x34
#define SSD1963_SET_REAR_ON				0x35
#define SSD1963_SET_ADDRESS_MODE		0x36
#define SSD1963_SET_SCROLL_START		0x37
#define SSD1963_EXIT_IDLE_MODE			0x38
#define SSD1963_ENTER_IDLE_MODE			0x39
#define SSD1963_WRITE_MEMORY_CONTINUE	0x3C
#define SSD1963_READ_MEMORY_CONTINUE	0x3E
#define SSD1963_SET_TEAR_SCANLINE		0x44
#define SSD1963_GET_SCANLINE			0x45
#define SSD1963_READ_DDB				0xA1
#define SSD1963_SET_LCD_MODE			0xB0
#define SSD1963_GET_LCD_MODE			0xB1
#define SSD1963_SET_HORI_PERIOD			0xB4
#define SSD1963_GET_HORI_PERIOD			0xB5
#define SSD1963_SET_VERT_PERIOD			0xB6
#define SSD1963_GET_VERT_PERIOD			0xB7
#define SSD1963_SET_GPIO_CONF			0xB8
#define SSD1963_GET_GPIO_CONF			0xB9
#define SSD1963_SET_GPIO_VALUE			0xBA
#define SSD1963_GET_GPIO_STATUS			0xBB
#define SSD1963_SET_POST_PROC			0xBC
#define SSD1963_GET_POST_PROC			0xBD
#define SSD1963_SET_PWM_CONF			0xBE
#define SSD1963_GET_PWM_CONF			0xBF
#define SSD1963_GET_LCD_GEN0			0xC0
#define SSD1963_SET_LCD_GEN0			0xC1
#define SSD1963_GET_LCD_GEN1			0xC2
#define SSD1963_SET_LCD_GEN1			0xC3
#define SSD1963_GET_LCD_GEN2			0xC4
#define SSD1963_SET_LCD_GEN2			0xC5
#define SSD1963_GET_LCD_GEN3			0xC6
#define SSD1963_SET_LCD_GEN3			0xC7
#define SSD1963_SET_GPIO0_ROP			0xC8
#define SSD1963_GET_GPIO0_ROP			0xC9
#define SSD1963_SET_GPIO1_ROP			0xCA
#define SSD1963_GET_GPIO1_ROP			0xCB
#define SSD1963_SET_GPIO2_ROP			0xCC
#define SSD1963_GET_GPIO2_ROP			0xCD
#define SSD1963_SET_GPIO3_ROP			0xCE
#define SSD1963_GET_GPIO3_ROP			0xCF
#define SSD1963_SET_DBC_CONF			0xD0
#define SSD1963_GET_DBC_CONF			0xD1
#define SSD1963_SET_DBC_TH				0xD4
#define SSD1963_GET_DBC_TH				0xD5
#define SSD1963_SET_PLL					0xE0
#define SSD1963_SET_PLL_MN				0xE2
#define SSD1963_GET_PLL_MN				0xE3
#define SSD1963_GET_PLL_STATUS			0xE4
#define SSD1963_SET_DEEP_SLEEP			0xE5
#define SSD1963_SET_LSHIFT_FREQ			0xE6
#define SSD1963_GET_LSHIFT_FREQ			0xE7
#define SSD1963_SET_PIXEL_DATA_INTERFACE 0xF0
#define SSD1963_PDI_8BIT			0
#define SSD1963_PDI_12BIT			1
#define SSD1963_PDI_16BIT			2
#define SSD1963_PDI_16BIT565	3
#define SSD1963_PDI_18BIT			4
#define SSD1963_PDI_24BIT			5
#define SSD1963_PDI_9BIT			6
#define SSD1963_GET_PIXEL_DATA_INTERFACE 0xF1
