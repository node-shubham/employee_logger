/*
 * mfrc522_config.c
 *
 *  Created on: 09-Jan-2023
 *      Author: shubham
 */


#include "mfrc522_config.h"

uint8_t check_validcard(uint16_t emp_id){

	/*
	scanned_EMPLO_ID = emp_id;
	if(chek_employee())
	{
		return 1;
	}
	return 0;
	*/

#if 1
	memset(uid_read,0,sizeof(uid_read));
	calculate_addr = FIRST_EMP_ADDR+(32*(emp_id-1))+4;
	HAL_I2C_Mem_Read(&i2c1, dev_addr1, calculate_addr, 2, (uint8_t *)&uid_read, 4, 100);
	sprintf(str1,"UID FROM EEPROM :%x %x %x %x\r\n",uid_read[0],uid_read[1],uid_read[2],uid_read[3]);
	HAL_UART_Transmit(&uart1,(uint8_t *)str1,strlen(str1),1000);
	if((uid_read[0]==cardstr[0])&&(uid_read[1]==cardstr[1])&&(uid_read[2]==cardstr[2])&&(uid_read[3]==cardstr[3]))
	{
		char msg[] = "Access Granted\r\n";
		HAL_UART_Transmit(&uart1,(uint8_t *)msg,sizeof(msg),1000);
		return 1;
	}
	char msg[] = "Access Denied\r\n";
	HAL_UART_Transmit(&uart1,(uint8_t *)msg,sizeof(msg),1000);
	return 0;
#endif


}

