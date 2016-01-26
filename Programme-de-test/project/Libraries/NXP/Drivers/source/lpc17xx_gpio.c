/**
 * @file	: lpc17xx_gpio.c
 * @brief	: Contains all functions support for GPIO firmware library on LPC17xx
 * @version	: 1.0
 * @date	: 11. Jun. 2009
 * @author	: HieuNguyen
 **************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup GPIO
 * @{
 */

/* Includes ------------------------------------------------------------------- */
#include "lpc17xx_gpio.h"

/* If this source file built with example, the LPC17xx FW library configuration
 * file in each example directory ("lpc17xx_libcfg.h") must be included,
 * otherwise the default FW library configuration file must be included instead
 */
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc17xx_libcfg.h"
#else
#include "lpc17xx_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */


#ifdef _GPIO

/* Private Functions ---------------------------------------------------------- */
/** @addtogroup GPIO_Private_Functions
 * @{
 */
/*********************************************************************//**
 * @brief		Get pointer to GPIO peripheral due to GPIO port
 * @param[in]	portNum		Port Number value, should be in range from 0 to 4.
 * @return		Pointer to GPIO peripheral
 **********************************************************************/
static LPC_GPIO_TypeDef *GPIO_GetPointer(uint8_t portNum)
{
	LPC_GPIO_TypeDef *pGPIO = NULL;

	switch (portNum) {
	case 0:
		pGPIO = LPC_GPIO0;
		break;
	case 1:
		pGPIO = LPC_GPIO1;
		break;
	case 2:
		pGPIO = LPC_GPIO2;
		break;
	case 3:
		pGPIO = LPC_GPIO3;
		break;
	case 4:
		pGPIO = LPC_GPIO4;
		break;
	default:
		break;
	}

	return pGPIO;
}

/*********************************************************************//**
 * @brief		Get pointer to FIO peripheral in halfword accessible style
 * 				due to FIO port
 * @param[in]	portNum		Port Number value, should be in range from 0 to 4.
 * @return		Pointer to FIO peripheral
 **********************************************************************/
static GPIO_HalfWord_TypeDef *FIO_HalfWordGetPointer(uint8_t portNum)
{
	GPIO_HalfWord_TypeDef *pFIO = NULL;

	switch (portNum) {
	case 0:
		pFIO = GPIO0_HalfWord;
		break;
	case 1:
		pFIO = GPIO1_HalfWord;
		break;
	case 2:
		pFIO = GPIO2_HalfWord;
		break;
	case 3:
		pFIO = GPIO3_HalfWord;
		break;
	case 4:
		pFIO = GPIO4_HalfWord;
		break;
	default:
		break;
	}

	return pFIO;
}

/*********************************************************************//**
 * @brief		Get pointer to FIO peripheral in byte accessible style
 * 				due to FIO port
 * @param[in]	portNum		Port Number value, should be in range from 0 to 4.
 * @return		Pointer to FIO peripheral
 **********************************************************************/
