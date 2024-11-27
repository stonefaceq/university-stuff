-- Індекси для таблиці "User"
CREATE INDEX idx_user_user_id ON "User" (user_id);

-- Індекси для таблиці Role
CREATE INDEX idx_role_role_id ON Role (role_id);

-- Індекси для таблиці UserRole
CREATE INDEX idx_user_role_user_role_id ON UserRole (user_role_id);
CREATE INDEX idx_user_role_user_id ON UserRole (user_id);
CREATE INDEX idx_user_role_role_id ON UserRole (role_id);

-- Індекси для таблиці Project
CREATE INDEX idx_project_project_id ON Project (project_id);

-- Індекси для таблиці ProjectMember
CREATE INDEX idx_project_member_project_member_id ON ProjectMember (project_member_id);
CREATE INDEX idx_project_member_project_id ON ProjectMember (project_id);
CREATE INDEX idx_project_member_user_id ON ProjectMember (user_id);

-- Індекси для таблиці TaskStatus
CREATE INDEX idx_task_status_status_id ON TaskStatus (status_id);

-- Індекси для таблиці Task
CREATE INDEX idx_task_task_id ON Task (task_id);
CREATE INDEX idx_task_project_id ON Task (project_id);
CREATE INDEX idx_task_status_id ON Task (status_id);
CREATE INDEX idx_task_updated_by ON Task (updated_by);

-- Індекси для таблиці Comment
CREATE INDEX idx_comment_comment_id ON Comment (comment_id);
CREATE INDEX idx_comment_task_id ON Comment (task_id);
CREATE INDEX idx_comment_user_id ON Comment (user_id);

-- Індекси для таблиці TimeLog
CREATE INDEX idx_time_log_time_log_id ON TimeLog (time_log_id);
CREATE INDEX idx_time_log_task_id ON TimeLog (task_id);
CREATE INDEX idx_time_log_user_id ON TimeLog (user_id);

-- Індекси для таблиці Attachment
CREATE INDEX idx_attachment_attachment_id ON Attachment (attachment_id);
CREATE INDEX idx_attachment_task_id ON Attachment (task_id);
CREATE INDEX idx_attachment_uploaded_by ON Attachment (uploaded_by);

-- Індекси для таблиці Notification
CREATE INDEX idx_notification_notification_id ON Notification (notification_id);
CREATE INDEX idx_notification_user_id ON Notification (user_id);

-- Індекси для таблиці Tag
CREATE INDEX idx_tag_tag_id ON Tag (tag_id);

-- Індекси для таблиці TaskTag
CREATE INDEX idx_task_tag_task_tag_id ON TaskTag (task_tag_id);
CREATE INDEX idx_task_tag_task_id ON TaskTag (task_id);
CREATE INDEX idx_task_tag_tag_id ON TaskTag (tag_id);

-- Індекси для таблиці Invoice
CREATE INDEX idx_invoice_invoice_id ON Invoice (invoice_id);
CREATE INDEX idx_invoice_project_id ON Invoice (project_id);

-- Індекси для таблиці Payment
CREATE INDEX idx_payment_payment_id ON Payment (payment_id);
CREATE INDEX idx_payment_invoice_id ON Payment (invoice_id);

-- Індекси для таблиці TaskAssignee
CREATE INDEX idx_task_assignee_task_assignee_id ON TaskAssignee (task_assignee_id);
CREATE INDEX idx_task_assignee_task_id ON TaskAssignee (task_id);
CREATE INDEX idx_task_assignee_user_id ON TaskAssignee (user_id);
