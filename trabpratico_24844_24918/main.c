#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <unistd.h>
#include <time.h>
#include "main.h"

#define C 50	//Numero maximo de registos em ficheiro (50)
#define M 5     //Numero maximo de clientes

struct analista{
    char nome[100];
    char utilizador[20];
    char password[50];
}m;

typedef struct creditos {
    char cliente[100];
    char garantia[500];
    char iban[25];
    int credito;
    char prioridade[10];
}INFO;

typedef struct elemento{
    INFO *node;
    struct elemento *next;
    struct elemento *ant;
}ELEM;

typedef struct queue{
    ELEM *inicio;
    ELEM *fim;
}QUEUE;

int erro(){
    system("cls");
    system("COLOR 4F");
    printf("\n\n\t\t!!Opcao Invalida!!");
    sleep(1);
    system("COLOR F0");
    system("cls");
}

void lerCSV(){
    char line[200];
    char tamanhoCSV[100];
    char *token=NULL, *ptr=NULL;
     char prioridade[100];
     float montanteInferior;
     float montanteSuperior;
     int valorMaximo;
    int res = 0, i = 0;
    FILE *fp;

    while(fscanf(fp,"%s", tamanhoCSV)!= EOF){
        token=strtok(tamanhoCSV,";");
        strcpy(prioridade, token);
        token = strtok(NULL, ";");
        montanteInferior = strtoll(token, &ptr, 10);

        token = strtok(NULL, ";");
        montanteSuperior = strtoll(token, &ptr, 10);
    }

}

int loginAdmin(){
    system("cls");

    char login[100], senha[100];
    char a[C], ficheiro[C];
    int k = 0, g = 0;

    printf("\nLOGIN:\n");
    do{
        FILE *fp;
        printf("\nUltilizador: ");
        fflush(stdin);
        gets(login);
        sprintf(ficheiro, ".\\Administrador\\admin_%s.txt", login);	//Verifica o ficheiro que o contem
        fp = fopen(ficheiro,"r");	//Abre o ficheiro

        if(fp != NULL){	//se o nome existir e o ficheiro abrir
            printf("Password: ");
            gets(senha);

            while(fscanf(fp,"%s",a)!=EOF){
                //compara a string do nome no ficheiro
                if(strcmp(a,login) == 0){
                    k=1;	//se coincide atribui valor 1 ? var
                    break;
                }
            }

            while(fscanf(fp,"%s",a)!=EOF){
                //compara a string da pass no ficheiro
                if(strcmp(a,senha) == 0){
                    g=1;	//se coincide atribui valor 1 ? var
                    break;
                }
            }

            fclose(fp);	//fecha o ficheiro

            if(k==1&&g==1){		//Se ambas as vari?veis tiverem valor 1 ? enviado para o menu do medico
                printf("\n\t!!Bem Vindo!!");
                menuAdmin();
            }else{		//caso contrario volta a pedir os dados ate serem inseridos corretamente
                erro();
                loginAdmin();
            }
        }else{
            erro();
            loginAdmin();
        }
    }while(k != 1 && g != 1);	//1Repete enquanto os dados nao forem aceites
    return 0;
}

int loginAnalista(){
    system("cls");

    char login[100], senha[100];
    char a[C], ficheiro[C];
    char anal[100];
    int k = 0, g = 0;

    printf("\nLOGIN:\n");
    do{
        FILE *fp;
        printf("\nUtilizador: ");
        fflush(stdin);
        gets(login);
        sprintf(ficheiro, ".\\Analista\\analista_%s.txt", login);	//Verifica o ficheiro que o contem
        fp = fopen(ficheiro,"r");	//Abre o ficheiro

        if(fp != NULL){	//se o nome existir e o ficheiro abrir
            printf("Password: ");
            gets(senha);

            while(fscanf(fp,"%s",a)!=EOF){
                //compara a string do nome no ficheiro
                if(strcmp(a,login) == 0){
                    k=1;	//se coincide atribui valor 1 ? var
                    break;
                }
            }

            while(fscanf(fp,"%s",a)!=EOF){
                //compara a string da pass no ficheiro
                if(strcmp(a,senha) == 0){
                    g=1;	//se coincide atribui valor 1 ? var
                    break;
                }
            }

            fclose(fp);	//fecha o ficheiro

            if(k==1&&g==1){		//Se ambas as vari?veis tiverem valor 1 ? enviado para o menu do medico
                printf("\n\t!!Bem Vindo!!");
                strcpy(anal,login);
                menuAnalista(anal);
            }else{		//caso contrario volta a pedir os dados ate serem inseridos corretamente
                erro();
                loginAnalista();
            }
        }else{
            erro();
            loginAnalista();
        }
    }while(k != 1 && g != 1);	//Repete enquanto os dados nao forem aceites



    return 0;
}

