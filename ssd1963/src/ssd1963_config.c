
#include <ssd1963_config.h>
#include "ssd1963.h"
#include "main.h"	

void front_Page(void)
{
	Set_Font(&Font16x26);

	fill_screen(WHITE);
	print_image(310, 170, 150, 100, logo);
	print_string(180, 290, "Attendance Management System", 0x1d6791);

}

void print_grid(void)
{
 for(int j=0; j<75; j++)
	{
	 for(int i=0; i<45; i++)
		 {
			if(i<45 && j<14)
			 draw_vl(99+50*j, 30+10*i, 3, 0x999999);
			if (i<10 && j<75)
				draw_hl(48+10*j, 30+45*i, 3, 0x999999);
		 }
	}
}		

 void background_page(void)
	{			
			fill_screen(BLACK);
		  for(int j=0; j<75; j++)
			{
			 for(int i=0; i<45; i++)
				 {
					if(i<45 && j<14)
					 draw_vl(99+50*j, 30+10*i, 3, 0x999999);   /// 0x808080 final color
					if (i<10 && j<75)
						draw_hl(48+10*j, 30+45*i, 3, 0x999999);
				 }
			}
		    Set_Font(&Font12x18);  
			  print_string(2, 2, "START", YELLOW);
			  print_string(100, 2, "RECORD :", WHITE);	
			  print_string(208, 2, "OFF", WHITE);
			  print_string(300, 2, "SWEEP :     mm/ sec", WHITE);
			  print_string(590, 2, "PAGES :", WHITE);
			  print_string(730, 2, "CH- ", WHITE);	
			  print_string(0, 240, "Ch 1", YELLOW);
//			  print_string(0, 200, "Ch B", 0x6699ff);
//			  print_string(0, 290, "Ch C", 0xccff66);
//			  print_string(0, 380, "Ch D", 0x66ffff);
//			  print_string(2, 260, "Ch E", 0xff0066);
//			  print_string(2, 310, "Ch F", 0xff9933);
//			  print_string(2, 360, "Ch G", 0xcc33ff);
//			  print_string(2, 410, "Ch H", 0xff7733);
			
			  print_string(10, 460, "Ev", WHITE);
}	

void test_point(void)
{
  fill_circle(600, 170, 10, RED);
}

void test_point1(void)
  {	   
	 fill_circle(600, 170, 10, WHITE);
	}

void button(u32 x1,u32 x2,u32 y1,u32 y2, u32 fill_color,u32 edge_color)
{
	fill_roundrect(x1, x2, y1, y2 ,fill_color ,edge_color);
	fill_roundrect2(x1+5, x2-5, y1+5, y2-5 ,button_fill_color);
}

void button_2(u32 x1,u32 x2,u32 y1,u32 y2, u32 b_color,u32 edge_color)
{
	fill_roundrect(x1, x2, y1, y2 ,b_color ,edge_color);
	fill_roundrect2(x1+5, x2-5, y1+5, y2-5 ,button2_fill_color);
}

void fill_UpTriangle(s16 x, s16 y, u16 size, u32 colour)   /// created by naveen
 {
	 for(int i =0; i< size; i++)
	  {
		  draw_hl(x+i,y-i,size-(i*2),colour);
	  }
 }

void	fill_DownTriangle(s16 x, s16 y, u16 size, u32 colour)   /// created by naveen
 {
	 for(int i =0; i< size; i++)
	  {
		  draw_hl(x+i,y+i,size-(i*2),colour);
	  }
 }


void	fill_RightTriangle(s16 x, s16 y, u16 size, u32 colour)   /// created by naveen
 {
	 for(int i =0; i< size; i++)
	  {
		  draw_vl(x+i,y+i,size-(i*2),colour);
	  }
 }

void	fill_LeftTriangle(s16 x, s16 y, u16 size, u32 colour)   /// created by naveen
 {
	 for(int i =0; i< size; i++)
	  {
		  draw_vl(x-i,y+i,size-(i*2),colour);
	  }
 }


