#include <iostream>
#include <cstdlib>
#include <time.h> 
#include <stdlib.h>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

const int N = 13;           // Кол-во слов (нужно для словаря и проверки скорости).
const int MAX_LEN = 255;    // Макс. длинна строки
const float secs = 10;      // Ожидание 60 секунд перед концом цикла
const float delay = secs * CLOCKS_PER_SEC; // Вычисление задержки через константу CLOCK_PER_SEC, которая содержит в себе количество системных едениц времени в секунду.

string chooseStart;

char word[N] = "";          // Вводимое слово

int chooseMenu;             // Переменная для хранения выбора в меню
int random;                 // Рандомайзер
int rightwrittedWords = 0;  // Счётчик слов которые введены верно

float typingSpeed = -1;
float newTypingSpeed = -1;

bool isNewSpeedTest = true;

 const char* const DICTONARY[N]= {      // Словарь слов которые будут использованны в проверке скорости.
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



#pragma region Useful and system functions

void clearScreen()      // Функция для очистки консоли
{
    system("cls");
} 

int countLinesInFile()  // Функция для подсчёта кол-ва строк в файле (возможном словаре слов)
{
    char* str = new char[1024];
    int i = 0;
    ifstream base("dict.txt");
    while (!base.eof()) // Будет работать пока файл открыт
    {
        base.getline(str, 1024, '\n');
        i++;
    }
    base.close();
    delete str;
    cout << i << '\n';
    return i;
}

/*
int readFile() // Открытие словаря и добавления каждого слова в словарь. Работает с библеотекой fstream TODO: Доделать
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

        const int N = 46000;
        char* DICTONARY[N];
        
        while (!filein.eof())
        {
            currentString = "";
            getline(filein, currentString);
            char currentChar;

            
        
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < currentString.length(); j++)
                {
                    currentChar = currentString[j];
                    DICTONARY[i] += currentChar;
                }

                

            }
            
        }
        filein.close();
        cout << DICTONARY[1];
    }

    return 0;
}
*/

#pragma endregion



#pragma region Main logic of program

void checkSpeed()    // Функция проверки скорости набора
{
    
    clock_t start = clock();    // Таймер, запоминание времени с момента запуска функции

    while (clock() - start < delay) {               
        random = rand() % N;                        //Случайное число, индекс
        cout << "Please write : \t" << DICTONARY[random] << '\n';   // Вывод : какое слово нам надо ввести
        cin.getline(word, MAX_LEN);
        if (strcmp(word, DICTONARY[random]) == 0) {
            rightwrittedWords++;                    //Если слова введены верно, наращиваем счётчик
            cout << rightwrittedWords << '\n';
        }
    }

    // Итоги

    cout << "\nCorrectly writted : " << rightwrittedWords;
    cout << "\nCount of words : " << N;
    cout << "\nYour speed " << rightwrittedWords / secs << " words per minute \n";
    
    

}

#pragma endregion



#pragma region Menu

void menu();

void menuChecker()      // Функция для проверки выбора в меню программы. Выполненна через switch case. Какую цифру пользователь введёт, в такой пункт меню и попадёт
                        // Реализованно за счёт получения цифры в переменную.
{
    switch (chooseMenu)
    {
    case 1:
        checkSpeed();
        menu();
        break;
    case 2:
        cout << "1";
        menu();
        break;
    case 3:
        cout << "2";
        menu();
        break;
    case 4:
        system("exit");
    }
}

void menu()
{
    std::cout << "\n";
    std::cout << "1. Check your speed" << "\n";
    std::cout << "2. Train symbols" << "\n";
    std::cout << "3. Clear screen" << "\n";
    std::cout << "4. Exit" << "\n";
    std::cin >> chooseMenu;
    menuChecker();
    std::cout << "\n";
}

#pragma endregion



int main()
{

    // Приветстиве

    std::cout << "Welcome to Keyboard Training\n";  
    std::cout << "Are you ready? (Write YES or NO)\n";

    // Проверка : готов ли пользователь начать использование
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

    std::cout << "Welcome! Lets check your speed for the first time \n";
    checkSpeed();
    isNewSpeedTest = false;
    
    

    std::cout << "Good job! Welcome to the program \n";
    std::cout << "\n";
    menu();

    

}

