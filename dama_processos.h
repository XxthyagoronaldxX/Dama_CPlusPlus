#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include "dama_Imgs.h"
#define DAMA_PROC
#ifdef DAMA_PROC

//--------------------------------------------------------------------------------------------------------------------------------------------

//Funções do jogo:
bool game_InitMenu();
bool game_AnaOpc(char opc);
void game_Init();
void game_Construtor();
void game_InitJogo();
void game_AdcInfo();
void game_AnaJogada();
void game_AnaPeca();
void game_TransDamaRei();
void game_JogDamaRei();
void game_AnaDamaRei();
void game_RotaJg();
void game_ContPc();
void game_Fim();

//--------------------------------------------------------------------------------------------------------------------------------------------

//Funções jogadas:
void game_DirCim();
void game_EsqCim();
void game_DirBai();
void game_EsqBai();

//--------------------------------------------------------------------------------------------------------------------------------------------

//Funções come:
void game_CimDir();
void game_CimEsq();
void game_BaiDir();
void game_BaiEsq();

//--------------------------------------------------------------------------------------------------------------------------------------------

//Função principal, inicia todas as funções necessarias para o inicio do jogo.
void game_Init(){
	game_Construtor();
	if (game_InitMenu()){
		game_AdcInfo();
		game_InitJogo();
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Função construtor, ela simplesmente reseta todas as variaveis para o seu padrão.
void game_Construtor(){
	for (int i = 0;i < tlJogo_lin;i++){
		for (int j = 0;j < tlJogo_col;j++){
			tlJogo[i][j] = tlJogoAux[i][j];
		}
	}
	preencheCampoNull();
	jg_Atual = 0; 
	jg_Atual_Lin = 0;
	jg_Atual_Col = 0;
    jg_Adver = 1;
    jg_Adver_Lin = 0;
	jg_Adver_Col = 0;
	jg_QuantPc[0] = 12;
	jg_QuantPc[1] = 12;
	ani_lin = 0;
	ani_col = 0;
	ani_atual = 'o';
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Função menu, inicia o menu e suas interfaces em geral.
bool game_InitMenu(){
	char opc;
	
	do{
		textColor(NULL, _BACKGROUND);
		system("cls");
		mosBg();
		mosMenu();
		gotoxy(0, 14);
		textColor(_MenuBttInfoE, _BACKGROUND);
		cout<<"Pressione 'e' para confirmar sua escolha";
		opc = getch();
		system("cls");
		switch(opc){
			case 'w':
				if (loc != 0){
					tlMenu[loc][0] = ' ';
					tlMenu[loc][1] = ' ';
					loc--;
					tlMenu[loc][0] = '-';
					tlMenu[loc][1] = '>';
				}
				break;
			case 's':
				if (loc != 2){
					tlMenu[loc][0] = ' ';
					tlMenu[loc][1] = ' ';
					loc++;
					tlMenu[loc][0] = '-';
					tlMenu[loc][1] = '>';
				}
				break;
			case 'e':
				textColor(2, 0);
				switch(loc){
					case 0:
						fflush(stdin);
						return true;
						break;
					case 1:
						mosInfo();
						break;
					case 2:
						return false;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}while(true);
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Funçaõ adiciona informações, adiciona nome dos jogadores.
void game_AdcInfo(){
	mosBg();
	cout<<"\nInforme o nome do primeiro jogador: \n\n- ";
	cin>>jg_Nomes[0];
	cout<<"\nInforme o nome do segundo jogador: \n\n- ";
	cin>>jg_Nomes[1];
	system("cls");
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Funçaõ initJogo, ela inicia todas as funções em conjunto, e daqui o jogo começa.
void game_InitJogo(){
	bool Exit = true;
	char opc;
	
	do{	
		if (jg_Atual > 1){
			jg_Atual = 0;
			jg_Adver = 1;
		}
		
		game_TransDamaRei();
		system("cls");
		textColor(_InfoJgs, _BACKGROUND);
		cout<<"=== Jogador: "<<jg_Nomes[jg_Atual]<<" === Peça: "<<jg_Pecas[jg_Atual]<<" ===\n\n";
		mosGame();
		opc = getch();
		
		if (!game_AnaOpc(opc)){		
			switch(opc){
				case 'd':
					if (ani_lin == 7 && ani_col != 8){
						tlJogo[ani_lin][ani_col] = ani_atual;
						ani_col++;
						ani_atual = tlJogo[ani_lin][ani_col];
						tlJogo[ani_lin][ani_col] = aniPeca;
					}
					break;
				case 'e':
					if (ani_atual == jg_PecasRei[jg_Atual]){
						game_JogDamaRei();
					}else{
						if (ani_lin == 7 && ani_col == 8){
							game_Construtor();
						}
						if (jg_Pecas[jg_Atual] == 'o'){
							if (ani_atual == jg_Pecas[jg_Atual]){
								if (tlJogo[ani_lin+1][ani_col+1] == ' '
								|| tlJogo[ani_lin+1][ani_col-1] == ' '
								|| tlJogo[ani_lin+1][ani_col+1] == jg_Pecas[jg_Adver]
								|| tlJogo[ani_lin+1][ani_col-1] == jg_Pecas[jg_Adver]){
									
									game_AnaJogada();
									
								}
							}
						}else{
							if (ani_atual == jg_Pecas[jg_Atual]){
								if (tlJogo[ani_lin-1][ani_col+1] == ' '
								|| tlJogo[ani_lin-1][ani_col-1] == ' '
								|| tlJogo[ani_lin-1][ani_col+1] == jg_Pecas[jg_Adver]
								|| tlJogo[ani_lin-1][ani_col-1] == jg_Pecas[jg_Adver]){
									
									game_AnaJogada();
									
								}
							}
						}
					}
					break;
				default:
					break;
			}
		}
		game_Fim();
	}while(Exit);
}

//Analisa as opções informados pela função (game_InitJogo) e a (game_JogDamaRei).
bool game_AnaOpc(char opc){	
	switch(opc){
		case 'w':
			if (ani_col != 8 && ani_lin != 0){
					tlJogo[ani_lin][ani_col] = ani_atual;
					ani_lin--;
					ani_atual = tlJogo[ani_lin][ani_col];
					tlJogo[ani_lin][ani_col] = aniPeca;
					return true;
			}
			break;
		case 's':
			if (ani_lin != 7){
				tlJogo[ani_lin][ani_col] = ani_atual;
				ani_lin++;
				ani_atual = tlJogo[ani_lin][ani_col];
				tlJogo[ani_lin][ani_col] = aniPeca;
				return true;
			}
			break;
		case 'a':
			if (ani_col != 0){
				tlJogo[ani_lin][ani_col] = ani_atual;
				ani_col--;
				ani_atual = tlJogo[ani_lin][ani_col];
				tlJogo[ani_lin][ani_col] = aniPeca;
				return true;
			}
			break;
		case 'd':
			if (ani_col != 7 && ani_col != 8){
				tlJogo[ani_lin][ani_col] = ani_atual;
				ani_col++;
				ani_atual = tlJogo[ani_lin][ani_col];
				tlJogo[ani_lin][ani_col] = aniPeca;
				return true;
			}
			break;
		default:
			break;
	}
	return false;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Funçaõ analisa jogada, procura de uma forma precisa as peças adversarias a o seu redor, e logo que acha manda uma informação para o usuario.
void game_AnaJogada(){
	char opcao;
	bool Exit = true, PcCome = false;
	
	do{
		system("cls");
		mosGame();
		jg_Atual_Lin = ani_lin;
		jg_Atual_Col = ani_col;
		cout<<endl<<endl;
		
		//Testa a chance de aparecer uma peça pra comer.
		if (tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
		&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col-2] == ' '){
			
			PcCome = true;
			
		}else if (tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
		&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col+2] == ' '){
			
			PcCome = true;
				
		}else if (tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
		&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col-2] == ' '){
			
			PcCome = true;
			
		}else if (tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
		&& tlJogo[jg_Atual_Lin - 2][jg_Atual_Col + 2] == ' '){
			
			PcCome = true;
		
		//Se a analise falhar, temos a analise da jogada automatica. -- Talvez com algum erro Revisar urgentemente --
		}else if (ani_atual == 'o'){
			
			if (tlJogo[ani_lin+1][ani_col+1] != ' ' || tlJogo[ani_lin+1][ani_col-1] != ' '){
				if (tlJogo[ani_lin+1][ani_col+1] == ' '){
					game_DirBai();
					game_RotaJg();
					Exit = false;
				}else if (tlJogo[ani_lin+1][ani_col-1] == ' '){
					game_EsqBai();
					game_RotaJg();
					Exit = false;
				}
			}
			
		}else if (ani_atual == 'x'){
			
			if (tlJogo[ani_lin-1][ani_col+1] != ' ' || tlJogo[ani_lin-1][ani_col-1] != ' '){
				if (tlJogo[ani_lin-1][ani_col+1] == ' '){
					game_DirCim();
					game_RotaJg();
					Exit = false;
				}else if (tlJogo[ani_lin-1][ani_col-1] == ' '){
					game_EsqCim();
					game_RotaJg();
					Exit = false;
				}
			}
			
		}
		
		if (!PcCome){
			if (tlJogo[ani_lin+1][ani_col-1] != ' ' && tlJogo[ani_lin+1][ani_col+1] != ' ' && ani_atual == 'o'){
				Exit = false;
			}
			
			if (tlJogo[ani_lin-1][ani_col-1] != ' ' && tlJogo[ani_lin-1][ani_col+1] != ' ' && ani_atual == 'x'){
				Exit = false;
			}
		}
		
		if (Exit){
			do{
				system("cls");
				mosGame();
				if (PcCome){
					cout<<"\n\nPressione [C] para comer a peça - ";
				}
				
				if (ani_atual == 'o'){
					if (tlJogo[ani_lin+1][ani_col+1] == ' ' && tlJogo[ani_lin+1][ani_col-1] == ' '){
						cout<<"\n\nMover para Esquerda [E] ou Direita [D]:\n\n- ";
					}else if (tlJogo[ani_lin+1][ani_col+1] == ' '){
						cout<<"\n\nMover para Direita [D]:\n\n- ";
					}else if (tlJogo[ani_lin+1][ani_col-1] == ' '){
						cout<<"\n\nMover para Esquerda [E]:\n\n- ";
					}
				}else if (ani_atual == 'x'){
					if (tlJogo[ani_lin-1][ani_col+1] == ' ' && tlJogo[ani_lin-1][ani_col-1] == ' '){
						cout<<"\n\nMover para Esquerda [E] ou Direita [D]:\n\n- ";
					}else if (tlJogo[ani_lin-1][ani_col+1] == ' '){
						cout<<"\n\nMover para Direita [D]:\n\n- ";
					}else if (tlJogo[ani_lin-1][ani_col-1] == ' '){
						cout<<"\n\nMover para Esquerda[E]:\n\n- ";
					}
				}
				
				opcao = getch();
				if (opcao == '0'){
					Exit = false;
				}else if (opcao == 'c' || opcao == 'C'){
					game_AnaPeca();
					game_RotaJg();
					game_ContPc();
					Exit = false;
				}else if (jg_Pecas[jg_Atual] == 'o'){
					switch(opcao){
						case 'e':
						case 'E':
							if (tlJogo[ani_lin+1][ani_col-1] == ' '){
								game_EsqBai();
								game_RotaJg();
								Exit = false;
							}
							break;
						case 'D':
						case 'd':
							if (tlJogo[ani_lin+1][ani_col+1] == ' '){
								game_DirBai();
								game_RotaJg();
								Exit = false;
							}
							break;
						default:
							break;
					}
				}else if (jg_Pecas[jg_Atual] == 'x'){
					switch(opcao){
						case 'e':
						case 'E':
							if (tlJogo[ani_lin-1][ani_col-1] == ' '){
								game_EsqCim();
								game_RotaJg();
								Exit = false;
							}
							break;
						case 'D':
						case 'd':
							if (tlJogo[ani_lin-1][ani_col+1] == ' '){
								game_DirCim();
								game_RotaJg();
								Exit = false;
							}
							break;
						default:
							break;
					}
				}
			}while(opcao != 'e' && opcao != 'E' && opcao != 'd' && opcao != 'D' && opcao != 'c' && opcao != 'C' && opcao != '0');	
		}	
	}while(Exit);
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Função analisa peça, ela somente testa todas as posiveis chances de comer a peça adversaria.
void game_AnaPeca(){
	system("cls");
	mosGame();
	Sleep(750);
	int opcPc = 0;
	
	if (tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col-2] == ' '
	&& tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col+2] == ' '
	&& tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col+2] == ' '){
		
		tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = 'E';
		tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = 'D';
		tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = 'C';
		opcPc = 7;
		
	}else if (tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col-2] == ' '
	&& tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col+2] == ' '
	&& tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col-2] == ' '){
		
		tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = 'E';
		tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = 'D';
		tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] = 'C';
		opcPc = 8;
		
	}else if (tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col-2] == ' '
	&& tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col-2] == ' '
	&& tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col+2] == ' '){
		
		tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] = 'E';
		tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = 'D';
		tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = 'C';
		opcPc = 9;
		
	}else if (tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col+2] == ' '
	&& tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col-2] == ' '
	&& tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col+2] == ' '){
		
		tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] = 'E';
		tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = 'D';
		tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = 'C';
		opcPc = 10;
		
	//Testa a chance de aparecer duas escolhas de comer uma peça advesaria.
	}else if (tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col-2] == ' '
	&& tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col+2] == ' '){
		
		tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = 'E';
		tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = 'D';
		opcPc = 1;
	
	}else if (tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col+2] == ' '
	&& tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col-2] == ' '){
		
		tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = 'D';
		tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] = 'E';
		opcPc = 2;
		
	}else if (tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col+2] == ' '
	&& tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col-2] == ' '){
		
		tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = 'D';
		tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] = 'E';
		opcPc = 3;
		
	}else if (tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col+2] == ' '
	&& tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col-2] == ' '){
		
		tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = 'D';
		tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = 'E';
		opcPc = 4;
		
	}else if (tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col+2] == ' '
	&& tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col+2] == ' '){
		
		tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = 'E';
		tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = 'D';
		opcPc = 5;
		
	}else if (tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col-2] == ' '
	&& tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
	&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col-2] == ' '){
		
		tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = 'E';
		tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = 'D';
		opcPc = 6;
		
	}
	
	//Se não ouver Double escolha então consequentemente a variavel opcPc = 0.
	if (opcPc != 0){
		char opc;
		
		if (opcPc <= 6){
			do{
				system("cls");
				mosGame();
				cout<<"\n\nDeseja comer peça da Direita [D] ou da Esquerda [E]: \n\n- ";
				opc = getch();
			}while(opc != 'd' && opc != 'D' && opc != 'e' && opc != 'E');
		}else{
			do{
				system("cls");
				mosGame();
				cout<<"\n\nDeseja comer peça da Direita [D], Esquerda [E] ou o Centro[C]: \n\n- ";
				opc = getch();
			}while(opc != 'd' && opc != 'D' && opc != 'e' && opc != 'E' && opc != 'c' && opc != 'C');
		}
		
		switch(opcPc){
			case 1:
				tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				if (opc == 'd' || opc == 'D'){
					
					game_BaiDir();
					
				}else{
					
					game_CimEsq();
			
				}
				game_AnaPeca();
				break;
			case 2:
				tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] = jg_Pecas[jg_Adver];
				if (opc == 'd' || opc == 'D'){					
					
					game_CimDir();
					
				}else{

					game_BaiEsq();
					
				}
				game_AnaPeca();
				break;
			case 3:
				tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] = jg_Pecas[jg_Adver];
				if (opc == 'd' || opc == 'D'){
					
					game_BaiDir();
					
				}else{

					game_BaiEsq();
					
				}
				game_AnaPeca();
				break;
			case 4:
				tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = jg_Pecas[jg_Adver];
				if (opc == 'd' || opc == 'D'){
					
					game_CimDir();
					
				}else{

					game_CimEsq();
					
				}
				game_AnaPeca();
				break;
			case 5:
				tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				if (opc == 'd' || opc == 'D'){
					
					game_CimDir();
					
				}else{

					game_BaiDir();
					
				}
				game_AnaPeca();
				break;
			case 6:
				tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				if (opc == 'd' || opc == 'D'){
					
					game_CimEsq();
					
				}else{

					game_BaiEsq();
					
				}
				game_AnaPeca();
				break;
			case 7:
				tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				if (opc == 'd' || opc == 'D'){
					
					game_BaiDir();
					
				}else if (opc == 'e' || opc == 'E'){
					
					game_CimEsq();
					
				}else{
					
					game_CimDir();
					
				}
				game_AnaPeca();
				break;
			case 8:
				tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] = jg_Pecas[jg_Adver];
				if (opc == 'd' || opc == 'D'){
					
					game_BaiDir();
					
				}else if (opc == 'e' || opc == 'E'){
					
					game_CimEsq();
					
				}else{
					
					game_BaiEsq();
					
				}
				game_AnaPeca();
				break;
			case 9:
				tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = jg_Pecas[jg_Adver];
				if (opc == 'd' || opc == 'D'){
					
					game_CimDir();
					
				}else if (opc == 'e' || opc == 'E'){
					
					game_BaiEsq();
					
				}else{
					
					game_CimEsq();
					
				}
				game_AnaPeca();
				break;
			case 10:
				tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = jg_Pecas[jg_Adver];
				if (opc == 'd' || opc == 'D'){
					
					game_CimDir();
					
				}else if (opc == 'e' || opc == 'E'){
					
					game_BaiEsq();
					
				}else{
					
					game_BaiDir();
					
				}
				game_AnaPeca();
				break;
			default:
				break;
		}
	}else{
		if (tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
		&& tlJogo[jg_Atual_Lin-2][jg_Atual_Col-2] == ' '){
			
			game_CimEsq();	
			game_AnaPeca();
			
		}else if (tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
		&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col+2] == ' '){
			
			game_BaiDir();
			game_AnaPeca();
			
		}else if (tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] == jg_Pecas[jg_Adver]
		&& tlJogo[jg_Atual_Lin+2][jg_Atual_Col-2] == ' '){
			
			game_BaiEsq();
			game_AnaPeca();
			
		}else if (tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] == jg_Pecas[jg_Adver]
		&& tlJogo[jg_Atual_Lin - 2][jg_Atual_Col + 2] == ' '){

			game_CimDir();
			game_AnaPeca();
			
		}
	}
	
	ajustAni();
	system("cls");
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Funções da peça DamaRei:

