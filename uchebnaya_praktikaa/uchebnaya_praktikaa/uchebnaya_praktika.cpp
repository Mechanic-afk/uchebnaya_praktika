#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

// Размер игрового поля
int boardSize;

// Перечисление для типов ячеек
enum class CellType {
    Empty,
    Cross,
    Circle
};

int askBoardSize();
int askMode();
bool playAgain();
void displayBoard(const std::vector<std::vector<CellType>>& board);
bool checkWin(const std::vector<std::vector<CellType>>& board, CellType player);
void makeComputerMove(std::vector<std::vector<CellType>>& board, CellType player);
void makePlayerMove(std::vector<std::vector<CellType>>& board, CellType player);
void playTwoPlayerGame();
void playAgainstComputer();
bool findWinningMove(const std::vector<std::vector<CellType>>& board, CellType player, int& row, int& col);

int main() {
    setlocale(0, "");
    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    while (true)
    {
        std::cout << "Здравствуйте, рады приветствовать вас в игре Крестики-Нолики!\nЗдесь вы можете играть с другом или с компьютером, а также сами выбирать, на каком поле играть. Приятной игры!" << std::endl;
        boardSize = askBoardSize();
        std::cout << "Игра в крестики-нолики " << boardSize << "x" << boardSize << std::endl;
        int mode = askMode();
        switch (mode) {
        case 1:
            playTwoPlayerGame();
            break;
        case 2:
            playAgainstComputer();
            break;
        }
        if (!(playAgain()))
            break;
    }
    return 0;
}

// Ввод размеров игрового поля
int askBoardSize()
{
    int size;
    do {
        std::cout << "Выберите размерность игрового поля: ";
        std::cin >> size;
        // Проверка состояния ввода и очистка ошибки, если она произошла
        if (std::cin.fail()) {
            std::cin.clear();               // Очистка состояния ошибки
            std::cin.ignore(10000, '\n');   // Пропуск некорректных символов во вводе
        }
    } while (size > 50 || size <= 0);
    return size;
}

// Ввод режима игры
int askMode()
{
    int mode;
    do {
        std::cout << "Выберите режим игры:" << std::endl;
        std::cout << "1. Человек против человека" << std::endl;
        std::cout << "2. Человек против компьютера" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> mode;
        // Проверка состояния ввода и очистка ошибки, если она произошла
        if (std::cin.fail()) {
            std::cin.clear();               // Очистка состояния ошибки
            std::cin.ignore(10000, '\n');   // Пропуск некорректных символов во вводе
        }
    } while ((mode != 1) && (mode != 2));
    return mode;
}

// Предложение сыграть еще раз
bool playAgain()
{
    int ans;
    do {
        std::cout << "Хотите сыграть еще раз?" << std::endl;
        std::cout << "1. Да\n2. Нет" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> ans;
        // Проверка состояния ввода и очистка ошибки, если она произошла
        if (std::cin.fail()) {
            std::cin.clear();               // Очистка состояния ошибки
            std::cin.ignore(10000, '\n');   // Пропуск некорректных символов во вводе
        }
    } while ((ans != 1) && (ans != 2));
    if (ans == 1)
        return true;
    else if (ans == 2)
        return false;
}

// Отображение текущего состояния игрового поля
void displayBoard(const std::vector<std::vector<CellType>>& board) {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            switch (board[i][j]) {
            case CellType::Empty:
                std::cout << '-';
                break;
            case CellType::Cross:
                std::cout << 'X';
                break;
            case CellType::Circle:
                std::cout << 'O';
                break;
            }
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

// Проверка на победу заданного игрока
bool checkWin(const std::vector<std::vector<CellType>>& board, CellType player) {
    // Проверка по горизонтали и вертикали
    for (int i = 0; i < boardSize; ++i) {
        bool rowWin = true;
        bool colWin = true;
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j] != player) {
                rowWin = false;
            }
            if (board[j][i] != player) {
                colWin = false;
            }
        }
        if (rowWin || colWin) {
            return true;
        }
    }

    // Проверка по диагоналям
    bool diagWin = true;
    bool revDiagWin = true;
    for (int i = 0; i < boardSize; ++i) {
        if (board[i][i] != player) {
            diagWin = false;
        }
        if (board[i][boardSize - i - 1] != player) {
            revDiagWin = false;
        }
    }
    if (diagWin || revDiagWin) {
        return true;
    }
    return false;
}

