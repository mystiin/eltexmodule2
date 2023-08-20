#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* newNode(int data) {
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

struct Node* insertNode(struct Node* root, int data) {
	if (root == NULL) {
		return newNode(data);
	}

	if (data < root->data) {
		root->left = insertNode(root->left, data);
	}
	else if (data > root->data) {
		root->right = insertNode(root->right, data);
	}

	return root;
}

void printTree(struct Node* root, int space) {
	if (root == NULL) {
		return;
	}

	space += 5;

	printTree(root->right, space);

	for (int i = 5; i < space; i++) {
		printf(" ");
	}

	printf("%d\n", root->data);

	printTree(root->left, space);
}
int treeHeight(struct Node* root) {
	if (root == NULL) {
		return 0;
	}

	int leftHeight = treeHeight(root->left);
	int rightHeight = treeHeight(root->right);

	return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}
int main() 
{
	struct Node* root = NULL;
	int choice;
	do
	{
		printf("1.Add Node in tree\n2.Print tree\n0.Exit\nInput: ");
		scanf_s("%d", &choice);
		int value;
		switch (choice)
		{
		case 1:
			scanf_s("%d", &value);
			root = insertNode(root, value);
		case 2:
			printTree(root, 0);
		}
	} while (choice != 0);
	return 0;
}
