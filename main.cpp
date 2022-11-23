#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

COORD cord = {0,0};

void gotoxy(int x, int y){
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

void drawCanva(){
    gotoxy(20, 11);
    for(int i=0; i < 29; i++){
        printf(".");
    }
    gotoxy(20, 18);
    for(int i=0; i < 29; i++){
        printf(".");
    }
    for(int i=0; i < 20; i++){
        gotoxy(29, i+5);
        printf(".\n");
    }
    for(int i=0; i < 20; i++){
        gotoxy(39, i+5);
        printf(".");
    }
}

int main()
{
    drawCanva();
    while(1){
        int i;
    }
    return 0;
}
