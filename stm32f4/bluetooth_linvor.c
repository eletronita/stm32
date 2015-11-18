/**
 * @file bluetooth_linvor.c
 * @author My Self
 * @date 9 Sep 2012
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */


#include "bluetooth_linvor.h"


  /**
    * @brief    This function sends a command to know the version of the module.
    * 		    When the command is sent, the response of the module is saved in the
    * 		    blt_linvor_struct.Version that you have passed as a pointer.
    *
    * @param      huart: pointer to a UART_HandleTypeDef structure that contains
    *             the configuration information for the specified UART module.
    * @param      blt_linvor_struct: pointer to a BLT_Linvor_TypeDef structure that contains
    *                the configuration information for the specified bluetooth module.
    * @retval     BLT_LINVOR_SUCCESS  : The version was get
    * @retval     BLT__LINVOR_ERROR   : The version wasn't get
    *
    * @attention  THIS FUNCTION MUST ONLY BE CALLED WHEN THE MODULE ISN'T CONNECTED TO
    * 		       A DEVICE OTHERWISE THE (AT) COMMAND IS SENT DIRECTLY TO THE DEVICE.
    *
    */

BLT_Linvor_ErrorStatus BLT_Get_Version( UART_HandleTypeDef *huart, BLT_Linvor_TypeDef *blt_linvor_struct)
{
  uint8_t for_var = 0;

  /* Set the AT command to get the version the module : AT+VERSION*/
  BLT_Linvor_TX[0] = 'A';
  BLT_Linvor_TX[1] = 'T';
  BLT_Linvor_TX[2] = '+';
  BLT_Linvor_TX[3] = 'V';
  BLT_Linvor_TX[4] = 'E';
  BLT_Linvor_TX[5] = 'R';
  BLT_Linvor_TX[6] = 'S';
  BLT_Linvor_TX[7] = 'I';
  BLT_Linvor_TX[8] = 'O';
  BLT_Linvor_TX[9] = 'N';

  /*Send AT+VERSION command in polling mode through the UART*/
  if(HAL_UART_Transmit(huart,BLT_Linvor_TX,VERSION_SEND_SIZE,BLT_LINVOR_TIMEOUT)== HAL_OK)
  {
    /*wait the response in polling mode of the AT command sent through the UART*/
	if(HAL_UART_Receive(huart,BLT_Linvor_RX,VERSION_RESP_SIZE,BLT_LINVOR_TIMEOUT) == HAL_OK)
	{
	  /*The correct response of the at command AT+VERSION is  OKlinvorVx.y. The code
	  * bellow takes only the part correspondent to the Vx.y of the complete response.
	  */
	  for(for_var = 0; for_var < VERSION_SIZE; for_var++)
	  {
	    blt_linvor_struct->Version[for_var] =  BLT_Linvor_RX[for_var+8];
	  }
	  return  BLT_LINVOR_SUCCESS;
	}
  }

  /*set version do none*/
  for(for_var = 0; for_var < VERSION_SIZE; for_var++)
  {
	  blt_linvor_struct->Version[for_var] = '-';
  }

  return BLT_LINVOR_ERROR;


}

  /**
     * @brief This function sends a command to set the NAME of the module.
     *
     * @param      huart : pointer to a UART_HandleTypeDef structure that contains
     *              the configuration information for the specified UART module.
     * @param      blt_linvor_struct : pointer to a BLT_Linvor_TypeDef structure that contains
     *             the name for the specified bluetooth module.
     * @param      size_name : the size in bytes of the name passed as parameter
     * @retval     BLT_SUCCESS : The name was set
     * @retval     BLT_ERROR   : The name wasn't set
     *
     * @attention  THIS FUNCTION MUST ONLY BE CALLED WHEN THE MODULE ISN'T CONNECTED TO
     * 		       A DEVICE OTHERWISE THE (AT) COMMAND IS SENT DIRECTLY TO THE DEVICE.
     */

