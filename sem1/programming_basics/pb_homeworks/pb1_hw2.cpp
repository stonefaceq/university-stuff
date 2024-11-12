#include <iostream>
using namespace std;

void matrixVector(int matrix[][4], int max, int last, int vctr[]) {
	int sum;
	int q;
	for (int i = 0; i <= max/2; i++) {
		sum = 0;
		q = 0;
		for (int j = 0; j <= i; j++) {
			sum += matrix[j][i - q];
			q++;
		}
		vctr[i] = sum;
	}
	int iter = 6;
	for (int i = last; i > 0; i--) {
		sum = 0;
		q = 0;
		for (int j = last; j >=i; j--) {
			sum += matrix[j][i + q];
			q++;
		}
		vctr[iter] = sum;
		iter -- ;
	}

	return;
}


void deleteSameChars(char str[], int size) {
	for (int i=0; i < size - 1; i++) {
		if (str[i] == str[i + 1]) {
			for (int j = i + 1; j < size; j++) {
				str[j] = str[j + 1]; 
				
			}
			size--;
			i--;
		}
	}
	for (int k = 0; k < size; k++) {
		cout << str[k] << endl;
	}
}

int main(int argc, char** argv) {
	/*int matrix[4][4] = {{1,2,3,4},
						{2,3,4,5},
						{3,4,5,6},
						{4,5,6,7} };
	int vctrSize = 4 * 2 - 1;
	int vctr[6]; 
	matrixVector(matrix, vctrSize, 3, vctr);
	for (int i = 0; i < vctrSize; i++) {
		cout << vctr[i] << endl;
	}
	*/

	/// 2nd task
	const int size = 100;
	char str[size];
	cout << "enter a line: ";
	cin.getline(str, size); 
	int size1 = strlen(str); 

	deleteSameChars(str, size1);
	return 0;
}