void Up_Button(s16 x, s16 y, u16 size, u32 circle_colour, u32 Button_colour)   /// created by naveen
 {
	 u16 button_size = size+(size/7);
   fill_circle(x, y, size, circle_colour);
	 fill_UpTriangle( x-(button_size/2),  y+(button_size/6),  button_size,  Button_colour );
 }

void Down_Button(s16 x, s16 y, u16 size, u32 circle_colour, u32 Button_colour)   /// created by naveen
 {
	 u16 button_size = size+(size/7);
   fill_circle(x, y, size, circle_colour);
	 fill_DownTriangle( x-(button_size/2),  y-(button_size/6),  button_size,  Button_colour );
 }

void Left_Button(s16 x, s16 y, u16 size, u32 circle_colour, u32 Button_colour)   /// created by naveen
 {
	 u16 button_size = size+(size/7);
   fill_circle(x, y, size, circle_colour);
	 fill_LeftTriangle( x+(button_size/6),  y-(button_size/2),  button_size,  Button_colour );
 }
void Right_Button(s16 x, s16 y, u16 size, u32 circle_colour, u32 Button_colour)   /// created by naveen
 {
	 u16 button_size = size+(size/7);
   fill_circle(x, y, size, circle_colour);
	 fill_RightTriangle( x-(button_size/6),  y-(button_size/2),  button_size,  Button_colour );
 }

void symbol_dwn_Arrow (u32 x, u32 y, u32 color)   /// for DOWN Arrow  symbol
{
		draw_line(x, y, x+9, y-9, color);
		draw_line(x, y-1, x+8, y-9, color);
		draw_line(x, y-2, x+7, y-9, color);
		draw_line(x, y-3, x+6, y-9, color);

		draw_line(x, y, x-9, y-9, color);
		draw_line(x, y-1, x-8, y-9, color);
		draw_line(x, y-2, x-7, y-9, color);
		draw_line(x, y-3, x-6, y-9, color);
}


//########################   FRONT_SCREEN  ###################################


void Front_screen(void)
{
	Set_Font(&Font16x26);
	fill_screen(PURPLE);
	//print_string(360,250,"09:00 AM",WHITE);
	//print_string(350,300,"24/01/2023",WHITE);
	print_image(355,180,87,120,thumb);
}

//########################   ADMIN_SCREEN  ########################################

void Admin_screen(void)
{
	Set_Font(&Font16x26);
	fill_screen(PURPLE);
	print_string(150,20,"RFID BASED ATTENDANCE MANAGEMENT",WHITE);

//	draw_hl(0,50,800,BLUE);
//	draw_vl(100,0,480,BLUE);
//	draw_hl(0,430,800,BLUE);
//	draw_vl(700,0,480,BLUE);
//
//	draw_vl(400,50,380,BLUE);
//	draw_hl(50,240,700,BLUE);

	Set_Font(&Font12x18);
	fill_circle(250,145,60,RED);
	print_image(225,115,48,60,user_management);
	print_string(230,218,"USER",WHITE);
	print_string(200,238,"MANAGEMENT",WHITE);

	fill_circle(550,145,60,RED);
	print_image(515,118,60,55,attendance_search);
	print_string(515,218,"SEARCH",WHITE);
	print_string(490,238,"ATTENDANCE",WHITE);


	fill_circle(550,335,60,RED);
	print_image(520,305,60,60,setting);
	print_string(510,408,"SETTING",WHITE);
	//draw_roundrect(505,578,288,365,BLACK);

	fill_circle(250,335,60,RED);
	print_image(220,305,60,60,user_role);
	print_string(200,408,"USER ROLE",WHITE);
}

//########################   USER MANAGEMENT   ####################################