int criarCredito(){
    ELEM *iniLista = NULL;
    ELEM *novo = NULL;
    INFO *credito = NULL;

    int op = -1;

    char ficheiro[C];
    char max[10], min[10], med[10];
    int maxM=0, maxm=0, minM=0, minm=0, medM=0, medm=0;

    novo = (ELEM *)malloc(sizeof(ELEM));
    credito = (INFO *)malloc(sizeof(INFO));

    if(iniLista == NULL){
        FILE * fp;

        printf("\nNome do cliente: ");
        fflush(stdin);
        gets(credito->cliente);

        printf("\nGarantia: ");
        fflush(stdin);
        gets(credito->garantia);

        printf("\nIban: ");
        fflush(stdin);
        gets(credito->iban);

        printf("\nCredito: ");
        scanf("%i", &(credito->credito));

        fp = fopen("prioridade.txt", "r");
        fscanf(fp, "%s %i %i %s %i %i %s %i %i", max, &maxm, &maxM, med, &medm, &medM, min, &minm, &minM);
        fclose(fp);

        if(credito->credito >= maxm && credito->credito <= maxM){
            strcpy(credito->prioridade,max);
            sprintf(ficheiro, ".\\Cliente\\Max\\cliente_%s.txt", credito->cliente);
            fp = fopen(ficheiro, "w");


            fprintf(fp, "%s\n%s\n%s\n%i\n%s\n", credito->cliente, credito->garantia, credito->iban,
                    credito->credito, credito->prioridade);
            fclose(fp);

            fp = fopen(".\\Cliente\\Max\\Clientes.txt", "a+");
            fprintf(fp, "\n%s", credito->cliente);
            fclose(fp);
        }else{
            if(credito->credito >= medm && credito->credito <= medM){
                strcpy(credito->prioridade,med);
                sprintf(ficheiro, ".\\Cliente\\Med\\cliente_%s.txt", credito->cliente);
                fp = fopen(ficheiro, "w");


                fprintf(fp, "%s\n%s\n%s\n%i\n%s\n", credito->cliente, credito->garantia, credito->iban,
                        credito->credito, credito->prioridade);
                fclose(fp);

                fp = fopen(".\\Cliente\\Med\\Clientes.txt", "a+");
                fprintf(fp, "\n%s", credito->cliente);
                fclose(fp);
            }else{
                if(credito->credito >= minm && credito->credito <= minM){
                    strcpy(credito->prioridade,min);
                    sprintf(ficheiro, ".\\Cliente\\Min\\cliente_%s.txt", credito->cliente);
                    fp = fopen(ficheiro, "w");
                    fprintf(fp, "%s\n%s\n%s\n%i\n%s\n", credito->cliente, credito->garantia, credito->iban, credito->credito, credito->prioridade);
                    fclose(fp);

                    fp = fopen(".\\Cliente\\Min\\Clientes.txt", "a+");
                    fprintf(fp, "\n%s", credito->cliente);
                    fclose(fp);
                }
            }
        }

        sprintf(ficheiro, ".\\Cliente\\cliente_%s.txt", credito->cliente);
        fp = fopen(ficheiro, "w");


        fprintf(fp, "%s\n%s\n%s\n%i\n%s\n", credito->cliente, credito->garantia, credito->iban,
                credito->credito, credito->prioridade);
        fclose(fp);

        fp = fopen(".\\Cliente\\Clientes.txt", "a+");
        fprintf(fp, "\n%s\n%s\n%s\n%i\n%s\n", credito->cliente, credito->garantia, credito->iban,
                credito->credito, credito->prioridade);
        fclose(fp);

        novo->node = credito;
        novo->next = iniLista;
        iniLista = novo;

        //aux->next =iniLista;
        //novo=NULL;
    }

    printf("\nDeseja Criar mais Creditos?\n");
    printf("1-SIM 2-NAO 0-SAIR");
    scanf("%i", &op);
    switch(op){
        case 1:{
            criarCredito();
            break;
        }
        case 2:{
            menuAdmin();
            break;
        }
        case 0:{
            printf("GOODBYE!!!");
            break;
        }
        default:{
            erro();
        }
    }

}

