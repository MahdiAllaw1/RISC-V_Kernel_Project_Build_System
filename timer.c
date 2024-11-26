#include "timer.h"
#include "processus.h"
#include "console.h"
#include "font.h"
#include <string.h>

#define CLINT_TIMER (( uint64_t *)0x0200bff8)
#define CLINT_TIMER_CMP ((uint64_t *)0x02004000)
#define TIMER_FREQ 10000000
#define IT_FREQ 20
uint32_t seconds = 0;
uint64_t nb_ticks = 0;
uint32_t col_timer;


void affiche_time(char *s){
        col_timer = 160-strlen(s);
        for (size_t i = 0; i < strlen(s); i++,col_timer++) {
            char c = s[i];
            int8_t* carac = (int8_t*) font8x8_basic[(int)c];
            char allume;
            for (int i=0; i<8; i++){
                int8_t line = carac[i];
                for (int j=0; j<8; j++){
                    allume = (line >> j) & 1;
                    if (allume == 1) {
                        pixel(i ,(col_timer*8)+j ,0xffffff);
                    }
                    else {
                        pixel(i , (col_timer*8)+j ,0x000000);
                    }
                }
            }
        }
}

void trap_handler(uint64_t mcause){
    uint64_t val;
    char s[8];

    __asm__("csrr %0, mcause": "=r"(val));
    if ((mcause & 0x7FFFFFFFFFFFFFFF) == 7) {
        nb_ticks++;
        val = *CLINT_TIMER;
        val = val + (TIMER_FREQ/IT_FREQ);
        *CLINT_TIMER_CMP = val;
        ordonnance();
    }

    seconds = nbr_secondes();
    sprintf(s,"%d:%d:%d", (seconds/3600),((seconds % 3600)/60),(seconds % 60));
    affiche_time(s);
}

void init_traitant_timer(void (*traitant)(void)){
    __asm__("csrw mtvec, %0":: "r"((uint64_t) traitant));
}

void enable_timer(){
    uint64_t val;
    __asm__("csrr %0, mie": "=r"(val));
    val |= 1 << 7;
    __asm__("csrw mie, %0":: "r"(val));

    val = *CLINT_TIMER;
    val = val + (TIMER_FREQ/IT_FREQ);
    *CLINT_TIMER_CMP = val;
}

uint32_t nbr_secondes(void){
    return (uint32_t)(nb_ticks/20);
}
