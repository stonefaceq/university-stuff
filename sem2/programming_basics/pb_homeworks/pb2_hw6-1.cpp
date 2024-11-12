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

int sumOrdered(node* nod, int min, int max, int* sum) { 
	if (nod->left && nod->num >= min) {
		sumOrdered(nod->left, min, max, sum);
	}
	if (nod->right && nod->num <= max) {
		sumOrdered(nod->right, min, max, sum);
	}
	if (nod->num >= min && nod->num <= max) {
		*sum = *sum + (nod->num);
	}
	return *sum;
}

int sumUnordered(node* nod, int min, int max, int* sum) {
	if (nod->left) 
		sumUnordered(nod->left, min, max, sum);
	if (nod->num >= min && nod->num <= max)
		*sum += nod->num;
	if (nod->right) 
		sumUnordered(nod->right, min, max, sum);

	return *sum;
}


int main() {
	int arr[14] = { 8, 2, 14, 6, 3, 9, 12, 11, 4, 7, 17, 15, 5, 13 };
	node* root = new node; 
	root->left = root->right = NULL; 
	root->num = 10;

	for (int i = 0; i < 14; i++) {
		addNode(root, arr[i]);
	}
	int m, n;
	int sum = 0;
	cout << "insert value M (minimum): ";
	cin >> m;
	cout << "insert value N (maximum): ";
	cin >> n;

//	cout << "sum= " << sumOrdered(root, m, n, &sum);
	cout << "sum= " << sumUnordered(root, m, n, &sum);
}
