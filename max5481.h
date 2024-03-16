// @File		MAX5481.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		16/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//

#ifndef MAX5481_H
#define MAX5481_H

#define MAX5481_SCK PORTCbits.RC0
#define MAX5481_DIN PORTCbits.RC1
#define MAX5481_CS PORTCbits.RC3

#define MAX5481_SCK_TRIS TRISCbits.RC0
#define MAX5481_DIN_TRIS TRISCbits.RC1
#define MAX5481_CS_TRIS TRISCbits.RC3

static void SPI_transfer(unsigned int data)
{     
    for(unsigned long mask = 0x800000; mask; mask >>= 1)
    {
        if(data & mask) MAX5481_DIN = 1; else MAX5481_DIN = 0;
            
         __asm__ __volatile__("nop");
         MAX5481_SCK = 1;
         __asm__ __volatile__("nop");
         MAX5481_SCK = 0;
         __asm__ __volatile__("nop");    
    }
}

// C0: BIT20, C1: BIT21
void MAX5481_Write(unsigned char c0, unsigned char c1, unsigned long value)
{    
    value <<= 7;
    value |= (unsigned long)((c0<<20)|(c1<<21));
    
    MAX5481_CS = 0;
    SPI_transfer(value);
    MAX5481_CS = 1;
}

void MAX5481_Init(void)
{
    MAX5481_SCK_TRIS = 0;
    MAX5481_DIN_TRIS = 0;
    MAX5481_CS_TRIS = 0;
    
    MAX5481_CS = 1;
}

#endif 