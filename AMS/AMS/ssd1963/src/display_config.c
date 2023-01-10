

#include "display_config.h"


void test_color(void)
{

	fill_screen(RED);
	HAL_Delay(200);
	fill_screen(GREEN);
	HAL_Delay(200);
	fill_screen(BLUE);
	HAL_Delay(200);
	fill_screen(YELLOW);
	HAL_Delay(200);
	fill_screen(PURPLE);
	HAL_Delay(200);
	fill_screen(GREY);
	HAL_Delay(200);
	fill_screen(BLACK);
	HAL_Delay(200);
	fill_screen(WHITE);
	HAL_Delay(200);
}

void test_pixel(void)
{
	set_pixel(100, 100, RED);
	set_pixel(100, 101, RED);
	set_pixel(100, 102, RED);
	set_pixel(100, 103, RED);
	set_pixel(100, 104, RED);
	set_pixel(100, 105, RED);
	set_pixel(100, 106, RED);
	set_pixel(100, 107, RED);
}

void test_increment(u32 p, s16 q)
{
	int i;
	float j=0;
	for(i=0;i<p;i++)
	{
		print_int(i, 400,280,0,0,GREEN);
		HAL_Delay(500);
		fill_area(390,450,220,290, BLACK);
	}

	while(j<q)
	{
		j= j+0.1;
		print_float(j,2, 400,250,'.',0,0,GREEN);
		HAL_Delay(500);
		fill_area(390,500,200,290, BLACK);
	}
}

void v_slider(u32 x, u32 y,u32 len, u32 color)
{
	draw_roundrect(x,x+20,y,y+len,color);
	fill_area(x+3,x+17,y+3,y+len-3,0x00627d);

}

void h_slider(u32 x, u32 y,u32 len, u32 color)
{
	draw_roundrect(x,x+len,y,y+15,color);
	fill_area(x+2,x+len-2,y+2,y+13,0x00627d);
}
