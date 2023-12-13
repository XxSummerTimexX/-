//Лабороторная работа номер 1
//Вариант 21


#include <iostream> 
#include <string>
#include <cctype>
using namespace std;

//проверяем является ли введенная строка целым числом..
bool isInteger(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

//Функция для проверки является ли число простым 
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

//функция для проверки гипотезы Гольдбаха.. 
pair<int, int> goldbach(int evenNumber) {
    for (int i = 2; i <= evenNumber / 2; i++) {
        if (isPrime(i) && isPrime(evenNumber - i)) { // проверяем является ли текущее число i и разность простыми
            return make_pair(i, evenNumber - i);
        }
    }
    return make_pair(-1, -1); //гипотеза гольдбаха не сработала
}

int main() {
    setlocale(LC_ALL, "RU");
    bool continueThisProg = true;
    while (continueThisProg) {
        int evenNumber;
        bool validInput = false;
        string input;

        //проверка ввода четного числа 
        while (!validInput) {
            cout << "Введите чётное число: ";
            cin >> input;
            if (isInteger(input)) {
                evenNumber = stoi(input);
                if (evenNumber % 2 == 0 && evenNumber > 0) {
                    validInput = true;
                }
            }
            if (!validInput) {
                cout << "Ошибка: Введите целое четное число > 0" << endl;
            }
        }

        //поиск пары простых чисел, сумма которых равна введенному четному числу 
        pair<int, int> result = goldbach(evenNumber);
        if (result.first != -1 && result.second != -1) {
            cout << "Ответ: " << evenNumber << " = " << result.first << " + " << result.second << "." << endl;
        }
        else {
            cout << "Гипотеза Гольдбаха не подтверждена для данного числа." << endl;
        }

        char choice;
        cout << "Хотите продолжить? Введите y если да или любой другой символ если нет: ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            continueThisProg = false;
        }
    }

    return 0;
}
