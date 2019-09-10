#include "HuffmanTADS/Huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_header(FILE *file, unsigned int *tam_lixo, unsigned int *tam_arv) {
	unsigned char bytes_cabecalho = (unsigned char) fgetc(file);
	*(tam_lixo) = bytes_cabecalho >> 5;

	unsigned char five_bytes_from_tree = bytes_cabecalho << 3;
	*(tam_arv) = five_bytes_from_tree >> 3;
	bytes_cabecalho = (unsigned char) fgetc(file);
	*(tam_arv) <<= 8;
	*(tam_arv) |= bytes_cabecalho;
}

Nodes *construct_tree_descompress(Nodes *Nodes_huff,
		FILE *file_input_comprimido) {
	unsigned char c;
	fscanf(file_input_comprimido, "%c", &c);

	if (c == 42) {
		Nodes_huff = CreatNode(0, c, NULL, NULL);
		Nodes_huff->left = construct_tree_descompress(Nodes_huff->left,
				file_input_comprimido);
		Nodes_huff->right = construct_tree_descompress(Nodes_huff->right,
				file_input_comprimido);
	} else {
		if (c == '\\') {
			fscanf(file_input_comprimido, "%c", &c);
		}
		Nodes_huff = CreatNode(0, c, NULL, NULL);
	}
	return Nodes_huff;
}

long long int FileSize(FILE *in) {
	long long int bytes;
	if (in != NULL) {
		fseek(in, 0, SEEK_END);
		bytes = ftell(in);
	}
	return bytes;
}

void descompress() {
	Nodes *temp;
	FILE *file_output, *file_input_descompress;
	unsigned char character;
	unsigned int tam_lixo, tam_arv;
	long long int tam_file = 0, bytes = 0;
	char arquivo_saida[100], nome_arquivo[30];
	int tam_arquivo_entrada = 0, i;
	int *header;

	printf("Nome do arquivo a descompactar?\n");
	scanf("%s", nome_arquivo);

	file_input_descompress = fopen(nome_arquivo, "rb");

	if (file_input_descompress == NULL) {
		printf("Unable to open file: %s\n", nome_arquivo);
		return;
	}

	bytes = FileSize(file_input_descompress);
	fclose(file_input_descompress);
	file_input_descompress = fopen(nome_arquivo, "rb");

	tam_arquivo_entrada = strlen(nome_arquivo);

	get_header(file_input_descompress, &tam_lixo, &tam_arv);
	Nodes *root = construct_tree_descompress(root, file_input_descompress);
	Nodes *root_aux = root;
	//printf("TAM FILE: %lld\n", bytes);
	//printf("TAM LIXO: %d | TAM TREE: %d\n", tam_lixo, tam_arv);
	for (i = 0; i < tam_arquivo_entrada - 5; i++) {
		arquivo_saida[i] = nome_arquivo[i];
	}
	arquivo_saida[i] = '\0';

	file_output = fopen(arquivo_saida, "wb");

	temp = root;

	while (bytes > 0) {
		fscanf(file_input_descompress, "%c", &character);
		if (bytes != 1) {
			for (i = 7; i >= 0; i--) {
				if (is_bit_set(character, i)) {
					root_aux = root_aux->right;
				} else {
					root_aux = root_aux->left;
				}
				if (eh_folha(root_aux)) {
					fprintf(file_output, "%c", root_aux->character);
					root_aux = root;
				}
			}
		} else {
			for (i = 7; i >= tam_lixo; i--) {
				if (is_bit_set(character, i)) {
					root_aux = root_aux->right;
				} else {
					root_aux = root_aux->left;
				}
				if (eh_folha(root_aux)) {
					fprintf(file_output, "%c", root_aux->character);
					root_aux = root;
				}
			}
		}
		bytes = bytes - 1;
	}

	fclose(file_input_descompress);
	fclose(file_output);
	printf("Descompactado com sucesso!\n");
}
