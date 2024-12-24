#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>  // 用于 memcpy 和 memcmp 函数
#include <iomanip>  // 用于 std::setw 和 std::left

#define SIZE 4
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

int grid[SIZE][SIZE] = {0}; // 游戏的网格
int score = 0; // 当前得分

void initialize(); // 初始化
void add_random_tile(); // 添加随机方块
void draw_grid(); // 绘制网格
void compress(int grid[SIZE][SIZE]); // 压缩网格
int merge(int grid[SIZE][SIZE]); // 合并网格
void move(int direction); // 移动数字
int can_move(); // 判断是否可以移动
int game_won(); // 判断是否赢得游戏
void clear_screen(); // 清空屏幕

int main() {
    char command;
    initialize();
    while (true) {
        clear_screen();
        draw_grid();
        std::cout << "得分: " << score << std::endl;
        if (game_won()) {
            std::cout << "你赢了！" << std::endl;
            break;
        }
        if (!can_move()) {
            std::cout << "游戏结束！" << std::endl;
            break;
        }
        command = std::cin.get(); // 使用 std::cin.get() 来代替 _getch()
        switch (command) {
        case UP:
            move(UP);
            break;
        case DOWN:
            move(DOWN);
            break;
        case LEFT:
            move(LEFT);
            break;
        case RIGHT:
            move(RIGHT);
            break;
        }
    }
    return 0;
}

void initialize() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    add_random_tile();
    add_random_tile();
}

void add_random_tile() {
    int empty_tiles[SIZE * SIZE][2];
    int count = 0;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (grid[i][j] == 0) {
                empty_tiles[count][0] = i;
                empty_tiles[count][1] = j;
                count++;
            }

    if (count > 0) {
        int rand_index = std::rand() % count;
        grid[empty_tiles[rand_index][0]][empty_tiles[rand_index][1]] = (std::rand() % 2 + 1) * 2;
    }
}

void draw_grid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0)
                std::cout << "   .   ";
            else
                std::cout << "  " << std::setw(4) << std::left << grid[i][j];
        }
        std::cout << std::endl;
    }
}

void compress(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        int pos = 0;
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] != 0) {
                grid[i][pos++] = grid[i][j];
            }
        }
        for (int j = pos; j < SIZE; j++) {
            grid[i][j] = 0; // 清空未填充的方块
        }
    }
}

int merge(int grid[SIZE][SIZE]) {
    int moved = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i][j + 1]) {
                grid[i][j] *= 2;
                score += grid[i][j];
                grid[i][j + 1] = 0;
                moved = 1;
            }
        }
    }
    return moved; // 返回合并是否发生
}

void move(int direction) {
    int original_grid[SIZE][SIZE];
    std::memcpy(original_grid, grid, sizeof(original_grid)); // 记录原始网格

    if (direction == UP || direction == DOWN) {
        for (int j = 0; j < SIZE; j++) {
            int temp[SIZE] = {0};
            int pos = 0;

            if (direction == UP) {
                for (int i = 0; i < SIZE; i++) {
                    if (grid[i][j] != 0) {
                        temp[pos++] = grid[i][j];
                    }
                }
            } else {
                for (int i = SIZE - 1; i >= 0; i--) {
                    if (grid[i][j] != 0) {
                        temp[pos++] = grid[i][j];
                    }
                }
            }

            merge(temp); // 合并计数

            if (direction == UP) {
                for (int i = 0; i < SIZE; i++) {
                    if (i < pos) grid[i][j] = temp[i];
                    else grid[i][j] = 0;
                }
            } else {
                for (int i = 0; i < SIZE; i++) {
                    if (i < pos) grid[SIZE - 1 - i][j] = temp[i];
                    else grid[SIZE - 1 - i][j] = 0;
                }
            }
        }

    } else if (direction == LEFT || direction == RIGHT) {
        for (int i = 0; i < SIZE; i++) {
            int temp[SIZE] = {0};
            int pos = 0;

            if (direction == LEFT) {
                for (int j = 0; j < SIZE; j++) {
                    if (grid[i][j] != 0) {
                        temp[pos++] = grid[i][j];
                    }
                }
            } else {
                for (int j = SIZE - 1; j >= 0; j--) {
                    if (grid[i][j] != 0) {
                        temp[pos++] = grid[i][j];
                    }
                }
            }

            merge(temp); // 合并计数

            if (direction == LEFT) {
                for (int j = 0; j < SIZE; j++) {
                    if (j < pos) grid[i][j] = temp[j];
                    else grid[i][j] = 0;
                }
            } else {
                for (int j = 0; j < SIZE; j++) {
                    if (j < pos) grid[i][SIZE - 1 - j] = temp[j];
                    else grid[i][SIZE - 1 - j] = 0;
                }
            }
        }
    }

    // 检查是否有变化
    if (std::memcmp(original_grid, grid, sizeof(original_grid)) != 0) add_random_tile(); // 只有在变化时添加新方块
}

int can_move() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0 || (j < SIZE - 1 && grid[i][j] == grid[i][j + 1]) || (i < SIZE - 1 && grid[i][j] == grid[i + 1][j])) return 1;
        }
    }
    return 0;
}

int game_won() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (grid[i][j] == 2048)
                return 1;
    return 0;
}

void clear_screen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // Windows 系统
    #else
        system("clear"); // Linux 或 Mac 系统
    #endif
}