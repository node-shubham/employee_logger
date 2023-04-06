

#include "24c256_config.h"


/*********
calculate_addr = FRIST_EMP_ADDR+(32*(scanned_EMPLO_ID-1));  // employee details store from page no. 162 to 511 (last page)
***********/

bool del = 0;
uint8_t dev_addr = 0xA0;
uint8_t dev_addr1 = 0xA1;
uint8_t serch_emp_no = 0;
uint16_t next_emp_id = 11;
uint16_t last_emp_id = 0;
uint16_t last_del_id = 0;
uint16_t scanned_EMPLO_ID = 0;
uint16_t calculate_addr = 0;
uint16_t del_addr[5] = {0};
uint32_t scanned_UID = 0;
char emp_name[19] = {0};

struct WRITE_DETAILS write_details;
struct READ_DETAILS read_details;


void collect_id (void)
{
	HAL_I2C_Mem_Read(&i2c1, dev_addr1, 0, 2, (uint8_t *) &(next_emp_id), sizeof(next_emp_id), 100);  ///  collect next_emp_id on page 1, address = 0
    HAL_Delay(100);

	if(0xffff == next_emp_id)
	   next_emp_id = 1;

	HAL_I2C_Mem_Read(&i2c1, dev_addr1, 2, 2, (uint8_t *) &(last_emp_id), sizeof(last_emp_id), 100);  ///  collect last_emp_id on page 1, address = 2
	if(0xffff == last_emp_id)
	  last_emp_id = 1;
}



bool chek_employee (void)
{
	calculate_addr = FIRST_EMP_ADDR +(32*(scanned_EMPLO_ID-1));  // employee details store from page no. 162 to 511 (last page)
	HAL_I2C_Mem_Read(&i2c1, dev_addr1, calculate_addr, 2, (uint8_t *) &(read_details), sizeof(read_details), 100);  ///  READ Employee_details
	if((scanned_EMPLO_ID == read_details.rd_EMPLO_id) && (scanned_UID == read_details.rd_EMPLO_RFID))
	  {
		print_string(50, 190, read_details.rd_EMPLO_name, 0x9900ff);
		return 1;    // employee available
	  }
	else
		return 0;   //  employee not available
}


void add_Employee (void)
{
  calculate_addr = FIRST_EMP_ADDR +(32*(next_emp_id-1));  // employee details store from page no. 162 to 511 (last page)
  if(LAST_EMP_ADDR < calculate_addr)
	 {
		print_string(10,90,"This employee_id is out of memory range",0x9900ff);
     }
  else
     {
	    HAL_I2C_Mem_Read(&i2c1, dev_addr1, calculate_addr, 2, (uint8_t *) &(read_details), sizeof(read_details), 100);  ///  READ Employee_details
	  	if((next_emp_id == read_details.rd_EMPLO_id) && (write_details.wr_EMPLO_name == read_details.rd_EMPLO_name))   ///   availble_employee
		  {
			print_string(10,90,"this employee is available",WHITE);
		  }
		else      //  when employee is not available
		   {
			 HAL_I2C_Mem_Write(&i2c1, dev_addr, calculate_addr, 2, (uint8_t *) &(write_details), sizeof(write_details), 100);  ///  write employee_id
			 HAL_Delay(5);
			 next_emp_id++;
			 HAL_I2C_Mem_Write(&i2c1, dev_addr, 0, 2, (uint8_t *) &(next_emp_id), sizeof(next_emp_id), 100);  ///  write employee_id
			 HAL_Delay(5);

			 uint16_t store_addr = 0;
			 uint8_t pos_1st_char = write_details.wr_EMPLO_name[0] - 65;			 // pos_1st_char can be A=0,B=1, C=2, D=3 ... Z=25
			 uint16_t char_addr = 3648+(2*pos_1st_char);     	//   base address of page 57 = 3648
			 HAL_I2C_Mem_Read(&i2c1, dev_addr1, char_addr, 2, (uint8_t *) &(store_addr), sizeof(store_addr), 100);  /// character_addr on page 57 - (3648+(2*pos_1st_char))
			 if(0xffff == store_addr)
			   {
				 store_addr = 3712+(256*pos_1st_char);    	//   base address of A = 3712 (page 58), 4 page = 4*64 = 256 byte
			   }
			 if(254>=(store_addr-(3712+(256*pos_1st_char))))
			   {
				 HAL_I2C_Mem_Write(&i2c1, dev_addr, store_addr, 2, (uint8_t *) &(calculate_addr), sizeof(calculate_addr), 100);  ///
				 HAL_Delay(5);
				 store_addr += 2;
				 HAL_I2C_Mem_Write(&i2c1, dev_addr, char_addr, 2, (uint8_t *) &(store_addr), sizeof(store_addr), 100);  ///  page 57 base addr = 3648
				 HAL_Delay(5);
			   }
		   }
     }
}

