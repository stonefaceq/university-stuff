
#include <iostream>
using namespace std;
#include <string>
#include <math.h>

void columnMax(int arr[7][5], int maxi, int maxj, int max[5]) { //1st task
	int tempmax;
	for (int j = 0; j < maxj; j++) {
		tempmax = 0;
		for (int i = 1; i < maxi; i++) {
			if (arr[i][j] > arr[i - 1][j] && arr[i][j] > tempmax) {
				max[j] = arr[i][j];
				tempmax = arr[i][j];
			}
		}
	}

}

int findMin(int arr[], int max) {
	int min = arr[0];
	for (int i = 0; i < max - 1; i++) {
		if (arr[i] > arr[i + 1] && arr[i + 1] < min) {
			arr[i + 1] = min;
		}
	}
	return min;
}
///////////////////////////
void upperLetters(char str[], int size) { // 2nd task
	for (int i = 0; i < size; i++) {
		if (str[i] == 32 || str[i] == 44 || str[i] == 46) {
			if (str[i + 1] != 32 && str[i + 1] != 44 && str[i + 1] != 46) {
				str[i + 1] = toupper(str[i + 1]);
			}
		}
	}
	str[0] = toupper(str[0]);
	
	cout << str << endl;
}


//////////////////////
bool complicatedPalindrome(int num) {
	bool palindrome = true;
	int length1 = 0;
	int length2 = 0;
	int numCopy = num;
	int arr1[10];
	int arr2[10];
	int numSquare = num * num;
	while (numCopy > 0)
	{
		arr1[length1] = numCopy % 10;
		numCopy /= 10;
		length1++;
	}
	numCopy = numSquare;
	while (numCopy > 0)
	{
		arr2[length2] = numCopy % 10;
		numCopy /= 10;
		length2++;
	}
	for (int i = 0; i < length1 / 2; i++)
	{
		if (arr1[i] != arr1[length1 - i - 1])
			return false;
	}
	for (int i = 0; i < length2 / 2; i++)
	{
		if (arr2[i] != arr2[length2 - i - 1])
			return false;
	}
	return true;
}



int main(int argc, char** argv) {
	/// 1st task

	/*int maxColumn[5];
	int matrix[7][5] = { {1,2,3,4,5},
						{2,3,9,5,0},
						{1,3,5,0,2},
						{3,3,3,3,4},
						{5,1,4,5,2},
						{3,6,2,8,4},
						{1,4,4,6,7} };
	columnMax(matrix, 7, 5, maxColumn);
	for (int k = 0; k < 5; k++) {
		cout << maxColumn[k] << endl;
	}
	cout << "min= " << findMin(maxColumn, 5);
	return 0;
}
*/


///2nd task


	const int size = 100;
	char str1[size];
	cout << "Enter a line:";
	cin.getline(str1, size);
	int size1 = strlen(str1);
	upperLetters(str1, size);
	return 0;
}

  


///3rd task

/*
const int N = 500;
int j = 0;
int arrayTrue[N];
for (int i = 0; i <= N; i++) {
	if (complicatedPalindrome(i)) {
		arrayTrue[j] = i;
		j++;
	}
}
for (int i = 0; i < j; i++) {
	cout << arrayTrue[i] << endl;
}

return 0;
}
*/