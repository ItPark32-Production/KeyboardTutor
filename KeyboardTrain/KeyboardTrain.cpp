#include <iostream>
#include <cstdlib>
#include <time.h> 
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <conio.h>

using namespace std;

string chooseStart;
int chooseMenu;
float typingSpeed = -1;
float newTypingSpeed = -1;
bool isNewSpeedTest = true;

const int N = 13;           // Кол-во слов (нужно для словаря и проверки скорости).
const int MAX_LEN = 255;    // Макс. длинна строки

const char* const DICTONARY[N] = {      // Словарь слов которые будут использованны в проверке скорости.
    "University",
    "Book",
    "Test",
    "Coding",
    "Programming",
    "Queen",
    "Beat",
    "City",
    "School",
    "Thing",
    "Snake",
    "Sharp",
    "Read"
};

int random;             //переменная для случайного выбора.
int score = 0;          //счётчик верно введённых слов
const float secs = 20;  //будем ждать 60 секунд
char word[N] = "";      //вводимое слово

const float delay = secs * CLOCKS_PER_SEC;

void clearScreen()      // Функция для очистки консоли
{
    system("cls");
} 

void menuChecker()      // Функция для проверки выбора в меню программы. Выполненна через switch case. Какую цифру пользователь введёт, в такой пункт меню и попадёт
                        // Реализованно за счёт получения цифры в переменную.
{
    switch (chooseMenu)
    {
    case 1:
        cout << "1";
    case 2:
        cout << "1";
    case 3:
        cout << "2";
    }
}

void menu()
{
    clearScreen();

    std::cout << "1. Check your speed" << "\n";
    std::cout << "2. Train symbols" << "\n";
    std::cout << "3. Exit" << "\n";
    std::cin >> chooseMenu;
    menuChecker();
}


void checkSpeed()    // Функция проверки скорости набора
{
    clock_t start = clock();

    while (clock() - start < delay) {
        random = rand() % N;                        //  Случайное число, индекс
        cout << "input word:\t " << DICTONARY[random] << '\n';
        cin.getline(word, MAX_LEN);
        if (strcmp(word, DICTONARY[random]) == 0) {
            score++;                               //   Если слова введены верно, наращиваем счётчик
            cout << score << '\n';
        }
    }

    cout << "\nCorrectly writted : " << score;
    cout << "\nCount of words" << N;
    if (newTypingSpeed == -1)
    {
        typingSpeed = N / secs;
    }
    else
    {
        newTypingSpeed = N / secs;
    }
}

int main()
{
    std::cout << "Welcome to Keyboard Training\n";
    std::cout << "Are you ready? (Write YES or NO)\n";
    for (; ; )
    {
        std::cin >> chooseStart;
        if (chooseStart == "NO")
        {
            return -1;
        }
        else if (chooseStart == "YES")
        {
            break;
        }
        else
        {
            std::cout << "Write YES or NO\n";
            continue;
        }
    }

    std::cout << "Welcome! Lets check your speed for the first time";
    checkSpeed();
    isNewSpeedTest = false;

    std::cout << "Good job! Welcome to the program";
    menu();

}