void User_Management(void)
{
	Set_Font(&Font12x18);
	fill_area(100,800,0,480,PURPLE);
	fill_area(70,720,121,439,PURPLE);

	fill_roundrect(250,580,115,195,0xff1a1a,PURPLE);
	fill_circle(250,155,77,PURPLE);
	fill_circle(250,155,60,RED);
	print_string(400,145,"NEW USER",WHITE);
	print_image(220,125,60,51,new_user);

	fill_roundrect(250,580,280,360,0xff1a1a,PURPLE);
	fill_circle(250,320,77,PURPLE);
	fill_circle(250,320,60,RED);
	print_string(400,310,"ALL USER",WHITE);
	print_image(215,300,70,35,all_user);
	BackBtn();

}

//#######################    NEW_USER     #########################################

void NewEntry_page(void)
{
	int x=0,y=0;
	//fill_screen(PURPLE);//0x00ffff);
	Set_Font(&Font12x18);

	fill_roundrect(100+x,700+x,40+y,440+y,0xcccccc,PURPLE);
	fill_roundrect(104+x,696+x,44+y,436+y,0xfffafa,0xcccccc);



	fill_roundrect(547,653,69,135,0xcedcfd,0xfffafa);
	fill_roundrect(550,650,72,132,0xe7eefe,0xcedcfd);
	fill_roundrect(560,640,62,82,WHITE,WHITE);
	print_string(565+x,65+y,"Emp.ID",0x737373);

	//Set_Font(&Font16x24);
	fill_roundrect(547,653,345,411,0xcedcfd,0xfffafa);
	fill_roundrect(550,650,348,408,0xe7eefe,0xcedcfd);
	print_string(573+x,370+y,"SCAN",0x737373);
		Set_Font(&Font12x18);

	NewUser_Name();
	NewUser_Desig(0,0,0,0);
	NewUser_Role();
	NewUser_Card();
	//BackBtn();
}

//######################  NEW_USER(NAME)  #############################
void NewUser_Name(void)
{
	Set_Font(&Font12x18);
	int x=0,y=0;
		fill_roundrect(197,503,69,135,0xcedcfd,0xfffafa);
		fill_roundrect(200+x,500+x,72+y,132+y,0xe7eefe,0xcedcfd);
		fill_roundrect(210+x,280+x,62+y,82+y,WHITE,WHITE);
		print_string(218+x,65+y,"Name",0x737373);

		fill_area(210,400,80,120,0xe7eefe);
		print_string(220,90,emp_name,0x737373);
}

//######################  NEW_USER(DESIG)  #############################
void NewUser_Desig(s32 x1, s32 x2, s32 y1, s32 y2)
{
	Set_Font(&Font12x18);
		fill_roundrect(x1+197,x2+503,y1+161,y2+227,0xcedcfd,0xfffafa);
		fill_roundrect(x1+200,x2+500,y1+164,y2+224,0xe7eefe,0xcedcfd);
		fill_roundrect(210+x1,290+x2,154+y1,174+y2,WHITE,WHITE);
		print_string(218+x1,155+y1,"Desig.",0x737373);
		symbol(470+x1,168+y1,'D',0x999999);
		symbol(470+x1,161+y1,'D',0xe7eefe);
		fill_area(210+x1,400+x2,180+y1,210+y2,0xe7eefe);
		print_string(220+x1,190+x2,desgn_ptr,0x737373);
		//draw_rect(450,500,170,220,BLUE);
}

//######################  NEW_USER(ROLE)  #############################
void NewUser_Role(void)
{
	Set_Font(&Font12x18);
	int x=0,y=0;
		fill_roundrect(197,503,253,319,0xcedcfd,0xfffafa);
		fill_roundrect(200+x,500+x,256+y,316+y,0xe7eefe,0xcedcfd);
		fill_roundrect(210+x,280+x,246+y,266+y,WHITE,WHITE);
		print_string(218+x,251+y,"Role",0x737373);
		symbol(470,264,'D',0x999999);
	symbol(470,257,'D',0xe7eefe);
		fill_area(210,400,270,310,0xe7eefe);
		print_string(220,280,role_ptr,0x737373);
		//draw_rect(450,500,260,310,BLUE);
}

