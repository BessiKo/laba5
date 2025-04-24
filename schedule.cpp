#include <iostream> 
#include <vector>
#include <map>
#include <sstream>
#include <string>

using namespace std;

class Schedule {
private:

    map<int, map<string, int>> this_month;// {{день, {"дисциплина", кол-во}}, {}, {}}
    map<int, map<string, int>> next_month;
    int days = 31;

public:
    // Метод для добавления пары в расписание
    void Class(int day, const string& subject) {
        if (day < 1 || day > days) {
            cout << "Такого дня нет: " << day << endl;
            return;
        }
        this_month[day][subject]++;  // Увеличение количества пар для данной дисциплины в указанный день
    }

    // Метод для перехода на следующий месяц
    void Next() {
        next_month.clear();  // Очистка данных следующего месяца
        int days_next = (days == 31) ? 30 : 31;

        // Переносим все занятия на предпоследний день следующего месяца
        int penultimate = days_next - 1; // предпоследний день

        for (const auto& [day, subjects] : this_month) {
            if (day <= days_next) {
                for (const auto& [subject, count] : subjects) {
                    next_month[day][subject] += count;  // Перенос пар в следующий месяц
                }
            } else {
                for (const auto& [subject, count] : subjects) {
                    next_month[penultimate][subject] += count;  // Перенос пар на предпоследний день
                }
            }
        }

        this_month = move(next_month);  // Перенос данных следующего месяца в текущий месяц
        days = days_next;
    }

    // расписания на указанный день
    void View(int day) const {
        if (day < 1 || day > days) {
            cout << "Такого дня нет: " << day << endl;
            return;
        }

        auto it = this_month.find(day);  // Поиск дня в текущем месяце
        if (it == this_month.end() || it->second.empty()) {  // Проверка, есть ли пары в этот день не найден или пуст
            cout << "In " << day << " day we are free!" << endl;
        } else {
            cout << "In " << day << " day classes in university: ";
            for (const auto& [subject, count] : it->second) {
                cout << subject << "(" << count << ") ";
            }
            cout << endl;
        }
    }
};

// Функция для разбиения строки на токены
vector<string> split(const string& s) {
    vector<string> tokens;
    istringstream stream(s);
    string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    Schedule schedule;
    int N;
    cin >> N;
    cin.ignore();

    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);
        auto tokens = split(line);

        if (tokens.empty()) continue;

        string command = tokens[0];
        if (command == "CLASS" && tokens.size() >= 3) {
            int day = stoi(tokens[1]);
            string subject = tokens[2];
            for (size_t j = 3; j < tokens.size(); ++j) {
                subject += " " + tokens[j];
            }
            schedule.Class(day, subject);
        } else if (command == "NEXT") { 
            schedule.Next();
        } else if (command == "VIEW" && tokens.size() >= 2) {
            int day = stoi(tokens[1]);
            schedule.View(day);
        } else {
            cout << "Ошибка" << endl;
        }
    }

    return 0;
}
