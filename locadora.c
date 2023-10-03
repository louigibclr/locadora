#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define ARQUIVO "./filmes.txt"

#define MAX_STRING 100
#define MAX_FILMES 5

typedef struct
{
    char titulo[MAX_STRING];
    char diretor[MAX_STRING];
    int anoLancamento;
    float classificacao;
    int quantidade;
} Filme;

void clearscr(void);
void mostrarFilmes();
Filme cadastrarFilme();
void exibirFilme(int i);
void salvarFilmes();
void carregarFilmes();
void deleteMovie(Filme *f);
void showOtherOptions(Filme *f);
void printReceipt(char title[MAX_STRING], int quantidade);
void setTime();
void flush();

Filme filmes[MAX_FILMES];
int totalFilmes = 0;

int main()
{
    int index, i, choice;
    Filme *f;
    char name[MAX_STRING];
    
    do
    {
        printf("- - - Locadora de Filmes - - -\n");
        printf("1. Cadastrar filme \n");
        printf("2. Ver filmes cadastrados\n");
        printf("3. Pesquisar filme pelo indice \n");
        printf("4. Salvar filmes cadastrados \n");
        printf("5. Carregar filmes \n");
        printf("6. Pesquisar filme pelo titulo \n");
        printf("7. Sair");
        printf("\n- - - - - - - - - - - - - - - -\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
        flush();
        // Verifique se a entrada contém apenas dígitos
        // Converta a string para um número inteiro
        switch (choice) {
        case 1:
            if (totalFilmes < MAX_FILMES)
            {
                filmes[totalFilmes] = cadastrarFilme();
                totalFilmes++;
                printf("\nFilme cadastrado com sucesso!\n");
                putchar('\n');
            }
            else
                printf("\nQuantidade maxima de filmes cadastrada!\n");
            break;
        case 2:
            mostrarFilmes();
            break;
        case 3:
            if (totalFilmes == 0)
                printf("\nNenhum filme foi cadastrado ainda!\n");
            else
            {
                for (int i = 0; i < totalFilmes; i++) {
                    f = &filmes[i];
                    printf("\n%d. %s\n", i, f->titulo);
                }
                printf("Digite o indice do filme que voce esta procurando: ");
                scanf("%d", &index);
                if (index >= totalFilmes || index < 0)
                {
                    printf("\nO filme correspondente ao indice digitado nao existe!\n");
                    printf("\nTotal de filmes: %d\n", totalFilmes);
                    break;
                }
                exibirFilme(index);
                f = &filmes[index];
                
                showOtherOptions(f);
            }
            break;
        case 4:
            salvarFilmes();
            break;
        case 5:
            carregarFilmes();
            break;
        case 6:
            if (totalFilmes == 0)
            {
                printf("\nNenhum filme foi cadastrado ainda!\n");
                break;
            }
            printf("\nDigite o titulo do filme que voce esta procurando.\n");
            fgets(name, MAX_STRING, stdin);
            name[strcspn(name, "\n")] = '\0';

            int achou = 0;
            int pegaIndice;

            for (i = 0; i < totalFilmes; i++)
            {
                if (strcmp(name, filmes[i].titulo) == 0)
                {
                    achou = 1;
                    pegaIndice = i;
                } 
            }
            if (achou == 1) {
                f = &filmes[pegaIndice];
                printf("\nFilme encontrado!\n");
                printf("\nTitulo: %s\n", f->titulo);
                printf("Diretor: %s\n", f->diretor);
                printf("Ano de Lancamento: %d\n", f->anoLancamento);
                printf("Classificacao: %.1f\n", f->classificacao);
                printf("Quantidade em estoque: %d\n", f->quantidade);
                showOtherOptions(f);
            } else {
                printf("\nFilme nao encontrado.\n");
                putchar('\n');
            }
            break;
        case 7:
            break;
        default:
            printf("\n\tEscolha uma opcao valida.\n");
            putchar('\n');
        }

    } while (choice != 7);

    return 0;
}

void clearscr(void) {
  printf("\x1b[2J");
  printf("\x1b[H");
}

Filme cadastrarFilme()
{
    Filme f;
    
    do {
    printf("\n- - - Cadastro de Filme - - -\n");
    printf("Informe o titulo do filme: ");
    fgets(f.titulo, MAX_STRING, stdin);
    f.titulo[strcspn(f.titulo, "\n")] = '\0';

    printf("Informe o diretor do filme: ");
    fgets(f.diretor, MAX_STRING, stdin);
    f.diretor[strcspn(f.diretor, "\n")] = '\0';

    printf("Informe o ano de lancamento do filme: ");
    scanf("%d", &f.anoLancamento);
    
    printf("Informe a classificacao do filme (0.0 a 10.0): ");
    scanf("%f", &f.classificacao);

    printf("Informe a quantidade de copias em estoque: ");
    scanf("%d", &f.quantidade);
    if (f.quantidade < 0) {
        printf("\nDigite uma quantidade maior que zero\n");
        while(getchar() != '\n');
    }
    } while (f.quantidade < 0);

    return f;
}

void exibirFilme(int i)
{
    Filme f = filmes[i];
    printf("\nTitulo: %s\n", f.titulo);
    printf("Diretor: %s\n", f.diretor);
    printf("Ano de Lancamento: %d\n", f.anoLancamento);
    printf("Classificacao: %.1f\n", f.classificacao);
    printf("Quantidade em estoque: %d\n", f.quantidade);
}

void mostrarFilmes()
{
    printf("\n- - - Lista de Filmes - - -\n");

    if (totalFilmes == 0)
        printf("Nenhum filme foi cadastrado ainda!\n");
    else
    {
        for (int i = 0; i < totalFilmes; i++)
        {
            exibirFilme(i);
        }
    }
    putchar('\n');
}

void showOtherOptions(Filme *f)
{
    int escolha;
    char confirm;
    do
    {
        printf("\n- - - O que deseja fazer? - - -\n");
        printf("1. Alugar filme\n");
        printf("2. Excluir filme\n");
        printf("3. Ir para a tela principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        flush();
        printf("\n");

        switch (escolha)
        {
        case 1:
            
            printf("Deseja confirmar o aluguel do filme? (y / n) ");
            scanf("%c", &confirm);
            confirm = tolower(confirm);
            if (confirm == 'n')
            {
                printf("\nAluguel de filmes cancelado!\n");
                break;
            }
                f->quantidade--;
                printReceipt(f->titulo, 1);
                break;
        case 2:
            deleteMovie(f);
            printf("\nFilme deletado com sucesso!\n");
            break;
        case 3:
            break;
        default:
            printf("\nOpcao invalida!\n");
        }
    } while (escolha > 3 || escolha < 1);
}

void printReceipt(char title[MAX_STRING], int quantidadeVendida)
{
    int valorTotal = quantidadeVendida * 10;
    printf("\n\t- - - Recibo - - -\n");
    printf("\n\tFilme(s) alugado(s): %s\n", title);
    printf("\n\tQuantidade de filmes alugados: %d\n", quantidadeVendida);
    printf("\n\tValor total: R$%d,00\n", valorTotal);
    setTime();
}

void setTime()
{
    struct tm *data_hora_atual;

    time_t segundos;

    time(&segundos);

    data_hora_atual = localtime(&segundos);

    
    printf("\n\tDia..........: %d\n", data_hora_atual->tm_mday);

    printf("\n\tMes..........: %d\n", data_hora_atual->tm_mon + 1);

    printf("\n\tAno..........: %d\n\n", data_hora_atual->tm_year + 1900);

    printf("\n\tHora ........: %d:", data_hora_atual->tm_hour);
    printf("%d:", data_hora_atual->tm_min);
    printf("%d\n", data_hora_atual->tm_sec);

    printf("\n\tData ........: %d/", data_hora_atual->tm_mday);
    printf("%d/", data_hora_atual->tm_mon + 1);
    printf("%d\n\n", data_hora_atual->tm_year + 1900);

    
    printf("\n\tData de devolucao: %d/", data_hora_atual->tm_mday + 7);
    printf("%d/", data_hora_atual->tm_mon + 1);
    printf("%d\n\n", data_hora_atual->tm_year + 1900);
}

void deleteMovie(Filme *f)
{
    int i, deletedMovieIndex;
    for (i = 0; i < MAX_FILMES; i++)
    {
        if (strcmp(filmes[i].titulo, f->titulo) == 0)
            deletedMovieIndex = i;
    }

    for (i = deletedMovieIndex; i < MAX_FILMES - 1; i++)
    {
        filmes[i] = filmes[i + 1];
    }
    totalFilmes--;
}

void salvarFilmes()
{
    FILE *file = fopen(ARQUIVO, "w");
    if (file == NULL)
    {
        printf("Erro ao salvar os filmes!\n");
        return;
    }

    for (int i = 0; i < totalFilmes; i++)
    {
        fprintf(file, "\"%s\",\"%s\",%d,%.1f,%d\n",
                filmes[i].titulo,
                filmes[i].diretor,
                filmes[i].anoLancamento,
                filmes[i].classificacao,
                filmes[i].quantidade);
    }

    fclose(file);
    printf("\nFilmes salvos com sucesso!\n");
    putchar('\n');
}

void carregarFilmes()
{
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL)
    {
        printf("Arquivo nao existe ou nao pode ser aberto.");
        return; // Se o arquivo não existir ou não puder ser aberto, simplesmente retorna
    }

    while (fscanf(file, "\"%[^\"]\",\"%[^\"]\",%d,%f,%d\n",
                  filmes[totalFilmes].titulo,
                  filmes[totalFilmes].diretor,
                  &filmes[totalFilmes].anoLancamento,
                  &filmes[totalFilmes].classificacao,
                  &filmes[totalFilmes].quantidade) != EOF)
    {
        totalFilmes++;
    }
    fclose(file);
    printf("\nFilmes carregados com sucesso!\n");
}

void flush() {
    while(getchar() != '\n');
}
