/*--------------------------------------------------*/
/*####          PROGRAMACAO EM C                ####*/
/*--------------------------------------------------*/
/*$$$$ APLICACAO                                $$$$*/
/*$$$$ nome : aplicacao<XX>.c                   $$$$*/ 
/*$$$$ autor: João Amorim,Lucas Oliveira,Nelson Novais$$$$*/
/*--------------------------------------------------*/
/*@@@@ DIRECTIVAS DE INCLUSAO                   @@@@*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "inputValues.c"
#define C 50

/*@@@@ DIRECTIVAS DE DEFINCAO                   @@@@*/


/*@@@@ VARIAVEIS GLOBAIS                        @@@@*/
int i;
int t;

/*@@@@ ESTRUTURAS                               @@@@*/
struct sessao{
	char nome[100];
	int id;
	char pass[50];
	char especialidade[50];
	int nExperiencia;
	int salario;
	int teleMedico;
	char localMedico[100];
	char removerFicheiro[100];
	int remove;
};
struct utente{
	char nomeUtente[100];
	int nPaciente;
	int idade;
	char sexo[50];
	char localUtente[100];
	char ProblSaude[100];
	char SituacaoClinica[100];
	char nomedoMedico[100];
	int teleUtente;
	char datada1Consulta[20];
	char dadtadaUltimaConsulta[20];
	char datadaProximaConsulta[20];
	char medicamento[200];
	char receitaUtente[100];
	char motivoFalta[300];
	char dataFalta[20];
	char password[50];
	char relatorioClinico[1000];
	char nomeInternamento[100];
	char nomeJustificacao[100];
};

/*@@@@ FUNCOES E PROCEDIMENTOS                  @@@@*/
void erroUtilizador(int t){
	system("color 4f");			// Ecrã vermelho com letras brancas
	printf("\n\tUtilizador não permitido!");
	t = 0;
	do{							// Ciclo de espera, para mim demora 4 segundos 
		t++;					// Até o t igualar 999999999 o ecrã ficará vermelho e dirá a mensagem "Utilizador não permitido!" em branco
	}while(t < 999999999);
	system("color f0");			// Ecrã branco com letras pretas
	system("cls");				// Limpar tudo do ecrã (para recomeçar um ciclo sem dizer os valores errados nem a mensagem "Utilizador não permitido!")
	printf("\n");
}

void erroOpcao(int t){
	system("color 4f");			// Ecrã vermelho com letras brancas
	printf("\n\tOpção Inválida!");
	t = 0;
	do{							// Ciclo de espera, para mim demora 4 segundos 
		t++;					// Até o t igualar 999999999 o ecrã ficará vermelho e dirá a mensagem "Utilizador não permitido!" em branco
	}while(t < 999999999);
	system("color f0");			// Ecrã branco com letras pretas
	system("cls");				// Limpar tudo do ecrã (para recomeçar um ciclo sem dizer os valores errados nem a mensagem "Utilizador não permitido!")
	printf("\n");
}

void admin(char login[100], char ficheiro[C], char a[50], int k, char senha[100], int g ){
	do{
		FILE*fp;
		
		
		k=0;g=0;
		sequencia("\nIntroduza o Username: ", login, 100);
		fp = fopen("admin.txt", "r");
		if(fp != NULL){
			
			sequencia("\nIntroduza a Password: ", senha,100);
			
			
			while(fscanf(fp,"%s",a)!=EOF){
				if(strcmp(a,login) == 0){
					k=1;
					break;
				}
			}
			fclose(fp);
			
			
			
			fp = fopen("admin.txt","r");
			while(fscanf(fp,"%s",a)!=EOF){
				if(strcmp(a,senha) == 0){
					g=1;
					break;
				}
			}
			fclose(fp);
			if(k==1&&g==1){
				printf("\nBem-Vindo!");
			}
			else{
				erroUtilizador(t);
			}
			printf("\n\n\n");
		}
		else{
			erroUtilizador(t);
		}
	}while(k != 1 && g != 1);
}