// Поиск возможного выигрышного хода для заданного игрока
bool findWinningMove(const std::vector<std::vector<CellType>>& board, CellType player, int& row, int& col) {
    // Поиск выигрышного хода по горизонтали
    for (int i = 0; i < boardSize; ++i) {
        int emptyCount = 0;
        int emptyRow = -1;
        int emptyCol = -1;

        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j] == CellType::Empty) {
                emptyCount++;
                emptyRow = i;
                emptyCol = j;
            }
            else if (board[i][j] != player) {
                emptyCount = 0;
                break;
            }
        }

        if (emptyCount == 1) {
            row = emptyRow;
            col = emptyCol;
            return true;
        }
    }

    // Поиск выигрышного хода по вертикали
    for (int i = 0; i < boardSize; ++i) {
        int emptyCount = 0;
        int emptyRow = -1;
        int emptyCol = -1;

        for (int j = 0; j < boardSize; ++j) {
            if (board[j][i] == CellType::Empty) {
                emptyCount++;
                emptyRow = j;
                emptyCol = i;
            }
            else if (board[j][i] != player) {
                emptyCount = 0;
                break;
            }
        }

        if (emptyCount == 1) {
            row = emptyRow;
            col = emptyCol;
            return true;
        }
    }

    // Поиск выигрышного хода по диагонали
    int emptyCount = 0;
    int emptyRow = -1;
    int emptyCol = -1;

    for (int i = 0; i < boardSize; ++i) {
        if (board[i][i] == CellType::Empty) {
            emptyCount++;
            emptyRow = i;
            emptyCol = i;
        }
        else if (board[i][i] != player) {
            emptyCount = 0;
            break;
        }
    }

    if (emptyCount == 1) {
        row = emptyRow;
        col = emptyCol;
        return true;
    }

    // Поиск выигрышного хода по обратной диагонали
    emptyCount = 0;
    emptyRow = -1;
    emptyCol = -1;

    for (int i = 0; i < boardSize; ++i) {
        if (board[i][boardSize - i - 1] == CellType::Empty) {
            emptyCount++;
            emptyRow = i;
            emptyCol = boardSize - i - 1;
        }
        else if (board[i][boardSize - i - 1] != player) {
            emptyCount = 0;
            break;
        }
    }

    if (emptyCount == 1) {
        row = emptyRow;
        col = emptyCol;
        return true;
    }

    return false;
}

// Ход компьютера (выбор наилучшего хода)
void makeComputerMove(std::vector<std::vector<CellType>>& board, CellType player) {
    int row, col;

    // Попытка найти выигрышный ход для компьютера
    if (findWinningMove(board, player, row, col)) {
        board[row][col] = player;
        return;
    }

    // Попытка помешать игроку выиграть
    CellType opponent = (player == CellType::Circle) ? CellType::Cross : CellType::Circle;
    if (findWinningMove(board, opponent, row, col)) {
        board[row][col] = player;
        return;
    }

    // Если нет возможности выиграть или помешать победе противника, выбрать случайную пустую клетку
    do {
        row = std::rand() % boardSize;
        col = std::rand() % boardSize;
    } while (board[row][col] != CellType::Empty);

    board[row][col] = player;
}

// Ход игрока (ввод координат хода)
void makePlayerMove(std::vector<std::vector<CellType>>& board, CellType player) {
    int row, col;
    do {
        std::cout << "Введите координаты хода (номер строки и столбца): ";
        std::cin >> row >> col;
        // Уменьшение на единицу для соответствия индексам в векторе
        --row;
        --col;
        // Проверка состояния ввода и очистка ошибки, если она произошла
        if (std::cin.fail()) {
            std::cin.clear();               // Очистка состояния ошибки
            std::cin.ignore(10000, '\n');   // Пропуск некорректных символов во вводе
        }
    } while (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] != CellType::Empty);

    board[row][col] = player;
}

// Игра между двумя игроками
void playTwoPlayerGame() {
    std::vector<std::vector<CellType>> board(boardSize, std::vector<CellType>(boardSize, CellType::Empty));
    int currentPlayer = 1;
    int totalMoves = 0;
    while (true) {
        std::cout << "Текущее состояние поля:" << std::endl;
        displayBoard(board);

        if (currentPlayer == 1) {
            std::cout << "Ход игрока 1 (нолики)." << std::endl;
            makePlayerMove(board, CellType::Circle);
        }
        else {
            std::cout << "Ход игрока 2 (крестики)." << std::endl;
            makePlayerMove(board, CellType::Cross);
        }

        ++totalMoves;

        // Проверка победы ноликов
        if (checkWin(board, CellType::Circle)) {
            displayBoard(board);
            std::cout << "Игрок 1 (нолики) победил!" << std::endl;
            break;
        }
        // Проверка победы крестиков
        else if (checkWin(board, CellType::Cross)) {
            displayBoard(board);
            std::cout << "Игрок 2 (крестики) победил!" << std::endl;
            break;
        }
        // Проверка ничьи
        else if (totalMoves == boardSize * boardSize) {
            displayBoard(board);
            std::cout << "Ничья!" << std::endl;
            break;
        }
        // Смена хода игрока
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}

// Игра против компьютера
void playAgainstComputer() {
    std::vector<std::vector<CellType>> board(boardSize, std::vector<CellType>(boardSize, CellType::Empty));
    int currentPlayer = 1;
    int totalMoves = 0;
    while (true) {
        std::cout << "Текущее состояние поля:" << std::endl;
        displayBoard(board);

        if (currentPlayer == 1) {
            std::cout << "Ваш ход (нолики)." << std::endl;
            makePlayerMove(board, CellType::Circle);
        }
        else {
            std::cout << "Ход компьютера (крестики)." << std::endl;
            makeComputerMove(board, CellType::Cross);
        }

        ++totalMoves;

        // Проверка победы ноликов
        if (checkWin(board, CellType::Circle)) {
            displayBoard(board);
            std::cout << "Вы победили!" << std::endl;
            break;
        }
        // Проверка победы крестиков
        else if (checkWin(board, CellType::Cross)) {
            displayBoard(board);
            std::cout << "Компьютер победил!" << std::endl;
            break;
        }
        // Проверка ничьи
        else if (totalMoves == boardSize * boardSize) {
            displayBoard(board);
            std::cout << "Ничья!" << std::endl;
            break;
        }
        // Смена хода игрока
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}