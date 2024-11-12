#include <iostream>
using namespace std;

struct node {
	int data;
	node* next;
};
struct matrix {
	node* list[5];
};

matrix createMatrix1() {
	matrix mtr1;

	node* last;
	for (int j = 0; j < 5; j++) {
		mtr1.list[j] = new node;
		mtr1.list[j]->data = NULL;
		last = mtr1.list[j];
		for (int i = 1; i < 6; i++) {
			if (!mtr1.list[j]->data) { ///щоб не вводити вручну. спочатку взагалі то я перший елемент вручну вводив, але мені це очі кололо і я зробив так
				mtr1.list[j]->data = i;
				last = mtr1.list[j];
			}
			else {
				node* temp = new node;
				temp->data = i;
				temp->next = NULL;
				last->next = temp;
				last = temp;
			}
		}
	}

	return mtr1;
}

matrix createMatrix2() {
	matrix mtr2;
	node* last = new node;
	for (int j = 0; j < 5; j++) {
		mtr2.list[j] = new node;
		mtr2.list[j]->data = NULL;
		for (int i = 5; i > 0; i--) {
			if (!mtr2.list[j]->data) {///щоб не вводити вручну. спочатку взагалі то я перший елемент вручну вводив, але мені це очі кололо і я зробив так
				
				mtr2.list[j]->data = i;
				last = mtr2.list[j];
			}
			else {
				node* temp = new node;
				temp->data = i;
				temp->next = NULL;
				last->next = temp;
				last = temp;
			}
		}
	}

	return mtr2;
}

void showMtr(matrix mtr1)
{
	for (int i = 0; i < 5; i++)
	{
		node* temp;
		temp = mtr1.list[i];
		while (temp)
		{
			cout << temp->data << "; ";
			temp = temp->next;
		}
		cout << endl;
	}
}

matrix mtrSum(matrix mtr1, matrix mtr2) { ///працює тільки якщо в матрицях однакова кількість елементів. 
	matrix mtrSum;
	node* mtr1Last;
	node* mtr2Last;
	node* last;
	for (int j = 0; j < 5; j++) {
		mtrSum.list[j] = new node;
		mtrSum.list[j]->data = mtr1.list[j]->data + mtr2.list[j]->data;
		last = mtrSum.list[j];
		mtr1Last = mtr1.list[j];
		mtr2Last = mtr2.list[j];
		for (int i = 1; i < 5; i++) {
			if (mtr1Last->next && mtr2Last->next) {
				mtr1Last = mtr1Last->next;
				mtr2Last = mtr2Last->next;
			}
			node* temp = new node;
			temp->data = mtr1Last->data + mtr2Last->data;
			temp->next = NULL;
			last->next = temp;
			last = temp;
		}
	}

	return mtrSum;
}

void listToArr(matrix mtrSum, int arr[][5]) {
	node* last;
	for (int j = 0; j < 5; j++) {
		last = mtrSum.list[j];
		for (int i = 0; i < 5; i++) {
			arr[j][i] = last->data;
			last = last->next;
		}
	}
	return;
}

int main() {
	matrix mtr1 = createMatrix1();
	matrix mtr2 = createMatrix2();
	matrix summ = mtrSum(mtr1, mtr2);
	showMtr(mtr1);
	cout << "________________" << endl;
	showMtr(mtr2);
	cout << "________________" << endl;
	showMtr(summ);
	int arr[5][5];
	listToArr(summ, arr);
	for (int i = 0; i < 5; i++) {
		cout << endl;
		for (int j = 0; j < 5; j++) {
			cout << arr[i][j] << "; ";
		}
	}
}