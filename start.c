#include <inttypes.h>
#include <stdio.h>
#include <cpu.h>
#include "console.h"
#include "timer.h"
#include "processus.h"

void wait(uint32_t seconds) {
    volatile uint32_t ticks = seconds * 100000000;
    while (ticks--) {
        __asm__ volatile("nop");
    }
}

void print_with_delay(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        printf("%c", c);

        if (c == '\n' || c == '\t' || c == '\b' || c == '\r') {
            wait(1);
        }
    }
}

void kernel_start(void) {

    //enable_it();
    init_traitant_timer(mon_traitant);
    enable_timer();
    //disable_it();

    efface_ecran();

    // Initialize process
    init_processus();
    int32_t pid = mon_pid();
    char *nom = mon_nom();
    printf("Processus actif PID: %d\n", pid);
    printf("Process actif nom: %s\n\n", nom);

    printf("creation de proc1\n");
    pid = cree_processus(proc1, "proc1");
    printf("Processus actif PID: %d\n\n", pid);
    
    printf("creation de proc2\n");
    pid = cree_processus(proc2, "proc2");
    printf("Processus actif PID: %d\n\n", pid);

    printf("creation de proc3\n");
    pid = cree_processus(proc3, "proc3");
    printf("Processus actif PID: %d\n\n", pid);

    idle();

    printf("Tests Done\n");

}