int consultarAnalista(){

    char ficheiro[C], nAnalista[100];
    char opConsulta;
    char d;
    char a[50], b[50], c[50];
    int cont = 0;

    printf("\nConsultar Analistas:\n");
    FILE*fp;

    fp=fopen(".\\Analista\\Analista.txt","r");
    do{
        d = fgetc(fp);
        printf("%c" , d);
    }while (d != EOF);
    fclose(fp);

    printf("\n\nAnalista a consultar: ");
    fflush(stdin);
    gets(nAnalista);
    sprintf(ficheiro, ".\\Analista\\analista_%s.txt", nAnalista);
    fp = fopen(ficheiro, "r");
    if(fp == NULL){
        erro();
    }else{
        fscanf(fp, "%s %s %s %i", a, b, c, &cont);
        printf("Nome: %s\nUtilizador: %s\nPass: %s\nContador: %i", a, b, c, cont);
    }
    fclose(fp);
    //sleep(2);
    do{
        printf("\n\nConsultar Analista: \n(S)im\n(N)ao\nOpcao: ");
        scanf("%c", &opConsulta);
        fflush(stdin);
        switch(opConsulta){
            case 'S':
            case 's':{
                consultarAnalista();
                //clrscr();
                break;
            }
            case 'N':
            case 'n':{//Voltar para o menu anterior

                menuAdmin();
                break;
            }
            default:{
                erro();
                break;
            }
        }

    }while(opConsulta != 'S' && opConsulta != 's' && opConsulta != 'N' && opConsulta != 'n');
}

int registarAnalista(){
    int k = 0;
    char a[C], ficheiro[C];
    char opConsulta;
    printf("\nRegisto de Analista:\n");
    FILE*fp;

    //Adicionar NOME do m?dico ao ficheiro
    printf("\nNome do Analista: ");
    fflush(stdin);
    gets(m.nome);

    //Adicionar NUMERO INTERNO do m?dico
    printf("\nNome de Ultilizador do Analista: ");
    gets(m.utilizador);

    fp = fopen(".\\Analista\\Analista.txt","r");

    while(fscanf(fp, "%s", a)!=EOF){

        //compara a string numero no ficheiro
        if(strcmp(a, m.utilizador) == 0){
            k = 1;	//se coincide atribui valor 1
            break;
        }
    }

    fclose(fp);

    if(k == 1){	//se a var tiver valor 1 d? erro pois ja exis1te o registo
        printf("\nNumero interno j? existe volte a tentar!\n");
        registarAnalista();
    }else{
        sprintf(ficheiro, ".\\Analista\\analista_%s.txt", m.utilizador);
        fp = fopen(ficheiro, "w");

        //Adicionar PASSWORD do analista
        printf("\nPASSWORD do Analista: ");
        gets(m.password);
        fprintf(fp, "%s\n%s\n%s\n0", m.nome,m.utilizador, m.password);
        fclose(fp);

        sprintf(ficheiro, ".\\Analista\\analisados_%s.txt", m.utilizador);
        fp = fopen(ficheiro, "w");
        fprintf(fp, "Creditos Analisados por %s:", m.utilizador);
        fclose(fp);

        //Insere nome e numero no ficheiro de pesquisa
        fp = fopen(".\\Analista\\Analista.txt","a+");
        fprintf(fp, "\n\nUtilizador: %s\nNome: %s\n", m.utilizador, m.nome);
        fclose(fp);
    }

    sleep(1);	//Espera 2 segundos para poder apresentar o menu seguinte
    do{
        system("cls");
        printf("\n\nRegistar Analista: \n(S)im\n(N)ao\nOpcao: ");
        scanf("%s", &opConsulta);
        switch(opConsulta){
            case 'S':
            case 's':{
                registarAnalista();
                break;
            }
            case 'N':
            case 'n':{
                menuAdmin();
                break;
            }
            default:{
                erro();
                break;
            }
        }
    }while(opConsulta != 'S' && opConsulta != 's' && opConsulta != 'N' && opConsulta != 'n');
    return 0;
}

void data(){
    struct tm *data_hora_atual;
    time_t segundos;
    time(&segundos);
    data_hora_atual = localtime(&segundos);

    printf("\n%d:%d:%d\n",data_hora_atual->tm_hour, data_hora_atual->tm_min, data_hora_atual->tm_sec);
    printf("\n%d/%d/%d\n", data_hora_atual->tm_mday, data_hora_atual->tm_mon+1, data_hora_atual->tm_year+1900);
}

