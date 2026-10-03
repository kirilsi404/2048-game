#include <iostream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// Пресмята base на степен exp (целочислено степенуване)
int power(int base, int exp) {
    int res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

// Разменя стойностите на две цели числа
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Заделя динамично двумерен масив (дъска) с размер size x size, запълнен с нули
int** createBoard(int size) {
    int** board = new int*[size];
    for (int i = 0; i < size; i++) {
        board[i] = new int[size]();
    }
    return board;
}

// Освобождава динамичната памет, заета от дъската
void freeBoard(int** board, int size) {
    if (!board) return;
    for (int i = 0; i < size; i++) {
        delete[] board[i];
    }
    delete[] board;
}

// Изчиства екрана на конзолата според операционната система
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Извежда текущото състояние на дъската, форматирано в колони
void printBoard(int** board, int size) {
    std::cout << "\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                std::cout << std::setw(6) << ".";
            } else {
                std::cout << std::setw(6) << board[i][j];
            }
        }
        std::cout << "\n\n";
    }
}

// Сбутва всички ненулеви плочки максимално наляво без да ги слива
void moveLeft(int** board, int size) {
    for (int i = 0; i < size; i++) {
        int index = 0;
        for (int j = 0; j < size; j++) {
            if (board[i][j] != 0) {
                swap(board[i][j], board[i][index]);
                index++;
            }
        }
    }
}

// Изпълнява пълен ход наляво: сбутване, сливане на съседни равни плочки и повторно сбутване
void left(int** board, int size) {
    moveLeft(board, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                board[i][j] *= 2;
                board[i][j + 1] = 0;
            }
        }
    }
    moveLeft(board, size);
}

// Сбутва всички ненулеви плочки максимално надясно без да ги слива
void moveRight(int** board, int size) {
    for (int i = 0; i < size; i++) {
        int index = size - 1;
        for (int j = size - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                swap(board[i][j], board[i][index]);
                index--;
            }
        }
    }
}

// Изпълнява пълен ход надясно: сбутване, сливане на съседни равни плочки и повторно сбутване
void right(int** board, int size) {
    moveRight(board, size);
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j > 0; j--) {
            if (board[i][j] != 0 && board[i][j] == board[i][j - 1]) {
                board[i][j] *= 2;
                board[i][j - 1] = 0;
            }
        }
    }
    moveRight(board, size);
}

// Сбутва всички ненулеви плочки максимално нагоре без да ги слива
void moveUp(int** board, int size) {
    for (int j = 0; j < size; j++) {
        int index = 0;
        for (int i = 0; i < size; i++) {
            if (board[i][j] != 0) {
                swap(board[i][j], board[index][j]);
                index++;
            }
        }
    }
}

// Изпълнява пълен ход нагоре: сбутване, сливане на съседни равни плочки и повторно сбутване
void up(int** board, int size) {
    moveUp(board, size);
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size - 1; i++) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j]) {
                board[i][j] *= 2;
                board[i + 1][j] = 0;
            }
        }
    }
    moveUp(board, size);
}

// Сбутва всички ненулеви плочки максимално надолу без да ги слива
void moveDown(int** board, int size) {
    for (int j = 0; j < size; j++) {
        int index = size - 1;
        for (int i = size - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                swap(board[i][j], board[index][j]);
                index--;
            }
        }
    }
}

// Изпълнява пълен ход надолу: сбутване, сливане на съседни равни плочки и повторно сбутване
void down(int** board, int size) {
    moveDown(board, size);
    for (int j = 0; j < size; j++) {
        for (int i = size - 1; i > 0; i--) {
            if (board[i][j] != 0 && board[i][j] == board[i - 1][j]) {
                board[i][j] *= 2;
                board[i - 1][j] = 0;
            }
        }
    }
    moveDown(board, size);
}

// Проверява дали играчът е достигнал или надминал целевата плочка (2^winCondition)
bool hasWon(int** board, int winCondition, int size) {
    int targetValue = power(2, winCondition);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] >= targetValue) return true;
        }
    }
    return false;
}

