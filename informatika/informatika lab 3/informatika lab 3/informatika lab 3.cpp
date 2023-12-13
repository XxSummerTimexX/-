#include <iostream>   
#include <string>   
#include <cstdlib>   
#include <limits> 

using namespace std;

const int BOARD_SIZE = 3; // аРзмерчик поля
// Перечисление для представления знаков на игровом поле
enum Sign {
    EMPTY = '.',
    X = 'X',
    O = 'O'
};

// Структура для представления координат
struct Coordinate {
    int row;
    int col;
};

// Инициализация игрового поля
char board[BOARD_SIZE][BOARD_SIZE] = {
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY}
};
// отображение поля
void printBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
// Функция для проверкии победителя
bool checkWinner(char sign) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((board[i][0] == sign && board[i][1] == sign && board[i][2] == sign) ||
            (board[0][i] == sign && board[1][i] == sign && board[2][i] == sign)) {
            return true;
        }
    }
    if ((board[0][0] == sign && board[1][1] == sign && board[2][2] == sign) ||
        (board[0][2] == sign && board[1][1] == sign && board[2][0] == sign)) {
        return true;
    }
    return false;
}
// Функция для получения хода от пользователя
Coordinate getUserMove(char userSign) {
    Coordinate move;
    cout << "Your turn" << endl;
    cout << "Input the row and column for your move (format: row column): ";

    while (!(cin >> move.row >> move.col) || move.row < 1 || move.row > BOARD_SIZE || move.col < 1 || move.col > BOARD_SIZE || board[move.row - 1][move.col - 1] != EMPTY) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter valid row and column: ";
    }

    move.row--;
    move.col--;
    return move;
}

// Функция для получения хода от бота
Coordinate getBotMove(char botSign) {
    Coordinate move;
    do {
        move.row = rand() % BOARD_SIZE;
        move.col = rand() % BOARD_SIZE;
    } while (board[move.row][move.col] != EMPTY);
    return move;
}

// Основная функция для игры в крестики-нолики
void playGame() {
    char userSign;
    cout << "Choose your sign (X/O): ";
    while ((cin >> userSign) && (userSign != 'X' && userSign != 'O')) {
        cout << "Invalid choice. Please choose X or O: ";
    }
    char botSign = (userSign == X) ? O : X;
    bool userTurn = true;
    int moves = 0;

    // Основной игровой цикл
    while (moves < BOARD_SIZE * BOARD_SIZE) {
        cout << "Current state:" << endl;
        printBoard();

        Coordinate move;
        if (userTurn) {
            move = getUserMove(userSign);
        }
        else {
            move = getBotMove(botSign);
        }

        if (board[move.row][move.col] == EMPTY) {
            board[move.row][move.col] = (userTurn) ? userSign : botSign;
            if (checkWinner(board[move.row][move.col])) {
                cout << ((userTurn) ? "Congratulations! You win!" : "Bot wins!") << endl;
                printBoard();
                return;
            }
            userTurn = !userTurn;
            moves++;
        }
        else {
            cout << "This cell is already occupied. Please choose another one." << endl;
        }
    }
    cout << "It's a draw!" << endl;
    printBoard();
}

int main() {
    srand((unsigned)time(0));
    cout << "Tic-tac-toe" << endl;
    playGame();
    return 0;
}
