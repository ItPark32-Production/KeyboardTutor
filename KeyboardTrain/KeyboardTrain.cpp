#include <iostream>
#include <cstdlib>
#include <time.h> 
#include <stdlib.h>
#include <string>
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

int random;  
int score = 0;          // Счётчик слов которые введены верно
const float secs = 20;  // Ожидание 20 секунд перед концом цикла
char word[N] = "";      // Вводимое слово

const float delay = secs * CLOCKS_PER_SEC; // Вычисление задержки через константу CLOCK_PER_SEC



#pragma region Useful and system functions

void clearScreen()      // Функция для очистки консоли
{
    system("cls");
} 

int countLinesInFile()
{
    char* str = new char[1024];
    int i = 0;
    ifstream base("dict.txt");
    while (!base.eof())
    {
        base.getline(str, 1024, '\n');
        i++;
    }
    base.close();
    delete str;
    cout << i << '\n';
    return i;
}

int readFile()
{
    string path = "dict.txt";
    
    ifstream filein;
    filein.open(path);

    if (!filein.is_open())
    {
        cout << "Cant open dictionary";
    }
    else
    {
        cout << "Opened";
        string currentString;
        while (!filein.eof())
        {
            currentString = "";
            getline(filein, currentString);
            cout << currentString << endl;
        }
        
    }
    filein.close();

    return 0;
}

#pragma endregion



#pragma region Main logic of program

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

#pragma endregion



#pragma region Menu

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

#pragma endregion



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

