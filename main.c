#include <stdio.h>
#include <stdlib.h>

int main() {

    char comando;
    char mapa[5][12] = {
        "###########",
        "#         #",
        "#         #",
        "#         #",
        "###########"
    };

    int andarX = 5;
    int andarY = 2;

    while(1) {
        system("clear");

        for(int y=0;y<5;y++){
            for(int x=0;x<11;x++){
                if(x == andarX && y == andarY){
                    printf("P");
                } 
                else{
                    printf("%c", mapa[y][x]);
                }
            }
            printf("\n");
        }

        printf("wasd:");
        scanf(" %c", &comando);

        if(comando == 'w'){
            if(mapa[andarY-1][andarX] != '#'){
                andarY--;
            }
        }
        else if(comando == 's'){
            if(mapa[andarY+1][andarX] != '#'){
                andarY++;
            }
        }

        else if(comando == 'a'){
            if(mapa[andarY][andarX-1] != '#'){
                andarX--;
            }
        }
        else if(comando == 'd'){
            if(mapa[andarY][andarX+1] != '#'){
            andarX++;
            }
        } else{
            printf("comando inválido!");
        }
}
    return 0;
}