-- 1. Користувацька функція для обчислення кількості завдань для проекту
CREATE OR REPLACE FUNCTION task_count_for_project(p_project_id INT) 
RETURNS INT AS $$
DECLARE
    result INT;
BEGIN
    SELECT COUNT(*) INTO result FROM Task WHERE project_id = p_project_id AND is_deleted = FALSE;
    RETURN result;
END;
$$ LANGUAGE plpgsql;

-- 2. Користувацька функція для перевірки, чи є завдання завершеним
CREATE OR REPLACE FUNCTION is_task_completed(p_task_id INT) 
RETURNS BOOLEAN AS $$
DECLARE
    result BOOLEAN;
BEGIN
    SELECT (status_id = 3) INTO result FROM Task WHERE task_id = p_task_id;  -- статус 3 = Completed
    RETURN result;
END;
$$ LANGUAGE plpgsql;

-- М'яке видалення завдання
CREATE OR REPLACE FUNCTION soft_delete_task(p_task_id INT) 
RETURNS VOID AS $$
BEGIN
    UPDATE Task SET is_deleted = TRUE WHERE task_id = p_task_id;
END;
$$ LANGUAGE plpgsql;

-- Відновлення м'яко видаленого завдання
CREATE OR REPLACE FUNCTION restore_task(p_task_id INT) 
RETURNS VOID AS $$
BEGIN
    UPDATE Task SET is_deleted = FALSE WHERE task_id = p_task_id;
END;
$$ LANGUAGE plpgsql;

-- М'яке видалення проекту
CREATE OR REPLACE FUNCTION soft_delete_project(p_project_id INT) 
RETURNS VOID AS $$
BEGIN
    UPDATE Project SET is_deleted = TRUE WHERE project_id = p_project_id;
END;
$$ LANGUAGE plpgsql;

-- Відновлення м'яко видаленого проекту
CREATE OR REPLACE FUNCTION restore_project(p_project_id INT) 
RETURNS VOID AS $$
BEGIN
    UPDATE Project SET is_deleted = FALSE WHERE project_id = p_project_id;
END;
$$ LANGUAGE plpgsql;

