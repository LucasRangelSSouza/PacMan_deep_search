/* Instituto Federal de Goias
Trabalho implementado para obtençao de nota da materia de Estrutura de Dados, 
mistrada pelo Dr. Eduardo Noronha para a turma de Bacharelado em Engenharia de 
Controle e Automaçao 

Aluno:
Lucas Rangel Soares de Souza   20161010700070 

*/


# include <stdio.h>
# include <stdlib.h> 
# include <string.h> 
# include <windows.h> 

# define LIN 23 
# define COL 75 
# define CS LIN/2 - 1 
# define CI LIN/2 + 1 
# define MAXDIV ((COL - 1)/4 - 1) +2 
# define PACMAN 'C' 
# define FRUTA '*' 
# define TIME 10 

void DesenhaCampo(char Campo[][COL]){
    int linhas,colunas;
    for (linhas=1;linhas<LIN - 1;linhas++)
        for (colunas=1;colunas<COL - 1;colunas++)
            Campo[linhas][colunas] = ' ';
    for (colunas=1;colunas<COL - 1;colunas++){
        Campo[0][colunas] = '-';
        Campo[CS][colunas] = '-';
        Campo[CI][colunas] = '-';
        Campo[LIN - 1][colunas] = '-';
    }
  
    for (linhas=1;linhas<LIN - 1;linhas++){
        Campo[linhas][0] = '|';
        Campo[linhas][COL - 1] = '|';
    }

     Campo[LIN/2][0] = PACMAN;
 
    for (colunas=0;colunas<COL;colunas = colunas + COL - 1){
        Campo[0][colunas] = '+';
        Campo[CS][colunas] = '+';
        Campo[CI][colunas] = '+';
        Campo[LIN - 1][colunas] = '+';
    }
}

void AtualizaCampo(char Campo[][COL]){

    int Linhas,Colunas; 
    
    system("cls"); 

   
    for (Linhas=0;Linhas<LIN;Linhas++){
        for(Colunas=0;Colunas<COL;Colunas++)
            printf("%c",Campo[Linhas][Colunas]);
        printf("\n");
    }
}


void ColunasePortas(char Campo[][COL], int PosicaoPortas[][MAXDIV + 1], int *NumPortasComodo, int PosicaoDiv[][MAXDIV]){

    int UltimaDivisoria,Linhas,Partes,Divisoria,Paredes,InicioDivisoria=1,Porta,LinhaDaPorta=CS;
	int i,contador = 0;
	
	for(Partes=0;Partes<2;Partes++){ 

        contador = 15;
	    UltimaDivisoria = 0; 
        Paredes = 1; 
        NumPortasComodo[Partes] = 1;
        Divisoria = 0; 

		for (i=1;i<=4 ; i++){
			
			Divisoria += 15 ;

            if (Divisoria != -1){

                Porta = 2;
                PosicaoPortas[Partes][NumPortasComodo[Partes] -1] = (Divisoria - UltimaDivisoria)/2 + UltimaDivisoria;
                Campo[LinhaDaPorta][(Divisoria - UltimaDivisoria)/2 + UltimaDivisoria] = ' ';
                NumPortasComodo[Partes]++;
                
                for (Linhas=InicioDivisoria;Linhas < InicioDivisoria + 10;Linhas++)
                    Campo[Linhas][Divisoria - 1] = '|';
                
                for (Linhas=InicioDivisoria -1;Linhas < InicioDivisoria + 11;Linhas = Linhas + 10)
                    Campo[Linhas][Divisoria - 1] = '+';
                
                PosicaoDiv[Partes][Paredes] = Divisoria - 1;
				Paredes++;
                UltimaDivisoria = Divisoria - 1;

            }
           
            PosicaoDiv[Partes][Paredes] = COL -1;
        }

        PosicaoPortas[Partes][NumPortasComodo[Partes] -1] = (COL - UltimaDivisoria)/2 + UltimaDivisoria;
        Campo[LinhaDaPorta][(COL - UltimaDivisoria)/2 + UltimaDivisoria] = ' ';
        InicioDivisoria = InicioDivisoria + 12;
        LinhaDaPorta = CI;
        AtualizaCampo(Campo);
   }

}