// Проверява дали има поне един възможен ход (свободна клетка или съседни равни плочки)
bool hasAvailableMoves(int** board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) return true;
            if (j + 1 < size && board[i][j] == board[i][j + 1]) return true;
            if (i + 1 < size && board[i][j] == board[i + 1][j]) return true;
        }
    }
    return false;
}

// Сравнява две дъски клетка по клетка и връща true, ако са напълно идентични
bool boardsAreEqual(int** a, int** b, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

// Копира състоянието на дъската src в dest
void copyBoard(int** src, int** dest, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

// Поставя ново число (2 с 90% шанс или 4 с 10% шанс) на случайна свободна позиция
void generateRandomNumber(int** board, int size) {
    int emptyCells = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) emptyCells++;
        }
    }
    if (emptyCells == 0) return;

    int targetIndex = rand() % emptyCells;
    int current = 0;
    int randomNum = (rand() % 100 < 90) ? 2 : 4;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                if (current == targetIndex) {
                    board[i][j] = randomNum;
                    return;
                }
                current++;
            }
        }
    }
}

// Извиква съответната функция за преместване според натиснатия клавиш
void applyMove(int** board, int size, char position) {
    switch (position) {
        case 'a': case 'A': left(board, size); break;
        case 'd': case 'D': right(board, size); break;
        case 'w': case 'W': up(board, size); break;
        case 's': case 'S': down(board, size); break;
        default: break;
    }
}

// Управлява основния игрови цикъл (ход, проверка за край, генериране на плочки)
void startGame(int size, int winCondition) {
    int** board = createBoard(size);
    int** prevBoard = createBoard(size);

    generateRandomNumber(board, size);
    generateRandomNumber(board, size);

    while (true) {
        clearScreen();
        printBoard(board, size);

        if (hasWon(board, winCondition, size)) {
            std::cout << "Congratulations, you won!\n";
            break;
        }

        if (!hasAvailableMoves(board, size)) {
            std::cout << "Game Over! No more valid moves.\n";
            break;
        }

        std::cout << "Move (W/A/S/D) or Q to quit: ";
        char move;
        std::cin >> move;

        if (move == 'q' || move == 'Q') {
            std::cout << "Game exited.\n";
            break;
        }

        copyBoard(board, prevBoard, size);
        applyMove(board, size, move);

        // Ново число се появява само ако дъската действително се е променила
        if (!boardsAreEqual(board, prevBoard, size)) {
            generateRandomNumber(board, size);
        }
    }

    freeBoard(board, size);
    freeBoard(prevBoard, size);
}

// Чете и валидира потребителските настройки за размер и целева плочка
void settings(int& size, int& winCondition) {
    std::cout << "Enter board size (3-10): ";
    std::cin >> size;
    while (size < 3 || size > 10) {
        std::cout << "Invalid size, enter between 3 and 10: ";
        std::cin >> size;
    }

    std::cout << "Enter target power of 2 (e.g., 11 for 2048): ";
    std::cin >> winCondition;
    while (winCondition < 4 || winCondition > 20) {
        std::cout << "Invalid power, enter between 4 and 20: ";
        std::cin >> winCondition;
    }

    startGame(size, winCondition);
}

// Извежда главното меню и обработва избора на потребителя
void startingMenu() {
    int size = 4;
    int winCondition = 11;
    int option;

    std::cout << "1. Start game\n";
    std::cout << "2. Settings\n";
    std::cout << "3. Quit\n";
    std::cout << "Choice: ";
    std::cin >> option;

    switch (option) {
        case 1: startGame(size, winCondition); break;
        case 2: settings(size, winCondition); break;
        case 3: std::cout << "Goodbye!\n"; break;
        default: std::cout << "Invalid option!\n"; break;
    }
}

// Входна точка на програмата: инициализира генератора на случайни числа и стартира менюто
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    startingMenu();
    return 0;
}