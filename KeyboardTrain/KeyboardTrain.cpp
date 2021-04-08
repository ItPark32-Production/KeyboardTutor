#include <iostream>
#include <cstdlib>
#include <time.h> 
#include <stdlib.h>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

const int DICT_SIZE_WORDS = 13;           // Кол-во слов (нужно для словаря и проверки скорости).
const int DICT_SIZE_SYMBOLS = 12;           // Кол-во символов (нужно для словаря и проверки скорости).
const int MAX_LEN = 255;    // Макс. длинна строки
const float secs = 10;      // Ожидание 60 секунд перед концом цикла
const float delay = secs * CLOCKS_PER_SEC; // Вычисление задержки через константу CLOCK_PER_SEC, которая содержит в себе количество системных едениц времени в секунду.

string chooseStart;

char word[DICT_SIZE_WORDS] = "";          // Вводимое слово
char symbol[DICT_SIZE_SYMBOLS] = "";          // Вводимый символ

int chooseMenu;             // Переменная для хранения выбора в меню
int random;                 // Рандомайзер
int randomSymbol;
int rightwrittedWords = 0;  // Счётчик слов которые введены верно
int profitPercent = 0;      // На сколько процентов улучшена скорость.

int rightwrittedSymbols = 0;  // Счётчик символов которые введены верно
int profitPercentSymbols = 0;      // На сколько процентов улучшена скорость.

float typingSpeed = 0;
float newTypingSpeed = 0;
float typingSpeedSymbols = 0;
float newTypingSpeedSymbols = 0;

bool isNewSpeedTest = true;

 const char* const DICTONARY_OF_WORDS[DICT_SIZE_WORDS]= {      // Словарь слов которые будут использованны в проверке скорости.
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

 const char* const DICTONARY_OF_SYMBOLS[DICT_SIZE_SYMBOLS] = {      // Символы слов которые будут использованны в проверке скорости.
    "!",
    "@",
    "#",
    "$",
    "%",
    "^",
    "*",
    "(",
    ")",
    "|",
    ".",
    "`",
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

void checkSpeedWords()    // Функция проверки скорости набора
{

    srand(time(0));
    
    rightwrittedWords = 0; // Обнуляем счётчик

    clock_t start = clock();    // Таймер, запоминание времени с момента запуска функции

    while (clock() - start < delay) {               
        random = rand() % DICT_SIZE_WORDS;                        //Случайное число, индекс
        cout << "Please write : \t" << DICTONARY_OF_WORDS[random] << '\n';   // Вывод : какое слово нам надо ввести
        cin.getline(word, MAX_LEN);
        if (strcmp(word, DICTONARY_OF_WORDS[random]) == 0) {
            rightwrittedWords++;                    //Если слова введены верно, наращиваем счётчик
            cout << "\n";
            cout << "Count of correctly writted words : " << rightwrittedWords << '\n';
            cout << "\n";
        }
    }

    // Итоги

    newTypingSpeed = rightwrittedWords / secs;

    cout << "\nCorrectly writted : " << rightwrittedWords;
    cout << "\nCount of words : " << DICT_SIZE_WORDS;
    cout << "\nYour speed " << newTypingSpeed << " words per minute";
    if (typingSpeed != 0)
    {
        if (newTypingSpeed > typingSpeed)
        {
            float newPercent = (100 * newTypingSpeed) / typingSpeed;
            profitPercent = newPercent - 100;   
            cout << "\nNew record! You're improved your speed by " << profitPercent << " %\n";
            typingSpeed = newTypingSpeed;
        }
    }
    else
    {
        typingSpeed = newTypingSpeed;
    }

}

void checkSpeedSymbols()    // Функция проверки скорости набора
{

    srand(time(0));

    rightwrittedSymbols = 0; // Обнуляем счётчик

    clock_t start = clock();    // Таймер, запоминание времени с момента запуска функции

    while (clock() - start < delay) {
        randomSymbol = rand() % DICT_SIZE_SYMBOLS;                        //Случайное число, индекс
        cout << "Please write : \t" << DICT_SIZE_SYMBOLS[randomSymbol] << '\n';   // Вывод : какое слово нам надо ввести
        cin.getline(word, MAX_LEN);
        if (strcmp(word, DICT_SIZE_SYMBOLS[randomSymbol]) == 0) {
            rightwrittedWords++;                    //Если слова введены верно, наращиваем счётчик
            cout << "\n";
            cout << "Count of correctly writted symbols : " << rightwrittedSymbols << '\n';
            cout << "\n";
        }
    }

    // Итоги

    newTypingSpeedSymbols = rightwrittedSymbols / secs;

    cout << "\nCorrectly writted : " << rightwrittedSymbols;
    cout << "\nCount of symbols : " << DICT_SIZE_SYMBOLS;
    cout << "\nYour speed " << newTypingSpeedSymbols << " symbols per minute";
    if (typingSpeed != 0)
    {
        if (newTypingSpeed > typingSpeed)
        {
            float newPercent = (100 * newTypingSpeed) / typingSpeed;
            profitPercentSymbols = newPercent - 100;
            cout << "\nNew record! You're improved your speed by " << profitPercent << " %\n";
            typingSpeedSymbols = newTypingSpeedSymbols;
        }
    }
    else
    {
        typingSpeed = newTypingSpeed;
    }
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
        checkSpeedWords();
        menu();
        break;
    case 2:
        cout << "1";
        menu();
        break;
    case 3:
        cout << "2";
        clearScreen();
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

    std::cout << "Lets check your speed for the first time \n";
    checkSpeedWords();

    isNewSpeedTest = false;

    std::cout << "Are you want to continue? (Write YES or NO)\n";

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

    std::cout << "Good job! Welcome to the program \n";
    std::cout << "\n";
    menu();
    
    
    

    

}

