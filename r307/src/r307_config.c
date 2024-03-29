/*
 * r307_config.c
 *
 *  Created on: 22-Mar-2023
 *      Author: shubh
 */

#include "r307_config.h"


void r307_init(void)
{
	  /* set up the instance, supply UART interface functions too */
	  finger.address = 0xFFFFFFFF;
	  finger.password = 0;
	  finger.manual_settings = 0;
	  finger.avail_func = uart6_avail;
	  finger.read_func = uart6_read;
	  finger.write_func = uart6_write;

	  /* init fpm instance, supply time-keeping function */
	  if (fpm_begin(&finger, HAL_GetTick))
	  {
		  fpm_read_params(&finger, &params);
		  printf("Found fingerprint sensor!\r\n");
		  printf("Capacity: %d\r\n", params.capacity);
		  printf("Packet length: %d\r\n", fpm_packet_lengths[params.packet_len]);
	  }
	  else {
		  printf("Did not find fingerprint sensor :(\r\n");
		  while (1);
	  }

}


/* main loop for enroll example */
void enroll_mainloop(void)
{
    while (1) {
        printf("Searching for a free slot to store the template...\r\n");
        int16_t fid;
        if (get_free_id(&fid)){
            enroll_finger(fid);
            //break;
            //return 1;
        }else{
            printf("No free slot in flash library!\r\n");
            //return 1;
        }
    }
}

/* this is equal to the template size for the fingerprint module,
 * some modules have 512-byte templates while others have
 * 768-byte templates. Check the printed result of read_template()
 * to determine the case for your module and adjust the needed buffer
 * size below accordingly */
#define BUFF_SZ     1024

uint8_t template_buffer[BUFF_SZ];

/* main loop for templates example */
void templates_mainloop(void)
{
    while (1) {
        printf("Enter the template ID # you want to read...\r\n");
        int16_t fid = 0;
        while (uart_read_byte(USART1) != -1);
        while (1) {
            while (uart_avail(USART1) == 0);
            char c = uart_read_byte(USART1);
            if (! isdigit(c)) break;
            fid *= 10;
            fid += c - '0';
        }

        /* read the template from its location into the buffer */
        read_template(fid, template_buffer, BUFF_SZ);
    }
}

/* get free ID in sensor database */
uint8_t get_free_id(int16_t * fid)
{
    int16_t p = -1;
    for (int page = 0; page < (params.capacity / FPM_TEMPLATES_PER_PAGE) + 1; page++) {
        p = fpm_get_free_index(&finger, page, fid);
        switch (p) {
            case FPM_OK:
                if (*fid != FPM_NOFREEINDEX) {
                    printf("Free slot at ID %d\r\n", *fid);
                    return 1;
                }
                break;
            default:
                printf("Error code: %d\r\n", p);
                return 0;
        }
    }

    return 0;
}

void matchprints_mainloop(void)
{
    int16_t fid = 18;
    int16_t otherfid = 16;

    while (1) {
        printf("Send any character to match the 2 predefined IDs...\r\n");
        while (uart_avail(USART1) == 0);
        match_prints(fid, otherfid);
        while (uart_read_byte(USART1) != -1);  // clear buffer
        //HAL_Delay(300);
    }
}

void fingerprint_match_loop()
{
	Set_Font(&Font12x18);
    while (1)
    {
        search_database();
        if(fingerMatchFlag){
        	fingerMatchFlag=0;
        	break;
        }
    }
    HAL_Delay(1000);
    fill_area(140, 700, 350, 380, PURPLE);
}

void fingerprint_enroll_loop()
{
    while (1)
    {
        printf("Searching for a free slot to store the template...\r\n");
        int16_t fid;
		if (get_free_id(&fid)){
			enroll_finger(fid);
		}else{
			printf("No free slot in flash library!\r\n");
		}
	    if(enrollOkFlag){
			enrollOkFlag=0;
			break;
        }
    }
    HAL_Delay(1000);
   // fill_area(140, 700, 350, 380, PURPLE);
}

void searchdb_mainloop(void)
{
    while (1)
    {
        printf("\r\nSend any character to search for a print...\r\n");
       // while (uart_avail(USART1) == 0);
        search_database();
        while (uart_read_byte(USART1) != -1);
    }
}

void search_database(void)
{
    int16_t p = -1;

    /* first get the finger image */
    printf("Waiting for valid finger\r\n");
    while (p != FPM_OK) {
        p = fpm_get_image(&finger);
        switch (p) {
            case FPM_OK:
                printf("Image taken\r\n");
                break;
            case FPM_NOFINGER:
                printf(".");
                break;
            default:
                printf("Error: %d\r\n", p);
                return;
        }
    }

    /* convert it and store in buffer/slot 1 */
    p = fpm_image2Tz(&finger, 1);
    switch (p) {
        case FPM_OK:
            printf("Image converted\r\n");
            break;
        default:
            printf("Error: %d\r\n", p);
            return;
    }

    /* search the database for the converted print (now in slot 1) */
    uint16_t fid, score;
    p = fpm_search_database(&finger, &fid, &score, 1);

    /* now wait to remove the finger, though not necessary;
       this was moved here after the search because of the R503 sensor,
       which seems to wipe its buffers after each scan */
    printf("Remove finger\r\n");
    while (fpm_get_image(&finger) != FPM_NOFINGER) {
        HAL_Delay(500);
    }
    printf("\r\n");

    if (p == FPM_OK) {
        printf("Found a print match!\r\n");
        print_string(160,350,"Fingerprint Matched. Welcome",WHITE);
        fingerMatchFlag =1;
    }
    else if (p == FPM_NOTFOUND) {
        printf("Did not find a match\r\n");
        print_string(160,350,"Fingerprint didn't Match. Please Try again !!",WHITE);
        HAL_Delay(1000);
        fill_area(140, 700, 350, 380, PURPLE);
        return;
    }
    else {
        printf("Error: %d\r\n", p);
        return;
    }

    // found a match!
    printf("Found at ID #%d with confidence %d\r\n", fid, score);

}


