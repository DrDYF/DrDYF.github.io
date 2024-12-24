#include <iostream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>

int game[7], player[7];

void clear_screen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // Windows 系统
    #else
        system("clear"); // Linux 或 Mac 系统
    #endif
}

int main() {
    srand((unsigned int)time(NULL));  // 用当前时间初始化随机数生成器
    std::cout << "君子先" << std::endl;

    int used[34] = {0}, pused[36] = {0}, prize = 0;  // 用于标记已使用的号码

    // 随机生成 7 个彩票号码
    for (int i = 0; i < 7; i++) {
        int num;
        do {
            num = (i == 0) ? 1 + rand() % 16 : 1 + rand() % 33;  // 蓝球 1-16, 红球 1-33
        } while (used[num]);  // 确保不重复
        game[i] = num;
        used[num] = 1;  // 标记该号码已经使用
    }

    // 获取用户输入的 7 个号码
    for (int i = 0; i < 7; i++) {
        int num;
        while (true) {
            std::cout << "[" << i + 1 << "/7]" << (i == 0 ? "蓝色球：" : "红色球：");
            std::cin >> num;

            if (i == 0 && num >= 1 && num <= 12) {  // 蓝球号码检查 (1-12)
                player[i] = num;
                break;
            } else if (i > 0 && num >= 1 && num <= 35) {  // 红球号码检查 (1-35)
                if (pused[num] == 0) {
                    player[i] = num;
                    pused[num] = 1;  // 标记该号码已经使用
                    break;
                } else {
                    std::cout << "重复啦" << std::endl;
                }
            } else {
                std::cout << "输错啦" << std::endl;
            }
        }
    }

    // 睡眠 1.5 秒后清屏
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    clear_screen();
    std::cout << "开奖啦！" << std::endl;

    // 显示红色球的开奖结果
    for (int i = 6; i >= 1; i--) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        std::cout << "红色球" << i << ": " << game[i] << std::endl;
    }

    // 显示蓝色球结果
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "激动人心的时刻到了！" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::cout << "蓝色球:" << game[0] << " !" << std::endl;

    int matchCount = 0;
    for (int i = 1; i < 7; i++) {
        for (int j = 1; j < 7; j++) {
            if (player[i] == game[j]) {
                matchCount++;
                break;
            }
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1400));
    std::cout << "你的嘞:" << std::endl;

    // 显示玩家的号码
    for (int i = 0; i < 7; i++) {
        std::cout << (i == 0 ? "蓝色球" : "红色球") << ":" << player[i] << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    // 判断是否中奖
    int Blue = (game[0] == player[0]);
    if (Blue) {
        switch (Blue + matchCount) {
            case 1: prize = 5; break;
            case 4: prize = 10; break;
            case 5: prize = 200; break;
            case 6: prize = 3000; break;
            case 7: prize = 10000000; break;
        }
    } else {
        switch (matchCount) {
            case 4: prize = 10; break;
            case 5: prize = 200; break;
            case 6: prize = 3000; break;
            case 7: prize = 5000000; break;
        }
    }

    std::cout << "中辣！" << prize << "Q" << std::endl;
    return 0;
}