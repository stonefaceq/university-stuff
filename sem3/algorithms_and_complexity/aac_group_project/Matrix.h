#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

class Matrix
{
public:
    // Constructor to create a zero-matrix with the given number of rows and columns
    Matrix();

    Matrix(int rowsNum, int colsNum)
    {
        rows = rowsNum;
        cols = colsNum;
        // Allocate memory for the matrix
        data = new double* [rows];
        for (int i = 0; i < rows; i++)
        {
            data[i] = new double[cols];
        }

        // initialize matrix data to zeros
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] = 0.0;
            }
        }
    }

    // Copy constructor
    Matrix(const Matrix& matrix)
    {
        rows = matrix.rows;
        cols = matrix.cols;
        data = matrix.data;
    }

    // Swap two rows of a matrix
    void swapRows(int firstRow, int secondRow)
    {
        for (int i = 0; i < cols; ++i)
        {
            double valueCopy = data[firstRow][i];
            data[firstRow][i] = data[secondRow][i];
            data[secondRow][i] = valueCopy;

        }
    }

    // Swap two columns of a matrix
    void swapColumns(int firstCol, int secondCol)
    {
        for (int i = 0; i < rows; ++i)
        {
            double valueCopy = data[i][firstCol];
            data[i][firstCol] = data[i][secondCol];
            data[i][secondCol] = valueCopy;
        }
    }

    // Get identity matrix with size N
    static Matrix getIdentity(int N)
    {
        Matrix Identity(N, N);
        for (int i = 0; i < N; ++i)
        {
            Identity.data[i][i] = 1;
        }
        return Identity;
    }


    Matrix getInverseGaussJordan()
    {
        if (cols != rows)
        {
            std::cerr << "Matrix is not square.\n";
            return *this;
        }

        // Create an augmented matrix [A | I] where A is the original matrix and I is the identity matrix.
        Matrix augmentedMatrix(rows, cols * 2);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                augmentedMatrix.setValue(i, j, data[i][j]);
                augmentedMatrix.setValue(i, j + cols, (i == j) ? 1.0 : 0.0);
            }
        }

        // Perform Gauss-Jordan elimination to transform the left side (A) into the identity matrix
        for (int i = 0; i < rows; ++i)
        {
            // Find the pivot row
            int pivotRow = i;
            double maxVal = std::abs(augmentedMatrix.getValue(i, i));

            for (int j = i + 1; j < rows; ++j)
            {
                double val = std::abs(augmentedMatrix.getValue(j, i));
                if (val > maxVal)
                {
                    maxVal = val;
                    pivotRow = j;
                }
            }

            // Swap the pivot row with the current row
            if (pivotRow != i)
            {
                augmentedMatrix.swapRows(i, pivotRow);
            }

            // Make the diagonal element of the current row equal to 1
            double pivotVal = augmentedMatrix.getValue(i, i);
            for (int j = 0; j < cols * 2; ++j)
            {
                augmentedMatrix.setValue(i, j, augmentedMatrix.getValue(i, j) / pivotVal);
            }

            // Eliminate other rows
            for (int j = 0; j < rows; ++j)
            {
                if (j != i)
                {
                    double factor = augmentedMatrix.getValue(j, i);
                    for (int k = 0; k < cols * 2; ++k)
                    {
                        augmentedMatrix.setValue(j, k, augmentedMatrix.getValue(j, k) - factor * augmentedMatrix.getValue(i, k));
                    }
                }
            }
        }

        // Extract the right side (I) as the inverted matrix
        Matrix invertedMatrix(rows, cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                invertedMatrix.setValue(i, j, augmentedMatrix.getValue(i, j + cols));
            }
        }

        return invertedMatrix;
    }

    

    // Get the number of rows in the matrix
    int getRows() const
    {
        return rows;
    }

    // Get the number of columns in the matrix
    int getCols() const
    {
        return cols;
    }

    // Set the value at a specific position in the matrix
    void setValue(int row, int col, double value)
    {
        if (row >= 0 && row < rows && col >= 0 && col < cols)
        {
            data[row][col] = value;
        }
        else
        {
            std::cerr << "Invalid row or column index.\n";
        }
    }

    // Get the value at a specific position in the matrix
    double getValue(int row, int col) const
    {
        if (row >= 0 && row < rows && col >= 0 && col < cols)
        {
            return data[row][col];
        }
        else
        {
            std::cerr << "Invalid row or column index.\n";
            return 0.0;
        }
    }

    // Print matrix to the console
    void print()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                std::cout << data[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
private:
    int rows;
    int cols;
    double** data;
};
#endif
