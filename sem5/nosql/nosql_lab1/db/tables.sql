CREATE TABLE "User" (
    user_id SERIAL PRIMARY KEY,
    username VARCHAR NOT NULL,
    email VARCHAR NOT NULL,
    password_hash VARCHAR NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    is_deleted BOOLEAN DEFAULT FALSE
);

----------------------
CREATE TABLE Role (
    role_id SERIAL PRIMARY KEY,
    name VARCHAR NOT NULL
);

--------------------------------
CREATE TABLE UserRole (
    user_role_id SERIAL PRIMARY KEY,
    user_id INT REFERENCES "User" (user_id) ON DELETE CASCADE,
    role_id INT REFERENCES Role (role_id) ON DELETE CASCADE
);

------------------------------
CREATE TABLE Project (
    project_id SERIAL PRIMARY KEY,
    name VARCHAR NOT NULL,
    description TEXT,
    start_date TIMESTAMP,
    end_date TIMESTAMP,
    is_deleted BOOLEAN DEFAULT FALSE,
    created_by INT REFERENCES "User" (user_id)
);

-----------------------------------------------
CREATE TABLE ProjectMember (
    project_member_id SERIAL PRIMARY KEY,
    project_id INT REFERENCES Project (project_id) ON DELETE CASCADE,
    user_id INT REFERENCES "User" (user_id) ON DELETE CASCADE
);

---------------------------
CREATE TABLE TaskStatus (
    status_id SERIAL PRIMARY KEY,
    name VARCHAR NOT NULL
);
-------------------------------------
CREATE TABLE Task (
    task_id SERIAL PRIMARY KEY,
    project_id INT REFERENCES Project (project_id) ON DELETE CASCADE,
    status_id INT REFERENCES TaskStatus (status_id),
    title VARCHAR NOT NULL,
    description TEXT,
    due_date TIMESTAMP,
    is_deleted BOOLEAN DEFAULT FALSE,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_by INT REFERENCES "User" (user_id)
);

---------------------------
CREATE TABLE Comment (
    comment_id SERIAL PRIMARY KEY,
    task_id INT REFERENCES Task (task_id) ON DELETE CASCADE,
    user_id INT REFERENCES "User" (user_id),
    content TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

---------------------------
CREATE TABLE TimeLog (
    time_log_id SERIAL PRIMARY KEY,
    task_id INT REFERENCES Task (task_id) ON DELETE CASCADE,
    user_id INT REFERENCES "User" (user_id),
    hours_spent FLOAT,
    date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

----------------------------
CREATE TABLE Attachment (
    attachment_id SERIAL PRIMARY KEY,
    task_id INT REFERENCES Task (task_id) ON DELETE CASCADE,
    file_path VARCHAR NOT NULL,
    uploaded_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    uploaded_by INT REFERENCES "User" (user_id)
);

---------------------------
CREATE TABLE Notification (
    notification_id SERIAL PRIMARY KEY,
    user_id INT REFERENCES "User" (user_id),
    message TEXT,
    is_read BOOLEAN DEFAULT FALSE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

----------------------------
CREATE TABLE Tag (
    tag_id SERIAL PRIMARY KEY,
    name VARCHAR NOT NULL
);

-----------------------------
CREATE TABLE TaskTag (
    task_tag_id SERIAL PRIMARY KEY,
    task_id INT REFERENCES Task (task_id) ON DELETE CASCADE,
    tag_id INT REFERENCES Tag (tag_id) ON DELETE CASCADE
);

----------------------------
CREATE TABLE Invoice (
    invoice_id SERIAL PRIMARY KEY,
    project_id INT REFERENCES Project (project_id),
    amount DECIMAL,
    issued_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    due_date TIMESTAMP
);

----------------------------
CREATE TABLE Payment (
    payment_id SERIAL PRIMARY KEY,
    invoice_id INT REFERENCES Invoice (invoice_id) ON DELETE CASCADE,
    amount DECIMAL,
    paid_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

----------------------------
CREATE TABLE TaskAssignee (
    task_assignee_id SERIAL PRIMARY KEY,
    task_id INT REFERENCES Task (task_id) ON DELETE CASCADE,
    user_id INT REFERENCES "User" (user_id) ON DELETE CASCADE
);