void rfid_read(void)
{
//	sprintf(str2,"#### TEST :%x %x %x %x \r\n", cardstr[0], cardstr[1], cardstr[2], cardstr[3]);
//	HAL_UART_Transmit(&uart1,(uint8_t *)str2,strlen(str2),1000);
//	memset(cardstr,0,4);

	status = 0;
	status = MFRC522_Request(PICC_REQIDL, cardstr);
	if(status == MI_OK)
	{
		sprintf(str1,"Card:%x,%x,%x", cardstr[0], cardstr[1], cardstr[2]);
		HAL_Delay(2);
		status = MFRC522_Anticoll(cardstr);
		if(status == MI_OK) {
			uint16_t read_empId=0;
			sprintf(str2,"UID:%x %x %x %x \r\n", cardstr[0], cardstr[1], cardstr[2], cardstr[3]);
			HAL_UART_Transmit(&uart1,(uint8_t *)str2,strlen(str2),1000);
			UID[0] = cardstr[0];
			UID[1] = cardstr[1];
			UID[2] = cardstr[2];
			UID[3] = cardstr[3];
			UID[4] = cardstr[4];
			HAL_Delay(10);
			status = MFRC522_SelectTag(cardstr);
			if (status > 0){
			  SectorKey[0] = ((Mx1[0][0])^(UID[0])) + ((Mx1[0][1])^(UID[1])) + ((Mx1[0][2])^(UID[2])) + ((Mx1[0][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[1] = ((Mx1[1][0])^(UID[0])) + ((Mx1[1][1])^(UID[1])) + ((Mx1[1][2])^(UID[2])) + ((Mx1[1][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[2] = ((Mx1[2][0])^(UID[0])) + ((Mx1[2][1])^(UID[1])) + ((Mx1[2][2])^(UID[2])) + ((Mx1[2][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[3] = ((Mx1[3][0])^(UID[0])) + ((Mx1[3][1])^(UID[1])) + ((Mx1[3][2])^(UID[2])) + ((Mx1[3][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[4] = ((Mx1[4][0])^(UID[0])) + ((Mx1[4][1])^(UID[1])) + ((Mx1[4][2])^(UID[2])) + ((Mx1[4][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[5] = ((Mx1[5][0])^(UID[0])) + ((Mx1[5][1])^(UID[1])) + ((Mx1[5][2])^(UID[2])) + ((Mx1[5][3])^(UID[3]));// 0x11; //KeyA[0]
			  HAL_Delay(10);
			  status = MFRC522_Auth(0x60, 3, SectorKey, cardstr);
			  unsigned char user_bytes[16]={0};
			  status =MFRC522_Read(3, user_bytes);
			  if(status == MI_OK) {
				sprintf(str2,"DATA:%x %x %x %x \r\n", user_bytes[9], user_bytes[10], user_bytes[11], user_bytes[12]);
				HAL_UART_Transmit(&uart1,(uint8_t *)str2,strlen(str2),1000);

				read_empId = (((user_bytes[10]& 0xffff)<<8)| (user_bytes[11]& 0x00ff));
				sprintf(str2,"employee id in card : %d\r\n", read_empId);
				HAL_UART_Transmit(&uart1,(uint8_t *)str2,strlen(str2),1000);
			  }
			}
			if(1==check_validcard(read_empId))
			{
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
				HAL_Delay(100);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);
			}
			MFRC522_StopCrypto1();
			MFRC522_Halt();
		}
	}
}



bool assign_card(void)
{
	status = 0;
	status = MFRC522_Request(PICC_REQIDL, cardstr);
	if(status == MI_OK)
	{
		sprintf(str1,"Card:%x,%x,%x", cardstr[0], cardstr[1], cardstr[2]);
		HAL_Delay(2);
		status = MFRC522_Anticoll(cardstr);
		if(status == MI_OK) {
			sprintf(str2,"UID:%x %x %x %x \r\n", cardstr[0], cardstr[1], cardstr[2], cardstr[3]);
			HAL_UART_Transmit(&uart1,(uint8_t *)str2,strlen(str2),1000);
			UID[0] = cardstr[0];
			UID[1] = cardstr[1];
			UID[2] = cardstr[2];
			UID[3] = cardstr[3];
			UID[4] = cardstr[4];
			HAL_Delay(2);
			status = MFRC522_SelectTag(cardstr);
			if (status > 0){
			  SectorKey[0] = ((Mx1[0][0])^(UID[0])) + ((Mx1[0][1])^(UID[1])) + ((Mx1[0][2])^(UID[2])) + ((Mx1[0][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[1] = ((Mx1[1][0])^(UID[0])) + ((Mx1[1][1])^(UID[1])) + ((Mx1[1][2])^(UID[2])) + ((Mx1[1][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[2] = ((Mx1[2][0])^(UID[0])) + ((Mx1[2][1])^(UID[1])) + ((Mx1[2][2])^(UID[2])) + ((Mx1[2][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[3] = ((Mx1[3][0])^(UID[0])) + ((Mx1[3][1])^(UID[1])) + ((Mx1[3][2])^(UID[2])) + ((Mx1[3][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[4] = ((Mx1[4][0])^(UID[0])) + ((Mx1[4][1])^(UID[1])) + ((Mx1[4][2])^(UID[2])) + ((Mx1[4][3])^(UID[3]));// 0x11; //KeyA[0]
			  SectorKey[5] = ((Mx1[5][0])^(UID[0])) + ((Mx1[5][1])^(UID[1])) + ((Mx1[5][2])^(UID[2])) + ((Mx1[5][3])^(UID[3]));// 0x11; //KeyA[0]
			  HAL_Delay(2);
			  status = MFRC522_Auth(0x60, 3, SectorKey, cardstr);
			  if (status == MI_OK){
				  sprintf(str3, "Auth. OK");
				  HAL_UART_Transmit(&uart1,(uint8_t *)str3,strlen(str3),1000);
				  // Clean-Up the Card:
				  card_data[0] = 0xFF;
				  card_data[1] = 0xFF;
				  card_data[2] = 0xFF;
				  card_data[3] = 0xFF;
				  card_data[4] = 0xFF;
				  card_data[5] = 0xFF;
				  card_data[6] = 0xFF; //Access_bits[6]
				  card_data[7] = 0x07; //Access_bits[7]
				  card_data[8] = 0x80; //Access_bits[8]
				  card_data[9] = 0x00;  //user_byte[9]
				  card_data[10] = 0x00; //user_byte[10]
				  card_data[11] = 0x00; //user_byte[11]
				  HAL_Delay(2);
				  status = MFRC522_Write(3, card_data);
				  if(status == MI_OK) {
					  sprintf(str3, "                ");
					  sprintf(str4, "Card Cleared!");
					  HAL_UART_Transmit(&uart1,(uint8_t *)str3,strlen(str3),1000);
					  HAL_UART_Transmit(&uart1,(uint8_t *)str4,strlen(str4),1000);
				  }
			  }
		   }
		}
	}
	MFRC522_StopCrypto1();
	HAL_Delay(20);
	MFRC522_Halt();

	uint8_t e_id[2]={0};
	e_id[0] =	(next_emp_id>>8)& 0xff;
	e_id[1] = 	next_emp_id & 0xff;

	for (int i = 0; i < 16; i++) {cardstr[i] = 0;}
	status = 0;
	// Find cards
	HAL_Delay(2);
	status = MFRC522_Request(PICC_REQIDL, cardstr);
	HAL_Delay(2);
	status = MFRC522_Anticoll(cardstr);
	HAL_Delay(2);
	status = MFRC522_SelectTag(cardstr);
	SectorKey[0] = 0xFF;
	SectorKey[1] = 0xFF;
	SectorKey[2] = 0xFF;
	SectorKey[3] = 0xFF;
	SectorKey[4] = 0xFF;
	SectorKey[5] = 0xFF;
	HAL_Delay(2);
	status = MFRC522_Auth(0x60, 3, SectorKey, cardstr);
	if (status == MI_OK){
	  card_data[0] = ((Mx1[0][0])^(UID[0])) + ((Mx1[0][1])^(UID[1])) + ((Mx1[0][2])^(UID[2])) + ((Mx1[0][3])^(UID[3]));// 0x11; //KeyA[0]
	  card_data[1] = ((Mx1[1][0])^(UID[0])) + ((Mx1[1][1])^(UID[1])) + ((Mx1[1][2])^(UID[2])) + ((Mx1[1][3])^(UID[3]));// 0x11; //KeyA[0]
	  card_data[2] = ((Mx1[2][0])^(UID[0])) + ((Mx1[2][1])^(UID[1])) + ((Mx1[2][2])^(UID[2])) + ((Mx1[2][3])^(UID[3]));// 0x11; //KeyA[0]
	  card_data[3] = ((Mx1[3][0])^(UID[0])) + ((Mx1[3][1])^(UID[1])) + ((Mx1[3][2])^(UID[2])) + ((Mx1[3][3])^(UID[3]));// 0x11; //KeyA[0]
	  card_data[4] = ((Mx1[4][0])^(UID[0])) + ((Mx1[4][1])^(UID[1])) + ((Mx1[4][2])^(UID[2])) + ((Mx1[4][3])^(UID[3]));// 0x11; //KeyA[0]
	  card_data[5] = ((Mx1[5][0])^(UID[0])) + ((Mx1[5][1])^(UID[1])) + ((Mx1[5][2])^(UID[2])) + ((Mx1[5][3])^(UID[3]));// 0x11; //KeyA[0]
	  card_data[6] = 0xFF; //Access_bits[6]
	  card_data[7] = 0x07; //Access_bits[7]
	  card_data[8] = 0x80; //Access_bits[8]

	  card_data[9] = 0x00; //user_byte[9]
	  card_data[10] = e_id[0]; //user_byte[10]
	  card_data[11] = e_id[1]; //user_byte[11]
	  HAL_Delay(2);
	  status = MFRC522_Write(3, card_data);
	  if(status == MI_OK) {
		  sprintf(str3, "Card Set!");
		  HAL_UART_Transmit(&uart1,(uint8_t *)str3,strlen(str3),1000);
		  FLAG_SCAN =1;
	  }
	  else{
		  sprintf(str4, "New Card!");
		  HAL_UART_Transmit(&uart1,(uint8_t *)str4,strlen(str4),1000);
	  }
	  unsigned char user_bytes[16]={0};
	  status =MFRC522_Read(3, user_bytes);
	  if(status == MI_OK) {
		sprintf(str2,"DATA:%x %x %x %x \r\n", user_bytes[9], user_bytes[10], user_bytes[11], user_bytes[12]);
		HAL_UART_Transmit(&uart1,(uint8_t *)str2,strlen(str2),1000);
	  }
		if(cardstr[0] !=	0x26)
		{
			for(int i=0;i<4;i++)
				issue_uid[i]= cardstr[i];
		}
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);

		return 0;
	}
	return 1;
}

