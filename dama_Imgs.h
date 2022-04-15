#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include "dama_color.h"
#define DAMA_IMGS
#ifdef DAMA_IMGS
using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------------

//Cores de cada parte do jogo:
static int _BACKGROUND = 15;
static int _AniPeca = 13;
static int _InfoJogoMenu1 = 12;
static int _InfoJogoMenu2 = 1;
static int _PecaX = 10;
static int _PecaO = 6;
static int _PecaRei = 12;
static int _NumsCantos = 2;
static int _TabuImg = 9;
static int _Menu = 1;
static int _BackGround = 4;
static int _BttR = 14;
static int _InfoJgs = 5;
static int _PegaInfo = 3;
static int _MenuBttInfoE = 11;
static int _Aguardando = 8;
static int _SelecionaLocCome = 13;

//--------------------------------------------------------------------------------------------------------------------------------------------

//Tela menu animada por matriz.
char tlMenu[3][20]{
"->   - JOGAR -   ",
"  - INFORMAÇÕES -",
"     - SAÍDA -   "
};
int tlMenu_lin = 3, tlMenu_col = 18, loc = 0;

//--------------------------------------------------------------------------------------------------------------------------------------------

//Matriz espelho.
const char tlJogoAux[8][11]{
"@ o o o  ",
" o o o o ",
"o o o o  ",
"         ",
"         ",
" x x x x ",
"x x x x  ",
" x x x xR"
};

//--------------------------------------------------------------------------------------------------------------------------------------------

//Matrizes para teste de jogabilidade:
const char tlJogoTest1[8][9]{
"@ o o o ",
" o o o o",
"      o ",
" ooo    ",
"  x     ",
"   x x x",
"x x x x ",
" x x x x"
};

const char tlJogoTest2[8][9]{
"@       ",
" o o ooo",
"      o ",
" ooo    ",
"  x   o ",
"   x x x",
"x x x x ",
" x x x x"
};

const char tlJogoTest3[8][11]{
"@ x o o  ",
"     o o ",
"o o o o  ",
"         ",
"         ",
" x x x x ",
"x x x x  ",
" x x x xR"
};

const char tlJogoTest4[8][11]{
"@ x o x  ",
"       o ",
"o o o o  ",
"         ",
"         ",
" x x x x ",
"x     x  ",
" o x o xR"
};

const char tlJogoTest5[8][11]{
"@ o o o  ",
" o o o o ",
"x   o o  ",
" o       ",
"x   o    ",
" x x x x ",
"x o x x  ",
"   x x xR"
};

//--------------------------------------------------------------------------------------------------------------------------------------------

//Variaveis para manipular tamanho do jogo e organizar nomes e pecas:

char tlJogo[8][11];
int tlJogo_lin = 8, tlJogo_col = 11, tlJogo_colR = 11;
char jg_Pecas[2] = {'x', 'o'};
char jg_PecasRei[2] = {'X', 'O'};
char tlJogo_null = '-';
string jg_Nomes[2];
int jg_Atual = 0, jg_Atual_Lin = 0, jg_Atual_Col = 0;
int jg_Adver = 1, jg_Adver_Lin = 0, jg_Adver_Col = 0;
int jg_QuantPc[2] = {12, 12};

//Localização do animaButton:

int ani_lin = 0, ani_col = 0;
char ani_atual = 'o';
char aniPeca = '@';

//--------------------------------------------------------------------------------------------------------------------------------------------

//Funções:

void mosGame();
void mosMenu();
void mosBg();
void mosInfo();
void ajustAni();
void preencheCampoNull();

//--------------------------------------------------------------------------------------------------------------------------------------------

