import json
import random
from datetime import datetime, timedelta

# Функція для створення випадкової дати у вказаному діапазоні
def generate_random_date(start_date, end_date):
    delta_days = (end_date - start_date).days
    random_days = random.randint(0, delta_days)
    return start_date + timedelta(days=random_days)

# Генерація даних для магазинів
def create_store_data(store_count, product_range, start_date, end_date, expiry_start, expiry_end):
    stores = []
    for store_index in range(store_count):
        store_info = {
            "storeId": f"store_{store_index}",
            "storeName": f"Store_{store_index}",
            "location": {
                "city": random.choice(["Kyiv", "Lviv", "Odessa", "Dnipro", "Kharkiv"]),
                "address": f"Street {random.randint(1, 100)}, Building {random.randint(1, 20)}"
            },
            "openingDate": generate_random_date(start_date, end_date).strftime("%Y-%m-%d"),
            "products": generate_product_data(store_index, product_range, expiry_start, expiry_end),
            "isOpen": random.choice([True, False])
        }
        stores.append(store_info)
    return stores

# Генерація продуктів для одного магазину
def generate_product_data(store_index, product_range, expiry_start, expiry_end):
    products = []
    product_count = random.randint(product_range[0], product_range[1])
    for product_index in range(product_count):
        product_info = {
            "productId": f"product_{store_index}_{product_index}",
            "productName": f"Product_{random.randint(1, 1000)}",
            "category": random.choice(["Electronics", "Clothing", "Food", "Toys", "Furniture"]),
            "price": round(random.uniform(5, 500), 2),
            "stock": random.randint(0, 1000),
            "expiryDate": (
                generate_random_date(expiry_start, expiry_end).strftime("%Y-%m-%d")
                if random.choice([True, False]) else None
            )
        }
        products.append(product_info)
    return products

# Основний код для генерації JSON-файлу
def main():
    start_date = datetime(2020, 1, 1)
    end_date = datetime(2023, 12, 31)
    expiry_start = datetime(2024, 1, 1)
    expiry_end = datetime(2025, 12, 31)

    store_data = create_store_data(
        store_count=1000, 
        product_range=(5, 20), 
        start_date=start_date, 
        end_date=end_date, 
        expiry_start=expiry_start, 
        expiry_end=expiry_end
    )

    output_file = "stores_and_products.json"
    with open(output_file, "w", encoding="utf-8") as file:
        json.dump(store_data, file, indent=2, ensure_ascii=False)
    
    print(f"JSON-файл '{output_file}' успішно створено!")

if __name__ == "__main__":
    main()