void consultarCreditoPorAnalisar(char anal[]) {
    struct tm *data_hora_atual;
    time_t segundos;
    time(&segundos);
    data_hora_atual = localtime(&segundos);
    char cl[100], gar[100], ib[25], pri[10];
    int cre;
    int aceitar = 0;
    char motivo[200];
    char n[100];
    char a[50], b[50], c[50];
    int cont = 0;
    char d, opConsulta;
    char ficheiro[C];
    char max[10], min[10], med[10];
    int maxM = 0, maxm = 0, minM = 0, minm = 0, medM = 0, medm = 0;
    int rem = 0;

    printf("\nConsultar Creditos:\n");
    FILE *fp;

    fp = fopen(".\\Cliente\\Clientes.txt", "r");
    do {
        d = fgetc(fp);
        printf("%c", d);
    } while (d != EOF);
    fclose(fp);

    printf("\n\nCredito a consultar: ");
    fflush(stdin);
    gets(n);
    sprintf(ficheiro, ".\\Cliente\\cliente_%s.txt", n);

    if ((fp = fopen(ficheiro, "r")) == NULL) {
        erro();
    } else {
        fscanf(fp, "%s %s %s %i %s", cl, gar, ib, &cre, pri);
        printf("\n%s\n%s\n%s\n%i\n%s", cl, gar, ib, cre, pri);
    }
    fclose(fp);

    fp = fopen("prioridade.txt", "r");
    fscanf(fp, "%s %i %i %s %i %i %s %i %i", max, &maxm, &maxM, med, &medm, &medM, min, &minm, &minM);
    fclose(fp);

    if (cre >= maxm && cre <= maxM) {
        sprintf(ficheiro, ".\\Cliente\\Max\\cliente_%s.txt", n);
        rem = remove(ficheiro);

    } else {
        if (cre >= medm && cre <= medM) {
            sprintf(ficheiro, ".\\Cliente\\Med\\cliente_%s.txt", n);
            rem = remove(ficheiro);

        } else {
            if (cre >= minm && cre <= minM) {
                sprintf(ficheiro, ".\\Cliente\\Min\\cliente_%s.txt", n);
                rem = remove(ficheiro);
            }
        }
    }

    sprintf(ficheiro, ".\\Cliente\\cliente_%s.txt", n);
    rem = remove(ficheiro);

    printf("\nAceitar Credito?\n");
    printf("1-SIM 2-NAO");
    scanf("%i", &aceitar);
    printf("Motivo? \n");
    fflush(stdin);
    gets(motivo);


    switch (aceitar) {
        case 1: {
            FILE *fp;
            sprintf(ficheiro, ".\\Analisado\\Aceite\\cliente_%s.txt", n);
            fp = fopen(ficheiro, "w");
            fprintf(fp, "\n%s\n%s\n%s\n%i\n%s\nACEITE\n", cl, gar, ib, cre, pri);
            fprintf(fp, "\n%s\n", motivo);
            fclose(fp);
            fp = fopen(".\\Analisado\\analisado.txt", "a+");
            fprintf(fp, "\n%s\n%s\n%s\n%i\n%s\nACEITE\n", cl, gar, ib, cre, pri);
            fprintf(fp, "\n%s\n", motivo);
            fclose(fp);
            sprintf(ficheiro, ".\\Analista\\analisados_%s.txt", anal);
            fp = fopen(ficheiro, "a+");
            fprintf(fp, "%s\n%s\n%s\n%i\n%s\n%d/%d/%d\n%d:%d:%d\nACEITE\n", cl, gar, ib, cre, pri,
                    data_hora_atual->tm_mday, data_hora_atual->tm_mon+1, data_hora_atual->tm_year+1900,
                    data_hora_atual->tm_hour, data_hora_atual->tm_min, data_hora_atual->tm_sec);
            fprintf(fp, "\n%s\n", motivo);
            fclose(fp);
            break;
        }
        case 2: {
            FILE *fp;
            sprintf(ficheiro, ".\\Analisado\\Rejeitado\\cliente_%s.txt", n);
            fp = fopen(ficheiro, "w");
            fprintf(fp, "\n%s\n%s\n%s\n%i\n%s\nREJEITADO\n", cl, gar, ib, cre, pri);
            fprintf(fp, "\n%s\n", motivo);
            fclose(fp);
            fp = fopen(".\\Analisado\\analisado.txt", "a+");
            fprintf(fp, "\n%s\n%s\n%s\n%i\n%s\nREJEITADO\n", cl, gar, ib, cre, pri);
            fprintf(fp, "\n%s\n", motivo);
            fclose(fp);
            sprintf(ficheiro, ".\\Analista\\analisados_%s.txt", anal);
            fp = fopen(ficheiro, "a+");
            fprintf(fp, "%s\n%s\n%s\n%i\n%s\n%d/%d/%d\n%d:%d:%d\nREJEITADO\n", cl, gar, ib, cre, pri,
                    data_hora_atual->tm_mday, data_hora_atual->tm_mon+1, data_hora_atual->tm_year+1900,
                    data_hora_atual->tm_hour, data_hora_atual->tm_min, data_hora_atual->tm_sec);
            fprintf(fp, "\n%s\n", motivo);
            fclose(fp);
            break;
        }
        default: {
            erro();
        }
    }


    //sleep(2);
    do {
        printf("\n\nConsultar Credito: \n(S)im\n(N)ao\nOpcao: ");
        scanf("%c", &opConsulta);
        fflush(stdin);
        switch (opConsulta) {
            case 'S':
            case 's': {
                FILE *fp;
                sprintf(ficheiro, ".\\Analista\\analista_%s.txt", anal);
                fp = fopen(ficheiro, "r");
                fscanf(fp, "%s %s %s %i", a, b, c, &cont);
                fclose(fp);
                cont = cont + 1;
                fp = fopen(ficheiro, "w");
                fprintf(fp, "%s\n%s\n%s\n%i", a, b, c, cont);
                fclose(fp);
                consultarCreditoPorAnalisar(anal);
                //clrscr();
                break;
            }
            case 'N':
            case 'n': {//Voltar para o menu anterior

                menuAnalista();
                break;
            }
            default: {
                erro();
                break;
            }
        }

    } while (opConsulta != 'S' && opConsulta != 's' && opConsulta != 'N' && opConsulta != 'n');
}

