import numpy as np
import matplotlib.pyplot as plt


def lagrange_interpolation(x, y, xi):
    """
    Обчислення значення інтерполяційного поліному Лагранжа.
    """
    n = len(x)
    result = 0
    for i in range(n):
        term = y[i]
        for j in range(n):
            if i != j:
                term *= (xi - x[j]) / (x[i] - x[j])
        result += term
    return result


def divided_differences(x, y):
    """
    Обчислення таблиці розділених різниць для поліному Ньютона.
    """
    n = len(x)
    diff_table = np.zeros((n, n))
    diff_table[:, 0] = y
    for j in range(1, n):
        for i in range(n - j):
            diff_table[i, j] = (diff_table[i + 1, j - 1] - diff_table[i, j - 1]) / (x[i + j] - x[i])
    return diff_table


def newton_interpolation(x, y, xi):
    """
    Обчислення значення інтерполяційного поліному Ньютона.
    """
    diff_table = divided_differences(x, y)
    n = len(x)
    result = diff_table[0, 0]
    term = 1
    for i in range(1, n):
        term *= (xi - x[i - 1])
        result += term * diff_table[0, i]
    return result


def evaluate_error(f, x_nodes, y_nodes, x_eval):
    """
    Обчислення абсолютної похибки між справжнім значенням функції
    та інтерпольованим значенням.
    """
    actual = f(x_eval)
    lagrange_est = lagrange_interpolation(x_nodes, y_nodes, x_eval)
    newton_est = newton_interpolation(x_nodes, y_nodes, x_eval)
    return abs(actual - lagrange_est), abs(actual - newton_est)


# Вхідні дані
def main():
    f = lambda x: 2 * np.sin(2 * x)

    # Введення вузлів
    n = int(input("Введіть кількість вузлів інтерполяції: "))
    x_nodes = np.array([float(input(f"Введіть x[{i}]: ")) for i in range(n)])
    y_nodes = f(x_nodes)

    # Точки для оцінки
    x_eval = np.linspace(min(x_nodes), max(x_nodes), 100)
    y_actual = f(x_eval)

    # Розрахунок значень інтерполяцій
    y_lagrange = [lagrange_interpolation(x_nodes, y_nodes, xi) for xi in x_eval]
    y_newton = [newton_interpolation(x_nodes, y_nodes, xi) for xi in x_eval]

    # Оцінка похибки
    errors = [evaluate_error(f, x_nodes, y_nodes, xi) for xi in x_eval]
    lagrange_errors, newton_errors = zip(*errors)

    # Виведення результатів
    print("\nМаксимальна похибка Лагранжа:", max(lagrange_errors))
    print("Максимальна похибка Ньютона:", max(newton_errors))

    # Побудова графіків
    plt.figure(figsize=(10, 6))
    plt.plot(x_eval, y_actual, label="Точна функція", color='black')
    plt.plot(x_eval, y_lagrange, label="Поліном Лагранжа", linestyle='--', color='blue')
    plt.plot(x_eval, y_newton, label="Поліном Ньютона", linestyle='--', color='green')
    plt.scatter(x_nodes, y_nodes, label="Вузли", color='red', zorder=5)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title("Інтерполяція Лагранжа та Ньютона")
    plt.legend()
    plt.grid()
    plt.show()


if __name__ == "__main__":
    main()