//Função mostra menu.
void mosMenu(){
	textColor(_Menu, _BACKGROUND);
	for (int i = 0;i < tlMenu_lin;i++){
		cout<<"        ";
		for (int j = 0;j < tlMenu_col;j++){
			cout<<tlMenu[i][j];
		}
		cout<<endl<<endl;
	}	
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Função mostra BackGround do jogo.
void mosBg(){
	textColor(_BackGround, _BACKGROUND);
	cout<<"====================================\n";
	cout<<" ==================================\n";
	cout<<"  ================================\n";
	cout<<"   ======== Dama Beta:) =========\n";
	cout<<"  ================================\n";
	cout<<" ==================================\n";
	cout<<"================ By: Cherthy Games =\n\n";
	textColor(_PegaInfo, _BACKGROUND);
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Função onde mostra um pequeno tutorial do jogo.
void mosInfo(){
	textColor(_InfoJogoMenu1, _BACKGROUND);
	cout<<" - Comandos usados no jogo - \n\n";
	textColor(_InfoJogoMenu2, _BACKGROUND);
	cout<<"      W - Para cima.\n\n";
	cout<<"      S - Para baixo.\n\n";
	cout<<"      A - Para o lado esquerdo.\n\n";
	cout<<"      D - Para o lado direito.\n\n";
	cout<<"      E - Seleciona algum movimento.\n\n";
	cout<<"      9 - Reseta jogo.\n\n";
	cout<<"      0 - Cancela o movimento.\n\n";
	textColor(_InfoJogoMenu1, _BACKGROUND);
	cout<<"\n - Funções presentes no jogo -\n\n";
	textColor(_InfoJogoMenu2, _BACKGROUND);
	cout<<"      R - Reseta o jogo.\n Se encontra no canto inferior\n           esquerdo.\n\n";
	cout<<"\n - Funções no jogo faltando -\n\n";
	cout<<"      1 - Peça rei.\n\n";
	textColor(_InfoJogoMenu1, _BACKGROUND);
	cout<<"OBS.: Estas funções serão adicionadas\n         na próxima versão.";
	cin.get();
	cin.get();
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Mostra tabuleiro do jogo, e mais as codernadas.
void mosGame(){
	bool colorP = true;
	textColor(_NumsCantos, _BACKGROUND);
	cout<<"       1     2     3     4     5     6     7     8     \n";
	
	textColor(_TabuImg, _BACKGROUND);
	cout<<endl<<"    -------------------------------------------------"<<endl;
	
	for (int i = 0;i < tlJogo_lin;i++){
		
		textColor(_NumsCantos, _BACKGROUND);
		cout<<i+1;
		textColor(_TabuImg, _BACKGROUND);
		cout<<"   |  ";
		
		for (int j = 0;j < tlJogo_colR;j++){
			colorP = true;
			if (j < 9-1){
				if (tlJogo[i][j] == 'X' || tlJogo[i][j] == 'O'){
					
					textColor(_PecaRei, _BACKGROUND);
					cout<<tlJogo[i][j];
					colorP = false;
					
				}else if (tlJogo[i][j] == 'o'){
					
					textColor(_PecaO, _BACKGROUND);
					cout<<tlJogo[i][j];
					colorP = false;
					
				}else if (tlJogo[i][j] == 'x'){
					
					textColor(_PecaX, _BACKGROUND);
					cout<<tlJogo[i][j];
					colorP = false;
					
				}else if (tlJogo[i][j] == aniPeca){
					
					textColor(_AniPeca, _BACKGROUND);
					cout<<tlJogo[i][j];
					colorP = false;
					
				}else if (tlJogo[i][j] == 'E' || tlJogo[i][j] == 'D' || tlJogo[i][j] == 'C'){
				
					textColor(_SelecionaLocCome, _BACKGROUND);
					cout<<tlJogo[i][j];
					colorP = false;
				
				}else{
					
					cout<<tlJogo[i][j];
					
				}
				
				textColor(_TabuImg, _BACKGROUND);
				
				if (colorP){
					
					cout<<"  |  ";
					
				}else{
					
					cout<<"  |  ";
					
				}
				
			}else if (i == 7 && j == 8){
				textColor(_BttR, _BACKGROUND);
				cout<<tlJogo[i][j];
				textColor(_TabuImg, _BACKGROUND);
			}
		}
		
//		cout<<endl<<"_____________________________"<<endl;
		cout<<endl<<"    -------------------------------------------------"<<endl;
		
	}	
	textColor(_InfoJgs, _BACKGROUND);
	cout<<endl<<"=== "<<jg_Nomes[0]<<" : "<<jg_QuantPc[0]<<" === "<<jg_Nomes[1]<<" : "<<jg_QuantPc[1]<<" ===";
	
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Após um movimento a peca anima '@', é realocada para um local vazio usando está função:
void ajustAni(){
	ani_lin = 0;
	ani_col = 1;
	ani_atual = tlJogo_null;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Está função preenche os campos onde a peça numca ira chegar:
void preencheCampoNull(){
	int aux = 1;
	for (int i = 0;i < tlJogo_lin;i++){
		for (int j = aux;j < tlJogo_col;j+=2){
			if (j < 9-1){
				tlJogo[i][j] = tlJogo_null;
				ani_atual = tlJogo_null;
			}
		}
		aux++;
		if (aux > 1){
			aux = 0;
		}
	}
	for (int i = 0; i < tlJogo_lin;i++){
		if (i <= 6){
			tlJogo[i][8] = 'N';
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//By Cherthy Games.

#endif 