#if 0
void display_Employee (void)
{
 // calculate_addr = FRIST_EMP_ADDR +(32*(scanned_EMPLO_ID-1));  // employee details store from page no. 162 to 511 (last page)
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
#endif

void search_Employee (void)
{
 if(0 != emp_name[0])
  {
	char frist_char = emp_name[0];
	uint16_t end_addr = 0;

	uint16_t char_addr = 3648+(2*(frist_char - 65));     	//   page 57 = 3648
	HAL_I2C_Mem_Read(&i2c1, dev_addr1, char_addr, 2, (uint8_t *) &(end_addr), sizeof(end_addr), 100);   // find end address
	if(0xffff == end_addr)
	 {
	   print_string(15,20,"this employee is not available",WHITE);
	 }
	else
	 {
	   uint8_t j=0, cnt_indx=0, total_emp=0;
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
					  HAL_I2C_Mem_Read(&i2c1, dev_addr1, start_addr, 2, (uint8_t *) &(all_addr[i]), sizeof(all_addr[i]), 100);
					  start_addr++;
					}
				  HAL_I2C_Mem_Read(&i2c1, dev_addr1, all_addr[i], 2, (uint8_t *) &(read_details), sizeof(read_details), 100);
				  if(read_details.rd_EMPLO_name[cnt_indx] == emp_name[cnt_indx])
					{
					  serch_emp_no = 0;
					  all_addr[j] = all_addr[i];
					  j++;
					  serch_emp_no = j;
					}
				}
			  total_emp = j;
			  cnt_indx++;
			}
	   if(5<serch_emp_no)
		   serch_emp_no=5;

	   char display_arr[21] = {0};
	   for(int i = 0; i < serch_emp_no; i++)
		  {
			HAL_I2C_Mem_Read(&i2c1, dev_addr1, all_addr[i], 2, (uint8_t *) &(read_details), sizeof(read_details), 100);
			print_string(90, (194+(53*i)), "E", 0x9900ff);
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
  uint8_t y = 0;
  uint16_t deleted_empId = 0;
  del = 1;
  search_Employee();
  if(serch_emp_no)
   {
	  while(del)
	  	  {
	  	    if(isTouched(100, 678, 179+(52*y), 225+(52*y)))
	  	      {
	            draw_rect(100, 678, (179+(52*y)), (225+(52*y)), RED_2);
	            deleted_empId = ((del_addr[y] - FIRST_EMP_ADDR)/32)+1;
	            uint16_t delStore_addr = 0;
				 HAL_I2C_Mem_Read(&i2c1, dev_addr1, 3700, 2, (uint8_t *) &(delStore_addr), sizeof(delStore_addr), 100);  //  store of delStore_addr on page 57 and block 26th- (3648+(2*26)) = 3700
				 if(0xffff == delStore_addr)
				   {
					 delStore_addr = 3392;       	//   base address of page 53 = 3392, for store deleted id
				   }
				 if(254>=(delStore_addr - 3392))
				   {
					 HAL_I2C_Mem_Write(&i2c1, dev_addr, delStore_addr, 2, (uint8_t *) &(deleted_empId), sizeof(deleted_empId), 100);  ///
					 HAL_Delay(5);
					 HAL_I2C_Mem_Write(&i2c1, dev_addr, 4, 2, (uint8_t *) &(deleted_empId), sizeof(deleted_empId), 100);  ///
					 HAL_Delay(5);
					 delStore_addr += 2;
					 HAL_I2C_Mem_Write(&i2c1, dev_addr, 3700, 2, (uint8_t *) &(delStore_addr), sizeof(delStore_addr), 100);
					 HAL_Delay(5);
				   }

	  	    	del = 0;
	  	      }
	  	    y++;
	  	    if(serch_emp_no <= y)
	  	       y = 0;
	  	  }
   }

}


void erase_EEPROM (void)
{
	uint16_t strt_erse_addr = 0;
	uint64_t erase_data = 0xfffffffffffffff;
	while(strt_erse_addr<EEPROM_LAST_ADDR)  // EEPROM_LAST_ADDR means witch address is last for erase.
	{
	  HAL_I2C_Mem_Write(&i2c1, dev_addr, strt_erse_addr, 2, (uint8_t *) &(erase_data), sizeof(erase_data), 100);  ///  write employee_id
		HAL_Delay(5);
		strt_erse_addr += 8;
	}
}

