

#include <24c256_config.h>


/*********
calculate_addr = 10368+(32*(scanned_EMPLO_ID-1));  // employee details store from page no. 162 to 511 (last page)
***********/


struct WRITE_DETAILS write_details;
struct READ_DETAILS read_details;

bool del = 0;
uint8_t dev_addr = 0xA0;
uint8_t dev_addr1 = 0xA1;
uint16_t next_emp_id = 0;
uint16_t last_emp_id = 0;
uint16_t scanned_EMPLO_ID = 0;
uint16_t calculate_addr = 0;
uint16_t del_addr[5] = {0};
uint32_t scanned_UID = 0;
char emp_name[19] = {0};

void var_init(void)
{
/*//	 bool availble_employee = 0;
	 uint8_t dev_addr = 0xA0;
	 uint8_t dev_addr1 = 0xA1;
	 uint16_t scanned_EMPLO_ID = 0;
	 uint16_t calculate_addr = 0;
	 uint32_t scanned_UID = 0;*/
}


void collect_id (void)
{
	HAL_I2C_Mem_Read(&hi2c1, dev_addr1, 0, 2, (uint8_t *) &(next_emp_id), sizeof(next_emp_id), 100);  ///  collect next_emp_id on page 1, address = 0
	if(0xffff == next_emp_id)
	  next_emp_id = 1;
	print_int(next_emp_id, 780, 10, 1, 1, 0x9900ff);
	HAL_I2C_Mem_Read(&hi2c1, dev_addr1, 2, 2, (uint8_t *) &(last_emp_id), sizeof(last_emp_id), 100);  ///  collect last_emp_id on page 1, address = 2
	if(0xffff == last_emp_id)
	  last_emp_id = 1;
}


bool chek_employee (void)
{
	HAL_I2C_Mem_Read(&hi2c1, dev_addr1, calculate_addr, 2, (uint8_t *) &(read_details), sizeof(read_details), 100);  ///  READ Employee_details
	if((scanned_EMPLO_ID == read_details.rd_EMPLO_id) && (scanned_UID == read_details.rd_EMPLO_RFID))
			return 1;    // employee available
	else
			return 0;   //  employee not available
}

void add_Employee (void)
{
  calculate_addr = 10368+(32*(next_emp_id-1));  // employee details store from page no. 162 to 511 (last page)
  if(LAST_EMP_ADDR < calculate_addr)
	 {
		print_string(10,90,"This employee_id is out of memory range",0x9900ff);
     }
  else
     {
	    HAL_I2C_Mem_Read(&hi2c1, dev_addr1, calculate_addr, 2, (uint8_t *) &(read_details), sizeof(read_details), 100);  ///  READ Employee_details
	  	if((next_emp_id == read_details.rd_EMPLO_id) && (write_details.wr_EMPLO_name == read_details.rd_EMPLO_name))   ///   availble_employee
		  {
			print_string(10,90,"this employee is available",WHITE);
		  }
		else      //  when employee is not available
		   {
			 HAL_I2C_Mem_Write(&hi2c1, dev_addr, calculate_addr, 2, (uint8_t *) &(write_details), sizeof(write_details), 100);  ///  write employee_id
			 HAL_Delay(5);
			 next_emp_id++;
			 HAL_I2C_Mem_Write(&hi2c1, dev_addr, 0, 2, (uint8_t *) &(next_emp_id), sizeof(next_emp_id), 100);  ///  write employee_id
			 HAL_Delay(5);

			 uint16_t store_addr = 0;
			 uint8_t pos_1st_char = write_details.wr_EMPLO_name[0] - 65;			 // pos_1st_char can be A=0,B=1, C=2, D=3 ... Z=25
			 uint16_t char_addr = 3648+(2*pos_1st_char);     	//   base address of page 57 = 3648
			 HAL_I2C_Mem_Read(&hi2c1, dev_addr1, char_addr, 2, (uint8_t *) &(store_addr), sizeof(store_addr), 100);  /// character_addr on page 57 - (3648+(2*pos_1st_char))
			 if(0xffff == store_addr)
			   {
				 store_addr = 3712+(256*pos_1st_char);    	//   base address of A = 3712 (page 58), 4 page = 4*64 = 256 byte
			   }
			 if(254>=(store_addr-(3712+(256*pos_1st_char))))
			   {
				 HAL_I2C_Mem_Write(&hi2c1, dev_addr, store_addr, 2, (uint8_t *) &(calculate_addr), sizeof(calculate_addr), 100);  ///
				 HAL_Delay(5);
				 store_addr += 2;
				 HAL_I2C_Mem_Write(&hi2c1, dev_addr, char_addr, 2, (uint8_t *) &(store_addr), sizeof(store_addr), 100);  ///  page 57 base addr = 3648
				 HAL_Delay(5);
			   }
		   }
     }
}

