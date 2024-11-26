#ifndef __TIMER_H__
#define __TIMER_H__

#include <inttypes.h>

extern void mon_traitant(void);

void affiche_time(char*);
void trap_handler();
void init_traitant_timer(void (*traitant)(void));
void enable_timer();
void enble_it();
uint32_t nbr_secondes(void);

#endif