void menuAdmin(int opcaoAdmin, char opcaoCovid,struct sessao c, char ficheiro[C], char w[100], char x[100]){
	do{
		printf("\n\n");
		printf("\t|*********************************|\n"
			   "\t|****          ADMIN         ****|\n"
	           "\t|*********************************|\n"
	           "\t|****    1 - Inserir Médico   ****|\n"
	           "\t|****    2 - Listar Médicos   ****|\n"
	           "\t|****    3 - Remover          ****|\n"
               "\t|****    0 - SAIR             ****|\n"
	           "\t|*********************************|\n");
	           
	         printf("\nSelecione a sua opção: ");
			 scanf("%d", &opcaoAdmin);
			 
			 switch(opcaoAdmin){
			 	case 1:{
			 		FILE*fp;
			 		printf("\nÉ especializado em covid-19?(S)im/(N)ão: ");
			 		scanf("%s", &opcaoCovid);
			 		
			 		switch(opcaoCovid){
			 			case 'S':
			 			case 's':{
			 			sequencia("\nIntroduza o nome do médico: ", c.nome, 50);
			 			c.id = inteiro("\nIntroduza o nº interno do médico: ");
                        sequencia("\nIntroduza a password do médico: ",c.pass, 50);
                        sequencia("\nIntroduza a localidade do médico: ", c.localMedico, 100);
                        c.nExperiencia = inteiro("\nIntroduza o nº de anos de Experiência: ");
                        c.salario = inteiro("\nIntroduza o valor do salário: ");
                        c.teleMedico = inteiro("\nIntroduza o contacto telefónico do médico: ");
			 			sprintf(ficheiro, ".\\Medico\\medico_%s.txt", c.nome);
						fp = fopen(ficheiro, "w");
			 			
			 			fprintf(fp, "\nNome: %s\nNº: %d\nPassword: %s\nEspecialidade: Covid-19\nLocalidade: %s"
						 "\nExperiência: %d\nSalario: %d\nTelefone: %d", c.nome, c.id, c.pass, c.localMedico, c.nExperiencia, c.salario, c.teleMedico);
						fprintf(fp, "\n");	
						fclose(fp);
						fp= fopen(".\\Medico\\MedicoCovid.txt", "a");
						fprintf(fp,"\n%s\n%d", c.nome, c.id);
						fclose(fp);
						break;
						}
					 	case 'N':
						case 'n':{
					 	sequencia("\nIntroduza o nome do médico: ", c.nome, 50);
					 	c.id = inteiro("\nIntroduza o nº interno do médico: ");
					 	sequencia("\nIntroduza a especialidade do médico: ", c.especialidade, 50);
                        sequencia("\nIntroduza a password do médico: ",c.pass, 50);
                         sequencia("\nIntroduza a localidade do médico: ", c.localMedico, 100);
                        c.nExperiencia = inteiro("\nIntroduza o nº de anos de Experiência: ");
                        c.salario = inteiro("\nIntroduza o valor do salário: ");
                        c.teleMedico = inteiro("\nIntroduza o contacto telefónico do médico: ");
					 	sprintf(ficheiro, ".\\Medico\\medico_%s.txt", c.nome);
						fp = fopen(ficheiro, "w");
			 			fprintf(fp, "\nNome: %s\nNº: %d\nPassword: %s\nEspecialidade: %s\nLocalidade: %s"
						 "\nExperiência: %d\nSalario: %d\nTelefone: %d", c.nome, c.id, c.pass,c.especialidade, c.localMedico, c.nExperiencia, c.salario, c.teleMedico);
			 			
						fprintf(fp, "\n");	
						fclose(fp);
						fp= fopen(".\\Medico\\MedicoNormal.txt", "a");
						fprintf(fp,"\n%s\n%d", c.nome, c.id);
					    fclose(fp);
					 	break;
					 }
					 default:{
					 	erroOpcao(t);
					 	break;
				}
		}
	}
				
				 case 2:{
				 	FILE*fp;
				 	printf("\n");
				 	printf("\tMédicos Covid Registados no sistema: ");
				 	fp = fopen(".\\Medico\\MedicoCovid.txt", "r");
				 	if(fp != NULL){
				 		fread(w, sizeof(w), 100, fp);
				 		printf("\n%s\n", w);
				 		printf("\n\n");
				 	}
					fclose(fp);
					
					printf("\tMédicos Normais Registados no Sistema: ");
				 	fp = fopen(".\\Medico\\MedicoNormal.txt", "r");
				 	if(fp != NULL){
				 		fread(x, sizeof(x), 100, fp);
				 		printf("\n%s\n", x);
				 		printf("\n\n");
					}
					fclose(fp);
					break;
				 }
				  case 3:{
				 	do{
					 
					 	 printf("\t|*********************************|\n"
			                  	"\t|****          ADMIN         ****|\n"
	          					"\t|*********************************|\n"
	           					"\t|****    1 - Remover Médico   ****|\n"
	           					"\t|****    2 - Remover Utente   ****|\n"
	           					"\t|****    3 - Remover Justificação |\n"
	           					"\t|****    4 - Remover Receita  ****|\n"
	           					"\t|****    5 - Remover Relatório****|\n"
               					"\t|****    0 - SAIR             ****|\n"
	          				 	"\t|*********************************|\n");
				 	c.remove = inteiro("\nOpcão: ");
				 	switch(c.remove){
				 		case 1:{
				 			sequencia("\nNome da Pessoa a remover: ", c.removerFicheiro, 100);
				 			sprintf(ficheiro, ".\\Medico\\medico_%s.txt", c.removerFicheiro);
                    
   					if (remove(ficheiro) == 0) 
      					printf("\nFicheiro Removido com sucessso"); 
                    else
                        printf("\nFicheiro Não Removido"); 

							break;
						 }
						case 2:{
							sequencia("\nNome da Pessoa a remover: ", c.removerFicheiro, 100);
				 			sprintf(ficheiro, ".\\Utente\\Utente_%s.txt", c.removerFicheiro);
                    
   					if (remove(ficheiro) == 0) 
      					printf("\nFicheiro Removido com sucessso"); 
                    else
                        printf("\nFicheiro Não Removido"); 
							break;
						}
						case 3:{
							sequencia("\nNome da Pessoa a remover: ", c.removerFicheiro, 100);
				 			sprintf(ficheiro, ".\\Justificacao\\Utente_%s.txt", c.removerFicheiro);
                    
   					if (remove(ficheiro) == 0) 
      					printf("\nFicheiro Removido com sucessso"); 
                    else
                        printf("\nFicheiro Não Removido"); 
							break;
						}
						case 4:{
							sequencia("\nNome da Pessoa a remover: ", c.removerFicheiro, 100);
				 			sprintf(ficheiro, ".\\Receitas\\Utente_%s.txt", c.removerFicheiro);
                    
   					if (remove(ficheiro) == 0) 
      					printf("\nFicheiro Removido com sucessso"); 
                    else
                        printf("\nFicheiro Não Removido");
							break;
						}
						case 5:{
							sequencia("\nNome da Pessoa a remover: ", c.removerFicheiro, 100);
				 			sprintf(ficheiro, ".\\Relatorio\\Utente_%s.txt", c.removerFicheiro);
                    
   					if (remove(ficheiro) == 0) 
      					printf("\nFicheiro Removido com sucessso"); 
                    else
                        printf("\nFicheiro Não Removido");
							break;
						}
					 }
				}while(c.remove!=0);
			}
		} 
	}while(opcaoAdmin != 0);
} 

