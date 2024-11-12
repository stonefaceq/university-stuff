#include <iostream>
using namespace std;


struct node {
	int num;
	node* offspring[3];
};

void offspringsNULL(node* nod)
{
	for (int i = 0; i < 3; i++)
		nod->offspring[i] = NULL;
}

void createSimpleTree(node* root)
{
	root->offspring[0] = new node;
	offspringsNULL(root->offspring[0]);
	root->offspring[0]->num = 2;
	root->offspring[0]->offspring[0] = new node;
	offspringsNULL(root->offspring[0]->offspring[0]);
	root->offspring[0]->offspring[0]->num = 5;

	root->offspring[1] = new node;
	offspringsNULL(root->offspring[1]);
	root->offspring[1]->num = 3;
	root->offspring[1]->offspring[0] = new node;
	offspringsNULL(root->offspring[1]->offspring[0]);
	root->offspring[1]->offspring[0]->num = 6;
	root->offspring[1]->offspring[1] = new node;
	offspringsNULL(root->offspring[1]->offspring[1]);
	root->offspring[1]->offspring[1]->num = 7;

	root->offspring[2] = new node;
	offspringsNULL(root->offspring[2]);
	root->offspring[2]->num = 4;
	root->offspring[2]->offspring[0] = new node;
	offspringsNULL(root->offspring[2]->offspring[0]);

	root->offspring[2]->offspring[0]->num = 8;

	root->offspring[2]->offspring[0]->offspring[0] = new node;
	offspringsNULL(root->offspring[2]->offspring[0]->offspring[0]);

	root->offspring[2]->offspring[0]->offspring[0]->num = 9;

	root->offspring[2]->offspring[0]->offspring[1] = new node;
	offspringsNULL(root->offspring[2]->offspring[0]->offspring[1]);

	root->offspring[2]->offspring[0]->offspring[1]->num = 10;

	root->offspring[2]->offspring[0]->offspring[2] = new node;
	offspringsNULL(root->offspring[2]->offspring[0]->offspring[2]);

	root->offspring[2]->offspring[0]->offspring[2]->num = 11;

	root->offspring[2]->offspring[0]->offspring[2]->offspring[0] = new node;
	offspringsNULL(root->offspring[2]->offspring[0]->offspring[2]->offspring[0]);

	root->offspring[2]->offspring[0]->offspring[2]->offspring[0]->num = 33;
}

void show(node* nod, int level)
{
	if (!nod)
		return;

	cout << level << ", " << nod->num << ";  ";

	for (int i = 0; i < 3; i++)
		show(nod->offspring[i], level + 1);


}

void heightTrinary(node* nod, int current, int* max) {
	if (!nod)
		return;
	if (current > *max)
		*max = current;
	heightTrinary(nod->offspring[0], current+1, max);
	heightTrinary(nod->offspring[1], current + 1, max);
	heightTrinary(nod->offspring[2], current + 1, max);
}

int main() {
	node* root;
	root = new node;
	root->num = 1;
	root->offspring[0] = root->offspring[1] = root->offspring[2] = NULL;

	createSimpleTree(root);

	show(root, 1);

	int max = 0;

	heightTrinary(root, 0, &max);

	cout << endl << "height:" << max;
}