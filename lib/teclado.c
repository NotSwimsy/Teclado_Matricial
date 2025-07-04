#include "stm32f103xb.h"
#include "teclado.h"

char teclas[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

void tecla_init(int f1, int f2, int f3, int f4, int c1, int c2, int c3, int c4){
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    int cols[4] = {c1, c2, c3, c4};
    int fils[4] = {f1, f2, f3, f4};

    for(int i = 0; i < 4; i++){
        if(cols[i] < 8){
            GPIOA->CRL &= ~(0xF << (cols[i] * 4));
            GPIOA->CRL |= (1 << (cols[i] * 4 + 3));
            GPIOA->BSRR |= (1 << (cols[i] * 4));
        } else {
            GPIOA->CRH &= ~(0xF << ((cols[i] % 8) * 4));
            GPIOA->CRH |= (1 << ((cols[i] % 8) * 4 + 3));
            GPIOA->BSRR |= (1 << (cols[i] * 4));
        }
    }

    for(int i = 0; i < 4; i++){
        if(fils[i] < 8){
            GPIOA->CRL &= ~(0xF << (fils[i] * 4));
            GPIOA->CRL |= (1 << (fils[i] * 4));
            GPIOA->BSRR |= (1 << (fils[i] * 4));
        } else {
            GPIOA->CRH &= ~(0xF << ((fils[i] % 8) * 4));
            GPIOA->CRH |= (1 << ((fils[i] % 8) * 4));
            GPIOA->BSRR |= (1 << (fils[i] * 4));
        }
    }
}

char leer_tecla(int f1, int f2, int f3, int f4, int c1, int c2, int c3, int c4){
    int cols[4] = {c1, c2, c3, c4};
    int fils[4] = {f1, f2, f3, f4};

    for(int i = 0; i < 4; i++){
        GPIOA->BSRR |= (1 << (fils[i] + 16));
        for(int j = 0; j < 4; j++){
            if(!(GPIOA->IDR & (1 << cols[j]))){
                return teclas[i][j];
            }
        }
        GPIOA->BSRR |= (1 << fils[i]);
    }
    return 'x';
}