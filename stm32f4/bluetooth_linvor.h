/**
 * @file bluetooth_linvor.h
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



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BLUETOOTH_LINVOR_H
#define _BLUETOOTH_LINVOR_H

#include <string.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_usart.h"
#include "stm32f4xx_hal_uart.h"


/** @defgroup Bluetooth_Linvor_Library
  * @{
  */

/** @defgroup Macros
  * @{
  */

/** @defgroup Private_Macros
  * @{
  */

/**
 * @}
 */


/** @defgroup Exported_Macros
  * @{
  */


#define BLT_LINVOR_TIMEOUT 2000         /**< Timeout utilized in the UART communication	*/


#define VERSION_SEND_SIZE  10           /**< Quantity of bytes sent in the AT+VERSION command */
#define VERSION_RESP_SIZE  12           /**< Quantity of bytes that is expected to be received as response to AT+VERSION command */
#define VERSION_SIZE       4            /**< Quantity of bytes representing the version of the module */

#define NAME_SEND_SIZE     7            /**< Quantity of bytes sent in the AT+Name command */
#define NAME_RESP_SIZE     9            /**< Quantity of bytes that is expected to be received as response to AT+NAME command */
#define NAME_RESP_OK       "OKsetname"  /**< Expected response to AT+NAME command */
#define NAME_MAX_SIZE      10           /**< Maximum size in bytes of the name of the BLT_Linvor module */


#define PIN_SEND_SIZE      10           /**< Quantity of bytes sent in the AT+PINxxx command */
#define PIN_RESP_SIZE      8            /**< Quantity of bytes that is expected to be received as response to AT+PINxxx command */
#define PIN_RESP_OK        "OKsetPIN"   /**< Expected response to AT+PINxxxx command */
#define PIN_MAX_SIZE       4            /**< Maximum size in bytes of the PIn code of the BLT_Linvor module */


#define BR_SEND_SIZE  8        			/**< Quantity of bytes sent in the AT+BAUDx command*/


/**
 * @}
 */


/**
 * @}
 */


/** @defgroup Typedefs
  * @{
  */



/** @defgroup Private_Typedefs
  * @{
  */


/**
 * Utilized as return parameter of functions
 */
typedef enum
{
  BLT_LINVOR_ERROR = 0,   /*!< Indicate a <b>Error</b> when returned by a function*/
  BLT_LINVOR_SUCCESS = ! BLT_LINVOR_ERROR /*!< Indicate a <b>Success</b> when returned by a function*/
} BLT_Linvor_ErrorStatus;

/**
 * Different baud rates that we can use in the communication.
 */
typedef enum
{
	BR_1200 = 0x01,     /*!< 1200   bits/s */
	BR_2400 = 0x02,	    /*!< 2400   bits/s */
	BR_4800 = 0x03,     /*!< 4800   bits/s */
	BR_9600 = 0x04,     /*!< 9600   bits/s */
	BR_19200 = 0x05,    /*!< 19200  bits/s */
	BR_38400 = 0x06,    /*!< 38400  bits/s */
	BR_57600 = 0x07,    /*!< 57600  bits/s */
	BR_115200 = 0x08    /*!< 115200 bits/s */

}BLT_Linvor_BR_TypeDef;

/**
 * @brief Holds configuration's parameters
 */
typedef struct
{
	 char Version[4];  /*!< Holds the version of the module */
	 char Name[10];    /*!< Holds the name of the module */
	 uint8_t Pin[4];   /*!< Holds the PIN code of the module */
	 int8_t BaudRate;  /*!< Holds the baud rate of the module */

}BLT_Linvor_TypeDef;


/**
 * @}
 */


/** @defgroup Exported_Typedefs
  * @{
  */


/**
 * @}
 */


/**
 * @}
 */


/** @defgroup Variables
  * @{
  */


/** @defgroup Private_Variables
  * @{
  */

uint8_t BLT_Linvor_TX[20]; /*!< Transmitter buffer of the BLT_Linvor */
uint8_t BLT_Linvor_RX[20]; /*!< Received buffer of the BLT_Linvor */

/**
 * @}
 */

/** @defgroup Exported_Variables
  * @{
  */

/**
 * @}
 */


/**
 * @}
 */



/** @defgroup Functions
  * @{
  */


/** @defgroup Exported_Functions
  * @{
  */

BLT_Linvor_ErrorStatus BLT_Get_Version( UART_HandleTypeDef *huart, BLT_Linvor_TypeDef *blt_linvor_struct);

BLT_Linvor_ErrorStatus BLT_Linvor_Set_Name( UART_HandleTypeDef *huart, BLT_Linvor_TypeDef *blt_linvor_struct, uint8_t size_name);

BLT_Linvor_ErrorStatus BLT_Linvor_Set_Pin( UART_HandleTypeDef *huart, BLT_Linvor_TypeDef *blt_linvor_struct);

BLT_Linvor_ErrorStatus BLT_Linvor_Set_BaudRate( UART_HandleTypeDef *huart, BLT_Linvor_TypeDef *blt_linvor_struct, BLT_Linvor_BR_TypeDef baudrate);


/**
 * @}
 */

/** @defgroup Private_Functions
  * @{
  */

ErrorStatus Compare_Array(uint8_t *array1, uint8_t *array2, uint8_t size);
/**
 * @}
 */

/**
 * @}
 */


/**
 * @}
 */


#endif /* _BLEUTOOTH_LINVOR_H */
