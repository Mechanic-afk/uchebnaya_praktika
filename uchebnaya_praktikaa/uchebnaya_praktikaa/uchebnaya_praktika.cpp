#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

// ������ �������� ����
int boardSize;

// ������������ ��� ����� �����
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
    // ������������� ���������� ��������� �����
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    while (true)
    {
        std::cout << "������������, ���� �������������� ��� � ���� ��������-������!\n����� �� ������ ������ � ������ ��� � �����������, � ����� ���� ��������, �� ����� ���� ������. �������� ����!" << std::endl;
        boardSize = askBoardSize();
        std::cout << "���� � ��������-������ " << boardSize << "x" << boardSize << std::endl;
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

// ���� �������� �������� ����
int askBoardSize()
{
    int size;
    do {
        std::cout << "�������� ����������� �������� ����: ";
        std::cin >> size;
        // �������� ��������� ����� � ������� ������, ���� ��� ���������
        if (std::cin.fail()) {
            std::cin.clear();               // ������� ��������� ������
            std::cin.ignore(10000, '\n');   // ������� ������������ �������� �� �����
        }
    } while (size > 50 || size <= 0);
    return size;
}

// ���� ������ ����
int askMode()
{
    int mode;
    do {
        std::cout << "�������� ����� ����:" << std::endl;
        std::cout << "1. ������� ������ ��������" << std::endl;
        std::cout << "2. ������� ������ ����������" << std::endl;
        std::cout << "��� �����: ";
        std::cin >> mode;
        // �������� ��������� ����� � ������� ������, ���� ��� ���������
        if (std::cin.fail()) {
            std::cin.clear();               // ������� ��������� ������
            std::cin.ignore(10000, '\n');   // ������� ������������ �������� �� �����
        }
    } while ((mode != 1) && (mode != 2));
    return mode;
}

// ����������� ������� ��� ���
bool playAgain()
{
    int ans;
    do {
        std::cout << "������ ������� ��� ���?" << std::endl;
        std::cout << "1. ��\n2. ���" << std::endl;
        std::cout << "��� �����: ";
        std::cin >> ans;
        // �������� ��������� ����� � ������� ������, ���� ��� ���������
        if (std::cin.fail()) {
            std::cin.clear();               // ������� ��������� ������
            std::cin.ignore(10000, '\n');   // ������� ������������ �������� �� �����
        }
    } while ((ans != 1) && (ans != 2));
    if (ans == 1)
        return true;
    else if (ans == 2)
        return false;
}

// ����������� �������� ��������� �������� ����
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

// �������� �� ������ ��������� ������
bool checkWin(const std::vector<std::vector<CellType>>& board, CellType player) {
    // �������� �� ����������� � ���������
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

    // �������� �� ����������
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

// ����� ���������� ����������� ���� ��� ��������� ������
bool findWinningMove(const std::vector<std::vector<CellType>>& board, CellType player, int& row, int& col) {
    // ����� ����������� ���� �� �����������
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

    // ����� ����������� ���� �� ���������
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

    // ����� ����������� ���� �� ���������
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

    // ����� ����������� ���� �� �������� ���������
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

// ��� ���������� (����� ���������� ����)
void makeComputerMove(std::vector<std::vector<CellType>>& board, CellType player) {
    int row, col;

    // ������� ����� ���������� ��� ��� ����������
    if (findWinningMove(board, player, row, col)) {
        board[row][col] = player;
        return;
    }

    // ������� �������� ������ ��������
    CellType opponent = (player == CellType::Circle) ? CellType::Cross : CellType::Circle;
    if (findWinningMove(board, opponent, row, col)) {
        board[row][col] = player;
        return;
    }

    // ���� ��� ����������� �������� ��� �������� ������ ����������, ������� ��������� ������ ������
    do {
        row = std::rand() % boardSize;
        col = std::rand() % boardSize;
    } while (board[row][col] != CellType::Empty);

    board[row][col] = player;
}

// ��� ������ (���� ��������� ����)
void makePlayerMove(std::vector<std::vector<CellType>>& board, CellType player) {
    int row, col;
    do {
        std::cout << "������� ���������� ���� (����� ������ � �������): ";
        std::cin >> row >> col;
        // ���������� �� ������� ��� ������������ �������� � �������
        --row;
        --col;
        // �������� ��������� ����� � ������� ������, ���� ��� ���������
        if (std::cin.fail()) {
            std::cin.clear();               // ������� ��������� ������
            std::cin.ignore(10000, '\n');   // ������� ������������ �������� �� �����
        }
    } while (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] != CellType::Empty);

    board[row][col] = player;
}

// ���� ����� ����� ��������
void playTwoPlayerGame() {
    std::vector<std::vector<CellType>> board(boardSize, std::vector<CellType>(boardSize, CellType::Empty));
    int currentPlayer = 1;
    int totalMoves = 0;
    while (true) {
        std::cout << "������� ��������� ����:" << std::endl;
        displayBoard(board);

        if (currentPlayer == 1) {
            std::cout << "��� ������ 1 (������)." << std::endl;
            makePlayerMove(board, CellType::Circle);
        }
        else {
            std::cout << "��� ������ 2 (��������)." << std::endl;
            makePlayerMove(board, CellType::Cross);
        }

        ++totalMoves;

        // �������� ������ �������
        if (checkWin(board, CellType::Circle)) {
            displayBoard(board);
            std::cout << "����� 1 (������) �������!" << std::endl;
            break;
        }
        // �������� ������ ���������
        else if (checkWin(board, CellType::Cross)) {
            displayBoard(board);
            std::cout << "����� 2 (��������) �������!" << std::endl;
            break;
        }
        // �������� �����
        else if (totalMoves == boardSize * boardSize) {
            displayBoard(board);
            std::cout << "�����!" << std::endl;
            break;
        }
        // ����� ���� ������
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}

// ���� ������ ����������
void playAgainstComputer() {
    std::vector<std::vector<CellType>> board(boardSize, std::vector<CellType>(boardSize, CellType::Empty));
    int currentPlayer = 1;
    int totalMoves = 0;
    while (true) {
        std::cout << "������� ��������� ����:" << std::endl;
        displayBoard(board);

        if (currentPlayer == 1) {
            std::cout << "��� ��� (������)." << std::endl;
            makePlayerMove(board, CellType::Circle);
        }
        else {
            std::cout << "��� ���������� (��������)." << std::endl;
            makeComputerMove(board, CellType::Cross);
        }

        ++totalMoves;

        // �������� ������ �������
        if (checkWin(board, CellType::Circle)) {
            displayBoard(board);
            std::cout << "�� ��������!" << std::endl;
            break;
        }
        // �������� ������ ���������
        else if (checkWin(board, CellType::Cross)) {
            displayBoard(board);
            std::cout << "��������� �������!" << std::endl;
            break;
        }
        // �������� �����
        else if (totalMoves == boardSize * boardSize) {
            displayBoard(board);
            std::cout << "�����!" << std::endl;
            break;
        }
        // ����� ���� ������
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}