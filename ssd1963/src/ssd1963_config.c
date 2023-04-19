
#include <ssd1963_config.h>
#include "ssd1963.h"
#include "main.h"	

void logo_page(void)
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


void fill_RightTriangle(s16 x, s16 y, u16 size, u32 colour)   /// created by naveen
 {
	 for(int i =0; i< size; i++)
	  {
		  draw_vl(x+i,y+i,size-(i*2),colour);
	  }
 }

void fill_LeftTriangle(s16 x, s16 y, u16 size, u32 colour)   /// created by naveen
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


void thumb_screen(void)
{
	Set_Font(&Font16x26);
	fill_screen(PURPLE);
	print_image(355,180,87,120,thumb);
	v_slider(450, 185,  100, WHITE);
}

//########################   ADMIN_SCREEN  ########################################

void Admin_screen(void)
{
	Set_Font(&Font16x26);
	fill_screen(PURPLE);
	print_string(150,20,"RFID BASED ATTENDANCE MANAGEMENT",WHITE);

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
	fill_area(80,800,0,480,PURPLE);
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
	Set_Font(&Font12x18);

	fill_roundrect(100+x,700+x,40+y,440+y,0xcccccc,PURPLE);
	fill_roundrect(104+x,696+x,44+y,436+y,0xfffafa,0xcccccc);

	fill_roundrect(547,653,69,135,0xcedcfd,0xfffafa);// emp id
	fill_roundrect(550,650,72,132,0xe7eefe,0xcedcfd);
	fill_roundrect(560,640,62,82,WHITE,WHITE);
	print_string(565+x,65+y,"Emp.ID",0x737373);

	fill_roundrect(547,653,253,319,0xcedcfd,0xfffafa);// save
	fill_roundrect(550,650,256,316,0xe7eefe,0xcedcfd);
	print_string(573+x,280+y,"SAVE",0x737373);

	fill_roundrect(547,653,345,411,0xcedcfd,0xfffafa);// scan
	fill_roundrect(550,650,348,408,0xe7eefe,0xcedcfd);
	print_string(573+x,370+y,"SCAN",0x737373);
	Set_Font(&Font12x18);

	NewUser_Name();
	NewUser_Desig(0,0,0,0);
	NewUser_Role();
	NewUser_Card();

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
	print_string(220,95,emp_name,0x737373);
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

void NewUserSideBtn(void)
{
	int x=0,y=0;
	fill_roundrect(547,653,69,135,0xcedcfd,0xfffafa);// emp id
	fill_roundrect(550,650,72,132,0xe7eefe,0xcedcfd);
	fill_roundrect(560,640,62,82,WHITE,WHITE);
	print_string(565+x,65+y,"Emp.ID",0x737373);

	fill_roundrect(547,653,253,319,0xcedcfd,0xfffafa);// save
	fill_roundrect(550,650,256,316,0xe7eefe,0xcedcfd);
	print_string(573+x,280+y,"SAVE",0x737373);

	fill_roundrect(547,653,345,411,0xcedcfd,0xfffafa);// scan
	fill_roundrect(550,650,348,408,0xe7eefe,0xcedcfd);
	print_string(573+x,370+y,"SCAN",0x737373);
}

//#######################   BACK_BUTTON   #############################
void BackBtn(void)
{
	//draw_roundrect(8, 72, 10, 70, GREEN);
	fill_circle(40, 40, 26, WHITE);
	fill_circle(40, 40, 22, PURPLE);
	symbol(27, 40, '<', WHITE);
	draw_line(30, 39, 50, 39, WHITE);
	draw_line(30, 40, 50, 40, WHITE);
	draw_line(30, 41, 50, 41, WHITE);
}


//########################   KEYPAD_PAGE   ########################################

void PageKeyPad(void)
{
		Set_Font(&Font12x18);
		//Set_Font(&Font16x24);
		int x=0,x1=0,y=31,y1=0,k=0;
		//draw_roundrect(104,696,228,462,BLUE);
		fill_roundrect(135,655,208,430,0x737373,0xfffafa);
		fill_roundrect(137,653,210,428,0xf2f2f2,0x737373);
		for(int i=0; i<3; i++)
		{
			x1+=25*i;
			for(int j=0; j<=9-(i*2-k); j++)
			{
				fill_roundrect(x1+150+x,x1+190+x,y1+190+y,y1+230+y,0x999999,0xf2f2f2);
				fill_roundrect(x1+153+x,x1+187+x,y1+193+y,y1+227+y,KEYPAD_COLOR ,0x999999);

				if(UC_FLAG)
				{
					if(NUM_FLAG)
					{
						print_char(x1+165+x,y1+202+y,symbol_key[i][j],0x737373);
					}
					else
					{
						print_char(x1+165+x,y1+202+y,char_key[i][j],0x737373);
					}
				}
				else
				{
					if(NUM_FLAG)
					{
						print_char(x1+165+x,y1+202+y,symbol_key[i][j],0x737373);
					}
					else
					{
						print_char(x1+165+x,y1+202+y,char_key[i][j],0x737373);
					}
				}
				x+=50;
			}
			x=0;
			k=1;
			y1+=50;
		}
		fill_roundrect(150,215,290+y,330+y,0x999999,0xf2f2f2);
		fill_roundrect(153,212,293+y,327+y,KEYPAD_COLOR,0x999999); // Caps
		print_string(175,302+y,"Uu",0x737373);

		fill_roundrect(175,265,340+y,380+y,0x999999,0xf2f2f2);
		fill_roundrect(178,262,343+y,377+y,KEYPAD_COLOR,0x999999);	//Num
		print_string(200,352+y,"123",0x737373);

		fill_roundrect(525,615,340+y,380+y,0x999999,0xf2f2f2);
		fill_roundrect(528,612,343+y,377+y,KEYPAD_COLOR,0x999999);  // keypad DOWN.
		symbol(555,360+y,'<',0x737373); //DOWN ARROW.
		draw_hl(557, 359+y, 25, 0x737373);
		draw_hl(557, 360+y, 25, 0x737373);
		draw_hl(557, 361+y, 25, 0x737373);


		fill_roundrect(275,515,340+y,380+y,0x999999,0xf2f2f2);
		fill_roundrect(278,512,343+y,377+y,KEYPAD_COLOR,0x999999); // space
		//print_string(363,352+y,"Space",0x737373);

		fill_roundrect(575,640,290+y,330+y,0x999999,0xf2f2f2);
		fill_roundrect(578,637,293+y,327+y,KEYPAD_COLOR,0x999999); // BackSpace
		BackSpaceBtn(553,131);
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

	for(idx=0; idx<NumOfBox;idx++)
	{
		if(active_role == idx)
		{
			fill_roundrect(197+x1,503+x2,y1+234+y,y1+280+y,0x999999,0x999999);  //b3b3b3
			print_string(265-50+x1,y1+246+y,(*(dpdown+idx)),WHITE);
		}
		else
		{
			fill_roundrect(197+x1,503+x2,y1+234+y,y1+280+y,0x999999,0x999999);
			fill_roundrect(198+x1,502+x2,y1+235+y,y1+279+y,0xe6e6e6,0xe6e6e6);
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
	fill_area(100,700,0,480,PURPLE);
	fill_roundrect(94,540,40,88,0xcedcfd,PURPLE);	//   Search box
	fill_roundrect2(97 ,537,43,85,0xe7eefe);
	fill_roundrect(570,684,40,88,0xb6cbbb,PURPLE); //   Search button
	fill_roundrect2(573,681,43,85,0xe7eefe);
	//print_string(590,40,"SEARCH",0x737373);

///////////////////////////// for button  //////////////////////////////////////////////////////


	/*fill_circle(760, 180-table_y, 20, 0xcedcfd);


	fill_circle(760, 180-table_y, 20, 0xcedcfd);
>>>>>>> c105fdbc14359a145b50db96db1a31f80e8eaf38
	fill_circle(760, 180-table_y, 18, 0xe7eefe);
	symbol(760, 175-table_y, '^', 0x737373);

	for(int i = 4; i<195; i=i+8)

		 {
		   draw_vl(760, 179+i, 3, 0xe7eefe);
			 draw_vl(759, 179+i, 3, 0xe7eefe);
		 }


	 {
	   draw_vl(760, 179+i, 3, 0xe7eefe);
		 draw_vl(759, 179+i, 3, 0xe7eefe);
	 }
>>>>>>> c105fdbc14359a145b50db96db1a31f80e8eaf38
	fill_circle(760, 418-table_y, 20, 0xcedcfd);
	fill_circle(760, 418-table_y, 18, 0xe7eefe);
    symbol_dwn_Arrow (760, 423-table_y, 0x737373);  /// for DOWN Arrow  symbol*/

    search_table();
	BackBtn();

}

//######################################    ROLE PAGE   #######################################

void Role_Page(void)
{

  uint8_t table_y = 22;
	fill_screen(PURPLE);

///////////////////////////// for button  //////////////////////////////////////////////////////

/*
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
*/

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
	fill_roundrect(95,540,25,73,0xcedcfd,PURPLE);	//   Search box
	fill_roundrect2(98 ,537,28,70,0xe7eefe);
	fill_roundrect(570,685,25,73,0xb6cbbb,PURPLE); //   Search button
	fill_roundrect2(573,681,28,70,0xe7eefe);

	fill_area(150,720,80,439,PURPLE);
	fill_roundrect(95, 685, 96, 464,0xcccccc,PURPLE);
	fill_roundrect(99,681,100,460,0xfffafa,0xcccccc);

///////////////////////////// for scroll up/down button  //////////////////////////////////////////////////////

//void arrowBar(u16 x, u16 y)  // x = 760,  y = 180
{
	fill_circle(760, 180-table_y, 20, 0xcedcfd);
	fill_circle(760, 180-table_y, 18, 0xe7eefe);
	symbol(760, 175-table_y, '^', 0x737373);
	for(int i = 4; i<195; i=i+8)
	{
		draw_vl(760, 179+i, 3, 0xe7eefe);
		draw_vl(759, 179+i, 3, 0xe7eefe);
	}

    fill_circle(760, 418-table_y, 20, 0xcedcfd);
	fill_circle(760, 418-table_y, 18, 0xe7eefe);
	symbol_dwn_Arrow (760, 423-table_y, 0x737373);  /// for DOWN Arrow  symbol
}

/////////////////////////////////////////////// for table  ///////////////////////////////////////////////////////////

  	fill_roundrect(114, 476, 121, 439, 0xcedcfd, 0xfffafa);
//	fill_area(20,730,90,140+3,0x74c69d);
	fill_area(120,470,149-table_y,192+3-table_y,0xcedcfd);
	fill_area(120,470,200-table_y,245+3-table_y,table_color);
	fill_area(120,470,252-table_y,297+3-table_y,table_color_2);
	fill_area(120,470,304-table_y,349+3-table_y,table_color);
	fill_area(120,470,356-table_y,401+3-table_y,table_color_2);
	fill_area(120,470,408-table_y,453+3-table_y,table_color);

	draw_vl(70+115,143-table_y,318,table_border_color);

	/////////////////////////////for string  ///////////////////////////////////////////////////////
	Set_Font(&Font12x18);
	print_string(142,163-table_y,"ID",0x737373);
	print_string(320,163-table_y,"NAME",0x737373);
	print_string(595,40,"SEARCH",0x737373);

	NewUser_Desig1(0xcedcfd);
	NewUser_Role1(0xcedcfd);
	NewUser_Card1(0xcedcfd);
	SaveAndEdit();


}


//######################  NEW_USER(DESIG)  #############################
void NewUser_Desig1(u32 Fill_colour)
{
	Set_Font(&Font12x18);
	fill_roundrect(494,670,199,259,0xcedcfd,0xfffafa);  // DESIG 0xe7eefe
	fill_roundrect(499,665,204,254,Fill_colour,0xcedcfd);

	symbol(640,200,'D',0x999999);
	symbol(640,195,'D',Fill_colour);

	print_string(510,220,desgn_ptr,0x737373);
}

//######################  NEW_USER(ROLE)  #############################
void NewUser_Role1(u32 Fill_colour)
{
		Set_Font(&Font12x18);
		//int x=0,y=0;
		fill_roundrect(494,670,289,349,0xcedcfd,0xfffafa);  // ROLE  0xe7eefe
		fill_roundrect(499,665,294,344, Fill_colour,0xcedcfd);

		symbol(640,293,'D',0x999999);
		symbol(640,288,'D',Fill_colour);


		//fill_area(499,615,294,344,0xe7eefe);
		print_string(510,309,role_ptr,0x737373);
}

//######################  NEW_USER(CARD)  #############################
void NewUser_Card1(u32 Fill_colour)
{
	Set_Font(&Font12x18);
	fill_roundrect(494,670,379,439,0xcedcfd,0xfffafa);  // CARD  Fill_colour =  0xe7eefe
	fill_roundrect(499,665,384,434,Fill_colour,0xcedcfd);

	symbol(640,386,'D',0x999999);
	symbol(640,381,'D',Fill_colour);
	print_string(510,400,card_ptr,0x737373);
}

void SaveAndEdit (void)
{
	fill_roundrect(590,670,121,169,0xcedcfd,0xfffafa);	//   Save and Modify button
	fill_roundrect(593,667,124,166,0xe7eefe,0xcedcfd);

	fill_roundrect(494,574,121,169,0xcedcfd,0xfffafa); //delete
	fill_roundrect(497,571,124,166,0xe7eefe,0xcedcfd);

	Set_Font(&Font12x18);
	print_string(500,138,"DELETE",0x737373);
	print_string(610,138,"EDIT",0x737373);

}

	
//############################ BackSpace Btn ###############################################

void BackSpaceBtn(u32 x, u32 y)
{
	Set_Font(&Font16x24);
	draw_hl(50+x, 199+y, 20, 0x737373);
	draw_hl(50+x, 200+y, 20, 0x737373);

	draw_hl(50+x, 220+y, 20, 0x737373);
	draw_hl(50+x, 221+y, 20, 0x737373);

	draw_vl(70+x, 200+y, 20, 0x737373);
	draw_vl(71+x, 200+y, 20, 0x737373);

	draw_line(37+x, 210+y, 50+x, 220+y, 0x737373);
	draw_line(37+x, 211+y, 50+x, 221+y, 0x737373);

	draw_line(37+x, 210+y, 50+x, 200+y, 0x737373);
	draw_line(37+x, 209+y, 50+x, 199+y, 0x737373);

	draw_line(55+x, 205+y, 65+x, 215+y, 0x737373);
	draw_line(54+x, 205+y, 64+x, 215+y, 0x737373);

	draw_line(55+x, 215+y, 65+x, 205+y, 0x737373);
	draw_line(56+x, 215+y, 66+x, 205+y, 0x737373);

}


void search_table(void)
{
	////////////////////////// for table  ///////////////////////////////////////////////////////////
	uint8_t table_y = 22;
	fill_roundrect(94, 684, 115, 440, 0xcedcfd, PURPLE);
	fill_area(100,678,200-table_y,245+3-table_y,table_color);
	fill_area(100,678,252-table_y,297+3-table_y,table_color_2);
	fill_area(100,678,304-table_y,349+3-table_y,table_color);
	fill_area(100,678,356-table_y,401+3-table_y,table_color_2);
	fill_area(100,678,408-table_y,453+3-table_y,table_color);

	draw_vl(100+65,143-table_y,318,table_border_color);
	draw_vl(390+120,143-table_y,318,table_border_color);
	draw_vl(170+425,143-table_y,318,table_border_color);

	Set_Font(&Font12x18);
	print_string(585,55,"SEARCH",0x737373);

	print_string(122,163-table_y,"ID",0x737373);
	print_string(330,163-table_y,"NAME",0x737373);
	print_string(535,163-table_y,"IN",0x737373);
	print_string(615,163-table_y,"OUT",0x737373);
	print_string(520,216-table_y,"09:30",0x737373);
	print_string(605,216-table_y,"06:00",0x737373);

}
