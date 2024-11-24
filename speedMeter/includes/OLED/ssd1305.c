/*****************************************************************************
* | File      	:   ssd1305.c
* | Author      :   Waveshare team
* | Function    :   2.23inch OLED HAT Drive function
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2023-12-20
* | Info        :
* -----------------------------------------------------------------------------
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "ssd1305.h"

unsigned char buffer[WIDTH * HEIGHT / 8];
#define BLACK 0
#define WHITE 1

void command(uint8_t cmd){
   #if USE_SPI
	OLED_DC_0;
    // OLED_CS_0;
    DEV_SPI_WriteByte(cmd);
    // OLED_CS_1;
#elif USE_IIC
    I2C_Write_Byte(cmd,IIC_CMD);
#endif
}

void data(uint8_t Data)
{
	#if USE_SPI
		OLED_DC_1;
		DEV_SPI_WriteByte(Data);
	#elif USE_IIC
		I2C_Write_Byte(Data,IIC_RAM);
	#endif
}
void SSD1305_begin()
{

	OLED_RST_1;
    DEV_Delay_ms(100);
    OLED_RST_0;
    DEV_Delay_ms(100);
    OLED_RST_1;
    DEV_Delay_ms(100);

    command(0xAE);//--turn off oled panel
	command(0x04);//--Set Lower Column Start Address for Page Addressing Mode
	command(0x10);//--Set Higher Column Start Address for Page Addressing Mode
	command(0x40);//---Set Display Start Line
	command(0x81);//---Set Contrast Control for BANK0
	command(0x80);//--Contrast control register is set
	command(0xA1);//--Set Segment Re-map
	command(0xA6);//--Set Normal/Inverse Display
	command(0xA8);//--Set Multiplex Ratio
	command(0x1F);
	command(0xC8);//--Set COM Output Scan Direction
	command(0xD3);//--Set Display Offset
	command(0x00);
	command(0xD5);//--Set Display Clock Divide Ratio/ Oscillator Frequency
	command(0xF0);
	command(0xD8);//--Set Area Color Mode ON/OFF & Low Power Display Mode
	command(0x05);
	command(0xD9);//--Set pre-charge period
	command(0xC2);
	command(0xDA);//--Set COM Pins Hardware Configuration
	command(0x12);
	command(0xDB);//--Set VCOMH Deselect Level
	command(0x3C);//--Set VCOM Deselect Level
	command(0xAF);//--Normal Brightness Display ON
}
void SSD1305_clear()
{
	int i;
	for(i = 0;i<sizeof(buffer);i++)
	{
		buffer[i] = 0;
	}
}
void SSD1305_pixel(int x, int y, char color)
{
    if(x > WIDTH || y > HEIGHT)return ;
    if(color)
        buffer[x+(y/8)*WIDTH] |= 1<<(y%8);
    else
        buffer[x+(y/8)*WIDTH] &= ~(1<<(y%8));
}
void SSD1305_char1616(unsigned char x,unsigned char y,unsigned char charAscii)
{
	unsigned char i, j;
	unsigned char charPixel = 0, y0 = y, pixelColor = BLACK;

	for (i = 0; i < 32; i ++) {
		charPixel = Font1612[charAscii - 0x30][i];
		for (j = 0; j < 8; j ++) {
			pixelColor = charPixel & 0x80? WHITE : BLACK;
			SSD1305_pixel(x, y, pixelColor);
			charPixel <<= 1;
			y ++;
			if ((y - y0) == 16) {
				y = y0;
				x ++;
				break;
			}
		}
	}
}

void SSD1305_char3216(unsigned char x,unsigned char y,unsigned char charAscii)
{
	unsigned char i, j;
	unsigned char chTemp = 0, y0 = y, chMode = 0;

	for (i = 0; i < 64; i ++) {
		chTemp = Font3216[charAscii - 0x30][i];
		for (j = 0; j < 8; j ++) {
			chMode = chTemp & 0x80? 1 : 0;
			SSD1305_pixel(x, y, chMode);
			chTemp <<= 1;
			y ++;
			if ((y - y0) == 32) {
				y = y0;
				x ++;
				break;
			}
		}
	}
}
void SSD1305_char(unsigned char x,unsigned char y,char acsii,char size,char mode)
{
	unsigned char i,j,y0=y;
	char temp;
	unsigned char ch = acsii - ' ';
	for(i = 0;i<size;i++)
	{
		if(size == 12)
		{
			if(mode)temp=Font1206[ch][i];
			else temp = ~Font1206[ch][i];
		}
		else
		{
			if(mode)temp=Font1608[ch][i];
			else temp = ~Font1608[ch][i];
		}
		for(j =0;j<8;j++)
		{
			if(temp & 0x80) SSD1305_pixel(x,y,1);
			else SSD1305_pixel(x,y,0);
			temp <<=1;
			y++;
			if((y-y0)==size)
			{
				y = y0;
				x ++;
				break;
			}
		}
	}
}
void SSD1305_string(unsigned char x,unsigned char y, const char *pString,
					unsigned char Size,unsigned char Mode)
{
    while (*pString != '\0') {
        if (x > (WIDTH - Size / 2)) {
			x = 0;
			y += Size;
			if (y > (HEIGHT - Size)) {
				y = x = 0;
			}
		}

        SSD1305_char(x, y, *pString, Size, Mode);
        x += Size / 2;
        pString ++;
    }
}

void SSD1305_bitmap(unsigned char x,unsigned char y,const unsigned char *pBmp,
					unsigned char chWidth,unsigned char chHeight)
{
	unsigned char i, j, byteWidth = (chWidth + 7)/8;
	for(j = 0; j < chHeight; j++){
		for(i = 0;i <chWidth;i ++){
			if(*(pBmp + j*byteWidth+i/8) & (128 >> (i & 7))){
				SSD1305_pixel(x + i, y + j, 1);
			}
		}
	}
}

void SSD1305_display()
{
    UWORD page, column;
    for (page = 0; page < (HEIGHT / 8); page++) {
        /* set page address */
        command(0xB0 + page);
        /* set low column address */
        command(0x04);
        /* set high column address */
        command(0x10);
        /* write data */
		for(column=0; column< WIDTH; column++) {
            data(buffer[page * WIDTH + column]);
        }
    }
}
