#include <iostream>
using namespace std;

// create stack / done
// add element / done
// add 10 elements /done
// show stack / done
// delete stack / done
// show i-th element / done
// menu

struct node {
	int num;
	node* next;
};

node createStack(node** head, int amount) {
	node* temp;
	temp = new node;
	for (int i = 0; i < amount; i++) {
		temp = new node;
		temp->num = rand();
		if (!head)
			temp->next = NULL;
		else
			temp->next = *head;

		*head = temp;
	}
	return **head;
}

void showStack(node* head) {
	while (head) {
		cout << head->num << endl;
		head = head->next;
	}
}

void addToStack(node** head, int value) {
	node* temp;
	temp = new node;
	temp->num = value;
	if (!head)
		temp->next = NULL;
	else
		temp->next = *head;

	*head = temp;
}
void addMoreToStack(node** head, int amount) {
	node* temp;
	temp = new node;
	for (int i = 0; i < amount; i++) {
		temp = new node;
		temp->num = i;
		if (!head)
			temp->next = NULL;
		else
			temp->next = *head;

		*head = temp;
	}
}

void deleteStack(node** head) {
	node* temp;
	if (!*head) {
		cout << "stack is already empty";
		return;
	}
	while (*head) {
		temp = *head;
		*head = (*head)->next;
		delete temp;
	}
	cout << "your stack has been deleted!" << endl;
}

void showElement(node* head, int number) {
	node* temp;
	if (number < 1) {
		cout << "wrong number!!!!" << endl;
		return;
	};
	for (int i = 1; i < number; i++) {
		temp = head->next;
		head = temp;
		if (!head) {
			cout << "wrong number!!!!" << endl;
			return;
		};

	}
	cout << "your element is:" << head->num << endl;
}

int averageStack(node* head) {
	int sum = 0;
	int count = 0;
	float average;
	while (head) {
		sum += head->num;
		head = head->next;
		count++;
	}
	if (count == 0) {
		cout << "error" << endl;
		return -1;
	}

	average = float(sum) / count;
	return average;
}

int biggestValue(node* head) {
	int biggest= head->num;
	while (head->next) {
		if ((head->next->num) > (head->num) && (head->next->num) > biggest) {
			biggest = head->next->num;
		}
		head = head->next;
	}

	return biggest;
}

int smallestValue(node* head) {
	int smallest = head->num;
	while (head->next) {
		if ((head->next->num) < (head->num) && (head->next->num) < smallest) {
			smallest = head->next->num;
		}
		head = head->next;
	}

	return smallest;
}

void menu() {
	char ch;
	node* head = NULL;
	do
	{
		cout << "Choose an action:" << endl;
		cout << ">> A to add new" << endl;
		cout << ">> C to create stack" << endl;
		cout << ">> S to show all" << endl;
		cout << ">> I to show i-th element" << endl;
		cout << ">> D to delete all" << endl;
		cout << ">> M to add many elements" << endl;
		cout << ">> V to calculate average" << endl;
		cout << ">> B to calculate biggest value" << endl;
		cout << ">> L to calculate smallest value" << endl;
		cout << ">> Q to quit" << endl;
		cin >> ch;
		switch (ch)
		{
		case 'A':
			cout << "add" << endl;
			int number;
			cout << "insert your number that u want to add:" << endl;
			cin >> number;
			addToStack(&head, number);
			break;
		case 'C':
			cout << "Create a stack:" << endl;
			cout << "insert your amount of elements:" << endl;
			cin >> number;
			createStack(&head, number);
			break;
		case 'S':
			cout << "Show:" << endl;
			showStack(head);
			break;
		case 'D':
			cout << "Delete" << endl;
			deleteStack(&head);
			break;
		case 'M':
			cout << "Add many:" << endl;
			cout << "Insert your amount of elements:" << endl;
			cin >> number;
			addMoreToStack(&head, number);
			break;
		case 'I':
			cout << "how I-th:" << endl;
			cout << "Insert your element's number (from end): " << endl;
			cin >> number;
			showElement(head, number);
			break;
		case 'Q':
			cout << "Quit" << endl;
			break;
		case 'V':
			cout << "Average is: " << averageStack(head) <<endl;
			break;
		case 'B':
			cout << "Biggest is: " << biggestValue(head) << endl;
			break;
		case 'L':
			cout << "Smallest is: " << smallestValue(head) << endl;
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