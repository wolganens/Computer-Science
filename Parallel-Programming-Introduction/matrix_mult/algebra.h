/* algebra.h
   Especificacao das funcoes
*/


//multiplica um vetor por um escalar e retorna um vetor
//tamanho do vetor = coluna
//tamanho do vetor retornado = coluna
double* mult_escalar_vetor(int coluna, double escalar, double*vetor);

//multiplica um vetor por um vetor e retorna um escalar
//tamanho do vetor1 = coluna
//tamanho do vetor2 = coluna
double mult_vetor_vetor(int coluna, double *vetor1, double *vetor2);

//multiplica uma matriz por um escalar e retorna uma matriz
//tamanho da matriz = linha x coluna
//tamanho da matriz retornada = linha x coluna
double** mult_escalar_matriz(int linha, int coluna, double escalar, double** matriz);

//multiplica uma matriz por um vetor e retorna um vetor
//tamanho da matriz = linha x coluna
//tamanho do vetor = linha
//tamanho do vetor retornado = coluna
double* mult_vetor_matriz(int linha, int coluna, double *vetor, double** matriz);

//multiplica uma matriz por uma matriz e retorna uma matriz
//coluna 1 e linha 2 precisam ser iguais
//tamanho da matriz1 = linha1 x coluna1
//tamanho da matriz2 = linha2 x coluna2
//tamanho da matriz retornada = linha1 x coluna2
double* mult_matriz_matriz(int linha1, int coluna1, int linha2, int coluna2, double *matriz1, double *matriz2);

double* ler_vetor(int *coluna, char *nome_arquivo);

double* ler_matriz(int *linha, int *coluna, char *nome_arquivo);