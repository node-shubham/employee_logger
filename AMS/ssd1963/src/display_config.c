

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

void Front_Page(void)
{
	Set_Font(&Font16x26);

	fill_screen(WHITE);
	print_image(310, 170, 150, 100, logo);
	print_string(180, 290, "Attendance Management System", 0x1d6791);
}

void Menu_Page(void)
{
	fill_screen(0xd4f7f6);//0x00ffff);
	Set_Font(&Font16x26);

	fill_roundrect(95,385,55,225,0x80c9c7,0xd4f7f6);   //0x80ff80
	fill_roundrect(100,380,60,220,0x80e8e5,0x80c9c7);
	print_string(210,130,"ADMIN",WHITE);

	fill_roundrect(415,705,55,225,0x80c9c7,0xd4f7f6);
	fill_roundrect(420,700,60,220,0x80e8e5,0x80c9c7);
	print_string(460,130,"LOG ATTENDANCE",WHITE);

	fill_roundrect(95,385,255,425,0x80c9c7,0xd4f7f6);
	fill_roundrect(100,380,260,420,0x80e8e5,0x80c9c7);
	print_string(220,330,"VIEW",WHITE);

	fill_roundrect(415,705,255,425,0x80c9c7,0xd4f7f6);
	fill_roundrect(420,700,260,420,0x80e8e5,0x80c9c7);
	print_string(520,330,"SETTING",WHITE);
}

void Admin_Login(void)
{
	int x=0,y=0;
	fill_screen(0xd4f7f6);//0x00ffff);
	Set_Font(&Font16x26);

	fill_roundrect(210+x,590+x,40+y,440+y,0xcccccc,0xd4f7f6);
	fill_roundrect(214+x,586+x,44+y,436+y,0xfffafa,0xcccccc);

	fill_roundrect(240+x,560+x,70+y,225+y,0x80c9c7,0xfffafa);
	fill_roundrect(245+x,555+x,75+y,220+y,0x80e8e5,0x80c9c7);
	print_string(375+x,135+y,"LOGIN",WHITE);


	fill_roundrect(240+x,560+x,255+y,410+y,0x80c9c7,0xfffafa);
	fill_roundrect(245+x,555+x,260+y,405+y,0x80e8e5,0x80c9c7);
	print_string(375+x,320+y,"THUMB",WHITE);
}

void Login_Page(void)
{
	int x=0,y=30;
	fill_screen(0xd4f7f6);//0x00ffff);
	Set_Font(&Font12x12);

	fill_roundrect(210+x,590+x,10+y,410+y,0xcccccc,0xd4f7f6);
	fill_roundrect(214+x,586+x,14+y,406+y,0xfffafa,0xcccccc);

	fill_roundrect(250+x,550+x,100+y,160+y,0xe7eefe,0xfffafa);
	fill_roundrect(260+x,355+x,90+y,110+y,WHITE,WHITE);
	print_string(268+x,95+y,"User ID",0x0c413f);


	fill_roundrect(250+x,550+x,200+y,260+y,0xe7eefe,0xfffafa);
	fill_roundrect(260+x,370+x,190+y,210+y,WHITE,WHITE);
	print_string(270+x,195+y,"PASSWORD",0x0c413f);


	Set_Font(&Font16x26);
	fill_roundrect(250+x,380+x,300+y,360+y,0x80c9c7,0xfffafa);
	fill_roundrect(253+x,377+x,303+y,357+y,0x80e8e5,0x80c9c7);
	print_string(285+x,317+y,"Reset",WHITE);

	fill_roundrect(420+x,550+x,300+y,360+y,0x80c9c7,0xfffafa);
	fill_roundrect(423+x,547+x,303+y,357+y,0x80e8e5,0x80c9c7);
	print_string(455+x,317+y,"Login",WHITE);
}

void Admin_Menu()
{
	int x=0,y=0;
	fill_screen(0xd4f7f6);//0x00ffff);
	Set_Font(&Font16x26);

	fill_roundrect(210+x,590+x,40+y,440+y,0xcccccc,0xd4f7f6);
	fill_roundrect(214+x,586+x,44+y,436+y,0xfffafa,0xcccccc);

	fill_roundrect(242+x,558+x,72+y,132+y,0x80c9c7,0xfffafa);
	fill_circle(270,102,47,0xfffafa);
	fill_circle(270,102,44,0x80c9c7);
	fill_circle(270,102,40,0x80e8e5);
	print_string(375+x,90+y,"Add User",WHITE);


	fill_roundrect(242+x,558+x,164+y,224+y,0x80c9c7,0xfffafa);
	fill_circle(270,194,47,0xfffafa);
	fill_circle(270,194,44,0x80c9c7);
	fill_circle(270,194,40,0x80e8e5);
	print_string(400+x,182+y,"Role",WHITE);

	fill_roundrect(242+x,558+x,256+y,316+y,0x80c9c7,0xfffafa);
	fill_circle(270,286,47,0xfffafa);
	fill_circle(270,286,44,0x80c9c7);
	fill_circle(270,286,40,0x80e8e5);
	print_string(400+x,274+y,"View",WHITE);

	fill_roundrect(242+x,558+x,348+y,408+y,0x80c9c7,0xfffafa);
	fill_circle(270,378,47,0xfffafa);
	fill_circle(270,378,44,0x80c9c7);
	fill_circle(270,378,40,0x80e8e5);
	print_string(375+x,366+y,"Delete User",WHITE);

}

void NewEntry_Page()
{
	int x=0,y=0;
	fill_screen(0xd4f7f6);//0x00ffff);
	Set_Font(&Font12x12);

	fill_roundrect(210+x,590+x,40+y,440+y,0xcccccc,0xd4f7f6);
	fill_roundrect(214+x,586+x,44+y,436+y,0xfffafa,0xcccccc);

	fill_roundrect(250+x,550+x,72+y,132+y,0xe7eefe,0xfffafa);
	fill_roundrect(260+x,320+x,62+y,82+y,WHITE,WHITE);
	print_string(268+x,67+y,"Name",0x0c413f);


	fill_roundrect(250+x,550+x,164+y,224+y,0xe7eefe,0xfffafa);
	fill_roundrect(260+x,310+x,154+y,174+y,WHITE,WHITE);
	print_string(268+x,159+y,"Age",0x0c413f);

	fill_roundrect(250+x,550+x,256+y,316+y,0xe7eefe,0xfffafa);
	fill_roundrect(260+x,305+x,246+y,266+y,WHITE,WHITE);
	print_string(268+x,251+y,"Job",0x0c413f);

	fill_roundrect(250+x,550+x,348+y,408+y,0xe7eefe,0xfffafa);
	fill_roundrect(260+x,360+x,338+y,358+y,WHITE,WHITE);
	print_string(268+x,343+y,"Address",0x0c413f);

}

