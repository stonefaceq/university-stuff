import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
import time


def check(Aplus, A):
    assert np.allclose(Aplus, np.dot(np.dot(Aplus, A), Aplus), atol=1e-4)
    assert np.allclose(A, np.dot(np.dot(A, Aplus), A), atol=1e-4)
    assert np.allclose(np.dot(A, Aplus), np.dot(A, Aplus).T, atol=1e-4)
    assert np.allclose(np.dot(Aplus, A), np.dot(Aplus, A).T, atol=1e-4)


def moorePenrose(A, eps, method="default"):
    if method == "alternative":
        return alternative_delta_method(A, eps)
    else:
        return default_delta_method(A, eps)


def default_delta_method(A, eps):
    delta = 1
    curr_eps = eps + 1
    E = np.eye(A.shape[0])
    curr_a = np.dot(A.T, np.linalg.inv(np.dot(A, A.T) + delta * E))

    while curr_eps > eps:
        prev_a = curr_a
        delta /= 2
        curr_a = np.dot(A.T, np.linalg.inv(np.dot(A, A.T) + delta * E))
        curr_eps = np.linalg.norm(curr_a - prev_a)

    return curr_a


def alternative_delta_method(A, eps):
    delta = 1
    curr_eps = eps + 1
    E = np.eye(A.shape[0])
    reduction_factor = 0.8  # Коефіцієнт адаптивного зменшення
    curr_a = np.dot(A.T, np.linalg.inv(np.dot(A, A.T) + delta * E))

    while curr_eps > eps:
        prev_a = curr_a
        delta *= reduction_factor  # Адаптивне зменшення delta
        curr_a = np.dot(A.T, np.linalg.inv(np.dot(A, A.T) + delta * E))
        curr_eps = np.linalg.norm(curr_a - prev_a)

    return curr_a


def greville(A):
    curr_a = A[0, :].reshape(1, -1)
    curr = np.zeros_like(curr_a).T
    if np.any(curr_a[0] != 0):
        curr = curr_a.T @ np.linalg.inv(curr_a @ curr_a.T)
    n = A.shape[0]

    for i in range(1, n):
        curr_a = A[i, :].reshape(1, -1)
        z = np.eye(curr.shape[0]) - np.dot(curr, A[:i, :])
        r = np.dot(curr, curr.T)
        condition = np.dot(np.dot(curr_a, z), curr_a.T)

        if np.linalg.matrix_rank(condition) == 1:
            row_to_add = np.dot(z, curr_a.T) / condition
        else:
            row_to_add = np.dot(r, curr_a.T) / (1 + np.dot(np.dot(curr_a, r), curr_a.T))

        curr = curr - np.dot(row_to_add, np.dot(curr_a, curr))
        curr = np.hstack((curr, row_to_add))

    return curr


def norm(A):
    return np.sum(np.abs(A))


def mse(image1, image2):
    return np.mean((image1 - image2) ** 2)


def main():
    # Завантажуємо зображення
    A = np.array(Image.open("x1.bmp"))
    B = np.array(Image.open("y6.bmp"))

    plt.imshow(A, cmap='gray')
    plt.show()
    plt.imshow(B, cmap='gray')
    plt.show()

    A = A.astype(np.float64)
    B = B.astype(np.float64)

    # Псевдообернена матриця методом Гревіля з підрахунком часу
    start_time = time.time()
    pseudoinverseG = greville(A)
    greville_time = time.time() - start_time
    print(f"Greville Method Time: {greville_time:.4f} seconds")

    check(pseudoinverseG, A)
    operatorG = np.dot(B, pseudoinverseG)
    resG = np.uint8(np.dot(operatorG, A))

    plt.imshow(resG, cmap='gray')
    plt.show()

    print("Error Greville: ", norm(np.dot(A, pseudoinverseG) - np.eye(A.shape[0])))

    # Псевдообернена матриця методом Мура-Пенроуза з підрахунком часу для альтернативного дельта-методу
    start_time = time.time()
    pseudoinverseMP_alt = moorePenrose(A, 0.00001, method="alternative")
    mp_alt_time = time.time() - start_time
    print(f"Moore-Penrose Method Time (alternative delta): {mp_alt_time:.4f} seconds")

    check(pseudoinverseMP_alt, A)
    operatorMP_alt = np.dot(B, pseudoinverseMP_alt)
    resMP_alt = np.uint8(np.dot(operatorMP_alt, A))

    plt.imshow(resMP_alt, cmap='gray')
    plt.show()

    print("Error Moore-Penrose (alternative delta): ", norm(np.dot(A, pseudoinverseMP_alt) - np.eye(A.shape[0])))

    # Псевдообернена матриця методом Мура-Пенроуза з підрахунком часу для дефолтного дельта-методу
    start_time = time.time()
    pseudoinverseMP_default = moorePenrose(A, 0.00001, method="default")
    mp_default_time = time.time() - start_time
    print(f"Moore-Penrose Method Time (default delta): {mp_default_time:.4f} seconds")

    check(pseudoinverseMP_default, A)
    operatorMP_default = np.dot(B, pseudoinverseMP_default)
    resMP_default = np.uint8(np.dot(operatorMP_default, A))

    plt.imshow(resMP_default, cmap='gray')
    plt.show()

    print("Error Moore-Penrose (default delta): ", norm(np.dot(A, pseudoinverseMP_default) - np.eye(A.shape[0])))

    # Порівняння матриць вихідних зображень між альтернативним і дефолтним методами Мура-Пенроуза
    mse_value = mse(resMP_alt, resMP_default)
    print(f"MSE between Moore-Penrose outputs (alternative vs. default delta): {mse_value:.4f}")


if __name__ == "__main__":
    main()
