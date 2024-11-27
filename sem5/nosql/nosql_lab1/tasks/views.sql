-- 1. Розріз (View) для перегляду активних проектів
CREATE OR REPLACE VIEW active_projects AS
SELECT p.project_id, p.name, p.start_date, p.end_date
FROM Project p
WHERE p.is_deleted = FALSE;

-- 2. Розріз (View) для перегляду користувачів та їх ролей
CREATE OR REPLACE VIEW user_roles_view AS
SELECT u.user_id, u.username, r.name AS role
FROM "User" u
JOIN UserRole ur ON u.user_id = ur.user_id
JOIN Role r ON ur.role_id = r.role_id;

-- 3. Розріз (View) для перегляду завдань з тегами
CREATE OR REPLACE VIEW task_with_tags AS
SELECT t.task_id, t.title, t.description, tg.name AS tag_name
FROM Task t
JOIN TaskTag tt ON t.task_id = tt.task_id
JOIN Tag tg ON tt.tag_id = tg.tag_id
WHERE t.is_deleted = FALSE;
