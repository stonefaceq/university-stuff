#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;


void rootsOfSquareEquation(int a, int b, int c) { //for 1st task
	int D = b * b - 4 * a * c;
	if (D < 0) {
		cout << "Incorrect input" << endl;
		return;
	}
	else if (D == 0) {
		int x1 = (-b + sqrt(D)) / 2 * a;
		cout << x1 << endl;
		return;
	}
	else {
		int x1 = (-b + sqrt(D)) / 2 * a;
		cout << x1 << " and ";
		int x2 = (-b - sqrt(D)) / 2 * a;
		cout << x2 << endl;
	}
}

////////////////////////////////

bool doesTriangleExist(float a, float b, float c) { //for triangle
	if (a > b && a > c) {
		float sum = b + c;
		if (sum > a)
			return true;
		else
			return false;
	}
	else if (b > a && b > c) {
		float sum = a + c;
		if (sum > b)
			return true;
		else
			return false;
	}
	else if (c > a && c > b) {
		float sum = b + a;
		if (sum > c)
			return true;
		else
			return false;
	}

}


bool kindOfTriangle(float a, float b, float c) {
	if (a * a > b * b + c * c && b * b > a * a + c * c && c * c > a * a + b * b)
		return true;
	else
		return false;
}


float areaOfTriangle(float a, float b, float c) {
	float p = (a + b + c) / 2;
	float S = sqrt(p * (p - a) * (p - b) * (p - c));
	return S;
}


////////////////////////////////////////////////////


bool isAnArmstrongNumber(int num, int amount, int array[]) { //for armstrong
	int sum = 0;
	int i = 0;
	for (i = 0; i < amount; i++) {
		sum += pow(array[i], amount);
	}
	if (num == sum)
		return true;
	else
		return false;
}


////////////////////////////////////////////////////


int jacobsthalNumber(int n) {           ////for jacobsthal
	int x1 = 0;
	int x2 = 1;
	int x3 = 1;
	for (int i = 3; i <= n+1; i++) {
		x3 = x2 + 2 * x1;
		x1 = x2;
		x2 = x3;
	}
	return x3;
}

////////////////////////////////////////////////////

int findANumber(int number, int array[], int first, int last) {  ///for 5th task
	if (first > last)
		return -1;

	int mid = (first + last) / 2;

	if (number == array[first])
		return first;
	else if (number == array[last])
		return last;
	else if (number == array[mid])
		return mid;
	else if (number < array[mid])
		return findANumber(number, array, mid + 1, last - 1);
	else if (number > array[mid])
		return findANumber(number, array, first + 1, mid - 1);
}

////////////////////////////////////////////////////

bool isItSimple(int num) { ///for 6th task
	for (int i = 3; i <= (sqrt(num)); i += 2)
		if (num % i == 0)
			return false;
	return true;


}

////////////////////////////////////////////////////
int GCD(int a, int r) { //for 7th task
	if (r == 0)
		return a;
	return GCD(r, a % r);
}

void mutuallyPrimeNumbers(int m, int n, int r) {
	for (int i = m; i <= n; i++) {
		if (GCD(i, r) == 1)
			cout << i << " is a mutually prime number with number R." << endl;
	}
	return;
}

////////////////////////////////////////////////////

bool isItUnique(int index, int array[]) { //for 8th task
	bool unique = true;
	for (int j = 1; j < 15; j++) {
		if (array[index] == array[index + j] || array[index] == array[index - j])
			unique = false;
		else
			unique = true;
		if (unique == false)
			return unique;
	}
	return unique;
}


/*void inAscendingOrder(int array[], int size) {   //намагався зробити функцію для впорядкування масиву по зростанню = не вийшло
	int array83[15];
	array[1] = array83[1];
	for (int i = 0; i < size; i++) {
		array[i] = array83[i];
	}
	for (int k = 0; k < size; k++) {
		for (int a = 0; a < size; a++) {
			if (array[k] > array[a]) {
				array83[size - 1] = array[k];
				array83[k] = array[k + 1];
			}
		}
	}
	cout << array83[1] << endl;
	return array[];
} */



