/***********************************************************/
/* Author    : Mohamed Ashraf                                 */
/* Date      : 25 may 2021                                 */
/* Version   : V01                                         */
/***********************************************************/
#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H

#define black   0x00
#define white   0xffff
#define red     0xF800
#define blue    0x1f
#define green   0x7e0

void HTFT_voidInitialize   (void);
void HTFT_voidDisplayImage (const u16* Copy_Image);
void HTFT_voidFillColor (u16 Copy_u16Color);
void HTFT_voidDrawChar (u8 Copy_u8Char, u16 Copy_u16Color, u8 Copy_u8Line, u8 Copy_u8Space);


#endif
