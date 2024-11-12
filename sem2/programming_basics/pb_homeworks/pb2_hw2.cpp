#include <iostream>
using namespace std;

struct node {
	int num;
	node *next, *prev;

};

void createList(node** head, node** tail, int amount) {
	if (amount < 1) {
		cout << "error. insert a positive number of elements." << endl;
		return;
	}
	node* temp;
	
	for (int i=0; i < amount; i++) {
		temp = new node;
		if (!*head) {
			temp->next = temp->prev = temp;
			temp->num = rand();
			*head = *tail = temp;
		}
		else {
			temp->num = rand(); 
			(*head)->prev = temp; 
			temp->next = *head; 
			temp->prev = *tail; 
			(*tail)->next = temp; 
			*tail = temp; 
		}
	}
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

		temp->next = temp->prev = temp;
		*head = *tail = temp;
	}
	else 
	{
		if (pos == 1) {
			(*head)->prev = temp;
			temp->next = *head;  
			(*tail)->next = temp;
			temp->prev = *tail;
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
				temp->next = *head; 
				(*head)->prev = temp; 
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

void deleteFrList(node** head, node** tail, int pos) {
	if (pos < 1) {
		cout << "invalid position. it must be a positive number" << endl;
		return;
	}
	if (!*head)
	{ 
		cout << "the list is empty, head does not exist." << endl;
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
		cout << "no such element. list is too short." << endl;
	}
	else {
		if (search == *tail) {
			(*tail)->prev->next = *head; 
			(*head)->prev = (*tail)->prev;
			*tail = (*tail)->prev;
			return;
		}
		if (search == *head) {
			(*head)->next->prev = *tail;
			(*tail)->next = (*head)->next;
			*head = (*head)->next;
			return;
		}
		search->next->prev = search->prev; 
		search->prev->next = search->next;
	}

}

void menu() {
	char ch;
	node* head, * tail;
	head = tail = NULL;
	do
	{
		cout << "Choose an action:" << endl;
		cout << ">> C to create list" << endl;
		cout << ">> S to show all" << endl;
		cout << ">> A to add one" << endl;
		cout << ">> D to delete one element" << endl;
		cout << ">> Q to quit" << endl;
		cin >> ch;
		switch (ch)
		{
		case 'C':
			cout << "Create a stack:" << endl;
			int num1, num2;
			cout << "insert your amount of elements:" << endl;
			cin >> num1;
			createList(&head, &tail, num1);
			break;
		case 'S':
			cout << "Show:" << endl;
			showList(head, tail);
			break;
		case 'A':
			cout << "Add one." << endl;
			cout << "insert an index of your element" << endl;
			cin >> num1;
			cout << "what element do u want to add?" << endl;
			cin >> num2;
			addToList(&head, &tail, num2, num1);
			break;
		case 'D':
			cout << "Delete" << endl;
			cout << "which element do u want to delete?" << endl; 
			cin >> num1;
			deleteFrList(&head, &tail, num1);
			break;
		case 'Q':
			cout << "Quit" << endl;
			break;
		default:
			cout << " try again!" << endl;
			break;
		}


	} while (ch != 'Q');
}

int main() {
	menu();
}
