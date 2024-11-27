-- Вставка даних в таблицю "User"
INSERT INTO "User" (username, email, password_hash) VALUES
('john_doe', 'john.doe@example.com', 'hashedpassword123'),
('jane_smith', 'jane.smith@example.com', 'hashedpassword456'),
('alex_jones', 'alex.jones@example.com', 'hashedpassword789');

-- Вставка даних в таблицю Role
INSERT INTO Role (name) VALUES
('Admin'),
('Manager'),
('Developer'),
('Tester');

-- Вставка даних в таблицю UserRole
INSERT INTO UserRole (user_id, role_id) VALUES
(1, 1),  -- John Doe as Admin
(2, 2),  -- Jane Smith as Manager
(3, 3);  -- Alex Jones as Developer

-- Вставка даних в таблицю Project
INSERT INTO Project (name, description, start_date, end_date, created_by) VALUES
('Project Alpha', 'A description for Project Alpha', '2024-01-01', '2024-06-30', 1),
('Project Beta', 'A description for Project Beta', '2024-02-01', '2024-07-31', 2);

-- Вставка даних в таблицю ProjectMember
INSERT INTO ProjectMember (project_id, user_id) VALUES
(1, 1),  -- John Doe in Project Alpha
(1, 2),  -- Jane Smith in Project Alpha
(2, 3);  -- Alex Jones in Project Beta

-- Вставка даних в таблицю TaskStatus
INSERT INTO TaskStatus (name) VALUES
('Not Started'),
('In Progress'),
('Completed'),
('On Hold');

-- Вставка даних в таблицю Task
INSERT INTO Task (project_id, status_id, title, description, due_date, updated_by) VALUES
(1, 1, 'Task 1 for Alpha', 'Description for Task 1 in Project Alpha', '2024-03-01', 1),
(1, 2, 'Task 2 for Alpha', 'Description for Task 2 in Project Alpha', '2024-03-15', 2),
(2, 3, 'Task 1 for Beta', 'Description for Task 1 in Project Beta', '2024-04-01', 3);

-- Вставка даних в таблицю Comment
INSERT INTO Comment (task_id, user_id, content) VALUES
(1, 1, 'This is the first comment on Task 1 of Project Alpha'),
(2, 2, 'This is a comment on Task 2 of Project Alpha'),
(3, 3, 'This is a comment on Task 1 of Project Beta');

-- Вставка даних в таблицю TimeLog
INSERT INTO TimeLog (task_id, user_id, hours_spent) VALUES
(1, 1, 4.5),
(2, 2, 3.0),
(3, 3, 5.0);

-- Вставка даних в таблицю Attachment
INSERT INTO Attachment (task_id, file_path, uploaded_by) VALUES
(1, '/files/alpha_task_1_file1.pdf', 1),
(2, '/files/alpha_task_2_file1.pdf', 2),
(3, '/files/beta_task_1_file1.pdf', 3);

-- Вставка даних в таблицю Notification
INSERT INTO Notification (user_id, message) VALUES
(1, 'You have a new task assigned to you in Project Alpha'),
(2, 'You have a new comment on your task in Project Alpha'),
(3, 'Your task in Project Beta has been completed');

-- Вставка даних в таблицю Tag
INSERT INTO Tag (name) VALUES
('Urgent'),
('Important'),
('Bug'),
('Feature');

-- Вставка даних в таблицю TaskTag
INSERT INTO TaskTag (task_id, tag_id) VALUES
(1, 1),  -- Tagging Task 1 with 'Urgent'
(2, 2),  -- Tagging Task 2 with 'Important'
(3, 3);  -- Tagging Task 1 with 'Bug'

-- Вставка даних в таблицю Invoice
INSERT INTO Invoice (project_id, amount, due_date) VALUES
(1, 5000.00, '2024-06-30'),
(2, 3000.00, '2024-07-31');

-- Вставка даних в таблицю Payment
INSERT INTO Payment (invoice_id, amount) VALUES
(1, 2500.00),
(2, 1500.00);

-- Вставка даних в таблицю TaskAssignee
INSERT INTO TaskAssignee (task_id, user_id) VALUES
(1, 1),  -- Assigning John Doe to Task 1 in Project Alpha
(2, 2),  -- Assigning Jane Smith to Task 2 in Project Alpha
(3, 3);  -- Assigning Alex Jones to Task 1 in Project Beta
