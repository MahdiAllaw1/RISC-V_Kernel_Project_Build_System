#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <inttypes.h>
#include <stdio.h>
#include "font.h"
#include <string.h>
#include <cpu.h>
/*
 * This is the function called by printf to send its output to the screen. You
 * have to implement it in the kernel and in the user program.
 */
extern void console_putbytes(const char *s, int len);

void pixel (uint32_t, uint32_t, uint32_t);
void ecrit_car(uint32_t lig, uint32_t col, char c);
void efface_ecran(void);
void place_curseur(uint32_t , uint32_t );
void efface_curseur(uint32_t , uint32_t );
void defilement(void);
void traite_car(char );

#endif

