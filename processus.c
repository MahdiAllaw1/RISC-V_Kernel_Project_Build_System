#include "processus.h"
#include "console.h"
#include <string.h>

#define MAX_PROCESSES 4
#define ACTIVABLE 1
#define ELU 2
#define ENDORMI 3
#define MORT 4


Process processes[MAX_PROCESSES];
Process *actif = NULL;
int next_pid = 0;

void init_processus(void){
    memset(processes, 0, sizeof(processes));

    processes[0].pid = 0;
    strcpy(processes[0].name, "idle");
    processes[0].etat = ELU;

    actif = &processes[0];
    next_pid = 1;
}

// la vraie vie, où idle n'est exécuté que lorsqu'aucun autre processus est disponible
void ordonnance(void){
    Process *suivant = NULL;

    for (int i = 1; i < MAX_PROCESSES; i++) {
        if (processes[i].etat == ENDORMI && processes[i].temps_reveil <= nbr_secondes() && processes[i].etat != MORT) {
            processes[i].etat = ACTIVABLE;
        }
    }

    for (int i = actif->pid + 1; i < MAX_PROCESSES; i++){
        if (processes[i].etat == ACTIVABLE){
            suivant = &processes[i];
            break;
        }
    }

    if (suivant == NULL){
        for (int i = 0; i < actif->pid; i++){
            if (processes[i].etat == ACTIVABLE){
                suivant = &processes[i];
                break;
            }
        }
    }

    if (suivant != NULL && suivant != actif && suivant->etat != ENDORMI && suivant->etat != MORT){

        if(actif->etat != ENDORMI && actif->etat != MORT){
            actif->etat = ACTIVABLE;
        }
        suivant->etat = ELU;
        Process *active = actif;
        actif = suivant;
        // le problem c'est ici il faut que fait le actif = suivant
        affiche_etats();
        ctx_sw(active->REG, suivant->REG);
    }
}

int32_t cree_processus(void (*code)(void), char *nom){
    if (next_pid < MAX_PROCESSES) {
        Process *new_proc = &processes[next_pid];
        new_proc->pid = next_pid;
        strcpy(new_proc->name, nom);
        new_proc->etat = ACTIVABLE;
        next_pid++;
        new_proc->REG[0] = (uint64_t)code;
        new_proc->REG[1] = (uint64_t)(new_proc->pile + sizeof(new_proc->pile) - 1);
        return new_proc->pid;
    }
    else return -1;
}

void dors(uint32_t nbr_secs){
    //printf("dors: l'actid c'est %s\n", actif->name);
    actif->etat = ENDORMI;
    actif->temps_reveil = nbr_secondes() + nbr_secs;
    ordonnance();
}

void fin_processus(void){
    actif->etat = MORT;
    ordonnance();
}

void idle(void)
{
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid()); 
        enable_it();
        hlt();
        disable_it();
    }
    printf("[idle] je termine\n");
}

void proc1(void) {
    for (int32_t i = 0; i < 2; i++){
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        dors(5);
    }
    fin_processus();
}

void proc2(void) {
    for (int32_t i = 0; i < 2; i++){
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        dors(7);
    }
    fin_processus();
}

void proc3(void) {
    for (int32_t i = 0; i < 2; i++){
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        dors(10);
    }
    fin_processus();
}

int32_t mon_pid(void){
    return actif->pid;
}

char *mon_nom(void){
    return actif->name;
}

void affiche_etats(void){
    char etats[50] = "";
    for (int i = 0; i < MAX_PROCESSES; i++) {
        char temp[10]; // Temporary buffer for each process state
        sprintf(temp, "P%d[%s] ", processes[i].pid, 
            processes[i].etat == ELU ? "ELU" : 
            processes[i].etat == ACTIVABLE ? "ACTIVABLE" : 
            processes[i].etat == ENDORMI ? "ENDORMI" : 
            processes[i].etat == MORT ? "MORT" : "UNKNOWN");
        strcat(etats, temp); // Append process state to the main string
    }

    int col = 0;
    for (size_t i = 0; i < strlen(etats); i++, col++) {
        char c = etats[i];
        int8_t *carac = (int8_t *)font8x8_basic[(int)c];
        char allume;
        for (int y = 0; y < 8; y++) {
            int8_t line = carac[y];
            for (int x = 0; x < 8; x++) {
                allume = (line >> x) & 1;
                if (allume == 1) {
                    pixel(y, (col * 8) + x, 0xffffff);
                } else {
                    pixel(y, (col * 8) + x, 0x000000);
                }
            }
        }
    }

}


