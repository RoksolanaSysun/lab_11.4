#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring> // ��� strcmp
#include <map>
#include <Windows.h>

using namespace std;

// ������� ��� ��������� ���������� ������
double CalculateAverageMileage(const string& filename, int& uniqueBrandsCount) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "�� ������� ������� ���� ��� �������!\n";
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
            brandTracker[brand] = true; // ������ ����� �� ����
        }
    }

    uniqueBrandsCount = brandTracker.size();
    infile.close();
    return (totalCount > 0) ? (totalMileage / totalCount) : 0.0;
}

// ������� ��� ���������� ����� �� �������� ����� ���������
void SortFile(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "�� ������� ������� ���� ��� �������!\n";
        return;
    }

    // ����� ��� ��������� �����
    string lines[1000];
    int count = 0;

    // ������� ����� � �����
    while (getline(infile, lines[count]) && count < 1000) {
        count++;
    }
    infile.close();

    // ������� ����� �� ��������
    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            // ���������� ����� �� ��������
            string brand1 = lines[i].substr(0, lines[i].find(' '));
            string brand2 = lines[j].substr(0, lines[j].find(' '));
            if (brand1 > brand2) {
                swap(lines[i], lines[j]);
            }
        }
    }

    // ���������� ���������� ������
    int uniqueBrandsCount = 0;
    double averageMileage = CalculateAverageMileage(filename, uniqueBrandsCount);

    // �������� ���������� ����� � ����� ����
    ofstream outfile("sorted_" + filename);
    if (!outfile.is_open()) {
        cout << "�� ������� ������� ���� ��� ������!\n";
        return;
    }

    cout << "\n³��������� ��� (�� �������� �����):\n";

    // ������ ������� ����� �� ������� �����
    for (int i = 0; i < count; ++i) {
        outfile << lines[i] << " ������� �����: " << averageMileage << "\n";
        cout << lines[i] << " ������� �����: " << averageMileage << "\n"; // �������� � �������
    }

    // ������ ������� ����� �� ������� ����� �����
    outfile << "ʳ������ ����� �����: " << uniqueBrandsCount << "\n";
    cout << "ʳ������ ����� �����: " << uniqueBrandsCount << "\n"; // �������� � �������

    outfile.close();
    cout << "���� ������ ����������� �� �������� �� sorted_" << filename << ".\n";
}

// ������� �������
int main() {
    SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
    SetConsoleOutputCP(1251);

    int option;
    string filename;

    while (true) {
        cout << "\n����:\n";
        cout << "1 - �������� ���� � ������ ���������\n";
        cout << "2 - ������������ �� ������� ����\n";
        cout << "0 - �����\n";
        cout << "������ �����: ";
        cin >> option;

        if (cin.fail()) {
            cout << "����������� ��������! ������ �����.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (option == 0) break;

        switch (option) {
        case 1: {
            ofstream outfile;
            cout << "������ ����� ����� ��� ���������� �����: ";
            cin >> filename;
            outfile.open(filename);

            if (!outfile.is_open()) {
                cout << "�� ������� �������� ����!\n";
                break;
            }

            char another;
            do {
                string brand;
                double price, mileage;
                cout << "������ ����� ���������: ";
                cin >> ws;
                getline(cin, brand);

                cout << "������ ���� ���������: ";
                cin >> price;

                cout << "������ ����� ���������: ";
                cin >> mileage;

                outfile << brand << " " << price << " " << mileage << "\n";

                cout << "������ �� ���� ���������? (y/n): ";
                cin >> another;
            } while (another == 'y' || another == 'Y');

            outfile.close();
            cout << "��� ��������� � ���� " << filename << ".\n";
            break;
        }
        case 2:
            cout << "������ ����� ����� ��� �������: ";
            cin >> filename;
            SortFile(filename);
            break;
        default:
            cout << "������������ ����. ��������� �� ���.\n";
        }
    }

    return 0;
}
