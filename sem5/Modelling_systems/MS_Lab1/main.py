import numpy as np
import matplotlib.pyplot as plt

def load_data(file_name):
    #відповідно завантажуємо файл
    return np.loadtxt(file_name)

def plot_data(t, y, title):
    #значить малюємо саме графік
    plt.plot(t, y)
    plt.title(title)
    plt.grid(True)
    plt.show()

def dft(y, N):
  # значить саме дискретне перетворення фур'є
    fourier_func = np.zeros(N, dtype=complex)
    for k in range(N):
        for j in range(N):
            fourier_func[k] += (y[j] / N) * np.exp(-1j * 2 * np.pi * k * j / N)
    return fourier_func

def fft(y, N):
   # відповідно швидке перетворення фур'є
    return np.fft.fft(y) / N

def plot_half_fft(fft_result, N, df):
    # відповідно обчислюємо і виводимо першу половину перетворення
    half_N = N // 2
    freqs = np.arange(half_N) * df  # значить частота для першої половини
    fft_half_abs = np.abs(fft_result[:half_N])  # і саме амплітуди для неї ж

    plt.plot(freqs, fft_half_abs)
    plt.title("Перша половина FFT")
    plt.grid(True)
    plt.xlabel("Частота (Hz)")
    plt.ylabel("Амплітуда")
    plt.show()


def find_peaks(fourier_func_abs, df, N):
   # значить відповідно "піки" шукаємо
    peaks = []
    for j in range(2, round(N / 2) - 1):
        if (fourier_func_abs[j] > fourier_func_abs[j - 1] and
            fourier_func_abs[j] > fourier_func_abs[j + 1] and
            abs(fourier_func_abs[j] - fourier_func_abs[j - 1]) > 1):
            peaks.append(j * df)
    return peaks

def create_matrix(t, sin_f, N):
   # відповідно матриця
    A = np.array([[np.sum(t ** 6), np.sum(t ** 5), np.sum(t ** 4), np.sum(sin_f * t ** 3), np.sum(t ** 3)],
                  [np.sum(t ** 5), np.sum(t ** 4), np.sum(t ** 3), np.sum(sin_f * t ** 2), np.sum(t ** 2)],
                  [np.sum(t ** 4), np.sum(t ** 3), np.sum(t ** 2), np.sum(sin_f * t), np.sum(t)],
                  [np.sum(sin_f * t ** 3), np.sum(sin_f * t ** 2), np.sum(sin_f * t), np.sum(sin_f ** 2), np.sum(sin_f)],
                  [np.sum(t ** 3), np.sum(t ** 2), np.sum(t), np.sum(sin_f), N]])
    return A
#[t^6         t^5         t^4         sin(f)*t^3         t^3}
#[t^5         t^4         t^3          sin(f)*t^2        t^2}
#[t^4         t^3         t^2           sin(f)*t          t }
#[sin(f)*t^3    sin(f)*t^2    sin(f)*t    sin^2(f)    sin(f)}
#[t^3         t^2          t              sin(f)          N }

def create_vector(y, t, sin_f):
   # значить вектор для саме апроксимації
    c = np.array([np.sum(y * t ** 3), np.sum(y * t ** 2), np.sum(y * t), np.sum(y * sin_f), np.sum(y)])
    return c

def approx_func(a, t, sin_f):
   # відповідно обчислення функції
    return a[0] * t ** 3 + a[1] * t ** 2 + a[2] * t + a[3] * sin_f + a[4]

def main():
    # значить початкові саме параметри з умови відповідно
    dt = 0.01
    T = 5
    t = np.arange(0, T + dt, dt)
    df = 1 / T

    # відповідно закачка даних
    y = load_data('f6.txt')
    N = len(y)

    # саме побудова початкового графіку
    plot_data(t, y, "Початкові значення")

    # значить рахуємо і будуємо саме ДПФ
    fourier_func = dft(y, N)
    plot_data(np.arange(N), np.abs(fourier_func), "Дискретне перетворення Фур’є (DFT)")

    # відповідно те саме з ШПФ
    fft_result = fft(y, N)
    plot_data(np.arange(N), np.abs(fft_result), "Швидке перетворення Фур’є (FFT)")

    #значить сама половина ШПФ, т.я. вони співпадають з ДПФ
    plot_half_fft(fft_result, N, df)

    # значить шукаємо екстремуми
    fourier_func_abs = np.abs(fft_result[:N // 2])
    peaks = find_peaks(fourier_func_abs, df, N)

    # і відповідно якщо знайшли екстремуми
    if peaks:
        sin_f = np.sin(2 * np.pi * peaks[0] * t)
    else:
        sin_f = np.zeros_like(t)

    # значить робимо матрицю і вектор для апроксимації
    A = create_matrix(t, sin_f, N)
    c = create_vector(y, t, sin_f)

    # відповідно розв'язуємо рівняння через нампай
    a = np.linalg.solve(A, c)

    # значить виводимо коефіцієнти в консоль
    print(f"Коефіцієнти: {a}")

    # відповідно побудова та графік апроксимуючої функції
    approx_y = approx_func(a, t, sin_f)
    plot_data(t, approx_y, "Апроксимуюча функція")

    # і значить саме похибка в консоль
    error_value = np.sum((approx_y - y) ** 2)
    print(f"Похибка: {error_value}")

if __name__ == '__main__':
    main()