/*void medico(int opcaoMedico, int idMedico){
	do{
		printf("\n\n");
		printf("\t|*********************************|\n"
			   "\t|****          Médico         ****|\n"
	           "\t|*********************************|\n"
	           "\t|****    1 - Iniciar Sessão   ****|\n"
               "\t|****    0 - SAIR             ****|\n"
	           "\t|*********************************|\n");


			printf("\nSelecione a opcão: ");
			scanf("%d", &opcaoMedico);
		
		if(opcaoMedico == 1){
			printf("\nIntroduza o seu ID: ");
			scanf("%d", idMedico);
		}	
	}while(opcaoMedico != 0);
}*/
void iSessaoMedico(char userm[100], char passm[100], char str1[100], char str2[100], int k, int g, char a[50], char ficheiro[C]){
	do{
	    FILE *fp;
	

	    k=0;g=0;
		sequencia("\n\tNome do utilizador: ", userm, 100);
	    sprintf(ficheiro, ".\\Medico\\medico_%s.txt", userm);
		fp = fopen(ficheiro,"r");
		if(fp != NULL){

			sequencia("\n\tPassword: ", passm, 100);
		
			while(fscanf(fp,"%s",a)!=EOF){
		        if(strcmp(a,userm) == 0){
			        k=1;
			        break;
		        }
		    }
		    fclose(fp);
		    
		    fp = fopen(ficheiro,"r");
		    while(fscanf(fp,"%s",a)!=EOF){
		        if(strcmp(a,passm) == 0){
			        g=1;
			        break;
		        }
		    }
		    fclose(fp);
			if(k==1&&g==1){
			    printf("\n\n\tBem Vindo!!!");
		    }
		    else{
			    printf("\n");

		    }
		    printf("\n");

		}
		else{
			printf("\n");
		}
	}while(k != 1 && g != 1);
}
void menuMedico(int opcaoMedico, struct utente m , char ficheiro[C], char doenteCovid, char w[100], char z[100],char q[100] ,
				char nomeUtenteListar[100], char a[50], int k, char y[50], int s, char h[100]){
    do{
    	printf("\n\n");
		printf("\t|*********************************************************|\n"
			   "\t|****                      Médico                     ****|\n"
	           "\t|*********************************************************|\n"
	           "\t|****  1 - Inserir Paciente                           ****|\n"
               "\t|****  2 - Listar Pacientes                           ****|\n"
               "\t|****  3 - Emitir Receita                             ****|\n"
               "\t|****  4 - Emitir Internamento                        ****|\n"
               "\t|****  5 - Justificação                               ****|\n"
               "\t|****  6 - Relatório Clínico                          ****|\n"
               "\t|****  7 - Consultar informações de outras consultas  ****|\n"
               "\t|****  0 - Sair                                       ****|\n"
	           "\t|*********************************************************|\n");
	    
	    opcaoMedico = inteiro("\nEscolha a sua opção: ");
	    switch(opcaoMedico){
	    	case 1:{
	    	FILE*fp;
	    	    printf("\nDoente Covid-19?(S)im ou (N)ão: ");
	    	    scanf("%s", &doenteCovid);
	    	    switch(doenteCovid){
				
				case 'N':
				case 'n':{
					
					
				sequencia("\nNome do Paciente: ", m.nomeUtente, 100);
				sequencia("\nPassword: ", m.password, 50);
				sequencia("\nSexo: ", m.sexo, 50);
				m.idade = inteiro("\nIdade: ");
				sequencia("\nLocalidade: ", m.localUtente, 100);
				m.teleUtente = inteiro("\nTelefone: ");
				m.nPaciente = inteiro("\nNº de Utente: ");
				sequencia("\nProblema de Saúde: ", m.ProblSaude, 100);
				sequencia("\nSituação Clínica: ", m.SituacaoClinica, 100);
				sequencia("\nData da Primeira Consulta: ", m.datada1Consulta, 20);
				sequencia("\nData da Ultima Consulta: ", m.dadtadaUltimaConsulta, 20);
				sequencia("\nData da Proxima Consulta: ", m.datadaProximaConsulta, 20);
				
	    		sprintf(ficheiro, ".\\Utente\\Utente_%s.txt", m.nomeUtente);
						fp = fopen(ficheiro, "w");
			 			
			 			fprintf(fp, "\nNome: %s\nPassword: %s\nSexo: %s\nIdade: %d\nLocalidade: %s\nTelefone: %d"
						 "\nNº de Utente: %d\nProblema de Saúde: %s\nSituação Clínica: %s"
						 "\nData da 1ºConsulta: %s\nData da Ultima Consulta: %s"
						 "\nData da Proxima Consulta: %s"
						 , m.nomeUtente, m.password, m.sexo, m.idade, m.localUtente, m.teleUtente, m.nPaciente,m.ProblSaude, m.SituacaoClinica, m.datada1Consulta, m.dadtadaUltimaConsulta, m.datadaProximaConsulta);
						fprintf(fp, "\n");	
						fclose(fp);
						fp= fopen(".\\Utente\\UtentesNaoCovid.txt", "a");
						fprintf(fp,"\n%s", m.nomeUtente);
						fclose(fp);

	          break;    
		      }
		      case 'S':
		      case 's':{
		
		      	sequencia("\nNome do Paciente: ", m.nomeUtente, 100);
		      	sequencia("\nPassword: ", m.password, 50);
				sequencia("\nSexo: ", m.sexo, 50);
				m.idade = inteiro("\nIdade: ");
				sequencia("\nLocalidade: ", m.localUtente, 100);
				m.teleUtente = inteiro("\nTelefone: ");
				m.nPaciente = inteiro("\nNº de Utente: ");
				sequencia("\nSituação Clínica: ", m.SituacaoClinica, 100);
				sequencia("\nData da Primeira Consulta: ", m.datada1Consulta, 20);
				sequencia("\nData da Ultima Consulta: ", m.dadtadaUltimaConsulta, 20);
				sequencia("\nData da Proxima Consulta: ", m.datadaProximaConsulta, 20);
				
	    		sprintf(ficheiro, ".\\Utente\\Utente_%s.txt", m.nomeUtente);
						fp = fopen(ficheiro, "w");
			 			
			 			fprintf(fp, "\nNome: %s\nPassword: %s\nSexo: %s\nIdade: %d\nLocalidade: %s\nTelefone: %d"
						 "\nNº de Utente: %d\nProblema de Saúde: Covid-19\nSituação Clínica: %s"
						 "\nData da 1ºConsulta: %s\nData da Ultima Consulta: %s"
						 "\nData da Proxima Consulta: %s"
						 , m.nomeUtente, m.password, m.sexo, m.idade, m.localUtente, m.teleUtente, m.nPaciente, m.SituacaoClinica, m.datada1Consulta, m.dadtadaUltimaConsulta, m.datadaProximaConsulta);
						fprintf(fp, "\n");	
						fclose(fp);
						fp= fopen(".\\Utente\\UtentesCovid.txt", "a");
						fprintf(fp,"\n%s", m.nomeUtente);
						fclose(fp);

			
	    	
				break;
			}
		}
	break;
	}
			case 2:{
				FILE*fp;
				printf("\n\tListagem de Utentes com Covid-19");
				fp=fopen(".//Utente/UtentesCovid.txt","r");
					fread(w, sizeof(w),100,fp);
					printf("\n%s", w);
				fclose(fp);
				printf("\n\tListagem de Utentes Não Covid-19");
					fp=fopen(".//Utente/UtentesNaoCovid.txt","r");
					fread(q, sizeof(q),100,fp);
					printf("\n%s", q);
				fclose(fp);
				sequencia("\nNome do Utente: ", nomeUtenteListar , 100);
						sprintf(ficheiro, ".//Utente/Utente_%s.txt", nomeUtenteListar);
						fp = fopen(ficheiro, "r");
						if(fp != NULL){
						
						fread(z, sizeof(z),100,fp);
						printf("\n%s\n", z);
						}
						fclose(fp);
						printf("\n");
				break;
			}
			case 3:{
				FILE*fp;
				printf("\nReceita");
				sequencia("\nNome do Utente: ", m.receitaUtente, 100);
                 sprintf(ficheiro, ".\\Utente\\Utente_%s.txt", m.receitaUtente);
		        
		        if((fp = fopen(ficheiro, "r") )!= NULL){

					
				
			
				
				
				sequencia("\nNome(s) do(s) Medicamento(s): ", m.medicamento, 200);
				//fp = fopen(ficheiro, "w");
			 			
			 	     sprintf(ficheiro, ".\\Receitas\\Utente_%s.txt", m.receitaUtente);
						fp = fopen(ficheiro, "w");
					  	fprintf(fp, "\nNome: %s\nNome(s) do(s) Medicamento(s): %s\nAssinatura do Médico: \n", m.receitaUtente, m.medicamento);
						fclose(fp);
						
						sprintf(ficheiro, ".\\Consultas\\Utente_%s.txt", m.receitaUtente);
						fp = fopen(ficheiro, "a+");
						fprintf(fp, "\nNome(s) do(s) Medicamento(s): %s", m.medicamento);
						fprintf(fp, "\n");
						fclose(fp);
		        }

			else{
				printf("\nUtente não existente");
			
		}
				break;
				
			}
			case 4:{
				FILE*fp;
				sequencia("\nNome do Utente: ", m.nomeInternamento, 100);
                 sprintf(ficheiro, ".\\Utente\\Utente_%s.txt", m.nomeInternamento);
		        
		        if((fp = fopen(ficheiro, "a") )!= NULL){
		        	fprintf(fp, "\nEste paciente está Internado");
		        	printf("\nEste paciente está Internado");
		        	
		        }else{
		        printf("\nUtente não existente");	
				}
				fclose(fp);
				break;
			}
			case 5:{
				FILE*fp;
				sequencia("\nNome do Utente: ", m.nomeJustificacao, 100);
                 sprintf(ficheiro, ".\\Utente\\Utente_%s.txt", m.nomeJustificacao);
		        
		        if((fp = fopen(ficheiro, "r") )!= NULL){

			
				sequencia("\nMotivo da Falta: ", m.motivoFalta, 300);
				sequencia("\nData da Falta: ", m.dataFalta, 20);
					fp = fopen(ficheiro, "w");
			 			
			 	     sprintf(ficheiro, ".\\Justificacao\\Utente_%s.txt", m.receitaUtente);
						fp = fopen(ficheiro, "w");
					  	fprintf(fp, "\nNome: %s\nMotivo da falta: %s\nData da Falta: %s\nAssinatura do Médico: \n", m.nomeJustificacao, m.motivoFalta, m.dataFalta);
						fprintf(fp, "\n");	
						fclose(fp);
		   }else{
			printf("\nUtente não existente");
		   }
				break;
			}
			case 6:{
				FILE*fp;
				sequencia("\nNome do Utente: ", m.nomeUtente, 100);
				 sprintf(ficheiro, ".\\Utente\\Utente_%s.txt", m.nomeUtente);
		        
		        if((fp = fopen(ficheiro, "r") )!= NULL){
	            sequencia("\nRelatório Clínico: ", m.relatorioClinico, 1000);
	            
				sprintf(ficheiro, ".\\Relatorio\\Utente_%s.txt", m.nomeUtente);
						fp = fopen(ficheiro, "w");
					  	fprintf(fp, "\nNome: %s\nRelatório Clínico: %s", m.nomeUtente, m.relatorioClinico);
						fprintf(fp, "\n");	
						fclose(fp);
						
				sprintf(ficheiro, ".\\Consultas\\Utente_%s.txt", m.nomeUtente);
						fp = fopen(ficheiro, "a+");
						fprintf(fp, "\nRelatório Clínico: %s", m.relatorioClinico);
						fprintf(fp, "\n");
						fclose(fp);		
				 }else{
			printf("\nUtente não existente");
		   }
				
				break;
			}
			case 7:{
				sequencia("\nIntroduza o nome do Utente que pretende consultar: ", m.nomeUtente, 100);
				FILE*fp;
		       		sprintf(ficheiro, ".\\Consultas\\Utente_%s.txt", m.nomeUtente);
		       		fp=fopen(ficheiro, "r");
		       		if(fp == NULL){
		       			printf("erro");
					   }else{
					   
		       		fread(h, sizeof(h), 100, fp);
		       		printf("\n%s", h);
		       		}
					   fclose(fp);
				
				break;
			}
		}
	}while(opcaoMedico!=0);
}
int iSessaoUtente(char userm[100], char passm[100], char str1[100], char str2[100], int k, int g, char a[50], char ficheiro[C], int opcaoUtente, char v[100]){
	do{
	    FILE *fp;
	

	    k=0;g=0;
		sequencia("\n\tNome do Utente: ", userm, 100);
	    sprintf(ficheiro, ".\\Utente\\Utente_%s.txt", userm);
		fp = fopen(ficheiro,"r");
		if(fp != NULL){

			sequencia("\n\tPassword: ", passm, 100);
		
			while(fscanf(fp,"%s",a)!=EOF){
		        if(strcmp(a,userm) == 0){
			        k=1;
			        break;
		        }
		    }
		    fclose(fp);
		    
		    fp = fopen(ficheiro,"r");
		    while(fscanf(fp,"%s",a)!=EOF){
		        if(strcmp(a,passm) == 0){
			        g=1;
			        break;
		        }
		    }
		    fclose(fp);
			if(k==1&&g==1){
			    printf("\n\n\tBem Vindo!!!");
		    }
		    else{
			    printf("\n");

		    }
		    printf("\n");

		}
		else{
			printf("\n");
		}
	}while(k != 1 && g != 1);
	do{
		printf("\n\n");
		printf("\t|***********************************|\n"
		       "\t|****           UTENTE          ****|\n"
		       "\t|***********************************|\n"
		       "\t|****  1 - Consultar Relatório  ****|\n"
		       "\t|****  0 - SAIR                 ****|\n"
		       "\t|***********************************|\n");
		       
		       
		      opcaoUtente = inteiro("\nQual a sua opção: ");
		    
		       
		       		FILE*fp;
		       		sprintf(ficheiro, ".\\Relatorio\\Utente_%s.txt", userm);
		       		fp=fopen(ficheiro, "r");
		       		if(fp == NULL){
		       			printf("erro");
					   }else{
					   
		       		fread(v, sizeof(v), 100, fp);
		       		printf("\n%s", v);
		       		}
					   fclose(fp);
	
			  
			   
		       
	}while(opcaoUtente != 0);
	
}

