#ifndef Huffman_h
#define Huffman_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000

typedef struct Tree {
	unsigned int frequency;
	char character;
	struct Tree *left;
	struct Tree *right;
} Nodes;

typedef struct Array {
	int size;
	Nodes *table[MAX];
} heap;

typedef struct SaveValues {
	unsigned int frequency;
	unsigned char c;
	unsigned char bits[10];
} NewValue;

typedef struct Hash {
	NewValue *array[256];
} hash;

Nodes *CreatNode(int data, char character, Nodes * left, Nodes *right) {
	Nodes* node = (Nodes*) malloc(sizeof(Nodes));
	node->frequency = data;
	node->character = character;
	node->left = left;
	node->right = right;
	return node;
}

heap *CreatTable(int size_table) {
	int i;
	heap *Table = (heap*) malloc(sizeof(heap));
	for (i = 0; i < size_table; i++) {
		Table->table[i] = NULL;
	}
	return Table;
}

hash *create_hash()
{
    hash* HASH = (hash*) malloc(sizeof(hash));

    for (int i = 0; i < 256; i++)
    {
    	HASH->array[i] = (NewValue*) malloc(sizeof(NewValue));
    	HASH->array[i]->frequency = 0;
    	HASH->array[i]->bits[0] = '\0';
    }
    return HASH;
}

void Swap(Nodes **a, Nodes **b) {
	Nodes *t = *a;
	*a = *b;
	*b = t;
}

int GetParentIndex(int index) {
	return index / 2;
}

int GetChildrenLeftIndex(int index) {
	return index * 2;
}

int GetChildrenRightIndex(int index) {
	return index * 2 + 1;
}

int is_leaf(Nodes *huffman_node) {
	if ((huffman_node->left == NULL) && (huffman_node->right == NULL)) {
		return 1;
	} else {
		return 0;
	}
}

int is_empty(Nodes *root) {
	return (root == NULL);
}

int is_bit_set(unsigned char byte, int i) {

	unsigned char aux = 1 << i;
	return (aux & byte);
}

unsigned char set_bit(unsigned char c, int i)
{
	unsigned char aux = 1 << i;
    	return aux | c;
}

void View(heap *Heap) {
	int i;
	for (i = 1; i <= Heap->size; i++) {
		printf(" %d %c ", Heap->table[i]->frequency, Heap->table[i]->character);
	}
}

void DownHeapMin(int index, heap *Heap) {
	if (index * 2 > Heap->size) {
		return;
	} else {
		int left = GetChildrenLeftIndex(index);
		int Right = GetChildrenRightIndex(index);
		int smallest = index;
		if (left <= Heap->size
				&& Heap->table[left]->frequency
						< Heap->table[smallest]->frequency) {
			smallest = left;
		}
		if (Right <= Heap->size
				&& Heap->table[Right]->frequency
						< Heap->table[smallest]->frequency) {
			smallest = Right;
		}
		if (smallest == index) {
			return;
		} else {
			Swap(&Heap->table[index], &Heap->table[smallest]);
			DownHeapMin(smallest, Heap);
		}
	}
}

Nodes *Pop(heap *Heap) {
	if (Heap->size == 0) {
		return 0;
	} else {
		Nodes *aux = Heap->table[1];
		Heap->table[1] = Heap->table[Heap->size];
		Heap->size--;
		DownHeapMin(1, Heap);
		return aux;
	}
}

void UpHeapMin(int index, heap *Heap) {
	if (index == 1) {
		return;
	} else {
		int Parentidx = GetParentIndex(index);
		if (Heap->table[index]->frequency < Heap->table[Parentidx]->frequency) {
			Swap(&Heap->table[index], &Heap->table[Parentidx]);
			UpHeapMin(Parentidx, Heap);
		}
	}
}

void Insert(int Value, char character, heap *Heap, Nodes *left, Nodes *right) {
	Heap->size++;
	Heap->table[Heap->size] = CreatNode(Value, character, left, right);
	UpHeapMin(Heap->size, Heap);
}

void print_tree_huffman(Nodes *huffman_node) {
	if (huffman_node != NULL) {
		if (((huffman_node->character == '*') || (huffman_node->character == '\\'))
				&& is_leaf(huffman_node)) {
			printf("\\%c", 92);
		}
		else
		{
			printf("%c", huffman_node->character);
			print_tree_huffman(huffman_node->left);
			print_tree_huffman(huffman_node->right);
		}
	}
}

void print_tree_huffman_file(FILE *output_file, Nodes *huffman_node) {
	if (huffman_node != NULL) {
		if (((huffman_node->character == '*') || (huffman_node->character == '\\'))
				&& is_leaf(huffman_node)) {
			fprintf(output_file, "\\%c", '*');
		} else {
			fprintf(output_file, "%c", huffman_node->character);
			print_tree_huffman_file(output_file, huffman_node->left);
			print_tree_huffman_file(output_file, huffman_node->right);
		}

	}
}

int lenght_tree(Nodes *root) {
	int count = 0;
	if (!is_empty(root)) {
		if (is_leaf(root)
				&& (root->character == '*' || root->character == 92)) {
			count = 1;
		}

		count = count + 1 + lenght_tree(root->left);
		count = count + lenght_tree(root->right);
	}

	return count;
}

int count_trash_file(hash *HASH)
{
	int i;
	long long int trash = 0;
	for(i = 0; i < 256; i ++)
	{
		 if(HASH->array[i]->frequency >= 1)
		 {
			 trash += strlen(HASH->array[i]->bits) * HASH->array[i]->frequency;
		 }
	 }

	trash = 8 - (trash % 8);

	 return trash;
}
#endif
