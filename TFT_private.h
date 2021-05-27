/***********************************************************/
/* Author    : Mohamed Ashraf                                 */
/* Date      : 25 may 2021                                 */
/* Version   : V01                                         */
/***********************************************************/
#ifndef TFT_PRIVATE_H
#define TFT_PRIVATE_H

// tft commands
#define memoryWrite         0x2c
#define setRowAddress       0x2b
#define seColumonAddress    0x2a
#define sleepOut            0x11
#define sleepIn             0x10
#define displayOn           0x29
#define displayOff          0x28


static void voidWriteCommand(u8 Copy_u8Command);
static void voidWriteData   (u8 Copy_u8Data);
static void voidWriteu16Data   (u16 Copy_u16Data);
static void voidDrawfont16x16Char (u8 Copy_u8Char, u16 Copy_u16Color);


#endif