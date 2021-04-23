#include <iostream>
#include <cstdlib>
#include <time.h> 
#include <stdlib.h>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

const int DICT_SIZE_SYMBOLS = 12;           // Кол-во символов (нужно для словаря и проверки скорости).
const int MAX_LEN = 255;    // Макс. длинна строки
float secs = 15;      // Ожидание 60 секунд перед концом цикла
const float delay = secs * CLOCKS_PER_SEC; // Вычисление задержки через константу CLOCK_PER_SEC, которая содержит в себе количество системных едениц времени в секунду.
const int N = 46000;

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
float bestTypingSpeed15Secs = 0;
float bestTypingSpeed30Secs = 0;
float bestTypingSpeed60Secs = 0;
float bestTypingSpeedSymbols15Secs = 0;
float bestTypingSpeedSymbols30Secs = 0;
float bestTypingSpeedSymbols60Secs = 0;

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
    int summaryWords = 0;
    clock_t start = clock();    // Таймер, запоминание времени с момента запуска функции

    while (clock() - start < delay) {               
        
        random = rand() % (46000 - 1+1) + 1;                        // Случайное число, индекс
        string currentWord = readFile();
        string inputWord;
   
        clearScreen();
        cout << "Count of correctly writted words : " << rightwrittedWords << '\n'; 
        cout << "Please write : \t" << currentWord << '\n';   // Вывод : какое слово нам надо ввести
        summaryWords++;
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

    if (typingSpeed != 0)
    {
        if (newTypingSpeed > typingSpeed)
        {
            float newPercent = (100 * newTypingSpeed) / typingSpeed;
            profitPercent = newPercent - 100;
            typingSpeed = newTypingSpeed;
        }
    }
    else
    {
        typingSpeed = newTypingSpeed;
    }

    // Итоги

    newTypingSpeed = rightwrittedWords / secs;

    cout << "\nCorrectly writted : " << rightwrittedWords;
    cout << "\nCount of words : " << summaryWords;
    cout << "\nYour speed " << newTypingSpeed << " words per " << secs << " secs" << "\n";
    if (secs == 15)
    {
        if (newTypingSpeed > bestTypingSpeed15Secs)
        {
            bestTypingSpeed15Secs = newTypingSpeed;
        }
    }
    else if (secs == 30)
    {
        if (newTypingSpeed > bestTypingSpeed30Secs)
        {
            bestTypingSpeed30Secs = newTypingSpeed;
        }
    }
    else if (secs == 60)
    {
        if (newTypingSpeed > bestTypingSpeed60Secs)
        {
            bestTypingSpeed60Secs = newTypingSpeed;
        }
    }

    system("pause");
}   