//Função que transforma as peças em DamaRei.
void game_TransDamaRei(){
	for (int j = 0;j < tlJogo_col;j++){
		if (j < 8){
			if (tlJogo[0][j] == 'x'){
				tlJogo[0][j] = 'X';
			}
			if (tlJogo[tlJogo_lin-1][j] == 'o'){
				tlJogo[tlJogo_lin-1][j] = 'O';
			}
		}
	}
}

//Função que analisa a jogada da DamaRei.
void game_JogDamaRei(){	
	int aux_lin = ani_lin, aux_col = ani_col;
	int aux_linC = ani_lin, aux_colC = ani_col;
	int typeX = 9, aux;
	
	const int tamMin = 8;
	bool alert;
	char opc;
	
	do{
		alert = true;
		
		system("cls");
		mosGame();
		textColor(_Aguardando, _BACKGROUND);
		cout<<"\n\nAguardando local.......\n\n";
		
		fflush(stdin);
		opc = getch();
		
		if (!game_AnaOpc(opc)){
			if (opc == 'E' || opc == 'e'
			|| opc == 'X' || opc == 'c'){			
				if (aux_lin != ani_lin && aux_col != ani_col){
					
					//Analisa pra baixo-direita.
					if ((aux_lin-ani_lin) == (aux_col-ani_col) && (aux_col-ani_col) < 0){
						
						aux_linC = aux_lin+1;
						aux_colC = aux_col+1;
						
						for (int i = 1;i <= (ani_lin-aux_lin);i++){
							if (tlJogo[aux_linC][aux_colC] == aniPeca){
								if (ani_atual != ' '){
									
									alert = false;
									
								}
							}else if (tlJogo[aux_linC][aux_colC] != ' '){
								
								alert = false;
								
							}
							
							aux_linC++;
							aux_colC++;
							
						}
					
					//Analisa pra cima-esquerda.
					}else if ((aux_lin-ani_lin) == (aux_col-ani_col) && (aux_col-ani_col) > 0){
						
						aux_linC = aux_lin-1;
						aux_colC = aux_col-1;
						
						for (int i = 1;i <= (aux_lin-ani_lin);i++){
							if (tlJogo[aux_linC][aux_colC] == aniPeca){
								if (ani_atual != ' '){
									
									alert = false;
									
								}
							}else if (tlJogo[aux_linC][aux_colC] != ' '){
								
								alert = false;
								
							}
							
							aux_linC--;
							aux_colC--;
							
						}
					
					//Analisa pra cima-direita.
					}else if (((aux_lin-ani_lin)+(aux_col-ani_col)) == 0 && (aux_lin-ani_lin) > 0){
						
						aux_linC = aux_lin-1;
						aux_colC = aux_col+1;
						
						for (int i = 1;i <= (aux_lin-ani_lin);i++){
							if (tlJogo[aux_linC][aux_colC] == aniPeca){
								if (ani_atual != ' '){
									
									alert = false;
									
								}
							}else if (tlJogo[aux_linC][aux_colC] != ' '){
								
								alert = false;
								
							}
							
							aux_linC--;
							aux_colC++;
							
						}

					//Analisa pra baixo-esquerda.
					}else if (((aux_lin-ani_lin)+(aux_col-ani_col)) == 0 && (aux_lin-ani_lin) < 0){
						
						aux_linC = aux_lin+1;
						aux_colC = aux_col-1;

						for (int i = 1;i <= (aux_col-ani_col);i++){
							if (tlJogo[aux_linC][aux_colC] == aniPeca){
								if (ani_atual != ' '){
									
									alert = false;
									
								}
							}else if (tlJogo[aux_linC][aux_colC] != ' '){
								
								alert = false;
								
							}
							
							aux_linC++;
							aux_colC--;
							
						}
						
					//Se alguma delas cair em um campo falso ou invalido.
					}else{
						
						alert = false;
						
					}
					
					//Se um dos campos for verdadeiro essas configurações são ativas.
					if (alert){						
						ani_atual = jg_PecasRei[jg_Atual];
						tlJogo[aux_lin][aux_col] = ' ';
						tlJogo[ani_lin][ani_col] = jg_PecasRei[jg_Atual];
						
						if (opc == 'c' || opc == 'C'){
							jg_Atual_Lin = ani_lin;
							jg_Atual_Col = ani_col;
							game_AnaPeca();
						}
						
						game_RotaJg();
						opc = '0';
					}
				}
			}
		}
	}while(opc != '0');
//	if (ana_col)
}

