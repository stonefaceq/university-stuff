-- 5. Збережена процедура для видалення всіх "м'яко видалених" записів
CREATE OR REPLACE PROCEDURE delete_soft_deleted_entities()
AS $$
BEGIN
    -- Видалення "м'яко видалених" користувачів
    DELETE FROM "User" WHERE is_deleted = TRUE;

    -- Видалення "м'яко видалених" проектів
    DELETE FROM Project WHERE is_deleted = TRUE;

    -- Видалення "м'яко видалених" завдань
    DELETE FROM Task WHERE is_deleted = TRUE;

    -- Видалення "м'яко видалених" коментарів
    DELETE FROM Comment WHERE task_id IN (SELECT task_id FROM Task WHERE is_deleted = TRUE);

    -- Видалення "м'яко видалених" логів часу
    DELETE FROM TimeLog WHERE task_id IN (SELECT task_id FROM Task WHERE is_deleted = TRUE);

    -- Видалення "м'яко видалених" вкладень
    DELETE FROM Attachment WHERE task_id IN (SELECT task_id FROM Task WHERE is_deleted = TRUE);

    -- Видалення "м'яко видалених" платіжних записів
    DELETE FROM Payment WHERE invoice_id IN (SELECT invoice_id FROM Invoice WHERE is_deleted = TRUE);

    -- Видалення "м'яко видалених" тегів завдань
    DELETE FROM TaskTag WHERE task_id IN (SELECT task_id FROM Task WHERE is_deleted = TRUE);

    -- Видалення "м'яко видалених" повідомлень
    DELETE FROM Notification WHERE is_read = TRUE AND user_id IN (SELECT user_id FROM "User" WHERE is_deleted = TRUE);

    -- Видалення "м'яко видалених" записів ролей користувачів
    DELETE FROM UserRole WHERE user_id IN (SELECT user_id FROM "User" WHERE is_deleted = TRUE);

    -- Видалення "м'яко видалених" записів проектних учасників
    DELETE FROM ProjectMember WHERE project_id IN (SELECT project_id FROM Project WHERE is_deleted = TRUE);
    
    -- Видалення "м'яко видалених" рахунків-фактур
    DELETE FROM Invoice WHERE is_deleted = TRUE;
END;
$$ LANGUAGE plpgsql;
