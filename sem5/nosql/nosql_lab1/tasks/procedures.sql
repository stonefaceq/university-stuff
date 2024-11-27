-- 1. Збережена процедура для додавання нового користувача
CREATE OR REPLACE PROCEDURE add_user(
    p_username VARCHAR, 
    p_email VARCHAR, 
    p_password_hash VARCHAR)
AS $$
BEGIN
    INSERT INTO "User" (username, email, password_hash) 
    VALUES (p_username, p_email, p_password_hash);
END;
$$ LANGUAGE plpgsql;

-- 2. Збережена процедура для видалення користувача (soft delete)
CREATE OR REPLACE PROCEDURE delete_user(p_user_id INT) 
AS $$
BEGIN
    UPDATE "User" SET is_deleted = TRUE WHERE user_id = p_user_id;
END;
$$ LANGUAGE plpgsql;

-- 3. Збережена процедура для оновлення статусу завдання
CREATE OR REPLACE PROCEDURE update_task_status(p_task_id INT, p_status_id INT)
AS $$
BEGIN
    UPDATE Task SET status_id = p_status_id WHERE task_id = p_task_id;
END;
$$ LANGUAGE plpgsql;

-- 4. Збережена процедура для обробки платежу
CREATE OR REPLACE PROCEDURE process_payment(p_invoice_id INT, p_amount DECIMAL)
AS $$
BEGIN
    INSERT INTO Payment (invoice_id, amount) VALUES (p_invoice_id, p_amount);
    UPDATE Invoice SET amount = amount - p_amount WHERE invoice_id = p_invoice_id;
    IF (SELECT amount FROM Invoice WHERE invoice_id = p_invoice_id) <= 0 THEN
        UPDATE Invoice SET paid_date = CURRENT_TIMESTAMP WHERE invoice_id = p_invoice_id;
    END IF;
END;
$$ LANGUAGE plpgsql;
