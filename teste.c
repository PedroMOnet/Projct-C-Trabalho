#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//$37
/*[1]esse struct está sendo declarado para realizar o tratamento desses
dados do paciente; o typedef serve para criar um alias do struct para
 que seja declarado posteriormente no código, necessariamente precisa
  ser algo existente
*/

//$73
/*[2]a variável arquivo serve como ponteiro para o tipo file, sendo assim 
       será responsavel por armazenar um endereço na memória. 

        O tipo FILE aparece no stdio e representa um arquivo aberto e contem
        informações sobre o estado do arquivo
    
        A função fopen retorna um ponteiro para a estrutura FILE que representa o 
        arquivo aberto O ponteiro é necessário porque o arquivo pode ser grande, e manipular 
        diretamente os dados do arquovo seria ineficiente. Em vez disso, o ponteiro permite acessar e 
        manipular o arquivo de forma indireta.
*/
//$92
/*[3]A função fgets em C é usada para ler uma linda de texto de um fluxo
        de entrada como o teclado (stdin)--->*standart input*
        e armazen-la em uma string, nesse caso foi utilizado pois alem de lidar
    melhor com os espaços, permite limitar o numero de caractéres lidos, além de ser mais seguro*/


/*o metodo define determina um valor como constante em todo o termo
do código*/
#define NOME_COMPLETO 100
#define DATA_MAXIMA 11
#define HORARIO 10

//[1]Comentário acima no cabeçalho
typedef struct{
    int identificador;
    //buffer responsavel por armazenar o texto a ser digitado
    char nome[NOME_COMPLETO];
    char data[DATA_MAXIMA];
    char horario[HORARIO];
} Paciente;

// Função que determina o próximo ID com base no último ID encontrado no arquivo
int proxID(const char* pacientes){
    FILE*arquivo = fopen(pacientes, "r");

    //[CORREÇÃO] Removihdo if duplicado
    if (arquivo == NULL) {
        // Se o arquivo não existir, o próximo ID será 1
        return 1;
    }

    int maiorID = 0;
    int atualID;
    char linha[256];

    while(fgets(linha, sizeof(linha), arquivo)){
        sscanf(linha, "%d", &atualID);
        if(atualID > maiorID){
            maiorID = atualID;
        }
    }
    fclose(arquivo);
    return maiorID + 1;
    // Próximo ID é o maior ID + 1
}
/*
void ListagemAtendimentos(){
    FILE*arquivo = fopen("pacientes.txt", "r");
    if(arquivo == NULL){return;}


}
*/
//função para novo cadastrado
void agendaAtendimtento(){
    //[2]Comentário acima no cabeçalho
    FILE*arquivo = fopen("pacientes.txt", "a");
    if(arquivo == NULL){
        printf("arquivo não encontrado\n");
        return;
    }

    Paciente x;
    //[3]comentário acima no cabeçalho

    //gera o identificador do paciente automaticamente
    x.identificador = proxID("pacientes.txt");
    printf("ID do paciente: %d\n", x.identificador); 

    printf("nome: ");
    fgets(x.nome, NOME_COMPLETO, stdin);
    //o strcspn pega o comprimento da string para tirar o enter
    x.nome[strcspn(x.nome, "\n")] = '\0'; //Remove o Enter da operação


    printf("digite a data da consulta: (DD/MM/AAAA) ");
    fgets(x.data, DATA_MAXIMA, stdin);
    x.data[strcspn(x.data, "\n")] = '\0';

       if(strlen(x.data) != 10 || x.data[2] != '/' ||  x.data[5] != '/'){
        printf("Formato de data incorreto. Use o formato DD/MM/AAAA\n");
        fclose(arquivo);
        return;
    }
    // limpa o buffer caso tenha sobrado \n
    if (strchr(x.data, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
    memset(x.horario, 0 ,sizeof(x.horario));
    printf("digite o horário (HH:MM): ");
    fgets(x.horario, HORARIO, stdin);
    x.horario[strcspn(x.horario, "\n")] = '\0';
    
    if(strlen(x.horario) != 5 || x.horario[2] != ':'){
        printf("Formato de horário incorreto. Use o formato HH:MM\n");
        fclose(arquivo);
        return;
    }

    //fprint(File print) pode escrever esses dados em um arquivo txt
    fprintf(arquivo, "%d, %s, %s,%s \n", x.identificador, x.nome, x.data, x.horario);
    //fecha o arquivo
    fclose(arquivo);
    printf("paciente agendado com sucesso\n");




}


int main(void){
    agendaAtendimtento();
    return 0;
}