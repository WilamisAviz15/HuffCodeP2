#include <stdio.h>
#include <stdlib.h>

typedef struct Set {
	int number, rank;
	struct Set*parent;
} TreeNode;

TreeNode *makeSet(int value) {
	TreeNode *node = malloc(sizeof(TreeNode));
	node->number = value;
	node->parent = node;
	node->rank = 0;
	return node;
}

TreeNode *findSet(TreeNode *node) {
	if (node != node->parent) {
		node->parent = findSet(node->parent);
	}
	return node->parent;
}

void Attach(TreeNode *node_x, TreeNode *node_y) {
	if (node_x->rank > node_y->rank) {
		node_y->parent = node_x;
	} else {
		node_x->parent = node_y;
		if (node_x->rank == node_y->rank) {
			node_y->rank = (node_y->rank) + 1;
		}
	}
}
void Union(TreeNode *node_x, TreeNode *node_y) {
	Attach(findSet(node_x), findSet(node_y));
}
int main() {
	int option, elements, i, index, index2;
	TreeNode *id[1000];
	do {
		printf("\n");
		printf("1.GenerateSets\n");
		printf("2.Consult\n");
		printf("3.Union\n");
		printf("4.Exit\n");
		printf("Enter Choice : ");
		scanf("%d", &option);
		switch (option) {
		case 1:
			printf("Enter the amount of elements:\n");
			scanf("%d", &elements);
			for (i = 1; i <= elements; i++) {
				id[i] = NULL;
				id[i] = makeSet(i);
			}
			break;
		case 2:
			printf("\nEnter index & index2 : ");
			scanf("%d%d", &index, &index2);
			if (findSet(id[index]) == findSet(id[index2])) {
				printf("S\n");
			} else {
				printf("N\n");
			}
			break;
		case 3:
			printf("\nEnter index & index2 : ");
			scanf("%d%d", &index, &index2);
			Union(id[index], id[index2]);
			break;
		case 4:
			break;
		}
	} while (option != 4);
	return 0;
}
