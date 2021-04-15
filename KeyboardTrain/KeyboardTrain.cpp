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

char symbol[DICT_SIZE_SYMBOLS] = "";          // Вводимый символ

int chooseMenu = 0;             // Переменная для хранения выбора в меню
int random = 0;                 // Рандомайзер
int randomSymbol = 0;
int rightwrittedWords = 0;  // Счётчик слов которые введены верно
int profitPercent = 0;      // На сколько процентов улучшена скорость.

int rightwrittedSymbols = 0;  // Счётчик символов которые введены верно
int profitPercentSymbols = 0;      // На сколько процентов улучшена скорость.

float typingSpeed = 0;
float newTypingSpeed = 0;
float typingSpeedSymbols = 0;
float newTypingSpeedSymbols = 0;

bool isNewSpeedTest = true;

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
    "`",
    "."
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


string readFile() // Открытие словаря и добавления каждого слова в словарь. Работает с библеотекой fstream TODO: Доделать
{
    string path = "dict.txt";
     string currentString;
    
    ifstream filein;
    filein.open(path);

    if (!filein.is_open())
    {
        cout << "Cant open directory";
    }
    else
    {
        const int N = 46000;
        random = rand() % N;
        for (int i = 0; i < random; i++)
        {
            getline(filein, currentString);
        }

    }
    filein.close();

    return currentString;
}


#pragma endregion



#pragma region Main logic of program

void checkSpeedWords()    // Функция проверки скорости набора
{

    srand(time(0));
    
    rightwrittedWords = 0; // Обнуляем счётчик

    clock_t start = clock();    // Таймер, запоминание времени с момента запуска функции

    while (clock() - start < delay) {               
        random = rand() % DICT_SIZE_WORDS;                        // Случайное число, индекс
        string currentWord = readFile();
        string inputWord;
        clearScreen();
        cout << "Count of correctly writted words : " << rightwrittedWords << '\n'; 
        cout << "Please write : \t" << currentWord << '\n';   // Вывод : какое слово нам надо ввести
        cin >> inputWord;   // Ввод слова от пользователя
        if ("EXIT" != inputWord)
        {
            if (inputWord == currentWord) {
                rightwrittedWords++;                    // Если слова введены верно, наращиваем счётчик
            }
        }
        else
        {
            break;
        }
    }

    // Итоги

    newTypingSpeed = rightwrittedWords / secs;

    cout << "\nCorrectly writted : " << rightwrittedWords;
    cout << "\nCount of words : " << DICT_SIZE_WORDS;
    cout << "\nYour speed " << newTypingSpeed << " words per minute" << "\n";
    if (typingSpeed != 0)
    {
        if (newTypingSpeed > typingSpeed)
        {
            float newPercent = (100 * newTypingSpeed) / typingSpeed;
            profitPercent = newPercent - 100;   
            cout << "New record! You're improved your speed by " << profitPercent << " %\n";
            typingSpeed = newTypingSpeed;
        }
    }
    else
    {
        typingSpeed = newTypingSpeed;
    }
    system("pause");
}   

void checkSpeedSymbols()    // Функция проверки скорости набора
{

    srand(time(0));

    rightwrittedSymbols = 0; // Обнуляем счётчик

    clock_t start = clock();    // Таймер, запоминание времени с момента запуска функции

    while (clock() - start < delay) {
        randomSymbol = rand() % DICT_SIZE_SYMBOLS; 
        cout << randomSymbol;//Случайное число, индекс
        clearScreen();
        cout << "Count of correctly writted symbols : " << rightwrittedSymbols << '\n';
        cout << "Please write : \t" << DICTONARY_OF_SYMBOLS[randomSymbol] << '\n';   // Вывод : какой символ нам надо ввести
        cin.getline(symbol, MAX_LEN);
        if (strcmp("EXIT", symbol) != 0)
        {
            if (strcmp(symbol, DICTONARY_OF_SYMBOLS[randomSymbol]) == 0) {
                rightwrittedSymbols++;                    //Если слова введены верно, наращиваем счётчик
                cout << "\n";
            }
        }
        else
        {
            break;
        }
    }

    // Итоги

    newTypingSpeedSymbols = rightwrittedSymbols / secs;

    cout << "\nCorrectly writted : " << rightwrittedSymbols;
    cout << "\nCount of symbols : " << DICT_SIZE_SYMBOLS;
    cout << "\nYour speed " << newTypingSpeedSymbols << " symbols per minute";
    if (typingSpeedSymbols != 0)
    {
        if (newTypingSpeedSymbols > typingSpeedSymbols)
        {
            float newPercent = (100 * newTypingSpeedSymbols) / typingSpeedSymbols;
            profitPercentSymbols = newPercent - 100;
            cout << "\nNew record! You're improved your speed by " << profitPercentSymbols << " %\n";
            typingSpeedSymbols = newTypingSpeedSymbols;
        }
    }
    else
    {
        typingSpeedSymbols = newTypingSpeedSymbols;
    }

    system("pause");
    
}

#pragma endregion



#pragma region Menu

void menu();



void info()
{

    clearScreen();

    cout << "Welcome to Keyboard Training" << "\n";
    cout << "This is a console program, that was written on C++";
    cout << "\n";
    cout << "Menu info : " << "\n";
    cout << "1 - This point can check your speed of writting words on keyboard" << "\n";
    cout << "2 - This point can check your speed of keyboard orientation and special character set" << "\n";
    cout << "3 - Suddenly if you need to clear your screen, this point can help you" << "\n";
    cout << "4 - Exit" << "\n";
    cout << "\n";
    cout << "When you're already doing your test, you can always stop it. Just write 'EXIT' (capslock)" << "\n";
}

int exit()  // Проверка : готов ли пользователь выйти из нашей чудесной программы
{
    cout << "Are you want to exit? (Write YES or NO)\n";

    for (; ; )
    {
        std::cin >> chooseStart;
        if (chooseStart == "NO")
        {
            break;
        }
        else if (chooseStart == "YES")
        {
            clearScreen();
            _exit(1);
        }
        else
        {
            std::cout << "Write YES or NO\n";
            continue;
        }
    }
}

void menuChecker()      // Функция для проверки выбора в меню программы. Выполненна через switch case. Какую цифру пользователь введёт, в такой пункт меню и попадёт
                        // Реализованно за счёт получения цифры в переменную.
{
    switch (chooseMenu)
    {
    case 1:
        info();
        system("pause");
        menu();
        break;
    case 2:
        checkSpeedWords();
        menu();
        break;
    case 3:
        checkSpeedSymbols();
        menu();
        break;
    case 4:
        clearScreen();
        menu();
    case 5:
        exit();
        menu(); // Сработает если пользоатель напишет NO
    }
}

void menu()
{
    
    clearScreen();

    readFile();

    cout << "1. Information" << "\n";
    cout << "2. Check your speed" << "\n";
    cout << "3. Train symbols" << "\n";
    cout << "4. Clear screen" << "\n";
    cout << "5. Exit" << "\n";
    cin >> chooseMenu;
    menuChecker();
    cout << "\n";
}

#pragma endregion



int main()
{

    // Приветстиве

    cout << "Welcome to Keyboard Training\n";  
    system("pause");
    menu();
    
    
    

    

}

