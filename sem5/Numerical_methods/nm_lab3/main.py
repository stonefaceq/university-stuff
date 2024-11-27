import numpy as np
import matplotlib.pyplot as plt
import warnings
import time
warnings.filterwarnings("ignore")

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

# Реалізація методу Гауса для розв'язання системи лінійних рівнянь
def gauss_solve(A, b):
    n = len(b)
    # Прямий хід (зведення до трикутної форми)
    for i in range(n):
        if A[i, i] == 0:
            raise ValueError("Нульовий головний елемент під час розв'язання методом Гауса.")
        for j in range(i + 1, n):
            factor = A[j, i] / A[i, i]
            A[j, i:] -= factor * A[i, i:]
            b[j] -= factor * b[i]

    # Зворотній хід (обчислення невідомих)
    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        x[i] = (b[i] - np.dot(A[i, i + 1:], x[i + 1:])) / A[i, i]
    return x

# Реалізація методу Ньютона з власним розв'язанням систем
def newton_method(initial_guess, eps=1e-4, max_iter=100):
    x, y = initial_guess
    start_time = time.time()  # Початок вимірювання часу
    print(f"\nПочаткове наближення: x = {x}, y = {y}")
    print(f"Точність: ε = {eps}\n")
    print("Ітерації:")

    for i in range(max_iter):
        # Обчислюємо значення функцій та Якобіана
        F = equations(x, y)
        J = jacobian(x, y)

        # Перевірка норми вектора функцій для умов завершення
        if np.linalg.norm(F, ord=2) < eps:
            elapsed_time = time.time() - start_time
            print(f"Знайдено розв'язок за {i + 1} ітерацій.")
            print(f"Час роботи алгоритму: {elapsed_time:.4f} секунд")
            return x, y

        # Розв'язуємо лінійну систему методом Гауса
        try:
            z = gauss_solve(J.copy(), -F.copy())
        except ValueError as e:
            raise ValueError(f"Метод Ньютона не може продовжувати: {e}")

        # Лог поточної ітерації
        print(f"Ітерація {i + 1}: x = {x:.6f}, y = {y:.6f}, Δx = {z[0]:.6f}, Δy = {z[1]:.6f}")

        # Перевірка норми вектора змін delta для оцінки збіжності
        if np.linalg.norm(z, ord=2) < eps:
            elapsed_time = time.time() - start_time
            print(f"Збіжність досягнута за {i + 1} ітерацій.")
            print(f"Час роботи алгоритму: {elapsed_time:.4f} секунд")
            return x, y

        # Оновлюємо значення x і y
        x += z[0]
        y += z[1]

    raise ValueError("Метод Ньютона не збігся за максимальну кількість ітерацій.")

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

# Функція для меню
def display_menu():
    print("\nМеню:")
    print("1. Вивести рівняння системи")
    print("2. Розв'язати систему")
    print("3. Вихід")

def main():
    while True:
        display_menu()
        choice = input("\nОберіть опцію: ")

        if choice == '1':
            print("\nРівняння системи:")
            print("f1(x, y) = x^2 - y^2 - 0.8")
            print("f2(x, y) = sin(x - y) - (x * y - 1)")
        elif choice == '2':
            try:
                x_init = float(input("Введіть початкове наближення для x: "))
                y_init = float(input("Введіть початкове наближення для y: "))
                eps = float(input("Введіть точність ε (наприклад, 1e-4): "))
                initial_guess = [x_init, y_init]
                solution = newton_method(initial_guess, eps)
                print(f"Розв'язок: x = {solution[0]:.6f}, y = {solution[1]:.6f}")
                plot_graphs(solution)  # Побудова графіків
            except ValueError as e:
                print(f"Помилка: {e}")
        elif choice == '3':
            break
        else:
            print("Невірний вибір. Спробуйте ще раз.")

# Викликаємо основну функцію
if __name__ == "__main__":
    main()