static GPIO_Byte_TypeDef *FIO_ByteGetPointer(uint8_t portNum)
{
	GPIO_Byte_TypeDef *pFIO = NULL;

	switch (portNum) {
	case 0:
		pFIO = GPIO0_Byte;
		break;
	case 1:
		pFIO = GPIO1_Byte;
		break;
	case 2:
		pFIO = GPIO2_Byte;
		break;
	case 3:
		pFIO = GPIO3_Byte;
		break;
	case 4:
		pFIO = GPIO4_Byte;
		break;
	default:
		break;
	}

	return pFIO;
}

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup GPIO_Public_Functions
 * @{
 */


/* GPIO ------------------------------------------------------------------------------ */

/*********************************************************************//**
 * @brief		Set Direction for GPIO port.
 * @param[in]	portNum		Port Number value, should be in range from 0 to 4
 * @param[in]	bitValue	Value that contains all bits to set direction,
 * 							in range from 0 to 0xFFFFFFFF.
 * 							example: value 0x5 to set direction for bit 0 and bit 1.
 * @param[in]	dir			Direction value, should be:
 * 							- 0: Input.
 * 							- 1: Output.
 * @return		None
 *
 * Note: All remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void GPIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir)
{
	LPC_GPIO_TypeDef *pGPIO = GPIO_GetPointer(portNum);

	if (pGPIO != NULL) {
		// Enable Output
		if (dir) {
			pGPIO->FIODIR |= bitValue;
		}
		// Enable Input
		else {
			pGPIO->FIODIR &= ~bitValue;
		}
	}
}


/*********************************************************************//**
 * @brief		Set Value for bits that have output direction on GPIO port.
 * @param[in]	portNum		Port number value, should be in range from 0 to 4
 * @param[in]	bitValue	Value that contains all bits on GPIO to set,
 * 							in range from 0 to 0xFFFFFFFF.
 * 							example: value 0x5 to set bit 0 and bit 1.
 * @return		None
 *
 * Note:
 * - For all bits that has been set as input direction, this function will
 * not effect.
 * - For all remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void GPIO_SetValue(uint8_t portNum, uint32_t bitValue)
{
	LPC_GPIO_TypeDef *pGPIO = GPIO_GetPointer(portNum);

	if (pGPIO != NULL) {
		pGPIO->FIOSET = bitValue;
	}
}

/*********************************************************************//**
 * @brief		Clear Value for bits that have output direction on GPIO port.
 * @param[in]	portNum		Port number value, should be in range from 0 to 4
 * @param[in]	bitValue	Value that contains all bits on GPIO to clear,
 * 							in range from 0 to 0xFFFFFFFF.
 * 							example: value 0x5 to clear bit 0 and bit 1.
 * @return		None
 *
 * Note:
 * - For all bits that has been set as input direction, this function will
 * not effect.
 * - For all remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void GPIO_ClearValue(uint8_t portNum, uint32_t bitValue)
{
	LPC_GPIO_TypeDef *pGPIO = GPIO_GetPointer(portNum);

	if (pGPIO != NULL) {
		pGPIO->FIOCLR = bitValue;
	}
}

/*********************************************************************//**
 * @brief		Read Current state on port pin that have input direction of GPIO
 * @param[in]	portNum		Port number to read value, in range from 0 to 4
 * @return		Current value of GPIO port.
 *
 * Note: Return value contain state of each port pin (bit) on that GPIO regardless
 * its direction is input or output.
 **********************************************************************/
uint32_t GPIO_ReadValue(uint8_t portNum)
{
	LPC_GPIO_TypeDef *pGPIO = GPIO_GetPointer(portNum);

	if (pGPIO != NULL) {
		return pGPIO->FIOPIN;
	}

	return (0);
}

/* FIO word accessible ----------------------------------------------------------------- */
/* Stub function for FIO (word-accessible) style */

/**
 * @brief The same with GPIO_SetDir()
 */
void FIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir)
{
	GPIO_SetDir(portNum, bitValue, dir);
}

/**
 * @brief The same with GPIO_SetValue()
 */
void FIO_SetValue(uint8_t portNum, uint32_t bitValue)
{
	GPIO_SetValue(portNum, bitValue);
}

/**
 * @brief The same with GPIO_ClearValue()
 */
void FIO_ClearValue(uint8_t portNum, uint32_t bitValue)
{
	GPIO_ClearValue(portNum, bitValue);
}

/**
 * @brief The same with GPIO_ReadValue()
 */
uint32_t FIO_ReadValue(uint8_t portNum)
{
	return (GPIO_ReadValue(portNum));
}


/*********************************************************************//**
 * @brief		Set mask value for bits in FIO port
 * @param[in]	portNum		Port number, in range from 0 to 4
 * @param[in]	bitValue	Value that contains all bits in to set,
 * 							in range from 0 to 0xFFFFFFFF.
 * @param[in]	maskValue	Mask value contains state value for each bit:
 * 							- 0: not mask.
 * 							- 1: mask.
 * @return		None
 *
 * Note:
 * - All remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 * - After executing this function, in mask register, value '0' on each bit
 * enables an access to the corresponding physical pin via a read or write access,
 * while value '1' on bit (masked) that corresponding pin will not be changed
 * with write access and if read, will not be reflected in the updated pin.
 **********************************************************************/