//######################  NEW_USER(CARD)  #############################
void NewUser_Card(void)
{
	Set_Font(&Font12x18);
	int x=0,y=0;
		fill_roundrect(197,503,345,411,0xcedcfd,0xfffafa);
		fill_roundrect(200+x,500+x,348+y,408+y,0xe7eefe,0xcedcfd);
		fill_roundrect(210+x,340+x,338+y,358+y,WHITE,WHITE);
		print_string(218+x,340+y,"Card/Thumb",0x737373);
		symbol(470,353,'D',0x999999);
	symbol(470,346,'D',0xe7eefe);
		fill_area(210,400,370,400,0xe7eefe);
		print_string(220,375,card_ptr,0x737373);
		//draw_rect(450,500,355,405,BLUE);


}

//#######################   BACK_BUTTON   #############################
void BackBtn(void)
{
//	int x=-40,y=0;
//	fill_roundrect(45+x,120+x,15+y,75+y,0xe60000,PURPLE);
//	fill_roundrect(47+x,118+x,17+y,77+y,RED,0xe60000);
//	draw_line(50+x,45+y,75+x,70+y,WHITE);
//	draw_line(50+x,45+y,75+x,20+y,WHITE);
//	draw_line(75+x,20+y,75+x,30+y,WHITE);
//	draw_line(75+x,70+y,75+x,60+y,WHITE);
//	draw_line(75+x,30+y,115+x,30+y,WHITE);
//	draw_line(75+x,60+y,115+x,60+y,WHITE);
//	draw_line(115+x,30+y,115+x,60+y,WHITE);
//	fill_roundrect(15,90,40,88,0xcedcfd,PURPLE);
//	fill_roundrect(18,87,43,85,0xfffafa,0xcedcfd);
//	Set_Font(&Font12x18);
//	print_string(30,54,"BACK",0x737373);
	print_image(10,10,60,60,back);
	//Set_Font(&Font12x18);
}


//########################   KEYPAD_PAGE   ########################################

void PageKeyPad(void)
{
		//Set_Font(&Font12x18);
		Set_Font(&Font16x24);
		int x=0,x1=0,y=31,y1=0,k=0;
		//draw_roundrect(104,696,228,462,BLUE);
		fill_roundrect(135,655,208,430,KEYPAD_COLOR,0xfffafa);
		fill_roundrect(137,653,210,428,WHITE,KEYPAD_COLOR);
		for(int i=0; i<3; i++)
		{
			x1+=25*i;
			for(int j=0; j<=9-(i*2-k); j++)
			{
				fill_roundrect(x1+150+x,x1+190+x,y1+190+y,y1+230+y,0x737373,WHITE);
				fill_roundrect(x1+152+x,x1+188+x,y1+192+y,y1+228+y,KEYPAD_COLOR ,0x737373);

				if(UC_FLAG)
				{
					if(NUM_FLAG)
					{
						print_char(x1+160+x,y1+200+y,symbol_key[i][j],WHITE);
					}
					else
					{
						print_char(x1+160+x,y1+200+y,char_key[i][j],WHITE);
					}
				}
				else
				{
					if(NUM_FLAG)
					{
						print_char(x1+160+x,y1+200+y,symbol_key[i][j],WHITE);
					}
					else
					{
						print_char(x1+160+x,y1+200+y,char_key[i][j],WHITE);
					}
				}
				x+=50;
			}
			x=0;
			k=1;
			y1+=50;
		}
		fill_roundrect(150,215,290+y,330+y,0x737373,WHITE);
		fill_roundrect(152,213,292+y,328+y,KEYPAD_COLOR,0x737373); // Caps
		print_string(155,300+y,"Caps",WHITE);

		fill_roundrect(175,265,340+y,380+y,0x737373,WHITE);
		fill_roundrect(177,263,342+y,378+y,KEYPAD_COLOR,0x737373);	//Num
		print_string(195,350+y,"Num",WHITE);

		fill_roundrect(525,615,340+y,380+y,0x737373,WHITE);
		fill_roundrect(527,613,342+y,378+y,KEYPAD_COLOR,0x737373);  // keypad DOWN.
		symbol(565,335+y,'D',WHITE); //DOWN ARROW.


		fill_roundrect(275,515,340+y,380+y,0x737373,WHITE);
		fill_roundrect(277,513,342+y,378+y,KEYPAD_COLOR,0x737373); // space
		print_string(360,350+y,"Space",WHITE);

		fill_roundrect(575,640,290+y,330+y,0x737373,WHITE);
		fill_roundrect(577,638,292+y,328+y,KEYPAD_COLOR,0x737373); // BackSpace
		print_string(580,300+y,"Back",WHITE);
		x=0;
		x1=0;
		y=0;
		y1=0;
		k=0;
	//Set_Font(&Font12x18);
}

