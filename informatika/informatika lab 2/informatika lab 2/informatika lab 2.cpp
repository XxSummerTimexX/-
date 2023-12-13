#include <iostream>
#include <string>
using namespace std;

struct Point {
    double x;
    double y;
};

bool validateInput(string input, double& value) {
    try {
        value = stod(input); // Преобразование строки в число типа double
        return true; // Вернуть true, если преобразование прошло успешно
    }
    catch (const invalid_argument& e) {
        return false; // Вернуть false, если преобразование вызвало исключение invalid_argument
    }
    catch (const out_of_range& e) {
        return false; // Вернуть false, если преобразование вызвало исключение out_of_range
    }
}

bool getInput(Point& point, int pointNumber) {
    string input;
    double value;

    cout << "Введите координаты точки #" << pointNumber << "> ";
    cin >> input;
    if (!validateInput(input, value)) {
        cout << "Неверный ввод. Пожалуйста, введите числовое значение." << endl;
        return false; // Вернуть false при неверном вводе
    }
    point.x = value;

    cin >> input;
    if (!validateInput(input, value)) {
        cout << "Неверный ввод. Пожалуйста, введите числовое значение." << endl;
        return false; // Вернуть false при неверном вводе
    }
    point.y = value;

    return true; // Вернуть true, если ввод прошел успешно
}

void constructParabola(Point p1, Point p2, Point p3) {
    // Та же реализация, что и раньше
    double a, b, c;
    double denominator = (p1.x - p2.x) * (p1.x - p3.x) * (p2.x - p3.x);
    a = (p3.x * (p2.y - p1.y) - p2.x * (p3.y - p1.y) + p1.x * (p3.y - p2.y)) / denominator;
    b = (p2.x * p2.x * (p1.y - p3.y) + p1.x * p1.x * (p3.y - p2.y) + p3.x * p3.x * (p2.y - p1.y)) / denominator;
    c = (p1.x * p2.x * (p1.x - p2.x) * p3.y + p2.x * p3.x * (p2.x - p3.x) * p1.y + p3.x * p1.x * (p3.x - p1.x) * p2.y) / denominator;

    cout << "y = " << a << "x^2 + " << b << "x + " << c << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    char choice;

    do {
        Point p1, p2, p3;

        while (!getInput(p1, 1)) {} // Запрашиваем координаты для точки 1, пока ввод не будет успешным
        while (!getInput(p2, 2)) {} // Запрашиваем координаты для точки 2, пока ввод не будет успешным
        while (!getInput(p3, 3)) {} // Запрашиваем координаты для точки 3, пока ввод не будет успешным

        constructParabola(p1, p2, p3); // Строим параболу по заданным точкам

        cout << "Продолжить? (Y/N)> ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y'); // Продолжаем программу, если выбран ответ "Y" или "y"

    return 0;
}