void FIO_SetMask(uint8_t portNum, uint32_t bitValue, uint8_t maskValue)
{
	LPC_GPIO_TypeDef *pFIO = GPIO_GetPointer(portNum);
	if(pFIO != NULL) {
		// Mask
		if (maskValue){
			pFIO->FIOMASK |= bitValue;
		}
		// Un-mask
		else {
			pFIO->FIOMASK &= ~bitValue;
		}
	}
}


/* FIO halfword accessible ------------------------------------------------------------- */

/*********************************************************************//**
 * @brief		Set direction for FIO port in halfword accessible style
 * @param[in]	portNum		Port number, in range from 0 to 4
 * @param[in]	halfwordNum	HalfWord part number, should be 0 (lower) or 1(upper)
 * @param[in]	bitValue	Value that contains all bits in to set direction,
 * 							in range from 0 to 0xFFFF.
 * @param[in]	dir			Direction value, should be:
 * 							- 0: Input.
 * 							- 1: Output.
 * @return		None
 *
 * Note: All remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void FIO_HalfWordSetDir(uint8_t portNum, uint8_t halfwordNum, uint16_t bitValue, uint8_t dir)
{
	GPIO_HalfWord_TypeDef *pFIO = FIO_HalfWordGetPointer(portNum);
	if(pFIO != NULL) {
		// Output direction
		if (dir) {
			// Upper
			if(halfwordNum) {
				pFIO->FIODIRU |= bitValue;
			}
			// lower
			else {
				pFIO->FIODIRL |= bitValue;
			}
		}
		// Input direction
		else {
			// Upper
			if(halfwordNum) {
				pFIO->FIODIRU &= ~bitValue;
			}
			// lower
			else {
				pFIO->FIODIRL &= ~bitValue;
			}
		}
	}
}


/*********************************************************************//**
 * @brief		Set mask value for bits in FIO port in halfword accessible style
 * @param[in]	portNum		Port number, in range from 0 to 4
 * @param[in]	halfwordNum	HalfWord part number, should be 0 (lower) or 1(upper)
 * @param[in]	bitValue	Value that contains all bits in to set,
 * 							in range from 0 to 0xFFFF.
 * @param[in]	maskValue	Mask value contains state value for each bit:
 * 					- 0: not mask.
 * 					- 1: mask.
 * @return		None
 *
 * Note:
 * - All remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 * - After executing this function, in mask register, value '0' on each bit
 * enables an access to the corresponding physical pin via a read or write access,
 * while value '1' on bit (masked) that corresponding pin will not be changed
 * with write access and if read, will not be reflected in the updated pin.
 **********************************************************************/
void FIO_HalfWordSetMask(uint8_t portNum, uint8_t halfwordNum, uint16_t bitValue, uint8_t maskValue)
{
	GPIO_HalfWord_TypeDef *pFIO = FIO_HalfWordGetPointer(portNum);
	if(pFIO != NULL) {
		// Mask
		if (maskValue){
			// Upper
			if(halfwordNum) {
				pFIO->FIOMASKU |= bitValue;
			}
			// lower
			else {
				pFIO->FIOMASKL |= bitValue;
			}
		}
		// Un-mask
		else {
			// Upper
			if(halfwordNum) {
				pFIO->FIOMASKU &= ~bitValue;
			}
			// lower
			else {
				pFIO->FIOMASKL &= ~bitValue;
			}
		}
	}
}