void listarCreditosAnalisados() {

    char d;

    printf("\nListagem de Creditos Analisados:\n");
    FILE*fp;

    fp=fopen(".\\Analisado\\analisado.txt","r");
    do{
        d = fgetc(fp);
        fflush(stdin);
        printf("%c" , d);
    }while (d != EOF);
    fclose(fp);

    sleep(3);
    menuAnalista();
}

void listagemPrioridade(){
    int op = 0;
    char d;

    printf("\nQual Prioridade Deseja Consultar? ");
    printf("\n1 - MAXIMA\n2 - MEDIA\n3 - MINIMA\n4 - Voltar ao Menu\n0 - SAIR");
    printf("\n: ");
    scanf("%i", &op);

    switch(op){
        case 1:{
            FILE*fp;

            fp=fopen(".\\Cliente\\Max\\Clientes.txt","r");
            do{
                d = fgetc(fp);
                fflush(stdin);
                printf("%c" , d);
            }while (d != EOF);
            fclose(fp);

            sleep(2);
            listagemPrioridade();

            break;
        }
        case 2:{
            FILE*fp;

            fp=fopen(".\\Cliente\\Med\\Clientes.txt","r");
            do{
                d = fgetc(fp);
                fflush(stdin);
                printf("%c" , d);
            }while (d != EOF);
            fclose(fp);

            sleep(2);
            listagemPrioridade();

            break;
        }
        case 3:{
            FILE*fp;

            fp=fopen(".\\Cliente\\Min\\Clientes.txt","r");
            do{
                d = fgetc(fp);
                fflush(stdin);
                printf("%c" , d);
            }while (d != EOF);
            fclose(fp);

            sleep(2);
            listagemPrioridade();

            break;
        }
        case 4:{
            menuAnalista();
            break;
        }
        case 0:{
            printf("HAVE A GREAT DAY!!!");
            break;
        }
        default:{
            erro();
        }

    }

}

