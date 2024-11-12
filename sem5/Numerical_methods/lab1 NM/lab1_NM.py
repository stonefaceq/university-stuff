import numpy as np
import matplotlib.pyplot as plt



def f(x):
    return x ** 2 - 10 * np.sin(x)


def df(x):
    return 2 * x - 10 * np.cos(x)


def d2f(x):
    return 2 + 10 * np.sin(x)



def draw():
    x = np.linspace(-6, 6, 1000)  
    y1 = f(x)  
    y2 = df(x)  
    y3 = d2f(x)  

    fig, ax = plt.subplots()
    ax.plot(x, y1, label='f(x)=x**2 - 10*sin(x)')
    ax.plot(x, y2, label='f\'(x)=2x - 10*cos(x)')
    ax.plot(x, y3, label='f\'\'(x)=2 + 10*sin(x)')

    ax.axhline(0, color='black', linewidth=0.5)  
    ax.axvline(0, color='black', linewidth=0.5)

    ax.set_title('Plotting Functions in Matplotlib', size=14)
    ax.set_xlim(-3.5, 3.5)  
    ax.set_ylim(-15, 15)  
    plt.legend()
    plt.show()


# Обчислення m1 та M1
def calculate_m1_M1(a, b, num_points=100):
    x_values = np.linspace(a, b, num_points)  # Генерація x значень
    derivatives = df(x_values)  # Обчислення похідних
    m1 = np.min(derivatives)  # Мінімальне значення похідної
    M1 = np.max(derivatives)  
    return m1, M1  


# Метод Ньютона для обчислення кореня
def newton_calc(epsilon, x_n):
    step = 0
    while np.abs(f(x_n)) > epsilon:  # Поки f(x_n) не досягає точності
        x_n = x_n - f(x_n) / df(x_n)  # Оновлення x_n за формулою методу Ньютона
        print("Step %i: f(%f) = %f" % (step, x_n, f(x_n)))  # Вивід результату
        step += 1
    print("Result = %f" % x_n)  # Вивід кореня
    return x_n  # Повернення знайденого кореня


# Метод Ньютона
def newton(epsilon):
    a, b = 2, 3  # Визначення інтервалу
    x_star = newton_calc(epsilon, b)  # Знаходження кореня

    return x_star  # Повернення кореня


# Метод релаксації для знаходження кореня
def relaxation_method(epsilon, x_n):
    step = 0
    max_steps = 1000  # Максимальна кількість ітерацій
    threshold = 1e10  # Поріг для запобігання розбігу

    # Обчислення m1 та M1
    m1, M1 = calculate_m1_M1(2, 3)  # Визначити інтервал [2, 3]

 
    tau_opt = 2 / (m1 + M1)  
    print(f"Optimal tau: {tau_opt}")

    x_star = newton(epsilon)  

    z0 = abs(x_n - x_star)  
    q = (M1 - m1) / (M1 + m1) 

   
    print(f"z0 = {z0}, q = {q}")

    
    if q > 0 and z0 > 0: 
        n_epsilon = int(np.ceil(np.log(abs(z0) / epsilon) / np.log(1 / q))) + 1
    else:
        print("Invalid values for z0 or q, setting n_epsilon to 0.")
        n_epsilon = 0

    print(f"Calculated n_epsilon: {n_epsilon}")  

    while np.abs(f(x_n)) > epsilon:  
        x_n_new = x_n - tau_opt * f(x_n)  
        print(f"Step {step}: x = {x_n}, f(x) = {f(x_n)}")  

        if np.abs(x_n_new - x_n) < epsilon: 
            break

        if np.abs(x_n_new) > threshold:  
            print("Divergence detected: x is too large. Stopping the method.")
            return

        x_n = x_n_new  
        step += 1  

        if step >= max_steps:  
            print("Maximum steps reached. Stopping the method.")
            break

    print(f"Result = {x_n} after {step} steps")  # Вивід результату і кількості ітерацій


epsilon = 1e-4
starting_approximation = 3

draw()
print("\n:NEWTON:")
newton(epsilon)
print("\n\n:RELAXATION METHOD:")
relaxation_method(epsilon, starting_approximation)