//###############################    DROPDOWN ROLE   ######################################
void dropdown(char *dpdown [], u32 NumOfBox,s16 x1, s16 x2, s16 y1)
{
  int y=0;
	//fill_area(197,503,234,430,WHITE);

	for(idx=0; idx<NumOfBox;idx++)
	{
		//fill_roundrect(197,503,y1+234+y,y1+280+y,0xb3b3b3,0xb3b3b3);
		//Set_Font(&Font16x24);
		if(active_role == idx)
		{
			fill_roundrect(197+x1,503+x2,y1+234+y,y1+280+y,0x999999,0x999999);  //b3b3b3
			print_string(265-50+x1,y1+246+y,(*(dpdown+idx)),WHITE);
		}
		else
		{
			fill_roundrect(197+x1,503+x2,y1+234+y,y1+280+y,0xe6e6e6,0xe6e6e6);
			print_string(265-50+x1 ,y1+246+y,(*(dpdown+idx)),0x999999);
		}

		 y+=40;

	}

	NumOfBox = 0;
}

//################################   TICK_LOGO   #######################################

void Tick_logo(void)
{
	//Set_Font(&Font16x26);
	//print_image(340,350,90,85,green_tick);
	HAL_Delay(3000);
	fill_area(330,440,350,440,WHITE);
}

//#######################################    SEARCH ATTENDANCE   ###########################################

