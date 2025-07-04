#include "stm32f103xb.h"
#include "teclado.h"
#include <string.h>
#include <stdbool.h>

char clave[6] = "C1516";
char ingreso[6];
char nueva[6];
int verde = 9;
int rojo = 10;
int p = 0;
bool ok = false;
bool cambio = false;

int main(void){
    tecla_init(1, 2, 3, 4, 5, 6, 7, 8);

    GPIOA->CRH &= ~(0xF << ((verde % 8) * 4));
    GPIOA->CRH |= (1 << (verde * 4));
    GPIOA->CRH &= ~(0xF << ((rojo % 8) * 4));
    GPIOA->CRH |= (1 << (rojo * 4));

    while(1){
        char t = leer_tecla(1, 2, 3, 4, 5, 6, 7, 8);

        if(t != 'x'){
            if(cambio){
                nueva[p] = t;
                p++;
                if(p == 5){
                    strcpy(clave, nueva);
                    memset(nueva, 0, sizeof(nueva));
                    cambio = false;
                    p = 0;
                }
            } else if(ok){
                if(t == '#'){
                    ok = false;
                    cambio = true;
                    p = 0;
                }
            } else {
                ingreso[p] = t;
                p++;
                if(p == 5){
                    ingreso[5] = '\0';
                    if(strcmp(ingreso, clave) == 0){
                        GPIOA->BSRR |= (1 << verde);
                        GPIOA->BSRR |= (1 << (rojo + 16));
                        ok = true;
                    } else {
                        GPIOA->BSRR |= (1 << (verde + 16));
                        GPIOA->BSRR |= (1 << rojo);
                        ok = false;
                    }
                    memset(ingreso, 0, sizeof(ingreso));
                    p = 0;
                }
            }
        }
    }
}