#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct node {
	string word;
	node* left;
	node* right;
};

void addNode(node* nod, string word1) {
	string wordtemp;
	if (nod->word[0] > 96 && nod->word[0] < 123)
		wordtemp = nod->word[0] - 32;
	else
		wordtemp = nod->word[0];
	if (word1[0] > 64 && word1[0] < 91) {
		if (word1[0] < wordtemp[0])
			if (nod->left)
				addNode(nod->left, word1);
			else
			{
				node* newNode = new node;
				newNode->word = word1;
				newNode->left = newNode->right = NULL;
				nod->left = newNode;
			}
		else
			if (nod->right)
				addNode(nod->right, word1);
			else
			{
				node* newNode = new node;
				newNode->word = word1;
				newNode->left = newNode->right = NULL;
				nod->right = newNode;
			}
	}
	else if (word1[0] > 96 && word1[0] < 123) {
		if (word1[0]-32 < wordtemp[0])
			if (nod->left)
				addNode(nod->left, word1);
			else
			{
				node* newNode = new node;
				newNode->word = word1;
				newNode->left = newNode->right = NULL;
				nod->left = newNode;
			}
		else
			if (nod->right)
				addNode(nod->right, word1);
			else
			{
				node* newNode = new node;
				newNode->word = word1;
				newNode->left = newNode->right = NULL;
				nod->right = newNode;
			}
	}
	else {
		cout << "bad word; try again"; 
		return;
	}

}




void sortWords(node* nod, string words[5], int max) {
	for (int i = 0; i < max; i++) {
		addNode(nod, words[i]);
	}
}
void showBinary(node* nod) {
	if (nod)
	{
		showBinary(nod->left);
		cout << nod->word << "; ";
		showBinary(nod->right);
	}
}



int main() {

	string words[5] = { "house" , "Monkey", "game", "donkey", "Queue" };
	for (int i = 0; i < 5; i++) {
		cout << words[i] << "; ";
	}

	node* root = new node;
	root->left = root->right = NULL;
	root->word = "Start";

	sortWords(root, words, 5);
	showBinary(root);

}

