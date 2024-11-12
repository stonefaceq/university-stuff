#include <iostream>
using namespace std;

struct node {
	int num;
	node* next, * prev;

};

struct index {
	int pos;
	int num;
	index* next, * prev;

};

void addToList(node** head, node** tail, int data, int pos) {
	if (pos < 1) {
		cout << "invalid position. it must be a positive number" << endl;
		return;
	}
	node* temp;
	temp = new node;
	temp->num = data;
	if (!*head)
	{

		temp->next = temp->prev = NULL;
		*head = *tail = temp;
	}
	else
	{
		if (pos == 1) {
			(*head)->prev = temp;
			temp->next = *head;
			temp->prev = NULL;
			*head = temp;
			return;
		}
		int i = 1;
		node* search;
		search = *head;
		while (i < pos && search != *tail) {
			search = search->next;
			i++;
		}
		if (pos > i) {
			if (pos == i + 1) {
				(*tail)->next = temp;
				temp->prev = *tail;
				temp->next = NULL;
				*tail = temp;
				return;
			}
			else {
				cout << "invalid position. size of list is too small." << endl;
				return;
			}
		}
		else {

			search->prev->next = temp;
			temp->prev = search->prev;
			search->prev = temp;
			temp->next = search;
			return;
		}
	}
}

void sparseList(node **head, node **tail) {
	addToList(head, tail, 0, 1);
	addToList(head, tail, 0, 2);
	addToList(head, tail, 1, 3);
	addToList(head, tail, 0, 4);
	addToList(head, tail, 3, 5);
	addToList(head, tail, 0, 6);
	addToList(head, tail, 0, 7);
	addToList(head, tail, 4, 8);
	addToList(head, tail, 0, 9);
}

void showList(node* head, node* tail)
{
	node* temp = head;
	while (temp)
	{
		cout << temp->num << endl;
		if (temp->next != head)
			temp = temp->next;
		else temp = NULL;
	}
}

void showListI(index* head, index* tail)
{
	index* temp = head;
	while (temp)
	{
		cout << temp->pos << "." << temp->num << endl;
		if (temp->next != head)
			temp = temp->next;
		else temp = NULL;
	}
}
int zeroAmount(node* head, node* tail, int m1, int m2) {
	int a = 0;
	if ((m1 == m2) || (m1 > m2) || (m1<1) || (m2==m1+1))
		return 0;
	else {
		
		node *search1 = head;
		node *search2 = head;
		for (int i = 1; i < m1; i++) {
		search1 = search1->next;
		if (search1 == tail)
			return 0;
		}
		for (int j = 1; j < m2; j++) {
			search2 = search2->next;
			if (search2->next == NULL) {
				search2 = tail; //// ??????????
				break;
			}
		}
		
		 while (search1->next != search2) {
			 search1 = search1->next;
			 
			 if (search1->num == 0)
				 a++;
		}
		
	}
	return a;
}

void compressedList(node* head, node* tail, index **Ihead, index **Itail) {
	int i = 1;
	while (true) {
		if ((head->num) != 0) {
			index* temp = new index; 
			temp->num = head->num;
			temp->pos = i;
			if (!*Ihead) {
				*Ihead = *Itail = temp;
				(*Ihead)->next = NULL;
				(*Itail)->next = NULL;
			}
			else {
				temp->prev = *Itail; 
				(*Itail)->next = temp;
				temp->next = NULL;
				*Itail = temp;

			}
		}
		head = head->next;
		i++;
		if ((head->next) == NULL) {
			break;
		}
	}

}

int main() {
	node* head, * tail;
	head = tail = NULL;
	index* Ihead, * Itail;
	Ihead = Itail = NULL;
	sparseList(&head, &tail);
	cout << endl;
	cout << endl;
	cout << zeroAmount(head, tail, 1, 15);
}