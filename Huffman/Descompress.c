#include "HuffmanTADS/Huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_header_descompress(FILE *file, unsigned int *len_trash, unsigned int *len_tree) {
	unsigned char bytes_header = (unsigned char) fgetc(file);
	*(len_trash) = bytes_header >> 5;

	unsigned char five_bytes_from_tree = bytes_header << 3;
	*(len_tree) = five_bytes_from_tree >> 3;
	bytes_header = (unsigned char) fgetc(file);
	*(len_tree) <<= 8;
	*(len_tree) |= bytes_header;
}

Nodes *construct_tree_descompress(Nodes *Nodes_huff,
		FILE *file_input_compressed) {
	unsigned char c;
	fscanf(file_input_compressed, "%c", &c);

	if (c == 42) {
		Nodes_huff = CreatNode(0, c, NULL, NULL);
		Nodes_huff->left = construct_tree_descompress(Nodes_huff->left,
				file_input_compressed);
		Nodes_huff->right = construct_tree_descompress(Nodes_huff->right,
				file_input_compressed);
	} else {
		if (c == '\\') {
			fscanf(file_input_compressed, "%c", &c);
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
	unsigned int len_trash, len_tree;
	long long int len_files = 0, bytes = 0;
	char file_output_name[100], name_file[30];
	int len_file_in = 0, i;
	int *header;

	printf("Nome do arquivo a descompactar?\n");
	scanf("%s", name_file);

	file_input_descompress = fopen(name_file, "rb");

	if (file_input_descompress == NULL) {
		printf("Unable to open file: %s\n", name_file);
		return;
	}

	bytes = FileSize(file_input_descompress);
	fclose(file_input_descompress);
	file_input_descompress = fopen(name_file, "rb");

	len_file_in = strlen(name_file);

	get_header_descompress(file_input_descompress, &len_trash, &len_tree);
	Nodes *root = construct_tree_descompress(root, file_input_descompress);
	Nodes *root_aux = root;

	for (i = 0; i < len_file_in - 5; i++) {
		file_output_name[i] = name_file[i];
	}
	file_output_name[i] = '\0';

	file_output = fopen(file_output_name, "wb");

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
				if (is_leaf(root_aux)) {
					fprintf(file_output, "%c", root_aux->character);
					root_aux = root;
				}
			}
		} else {
			for (i = 7; i >= len_trash; i--) {
				if (is_bit_set(character, i)) {
					root_aux = root_aux->right;
				} else {
					root_aux = root_aux->left;
				}
				if (is_leaf(root_aux)) {
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