void ColocaFrutas(char Campo[][COL],int PosicaoDiv[][MAXDIV],int PosFrutaX[][50],int PosFrutaY[][50],int NumFrutas[][MAXDIV + 1],int *NumPortasComodo){

    int LinhaBase=1,Partes,Quartos,Frutas,ContDiv=0;
    //char TituloComodo[2][10]={"SUPERIOR","INFERIOR"};
	for (Partes=0;Partes<2;Partes++){

     system("cls"); 
            
        for (Quartos=0;Quartos<NumPortasComodo[Partes];Quartos++){
            
			NumFrutas[Partes][Quartos]=2;
                  
            for (Frutas=0;Frutas<NumFrutas[Partes][Quartos];Frutas++){
                           
                PosFrutaY[ContDiv][Frutas]= LinhaBase+((int)rand()%((LinhaBase + 10)-(LinhaBase))); 
				    
				PosFrutaX[ContDiv][Frutas]=(PosicaoDiv[Partes][Quartos] + 1)+( ((int) rand()) %((PosicaoDiv[Partes][Quartos + 1] +1)-(PosicaoDiv[Partes][Quartos] + 1)));
               
                Campo[PosFrutaY[ContDiv][Frutas] -1][PosFrutaX[ContDiv][Frutas] -1] = FRUTA;
            }
         
            ContDiv++;
        }
        AtualizaCampo(Campo);
        LinhaBase = LinhaBase + 12;
    }
}

void AndaCima(char Campo[][COL],int *LinhaPac, int *ColunaPac, int *ContPassos){

    Campo[*LinhaPac][*ColunaPac] = ' '; 
    (*LinhaPac)--;
    Campo[*LinhaPac][*ColunaPac] = PACMAN; 
    (*ContPassos)++; 
    AtualizaCampo(Campo);
}


void AndaBaixo(char Campo[][COL],int *LinhaPac, int *ColunaPac, int *ContPassos){

    Campo[*LinhaPac][*ColunaPac] = ' ';
    (*LinhaPac)++;
    Campo[*LinhaPac][*ColunaPac] = PACMAN;
    (*ContPassos)++;
    AtualizaCampo(Campo);

}


void AndaDireita(char Campo[][COL],int *LinhaPac, int *ColunaPac, int *ContPassos){

    Campo[*LinhaPac][*ColunaPac] = ' ';
    (*ColunaPac)++;
    Campo[*LinhaPac][*ColunaPac] = PACMAN;
    (*ContPassos)++;
    AtualizaCampo(Campo);
}


void AndaEsquerda(char Campo[][COL],int *LinhaPac, int *ColunaPac, int *ContPassos){

    Campo[*LinhaPac][*ColunaPac] = ' ';
    (*ColunaPac)--;
    Campo[*LinhaPac][*ColunaPac] = PACMAN;
    (*ContPassos)++;
    AtualizaCampo(Campo);
}


void PegaFruta(char Campo[][75], int frutaperto, int quartoperto, int *ColunaPac, int *LinhaPac,int PosFrutaY[][50], int PosFrutaX[][50],int *ContPassos){

    
    if (PosFrutaX[quartoperto][frutaperto] < *ColunaPac + 1)
        while (PosFrutaX[quartoperto][frutaperto] < *ColunaPac + 1)
            AndaEsquerda(Campo,LinhaPac,ColunaPac,ContPassos);
    else
        while (PosFrutaX[quartoperto][frutaperto] > *ColunaPac + 1)
            AndaDireita(Campo,LinhaPac,ColunaPac,ContPassos);


   
    if (PosFrutaY[quartoperto][frutaperto] < *LinhaPac + 1)
        while (PosFrutaY[quartoperto][frutaperto] < *LinhaPac + 1)
            AndaCima(Campo,LinhaPac,ColunaPac,ContPassos);

    else
        while (PosFrutaY[quartoperto][frutaperto] > *LinhaPac + 1)
            AndaBaixo(Campo,LinhaPac,ColunaPac,ContPassos);
}


void EncontraFrutaProxima(char Campo[][75], int PosFrutaY[][50], int PosFrutaX[][50], int NumFrutas[][MAXDIV + 1], int *LinhaPac, int *ColunaPac, int parte, int quartos, int atualquarto,int *ContPassos){

    int aux=0,aux2,menordistancia,quartoperto,frutaperto,posicaox,posicaoy;

    quartoperto = quartos; 

   
    while (aux < NumFrutas[parte][atualquarto]){
            menordistancia = 100;
     
        for (aux2=0;aux2<NumFrutas[parte][atualquarto];aux2++)
           
            if (Campo[PosFrutaY[quartos][aux2]-1][PosFrutaX[quartos][aux2]-1] == FRUTA){

                
                if (PosFrutaY[quartos][aux2] - (*LinhaPac +1) < 0)
                    posicaoy = -(PosFrutaY[quartos][aux2] - (*LinhaPac +1));
                else
                    posicaoy = PosFrutaY[quartos][aux2] - (*LinhaPac +1);

                
                if (PosFrutaX[quartos][aux2] - (*ColunaPac +1) < 0)
                    posicaox = -(PosFrutaX[quartos][aux2] - (*ColunaPac +1));
                else
                    posicaox = PosFrutaX[quartos][aux2] - (*ColunaPac +1);
                
                if ( posicaoy + posicaox < menordistancia){

                    menordistancia = posicaoy + posicaox;
                    frutaperto = aux2; 
                }
            }

        PegaFruta(Campo,frutaperto,quartoperto,ColunaPac,LinhaPac,PosFrutaY,PosFrutaX,ContPassos);
        aux++; 
    }
}


