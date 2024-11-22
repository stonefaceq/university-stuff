import numpy as np

# Матриця чутливості
def computeSensitivityMatrix(parameters):
    c1, c2, m2 = parameters
    return np.array([
        [0, 1, 0, 0, 0, 0],
        [-(c1 + c2) / m1, 0, c2 / m1, 0, 0, 0],
        [0, 0, 0, 1, 0, 0],
        [c2 / m2, 0, -(c2 + c3) / m2, 0, c3 / m2, 0],
        [0, 0, 0, 0, 0, 1],
        [0, 0, c3 / m3, 0, -(c4 + c3) / m3, 0]
    ])

# Похідні параметрів
def computeParameterDerivatives(states, parameters):
    c1, c2, m2 = parameters

    # Матриця похідних по c1
    derivatives_param0 = np.array([
        [0, 0, 0, 0, 0, 0],
        [-1 / m1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0]
    ])

    # Матриця похідних по c2
    derivatives_param1 = np.array([
        [0, 0, 0, 0, 0, 0],
        [-1 / m1, 0, 1 / m1, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [1 / m2, 0, -1 / m2, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0]
    ])

    # Матриця похідних по m2
    derivatives_param2 = np.array([
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [-c2 / (m2 ** 2), 0, (c2 + c3) / (m2 ** 2), 0, -c3 / (m2 ** 2), 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0]
    ])

    # Обчислення матриць похідних для поточного стану
    derivatives_param0 = derivatives_param0 @ states
    derivatives_param1 = derivatives_param1 @ states
    derivatives_param2 = derivatives_param2 @ states

    return np.array([derivatives_param0, derivatives_param1, derivatives_param2]).T

# Динаміка моделі
def computeModelDynamics(states, parameters):
    return computeSensitivityMatrix(parameters) @ states

# Оптимізація параметрів
def optimizeParameters(initial_parameters, start_time, end_time, time_step, tolerance):
    time_points = np.linspace(start_time, end_time, int((end_time - start_time) / time_step + 1))

    while True:
        # Модельні стани
        model_states = np.zeros_like(observations)
        model_states[0] = observations[0].copy()

        # Інтегруємо модель за методом Рунге-Кутта; знаходимо стани моделі у кожен часовий відрізок
        for i in range(1, len(time_points)):
            previous_state = model_states[i - 1]
            k1 = time_step * computeModelDynamics(previous_state, initial_parameters)
            k2 = time_step * computeModelDynamics(previous_state + k1 / 2, initial_parameters)
            k3 = time_step * computeModelDynamics(previous_state + k2 / 2, initial_parameters)
            k4 = time_step * computeModelDynamics(previous_state + k3, initial_parameters)
            current_state = previous_state + (k1 + 2 * k2 + 2 * k3 + k4) / 6
            model_states[i] = current_state

        # Інтегруємо функції чутливості
        sensitivity_matrix = np.zeros((len(time_points), 6, 3))
        parameter_derivatives = computeParameterDerivatives(model_states.T, initial_parameters)
        sensitivity_coefficients = computeSensitivityMatrix(initial_parameters)
        for i in range(1, len(time_points)):
            k1 = time_step * (sensitivity_coefficients @ sensitivity_matrix[i - 1] + parameter_derivatives[i - 1])
            k2 = time_step * (sensitivity_coefficients @ (sensitivity_matrix[i - 1] + k1 / 2) + parameter_derivatives[i - 1])
            k3 = time_step * (sensitivity_coefficients @ (sensitivity_matrix[i - 1] + k2 / 2) + parameter_derivatives[i - 1])
            k4 = time_step * (sensitivity_coefficients @ (sensitivity_matrix[i - 1] + k3) + parameter_derivatives[i - 1])
            sensitivity_matrix[i] = sensitivity_matrix[i - 1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6

        # Оновлення параметрів
        sensitivity_derivatives = (np.array([u.T @ u for u in sensitivity_matrix]) * time_step).sum(0)
        sensitivity_derivatives = np.linalg.inv(sensitivity_derivatives)

        state_difference = (observations - model_states)
        sensitivity_observations = (np.array(
            [sensitivity_matrix[i].T @ state_difference[i] for i in range(len(time_points))]) * time_step).sum(0)

        quality_pointer = (np.array(
            [state_difference[i].T @ state_difference[i] for i in range(len(time_points))]) * time_step).sum(0)

        parameter_update = sensitivity_derivatives @ sensitivity_observations
        initial_parameters += parameter_update

        if np.abs((quality_pointer)).max() < tolerance:
            return initial_parameters, quality_pointer

        if np.abs((parameter_update)).max() < tolerance:
            return initial_parameters, quality_pointer

if __name__ == "__main__":
    # Зчитуємо спостереження з файлу та перетворюємо їх у масив numpy
    with open('y6.txt') as file:
        observations = np.array([line.split() for line in file.readlines()], float).T

    # Відомі параметри
    c3 = 0.2
    c4 = 0.12
    m1 = 12
    m3 = 18

    # Початкове наближення
    initial_guess = np.array([0.1, 0.15, 19])  # c1, c2, m2
    start_time = 0  # початок інтервалу
    end_time = 50  # кінець інтервалу
    time_step = 0.2  # крок
    tolerance = 1e-6  # параметр точності

    solution, quality_pointer = optimizeParameters(initial_guess, start_time, end_time, time_step, tolerance)
    print(f"Ідентифіковані параметри: c1 = {solution[0]}, c2 = {solution[1]}, m2 = {solution[2]}")
    print(f"Показник якості: {quality_pointer}")