void game_AnaDamaRei(){
	
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Funções de movimento:

//Cima pra direita:
void game_DirCim(){
	ani_atual = ' ';
	tlJogo[ani_lin-1][ani_col+1] = jg_Pecas[jg_Atual];
	jg_Atual_Lin = ani_lin-1; jg_Atual_Col = ani_col+1;
}

//Cima pra Esquerda:
void game_EsqCim(){
	ani_atual = ' ';
	tlJogo[ani_lin-1][ani_col-1] = jg_Pecas[jg_Atual];
	jg_Atual_Lin = ani_lin-1; jg_Atual_Col = ani_col-1;
}
	
//Baixo pra direita:
void game_DirBai(){
	ani_atual = ' ';
	tlJogo[ani_lin+1][ani_col+1] = jg_Pecas[jg_Atual];
	jg_Atual_Lin = ani_lin+1; jg_Atual_Col = ani_col+1;
}

//Baixo pra esquerda:
void game_EsqBai(){
	ani_atual = ' ';
	tlJogo[ani_lin+1][ani_col-1] = jg_Pecas[jg_Atual];
	jg_Atual_Lin = ani_lin+1; jg_Atual_Col = ani_col-1;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Função rotaciona jogador:
void game_RotaJg(){
	jg_Atual++;
	jg_Adver--;
		
	if (jg_Atual > 1){
		jg_Atual = 0;
		jg_Adver = 1;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Função que conta a quantidade de peça adversaria e amiga:
void game_ContPc(){
	jg_QuantPc[0] = 0;
	jg_QuantPc[1] = 0;
	for (int i = 0;i < tlJogo_lin;i++){
		for (int j = 0;j < tlJogo_col;j++){
			if (tlJogo[i][j] == aniPeca){
				if (ani_atual == 'x'){
					jg_QuantPc[0]++;
				}else if (ani_atual == 'o'){
					jg_QuantPc[1]++;
				}
			}else if (tlJogo[i][j] == 'x' || tlJogo[i][j] == 'X'){
				jg_QuantPc[0]++;
			}else if (tlJogo[i][j] == 'o' || tlJogo[i][j] == 'O'){
				jg_QuantPc[1]++;
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Função que analise se um jogador está sem peça:
void game_Fim(){
	if (jg_QuantPc[0] == 0){
		system("cls");
		mosGame();
		cout<<"O jogador: "<<jg_Nomes[1]<<" venceu o jogo.";
		cin.get();
		cin.get();
		game_Init();
	}else if (jg_QuantPc[1] == 0){
		system("cls");
		mosGame();
		cout<<"O jogador: "<<jg_Nomes[0]<<" venceu o jogo.";
		cin.get();
		cin.get();
		game_Init();
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------

//Funções de movimento para comer peças:

//Função come peça de cima pra direita:
void game_CimDir(){
	tlJogo[jg_Atual_Lin-1][jg_Atual_Col+1] = ' ';
	if (tlJogo[jg_Atual_Lin][jg_Atual_Col] == jg_PecasRei[jg_Atual]){
		
		tlJogo[jg_Atual_Lin-2][jg_Atual_Col+2] = jg_PecasRei[jg_Atual];
		
	}else{
		
		tlJogo[jg_Atual_Lin-2][jg_Atual_Col+2] = jg_Pecas[jg_Atual];
		
	}
	tlJogo[jg_Atual_Lin][jg_Atual_Col] = ' ';
	ani_atual = ' ';
	
	jg_Atual_Lin-=2;
	jg_Atual_Col+=2;
}

//Função come peça de cima pra esquerda:
void game_CimEsq(){
	tlJogo[jg_Atual_Lin-1][jg_Atual_Col-1] = ' ';
	if (tlJogo[jg_Atual_Lin][jg_Atual_Col] == jg_PecasRei[jg_Atual]){
		
		tlJogo[jg_Atual_Lin-2][jg_Atual_Col-2] = jg_PecasRei[jg_Atual];
		
	}else{
		
		tlJogo[jg_Atual_Lin-2][jg_Atual_Col-2] = jg_Pecas[jg_Atual];
		
	}
	tlJogo[jg_Atual_Lin][jg_Atual_Col] = ' ';
	ani_atual = ' ';
	
	jg_Atual_Lin-=2;
	jg_Atual_Col-=2;	
}

//Função come peça de baixo pra direita:
void game_BaiDir(){
	tlJogo[jg_Atual_Lin+1][jg_Atual_Col+1] = ' ';
	if (tlJogo[jg_Atual_Lin][jg_Atual_Col] == jg_PecasRei[jg_Atual]){
		
		tlJogo[jg_Atual_Lin+2][jg_Atual_Col+2] = jg_PecasRei[jg_Atual];
		
	}else{
		
		tlJogo[jg_Atual_Lin+2][jg_Atual_Col+2] = jg_Pecas[jg_Atual];
		
	}
	tlJogo[jg_Atual_Lin][jg_Atual_Col] = ' ';
	ani_atual = ' ';
	
	jg_Atual_Lin+=2;
	jg_Atual_Col+=2;	
}

//Função come peça de baixo pra esquerda:
void game_BaiEsq(){
	tlJogo[jg_Atual_Lin+1][jg_Atual_Col-1] = ' ';
	if (tlJogo[jg_Atual_Lin][jg_Atual_Col] == jg_PecasRei[jg_Atual]){
		
		tlJogo[jg_Atual_Lin+2][jg_Atual_Col-2] = jg_PecasRei[jg_Atual];
		
	}else{
		
		tlJogo[jg_Atual_Lin+2][jg_Atual_Col-2] = jg_Pecas[jg_Atual];
		
	}
	tlJogo[jg_Atual_Lin][jg_Atual_Col] = ' ';
	ani_atual = ' ';
	
	jg_Atual_Lin+=2;
	jg_Atual_Col-=2;
}

//--------------------------------------------------------------------------------------------------------------------------------------------

#endif 