void attendence_search(void)
{
 	uint8_t table_y = 22;
	//fill_screen(PURPLE);
	fill_area(100,700,0,480,PURPLE);
	//fill_roundrect(73, 705, 36, 464,0xcccccc,PURPLE);
	//fill_roundrect(77,701,40,460,0xfffafa,0xcccccc);
	//fill_area(0,800,0,70+10,0x74c69d);
	//fill_roundrect(130,530,25,75,0x9900ff, 0x74c69d);
	fill_roundrect(108,540,40,88,0xcedcfd,PURPLE);	//   Search box
	fill_roundrect2(111 ,537,43,85,0xe7eefe);
	//draw_roundrect(170,570,46,94,BLUE);
	fill_roundrect(570,670,40,88,0xb6cbbb,PURPLE); //   Search button
	fill_roundrect2(573,667,43,85,0xe7eefe);
	//print_string(590,40,"SEARCH",0x737373);

///////////////////////////// for button  //////////////////////////////////////////////////////

	//draw_circle(760, 180-table_y+1, 20, 0x9900ff);
	fill_circle(760, 180-table_y, 20, 0xcedcfd);
	fill_circle(760, 180-table_y, 18, 0xe7eefe);
	symbol(760, 175-table_y, '^', 0x737373);

	for(int i = 4; i<195; i=i+8)
	 {
	   draw_vl(760, 179+i, 3, 0xe7eefe);
		 draw_vl(759, 179+i, 3, 0xe7eefe);
	 }

	//draw_circle(760, 418-table_y+1, 20, 0x9900ff);
	fill_circle(760, 418-table_y, 20, 0xcedcfd);
	fill_circle(760, 418-table_y, 18, 0xe7eefe);
  symbol_dwn_Arrow (760, 423-table_y, 0x737373);  /// for DOWN Arrow  symbol

////////////////////////// for table  ///////////////////////////////////////////////////////////

  	fill_roundrect(94, 684, 115, 440, 0xcedcfd, PURPLE);
//	fill_area(20,730,90,140+3,0x74c69d);
	fill_area(100,678,149-table_y,192+3-table_y,0xcedcfd);
	fill_area(100,678,200-table_y,245+3-table_y,table_color);
	fill_area(100,678,252-table_y,297+3-table_y,table_color_2);
	fill_area(100,678,304-table_y,349+3-table_y,table_color);
	fill_area(100,678,356-table_y,401+3-table_y,table_color_2);
	fill_area(100,678,408-table_y,453+3-table_y,table_color);


	//draw_rect(70,720,143-table_y,461-table_y,table_border_color);

	draw_vl(100+65,143-table_y,318,table_border_color);
	draw_vl(390+140,143-table_y,318,table_border_color);
	draw_vl(170+435,143-table_y,318,table_border_color);

/*
//	draw_hl(20,143,710,table_border_color);
	draw_hl(70,196-table_y,650,table_border_color);
	draw_hl(70,249-table_y,650,table_border_color);
	draw_hl(70,302-table_y,650,table_border_color);
	draw_hl(70,355-table_y,650,table_border_color);
	draw_hl(70,408-table_y,650,table_border_color);
*/
/////////////////////////////for string  ///////////////////////////////////////////////////////

	Set_Font(&Font12x18);
	print_string(585,55,"SEARCH",0x737373);


//	print_int(4, 400, 25+5, 1, 1, WHITE);
//	print_string(200,50,"NAVEEN PRAKASH MAURYA",0x737373);
//	print_string(760,20+5,"6",WHITE);
	print_string(122,163-table_y,"ID",0x737373);
	print_string(330,163-table_y,"NAME",0x737373);
	print_string(535,163-table_y,"IN",0x737373);
	print_string(615,163-table_y,"OUT",0x737373);
//	print_string(170,216-table_y,"NAVEEN PRAKASH MAURYA",0x9900ff);
//	print_string(90,216-table_y,"E001",0x9900ff);
	print_string(540,216-table_y,"09:30",0x737373);
	print_string(615,216-table_y,"06:00",0x737373);
	BackBtn();
}

//######################################    ROLE PAGE   #######################################

void Role_Page(void)
{

  uint8_t table_y = 22;
	fill_screen(PURPLE);

///////////////////////////// for button  //////////////////////////////////////////////////////

	//draw_circle(760, 180-table_y+1, 20, 0x9900ff);
	fill_circle(760, 180-table_y, 20, 0xcedcfd);
	fill_circle(760, 180-table_y, 18, 0xe7eefe);
	symbol(760, 175-table_y, '^', 0x737373);

	for(int i = 4; i<195; i=i+8)
	 {
	   draw_vl(760, 179+i, 3, 0xe7eefe);
		 draw_vl(759, 179+i, 3, 0xe7eefe);
	 }

	//draw_circle(760, 418-table_y+1, 20, 0x9900ff);
	fill_circle(760, 418-table_y, 20, 0xcedcfd);
	fill_circle(760, 418-table_y, 18, 0xe7eefe);
  symbol_dwn_Arrow (760, 423-table_y, 0x737373);  /// for DOWN Arrow  symbol

////////////////////////// for table  ///////////////////////////////////////////////////////////

//	fill_area(20,730,90,140+3,0x74c69d);
	fill_area(70,720,143-table_y,193+3-table_y,0x8c8c8c);
	fill_area(70,720,196-table_y,246+3-table_y,table_color);
	fill_area(70,720,249-table_y,299+3-table_y,table_color_2);
	fill_area(70,720,302-table_y,352+3-table_y,table_color);
	fill_area(70,720,355-table_y,405+3-table_y,table_color_2);
	fill_area(70,720,408-table_y,458+3-table_y,table_color);


	draw_rect(70,720,143-table_y,461-table_y,table_border_color);

	draw_vl(70+90,143-table_y,318,table_border_color);
	draw_vl(550,143-table_y,318,table_border_color);
//	draw_vl(120+460,143-table_y,318,table_border_color);


//	draw_hl(20,143,710,table_border_color);
	draw_hl(70,196-table_y,650,table_border_color);
	draw_hl(70,249-table_y,650,table_border_color);
	draw_hl(70,302-table_y,650,table_border_color);
	draw_hl(70,355-table_y,650,table_border_color);
	draw_hl(70,408-table_y,650,table_border_color);



/////////////////////////////for string  ///////////////////////////////////////////////////////

	Set_Font(&Font12x18);

	print_string(95,163-table_y,"ID",WHITE);
	print_string(300,163-table_y,"NAME",WHITE);
	print_string(620,163-table_y,"ROLE",WHITE);
	print_string(80,216-table_y,"E001",0x9900ff);
	print_string(210,216-table_y,"NAVEEN PRAKASH MAURYA",0x9900ff);
	print_string(570,216-table_y,"EMPLOYEE",0x9900ff);
	BackBtn();
}