void EntraSaiPorta(char Campo[][COL], int PosicaoPortas[][MAXDIV + 1], int *NumPortasComodo, int *LinhaPac, int *ColunaPac, int *ContPassos, int NumFrutas[][MAXDIV + 1], int PosFrutaY[][50], int PosFrutaX[][50]){

    int aux,aux2=0,aux3=0;
    int quartossuperior = 0; 
    int quartosinferior = NumPortasComodo[0]; 

    for(aux=0;aux<NumPortasComodo[0] + NumPortasComodo[1];aux++){

        
        if(((PosicaoPortas[0][aux2] <= PosicaoPortas[1][aux3]) && (aux2 < NumPortasComodo[0])) ||(aux3 == NumPortasComodo[1])) {
            while(*ColunaPac < PosicaoPortas[0][aux2])
                AndaDireita(Campo,LinhaPac,ColunaPac,ContPassos); 

            AndaCima(Campo,LinhaPac,ColunaPac,ContPassos); 


            if (NumFrutas[0][aux2] > 0){ 
                AndaCima(Campo,LinhaPac,ColunaPac,ContPassos); 
    
                EncontraFrutaProxima(Campo,PosFrutaY,PosFrutaX,NumFrutas,LinhaPac,ColunaPac,0,quartossuperior,aux2,ContPassos);
               
                if (PosicaoPortas[0][aux2] < *ColunaPac)
                    while (PosicaoPortas[0][aux2] < *ColunaPac)
                        AndaEsquerda(Campo,LinhaPac,ColunaPac,ContPassos);

                else
                    while (PosicaoPortas[0][aux2] > *ColunaPac)
                        AndaDireita(Campo,LinhaPac,ColunaPac,ContPassos);

                while (9 > *LinhaPac)
                        AndaBaixo(Campo,LinhaPac,ColunaPac,ContPassos);

                AndaBaixo(Campo,LinhaPac,ColunaPac,ContPassos);
            }

            AndaBaixo(Campo,LinhaPac,ColunaPac,ContPassos);

            aux2++; 
            quartossuperior++;

        
        }else{

            while(*ColunaPac < PosicaoPortas[1][aux3])
                AndaDireita(Campo,LinhaPac,ColunaPac,ContPassos);

            AndaBaixo(Campo,LinhaPac,ColunaPac,ContPassos);

            if (NumFrutas[1][aux3] > 0){
                AndaBaixo(Campo,LinhaPac,ColunaPac,ContPassos);

                EncontraFrutaProxima(Campo,PosFrutaY,PosFrutaX,NumFrutas,LinhaPac,ColunaPac,1,quartosinferior,aux3,ContPassos);

                if (PosicaoPortas[1][aux3] < *ColunaPac)
                    while (PosicaoPortas[1][aux3] < *ColunaPac)
                        AndaEsquerda(Campo,LinhaPac,ColunaPac,ContPassos);

                else
                    while (PosicaoPortas[1][aux3] > *ColunaPac)
                        AndaDireita(Campo,LinhaPac,ColunaPac,ContPassos);

                while (13 < *LinhaPac)
                        AndaCima(Campo,LinhaPac,ColunaPac,ContPassos);

                AndaCima(Campo,LinhaPac,ColunaPac,ContPassos);
            }
            AndaCima(Campo,LinhaPac,ColunaPac,ContPassos);
            aux3++;
            quartosinferior++;
        }
    }

    while(*ColunaPac < COL - 1)
        AndaDireita(Campo,LinhaPac,ColunaPac,ContPassos); 
}

int main(){

    char Campo[LIN][COL];
    int PosicaoPortas[2][MAXDIV + 1],NumPortasComodo[2],PosicaoDiv[2][MAXDIV];
    int PosFrutaX[2*(MAXDIV + 1)][50],PosFrutaY[2*(MAXDIV + 1)][50],NumFrutas[2][MAXDIV + 1];
    int LinhaPac=CS+1,ColunaPac = 0,ContPassos=0;

    PosicaoDiv[0][0] = 0;
    PosicaoDiv[1][0] = 0;

    DesenhaCampo(Campo);
    AtualizaCampo(Campo);
    ColunasePortas(Campo,PosicaoPortas,NumPortasComodo,PosicaoDiv);
    AtualizaCampo(Campo);
    ColocaFrutas(Campo,PosicaoDiv,PosFrutaX,PosFrutaY,NumFrutas,NumPortasComodo);
	system("pause");
    EntraSaiPorta(Campo,PosicaoPortas,NumPortasComodo,&LinhaPac,&ColunaPac,&ContPassos,NumFrutas,PosFrutaY,PosFrutaX);

    printf("\nTotal de Passos: %d\n",ContPassos);
   
    return 0;
}
