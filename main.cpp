#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

typedef struct{
    int x;
    int y;
} playerCd;

typedef struct{
    int x;
    int y;
    int used;
    int player;
} saved;

COORD cord = {0,0};
playerCd playerCoord[2];
int backupX, backupY, whosTurn, enter=0, counter=0;
saved savedPosyx[9];

void gotoxy(int x, int y){
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

void printZero(int x, int y){
    for(int i=0; i < 4; i++){
        gotoxy(x, y+i);
        for(int j=0; j < 4; j++){
            printf("%c", 177);
        }
        cout << endl;
    }
}

void printX(int x, int y){
    gotoxy(x, y++);
    printf("*  *");
    gotoxy(x, y++);
    printf(" ** ");
    gotoxy(x, y++);
    printf(" ** ");
    gotoxy(x, y);
    printf("*  *");
}

void CheckAndChangePosition(char direction, int player, int isEnter){
    int x=0, y=0;
    x = playerCoord[player].x;
    y = playerCoord[player].y;

    switch(direction){
    case 'd' :
        x += 11;
        break;

    case 'a' :
        x -= 11;
        break;

    case 'w' :
        y -= 7;
        break;

    case 's' :
        y += 7;
        break;
    }

    if(y > 20 || y < 6){
        return;
    }else if(x > 45 || x < 23){
        return;
    }

    gotoxy((playerCoord[player].x) - 2, (playerCoord[player].y) - 1);
    cout << " ";
    playerCoord[player].x = x; playerCoord[player].y = y;
    gotoxy((playerCoord[player].x) - 2, (playerCoord[player].y) - 1);
    cout << ".";


    if(isEnter == 1){
        switch(player){
        case 0:
            printZero(playerCoord[0].x, playerCoord[0].y); enter  = 0;
            break;

        case 1:
            printX(playerCoord[1].x, playerCoord[1].y); enter = 0;
            break;
        }
    }
}

void drawCanva(){
    gotoxy(20, 11);
    for(int i=0; i < 32; i++){
        printf(".");
    }
    gotoxy(20, 18);
    for(int i=0; i < 32; i++){
        printf(".");
    }
    for(int i=0; i < 20; i++){
        gotoxy(30, i+5);
        printf(".\n");
    }
    for(int i=0; i < 20; i++){
        gotoxy(41, i+5);
        printf(".");
    }
}

void saveLocation(int x, int y, int turn){
    int who = turn, hell = counter;
    savedPosyx[counter].used = 1;
    savedPosyx[counter].x = x;
    savedPosyx[counter].y = y;
    savedPosyx[counter].player = turn;
    counter++;
}

int searchIfUsed(int x, int y){
    for(int i=0; i < counter; i++){
        if(savedPosyx[i].x == x && savedPosyx[i].y == y && savedPosyx[i].used == 1){
            return 0;
        }
    }
    return 1;
}

void inherit(int player){
    if(player == 0){
        playerCoord[1].x = playerCoord[0].x;
        playerCoord[1].y = playerCoord[0].y;
    }else if(player == 1){
        playerCoord[0].x = playerCoord[1].x;
        playerCoord[0].y = playerCoord[1].y;
    }
}

void checkWinner(int turn){
    int addX = 0, addY=0, i=0, j=0, values[2][3] = {{23, 34, 45}, {6, 13, 20}}, diag_1 = 0, diag_2=0;
    playerCd checking[5];
    for( i=0, j=0; i < counter; i++){
        if(savedPosyx[i].player == turn){
            checking[j].x = savedPosyx[j].x;
            checking[j].y = savedPosyx[j].y;
            j++;
        }
    }


    for(int k=0; k < 3; k++){
        for(int f=0; f < j; f++){
            if(checking[f].x == values[0][k]){
                addX++;
            }
            if(checking[f].y == values[1][k]){
                addY++;
            }

            if((checking[f].x == 23 && checking[f].y == 6) ||
            (checking[f].x == 34 && checking[f].y == 13) || (checking[f].x == 45
            && checking[f].y == 20)){
                diag_1++;
            }

            if((checking[f].x == 45 && checking[f].y == 6) ||
            (checking[f].x == 34 && checking[f].y == 13) || (checking[f].x == 23
            && checking[f].y == 20)){
                diag_2++;
            }

        }
        if(addX >= 3 || addY >= 3 || diag_1 >= 3 || diag_2 >= 3){
            gotoxy(0,0);
            cout << "player ";
            if(turn ==0){
                cout << "2";
            }else{
                cout << "1";
            }
            cout << " wins!";
            exit(0);
        }
    }

}

int main()
{
    int flag = 0, helper, inc=0;
    char c;
    drawCanva();
    srand((unsigned)time(NULL));
    helper = (rand() % (1 - 0 + 1)) + 0;
    playerCoord[0].x = 34 ; playerCoord[0].y = 13;
    playerCoord[1].x = 34 ; playerCoord[1].y = 13;

    gotoxy(32, 12);
    cout << ".";

    while(1){
        if(_kbhit()){
            c = _getch();
            if(c == 13 && searchIfUsed(playerCoord[helper].x, playerCoord[helper].y)){
                enter = 1;
                saveLocation(playerCoord[helper].x, playerCoord[helper].y, helper);
                if(counter >= 5){
                    checkWinner(helper);
                }
                inherit(helper);
                if(helper == 1){helper = 0;}
                else if(helper == 0){helper = 1;}

                if(counter == 9){
                    exit(0);
                }
            }

            CheckAndChangePosition(c, helper, enter);

        }
    }
    return 0;
}
