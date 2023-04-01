
		#include "stdio.h"
		#include "string.h"
		#include "ssd1963.h"
		#include "types.h"
		#include "stdint.h"
		#include "stdlib.h"
		#include "fonts.h"
		#include "stdbool.h"
		
		static sFONT *Current_Font;
		void Set_Font (sFONT *fonts)
		{
			Current_Font = fonts;
		}
		float Time = 1.0;
		void write_cmd(unsigned int commandToWrite)
		{
			SSD1963_DATAPORT->ODR  = commandToWrite;
			SSD1963_CTRLPORT2->BSRR = SSD1963_PIN_RD;
			SSD1963_CTRLPORT1->BSRR  = (SSD1963_PIN_RS | SSD1963_PIN_CS | SSD1963_PIN_WR)<<16;
			__asm("nop");
			SSD1963_CTRLPORT1->BSRR = (SSD1963_PIN_RS | SSD1963_PIN_CS | SSD1963_PIN_WR);
		}
		
		void write_data(unsigned int dataToWrite)
		{
			SSD1963_DATAPORT->ODR  = dataToWrite;
			SSD1963_CTRLPORT1->BSRR = SSD1963_PIN_RS;
			SSD1963_CTRLPORT2->BSRR = SSD1963_PIN_RD;
			SSD1963_CTRLPORT1->BSRR  = (SSD1963_PIN_CS | SSD1963_PIN_WR)<<16;
			__asm("nop");
			SSD1963_CTRLPORT1->BSRR = (SSD1963_PIN_CS | SSD1963_PIN_WR);
		}
		
		void set_window(u16 x1, u16 x2, u16 y1, u16 y2)
		{
			write_cmd(0x2a); 															//SET page address
			write_data((x1)>>8); 													//SET start page address=0
			write_data(x1);
			write_data((x2)>>8); 													//SET end page address=800
			write_data(x2);

			write_cmd(0x2b); 															//SET column address
			write_data((y1)>>8); 													//SET start column address=0
			write_data(y1);
			write_data((y2)>>8); 													//SET end column address=480
			write_data(y2); 
		}
		
		void add_color(u32 color)
		{
			write_data((color)>>16);
			write_data((color)>>8);
			write_data(color);
		}
		
		void fill_screen(u32 color)
		{
			register u32 i;
			set_window(0,800,0,480);
			write_cmd(0x2c);
			for(i=0;i<801*481;i++)
					add_color(color);
		}
		
		void fill_area(u32 sx, u32 ex, u32 sy,u32 ey,u32 color)
		{
			register int i;
			set_window(sx, ex, sy, ey);
			write_cmd(0x2c);
			for(i = 0; i < ((ex-sx+1)*(ey-sy+1)); i++)
				add_color(color);
		}
		
		void clear_screen(void)
		{
				fill_screen(WHITE);
		}
		
		void set_pixel(u16 x, u16 y, u32 color)
		{
			set_window(x, x, y, y);
			write_cmd(0x2c);														// memory write start 
			add_color(color);
		}
		
		
		void draw_hl(s16 x, s16 y, s16 l, u32 color)
		{
			register int i;
			for (i=0; i<= l; i++)
				set_pixel(x+i, y, color);

		}
		
		void draw_vl(s16 x, s16 y, s16 l,u32 color)
		{
			register int i;
			for (i=0; i<= l; i++)
				set_pixel(x, y+i, color);
		}
		
		void draw_rect(u32 x1, u32 x2,u32 y1, u32 y2,u32 color)
		{
			if (x1>x2)
				swap(int, x1, x2);
			if (y1>y2)
				swap(int, y1, y2);
			

			draw_hl(x1, y1, x2-x1,color);
			draw_hl(x1, y2, x2-x1,color);
			draw_vl(x1, y1, y2-y1,color);
			draw_vl(x2, y1, y2-y1,color);	
		}		

		void draw_roundrect(u32 x1, u32 x2,u32 y1, u32 y2, u32 color)
		{
			if (x1>x2)
			{
				swap(int, x1, x2);
			}
			if (y1>y2)
			{
				swap(int, y1, y2);
			}
			if ((x2-x1)>4 && (y2-y1)>4)
			{
				set_pixel(x1+1,y1+4, color);
				set_pixel(x1+2,y1+3, color);
				set_pixel(x1+3,y1+2, color);
				set_pixel(x1+4,y1+1, color);
				
				set_pixel(x2-4,y1+1, color);
				set_pixel(x2-3,y1+2, color);
				set_pixel(x2-2,y1+3, color);
				set_pixel(x2-1,y1+4, color);
				
				set_pixel(x1+1,y2-4, color);
				set_pixel(x1+2,y2-3, color);
				set_pixel(x1+3,y2-2, color);
				set_pixel(x1+4,y2-1, color);
				
				set_pixel(x2-4,y2-1, color);
				set_pixel(x2-3,y2-2, color);
				set_pixel(x2-2,y2-3, color);
				set_pixel(x2-1,y2-4, color);
				
				
				draw_hl(x1+5, y1, x2-x1-10,color);
				draw_hl(x1+5, y2, x2-x1-10,color);
				draw_vl(x1, y1+5, y2-y1-10,color);
				draw_vl(x2, y1+5, y2-y1-10,color);
			}
		}
		
		void fill_roundrect(u32 x1, u32 x2,u32 y1, u32 y2,u32 fill_color, u32 edge_color)
		{
			fill_area(x1, x2, y1,y2 , fill_color);		// single color fill
			//gradient_fill(x1, x2, y1, y2, 0x56C1ED, 0x2473B8, 0x1D448E); // 3 level gradient color fill
			register int i,j;
			
			for(i=0;i<5;i++)
				for(j=0;j<=i;j++)
				{
					set_pixel(x1+4-i, y1+j, edge_color);
					set_pixel(x2+i-4, y1+j, edge_color);
				}
			for(i=0;i< 5;i++)
				for(j=5;j>i;j--)
				{			
					set_pixel(x1+i, y2+j-5, edge_color);
					set_pixel(x2-i, y2-5+j, edge_color);
				} 
		}
		
		void gradient_fill(u32 x1, u32 x2, u32 y1, u32 y2)
		{

			u16 strip = (y2-y1)/30;
			u16 j=0;
		//	u32 color_code[]= {0x5fc8e6, 0x53b8d9, 0x48a9cb, 0x3d99be, 0x328ab0, 0x2e81a7, 0x2a799e, 0x267095, 0x276b8f, 0x286688, 0x286282, 0x285d7c};   // smart wave  ocen blue gradient
		//		u32 color_code[]= {0x389482, 0x339985, 0x2e9e88, 0x29a38b, 0x24a88e, 0x1fad91, 0x19b394,0x14b897, 0x0fbd9a, 0x0ac29d, 0x05c7a0, 0x00cca3	};   // smart wave  green gradient
        	u32 color_code[]={0xc2708b,0xc76b8a,0xcc6688,0xd16186,0xd65c85,0xdb5783,0xe05281,0xe64c7f,0xeb477e,0xf0427c,0xf53d7a,0xfa3879,0xff3377,0xc2708b,0xc76b8a,0xcc6688,0xd16186,0xd65c85,0xdb5783,0xe05281,};   // smart wave  pink gradient

			
			for(int i=0;i<10;i++)
			{
	
					fill_area(x1, x2, y1+(i+j), y1+ (i+j+1)*strip, color_code[i]);
					fill_area(x1, x2, y1+(i+j+1)*strip, y1+ (i+j+2)*strip, color_code[i+1]);
					fill_area(x1, x2, y1+(i+j+2)*strip, y1+ (i+j+3)*strip, color_code[i+2]);
					j=j+2;
			}		
		}
		
		void gradient_roundrect(u32 x1, u32 x2,u32 y1, u32 y2, u32 edge_color)
		{
			//fill_area(x1, x2, y1,y2 , fill_color);		// single color fill
			//gradient_fill(x1, x2, y1, y2, 0x56C1ED, 0x2473B8, 0x1D448E); // 3 level gradient color fill
			gradient_fill(x1, x2, y1, y2);
			register int i,j;
			
			for(i=0;i<5;i++)
				for(j=0;j<=i;j++)
				{
					set_pixel(x1+4-i, y1+j, edge_color);
					set_pixel(x2+i-4, y1+j, edge_color);
				}
			for(i=0;i< 5;i++)
				for(j=5;j>i;j--)
				{			
					set_pixel(x1+i, y2+j-5, edge_color);
					set_pixel(x2-i, y2-5+j, edge_color);
				} 
		}
		void draw_circle(uint32_t x, uint32_t y, uint32_t r, uint32_t color)
		{
			int32_t  D;  // Decision Variable 
			u32  CurX;   // Current X Value 
			u32  CurY;   // Current Y Value 

			
			D = 3 - (r << 1);
			CurX = 0;
			CurY = r;

			while (CurX <= CurY)
			{
				if (((x+CurX) < WIDTH) && ((y+CurY) < HEIGHT))
					set_pixel(x+CurX, y+CurY, color);
				if (((x+CurX) < WIDTH) && ((y-CurY) >= MIN_Y))
					set_pixel(x+CurX, y-CurY, color);
				if (((x-CurX) >= MIN_X) && ((y+CurY) < HEIGHT))
					set_pixel(x-CurX, y+CurY, color);
				if (((x-CurX) >= MIN_X) && ((y-CurY) >= MIN_Y))
					set_pixel(x-CurX, y-CurY, color);
				if (((x+CurY) < WIDTH) && ((y+CurX) < HEIGHT))
					set_pixel(x+CurY, y+CurX, color);
				if (((x+CurY) < WIDTH) && ((y-CurX) >= MIN_Y))
					set_pixel(x+CurY, y-CurX, color);
				if (((x-CurY) >= MIN_X) && ((y+CurX) < HEIGHT))
					set_pixel(x-CurY, y+CurX, color);
				if (((x-CurY) >= MIN_X) && ((y-CurX) >= MIN_Y))
					set_pixel(x-CurY, y-CurX, color);

				if (D < 0)
				{
					D += (CurX << 2) + 6;
				}
				else
				{
					D += ((CurX - CurY) << 2) + 10;
					CurY--;
				}
				CurX++;
			}
		}

		///// Thick Circle function //////////////
		void draw_thick_circle(uint32_t x, uint32_t y, uint32_t r, uint32_t t, uint32_t color)
		{
			for(register int i = 0; i <= t; i++){
			draw_circle(x,y,(r+i),color);}
			
		
		}
		
		
		void fill_circle(u32 x, u32 y, u32 r, u32 color)
		{
			int32_t  D;       /* Decision Variable */
			uint32_t  CurX;   /* Current X Value */
			uint32_t  CurY;   /* Current Y Value */

			D = 3 - (r << 1);
			CurX = 0;
			CurY = r;

			while (CurX <= CurY)
			{
				if(CurY > 0)
				{
						draw_line(x-CurX, y+CurY, x-CurX, y-CurY, color);
						draw_line(x+CurX, y+CurY, x+CurX, y-CurY, color);
				}

				if(CurX > 0)
				{
					draw_line(x-CurY, y+CurX, x-CurY, y-CurX, color);
					draw_line(x+CurY, y+CurX, x+CurY, y-CurX, color);
				}

				if (D < 0)
				{
					D += (CurX << 2) + 6;
				}
				else
				{
					D += ((CurX - CurY) << 2) + 10;
					CurY--;
				}
				CurX++;
			}
		}
			
		void draw_line( u32 x1, u32 y1, u32 x2, u32 y2 , u32 color )
		{
			uint8_t yLonger = 0;
			int incrementVal, endVal;
			int shortLen = y2-y1;
			int longLen = x2-x1;
			int decInc;
			int j = 0, i = 0;

			if(ABS(shortLen) > ABS(longLen)) {
				int swap = shortLen;
				shortLen = longLen;
				longLen = swap;
				yLonger = 1;
			}

			endVal = longLen;

			if(longLen < 0) {
				incrementVal = -1;
				longLen = -longLen;
				endVal--;
			} else {
				incrementVal = 1;
				endVal++;
			}

			if(longLen == 0)
				decInc = 0;
			else
				decInc = (shortLen << 16) / longLen;

			if(yLonger) {
				for(i = 0;i != endVal;i += incrementVal) {
					set_pixel(x1 + (j >> 16),y1 + i,color);
					j += decInc;
				}
			} else {
				for(i = 0;i != endVal;i += incrementVal) {
					set_pixel(x1 + i,y1 + (j >> 16),color);
					j += decInc;
				}
			}
		} 
		void print_int(s32 num, s32 x, s32 y, u32 length, char filler ,u32 color)
		{
			char buf[25];
			char st[27];
			bool neg = false;
			int c=0, f=0;
			
			if (num==0)
			{
				if (length!=0)
				{
					for (c=0; c<(length-1); c++)
						st[c]=filler;
					st[c]=48;
					st[c+1]=0;
				}
				else
				{
					st[0]=48;
					st[1]=0;
				}
			}
			else
			{
				if (num < 0)
				{
					neg=true;
					num=-num;
				}
				
				while (num>0)
				{
					buf[c]=48+(num % 10);
					c++;
					num=(num-(num % 10))/10;
				}
				buf[c]=0;
				
				if (neg)
				{
					st[0]=45;
				}
				
				if (length>(c+neg))
				{
					for (int i=0; i<(length-c-neg); i++)
					{
						st[i+neg]=filler;
						f++;
					}
				}

				for (int i=0; i<c; i++)
				{
					st[i+neg+f]=buf[c-i-1];
				}
				st[c+neg+f]=0;

			}
			print_string(x, y, st, color);
		}
		
		void convert_float(char *buf, double num, int width, s8 prec)
		{
				char format[10];
				sprintf(format, "%%%i.%if", width, prec);
				sprintf(buf, format, num);
		}
		
		void print_float(double num, s8 dec, int x, int y, char divider, int length, char filler ,u32 color)   // dec : 0 not supported (1-5)
		{
			char st[27];
			bool neg=false;

			if (dec<1)
				dec=1;
			else if (dec>5)
				dec=5;

			if (num<0)
				neg = true;

			convert_float(st, num, length, dec);


			if (divider != '.')
			{
				for (int i=0; i<sizeof(st); i++)
					if (st[i]=='.')
						st[i]=divider;
			}

			if (filler != ' ')
			{
				if (neg)
				{
					st[0]='-';
					for (int i=1; i<sizeof(st); i++)
						if ((st[i]==' ') || (st[i]=='-'))
							st[i]=filler;
				}
				else
				{
					for (int i=0; i<sizeof(st); i++)
						if (st[i]==' ')
							st[i]=filler;
				}
			}
			print_string(x, y, st, color);
		}

		void draw_char(uint16_t x, uint16_t y, const uint16_t *c, u32 color)
		{
			register u32 index = 0, i = 0;

			for(index = 0; index < Current_Font->Height; index++)
			{
				for(i = 0; i < Current_Font->Width; i++)
				{
					if( ((((c[index] & ((0x80 << ((Current_Font->Width / 12 ) * 8 ) ) >> i)) == 0x00) && (Current_Font->Width <= 12)) ||
					(((c[index] & (0x1 << i)) == 0x00)&&(Current_Font->Width > 12 )))  == 0x00)
					{
						if(Current_Font->Height > 24)
							set_pixel( x-i,y+index, color);
						else
							set_pixel( x+i,y+index, color);
					}
				}
			}
		}

		void print_char(uint16_t x, uint16_t y, uint8_t c, u32 color)
		{
			c -= 32;
			draw_char(x, y, &Current_Font->table[c * Current_Font->Height], color);
		}

		void print_string(uint16_t x, uint16_t y, char *ptr,u32 color)
		{
			 register u16 refcolumn = x;
			while (*ptr != 0)
			{
				/* Display one character on LCD */
				print_char(x,y, *ptr, color);
				/* Decrement the column position by 16 */
				refcolumn += Current_Font->Width;
				x += Current_Font->Width;
				/* Point on the next character */
				ptr++;
			}
		}
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		void print_image(u32 x, u32 y, u32 x_res, u32 y_res,const u32 *ptr_image)
		{
			register u32 cnt =0;
			set_window(x,x + x_res-1, y,y + y_res-1);
			write_cmd(0x2c);
			for(cnt = 0; cnt < (x_res * y_res) ; cnt++)
			{
				add_color(*(ptr_image));
				ptr_image++;
			}
		}
			
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
		void ssd1963_setup (void)
		{
			SSD1963_CTRLPORT2->BSRR = SSD1963_PIN_RST << 16;
			HAL_Delay(10);
			SSD1963_CTRLPORT2->BSRR = SSD1963_PIN_RST;
			HAL_Delay(10);

			write_cmd(0xE2);														//PLL multiplier, set PLL clock to 120M
				write_data(0x1E);	    											//N=0x36 for 6.5M, 0x23 for 10M crystal
				write_data(0x02);
				write_data(0x54);
			write_cmd(0xE0);														// PLL enable
				write_data(0x01);
				HAL_Delay(1);
			write_cmd(0xE0);
				write_data(0x03);
				HAL_Delay(1);
			write_cmd(0x01);														// software reset
				HAL_Delay(1);
			write_cmd(0xE6);														//PLL setting for PCLK, depends on resolution
				write_data(0x03);
				write_data(0xFF);
				write_data(0xFF);
				HAL_Delay(1);
			write_cmd(0xB0);														//LCD SPECIFICATION
				write_data(0x20);
				write_data(0x00);
				write_data(0x03);														//Set HDP	799
				write_data(0x1F);
				write_data(0x01);														//Set VDP	479
				write_data(0xDF);
				write_data(0x00);
				HAL_Delay(1);
			write_cmd(0xB4);														//HSYNC
				write_data(0x03);														//Set HT	928
				write_data(0xA0);
				write_data(0x00);														//Set HPS	46
				write_data(0x2E);
				write_data(0x30);														//Set HPW	48
				write_data(0x00);														//Set LPS	15
				write_data(0x0F);
				write_data(0x00);
				HAL_Delay(1);
			write_cmd(0xB6);														//VSYNC
				write_data(0x02);														//Set VT	525
				write_data(0x0D);
				write_data(0x00);														//Set VPS	16
				write_data(0x10);
				write_data(0x10);														//Set VPW	16
				write_data(0x00);														//Set FPS	8
				write_data(0x08);
				HAL_Delay(1);
			write_cmd(0xBA);
				write_data(0x0F);														//GPIO[3:0] out 1
				HAL_Delay(1);
			write_cmd(0xB8);
				write_data(0x07);	   											 //GPIO3=input, GPIO[2:0]=output
				write_data(0x01);														//GPIO0 normal
				HAL_Delay(1);
			write_cmd(0x36);														//rotation
				write_data(0x08);		//write_data(0x2A);
				HAL_Delay(1);
			
			write_cmd(0xF0);														//pixel data interface
				write_data(0x00);
				HAL_Delay(1);
			write_cmd(0xB8);
				write_data(0x0f);   											 //GPIO is controlled by host GPIO[3:0]=output   GPIO[0]=1  LCD ON  GPIO[0]=1  LCD OFF 
				write_data(0x01);   											 //GPIO0 normal
				HAL_Delay(1);
			write_cmd(0xBA);
				write_data(0x01);    												//GPIO[0] out 1 --- LCD display on/off control PIN
				HAL_Delay(1);
			write_cmd(0x29);														//display on
			write_cmd(0xBE);														//set PWM for B/L
				write_data(0x06);
				write_data(0xf0);
				write_data(0x00);
				write_data(0xf0);
				write_data(0x00);
				write_data(0x00);
				HAL_Delay(1);
			write_cmd(0xd0); 
				write_data(0x0d);	
			write_cmd(0x2C); 
			write_cmd(0x29);
		}	
				
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

		void symbol (u32 x, u32 y,s8 sym, u32 color)
		{
			if(sym == '+')
			{	
				draw_hl(x,y,15,color);
				draw_hl(x,y+1,15,color);
				draw_hl(x,y+2,15,color);
				draw_hl(x,y+3,15,color);
				draw_vl(x+8,y-7,16,color);
				draw_vl(x+9,y-7,16,color);
				draw_vl(x+6,y-7,16,color);
				draw_vl(x+7,y-7,16,color);
			}	
			if(sym == '-')
			{	
				draw_hl(x,y,15,color);
				draw_hl(x,y+1,15,color);
				draw_hl(x,y+2,15,color);
				draw_hl(x,y+3,15,color);
			}
			if(sym == 'D')
			{
				for(int i=1; i<=15; i++)
				{	
				//	fill_area(x,x+10,y+5,y+5+i,color);
					fill_area(x-10+i,x+5,y+20,y+20+i,color);
					fill_area(x+5,x+20-i,y+20,y+20+i,color);
				}

			}
			if(sym == '<')   /// for LEFT Arrow  symbol
			{	
				draw_line(x, y, x+9, y-9, color);
				draw_line(x+1, y, x+9, y-8, color);
				draw_line(x+2, y, x+9, y-7, color);
				draw_line(x+3, y, x+9, y-6, color);
				
				draw_line(x, y, x+9, y+9, color);
				draw_line(x+1, y, x+9, y+8, color);
				draw_line(x+2, y, x+9, y+7, color);
				draw_line(x+3, y, x+9, y+6, color);
			}	
			if(sym == '>')   /// for RIGHT Arrow  symbol
			{	
        draw_line(x, y, x-9, y-9, color);
				draw_line(x-1, y, x-9, y-8, color);
				draw_line(x-2, y, x-9, y-7, color);
				draw_line(x-3, y, x-9, y-6, color);
				
				draw_line(x, y, x-9, y+9, color);
				draw_line(x-1, y, x-9, y+8, color);
				draw_line(x-2, y, x-9, y+7, color);
				draw_line(x-3, y, x-9, y+6, color);
			}
			
			if(sym == '^')   /// for UP Arrow  symbol
			{	
        draw_line(x, y, x+9, y+9, color);
				draw_line(x, y+1, x+8, y+9, color);
				draw_line(x, y+2, x+7, y+9, color);
				draw_line(x, y+3, x+6, y+9, color);
				
				draw_line(x, y, x-9, y+9, color);
				draw_line(x, y+1, x-8, y+9, color);
				draw_line(x, y+2, x-7, y+9, color);
				draw_line(x, y+3, x-6, y+9, color);
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
		}
			
void fill_roundrect2(u32 x1,u32 x2,u32 y1,u32 y2,u32 fill_color)
{
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		for (int i=0; i<((y2-y1)/2)+1; i++)
		{
			switch(i)
			{
			case 0:
				draw_hl(x1+2, y1+i, x2-x1-4,fill_color);
				draw_hl(x1+2, y2-i, x2-x1-4,fill_color);
				break;
			case 1:
				draw_hl(x1+1, y1+i, x2-x1-2,fill_color);
				draw_hl(x1+1, y2-i, x2-x1-2,fill_color);
				break;
			default:
				draw_hl(x1, y1+i, x2-x1,fill_color);
				draw_hl(x1, y2-i, x2-x1,fill_color);
			}
		}
	}
}

