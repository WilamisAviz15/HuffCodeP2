#include "HuffmanTADS/Huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void conting_freq(FILE *file_input, hash *Hash) {
	long long int bytes = 0;
	unsigned char c;
	while (fscanf(file_input, "%c", &c) != EOF) {
		Hash->array[c]->frequency++;
	}
}

Nodes *construct_tree(char nome_arquivo[], FILE *file_input, hash *Hash) {
	FILE *file_output;
	unsigned char caracter;
	Nodes *root, *left, *right, *top;
	int byte = 0;

	heap *Heap = CreatTable(256);
	Heap->size = 0;

	unsigned int *string = (unsigned int*) calloc(256, sizeof(unsigned int));
	int cont, i;
	i = cont = 0;
	file_input = fopen(nome_arquivo, "rb");
	if (file_input == NULL) {
		printf("Unable to open file: %s\n", nome_arquivo);
		exit(1);
	} else {
		conting_freq(file_input, Hash);
	}

	for (i = 0; i < 256; i++) {
		if (Hash->array[i]->frequency >= 1) {
			Insert(Hash->array[i]->frequency, i, Heap, NULL, NULL);
		}
	}

	while (Heap->size > 0) {
		Nodes *left = Pop(Heap);
		Nodes *right = Pop(Heap);

		unsigned char asterisk = 42;
		if (Heap->size == 0) {
			return root = CreatNode((left->frequency + right->frequency), asterisk, left, right);
		}
		if ((right->character == '*' && left->character != '*') && (right->frequency == left->frequency)) {
			Insert(left->frequency + right->frequency, asterisk, Heap, right, left);
		} else {
			Insert(left->frequency + right->frequency, asterisk, Heap, left, right);
		}
	}
}

void Encode(Nodes *root, hash *HASH, char *new_path_bits) {
	if (root != NULL) {
		unsigned char item = root->character;
		if (is_leaf(root)) {
			strcat(HASH->array[item]->bits, new_path_bits);
			HASH->array[item]->frequency = root->frequency;
			HASH->array[item]->c = root->character;
		} else {
			Encode(root->left, HASH, strcat(new_path_bits, "0"));
			new_path_bits[strlen(new_path_bits) - 1] = '\0';
			Encode(root->right, HASH, strcat(new_path_bits, "1"));
			new_path_bits[strlen(new_path_bits) - 1] = '\0';
		}
	}
}

void get_header_compact(FILE* fileout, hash *HASH, Nodes *root,
		int len_tree) {
	unsigned char* bytes = (unsigned char*) malloc(3 * sizeof(unsigned char));
	int trash = count_trash_file(HASH);

	bytes[0] = trash << 5 | len_tree >> 8;
	bytes[1] = len_tree;

	fwrite(bytes, 1, 2, fileout);
	print_tree_huffman_file(fileout, root);
}

void insert_file_binary(FILE *file_input, FILE *file_out, hash *HASH,
		char nome_arquivo[]) {
	unsigned char c;
	unsigned char byte = { 0 };
	int bit = 7, i;
	file_input = fopen(nome_arquivo, "rb");
	while (fscanf(file_input, "%c", &c) != EOF) {
		for (i = 0; HASH->array[c]->bits[i] != '\0'; i++) {
			if (bit < 0) {
				fprintf(file_out, "%c", byte);
				byte = 0;
				bit = 7;
			}
			if (HASH->array[c]->bits[i] == '1') {
				byte = set_bit(byte, bit);
			}
			bit--;
		}
	}
	fprintf(file_out, "%c", byte);
}

void insert_header_file(char name_file[], hash *HASH, Nodes *root,
		unsigned long long int size_tree, FILE *file_input) {
	FILE *file_output;
	int bin_tam[8];
	int i;
	char name_file_output[30];
	strcpy(name_file_output, name_file);
	strcat(name_file_output, ".huff");

	file_output = fopen(name_file_output, "wb");
	get_header_compact(file_output, HASH, root, size_tree);
	insert_file_binary(file_input, file_output, HASH, name_file);
}
void compress() {
	FILE *file_input, *file_output;
	char file_name[30];
	unsigned long long int size_tree;
	unsigned char *vector = (unsigned char *) malloc(10 * sizeof(unsigned char));
	printf("Informe o nome do arquivo.\n");
	scanf("%s", file_name);
	hash *HASH = create_hash();
	Nodes *root = construct_tree(file_name, file_input, HASH);
	Encode(root, HASH, vector);
	size_tree = lenght_tree(root);
	int len_lixo = count_trash_file(HASH);
	insert_header_file(file_name, HASH, root, size_tree, file_input);
	printf("Compactado com sucesso!\n");
}
