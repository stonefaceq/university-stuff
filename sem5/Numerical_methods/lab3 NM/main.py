import numpy as np
import matplotlib.pyplot as plt
import warnings
warnings.filterwarnings("ignore")

import pandas


# Визначаємо систему нелінійних рівнянь
def equations(x, y):
    f1 = x ** 2 - y ** 2 - 0.8
    f2 = np.sin(x - y) - (x * y - 1)
    return np.array([f1, f2])


# Визначаємо матрицю Якобіана
def jacobian(x, y):
    df1_dx = 2 * x
    df1_dy = -2 * y
    df2_dx = np.cos(x - y) - y
    df2_dy = -np.cos(x - y) - x
    return np.array([[df1_dx, df1_dy], [df2_dx, df2_dy]])


# Реалізація методу Ньютона з перевіркою на збіжність
def newton_method(initial_guess, eps=1e-4, max_iter=100):
    x, y = initial_guess
    for i in range(max_iter):
        # Обчислюємо значення функцій та Якобіана
        F = equations(x, y)
        J = jacobian(x, y)

        # Перевірка норми вектора функцій для умов завершення
        if np.linalg.norm(F, ord=2) < eps:
            print(f"Знайдено розв'язок за {i + 1} ітерацій:")
            return x, y

        # Розв'язуємо лінійну систему для знаходження оновлення [delta_x, delta_y]
        try:
            delta = np.linalg.solve(J, -F)
        except np.linalg.LinAlgError:
            raise ValueError("Якобіан є виродженим; метод Ньютона не збігається.")

        # Перевірка норми вектора змін delta для оцінки збіжності
        if np.linalg.norm(delta, ord=2) < eps:
            print(f"Збіжність досягнута за {i + 1} ітерацій:")
            return x, y

        # Оновлюємо значення x і y
        x += delta[0]
        y += delta[1]

    raise ValueError("Метод Ньютона не збігся за максимальну кількість ітерацій")


# Побудова графіків рівнянь
def plot_graphs(solution):
    x_vals = np.linspace(-2, 2, 400)
    y_vals = np.linspace(-2, 2, 400)
    X, Y = np.meshgrid(x_vals, y_vals)

    # Обчислення значень для рівнянь
    F1 = X ** 2 - Y ** 2 - 0.8
    F2 = np.sin(X - Y) - (X * Y - 1)

    # Побудова графіків
    plt.figure(figsize=(10, 6))
    contour1 = plt.contour(X, Y, F1, levels=[0], colors='blue', linewidths=1, linestyles='dashed')
    contour2 = plt.contour(X, Y, F2, levels=[0], colors='red', linewidths=1, linestyles='dashed')

    # Додаємо розв'язок на графік
    plt.plot(solution[0], solution[1], 'go', label='Розв\'язок (x, y)')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Графік системи нелінійних рівнянь')

    # Додаємо легенду
    handles = [contour1.collections[0], contour2.collections[0]]
    labels = [r'$x^2 - y^2 = 0.8$', r'$\sin(x - y) = xy - 1$']
    plt.legend(handles=handles, labels=labels)

    plt.grid(True)
    plt.show()


# Функція для меню та введення даних
def main():
    print("Вітаємо у програмі для розв'язання системи нелінійних рівнянь методом Ньютона!")
    try:
        # Введення початкових наближень
        x_init = float(input("Введіть початкове наближення для x: "))
        y_init = float(input("Введіть початкове наближення для y: "))
        eps = float(input("Введіть точність ε (наприклад, 1e-4): "))
    except ValueError:
        print("Невірний ввід. Будь ласка, введіть числові значення.")
        return

    initial_guess = [x_init, y_init]

    # Запускаємо метод Ньютона
    try:
        solution = newton_method(initial_guess, eps)
        print(f"Розв'язок: x = {solution[0]:.6f}, y = {solution[1]:.6f}")
        plot_graphs(solution)  # Побудова графіків
    except ValueError as e:
        print(f"Помилка: {e}")


# Викликаємо основну функцію
if __name__ == "__main__":
    main()