/*********************************************************************//**
 * @brief		Set bits for FIO port in halfword accessible style
 * @param[in]	portNum		Port number, in range from 0 to 4
 * @param[in]	halfwordNum	HalfWord part number, should be 0 (lower) or 1(upper)
 * @param[in]	bitValue	Value that contains all bits in to set,
 * 							in range from 0 to 0xFFFF.
 * @return		None
 *
 * Note:
 * - For all bits that has been set as input direction, this function will
 * not effect.
 * - For all remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void FIO_HalfWordSetValue(uint8_t portNum, uint8_t halfwordNum, uint16_t bitValue)
{
	GPIO_HalfWord_TypeDef *pFIO = FIO_HalfWordGetPointer(portNum);
	if(pFIO != NULL) {
		// Upper
		if(halfwordNum) {
			pFIO->FIOSETU = bitValue;
		}
		// lower
		else {
			pFIO->FIOSETL = bitValue;
		}
	}
}


/*********************************************************************//**
 * @brief		Clear bits for FIO port in halfword accessible style
 * @param[in]	portNum		Port number, in range from 0 to 4
 * @param[in]	halfwordNum	HalfWord part number, should be 0 (lower) or 1(upper)
 * @param[in]	bitValue	Value that contains all bits in to clear,
 * 							in range from 0 to 0xFFFF.
 * @return		None
 *
 * Note:
 * - For all bits that has been set as input direction, this function will
 * not effect.
 * - For all remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void FIO_HalfWordClearValue(uint8_t portNum, uint8_t halfwordNum, uint16_t bitValue)
{
	GPIO_HalfWord_TypeDef *pFIO = FIO_HalfWordGetPointer(portNum);
	if(pFIO != NULL) {
		// Upper
		if(halfwordNum) {
			pFIO->FIOCLRU = bitValue;
		}
		// lower
		else {
			pFIO->FIOCLRL = bitValue;
		}
	}
}


/*********************************************************************//**
 * @brief		Read Current state on port pin that have input direction of GPIO
 * 				in halfword accessible style.
 * @param[in]	portNum		Port number, in range from 0 to 4
 * @param[in]	halfwordNum	HalfWord part number, should be 0 (lower) or 1(upper)
 * @return		Current value of FIO port pin of specified halfword.
 * Note: Return value contain state of each port pin (bit) on that FIO regardless
 * its direction is input or output.
 **********************************************************************/
uint16_t FIO_HalfWordReadValue(uint8_t portNum, uint8_t halfwordNum)
{
	GPIO_HalfWord_TypeDef *pFIO = FIO_HalfWordGetPointer(portNum);
	if(pFIO != NULL) {
		// Upper
		if(halfwordNum) {
			return (pFIO->FIOPINU);
		}
		// lower
		else {
			return (pFIO->FIOPINL);
		}
	}
	return (0);
}


/* FIO Byte accessible ------------------------------------------------------------ */

/*********************************************************************//**
 * @brief		Set direction for FIO port in byte accessible style
 * @param[in]	portNum		Port number, in range from 0 to 4
 * @param[in]	byteNum		Byte part number, should be in range from 0 to 3
 * @param[in]	bitValue	Value that contains all bits in to set direction,
 * 							in range from 0 to 0xFF.
 * @param[in]	dir			Direction value, should be:
 * 							- 0: Input.
 * 							- 1: Output.
 * @return		None
 *
 * Note: All remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void FIO_ByteSetDir(uint8_t portNum, uint8_t byteNum, uint8_t bitValue, uint8_t dir)
{
	GPIO_Byte_TypeDef *pFIO = FIO_ByteGetPointer(portNum);
	if(pFIO != NULL) {
		// Output direction
		if (dir) {
			//mthomas if ((byteNum >= 0) && (byteNum <= 3)) {
			if (byteNum <= 3) {
				pFIO->FIODIR[byteNum] |= bitValue;
			}
		}
		// Input direction
		else {
			// mthomas if ((byteNum >= 0) && (byteNum <= 3)) {
			if (byteNum <= 3) {
				pFIO->FIODIR[byteNum] &= ~bitValue;
			}
		}
	}
}

/*********************************************************************//**
 * @brief		Set mask value for bits in FIO port in byte accessible style
 * @param[in]	portNum		Port number, in range from 0 to 4
 * @param[in]	byteNum		Byte part number, should be in range from 0 to 3
 * @param[in]	bitValue	Value that contains all bits in to set mask,
 * 							in range from 0 to 0xFF.
 * @param[in]	maskValue	Mask value contains state value for each bit:
 * 							- 0: not mask.
 * 							- 1: mask.
 * @return		None
 *
 * Note:
 * - All remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 * - After executing this function, in mask register, value '0' on each bit
 * enables an access to the corresponding physical pin via a read or write access,
 * while value '1' on bit (masked) that corresponding pin will not be changed
 * with write access and if read, will not be reflected in the updated pin.
 **********************************************************************/
