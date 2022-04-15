#include <windows.h>
#define COLOR_H
#ifdef COLOR_H
using namespace std;

typedef enum {BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,   
LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE} COLORS;

static int letra_Bg = 1; //BackGround
static int letra_Fg = 1; //ForeGround

void textColor(int letras, int bg){
	letra_Fg = letras;
	letra_Bg = bg;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letras + (letra_Bg << 4));
}

void gotoxy(int x, int y){
	COORD c;
	c.X = x;
	c.Y = y;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

#endif
