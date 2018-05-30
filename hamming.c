/* Trabalho de Introdução à Ciência da Informação */
/* Nome: Matheus Dalmolin da Silva */
/* Objetivo: Fazer um programa para executar o código de correção de erros Hamming(7,4). */

#include <stdio.h>
#include <stdlib.h>

void corrige_hamming(int* codigo_hamming)
{
	for (int i = 0; i < 7; i++)
		codigo_hamming[i] = codigo_hamming[i] % 2 == 0 ? 0 : 1;
}

void injeta_erros(int* codigo_hamming, int bit_erro)
{
	codigo_hamming[bit_erro - 1] = codigo_hamming[bit_erro - 1] ? 0 : 1;
}

void imprime_hamming(int* codigo_hamming)
{
	for (int i = 0; i < 7; i++)
		printf("\nbit %d\t%d", i + 1, codigo_hamming[i]);
}

void imprime_paridade(int* resultado_paridade)
{
	for (int i = 0; i < 3; i++)
		printf("\n\t%d", resultado_paridade[i]);
}

void corrige_erros(int* codigo_hamming, int num_decimal)
{
	codigo_hamming[num_decimal-1] = codigo_hamming[num_decimal-1] ? 0 : 1;
}

void aplicar_modulo2(int* resultado_paridade)
{
	for (int i = 0; i < 3; i++)
		resultado_paridade[i] = resultado_paridade[i] % 2 == 0 ? 0 : 1;
}

void testar_paridade(int matriz_paridade[][7], int* resultado_paridade, int elemento, int* codigo_hamming)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
			elemento += matriz_paridade[i][j] * codigo_hamming[j];
		resultado_paridade[i] = elemento;
		elemento = 0;
	}
}

void gerar_codigo_hamming(int matriz_geradora[][4], int* numero_binario, int elemento, int* codigo_hamming)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			elemento += matriz_geradora[i][j] * numero_binario[j];
		}
		codigo_hamming[i] = elemento;
		elemento = 0;
	}
}

