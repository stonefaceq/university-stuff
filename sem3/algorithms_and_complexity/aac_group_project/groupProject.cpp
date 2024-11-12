
#include <iostream>
#include "Matrix.h"

int main() {
    // Create a sample matrix
    Matrix matrix(4, 4);
    matrix.setValue(0, 0, 2);
    matrix.setValue(0, 1, 1);
    matrix.setValue(0, 2, 1);
    matrix.setValue(0, 3, 1);
    matrix.setValue(1, 0, 1);
    matrix.setValue(1, 1, 3);
    matrix.setValue(1, 2, 2);
    matrix.setValue(1, 3, 2);
    matrix.setValue(2, 0, 2);
    matrix.setValue(2, 1, 1);
    matrix.setValue(2, 2, 2);
    matrix.setValue(2, 3, 2);
    matrix.setValue(3, 0, 1);
    matrix.setValue(3, 1, 2);
    matrix.setValue(3, 2, 3);
    matrix.setValue(3, 3, 1);


    std::cout << "Original Matrix:" << std::endl;
    matrix.print();

    // Get the inverse using Gauss-Jordan elimination
    Matrix inverseMatrix = matrix.getInverseGaussJordan();

    std::cout << "\nInverse Matrix:" << std::endl;
    inverseMatrix.print();


    return 0;
}