//############################################    ALL USER   ###############################################

void AllUser_Page(void)
{
  uint8_t table_y = 22;
	//fill_screen(PURPLE);
	fill_area(150,720,80,439,PURPLE);
	fill_roundrect(45, 725, 96, 464,0xcccccc,PURPLE);
	fill_roundrect(49,721,100,460,0xfffafa,0xcccccc);
	//button_2(20,90,15,65,table_color,0x74c69d);  //   Back button
	//button_2(600,750,36,84,0xe7eefe,0x74c69d);


//	NewUser_Desig(297,217,38,52);

///////////////////////////// for scroll up/down button  //////////////////////////////////////////////////////

	//draw_circle(760, 180-table_y+1, 20, 0x9900ff);
	fill_circle(760, 180-table_y, 20, 0xcedcfd);
	fill_circle(760, 180-table_y, 18, 0xe7eefe);
	symbol(760, 175-table_y, '^', 0x737373);
/*
	for(int i = 4; i<195; i=i+8)
	 {
	   draw_vl(760, 179+i, 3, 0xe7eefe);
		 draw_vl(759, 179+i, 3, 0xe7eefe);
	 }
*/
	//draw_circle(760, 418-table_y+1, 20, 0x9900ff);
	fill_circle(760, 418-table_y, 20, 0xcedcfd);
	fill_circle(760, 418-table_y, 18, 0xe7eefe);
  symbol_dwn_Arrow (760, 423-table_y, 0x737373);  /// for DOWN Arrow  symbol

/////////////////////////////////////////////// for table  ///////////////////////////////////////////////////////////

  	fill_roundrect(64, 476, 121, 439, 0xcedcfd, 0xfffafa);
//	fill_area(20,730,90,140+3,0x74c69d);
	fill_area(70,470,149-table_y,192+3-table_y,0xcedcfd);
	fill_area(70,470,200-table_y,245+3-table_y,table_color);
	fill_area(70,470,252-table_y,297+3-table_y,table_color_2);
	fill_area(70,470,304-table_y,349+3-table_y,table_color);
	fill_area(70,470,356-table_y,401+3-table_y,table_color_2);
	fill_area(70,470,408-table_y,453+3-table_y,table_color);



//	draw_rect(70,470,143-table_y,461-table_y,table_border_color);

	draw_vl(70+65,143-table_y,318,table_border_color);
//	draw_vl(470,143-table_y,318,table_border_color);
//	draw_vl(120+460,143-table_y,318,table_border_color);

/*
//	draw_hl(20,143,710,table_border_color);
	draw_hl(70,196-table_y,400,table_border_color);
	draw_hl(70,249-table_y,400,table_border_color);
	draw_hl(70,302-table_y,400,table_border_color);
	draw_hl(70,355-table_y,400,table_border_color);
	draw_hl(70,408-table_y,400,table_border_color);
*/
/////////////////////////////for drop down  ///////////////////////////////////////////////////////

//	Down_Button(700, 200, 15, BLACK,RED);
//	Down_Button(700, 253, 15, BLACK,RED);
//	Down_Button(700, 306, 15, BLACK,RED);
//	Down_Button(700, 359, 15, BLACK,RED);
//	Down_Button(700, 412, 15, BLACK,RED);


/////////////////////////////for string  ///////////////////////////////////////////////////////

	Set_Font(&Font12x18);

	print_string(92,163-table_y,"ID",0x737373);
	print_string(270,163-table_y,"NAME",0x737373);

	print_string(80,216-table_y,"E999",0x737373);
	//print_string(170,216-table_y,"NAVEEN PRAKASH MAURYA",0x9900ff);

	//BackBtn();

	NewUser_Desig1();
	NewUser_Role1();
	NewUser_Card1();
	SaveAndExit();
}


