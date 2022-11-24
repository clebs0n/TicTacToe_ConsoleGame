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
int backupX, backupY;

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

void saveCurrentPosxy(int x, int y){
    backupX = x;
    backupY = y;
}

void CheckAndChangePosition(char direction, int player){
    int x=0, y=0;
    x = playerCoord[player].x;
    y = playerCoord[player].y;

    switch(direction){
    case 'r' :
        x += 11;
        break;

    case 'l' :
        x -= 11;
        break;

    case 'u' :
        y -= 7;
        break;

    case 'd' :
        y += 7;
        break;
    }

    if(y > 20 || y < 6){
        saveCurrentPosxy(playerCoord[player].x, playerCoord[player].y);
        gotoxy(23, 0);
        cout << "error";
        gotoxy(backupX, backupY);
        return;
    }else if(x > 45 || x < 23){
        saveCurrentPosxy(playerCoord[player].x, playerCoord[player].y);
        gotoxy(23, 0);
        cout << "error";
        gotoxy(backupX, backupY);
        return;
    }

    playerCoord[player].x = x; playerCoord[player].y = y;
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

int main()
{
    char c;
    drawCanva();
    srand((unsigned)time(NULL));

    while(1){
        if(_kbhit()){
            c = _getch();
            CheckAndChangePosition(c, 0);
        }
    }
    return 0;
}