BLT_Linvor_ErrorStatus BLT_Linvor_Set_Name( UART_HandleTypeDef *huart, BLT_Linvor_TypeDef *blt_linvor_struct, uint8_t size_name)
{
  uint8_t for_var = 0;

  if(size_name > NAME_MAX_SIZE)
  {
	  return BLT_LINVOR_ERROR;
  }

  /* Set the AT command to set the name of the module : AT+NAME*/
  BLT_Linvor_TX[0] = 'A';
  BLT_Linvor_TX[1] = 'T';
  BLT_Linvor_TX[2] = '+';
  BLT_Linvor_TX[3] = 'N';
  BLT_Linvor_TX[4] = 'A';
  BLT_Linvor_TX[5] = 'M';
  BLT_Linvor_TX[6] = 'E';


  for(for_var = 0;  for_var < size_name; for_var++)
  {
    BLT_Linvor_TX[for_var + NAME_SEND_SIZE] = blt_linvor_struct->Name[for_var];
  }

  for(for_var = size_name;  for_var < NAME_MAX_SIZE; for_var++)
  {
    blt_linvor_struct->Name[for_var] = 'x';
  }

  if(HAL_UART_Transmit(huart,BLT_Linvor_TX,NAME_SEND_SIZE+size_name,BLT_LINVOR_TIMEOUT) == HAL_OK)
  {
    /*wait the response in polling mode of the AT command sent through the UART*/
	if(HAL_UART_Receive(huart,BLT_Linvor_RX,NAME_RESP_SIZE,BLT_LINVOR_TIMEOUT) == HAL_OK)
	{
	  if(Compare_Array(BLT_Linvor_RX,NAME_RESP_OK,NAME_RESP_SIZE)  == SUCCESS)
	  {
	    return BLT_LINVOR_SUCCESS;
	  }
	}
  }

  for(for_var = 0;  for_var < 10; for_var++)
  {
    blt_linvor_struct->Name[for_var] = '-';
  }

  return BLT_LINVOR_ERROR;

}



/**
   * @brief      This function sends a command to set the PIN code of the module.

   *
   * @param 	 huart : pointer to a UART_HandleTypeDef structure that contains
   *             the configuration information for the specified UART module.
   *
   * @param  	 blt_linvor_struct : pointer to a BLT_Linvor_TypeDef structure that contains
   *             the pin code for the specified bluetooth module.
   *
   * @retval 	 BLT_LINVOR_SUCCESS : The PIN code was set
   * @retval 	 BLT_LINVOR_ERROR   : The PIN code wasn't set
   *
   * @attention  THIS FUNCTION MUST ONLY BE CALLED WHEN THE MODULE ISN'T CONNECTED TO
   * 		     A DEVICE OTHERWISE THE (AT) COMMAND IS SENT DIRECTLY TO THE DEVICE.
   */

BLT_Linvor_ErrorStatus BLT_Linvor_Set_Pin( UART_HandleTypeDef *huart, BLT_Linvor_TypeDef *blt_linvor_struct)
{
  uint8_t for_var = 0;
  /* Set the AT command to set the PIN code the module : AT+Pinxxxx*/
  BLT_Linvor_TX[0] = 'A';
  BLT_Linvor_TX[1] = 'T';
  BLT_Linvor_TX[2] = '+';
  BLT_Linvor_TX[3] = 'P';
  BLT_Linvor_TX[4] = 'I';
  BLT_Linvor_TX[5] = 'N';

  /* Insert the "PIN code" to the BLT_Linvor_TX*/
  for(for_var = 0;  for_var < PIN_MAX_SIZE; for_var++)
  {
	  BLT_Linvor_TX[for_var+6] = blt_linvor_struct->Pin[for_var];
  }

  /*Send AT+PINxxxx where xxxx is the new "PIN" command in polling mode through the UART*/
  if(HAL_UART_Transmit(huart,BLT_Linvor_TX,PIN_SEND_SIZE,BLT_LINVOR_TIMEOUT) == HAL_OK)
  {
    /*wait the response in polling mode of the AT command sent through the UART*/
	if(HAL_UART_Receive(huart,BLT_Linvor_RX,PIN_RESP_SIZE,BLT_LINVOR_TIMEOUT) == HAL_OK)
	{
	  /*Check if the response received is equal to the response expected*/
	  if(Compare_Array(BLT_Linvor_RX,PIN_RESP_OK,PIN_RESP_SIZE)  == SUCCESS)
	  {
	    return BLT_LINVOR_SUCCESS;
	  }
	}
  }
  for(for_var = 0;  for_var < PIN_MAX_SIZE; for_var++)
  {
    blt_linvor_struct->Pin[for_var] = '-';
  }

  return BLT_LINVOR_ERROR;
}