void checkSpeedSymbols()    // Функция проверки скорости набора
{

    srand(time(0));

    rightwrittedSymbols = 0; // Обнуляем счётчик
    int summarySymbols = 0;
    clock_t start = clock();    // Таймер, запоминание времени с момента запуска функции

    while (clock() - start < delay) {
        randomSymbol = rand() % DICT_SIZE_SYMBOLS; 
        cout << randomSymbol;   //Случайное число, индекс
        clearScreen();
        cout << "Count of correctly writted symbols : " << rightwrittedSymbols << '\n';
        cout << "Please write : \t" << DICTONARY_OF_SYMBOLS[randomSymbol] << '\n';   // Вывод : какой символ нам надо ввести
        summarySymbols++;
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
    cout << "\nCount of symbols : " << summarySymbols;
    cout << "\nYour speed " << newTypingSpeedSymbols << " symbols per minute";

    if (secs == 15)
    {
        if (newTypingSpeedSymbols > bestTypingSpeedSymbols15Secs)
        {
            bestTypingSpeedSymbols15Secs = newTypingSpeedSymbols;
        }
    }
    else if (secs == 30)
    {
        if (newTypingSpeedSymbols > bestTypingSpeedSymbols30Secs)
        {
            bestTypingSpeedSymbols30Secs = newTypingSpeedSymbols;
        }
    }
    else if (secs == 60)
    {
        if (newTypingSpeedSymbols > bestTypingSpeedSymbols60Secs)
        {
            bestTypingSpeedSymbols60Secs = newTypingSpeedSymbols;
        }
    }

    if (typingSpeedSymbols != 0)
    {
        if (newTypingSpeedSymbols > typingSpeedSymbols)
        {
            float newPercent = (100 * newTypingSpeedSymbols) / typingSpeedSymbols;
            profitPercentSymbols = newPercent - 100;
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

void chooseTime()
{
    cout << "\nChoose test time" << "\n";
    cout << "1. 15 secs" << "\n";
    cout << "2. 30 secs" << "\n";
    cout << "3. 60 secs";
    cout << "\n";
    cin >> chooseMenu;

    if (chooseMenu < 4 and chooseMenu > 0)
    {
        switch (chooseMenu)
        {
        case 1:
            secs = 15;
            break;
        case 2:
            secs = 30;
            break;
        case 3:
            secs = 60;
            break;
        }
    }
    else
    {
        cout << "Incorrect menu point";
    }

}

void menu();



void info()
{

    clearScreen();

    cout << "Welcome to Keyboard Training" << "\n";
    cout << "This is a console program, that was written on C++";
    cout << "\n";
    cout << "Menu info : " << "\n";
    cout << "2 - This point can check your speed of writting words on keyboard" << "\n";
    cout << "3 - This point can check your speed of keyboard orientation and special character set" << "\n";
    cout << "4 - Your global statistic" << "\n";
    cout << "5 - Suddenly if you need to clear your screen, this point can help you" << "\n";
    cout << "6 - Exit" << "\n";
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

void stats()
{
    clearScreen();
    cout << "\nWORDS TRAINING STATISTIC \n";
    cout << "\n";
    cout << "Your previous words typing speed : " << newTypingSpeed << "\n";
    cout << "Your best words typing speed per 15 secs : " << bestTypingSpeed15Secs << "\n";
    cout << "Your best words typing speed per 30 secs : " << bestTypingSpeed30Secs << "\n";
    cout << "Your best words typing speed per 60 secs : " << bestTypingSpeed60Secs << "\n";
    if (profitPercent > 0)
    {
        cout << "New record! You're improved your speed by " << profitPercent << " %\n";
    }

    cout << "\n";

    cout << "\nSYMBOLS TRAINING STATISTIC \n";
    cout << "\n";
    cout << "Your previous symbols typing speed : " << newTypingSpeedSymbols << "\n";
    cout << "Your best words typing speed per 15 secs : " << bestTypingSpeedSymbols15Secs << "\n";
    cout << "Your best words typing speed per 30 secs : " << bestTypingSpeedSymbols30Secs << "\n";
    cout << "Your best words typing speed per 60 secs : " << bestTypingSpeedSymbols60Secs << "\n";
    if (profitPercentSymbols > 0)
    {
        cout << "\nNew record! You're improved your speed by " << profitPercentSymbols << " %\n";
    }

}

void menuChecker()      // Функция для проверки выбора в меню программы. Выполненна через switch case. Какую цифру пользователь введёт, в такой пункт меню и попадёт
                        // Реализованно за счёт получения цифры в переменную.
{
    if (chooseMenu < 7 and chooseMenu > 0)
    {
        switch (chooseMenu)
        {
        case 1:
            info();
            std::system("pause");
            menu();
            break;
        case 2:
            chooseTime();
            checkSpeedWords();
            menu();
            break;
        case 3:
            chooseTime();
            checkSpeedSymbols();
            menu();
            break;
        case 4:
            stats();
            system("pause");
            menu();
        case 5:
            clearScreen();
            menu();
        case 6:
            exit();
            menu(); // Сработает если пользоатель напишет NO
        }
    }
    else
    {
        menu();
    }

}

void menu()
{
    
    chooseMenu = 0;

    clearScreen();

    readFile();

    cout << "1. Information" << "\n";
    cout << "2. Check your speed" << "\n";
    cout << "3. Train symbols" << "\n";
    cout << "4. Your statisitc" << "\n";
    cout << "5. Clear screen" << "\n";
    cout << "6. Exit" << "\n";
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

