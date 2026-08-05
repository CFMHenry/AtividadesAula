/******************************************************************************

4. Crie uma estrutura representando os alunos de um determinado curso. A estrutura deve
conter a matr´ıcula do aluno, nome, nota da primeira prova, nota da segunda prova e nota
da terceira prova.
(a) Permita ao usuario entrar com os dados de 5 alunos. ´
(b) Encontre o aluno com maior nota da primeira prova.
(c) Encontre o aluno com maior media geral. ´
(d) Encontre o aluno com menor media geral ´
(e) Para cada aluno diga se ele foi aprovado ou reprovado, considerando o valor 6 para
aprovac¸ao.

*******************************************************************************/
#include <stdio.h>

typedef struct aluno{
    int matricula;
    char nome[50];
    int n1, n2, n3;
} Alunos;

int Cadastrar(Alunos alunos[], int TAM);
void MaiorN1(Alunos alunos[], int TAM);
void MaiorMedia(Alunos alunos[], int TAM);
void MenorMedia(Alunos alunos[], int TAM);
void ListarAlunos(Alunos alunos[], int TAM);
int ExisteAluno(int TAM);

int main()
{
    Alunos alunos[10];
    int opcao, TAM = -1;
    
    printf("Seja bem vindo ao sistema escola!\n");
    printf("Para começar selecione uma opção: ");
    
    do{
        printf("\n 0 - sair\n 1 - Cadastrar aluno\n 2 - Aluno com maior n1 ");
        printf("\n 3 - Aluno com maior media geral\n 4 - Aluno com menor media geral \n 5 - listar alunos aprovados e reprovados\n ");
        
        scanf("%d", &opcao);
        
        switch(opcao){
            case 0:
                printf("\nAté logo!");
                break;
            case 1:
                TAM = Cadastrar(alunos, TAM);
                break;
            case 2:
                MaiorN1(alunos, TAM);
                break;
            
        }
        
    }while(opcao);

    return 0;
}

int ExisteAluno(int TAM){
    if(TAM >= 0)
        return 1;
    else
        return 0;
}

int Cadastrar(Alunos alunos[], int TAM){
    int continuar;
    do{
        TAM += 1;
        printf("Digite o nome do(a) aluno(a) a ser cadastrado(a): ");
        scanf(" %49[^\n]", alunos[TAM].nome);
        getchar();
        
        printf("Digite a matricula do aluno: ");
        scanf("%d", &alunos[TAM].matricula);
        getchar();
        
        printf("Digite a nota da primeira prova: ");
        scanf("%d", &alunos[TAM].n1);
        getchar();
        
        printf("Digite a nota da segunda prova: ");
        scanf("%d", &alunos[TAM].n2);
        getchar();
        
        printf("Digite a nota da terceira prova: ");
        scanf("%d", &alunos[TAM].n3);
        getchar();
        
        printf("Deseja continuar cadastrando alunos? 0 - nao, 1 - sim ");
        scanf("%d", &continuar);
        getchar();
        
    }while(continuar);
    
    return TAM;
}

void MaiorN1(Alunos alunos[], int TAM){
    int iCont, indx = 0;
    if(!ExisteAluno(TAM)){
        printf("Nenhum aluno cadastrado!");
    }
    else{
        for(iCont = 0; iCont <= TAM; iCont++){
            if(alunos[iCont].n1 > alunos[indx].n1)
                indx = iCont;
            
        }
        
        printf("Aluno: %s\n", alunos[indx].nome);
        printf("Nota 1: %d\n", alunos[indx].n1);
    }
}