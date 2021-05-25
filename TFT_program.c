/***********************************************************/
/* Author    : Mohamed Ashraf                                 */
/* Date      : 25 may 2021                                 */
/* Version   : V01                                         */
/***********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "SPI_interface.h"
#include "STK_interface.h"

#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"

void HTFT_voidInitialize   (void)
{
	/* Reset Pulse */
	MGPIO_VidSetPinValue(TFT_RST_PIN,HIGH);
	MSTK_voidSetBusyWait(100);
	MGPIO_VidSetPinValue(TFT_RST_PIN,LOW);
	MSTK_voidSetBusyWait(1);
	MGPIO_VidSetPinValue(TFT_RST_PIN,HIGH);
	MSTK_voidSetBusyWait(100);
	MGPIO_VidSetPinValue(TFT_RST_PIN,LOW);
	MSTK_voidSetBusyWait(100);
	MGPIO_VidSetPinValue(TFT_RST_PIN,HIGH);
	MSTK_voidSetBusyWait(120000);
	
	/* Sleep Out Command */
	voidWriteCommand(0x11);
	
	/* Wait 150 ms */
	MSTK_voidSetBusyWait(150000);
	
	/* Color Mode Command */
	voidWriteCommand(0x3A);
	voidWriteData   (0x05);
	
	/* Display On Command */
	voidWriteCommand(0x29);
}


void HTFT_voidDisplayImage (const u16* Copy_Image)
{
	u16 counter;
	u8 Data;

	/* Set X Address */
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(127);
	
	/* Set Y Address */
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(159);

	/* RAM Write */
	voidWriteCommand(0x2C);

	for(counter = 0; counter< 20480;counter++)
	{
		Data = Copy_Image[counter] >> 8;

		/* Write the high byte */
		voidWriteData(Data);
		/* Write the low byte */
		Data = Copy_Image[counter] & 0x00ff;
		voidWriteData(Data);
	}


}

static void voidWriteCommand(u8 Copy_u8Command)
{
	u8 Local_u8Temp;
	
	/* Set A0 Pin to Low */
	MGPIO_VidSetPinValue(TFT_A0_PIN,LOW);
	
	/* Send Command over SPI */
	MSPI1_voidSendReceiveSynch(Copy_u8Command,&Local_u8Temp);
}

static void voidWriteu16Data   (u16 Copy_u16Data)
{

	u16 Data;
	Data = Copy_u16Data >> 8;

	/* Write the high byte */
	voidWriteData(Data);
	/* Write the low byte */
	Data = Copy_u16Data & 0x00ff;
	voidWriteData(Data);

}

static void voidWriteData   (u8 Copy_u8Data)
{
	u8 Local_u8Temp;
	
	/* Set A0 Pin to High to send data */
	MGPIO_VidSetPinValue(TFT_A0_PIN,HIGH);
	
	/* Send data over SPI */
	MSPI1_voidSendReceiveSynch(Copy_u8Data,&Local_u8Temp);
}



void HTFT_voidFillColor (u16 Copy_u16Color)
{
	u16 counter;

	/* Set X Address */
	voidWriteCommand(seColumonAddress);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(127);

	/* Set Y Address */
	voidWriteCommand(setRowAddress);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(159);

	/* RAM Write */
	voidWriteCommand(0x2C);

	for(counter = 0; counter< 20480;counter++)
	{
		voidWriteu16Data(Copy_u16Color);
	}


}


void HTFT_voidDrawChar (u16* Copy_u16Char, u16 Copy_u16Color, u8 Copy_u8Line, u8 Copy_u8Space)
{

	u8 xStart = Copy_u8Space*16;
	u8 xEnd   = xStart+15;

	u8 yStart = Copy_u8Line*16;
	u8 yEnd   = yStart+15;


	/* Set X Address */
	voidWriteCommand(seColumonAddress);
	voidWriteData(0);
	voidWriteData(xStart);
	voidWriteData(0);
	voidWriteData(xEnd);

	/* Set Y Address */
	voidWriteCommand(setRowAddress);
	voidWriteData(0);
	voidWriteData(yStart);
	voidWriteData(0);
	voidWriteData(yEnd);

	/* RAM Write */
	voidWriteCommand(memoryWrite);






	for(u8 i=0 ; i<16 ; i++)
	{
		for(u8 j=0 ; j<16 ; j++)
		{
			// draw colomuns starts from bottom
			if( (Copy_u16Char[15-i]>>j) & 0x01 ){
				voidWriteu16Data(Copy_u16Color);
			}
			else{
				voidWriteu16Data(black);
			}

		}

	}




}
