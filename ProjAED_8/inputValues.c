/*--------------------------------------------------*/
/*####          PROGRAMACAO EM C	       	    ####*/
/*--------------------------------------------------*/
/*$$$$ INPUT VALUES	(implementacao)        		$$$$*/
/*$$$$ nome : inputValues.c			          	$$$$*/ 
/*$$$$ autor: Salvador Lima      		        $$$$*/
/*--------------------------------------------------*/
/*@@@@ DIRECTIVAS DE INCLUSAO         		    @@@@*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULO '\0'

char carater(char mensagem[]) {
	char carater;
	
	printf("%s", mensagem);
	
	fflush(stdin);
	scanf("%c", &carater);
	fflush(stdin);
	
	return carater;
}

int inteiro(char mensagem[]) {
	int inteiro;
	
	printf("%s", mensagem);

	scanf("%i", &inteiro);

	
	return inteiro;
}

float real(char mensagem[]) {
	float real;
	
	printf("%s", mensagem);
		
	scanf("%f", &real);
	
	return real;
}

void sequencia(char mensagem[], char cadeia[], int tamanho) {
	printf("%s", mensagem);
	
	fflush(stdin);
	fgets(&cadeia[0], tamanho, stdin);
	fflush(stdin);	
		
	cadeia[(strlen(&cadeia[0]) == (tamanho - 1)) ? (!isprint(cadeia[strlen(&cadeia[0]) - 1]) ? strlen(&cadeia[0]) - 1 : tamanho - 1) : strlen(&cadeia[0]) - 1] = NULO;
}

void pausa() {
	char tecla;
	
	printf("%s", "\n\n\tPremir a tecla 0 para SAIR/CONTINUAR...");
	
	do {
		fflush(stdin);
		tecla = getch();
		if(tecla == '0')
			break;
	} while(1);
	
	printf("\n");
}

void linha() {
	printf("\n");
}
/*--------------------------------------------------*/
