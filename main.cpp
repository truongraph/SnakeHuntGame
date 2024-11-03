#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

//======================================
// Kích thước của bàn cờ
//======================================
const int width = 40;
const int height = 15;

//======================================
// Các biến toàn cục
//======================================
int x, y, fruitX, fruitY, score;
vector<pair<int, int>> snake; // Vecto chứa vị trí của rắn
char direction; // Hướng di chuyển của rắn
bool gameOver;

//======================================
// Hàm vẽ bàn cờ và rắn
//======================================
void Draw(HANDLE hConsole, const string& playerName) {
    COORD coord;
    coord.X = 0; coord.Y = 0; // Bắt đầu từ tọa độ (0, 0)
    SetConsoleCursorPosition(hConsole, coord); // Đặt con trỏ tới vị trí bắt đầu

    // Vẽ tiêu đề lớn
    cout << "  ____  _   _    _    _  _______ " << endl;
    cout << " / ___|| \\ | |  / \\  | |/ / ____|" << endl;
    cout << " \\___ \\|  \\| | / _ \\ | ' /|  _|  " << endl;
    cout << "  ___) | |\\  |/ ___ \\| . \\| |___ " << endl;
    cout << " |____/|_| \\_/_/   \\_\\_|\\_\\_____|" << endl;
     cout << endl;
    cout << "Wellcome : " << playerName << endl; // Hiển thị tên người chơi
    cout << "Score : " << score << endl; // Hiện điểm
    // Vẽ viền
    for (int i = 0; i < width + 2; i++) cout << "=";
    cout << endl;
    // Vẽ thân rắn
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "|"; // Biên trái

            if (i == y && j == x) {
                cout << "O"; // Vẽ đầu rắn
            } else if (i == fruitY && j == fruitX) {
                cout << "*"; // Vẽ trái cây
            } else {
                bool isSnakeBody = false;
                for (const auto& s : snake) {
                    if (s.first == j && s.second == i) {
                        cout << "o"; // Vẽ thân rắn
                        isSnakeBody = true;
                        break;
                    }
                }
                if (!isSnakeBody) cout << " "; // Ô trống
            }

            if (j == width - 1) cout << "|"; // Biên phải
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "="; // Biên dưới
    cout << endl;
    cout << "Guide:" << endl;
    cout << "- Press A,W,S,D to move the snake" << endl;
    cout << "- Press (x) to stop the game" << endl;
}

//======================================
// Hàm thiết lập trò chơi
//======================================
void Setup() {
    gameOver = false;
    direction = ' '; // Khởi tạo hướng di chuyển
    x = width / 2; // Khởi tạo vị trí đầu rắn
    y = height / 2;
    fruitX = rand() % width; // Vị trí trái cây
    fruitY = rand() % height;
    score = 0;
    snake.push_back(make_pair(x, y)); // Đầu rắn
}

// Hàm xử lý đầu vào
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            direction = 'L'; break; // Trái
        case 'd':
            direction = 'R'; break; // Phải
        case 'w':
            direction = 'U'; break; // Lên
        case 's':
            direction = 'D'; break; // Xuống
        case 'x':
            gameOver = true; break; // Thoát game
        }
    }
}

//======================================
// Hàm cập nhật trạng thái
//======================================
void Logic() {
    int prevX = snake[0].first;
    int prevY = snake[0].second;
    int prev2X, prev2Y;
    snake[0].first = x;
    snake[0].second = y;

    for (size_t i = 1; i < snake.size(); i++) {
        prev2X = snake[i].first;
        prev2Y = snake[i].second;
        snake[i].first = prevX;
        snake[i].second = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction) {
    case 'L': x--; break;
    case 'R': x++; break;
    case 'U': y--; break;
    case 'D': y++; break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[i].first == x && snake[i].second == y) gameOver = true; // Tự đâm vào
    }

    if (x == fruitX && y == fruitY) {
        score += 10; // Tăng điểm
        fruitX = rand() % width; // Vị trí mới cho trái cây
        fruitY = rand() % height;
        snake.push_back(make_pair(-1, -1)); // Thêm thân rắn
    }
}

//======================================
// Hàm nhập tên và bắt đầu game
//======================================
void StartGame(string &playerName) {
    cout << "=====================================" << endl;
    cout << "       TTM - SNAKE HUNT GAME    " << endl;
    cout << "=====================================" << endl;
    cout << endl;
    cout << "  ____  _   _    _    _  _______ " << endl;
    cout << " / ___|| \\ | |  / \\  | |/ / ____|" << endl;
    cout << " \\___ \\|  \\| | / _ \\ | ' /|  _|  " << endl;
    cout << "  ___) | |\\  |/ ___ \\| . \\| |___ " << endl;
    cout << " |____/|_| \\_/_/   \\_\\_|\\_\\_____|" << endl;
    cout << endl;
    cout << "Member of team: " << endl;
    cout << "1. Vo Dang Truong - MSSV 24730075 " << endl;
    cout << "2. Do Ngoc Minh Tien - MSSV 24730070" << endl;
    cout << "3. Ly Duc Minh - MSSV 24730045" << endl;
    cout << endl;
    cout << "Loading... ";
    for (int i = 1; i <= 100; i++) {
        Sleep(10);
        cout << "=";
    }
    cout << " 100%" << endl;
    cout << endl;
    cout << "Enter your name and press (ENTER) to start playing: ";
    getline(cin, playerName);
    system("cls"); // Xóa màn hình
}

//======================================
// Hàm ẩn con trỏ
//======================================
void HideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; // Ẩn con trỏ
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

//======================================
// Hàm chính
//======================================
int main() {
    HideCursor(); // Ẩn con trỏ
    string playerName;
    StartGame(playerName); // Màn hình chọn bắt đầu game
    Setup(); // Khởi tạo trò chơi

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Lấy thông tin console
    while (!gameOver) {
        Draw(hConsole, playerName); // Vẽ trò chơi
        Input(); // Nhận đầu vào
        Logic(); // Cập nhật trạng thái
        Sleep(110); // Tốc độ di chuyển
    }
    cout << endl;
    cout << "=====================================" << endl;
    cout << "   GAME OVER.!!!             " << endl;
    cout << "=====================================" << endl;
    cout << "   YOUR SCORE IS :" << score << endl;
    cout << "=====================================" << endl;
    return 0;
}
