import time
import json
from pymongo import MongoClient
import psycopg2

# Підключення до MongoDB
mongo_client = MongoClient("mongodb://localhost:27017/")
mongo_db = mongo_client["lab1database"]
mongo_collection = mongo_db["lab1collection"]

# Підключення до PostgreSQL
pg_conn = psycopg2.connect(
    dbname="lab2",
    user="postgres",
    password="pass4user",
    host="localhost",
    port="5432"
)
pg_cursor = pg_conn.cursor()

# Функція для вимірювання часу виконання
def measure_time(query_func, *args):
    start_time = time.time()
    query_func(*args)
    end_time = time.time()
    return end_time - start_time

results = []

# Test 1: Пошук продуктів за категорією і ціною
def mongo_filter_products():
    mongo_collection.aggregate([
        {"$unwind": "$products"},
        {"$match": {"products.category": "Electronics", "products.price": {"$lt": 1000}}}
    ])

def postgres_filter_products():
    pg_cursor.execute("""
        SELECT * FROM products
        WHERE category = 'Electronics' AND price < 1000;
    """)
    pg_cursor.fetchall()

results.append({
    "test": "Filter products by category and price",
    "MongoDB": measure_time(mongo_filter_products),
    "PostgreSQL": measure_time(postgres_filter_products)
})

# Test 2: Пошук магазинів з певною кількістю продуктів певної категорії
def mongo_find_stores_number_of_categories():
    mongo_collection.aggregate([
        {"$unwind": "$products"},
        {"$match": {"products.category": "Books"}},
        {"$group": {
            "_id": "$store_uid",
            "product_count": {"$sum": 1}
        }},
        {"$match": {"product_count": {"$gt": 10}}}
    ])

def postgres_find_stores_number_of_categories():
    pg_cursor.execute("""
        SELECT s.store_uid, COUNT(*) AS product_count
        FROM stores s
        JOIN products p ON s.store_uid = p.store_uid
        WHERE p.category = 'Books'
        GROUP BY s.store_uid
        HAVING COUNT(*) > 10;
    """)
    pg_cursor.fetchall()

results.append({
    "test": "Find stores with more than 10 products in a specific category",
    "MongoDB": measure_time(mongo_find_stores_number_of_categories),
    "PostgreSQL": measure_time(postgres_find_stores_number_of_categories)
})

# Test 3: Підрахунок продуктів за категоріями для кожного магазину
def mongo_count_products_by_categories():
    mongo_collection.aggregate([
        {"$unwind": "$products"},
        {"$group": {
            "_id": {"store_uid": "$store_uid", "category": "$products.category"},
            "product_count": {"$sum": 1}
        }}
    ])

def postgres_count_products_by_categories():
    pg_cursor.execute("""
        SELECT p.store_uid, p.category, COUNT(*) AS product_count
        FROM products p
        GROUP BY p.store_uid, p.category;
    """)
    pg_cursor.fetchall()

results.append({
    "test": "Count products by category for each store",
    "MongoDB": measure_time(mongo_count_products_by_categories),
    "PostgreSQL": measure_time(postgres_count_products_by_categories)
})

# Test 4: Отримання повної інформації про магазини з певними умовами
def mongo_full_store_info():
    mongo_collection.aggregate([
        {"$unwind": "$products"},
        {"$match": {"products.price": {"$gt": 500}, "products.category": "Furniture"}},
        {"$group": {
            "_id": "$store_uid",
            "store_name": {"$first": "$store_name"},
            "products": {"$push": "$products"}
        }}
    ])

def postgres_full_store_info():
    pg_cursor.execute("""
        SELECT s.*, p.*
        FROM stores s
        JOIN products p ON s.store_uid = p.store_uid
        WHERE p.price > 500 AND p.category = 'Furniture';
    """)
    pg_cursor.fetchall()

results.append({
    "test": "Filter stores with specific products and get full info",
    "MongoDB": measure_time(mongo_full_store_info),
    "PostgreSQL": measure_time(postgres_full_store_info)
})

# Вивід результатів
for result in results:
    print(f"Test: {result['test']}")
    print(f"  MongoDB: {result['MongoDB']:.6f} seconds")
    print(f"  PostgreSQL: {result['PostgreSQL']:.6f} seconds")

# Закриття підключень
pg_cursor.close()
pg_conn.close()
mongo_client.close()
