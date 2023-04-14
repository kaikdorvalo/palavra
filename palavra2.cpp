#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#define tam 25
#define maxpal 100

FILE *arqpal;
int qpal=0;
char palavras[maxpal][20];
char palavrasorteada[20];
int resultado;
int Py,Px;

bool abreArquivo();
void leArquivo();
void mostraPalavras();

char pal[tam][tam];
char palavraDigitada[26];

void sorteia();
void sorteiaPosicao();
void mostra();
void inserirPalavra();
int procuraDireita();
int procuraEsquerda();
int procuraCima();
int procuraBaixo();
int procura();
void compara(char aux[26],char palavraDigitada[26],int *encontrou);

//---------------------------------------------
int main () {
  setlocale(LC_ALL,"portuguese");
  srand(time(NULL));
  
  if (abreArquivo()==0)
     return 0;
  leArquivo();
  strcpy(palavrasorteada,palavras[rand()%maxpal]);

  sorteia();
  sorteiaPosicao();
  inserirPalavra();
  do {
  	do {
  		system("cls");
  		printf("Palavra: %s  Linha: %i Coluna: %i \n\n",palavrasorteada,Py,Px);
  		mostra();
  		printf("\nDite a palavra: ");
		gets(palavraDigitada);	
	} while (strlen(palavraDigitada)==0);
  	strupr(palavraDigitada);
  	resultado=procura();
  	if (resultado>0) {
  		printf("Palavra %s foi encontrada! \n", palavraDigitada);
  		system("pause");  		
	}
  	else {
   		printf("Palavra não encontrada\n");
  		system("pause"); 		
	}
  	system("cls");
  } while(true);
  system("pause");
  return 0;
}
//---------------------------------------------
void sorteia(){
  char vog[6]="AEIOU";
  char con[22]="BCDFGHJKLMNPQRSTVXWYZ";
  int cont=1;
  //A=65   Z=90
  for (int x=0; x<tam; x++)
    for (int y=0; y<tam; y++){
      if (cont==1 || cont==3)
      { 
         pal[x][y]=vog[rand()%5];
      }   
      else
      {
         pal[x][y]=con[rand()%21];
      }   
      cont++;
      if (cont>3)
      {
        cont=1;
      }  
    }      
}

//---------------------------------------------
void mostra(){
  for (int x=0; x<tam; x++){
     for (int y=0; y<tam; y++)
        printf("%c ",pal[x][y]);
     printf("\n");   
  }   
}
//----------------------------------------------
bool abreArquivo(){
  arqpal = fopen("palavras.txt", "r"); //leitura
  if (arqpal == NULL)
  {  // Se houve erro na leitura do arquivo
     printf("Problemas na leitura do arquivo\n");
     system("pause");
     return 0; //nÃ£o conseguiu abrir o arquivo
  }   
  else
  {
     fclose(arqpal);
     return 1; //conseguiu abrir o arquivo
  }   
}
//-----------------------------------------------
void leArquivo(){
   arqpal = fopen("palavras.txt", "r"); //leitura
   qpal=0;
   while (!feof(arqpal))
   {
      //fgets(string,tamanho,arquivo)
      fgets(palavras[qpal],20,arqpal);
      palavras[qpal][strlen(palavras[qpal])-1]='\0';
      qpal++;
   }
   fclose(arqpal);
}
//------------------------------------------------
void mostraPalavras(){
for (int x=0; x<qpal; x++){
     printf("%s\n",palavras[x]);
  }    
  system("pause");
}
//-------------------------------------------------
void inserirPalavra(){
    int sentido=rand()%4;
    int tamanho=strlen(palavrasorteada);
    int Px2,Py2;
    switch (sentido) {
        case 0: //para a direita
            if (tamanho+Px>tam-1) {
            	Px=tam-tamanho;                                 
            }    
            Px2=Px;
			Py2=Py;
            for(int x=0;x<tamanho;x++) {
                pal[Py2][Px2]=palavrasorteada[x];
                Px2++;
            }
            break;
        case 1: // para esquerda
            if (Px-tamanho<0){
                Px=tamanho-1;
            }
            Px2=Px;
			Py2=Py;
            for (int x=0;x<tamanho;x++) {
                pal[Py2][Px2]=palavrasorteada[x];
                Px2--;
            }
            break;
        case 2: //para cima
            if (Py-tamanho<0){
            	Py=tamanho-1;
            }
            Px2=Px;
			Py2=Py;
            for (int x=0;x<tamanho;x++) {
                pal[Py2][Px2]=palavrasorteada[x];
                Py2--;
            }
            break;
        case 3: // para baixo
            if (tamanho+Py>tam-1) {
            	Py=tam-tamanho;
            }
            Px2=Px;
			Py2=Py;
            for (int x=0;x<tamanho;x++) {
                pal[Py2][Px2]=palavrasorteada[x];
                Py2++;   
            }    
            break;   
    }   
}
//-----------------------------------------------------------------------
void sorteiaPosicao() {
	Py=rand()%tam;
    Px=rand()%tam;
}

void compara(char aux[26],char palavraDigitada[26],int *encontrou) {
	if (strstr(aux,palavraDigitada)!=NULL)
		*encontrou=1;
}
//-----------------------------------------------------------------------
int procuraDireita() {
	int encontrou=0;
	for (int x=0;x<tam;x++)
		compara(pal[x],palavraDigitada,&encontrou);
	return encontrou;
}
//-----------------------------------------------------------------------
int procuraEsquerda() {
	int encontrou=0;
	char aux[26];
	for (int x=0;x<tam;x++) {
		int cont=tam-1;
		for (int y=0;y<tam;y++) {
			aux[cont]=pal[x][y];
			cont--;
		}
		aux[26]='\0';
		compara(aux,palavraDigitada,&encontrou);
	}
	return encontrou;
}
//-----------------------------------------------------------------------
int procuraCima() {
	int encontrou=0;
	char aux[26];
	for (int x=0;x<tam;x++) {
		int cont=tam-1;
		for (int y=0;y<tam;y++) {
			aux[cont]=pal[y][x];
			cont--;
		}
		aux[26]='\0';
		compara(aux,palavraDigitada,&encontrou);
	}
	return encontrou;
}
//-----------------------------------------------------------------------
int procuraBaixo() {
	int encontrou=0;
	char aux[26];
	for (int x=0;x<tam;x++) {
		for (int y=0;y<tam;y++)
			aux[y]=pal[y][x];
		aux[26]='\0';
		compara(aux,palavraDigitada,&encontrou);
	}
	return encontrou;
}
//-----------------------------------------------------------------------
int procura() {
	int encontrou=0;
	encontrou+=procuraDireita();
	encontrou+=procuraEsquerda();
	encontrou+=procuraCima();
	encontrou+=procuraBaixo();
	return encontrou;
}