int main() {

	int choice;
	do
	{
		cout << "CHOOSE THE TASK." << endl;
		cout << ">>> 1 FOR TASK 1" << endl << ">>> 2 FOR TASK 2" << endl << ">>> 3 FOR TASK 3" << endl << ">>> 4 FOR TASK 4" << endl;
		cout << ">>> 5 FOR TASK 5" << endl << ">>> 6 FOR TASK 6" << endl << ">>> 7 FOR TASK 7" << endl << ">>> 8 FOR TASK 8" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: {
			int a, b, c;
			cout << "A= ";
			cin >> a;
			cout << "B= ";
			cin >> b;
			cout << "C= ";
			cin >> c;
			cout << "your equation is: " << a << "x^2 + " << b << "x + " << c << "." << endl;
			cout << "your roots are: ";
			rootsOfSquareEquation(a, b, c);

			break;
		}
		case 2: {
			float tria1, tria2, tria3;
			cout << "A= ";
			cin >> tria1;
			cout << "B= ";
			cin >> tria2;
			cout << "C= ";
			cin >> tria3;
			if (tria1 <= 0 || tria2 <= 0 || tria3 <= 0) {
				cout << "incorrect input";
				return 0;
			}
			if (doesTriangleExist(tria1, tria2, tria3))
				cout << "this triangle exists!" << endl << endl;
			else {
				cout << "this triangle does not exist!";
				return 0;
			}

			if (kindOfTriangle)
				cout << "triangle is acute!" << endl << endl;
			else
				cout << "triangle is not acute!";

			cout << "area of your triangle equals:" << areaOfTriangle(tria1, tria2, tria3) << endl;
			break; }
		case 3: {
			int num;
			cout << "enter a number" << endl;
			cin >> num;
			int numCopy = num; //змінна введена щоб не похєрити змінну num в циклі while
			int array3[15];
			int i = 0;
			int sum = 0;
			int amount = 0;
			while (numCopy > 0)
			{
				array3[amount] = numCopy % 10;
				numCopy /= 10;
				amount++;
			}

			if (isAnArmstrongNumber(num, amount, array3))
				cout << "this is an Armstrong number!" << endl;
			else
				cout << "this isn't an Armstrong number!" << endl;
			break;
		}
		case 4:
			int n1;
			cout << "Enter an index of a number that you want to find:  ";
			cin >> n1;
			if (n1 < 0) {
				cout << "number must be greater than 0" << endl;
				return 0;
			}
			cout << "your num is:" << jacobsthalNumber(n1) << endl;

			return 0;
			break;
		case 5:
			int array5[20];
			int number, first, last;
			for (int i = 0; i < 20; i++) {
				array5[i] = 500 / ((i + 1));
				cout << array5[i] << endl;
			}
			cout << "Enter a number to find: ";
			cin >> number;
			cout << "Enter a range where you want to fing your number. First index:";
			cin >> first;
			cout << "Enter a range where you want to fing your number. Last index:";
			cin >> last;
			if (number < array5[19] || number > array5[0]) {
				cout << "Incorrect input! No such number in array.";
				return 0;
			}
			if (findANumber(number, array5, first, last) == -1) {
				cout << "Incorrect input! Something seems wrong.";
				return 0;
			}
			cout << "your number's index is: " << findANumber(number, array5, first, last) << endl;
			break;
		case 6:
			cout << "Number 2 is simple." << endl;
			for (int i = 3; i <= 100; i += 2) {
				if (isItSimple(i))
					cout << "Number " << i << " is simple." << endl;
			}
			break;
		case 7:
			int m, n, r;
			cout << "Enter number M: ";
			cin >> m;
			cout << "Enter number N: ";
			cin >> n;
			if (m > n) {
				cout << "Number N must be greater than number M.";
				return 0;
			}
			cout << "Enter number R: ";
			cin >> r;

			mutuallyPrimeNumbers(m, n, r);
			break;
		case 8: {
			int index82 = 0;
			int array8[] = { 2, 5, 6, 1, 3, 4, 9, 4, 8, 1, 3, 4, 2, 7, 1 };
			int array82[15];
			for (int k = 0; k < 14; k++) {
				cout << array8[k] << ";   ";
			}
			for (int i = 0; i < 14; i++) {
				if (isItUnique(i, array8)) {
					cout << endl << array8[i] << "  is a unique number." << endl;
					array82[index82] = array8[i];
					index82++;
				}
			}

			int number8 = 0;
			
				for (int j = 0; j < index82; j++) { 
					for (int k = 0; k < index82; k++) {
						if (array82[j] < array82[k]) {
							number8 = array82[j];
							array82[j] = array82[k];
							array82[k] = number8;
						}
					}
				}
			
			for (int a = 0; a < index82; a++) {
				cout << array82[a] << ";    ";
			}
			cout << endl;
			break;
		}
		default:
			cout << "BAD CHOICE! TRY AGAIN!" << endl;
			break;
		}
	} while (choice != 0);

	return 0;
}