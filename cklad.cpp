#include <iostream> 
#include <map> 
#include <vector>
#include <string>
#include <iomanip>
#include <locale>

using namespace std;

// Структура о товаре в ячейке - название и кол-во
struct Cell {
    string product;
    int quantity;
};

// склад map ключ - адрес ячейки, значение - вектор товаров {{A111 {{"name", count}, {}, {}}}, {}, {}}
map<string, vector<Cell>> store;

// количества товаров в ячейкe
int Quantity(const string& address) {
    int count = 0;
    const vector<Cell>& cellVector = store[address];  // Получение вектора товаров по адресу
    for (size_t i = 0; i < cellVector.size(); ++i) {  // Перебор всех товаров в ячейке
        count += cellVector[i].quantity;  // + кол-во текущего товара
    }
    return count;
}

// инициализации склада
void Creation() {
    vector<string> area = {"A", "B"};
    for (const string& area : area) {
        for (int rack = 1; rack <= 6; ++rack) {  // стеллажи - 6
            for (int section = 1; section <= 4; ++section) {  // секции - 4
                for (int shelf = 1; shelf <= 4; ++shelf) {  // полоки  - 4
                    string address = area + to_string(rack) + to_string(section) + to_string(shelf);  // адреса ячейки
                    store[address] = {};  // Инициализация пустой ячейки
                }
            }
        }
    }
}

// добавления товара
void add(const string& product, int quantity, const string& address) {
    if (store.count(address) == 0) {  // Проверка существования адреса
        cout << "Такого адреса не существует" << endl;
        return;
    }

    int can = 10 - Quantity(address);  // оставшееся место
    if (quantity > can) {
        cout << "По данному адресу вы можете положить не более " << can << " единиц товара." << endl;
        return;
    }

    vector<Cell>& cellVector = store[address];
    // есть ли уже такой товар в ячейке
    for (size_t i = 0; i < cellVector.size(); ++i) {
        Cell& cell = cellVector[i];
        if (cell.product == product) {
            cell.quantity += quantity;
            return;
        }
    }

    // Добавление нового товара в ячейку
    cellVector.push_back({product, quantity});
}

// удаления товара из ячейки
void remove(const string& product, int quantity, const string& address) {
    if (store.count(address) == 0) {
        cout << "Такого адреса не существует" << endl;
        return;
    }

    vector<Cell>& cellVector = store[address];
    for (size_t i = 0; i < cellVector.size(); ++i) {
        Cell& cell = cellVector[i]; 
        if (cell.product == product) {
            if (cell.quantity < quantity) {
                cout << "Вы удаляете больше единиц товара, чем есть в ячейке" << endl;
                return;
            }
            cell.quantity -= quantity;
            if (cell.quantity == 0) {
                cellVector.erase(cellVector.begin() + i);  // Удаление товара из ячейки, если его количество стало 0
                return;
            }
            return;
        }
    }

    cout << "Такого товара нет, чтобы его удалять" << endl;
}

// Функция для вывода информации о состоянии склада
void info() {
    int totalCapacity = 1920;  // Общая вместимость склада
    int totalItems = 0;         // Общее количество товаров на складе
    int zoneACapacity = 960;   // Вместимость зоны A
    int zoneBCapacity = 960;   
    int zoneAItems = 0;        // Количество товаров в зоне A
    int zoneBItems = 0;        

    cout << "Состояние склада:" << endl;
    for (map<string, vector<Cell>>::const_iterator it = store.begin(); it != store.end(); ++it) {  // Перебор всех ячеек
        const string& address = it->first;  //  адреса
        const vector<Cell>& cellVector = it->second;  // вектора товаров
        if (!cellVector.empty()) { 
            cout << address << ": ";
            for (size_t i = 0; i < cellVector.size(); ++i) {  // Перебор всех товаров в ячейке
                const Cell& cell = cellVector[i]; 
                if (cell.quantity > 0) {
                    cout << cell.product << " (" << cell.quantity << " шт.) ";
                    totalItems += cell.quantity;
                    if (address[0] == 'A') {
                        zoneAItems += cell.quantity;  // Увеличение количества товаров в зоне A
                    } else if (address[0] == 'B') {
                        zoneBItems += cell.quantity;
                    }
                }
            }
            cout << endl;
        }
    }

    cout << "Пустые ячейки:" << endl;
    for (map<string, vector<Cell>>::const_iterator it = store.begin(); it != store.end(); ++it) {
        if (it->second.empty() || Quantity(it->first) == 0) { 
            cout << it->first << " "; 
        }
    }

    cout << endl;

    //насколько процентов загружен склад, на сколько процентов загружена каждая зона склада
    cout << "Склад загружен на: " << fixed << setprecision(2)
         << (static_cast<double>(totalItems) / totalCapacity) * 100 << "%" << endl;
    cout << "Зона A загружена на: " << (static_cast<double>(zoneAItems) / zoneACapacity) * 100 << "%" << endl;
    cout << "Зона B загружена на: " << (static_cast<double>(zoneBItems) / zoneBCapacity) * 100 << "%" << endl;
}

int main() {
    Creation();  // Инициализация склада
    string command, product, address;
    int quantity;

    while (true) {
        cin >> command; 
        if (command == "ADD") { 
            cin >> product >> quantity >> address;
            add(product, quantity, address);
        } else if (command == "REMOVE") { 
            cin >> product >> quantity >> address;
            remove(product, quantity, address); 
        } else if (command == "INFO") {
            info();
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "Такой команды не существует" << endl;
        }
    }

    return 0;
}
