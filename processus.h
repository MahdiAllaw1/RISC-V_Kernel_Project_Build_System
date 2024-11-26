#ifndef __PROCESSUS_H__
#define __PROCESSUS_H__

#include <inttypes.h>
#include "timer.h"

extern void ctx_sw(uint64_t *old, uint64_t *new);

typedef struct {
    int32_t pid;
    char name[60];
    int etat;         // un processus peut être élu (en train d'exécuter), activable (prêt à être élu), endormi pour une durée donnée
    uint32_t temps_reveil;
    uint64_t REG[17];
    int pile[4096];
} Process;

void init_processus(void);
void ordonnance(void);
int32_t cree_processus(void (*)(void), char *);
void dors(uint32_t );
void idle(void);
void proc1(void);
void proc2(void);
void proc3(void);
int32_t mon_pid(void);
char *mon_nom(void);
void affiche_etats(void);

#endif
