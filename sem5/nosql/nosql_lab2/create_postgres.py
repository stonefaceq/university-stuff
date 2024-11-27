import json
import psycopg2

def connect_to_postgres(database, user, password, host, port):
    """
    Функція для підключення до PostgreSQL.
    """
    return psycopg2.connect(
        dbname=database,
        user=user,
        password=password,
        host=host,
        port=port
    )

def setup_database(cursor):
    """
    Створює необхідні таблиці в базі даних, якщо вони ще не існують.
    """
    create_tables_query = """
    CREATE TABLE IF NOT EXISTS stores (
        store_id SERIAL PRIMARY KEY,
        store_uid TEXT UNIQUE NOT NULL,
        store_name TEXT,
        city TEXT,
        address TEXT,
        opening_date DATE,
        is_open BOOLEAN
    );

    CREATE TABLE IF NOT EXISTS products (
        product_id SERIAL PRIMARY KEY,
        store_uid TEXT REFERENCES stores(store_uid) ON DELETE CASCADE,
        product_name TEXT,
        category TEXT,
        price NUMERIC,
        stock INTEGER,
        expiry_date DATE
    );
    """
    cursor.execute(create_tables_query)

def load_json_data(file_path):
    """
    Завантажує дані з JSON-файлу.
    """
    with open(file_path, 'r', encoding='utf-8') as file:
        return json.load(file)

def insert_store_data(cursor, store_data):
    """
    Вставляє дані магазину в таблицю stores.
    """
    insert_store_query = """
    INSERT INTO stores (store_uid, store_name, city, address, opening_date, is_open)
    VALUES (%s, %s, %s, %s, %s, %s)
    ON CONFLICT (store_uid) DO NOTHING;
    """
    cursor.execute(insert_store_query, (
        store_data['storeId'],
        store_data['storeName'],
        store_data['location']['city'],
        store_data['location']['address'],
        store_data['openingDate'],
        store_data['isOpen']
    ))

def insert_product_data(cursor, store_id, product_data):
    """
    Вставляє дані продукту в таблицю products.
    """
    insert_product_query = """
    INSERT INTO products (store_uid, product_name, category, price, stock, expiry_date)
    VALUES (%s, %s, %s, %s, %s, %s);
    """
    cursor.execute(insert_product_query, (
        store_id,
        product_data['productName'],
        product_data['category'],
        product_data['price'],
        product_data['stock'],
        product_data.get('expiryDate')  # Може бути None
    ))

def main():
    # Налаштування підключення
    database_config = {
        "database": "lab2",
        "user": "postgres",
        "password": "pass4user",
        "host": "localhost",
        "port": "5432"
    }

    json_file_path = 'stores_and_products.json'  # Замініть на шлях до JSON-файлу

    try:
        # Підключення до бази даних
        connection = connect_to_postgres(**database_config)
        cursor = connection.cursor()

        # Створення таблиць
        setup_database(cursor)
        connection.commit()

        # Завантаження даних із JSON
        store_data_list = load_json_data(json_file_path)

        # Вставка даних у базу
        for store_data in store_data_list:
            insert_store_data(cursor, store_data)
            for product in store_data['products']:
                insert_product_data(cursor, store_data['storeId'], product)

        # Застосування змін
        connection.commit()
        print("Дані успішно завантажені в PostgreSQL!")

    except Exception as e:
        print(f"Виникла помилка: {e}")
    finally:
        # Закриття підключення
        if cursor:
            cursor.close()
        if connection:
            connection.close()

if __name__ == "__main__":
    main()