void listagemMontante(){    //NAO ESTA A FUNCIONAR!!!!
    int mon = 0;
    int i = 0;
    char d;
    char opConsulta;
    typedef struct montante{
        char cl[100], gar[100], ib[25], pri[10];
        int cre;
    }MON;

    MON cc[M];


    printf("Qual é o Montante? ");
    scanf("%i", &mon);

    FILE *fp;
    fp = fopen(".\\Cliente\\Clientes.txt", "r");

    do {
        d = fgetc(fp);
        fscanf(fp, "%s %s %s %i %s", cc[i].cl, cc[i].gar, cc[i].ib, &cc[i].cre, cc[i].pri);
        i++;
    }while(d != EOF);
    fclose(fp);

    for(i = 0;i < M; i++){
        if(cc[i].cre > mon){
            printf("%s\n", cc[i].cl);
        }
    }

    do {
        printf("\n\nVerificar outro Montante? \n(S)im\n(N)ao\nOpcao: ");
        scanf("%c", &opConsulta);
        fflush(stdin);
        switch (opConsulta) {
            case 'S':
            case 's': {
                listagemMontante();
                break;
            }
            case 'N':
            case 'n': {//Voltar para o menu anterior

                menuAnalista();
                break;
            }
            default: {
                erro();
                break;
            }
        }

    } while (opConsulta != 'S' && opConsulta != 's' && opConsulta != 'N' && opConsulta != 'n');
}

void listagemAnalista(){
    char d;
    char ficheiro[C];
    char n[50];
    char opConsulta;

    FILE*fp;
    fp=fopen(".\\Analista\\Analista.txt","r");
    do{
        d = fgetc(fp);
        printf("%c" , d);
    }while (d != EOF);
    fclose(fp);
    printf("De qual Analista pretende ver os Consultados? \n");
    fflush(stdin);
    gets(n);
    fflush(stdin);

    sprintf(ficheiro, ".\\Analista\\analisados_%s.txt", n);
    fp = fopen(ficheiro, "r");

    if(fp == NULL){
        erro();
    }else {
        do {
            d = fgetc(fp);
            printf("%c", d);
        } while (d != EOF);
    }

    do {
        printf("\n\nVerificar outro Analista? \n(S)im\n(N)ao\nOpcao: ");
        scanf("%c", &opConsulta);
        fflush(stdin);
        switch (opConsulta) {
            case 'S':
            case 's': {
                listagemAnalista();
                break;
            }
            case 'N':
            case 'n': {//Voltar para o menu anterior

                menuAnalista();
                break;
            }
            default: {
                erro();
                break;
            }
        }

    } while (opConsulta != 'S' && opConsulta != 's' && opConsulta != 'N' && opConsulta != 'n');

}

void relatorio(){
    int i = 0;
    int j = 0;
    char ler[100];
    char d;
    char opConsulta;
    typedef struct montante{
        char cl[100], gar[100], ib[25], pri[10], par[10];
        char mot[100];
        int cre;
    }MON;

    MON cc[M];
    MON mon[M];

    FILE *fp;
    fp = fopen(".\\Analisado\\analisado.txt", "r");


    while(!feof(fp)){
        fgets(ler, 100,fp);
        //printf("%i - %s", i,ler);
        if(i == 1+(8*j)){
            strcpy(cc[j].cl, ler);
            //printf("%s", cc[j].cl);
        }
        if(i == 2+(8*j)){
            strcpy(cc[j].gar, ler);
            //printf("%s", cc[j].gar);
        }
        if(i == 3+(8*j)){
            strcpy(cc[j].ib, ler);
            //printf("%s", cc[j].ib);
        }
        if(i == 4+(8*j)){
            cc[j].cre = atoi(ler);
            //printf("%i", cc[j].cre);
        }
        if(i == 5+(8*j)){
            strcpy(cc[j].pri, ler);
            //printf("%s", cc[j].pri);
        }
        if(i == 6+(8*j)){
            strcpy(cc[j].par, ler);
            //printf("%s", cc[j].par);
        }
        if(i == 7+(8*j)){
            strcpy(cc[j].mot, ler);
            //printf("%s", cc[j].mot);
        }
        i++;
        if(i % 8 == 0){
            j++;
        }
    }
    fclose(fp);

    for(i = 0; i < M; i++){
        for(j = i+1; j < M; j++){
            if(cc[i].cre < cc[j].cre){
                mon[0]=cc[i];
                cc[i]=cc[j];
                cc[j]=mon[0];
            }
        }
    }
    for(i = 0; i < M; i++){
        printf("%s %s %s %i\n%s %s %s\n\n", cc[i].cl, cc[i].gar, cc[i].ib, cc[i].cre, cc[i].pri, cc[i].par, cc[i].mot);
    }

    sleep(2);
    menuAnalista();

}

