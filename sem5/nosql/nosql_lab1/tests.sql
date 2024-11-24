-- Тест 1: Перевірка м'якого видалення завдання (soft_delete_task)

-- Перевіримо, чи існує завдання з task_id = 1
SELECT task_id, title, is_deleted FROM Task WHERE task_id = 1;

-- Виконаємо м'яке видалення завдання з task_id = 1
SELECT soft_delete_task(1);

-- Перевіримо, чи завдання стало м'яко видаленим
SELECT task_id, title, is_deleted FROM Task WHERE task_id = 1;

-- Тест 2: Перевірка відновлення м'яко видаленого завдання (restore_task)

-- Перевіримо, чи завдання з task_id = 2 є м'яко видаленим
SELECT task_id, title, is_deleted FROM Task WHERE task_id = 2;

-- Виконаємо відновлення завдання з task_id = 2
SELECT restore_task(2);

-- Перевіримо, чи завдання було відновлене
SELECT task_id, title, is_deleted FROM Task WHERE task_id = 2;

-- Тест 3: Перевірка м'якого видалення проекту (soft_delete_project)

-- Перевіримо, чи існує проект з project_id = 1
SELECT project_id, name, is_deleted FROM Project WHERE project_id = 1;

-- Виконаємо м'яке видалення проекту з project_id = 1
SELECT soft_delete_project(1);

-- Перевіримо, чи проект став м'яко видаленим
SELECT project_id, name, is_deleted FROM Project WHERE project_id = 1;

-- Тест 4: Перевірка відновлення м'яко видаленого проекту (restore_project)

-- Перевіримо, чи проект з project_id = 2 є м'яко видаленим
SELECT project_id, name, is_deleted FROM Project WHERE project_id = 2;

-- Виконаємо відновлення проекту з project_id = 2
SELECT restore_project(2);

-- Перевіримо, чи проект було відновлено
SELECT project_id, name, is_deleted FROM Project WHERE project_id = 2;

-- Тест 5: Перевірка розрізу для активних проектів (active_projects)

-- Перевіримо дані в розрізі active_projects
SELECT * FROM active_projects;

-- Тест 6: Перевірка трігеру для автоматичного оновлення поля updated_at у таблиці Task (task_update_timestamp)

-- Перевіримо початковий час оновлення завдання з task_id = 1
SELECT task_id, title, updated_at FROM Task WHERE task_id = 1;

-- Оновимо завдання з task_id = 1, щоб спровокувати спрацювання трігеру
UPDATE Task SET title = 'Updated Task Title' WHERE task_id = 1;

-- Перевіримо, чи час оновлення змінився після виконання оновлення
SELECT task_id, title, updated_at FROM Task WHERE task_id = 1;
