-- 7. Процедура для видалення всіх таблиць у базі даних
CREATE OR REPLACE PROCEDURE drop_all_tables()
AS $$
DECLARE
    row RECORD;
BEGIN
    -- Для кожної таблиці в схемі public виконуємо DROP
    FOR row IN 
        SELECT tablename 
        FROM pg_tables
        WHERE schemaname = 'public'  -- можна змінити схему, якщо потрібно
    LOOP
        -- Динамічне виконання SQL для видалення таблиці
        EXECUTE format('DROP TABLE IF EXISTS public.%I CASCADE', row.tablename);
    END LOOP;
END;
$$ LANGUAGE plpgsql;
