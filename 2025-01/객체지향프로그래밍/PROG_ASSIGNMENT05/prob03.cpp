#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

// 방향 벡터: 왼쪽(a), 오른쪽(f), 위(d), 아래(s)
const vector<pair<int, int>> directions = {
    {-1, 0}, // a
    {1, 0},  // f
    {0, -1}, // d
    {0, 1}   // s
};

class GameObject {
protected:
    int distance;
    int x, y;

public:
    GameObject(int startX, int startY, int distance) {
        this->x = startX;
        this->y = startY;
        this->distance = distance;
    }

    virtual ~GameObject() {};

    virtual void move() = 0;
    virtual char getShape() = 0;

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    bool collide(GameObject* p) {
        if (this->x == p->getX() && this->y == p->getY())
            return true;
        else
            return false;
    }
};

char userInput = ' ';

class Human : public GameObject {
public:
    Human(int x, int y) : GameObject(x, y, 1) {}

    void move() override {
        int dir = -1;

        if (userInput == 'a')
            dir = 0;

        else if (userInput == 'f')
            dir = 1;

        else if (userInput == 'd')
            dir = 2;

        else if (userInput == 's')
            dir = 3;

        if (dir != -1) {
            int nx = x + directions[dir].first * distance;
            int ny = y + directions[dir].second * distance;

            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                x = nx;
                y = ny;
            }

            else {
                throw runtime_error("잘못된 이동: 가장자리 너머로 이동할 수 없습니다.");
            }
        }
    }

    char getShape() override {
        return 'H';
    }
};

class Monster : public GameObject {
public:
    Monster(int x, int y) : GameObject(x, y, 2) {}

    void move() override {
        for (int i = 0; i < 4; ++i) {
            int dir = rand() % 4;
            int nx = x + directions[dir].first * distance;
            int ny = y + directions[dir].second * distance;

            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                x = nx;
                y = ny;

                break;
            }
        }
    }

    char getShape() override {
        return 'M';
    }
};

class Food : public GameObject {
public:
    Food(int x, int y) : GameObject(x, y, 1) {}

    void move() override {
        if (rand() % 5 < 3)
            return;

        for (int i = 0; i < 4; ++i) {
            int dir = rand() % 4;
            int nx = x + directions[dir].first * distance;
            int ny = y + directions[dir].second * distance;

            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                x = nx;
                y = ny;

                break;
            }
        }
    }

    char getShape() override {
        return '@';
    }
};

class Game {
    Human* human;
    Monster* monster;
    Food* food;

public:
    Game() {
        human = new Human(0, 0);
        monster = new Monster(WIDTH - 1, 0);
        food = new Food(WIDTH / 2, HEIGHT - 1);
    }

    ~Game() {
        delete human;
        delete monster;
        delete food;
    }

    void draw() {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (human->getX() == x && human->getY() == y)
                    cout << human->getShape();

                else if (monster->getX() == x && monster->getY() == y)
                    cout << monster->getShape();

                else if (food->getX() == x && food->getY() == y)
                    cout << food->getShape();

                else
                    cout << '-';
            }

            cout << endl;
        }
    }

    void play() {
        cout << "** Human의 Food 먹기 게임을 시작합니다. **\n";

        while (true) {
            draw();

            cout << "왼쪽(a), 아래(s), 위(d), 오른쪽(f) >> ";
            string input;
            getline(cin, input);
            userInput = input.empty() ? ' ' : input[0];

            try {
                human->move();
            }

            catch (const exception& e) {
                cout << e.what() << "\n";
                continue;
            }

            monster->move();
            food->move();

            if (human->collide(food)) {
                draw();
                cout << "성공! Human이 Food(@)를 먹었습니다.\n";
                break;
            }

            else if (monster->collide(human)) {
                draw();
                cout << "실패! Monster(M)가 Human(H)을 잡았습니다.\n";
                break;
            }

            else if (monster->collide(food)) {
                draw();
                cout << "실패! Monster(M)가 Food(@)를 먹었습니다.\n";
                break;
            }
        }
    }
};

int main() {
    srand((unsigned)time(0));
    Game game;
    game.play();
    return 0;
}