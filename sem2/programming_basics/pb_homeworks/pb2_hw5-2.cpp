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

void showBinaryBrackets(node* nod, bool sibling) {
		cout << nod->num;
		if (nod->left or nod->right)
		{
			cout << " ( ";
			if (nod->left) {
				if (nod->right)
					showBinaryBrackets(nod->left, true);
				else
					showBinaryBrackets(nod->left, false);
			}
			if (nod->right) {
				
					showBinaryBrackets(nod->right, false);
			}
			cout << " ) ";
		}
		if (sibling)
			cout << ", ";
	}

void showBinaryLevels(node* nod, int level) {
	if (!nod)
		return;

	cout << level << "." << nod->num << ";  ";
	showBinaryLevels(nod->left, level + 1);
	showBinaryLevels(nod->right, level + 1);
}


int main() {
	int arr[14] = { 8, 2, 14, 6, 3, 9, 12, 11, 4, 7, 17, 15, 5, 13 };
	node* root = new node; 
	root->left = root->right = NULL; 
	root->num = 10;

	for (int i = 0; i < 14; i++) {
		addNode(root, arr[i]);
	}
	
	showBinaryBrackets(root, false);
	cout << endl << "_________________"<<endl;
	showBinaryLevels(root, 1);
}
