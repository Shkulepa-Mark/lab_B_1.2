#include <iostream>
using namespace std;

void splitStr(char*, const char*, char*, char*, int&);
bool compare_alph(char*, char*);
void sort_text(char**, int);
void print_text(char**, int);
void clear_trash(char**, int);

void splitStr(char* str, const char* razd, char* context, char* words[], int& wordCount) 
{
    char* Ptr = strtok_s(str, razd, &context);
    int index = 0;

    while (Ptr != nullptr && index < 80)
    {
        words[index] = new char[strlen(Ptr) + 1]; // выделяем память для слова
        strcpy_s(words[index], strlen(Ptr) + 1, Ptr); // копируем слово в выделенную память
        index++;
    
        Ptr = strtok_s(nullptr, razd, &context);
        wordCount++;
    }
}

bool compare_alph(char* word1, char* word2) //сравнивает два слова по алфавиту (word1<word2)
{
    return strcmp(word1, word2) < 0;
}

void sort_text(char** words, int word_counter) //сортировка текста выбором
{
    for (int i = 0; i < word_counter - 1; i++)
    {
        int i_min = i;
        for (int j = i + 1; j < word_counter; j++)
        {
            if (compare_alph(words[j], words[i_min]))
                i_min = j;
        }
        if (i != i_min)
        {
            char* temp = words[i];
            words[i] = words[i_min];
            words[i_min] = temp;
        }
    }
}

char* newStr(char** words, int wordCount)
{
    char* result = new char[80] {};

    for (int i = 0; i < wordCount; i++) {
        strcat_s(result, 80, words[i]);
        strcat_s(result, 80, " ");
    }
    return result;
}

void clear_trash(char **words,int wordCount)
{
    for (int i = 0; i < wordCount; i++)
    {
        delete[] words[i];
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int wordCount = 0;
    char str[80] = "";
    char* words[80] = {nullptr};

    const char razd[] = " ,?!;-.";
    char* context = nullptr;

    cout << "Введите строку: ";

    cin.getline(str, 80);

    splitStr(str, razd, context, words, wordCount);

    sort_text(words, wordCount);

    char* resultStr =  newStr(words, wordCount);
    cout << resultStr;

    clear_trash(words, wordCount);

    return 0;
}
