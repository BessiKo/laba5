#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Структура для хранения информации о посетителе - время и номер
struct Visitor {
    int time;
    string coupon;
};

// выдача талончика
string Coupon() {
    static int counter = 0;
    ostringstream oss; 
    oss << "T" << counter++;
    return oss.str();
}

// добавление посетителя в очередь - время и номер - заносим в вектор
void in_enqueue(queue<Visitor>& queue, int time) {
    Visitor visitor;
    visitor.time = time;  // время
    visitor.coupon = Coupon();  // талончик
    queue.push(visitor);
    cout << visitor.coupon << endl;
}

// распределения посетителей по окнам
void okno(queue<Visitor>& queue, int count_windows) {
    vector<vector<Visitor>> windows(count_windows);  // посетителей в каждом окне
    vector<int> windowEndTimes(count_windows, 0);  // времени окончания обслуживания в каждом окне

    vector<Visitor> visitors;  // все посетители
    while (!queue.empty()) {
        visitors.push_back(queue.front());
        queue.pop();
    }

    // Сортируем посетителей по убыванию времени обслуживания
    sort(visitors.begin(), visitors.end(), [](const Visitor& a, const Visitor& b) {
        return a.time > b.time;
    });

    // Распределяем посетителей по окнам
    for (const auto& visitor : visitors) {
        // Найти окно с минимальным временем окончания обслуживания - индекс
        int minindex = min_element(windowEndTimes.begin(), windowEndTimes.end()) - windowEndTimes.begin();
        windows[minindex].push_back(visitor);

        // время для этого окна
        windowEndTimes[minindex] += visitor.time;
    }

    for (int i = 0; i < count_windows; ++i) {
        cout << "Окно " << i + 1 << " (" << windowEndTimes[i] << " минут):";
        for (const auto& visitor : windows[i]) {
            cout << " " << visitor.coupon;
        }
        cout << endl;
    }
}

int main() {
    int count_windows;  // кол-во окон
    cout << "Кол-во окон: ";
    cin >> count_windows;

    queue<Visitor> queue;
    string command;
    int time;

    while (true) {
        cin >> command;
        if (command == "ENQUEUE") {
            cin >> time;
            in_enqueue(queue, time);
        } else if (command == "DISTRIBUTE") {
            okno(queue, count_windows);
            break;
        }
    }

    return 0;
}