/**
   * @brief This function sends a command to set the baud rate of the module.
   *
   * @param     huart : pointer to a UART_HandleTypeDef structure that contains
   *            the configuration information for the specified UART module.
   *
   * @param     blt_linvor_struct : pointer to a BLT_Linvor_TypeDef structure that contains
   *            the baud rate for the specified bluetooth module.
   *
   * @retval    BLT_LINVOR_SUCCESS : The baud rate was set
   * @retval    BLT_LINVOR_ERROR   : The  baud rate wasn't set
   *
   * @attention THIS FUNCTION MUST ONLY BE CALLED WHEN THE MODULE ISN'T CONNECTED TO
   * 		    A DEVICE OTHERWISE THE (AT) COMMAND IS SENT DIRECTLY TO THE DEVICE.
   */

BLT_Linvor_ErrorStatus BLT_Linvor_Set_BaudRate( UART_HandleTypeDef *huart, BLT_Linvor_TypeDef *blt_linvor_struct, BLT_Linvor_BR_TypeDef baudrate)
{

  uint8_t br_receive_size = 0;
  uint32_t br_mcu_driver = 0;
  /* Set the AT command to get the version the module : AT+BAUDx*/
  BLT_Linvor_TX[0] = 'A';
  BLT_Linvor_TX[1] = 'T';
  BLT_Linvor_TX[2] = '+';
  BLT_Linvor_TX[3] = 'B';
  BLT_Linvor_TX[4] = 'A';
  BLT_Linvor_TX[5] = 'U';
  BLT_Linvor_TX[6] = 'D';

  switch (baudrate)
  {
	case BR_1200:
		br_receive_size = 6;
		br_mcu_driver = 1200;
		BLT_Linvor_TX[7] = '1';
		break;
	case BR_2400:
		br_receive_size = 6;
		br_mcu_driver = 2400;
		BLT_Linvor_TX[7] = '2';
		break;
	case BR_4800:
		br_receive_size = 6;
		br_mcu_driver = 4800;
		BLT_Linvor_TX[7] = '3';
		break;
	case BR_9600:
		br_receive_size = 6;
		br_mcu_driver = 9600;
		BLT_Linvor_TX[7] = '4';
		break;
	case BR_19200:
		br_receive_size = 7;
		br_mcu_driver = 19200;
		BLT_Linvor_TX[7] = '5';
		break;
	case BR_38400:
		br_receive_size = 7;
		br_mcu_driver = 38400;
		BLT_Linvor_TX[7] = '6';
		break;
	case BR_57600:
		br_receive_size = 7;
		br_mcu_driver = 57600;
		BLT_Linvor_TX[7] = '7';
		break;
	case BR_115200:
		br_receive_size = 8;
		br_mcu_driver = 115200;
		BLT_Linvor_TX[7] = '8';
		break;
	default:
		return BLT_LINVOR_ERROR;
		break;
  }

  /*Send AT+BAUDx, where x is the baud rate to be set in the module.
   * The command in sent in polling mode through the UART*/
   if(HAL_UART_Transmit(huart,BLT_Linvor_TX,BR_SEND_SIZE,BLT_LINVOR_TIMEOUT) == HAL_OK)
   {
	 /* change the baud rate of the microcontroller's uart*/
	  huart->Init.BaudRate = br_mcu_driver;
	  HAL_UART_Init(huart);
     /*wait the response in polling mode of the AT command sent through the UART*/
 	if(HAL_UART_Receive(huart,BLT_Linvor_RX,br_receive_size,BLT_LINVOR_TIMEOUT) == HAL_OK)
 	{
 		 blt_linvor_struct->BaudRate = baudrate;
 		 return BLT_LINVOR_SUCCESS;
 	}
   }

  blt_linvor_struct->BaudRate = -1;
  return BLT_LINVOR_ERROR;
}




ErrorStatus Compare_Array(uint8_t *array1, uint8_t *array2, uint8_t size)
{
	uint8_t temp_count = 0;
	for(; temp_count < size; temp_count++)
	{
		if(*(array1++) != *(array2++))
			return ERROR;
	}

	return SUCCESS;
}



