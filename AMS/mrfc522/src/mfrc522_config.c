/*
 * mfrc522_config.c
 *
 *  Created on: 09-Jan-2023
 *      Author: shubham
 */


#include "mfrc522_config.h"


uint8_t check_validcard(void)
{
	int i=4;

	while(i--)
	{
		if(card_auth[i]!=rfid_id[i])
		{
			char msg[] = "Unauthorised Access\r\n";
			HAL_UART_Transmit(&uart1,(uint8_t *)msg,sizeof(msg),1000);
			return 0;
			break;
		}
	}
	return 1;
}
