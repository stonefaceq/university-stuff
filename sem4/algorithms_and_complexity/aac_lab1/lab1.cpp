#include <vector>
#include <algorithm>
#include <time.h>
#include <math.h>
#include <iostream>


struct Constants //зберігання констант для хеш-формули
{
	int a = 0; //ціла частина
	int b = 0; //дробова частина
	int c = 0; //знак
	int k = 0;
	void randomize(int p);
};

struct HashTable //структура хеш-таблиці
{
	Constants consts;
	int p;
	int size = 0;
	std::vector<std::vector<double>>* key_array;
	Constants* constants_array;
	HashTable(std::vector<std::vector<double>> keys);
	void rehash();
	void print();
	void find(std::vector<double> key);
	~HashTable();
};

bool is_prime(int value) //перевірка на простоту
{
    for (int i = 2; i * i <= value; i++)
    {
        if (value % i == 0)
            return false;
    }

    return true;
}


int next_prime(int value) //наступне просте число після заданого значення
{
    if (value <= 2)
        return 2;

    value++;

    while (!is_prime(value))
        value++;

    return value;
}

int* decompose_real_number(double value) //"розбираємо" число в масив [ціла частина, дробова частина] з точністю 1000
{
    int precision = 3;

    int* result = new int[2];

    double integer_part, fractional_part;
    fractional_part = modf(value, &integer_part);

    result[0] = abs((int)integer_part);
    result[1] = abs((int)(fractional_part * pow(10, precision)));

    return result;
}


int double_to_int_function(double value, int p, Constants constants) //перетворення дійсного в натуральне
{
    int* parts = decompose_real_number(value);

    int sign = 0;
    if (value < 0)
        sign = 1;

    int result = (parts[0] * constants.a + parts[1] * constants.b + constants.c * sign) % p;

    return result;
}

int hash_function(std::vector<double> double_array, int size, int p, Constants constants) //хешування масиву, повернення хеш-таблиці
{
    int result = 0;
    int arr_size = double_array.size();
    for (int i = 0; i < arr_size; i++)
        result += double_to_int_function(double_array[i], p, constants) * pow(constants.k, i);
    result = (result % p) % size;
    return result;
}


void Constants::randomize(int p) //знаходження випадкових констант 
{
    this->a = rand() % p;
    this->b = rand() % p;
    this->c = rand() % p;

    int k_div = 6;
    this->k = rand() % k_div;
}

HashTable::HashTable(std::vector<std::vector<double>> keys) //конструктор хеш-таблиці для вхідного масиву масивів keys
{
    srand(time(NULL));

    std::sort(keys.begin(), keys.end());
    keys.erase(std::unique(keys.begin(), keys.end()), keys.end());

    for (int i = 0; i < keys.size(); ) {
        if (keys[i].size() == 0) {
            keys.erase(keys.begin() + i);
        }
        else ++i;
    }

    this->size = keys.size();

    this->key_array = new std::vector<std::vector<double>>[this->size];
    this->constants_array = new Constants[this->size];

    this->p = next_prime(pow(size, 2));
    this->consts.randomize(this->p);

    for (auto& elem : keys)
    {
        int key = hash_function(elem, this->size, this->p, this->consts);
        this->key_array[key].push_back(elem);
    }

    rehash();
}

void HashTable::rehash() //пере-хешування для зникнення колізій, рандомізація констант
{
    for (int i = 0; i <= this->size - 1; i++)
    {
        int collisions_amount = this->key_array[i].size();
        int collision_array_size = pow(collisions_amount, 2);
        if (collisions_amount >= 2)
        {
            int attempt = 0;
            while (attempt < 30)
            {
                this->constants_array[i].randomize(this->p);
                std::vector<std::vector<double>> collision_array;
                collision_array.resize(collision_array_size);

                int counter = 0;
                for (counter = 0; counter <= collisions_amount - 1; counter++)
                {
                    std::vector<double> collision = this->key_array[i][counter];
                    int sub_key = hash_function(collision, collision_array_size, this->p, this->constants_array[i]);
                    if (collision_array[sub_key].size() != 0)
                        break;
                    collision_array[sub_key] = collision;
                }
                if (counter == collisions_amount)
                {
                    /*for (auto& elem : collision_array)
                        if(isnan(elem))
                            elem = 0;*/
                    this->key_array[i] = collision_array;
                    break;
                }

                attempt++;
            }
            if (attempt == 30)
                std::cout << "ERROR! NO POSSIBLE WAY TO AVOID COLLISIONS!\n\n";
        }
    }
}

