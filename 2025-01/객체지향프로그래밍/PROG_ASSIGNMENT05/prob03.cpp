#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

// ���� ����: ����(a), ������(f), ��(d), �Ʒ�(s)
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
                throw runtime_error("�߸��� �̵�: �����ڸ� �ʸӷ� �̵��� �� �����ϴ�.");
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
        cout << "** Human�� Food �Ա� ������ �����մϴ�. **\n";

        while (true) {
            draw();

            cout << "����(a), �Ʒ�(s), ��(d), ������(f) >> ";
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
                cout << "����! Human�� Food(@)�� �Ծ����ϴ�.\n";
                break;
            }

            else if (monster->collide(human)) {
                draw();
                cout << "����! Monster(M)�� Human(H)�� ��ҽ��ϴ�.\n";
                break;
            }

            else if (monster->collide(food)) {
                draw();
                cout << "����! Monster(M)�� Food(@)�� �Ծ����ϴ�.\n";
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