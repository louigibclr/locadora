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

void mostrarFilmes();
Filme cadastrarFilme();
void exibirFilme(int i);
void salvarFilmes();
void carregarFilmes();
void deleteMovie(Filme *f);
int rentMovies(int quantidadeDisponivel);
int showOtherOptions(int opcaoAcaoFilme);
void printReceipt(char title[MAX_STRING], int quantidade);
void setTime();
void flush();

Filme filmes[MAX_FILMES];
int totalFilmes = 0;

int main()
{
    int index, i, isMovieAvailable = 0, opcaoAcaoFilme, quantidadeAlugada, choice;
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
        printf("7. Sair \n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
        flush();
        // Verifique se a entrada contém apenas dígitos
        // Converta a string para um número inteiro
        switch (choice)
        {
        case 1:
            if (totalFilmes < MAX_FILMES)
            {
                filmes[totalFilmes] = cadastrarFilme();
                totalFilmes++;
                printf("\nFilme cadastrado com sucesso!\n");
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
                    printf("%d. %s\n", i, f->titulo);
                }
                printf("Digite o indice do filme que voce esta procurando: ");
                scanf("%d", &index);
                if (index >= totalFilmes)
                {
                    printf("\nO filme do indice digitado nao existe!\n");
                    printf("\nTotal de filmes: %d\n", totalFilmes);
                    break;
                }
                exibirFilme(index);
                f = &filmes[index];
                
                opcaoAcaoFilme = showOtherOptions(opcaoAcaoFilme);

                if (opcaoAcaoFilme == 1)
                {
                    quantidadeAlugada = rentMovies(f->quantidade);
                    if (quantidadeAlugada == 0)
                    {
                        printf("\nAluguel de filmes cancelado!\n");
                        break;
                    }
                    f->quantidade -= quantidadeAlugada;
                    printReceipt(f->titulo, quantidadeAlugada);
                }
                else if (opcaoAcaoFilme == 2)
                {
                    deleteMovie(f);
                    printf("\nFilme deletado com sucesso!\n");
                }
                else
                    break;
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
            for (i = 0; i < totalFilmes; i++)
            {
                if (strcmp(name, filmes[i].titulo) == 0)
                {
                    f = &filmes[i];
                    isMovieAvailable = 1;
                    printf("\nFilme encontrado!\n");
                    break;
                }
            }

            if (isMovieAvailable == 0)
            {
                printf("\nFilme nao encontrado!\n");
                break;
            }
            isMovieAvailable = 0;
            printf("\nTitulo: %s\n", f->titulo);
            printf("Diretor: %s\n", f->diretor);
            printf("Ano de Lancamento: %d\n", f->anoLancamento);
            printf("Classificacao: %.1f\n", f->classificacao);
            printf("Quantidade em estoque: %d\n", f->quantidade);

            opcaoAcaoFilme = showOtherOptions(opcaoAcaoFilme);

            if (opcaoAcaoFilme == 1)
            {
                quantidadeAlugada = rentMovies(f->quantidade);
                if (quantidadeAlugada == 0)
                {
                    printf("\nAluguel de filmes cancelado!\n");
                    break;
                }
                f->quantidade -= quantidadeAlugada;
                printReceipt(f->titulo, quantidadeAlugada);
            }
            else if (opcaoAcaoFilme == 2)
            {
                deleteMovie(f);
                printf("\nFilme deletado com sucesso!\n");
            }
            else
                break;
            break;
        
        case 7:
            break;
        default:
            printf("Opcao invalida. Digite outro.\n");
            putchar('\n');
        }

    } while (choice != 7);

    return 0;
}

Filme cadastrarFilme()
{
    Filme f;

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
}

int showOtherOptions(int opcaoAcaoFilme)
{
    int secondOption;
    do
    {
        printf("\n- - - Acoes para o filme - - -\n");
        printf("1. Alugar filme\n");
        printf("2. Excluir filme\n");
        printf("3. Ir para a tela principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &secondOption);

        switch (secondOption)
        {
        case 1:
            opcaoAcaoFilme = secondOption;
            break;
        case 2:
            opcaoAcaoFilme = secondOption;
            break;
        case 3:
            opcaoAcaoFilme = secondOption;
            break;
        default:
            printf("\nOpcao invalida!\n");
        }
    } while (secondOption > 3 || secondOption < 1);
    return opcaoAcaoFilme;
}

int rentMovies(int quantidadeDisponivel)
{
    int quantidadeDemanda;
    if (quantidadeDisponivel == 0)
    {
        printf("\nFilme esgotado!\n");
        return 0;
    }

    do
    {
        printf("\nQuantidade disponivel: %d\n", quantidadeDisponivel);
        printf("Digite 0 caso queira cancelar o aluguel.\n");
        printf("Informe quantas copias voce quer: ");

        scanf("%d", &quantidadeDemanda);

        if (quantidadeDemanda > quantidadeDisponivel)
            printf("\nQuantidade maior que a disponivel, tente novamente!\n");

        if (quantidadeDemanda == 0)
            return 0;

    } while (quantidadeDemanda > quantidadeDisponivel);
    return quantidadeDemanda;
}

void printReceipt(char title[MAX_STRING], int quantidadeVendida)
{
    int valorTotal = quantidadeVendida * 10;
    printf("\n- - - Recibo - - -\n");
    printf("\nFilme(s) alugado(s): %s\n", title);
    printf("\nQuantidade de filmes alugados: %d\n", quantidadeVendida);
    printf("\nValor total: R$%d,00\n", valorTotal);
    setTime();
}

void setTime()
{
    struct tm *data_hora_atual;

    time_t segundos;

    time(&segundos);

    data_hora_atual = localtime(&segundos);

    
    printf("\n \tDia..........: %d\n", data_hora_atual->tm_mday);

    printf("\t \tMes..........: %d\n", data_hora_atual->tm_mon + 1);

    printf("\n \tAno..........: %d\n\n", data_hora_atual->tm_year + 1900);

    printf("\n \tHora ........: %d:", data_hora_atual->tm_hour);
    printf("%d:", data_hora_atual->tm_min);
    printf("%d\n", data_hora_atual->tm_sec);

    printf("\nData ........: %d/", data_hora_atual->tm_mday);
    printf("%d/", data_hora_atual->tm_mon + 1);
    printf("%d\n\n", data_hora_atual->tm_year + 1900);

    
    printf("\nData de devolucao: %d/", data_hora_atual->tm_mday + 7);
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
    printf("Filmes salvos com sucesso!\n");
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