void FIO_ByteSetMask(uint8_t portNum, uint8_t byteNum, uint8_t bitValue, uint8_t maskValue)
{
	GPIO_Byte_TypeDef *pFIO = FIO_ByteGetPointer(portNum);
	if(pFIO != NULL) {
		// Mask
		if (maskValue) {
			// mthomas if ((byteNum >= 0) && (byteNum <= 3)) {
			if (byteNum <= 3) {
				pFIO->FIOMASK[byteNum] |= bitValue;
			}
		}
		// Un-mask
		else {
			// mthomas if ((byteNum >= 0) && (byteNum <= 3)) {
			if (byteNum <= 3) {
				pFIO->FIOMASK[byteNum] &= ~bitValue;
			}
		}
	}
}


/*********************************************************************//**
 * @brief		Set bits for FIO port in byte accessible style
 * @param[in]	portNum		Port number, in range from 0 to 4
 * @param[in]	byteNum		Byte part number, should be in range from 0 to 3
 * @param[in]	bitValue	Value that contains all bits in to set,
 * 							in range from 0 to 0xFF.
 * @return		None
 *
 * Note:
 * - For all bits that has been set as input direction, this function will
 * not effect.
 * - For all remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void FIO_ByteSetValue(uint8_t portNum, uint8_t byteNum, uint8_t bitValue)
{
	GPIO_Byte_TypeDef *pFIO = FIO_ByteGetPointer(portNum);
	if (pFIO != NULL) {
		// mthomas if ((byteNum >= 0) && (byteNum <= 3)) {
		if (byteNum <= 3) {
			pFIO->FIOSET[byteNum] = bitValue;
		}
	}
}


/*********************************************************************//**
 * @brief		Clear bits for FIO port in byte accessible style
 * @param[in]	portNum		Port number, in range from 0 to 4
 * @param[in]	byteNum		Byte part number, should be in range from 0 to 3
 * @param[in]	bitValue	Value that contains all bits in to clear,
 * 							in range from 0 to 0xFF.
 * @return		None
 *
 * Note:
 * - For all bits that has been set as input direction, this function will
 * not effect.
 * - For all remaining bits that are not activated in bitValue (value '0')
 * will not be effected by this function.
 **********************************************************************/
void FIO_ByteClearValue(uint8_t portNum, uint8_t byteNum, uint8_t bitValue)
{
	GPIO_Byte_TypeDef *pFIO = FIO_ByteGetPointer(portNum);
	if (pFIO != NULL) {
		// mthomas if ((byteNum >= 0) && (byteNum <= 3)) {
		if (byteNum <= 3) {
			pFIO->FIOCLR[byteNum] = bitValue;
		}
	}
}


/*********************************************************************//**
 * @brief		Read Current state on port pin that have input direction of GPIO
 * 				in byte accessible style.
 * @param[in]	portNum		Port number, in range from 0 to 4
 * @param[in]	byteNum		Byte part number, should be in range from 0 to 3
 * @return		Current value of FIO port pin of specified byte part.
 * Note: Return value contain state of each port pin (bit) on that FIO regardless
 * its direction is input or output.
 **********************************************************************/
uint8_t FIO_ByteReadValue(uint8_t portNum, uint8_t byteNum)
{
	GPIO_Byte_TypeDef *pFIO = FIO_ByteGetPointer(portNum);
	if (pFIO != NULL) {
		// mthomas if ((byteNum >= 0) && (byteNum <= 3)) {
		if (byteNum <= 3) {
			return (pFIO->FIOPIN[byteNum]);
		}
	}
	return (0);
}

/**
 * @}
 */

#endif /* _GPIO */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
