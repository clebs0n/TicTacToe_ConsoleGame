#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

typedef struct{
    int x;
    int y;
} playerCd;

COORD cord = {0,0};
playerCd playerCoord[2];
int backupX, backupY, whosTurn, saved[3][3] = {0}, enter=0;

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

void clearPlayerTraces(int x, int y){
    for(int i=0; i < 4; i++){
            gotoxy(x,y+i);
        for(int j=0; j < 4; j++){
            cout << " ";
        }
    }
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

    if(isEnter == 0){
        clearPlayerTraces(playerCoord[whosTurn].x, playerCoord[whosTurn].y);
    }

    playerCoord[player].x = x; playerCoord[player].y = y;

    switch(whosTurn){
    case 0:
        printZero(playerCoord[0].x, playerCoord[0].y); enter = 0;
        break;

    case 1:
        printX(playerCoord[1].x, playerCoord[1].y); enter = 0;
        break;
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

void saveLocation(int x, int y){
    saved[(x/23)-1][(y/7)-1] = 1;
}

int main()
{
    int flag = 0;
    char c;
    drawCanva();
    srand((unsigned)time(NULL));
    whosTurn = (rand() % (1 - 0 + 1)) + 0;
    playerCoord[0].x = 34 ; playerCoord[0].y = 13;
    playerCoord[1].x = 34 ; playerCoord[1].y = 13;

    if(whosTurn == 0){
        printZero(playerCoord[0].x, playerCoord[0].y);
    }else{
        printX(playerCoord[1].x, playerCoord[1].y);
    }

    while(1){
        if(_kbhit()){
            c = _getch();
            if(c == 13 && saved[(playerCoord[whosTurn].x/23)-1][(playerCoord[whosTurn].y/7)-1] == 0){
                enter = 1; flag = 1;
                saveLocation(playerCoord[whosTurn].x, playerCoord[whosTurn].y);
            }
            if(flag == 0){
                CheckAndChangePosition(c, whosTurn, enter);
            }
            flag = 0;
        }
    }
    return 0;
}