int main()
{
	int matriz_geradora[7][4] = {{1, 1, 0, 1}, {1, 0, 1, 1}, {1, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
	int matriz_paridade[4][7] = {{1, 0, 1, 0, 1, 0, 1}, {0, 1, 1, 0, 0, 1, 1}, {0, 0, 0, 1, 1, 1, 1}};
	int numero_binario[4];
	int codigo_hamming[7];
	int resultado_paridade[3];
	int elemento = 0;      // variável que auxilia na soma dos elementos do código
	int bit_erro;          // uso essa variável bit_erro pra aplicar o erro em um bit apenas
	int vet_erros_bit[2];  // uso o vetor para aplicar erro em dois bits
	int num_decimal = 0;   // variável para traduzir a paridade para um número decimal

	printf("Primeiramente, vamos injetar um erro no codigo de Haming gerado.\nDepois de injetar um erro, vamos testar injetando dois erros.\n\nDigite um numero de 4 bits para obter o codigo de Hamming:\n");
	for (int i = 0; i < 4; i++)
	{
		scanf("%d", &numero_binario[i]);
		if (numero_binario[i]!=0 && numero_binario[i]!=1)
		{
			printf("Valor binario invalido, insira novamente o valor para a posicao %d\n", i);
			i--;
		}
	}

	/* Chamando a função para gerar o código Hamming */
	gerar_codigo_hamming(matriz_geradora, numero_binario, elemento, codigo_hamming);

	printf("Codigo Hamming do numero binario ");
	for (int i = 0; i < 4; i++)
		printf("%d", numero_binario[i]);

	/* Chamando as funções que corrige e imprime o código gerado, respectivamente */
	corrige_hamming(codigo_hamming);
	imprime_hamming(codigo_hamming);

	printf("\nTestando se o codigo foi transmitido corretamente.\nAplicando a matriz de paridade.\n\n");

	/* Chamando a função para testar a paridade do código gerado */
	testar_paridade(matriz_paridade, resultado_paridade, elemento, codigo_hamming);
	system("PAUSE");

	printf("\nResultado da paridade.");

	/* Chamando a função para imprimir a paridade do código */
	imprime_paridade(resultado_paridade);

	printf("\nAplicando modulo 2 no resultado.");

	/* Chamando as funções para aplicar o módulo 2 na paridade e imprimir após aplicar o módulo 2 */
	aplicar_modulo2(resultado_paridade);
	imprime_paridade(resultado_paridade);

	/* Testando se o código houve algum erro na transferência */
	if (!(resultado_paridade[0] + resultado_paridade[1] + resultado_paridade[2]))
		printf("\nCodigo transferido sem erros!");

	printf("\nInsira o bit que voce quer injetar o erro!\n");
	do
	{
		scanf("%d", &bit_erro);
		if (bit_erro <= 0 || bit_erro >= 8)
			printf("Valor invalido, insira novamente um valor valido!\n");
	} while (bit_erro <= 0 || bit_erro >= 8);
	
	printf("\nInjetando erro no bit %d!\nConteudo do bit %d eh %d, esse valor vai ser invertido!\n", bit_erro, bit_erro, codigo_hamming[bit_erro - 1]);
	injeta_erros(codigo_hamming, bit_erro);

	printf("\n\n");
	system("PAUSE");

	printf("\nCodigo Hamming apos injetar erro no bit %d:", bit_erro);
	imprime_hamming(codigo_hamming);

	printf("\n\n");
	system("PAUSE");

	printf("\nSe testarmos o codigo com erro, na matriz de paridade, vamos ter o seguinte resultado.");

	// testando paridade
	testar_paridade(matriz_paridade, resultado_paridade, elemento, codigo_hamming);

	printf("\nResultado da paridade.");
	imprime_paridade(resultado_paridade);

	printf("\nAplicando modulo 2.");
	aplicar_modulo2(resultado_paridade);
	for (int i = 0, j = 1; i < 3; i++)
	{
		printf("\n\t%d", resultado_paridade[i]);
		num_decimal += resultado_paridade[i] * j;
		j *= 2;
	}

	printf("\n\n");
	system("PAUSE");

	printf("\nInterpretando o resultado da paridade com o codigo, sabemos que o bit %d esta com erro.", num_decimal);
	corrige_erros(codigo_hamming, num_decimal);

	printf("\n\n");
	system("PAUSE");

	printf("\nApos correcao do bit %d, o codigo Hamming ficou:\n");
	imprime_hamming(codigo_hamming);

	printf("\n\n");
	system("PAUSE");

	printf("\nAgora vamos testar injetando dois erros.\nDigite um numero de 4 bits em binario.\n");

	printf("\nInsira os bits que voce quer injetar os erros!\n");
	for (int i = 0; i < 2; i++)
	{
		scanf("%d", &vet_erros_bit[i]);
		if (vet_erros_bit[i] <= 0 || vet_erros_bit[i] >= 8)
		{
			printf("Valor invalido, insira novamente um valor valido!\n");
			i--;
		}
	}
	printf("\nInjetando erro nos bits %d e %d!\nConteudo do bit %d eh %d, e o valor do bit %d eh %d.\nEsses valores vao ser invertidos!\n", vet_erros_bit[0], vet_erros_bit[1], vet_erros_bit[0], codigo_hamming[vet_erros_bit[0] - 1], vet_erros_bit[1], codigo_hamming[vet_erros_bit[1] - 1]);
	for (int i = 0; i < 2; i++)
		injeta_erros(codigo_hamming, vet_erros_bit[i]);

	printf("\n\n");
	system("PAUSE");

	printf("\nCodigo Hamming apos injetar erro nos bits %d e %d:", vet_erros_bit[0], vet_erros_bit[1]);
	imprime_hamming(codigo_hamming);

	printf("\n\n");
	system("PAUSE");

	printf("\nSe testarmos o codigo com erro, na matriz de paridade, vamos ter o seguinte resultado.");
	testar_paridade(matriz_paridade, resultado_paridade, elemento, codigo_hamming);

	printf("\nResultado da paridade.");
	imprime_paridade(resultado_paridade);

	printf("\nAplicando modulo 2.");
	aplicar_modulo2(resultado_paridade);
	imprime_paridade(resultado_paridade);

	printf("\nSabemos que esse resultado da paridade eh erroneo. Ele nao consegue acusar o bit exato que esta com erro.\nPor isso nao conseguimos corrigir os erros.");

	printf("\n\n");
	system("PAUSE");
	return 0;
}