void enroll_finger(int16_t fid)
{
    int16_t p = -1;
    printf("Waiting for valid finger to enroll\r\n");
    while (p != FPM_OK) {
        p = fpm_get_image(&finger);
        switch (p) {
            case FPM_OK:
                printf("Image taken\r\n");
                break;
            case FPM_NOFINGER:
                printf(".\r\n");
                break;
            default:
                printf("Error code: 0x%X!\r\n", p);
                break;
        }
    }
    // OK success!

    p = fpm_image2Tz(&finger, 1);
    switch (p) {
        case FPM_OK:
            printf("Image converted\r\n");
            break;
        default:
            printf("Error code: 0x%X!\r\n", p);
            return;
    }

    printf("Remove finger\r\n");
    HAL_Delay(2000);
    p = 0;
    while (p != FPM_NOFINGER) {
        p = fpm_get_image(&finger);
        HAL_Delay(10);
    }

    p = -1;
    printf("Place same finger again\r\n");
    while (p != FPM_OK) {
        p = fpm_get_image(&finger);
        switch (p) {
            case FPM_OK:
                printf("Image taken\r\n");
                break;
            case FPM_NOFINGER:
                printf(".\r\n");
                break;
            default:
                printf("Error code: 0x%X!\r\n", p);
                break;
        }
    }

    // OK success!

    p = fpm_image2Tz(&finger, 2);
    switch (p) {
        case FPM_OK:
            printf("Image converted\r\n");
            break;
        default:
            printf("Error code: 0x%X!\r\n", p);
            return;
    }

    // OK converted!
    p = fpm_create_model(&finger);
    switch (p) {
        case FPM_OK:
            printf("Prints matched!\r\n");
            break;
        default:
            printf("Error code: 0x%X!\r\n", p);
            return;
    }

    printf("ID %d...", fid);
    p = fpm_store_model(&finger, fid, 1);
    switch (p) {
        case FPM_OK:
            printf("Stored!\r\n");
            enrollOkFlag=1;
            break;
        default:
            printf("Error code: 0x%X!\r\n", p);
            return;
    }
}

uint16_t read_template(uint16_t fid, uint8_t * buffer, uint16_t buff_sz)
{
    int16_t p = fpm_load_model(&finger, fid, 1);
    switch (p) {
        case FPM_OK:
            printf("Template %d loaded.\r\n", fid);
            break;
        default:
            printf("Error code: 0x%X!\r\n", p);
            return 0;
    }

    // OK success!

    p = fpm_download_model(&finger, 1);
    switch (p) {
        case FPM_OK:
            break;
        default:
            printf("Error code: 0x%X!\r\n", p);
            return 0;
    }

    uint8_t read_finished;
    int16_t count = 0;
    uint16_t readlen = buff_sz;
    uint16_t pos = 0;

    while (1) {
        uint8_t ret = fpm_read_raw(&finger, FPM_OUTPUT_TO_BUFFER, buffer + pos, &read_finished, &readlen);
        if (ret) {
            count++;
            pos += readlen;
            readlen = buff_sz - pos;
            if (read_finished)
                break;
        }
        else {
            printf("Error receiving packet %d\r\n", count);
            return 0;
        }
    }

    uint16_t total_bytes = count * fpm_packet_lengths[params.packet_len];

    /* just for pretty-printing */
    uint16_t num_rows = total_bytes / 16;

    printf("Printing template:\r\n");
    printf("---------------------------------------------\r\n");
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < 16; col++) {
            printf("%X, ", buffer[row * 16 + col]);
        }
        printf("\r\n");
    }
    printf("--------------------------------------------\r\n");

    printf("%d bytes read.\r\n", total_bytes);
    return total_bytes;
}

void match_prints(int16_t fid, int16_t otherfid)
{
    /* read template into slot 2 */
    int16_t p = fpm_load_model(&finger, fid, 1);
    switch (p) {
        case FPM_OK:
            printf("Template %d loaded.\r\n", fid);
            break;
        default:
            printf("Error code: 0x%X!\r\n", p);
            return;
    }

    /* read template into slot 2 */
    p = fpm_load_model(&finger, otherfid, 2);
    switch (p) {
        case FPM_OK:
            printf("Template %d loaded.\r\n", otherfid);
            break;
        default:
            printf("Error code: 0x%X!\r\n", p);
            return;
    }

    uint16_t match_score = 0;
    p = fpm_match_template_pair(&finger, &match_score);
    switch (p) {
        case FPM_OK:
            printf("Match score: %d\r\n", match_score);
            break;
        case FPM_NOMATCH:
            printf("Prints did not match.\r\n");
            break;
        default:
            printf("Error code: 0x%X!\r\n", p);
            return;
    }
}

/* UART interface for fingerprint sensor library -- using USART3 */
uint16_t uart6_avail(void) {
    return uart_avail(USART6);
}

uint16_t uart6_read(uint8_t * bytes, uint16_t len) {
    return uart_read(USART6, bytes, len);
}

void uart6_write(uint8_t * bytes, uint16_t len) {
    uart_write(USART6, bytes, len);
}