//######################  NEW_USER(DESIG)  #############################
void NewUser_Desig1(void)
{
	Set_Font(&Font12x18);
		fill_roundrect(494,700,199,259,0xcedcfd,0xfffafa);  // DESIG
		fill_roundrect(499,695,204,254,0xe7eefe,0xcedcfd);

		symbol(670,200,'D',0x999999);
		symbol(670,195,'D',0xe7eefe);


		fill_area(499,615,204,254,0xe7eefe);
		print_string(510,220,desgn_ptr,0x737373);
}

//######################  NEW_USER(ROLE)  #############################
void NewUser_Role1(void)
{
		Set_Font(&Font12x18);
		//int x=0,y=0;
		fill_roundrect(494,700,289,349,0xcedcfd,0xfffafa);  // ROLE
		fill_roundrect(499,695,294,344,0xe7eefe,0xcedcfd);

		symbol(670,293,'D',0x999999);
		symbol(670,288,'D',0xe7eefe);


		fill_area(499,615,294,344,0xe7eefe);
		print_string(510,309,role_ptr,0x737373);
}

//######################  NEW_USER(CARD)  #############################
void NewUser_Card1(void)
{
	Set_Font(&Font12x18);
	//int x=0,y=0;
		fill_roundrect(494,700,379,439,0xcedcfd,0xfffafa);  // CARD
		fill_roundrect(499,695,384,434,0xe7eefe,0xcedcfd);

		symbol(670,386,'D',0x999999);
		symbol(670,381,'D',0xe7eefe);


		fill_area(499,615,384,434,0xe7eefe);
		print_string(510,400,card_ptr,0x737373);
}

void SaveAndExit (void)
{
	fill_roundrect(610,700,121,169,0xcedcfd,0xfffafa);	//   Save and Modify button
	fill_roundrect(613,697,124,166,0xe7eefe,0xcedcfd);
	//draw_roundrect(630,720,121,169,BLUE);

	fill_roundrect(494,584,121,169,0xcedcfd,0xfffafa);
	fill_roundrect(497,581,124,166,0xe7eefe,0xcedcfd);
	//draw_roundrect(494,584,121,169,BLUE);

	Set_Font(&Font12x18);
	print_string(515,138,"SAVE",0x737373);
	print_string(637,138,"EDIT",0x737373);
}

	/*
 void test_color(void)
		{
			fill_screen(BLACK);
			HAL_Delay(500);
			fill_screen(WHITE);
			HAL_Delay(500);
			fill_screen(RED);
			HAL_Delay(500);
			fill_screen(GREEN);
			HAL_Delay(500);
			fill_screen(BLUE);
			HAL_Delay(500);
			fill_screen(YELLOW);
			HAL_Delay(500);
			fill_screen(PURPLE);
			HAL_Delay(500);
			fill_screen(GREY);
			HAL_Delay(500);
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
			//fill_circle(x+10,y+len-40,14,0x00627d);
			//draw_circle(x+10,y+len-40, 15, color);
		}
		
 void h_slider(u32 x, u32 y,u32 len, u32 color)
		{
			draw_roundrect(x,x+len,y,y+15,color);
			fill_area(x+2,x+len-2,y+2,y+13,0x00627d);
		}*/
	