void display_Employee (void)
{
 calculate_addr = 10368+(32*(scanned_EMPLO_ID-1));  // employee details store from page no. 162 to 511 (last page)
 if(LAST_EMP_ADDR < calculate_addr)
   {
	 print_string(10,90,"This employee_id is out of memory range",0x9900ff);
   }
 else
	 {
		 if(chek_employee())     ///    availble_employee = 1;
		  {
  //	    data have readed successfully and stored in read_details structure please copy that.
		  }
		 else     ///    availble_employee = 0;
		    {
			 		   print_string(10,90,"this employee is not available",WHITE);
				}
	 }
}

void search_Employee (void)
{
 if(0 != emp_name[0])
  {
	char frist_char = emp_name[0];
	uint16_t end_addr = 0;

	uint16_t char_addr = 3648+(2*(frist_char - 65));     	//   page 57 = 3648
	HAL_I2C_Mem_Read(&hi2c1, dev_addr1, char_addr, 2, (uint8_t *) &(end_addr), sizeof(end_addr), 100);   // find end address
	if(0xffff == end_addr)
	 {
	   print_string(15,20,"this employee is not available",WHITE);
	 }
	else
	 {
	   uint8_t j=0,k = 0, cnt_indx=0, total_emp=0;
	   uint16_t start_addr = 3712+(256*(frist_char - 65));
	   total_emp = (end_addr - start_addr)+1;
	   uint16_t all_addr[total_emp];

	   while(0 != emp_name[cnt_indx])
			{
			  j = 0;
			  for(int i = 0; i < total_emp; i++)
				{
				  if(0 == cnt_indx)
					{
					  HAL_I2C_Mem_Read(&hi2c1, dev_addr1, start_addr, 2, (uint8_t *) &(all_addr[i]), sizeof(all_addr[i]), 100);
					  start_addr++;
					}
				  HAL_I2C_Mem_Read(&hi2c1, dev_addr1, all_addr[i], 2, (uint8_t *) &(read_details), sizeof(read_details), 100);
				  if(read_details.rd_EMPLO_name[cnt_indx] == emp_name[cnt_indx])
					{
					  k = 0;
					  all_addr[j] = all_addr[i];
					  j++;
					  k = j;
					}
				}
			  total_emp = j;
			  cnt_indx++;
			}
	   if(5<k)
	     k=5;

	   char display_arr[21] = {0};
	   for(int i = 0; i < k; i++)
		  {
			HAL_I2C_Mem_Read(&hi2c1, dev_addr1, all_addr[i], 2, (uint8_t *) &(read_details), sizeof(read_details), 100);
			print_string(90, (194+(53*i)), "E",0x9900ff);
			print_int(read_details.rd_EMPLO_id, 99, (194+(53*i)), 1, 1, 0x9900ff);
			print_string(170, (194+(53*i)), read_details.rd_EMPLO_name, 0x9900ff);
			sprintf(display_arr, "%d:%d       %d:%d", read_details.rd_entry_HH, read_details.rd_entry_MM, read_details.rd_exit_HH, read_details.rd_exit_MM);
			print_string(505, (194+(53*i)), display_arr, 0x9900ff);
			if(1 == del)
			  {
				del_addr[i] = all_addr[i];
			  }
		  }
	 }
	}
}


void delete_Employee (void)
{
  del = 1;
  search_Employee();
  while(del)
	  {
	    if(isTouched(200, 300, (194+(53*1)), 205))
	      {

	      }


	del = 0;
	}
}


void erase_EEPROM (void)
{
	uint16_t strt_erse_addr = 0;
	uint64_t erase_data = 0xffffffffffffffff;
	while(strt_erse_addr<EEPROM_LAST_ADDR)  // EEPROM_LAST_ADDR means witch address is last for erase.
	{
	  HAL_I2C_Mem_Write(&hi2c1, dev_addr, strt_erse_addr, 2, (uint8_t *) &(erase_data), sizeof(erase_data), 100);  ///  write employee_id
		HAL_Delay(5);
		strt_erse_addr += 8;
	}
}