int menuAnalistaAdmin() {
    int opMenu = -1;

    printf("\n\n\tMenu Analista para Admin\n "
           "\n1 - Verificar Créditos por Analisar"
           "\n2 - Listagem de Créditos Analisados"
           "\n3 - Listagem por Prioridade"
           "\n4 - Listagem por Montante"
           "\n5 - Listagem por Analista"
           "\n6 - Relatorio"
           "\n0 - Sair"
           "\n: ");
    scanf("%i", &opMenu);


    switch (opMenu) {
        case 1: {
            printf("\nEsta opcao so é valida para analista!!!\n");
            menuAnalistaAdmin();
            break;
        }
        case 2:{
            listarCreditosAnalisados();
            break;
        }
        case 3:{
            listagemPrioridade();
            break;
        }
        case 4:{
            listagemMontante();
            break;
        }
        case 5:{
            listagemAnalista();
            break;
        }
        case 6:{
            relatorio();
            break;
        }
        case 0: {
            printf("\n\n\t\tGOODBYE");
            sleep(2);
            break;
        }
        default: {
            erro();
            break;
        }

    }
}

void registarAdmin(){
    char ficheiro[C];
    char opConsulta;
    printf("\nRegisto de Admin:\n");
    FILE*fp;

    //Adicionar NOME do m?dico ao ficheiro
    printf("\nNome do Admin: ");
    fflush(stdin);
    gets(m.nome);

    //Adicionar NUMERO INTERNO do m?dico
    printf("\nNome de Ultilizador do Admin: ");
    gets(m.utilizador);

        sprintf(ficheiro, ".\\Administrador\\admin_%s.txt", m.utilizador);
        fp = fopen(ficheiro, "w");

        //Adicionar PASSWORD do analista
        printf("\nPASSWORD do Admin: ");
        gets(m.password);
        fprintf(fp, "Nome: %s\nUtilizador: %s\nPass: %s", m.nome,m.utilizador, m.password);
        fclose(fp);

    sleep(1);	//Espera 2 segundos para poder apresentar o menu seguinte
    do{
        system("cls");
        printf("\n\nRegistar Admin: \n(S)im\n(N)ao\nOpcao: ");
        scanf("%s", &opConsulta);
        switch(opConsulta){
            case 'S':
            case 's':{
                registarAdmin();
                break;
            }
            case 'N':
            case 'n':{
                menuAdmin();
                break;
            }
            default:{
                erro();
                break;
            }
        }
    }while(opConsulta != 'S' && opConsulta != 's' && opConsulta != 'N' && opConsulta != 'n');
}

void removerAnalista(){
    char ficheiro[C];
    int rem1 = 0;
    int rem2 = 0;
    char nome[100];
    char opConsulta;

    printf("Qual e o Analista que Dejesa remover? ");
    scanf("%s", nome);

    sprintf(ficheiro, ".\\Analista\\analista_%s.txt", nome);
    rem1 = remove(ficheiro);

    sprintf(ficheiro, ".\\Analista\\analisados_%s.txt", nome);
    rem2 = remove(ficheiro);

    if(rem1 == 0 && rem2 == 0){
        printf("\nFicheiros Removidos com Sucesso!!!\n");
    }else{
        erro();
    }

    do{
        system("cls");
        printf("\n\nRemover Analista: \n(S)im\n(N)ao\nOpcao: ");
        scanf("%s", &opConsulta);
        switch(opConsulta){
            case 'S':
            case 's':{
                removerAnalista();
                break;
            }
            case 'N':
            case 'n':{
                menuAdmin();
                break;
            }
            default:{
                erro();
                break;
            }
        }
    }while(opConsulta != 'S' && opConsulta != 's' && opConsulta != 'N' && opConsulta != 'n');
}

