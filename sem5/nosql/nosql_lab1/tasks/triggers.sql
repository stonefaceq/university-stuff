-- 1. Тригер для автоматичного оновлення поля updated_at у таблиці Task
CREATE OR REPLACE FUNCTION update_task_timestamp() 
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at := CURRENT_TIMESTAMP;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER task_update_timestamp
BEFORE UPDATE ON Task
FOR EACH ROW
EXECUTE FUNCTION update_task_timestamp();

-- 2. Тригер для автоматичного встановлення is_deleted у TRUE при видаленні користувача
CREATE OR REPLACE FUNCTION soft_delete_user() 
RETURNS TRIGGER AS $$
BEGIN
    UPDATE "User" SET is_deleted = TRUE WHERE user_id = OLD.user_id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_soft_delete_user
AFTER DELETE ON "User"
FOR EACH ROW
EXECUTE FUNCTION soft_delete_user();

-- 3. Тригер для обмеження кількості завдань в проекті (макс 5 завдань)
CREATE OR REPLACE FUNCTION check_task_limit() 
RETURNS TRIGGER AS $$
BEGIN
    IF (SELECT COUNT(*) FROM Task WHERE project_id = NEW.project_id) >= 5 THEN
        RAISE EXCEPTION 'Maximum task limit reached for this project';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

