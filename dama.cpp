#include <iostream>
#include <pthread.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include "dama_processos.h"
using namespace std;

int main(){
	setlocale (LC_ALL, "Portuguese");
	//Jogo iniciado atraves de uma fun��o apenas, ap�s isso este m�todo carrega mais duas fun��es de sistematiza��o
	//Updates:  
	//1 - Jogo animado.
	//2 - Pe�as se movimentando perfeitamente.
	//3 - Comer uma pe�a (Fun��o concertada).
	//4 - Fun��o de resetar implementada.
	//5 - Fun��o peca rei concluida. :)                   
	                                            
	system("color 20");
	SetConsoleTitle("Dama-Beta (Cherthy Games).");
    game_Init(); //Fun��o principal, (Inicia 4 eventos consecutivos).
	return 0;
}