/*void utente(int opcaoUtente, int idUtente){
	do{
		printf("\n\n");
		printf("\t|*********************************|\n"
			   "\t|****          Utente         ****|\n"
	           "\t|*********************************|\n"
	           "\t|****    1 - Iniciar Sessão   ****|\n"
               "\t|****    0 - SAIR             ****|\n"
	           "\t|*********************************|\n");
	
		printf("\nSelecione a opcão: ");
		scanf("%d", &opcaoUtente);
	
		if(opcaoUtente == 1){
		printf("\nIntroduza o seu nrº interno: ");
		scanf("%d", idUtente);
		}
	}while(opcaoUtente != 0);
}*/

/*@@@@ FUNCAO MAIN                              @@@@*/
int main(void) {
	
    setlocale(LC_ALL, "Portuguese");
    system("COLOR FC");
    
    // DECLARACAO DE VARIAVEIS E DE CONSTANTES
	// ADMIN	
int opcao;
int k,g;
char a[50];
char user[100];
char pass[100];
char ficheiro[C];
char x[100];
char w[100];
//MENU ADMIN
char nomeMedico;
char nomeMedicoN;
int opcaoAdmin;
char opcaoCovid;
struct sessao c;
// MEDICO
int opcaoMedico;
int idMedico;
struct utente m;

//teste
  char userm[100];
	char passm[100];
	char str1[100];
	char str2[100];
	char doenteCovid;
	//char w[100];
	char z[10000];
	char q[100];
	char nomeUtenteListar[100];
	int l;
	char b[50];	
	int s;
	char y[50];
	char v[100];
	char h[100];
//UTENTE
int opcaoUtente;
int idUtente;
	
    // SEQUENCIA LOGICA DE INSTRUCOES
    printf("\n");
    	do{
        printf("\n\n");
		printf("\t|**************************|\n"
		       "\t|****       Menu       ****|\n"
		       "\t|**************************|\n"
		       "\t|****    1 - ADMIN     ****|\n"
		       "\t|****    2 - MÉDICO    ****|\n"
		       "\t|****    3 - UTENTE    ****|\n"
		       "\t|****    0 - SAIR      ****|\n"
			   "\t|**************************|\n");
			   
		printf("\nSelecione a opção: ");
		scanf("%d", &opcao);
		
		switch(opcao){
			case 1:{
				admin(user, ficheiro, a, k, pass, g);
				menuAdmin(opcaoAdmin, opcaoCovid, c, ficheiro, w, x);
				
				break;
			}
			case 2:{
				//medico(opcaoMedico, idMedico);
				iSessaoMedico(userm, passm, str1, str2, k, g, a, ficheiro);
				menuMedico(opcaoMedico, m, ficheiro, doenteCovid, w, z, q, nomeUtenteListar, a, k, y, s, h);
				break;
			}
			case 3:{
				iSessaoUtente(userm, passm, str1, str2, k, g, a, ficheiro, opcaoUtente, v);
				//ConsultarRelatorio(opcaoUtente, userm, v, ficheiro);
				break;
			}
		}	   	
	}while(opcao != 0);

	
	    
    printf("\n\n");
    
    return 0;
}
/*--------------------------------------------------*/