HashTable::~HashTable()
{
    delete[] this->key_array;
    this->key_array = nullptr;

    delete[] this->constants_array;
    this->constants_array = nullptr;
}

void HashTable::print() //вивід хеш-таблиці
{
    for (int i = 0; i <= this->size - 1; i++)
    {
        std::cout << "Element " << i << ":";
        for (auto& elem : this->key_array[i])
            if (elem.size() == 0) std::cout << " _ ";
            else
            {
                std::cout << " {";
                for (auto& arr : elem)
                    std::cout << arr << "; ";
                std::cout << "} ";
            }
        std::cout << "\n";
    }

    std::cout << "\n";
    std::cout << "Constant Hash: ";
    std::cout << "a = " << this->consts.a
        << "  b = " << this->consts.b
        << "  c = " << this->consts.c
        << "  k = " << this->consts.k
        << "  p = " << this->p;
    std::cout << "\n";

    for (int i = 0; i <= this->size - 1; i++)
    {
        std::cout << "Constant[" << i << "]: ";
        std::cout << "a = " << this->constants_array[i].a
            << "  b = " << this->constants_array[i].b
            << "  c = " << this->constants_array[i].c
            << "  k = " << this->constants_array[i].k;
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

void HashTable::find(std::vector<double> key) //виводить інформацію про комірку в хеш-таблиці, де знаходиться масив дійсних чисел key
{
    int main_idx = hash_function(key, this->size, this->p, this->consts);
    int arr_size = this->key_array[main_idx].size();
    if (arr_size == 0)
    {
        std::cout << "THERE IS NO SUCH A NUMBER!\n\n";
        return;
    }

    int second_idx = 0;
    if (arr_size > 1)
        second_idx = hash_function(key, this->key_array[main_idx].size(), this->p, this->constants_array[main_idx]);

    if (this->key_array[main_idx][second_idx] == key && this->key_array[main_idx][second_idx].size() != 0)
        std::cout << "{" << main_idx << " ; " << second_idx << "}\n\n";
    else
        std::cout << "THERE IS NO SUCH A NUMBER!\n\n";
}



int main() {   //основна функція, створення
   
    std::vector<std::vector<double>> test
    {
        {0.01, -0.1, 0.02, -0.01, 0.25, 0.7},
        {2, 4, 5},
        {4, 26.3, 0.87},
        {109, 2, 5},
        {1.53, 0.08, 12.04}
    };

    std::vector<std::vector<double>> test2
    {
        {16.2, 10.001, 10.0004, 15, 0.02},
        {29.32, -15.9, 30.047},
        {-6, 2.3, 0.08754},
        {88895.643, -3.4356, 5.3},
        {553.43562, 34.42, -0.001},
        {0.9, 1.95, -0.26, 0.666, 65.68, -17.92}
    };

    std::vector<std::vector<double>> test3
    {
      {16.2, 10.001, 10.0004, 15, 0.02},
      {29.32, -15.9, 30.047},
      {-6, 2.3, 0.08754},
      {88895.643, -3.4356, 5.3},
      {88895.643, 5.3, -3.4356,},
      {},
      {553.43562, 34.42, -0.001},
      {0.9, 1.95, -0.26, 0.666, 65.68, -17.92}
    };

    HashTable test_table(test2);
    test_table.print();

    return 0;
}