void removerCredito(){
    char ficheiro[C];
    int rem = 0;
    int rem1, rem2, rem3;
    char nome[100];
    char opConsulta;

    printf("Qual e o Credito que Dejesa remover? \n: ");
    scanf("%s", nome);

    sprintf(ficheiro, ".\\Cliente\\cliente_%s.txt", nome);
    rem = remove(ficheiro);

    sprintf(ficheiro, ".\\Cliente\\Max\\cliente_%s.txt", nome);
    rem1 = remove(ficheiro);
    sprintf(ficheiro, ".\\Cliente\\Min\\cliente_%s.txt", nome);
    rem3 = remove(ficheiro);
    sprintf(ficheiro, ".\\Cliente\\Med\\cliente_%s.txt", nome);
    rem2 = remove(ficheiro);

    if(rem == 0){
        printf("\nFicheiro Removido com Sucesso!!!\n");
    }else{
        erro();
    }

    do{
        system("cls");
        printf("\n\nRemover Credito: \n(S)im\n(N)ao\nOpcao: ");
        scanf("%s", &opConsulta);
        switch(opConsulta){
            case 'S':
            case 's':{
                removerCredito();
                break;
            }
            case 'N':
            case 'n':{
                menuAdmin();
                break;
            }
            default:{
                erro();
                break;
            }
        }
    }while(opConsulta != 'S' && opConsulta != 's' && opConsulta != 'N' && opConsulta != 'n');
}

int menuAdmin(){
    int opMenu=-1;
    printf("\n\n\tMenu Admin\n "
           "\n1 - Registrar Analista"
           "\n2 - Verificar Analistas"
           "\n3 - Criar Credito"
           "\n4 - Menu Analista"
           "\n5 - Registar Admin"
           "\n6 - Remover Analistas"
           "\n7 - Remover Creditos"
           "\n0 - Sair"
           "\n: ");
    scanf("%i", &opMenu);


    switch(opMenu){
        case 1:{
            registarAnalista();
            break;
        }
        case 2:{
            consultarAnalista();
            break;
        }
        case 3:{
            criarCredito();
            break;
        }
        case 4:{
            menuAnalistaAdmin();
        }
        case 5:{
            registarAdmin();
            break;
        }
        case 6:{
            removerAnalista();
            break;
        }
        case 7:{
            removerCredito();
            break;
        }
        case 0:{
            printf("\n\n\t\tGOODBYE");
            sleep(2);
            break;
        }
        default:{
            erro();
            break;
        }

    }

    return 0;
}


int menuAnalista(char anal[]) {
    int opMenu = -1;
    int cont = 0;
    char a[50], b[50], c[50];
    char ficheiro[C];

    printf("\n\n\tMenu Analista\n "
           "\n1 - Verificar Créditos por Analisar"
           "\n2 - Listagem de Créditos Analisados"
           "\n3 - Listagem por Prioridade"
           "\n4 - Listagem por Montante"
           "\n5 - Listagem por Analista"
           "\n6 - Relatorio"
           "\n0 - Sair"
           "\n: ");
    scanf("%i", &opMenu);


    switch (opMenu) {
        case 1: {
            FILE *fp;
            sprintf(ficheiro, ".\\Analista\\analista_%s.txt", anal);
            fp = fopen(ficheiro, "r");
            fscanf(fp, "%s %s %s %i", a, b, c, &cont);
            fclose(fp);
            cont = cont + 1;
            fp = fopen(ficheiro, "w");
            fprintf(fp, "%s\n%s\n%s\n%i", a, b, c, cont);
            fclose(fp);
            consultarCreditoPorAnalisar(anal);
            break;
        }
        case 2:{
            listarCreditosAnalisados();
            break;
        }
        case 3:{
            listagemPrioridade();
            break;
        }
        case 4:{
            listagemMontante();
            break;
        }
        case 5:{
            listagemAnalista();
            break;
        }
        case 6:{
            relatorio();
            break;
        }
        case 0: {
            printf("\n\n\t\tGOODBYE");
            sleep(2);
            break;
        }
        default: {
            erro();
            break;
        }

    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    system("COLOR F0");
    char anal[100];
    int opMenu;
    ELEM *iniLista = NULL;

    data();

    setbuf(stdout, 0);
    printf("*****************************************\n"
           "|\t\tBEM-VINDO\t\t|\n"
           "|\t\t\t\t\t|\n"
           "|\t\tPressione:\t\t|\n"
           "|\t\t1 - Administrador\t|\n"
           "|\t\t2 - Analista\t\t|\n"
           "|\t\t0 - Sair\t\t|\n"
           "*****************************************"
           "\n:");
    scanf("%i", &opMenu);


    switch (opMenu) {
        case 1: {
            loginAdmin();
            break;
        }
        case 2: {
            loginAnalista();

            break;
        }
        case 0: {
            printf("\n\n\t\tBye !!!");
            break;
        }
        default: {
            erro();
            break;
        }
    }

    return 0;
}

