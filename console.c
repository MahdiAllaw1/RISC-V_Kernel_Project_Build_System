#include "console.h"

uint32_t ligne = 1, colone = 0;

void pixel(uint32_t x, uint32_t y, uint32_t couleur){
    if (x >= 720 || y >= 1280) return;
    uint32_t* pixel_adress = (uint32_t*)(0x80000000);
    pixel_adress += (y + x * 1280);
    *pixel_adress = couleur;
}

void ecrit_car(uint32_t lig, uint32_t col, char c){
    int8_t* carac = (int8_t*)font8x8_basic[(int)c];
    char allume;
    place_curseur(ligne, colone+1);
    for (int i=0; i<8; i++){
        int8_t line = carac[i];
        for (int j=0; j<8; j++){
            allume = (line >> j) & 1;
            if (allume == 1) {
                pixel((lig*8)+i ,(col*8)+j ,0xffffff);
            }
            else {
                pixel((lig*8)+i , (col*8)+j ,0x000000);
            }
        }
    }
}

void efface_ecran(void){
    for(uint32_t x = 0; x<720; x++){
        for(uint32_t y = 0; y<1280; y++){
            pixel(x,y,0x000000);
        }
    }
    place_curseur(1,0);
}

void place_curseur(uint32_t lig, uint32_t col){
    efface_curseur(ligne,colone);
    if (colone >= 160){ 
        ligne = lig;
        colone = 0;
        for (uint32_t i=0; i<8; i++){
            for (uint32_t j=0; j<8; j++)
                pixel((ligne*8)+i, j, 0xffffff);
        }
        defilement();
    }
    else{
        ligne = lig;
        colone = col;
        for (uint32_t i=0; i<8; i++){
            for (uint32_t j=0; j<8; j++)
                pixel((lig*8)+i, (col*8)+j, 0xffffff);
        }
        defilement();
    }
}

void efface_curseur(uint32_t lig, uint32_t col){
    for (uint32_t i=0; i<8; i++){
        for (uint32_t j=0; j<8; j++)
            pixel((lig*8)+i, (col*8)+j, 0x00);
    }
}

void defilement(void){
    if(ligne >= 90){
        memmove((uint32_t*)(0x80000000+8*1280*4), (uint32_t*)(0x80000000 + 16 * 1280 * 4), 1280 * 4 * (720 - 8));
        for (uint32_t j = 0; j < 1280; j++) {
            for (uint32_t i = 0; i < 8; i++) {
                pixel((90 - 1)*8 + i, j, 0x000000);
            }
        }
        place_curseur(90-1,0);
    }
}

void traite_car(char c){
    if(colone >= 160){
        place_curseur(ligne+1,0);
        defilement();
    }
    else if(ligne >= 90){
        defilement();
    }
    if (c >= 32 && c <= 126){
        ecrit_car(ligne,colone,c);
    }
    else if(c == '\b' && colone > 0){
        place_curseur(ligne,colone-1);
    }
    else if(c == '\t'){
        if(colone < 160-8){
            uint32_t col = 8 - (colone % 8);
            place_curseur(ligne,colone+col);
        } 
        else{
            place_curseur(ligne+1,0);
            defilement();
        }
    }
    else if(c == '\n'){
        place_curseur(ligne+1,0);
        defilement();
    }
    else if(c == '\f'){
        efface_ecran();
    }
    else if(c == '\r'){
        place_curseur(ligne,0);
    }
}

void console_putbytes(const char *s, int len){
    for (int i = 0; i < len; i++) {
        traite_car(s[i]);
    }
}