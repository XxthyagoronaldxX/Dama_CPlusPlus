#include <iostream>
#include <pthread.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include "dama_processos.h"
using namespace std;

int main(){
	setlocale (LC_ALL, "Portuguese");
	//Jogo iniciado atraves de uma função apenas, após isso este método carrega mais duas funções de sistematização
	//Updates:  
	//1 - Jogo animado.
	//2 - Peças se movimentando perfeitamente.
	//3 - Comer uma peça (Função concertada).
	//4 - Função de resetar implementada.
	//5 - Função peca rei concluida. :)                   
	                                            
	system("color 20");
	SetConsoleTitle("Dama-Beta (Cherthy Games).");
    game_Init(); //Função principal, (Inicia 4 eventos consecutivos).
	return 0;
}
