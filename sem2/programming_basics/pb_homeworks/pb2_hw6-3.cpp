#include <iostream>
using namespace std;


struct node {
	int num;
	node* left;
	node* right;
};

void addNode(node* nod, int number) {
	if (number < nod->num)
		if (nod->left)
			addNode(nod->left, number);
		else
		{
			node* newNode = new node;
			newNode->num = number;
			newNode->left = newNode->right = NULL;
			nod->left = newNode;
		}
	else
		if (nod->right)
			addNode(nod->right, number);
		else
		{
			node* newNode = new node;
			newNode->num = number;
			newNode->left = newNode->right = NULL;
			nod->right = newNode;
		}

}

int maxUndVal(node* nod, int V, int *max) {

	if (nod->right and nod->num < V)
		maxUndVal(nod->right, V, max);
	if (nod->num < V && nod->num > *max)
		*max = nod->num;

	if (nod->left)
		maxUndVal(nod->left, V, max);
	return *max;
}


int main() {
	int arr[14] = { 8, 2, 14, 6, 3, 9, 12, 11, 4, 7, 17, 15, 5, 13 };
	node* root = new node;
	root->left = root->right = NULL;
	root->num = 10;

	for (int i = 0; i < 14; i++) {
		addNode(root, arr[i]);
	}
	int max = 0;


	cout << "max= " << maxUndVal(root, 12, &max);
}
