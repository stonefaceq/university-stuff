import numpy as np

# Функція для обчислення абсолютного значення
def abs_value(x):
    return x if x >= 0 else -x

# Функція для обчислення норми вектора
def vector_norm(v):
    return sum(abs_value(x) ** 2 for x in v) ** 0.5

# Функція для визначення знака числа
def sign_of(value):
    return 1 if value > 0 else -1 if value < 0 else 0

# Функція для реалізації методу Зейделя
def zeidel_method(aMatrix, bVector, eps=1e-10, max_iterations=1000):
    n = len(bVector)
    x = [0.0] * n  # Початкове наближення
    x_new = x[:]

    for iteration in range(max_iterations):
        for i in range(n):
            sum1 = sum(aMatrix[i][j] * x_new[j] for j in range(i))  # Сума по старим значенням
            sum2 = sum(aMatrix[i][j] * x[j] for j in range(i + 1, n))  # Сума по новим значенням
            x_new[i] = (bVector[i] - sum1 - sum2) / aMatrix[i][i]

        # Перевірка на збіжність
        if vector_norm([x_new[j] - x[j] for j in range(n)]) < eps:
            print(f"Збіжність досягнута після {iteration + 1} ітерацій.")
            return x_new

        x = x_new[:]

    print(f"Не вдалося досягти збіжності за {max_iterations} ітерацій.")
    return x_new

# Функція для обчислення детермінанту
def calc_determinant(matrix):
    order = len(matrix)
    if order == 1:
        return matrix[0][0]
    elif order == 2:
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]

    det = 0
    for column in range(order):
        minor_matrix = [[matrix[row][col] for col in range(order) if col != column] for row in range(1, order)]
        det += ((-1) ** column) * matrix[0][column] * calc_determinant(minor_matrix)
    return det

# Метод квадратних коренів
def sqrt_decomposition(matrix, b, eps=1e-3):
    size = matrix.shape[0]
    D = np.zeros((size, size))
    S = np.zeros((size, size))

    for i in range(size):
        sum_sq = 0
        for j in range(i):
            sum_sq += S[j][i] * S[j][i] * D[j][j]

        D[i][i] = sign_of(matrix[i][i] - sum_sq)
        S[i][i] = np.sqrt(abs(matrix[i][i] - sum_sq))

        for j in range(i + 1, size):
            sum_sq = 0
            for k in range(i):
                sum_sq += S[k][i] * D[k][k] * S[k][j]
            S[i][j] = (matrix[i][j] - sum_sq) / (D[i][i] * S[i][i])

    S_t = np.transpose(S)
    SD_t = np.dot(S_t, D)

    determinant_val = calc_determinant(SD_t)
    print(f"detA = Det(SD^T) = {determinant_val}")

    y = forward_solve(SD_t, b)
    x = backward_solve(S, y)

    return x

# Функція для створення оригінальної матриці та вектора
def create_original_matrix_and_vector():
    aMatrix = np.array([
        [4, 2, 2, 2],
        [2, -3, -1, -1],
        [2, -1, -4, -2],
        [2, -1, -2, 3]
    ])

    bVector = np.array([8, -6, -9, 3])
    return aMatrix, bVector

# Функція для створення матриці, що задовольняє умови для методу Зейделя
def create_zeidel_matrix():
    zeidelMatrix = np.array([
    [10, 1, 2, 3],
    [1, 12, 3, 1],
    [2, 3, 15, 2],
    [3, 1, 2, 18]
])

    desired_roots = np.array([1, 2, 3, 2])
    zeidelVector = np.dot(zeidelMatrix, desired_roots).tolist()
    return zeidelMatrix, zeidelVector

# Пряме підставлення для трикутної матриці
def forward_solve(lower_triangular, rhs_vector):
    n = len(rhs_vector)
    y = np.zeros(n)
    for i in range(n):
        cumulative_sum = sum(lower_triangular[i][j] * y[j] for j in range(i))
        y[i] = (rhs_vector[i] - cumulative_sum) / lower_triangular[i][i]
    return y

# Зворотне підставлення для трикутної матриці
def backward_solve(upper_triangular, rhs_vector):
    n = len(rhs_vector)
    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        cumulative_sum = sum(upper_triangular[i][j] * x[j] for j in range(i + 1, n))
        x[i] = (rhs_vector[i] - cumulative_sum) / upper_triangular[i][i]
    return x

# Головна функція
def main():
    # Використання оригінальної матриці для методу квадратних коренів
    aMatrix, bVector = create_original_matrix_and_vector()
    print("----------- Квадратний корінь ----------")
    roots_sqrt = sqrt_decomposition(aMatrix, bVector)
    print("Корені (метод квадратних коренів):", roots_sqrt)

    # Використання матриці для методу Зейделя
    zeidelMatrix, zeidelVector = create_zeidel_matrix()
    print("\n----------- Метод Зейделя -----------")
    roots_zeidel = zeidel_method(zeidelMatrix,zeidelVector)  # використання перших 3 елементів вектора b
    print("Корені (метод Зейделя):", roots_zeidel)

if __name__ == "__main__":
    main()
