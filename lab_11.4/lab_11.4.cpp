#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring> // для strcmp
#include <map>
#include <Windows.h>

using namespace std;

// Функція для підрахунку середнього пробігу
double CalculateAverageMileage(const string& filename, int& uniqueBrandsCount) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Не вдалося відкрити файл для читання!\n";
        return 0.0;
    }

    string line, brand;
    double mileage, totalMileage = 0.0;
    int totalCount = 0;
    map<string, bool> brandTracker;

    while (getline(infile, line)) {
        istringstream iss(line);
        double price;
        if (iss >> brand >> price >> mileage) {
            totalMileage += mileage;
            totalCount++;
            brandTracker[brand] = true; // Додаємо марку до мапи
        }
    }

    uniqueBrandsCount = brandTracker.size();
    infile.close();
    return (totalCount > 0) ? (totalMileage / totalCount) : 0.0;
}

// Функція для сортування файлу за алфавітом марки автомобіля
void SortFile(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Не вдалося відкрити файл для читання!\n";
        return;
    }

    // Масив для зберігання рядків
    string lines[1000];
    int count = 0;

    // Зчитуємо рядки у масив
    while (getline(infile, lines[count]) && count < 1000) {
        count++;
    }
    infile.close();

    // Сортуємо масив за алфавітом
    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            // Сортування рядків за алфавітом
            string brand1 = lines[i].substr(0, lines[i].find(' '));
            string brand2 = lines[j].substr(0, lines[j].find(' '));
            if (brand1 > brand2) {
                swap(lines[i], lines[j]);
            }
        }
    }

    // Розрахунок середнього пробігу
    int uniqueBrandsCount = 0;
    double averageMileage = CalculateAverageMileage(filename, uniqueBrandsCount);

    // Записуємо відсортовані рядки у новий файл
    ofstream outfile("sorted_" + filename);
    if (!outfile.is_open()) {
        cout << "Не вдалося відкрити файл для запису!\n";
        return;
    }

    cout << "\nВідсортовані дані (за алфавітом марки):\n";

    // Додаємо середній пробіг до кожного рядка
    for (int i = 0; i < count; ++i) {
        outfile << lines[i] << " Середній пробіг: " << averageMileage << "\n";
        cout << lines[i] << " Середній пробіг: " << averageMileage << "\n"; // Виводимо в консоль
    }

    // Додаємо останній рядок із кількістю різних марок
    outfile << "Кількість різних марок: " << uniqueBrandsCount << "\n";
    cout << "Кількість різних марок: " << uniqueBrandsCount << "\n"; // Виводимо в консоль

    outfile.close();
    cout << "Файл успішно відсортовано та оновлено як sorted_" << filename << ".\n";
}

// Основна функція
int main() {
    SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(1251);

    int option;
    string filename;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1 - Створити файл з даними автомобілів\n";
        cout << "2 - Упорядкувати та оновити файл\n";
        cout << "0 - Вихід\n";
        cout << "Оберіть опцію: ";
        cin >> option;

        if (cin.fail()) {
            cout << "Неправильне значення! Введіть число.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (option == 0) break;

        switch (option) {
        case 1: {
            ofstream outfile;
            cout << "Введіть назву файлу для збереження даних: ";
            cin >> filename;
            outfile.open(filename);

            if (!outfile.is_open()) {
                cout << "Не вдалося створити файл!\n";
                break;
            }

            char another;
            do {
                string brand;
                double price, mileage;
                cout << "Введіть марку автомобіля: ";
                cin >> ws;
                getline(cin, brand);

                cout << "Введіть ціну автомобіля: ";
                cin >> price;

                cout << "Введіть пробіг автомобіля: ";
                cin >> mileage;

                outfile << brand << " " << price << " " << mileage << "\n";

                cout << "Додати ще один автомобіль? (y/n): ";
                cin >> another;
            } while (another == 'y' || another == 'Y');

            outfile.close();
            cout << "Дані збережено у файл " << filename << ".\n";
            break;
        }
        case 2:
            cout << "Введіть назву файлу для обробки: ";
            cin >> filename;
            SortFile(filename);
            break;
        default:
            cout << "Неправильний вибір. Спробуйте ще раз.\n";
        }
    }

    return 0;
}
