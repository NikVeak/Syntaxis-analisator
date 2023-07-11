#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include "compilator.h"
using namespace std;

int findCount(char sym, string line)
{
    int count = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == sym)
        {
            count++;
        }
    }
    return count++;
}

string reserve_words[4] = { "var", "logical", "begin", "end" };
string operand[4] = { ".not.", ".and.", ".or.", ".eq." };
char symbols[47] =
{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'y', 'x', 'z',
    'A', 'B', 'D', 'F', 'G', 'H', 'I', 'J', 'K',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'W', 'Y', 'X'
};

char help_symbols[8] = { ' ', ';', ',', '=', ':', '(', ')' };
string magazine = "@";
string variables[256];
int count_variables = 0;
string condition = "S";
bool flag = 0;
string constants[2] = { "0", "1"};
ifstream in("program.txt");
string line;

int main()
{
    setlocale(LC_ALL, "Rus");
    cout << "-------------------Магазинный автомат--------------" << endl;
    cout << "Результат" << endl;
    string line;
    int count_line = 0;
    int number_str = 0;
    for (int i = 0; i < 256; i++)
    {
        variables[i] = "";
    }
    bool res = false;
    if (in.is_open())
    {
        string word;
        while (in >> word)
        {      
            line += word;
            if (condition == "S")
            {
                if (word == reserve_words[0])
                {
                    condition = "A"; 
                    magazine += 'V';
                    continue;
                }
                else
                {
                    cout << "Строка " << count_line+1 << " Ошибка! Ожидалось var, а встречено" << word << endl;
                    return 1;
                }
            }
            
            if (condition == "A")
            {
                if (magazine.back() == 'V')
                {
                    if (word.length() > 12)
                    {
                        cout << "Строка " << count_line+1 << " Ошибка в " << word << " ! Макс длина идентифкатора = 12 !" << "Получено = " << word.length() << endl;
                        return 2;
                    }
                    if (word.back() == ':')
                    {
                        for (int i = 0; i < word.length(); i++)
                        {
                            for (int j = 0; j < 47; j++)
                            {
                                if (symbols[j] == word[i])
                                {
                                    variables[count_variables] += word[i];
                                }
                            }
                        }
                        condition = "L";
                        magazine = "@";
                        continue;
                    }

                    if (word.back() != ',' )
                    {
                        cout << "Строка " << count_line+1 << " Ошибка ! Ожидалась ',' " << endl;
                        return 3;
                    }

                    for (int i = 0; i < word.length(); i++)
                    {
                        if (word[i] == ',')
                        {
                            count_variables++;
                            break;
                        }
                        for (int j = 0; j < 47; j++)
                        {
                            if (symbols[j] == word[i] && word[i] != ',')
                            {
                                variables[count_variables] += word[i];
                            }                            
                        }
                    }
                }               
            }
            
            if (condition == "L")
            {
                if (word == "logical")
                {
                    count_line++;
                    condition = "C";
                    continue;
                }
                else
                {
                    cout <<"Строка "<<count_line+1 << " Ошибка ! Ожидался logical, а встречено " << word << endl;
                    return 19;
                }
            }

            if (condition == "C")
            {
                if (word == ";")
                {
                    condition = "D";
                    continue;
                }
                else
                {
                    cout << "Строка " << count_line+1 << " Ошибка ! ожидалась ';', а встречено " << word << endl;
                    return 6;
                }
            }

            if (condition == "D")
            {
                if (word == "begin")
                {
                    condition = "B";
                    continue;
                }
                else
                {
                    cout << "Строка " << count_line+1 <<" Ошибка ! Ожидался begin, а встречено "<<word<<endl;
                    return 7;
                }
            }

            if (condition == "B")
            {
                count_line++;
                if (word == "end")
                {
                    condition = "Z";
                    magazine = "@";
                    res = true;
                    break;
                }
                for (int i = 0; i < 256; i++)
                {
                    if (variables[i] == word)
                    {
                        condition = "B1";
                        flag = true;
                        break;
                    }
                }
                if (flag)
                {
                    continue;
                }
                else
                {

                    cout << "Строка " << count_line << " Ошибка ! Ожидалась переменная, а встречено " << word << endl;
                    return 8;
                }
            }


            if (condition == "B1")
            {
                flag = false;
                if (word == "=")
                {
                    condition = "E";
                    magazine += 'E';
                    continue;
                }
                else
                {
                    cout << "Строка " << count_line-1 << " Ошибка ! Ожидалось '='  , а встречено "<<word << endl;
                    return 9;
                }
            }

            if (condition == "E")
            {
                if (magazine.back() == 'E')
                {
                    if (word == constants[0] || word == constants[1])
                    {
                        magazine += 'I';
                        continue;
                    }
                    if (word == operand[0])
                    {
                        magazine += 'E';
                        continue;
                    }
                    if (word == "(")
                    {
                        magazine += '(';
                        magazine += 'E';
                        continue;
                    }
                    for (int j = 0; j < 256; j++)
                    {
                        if (variables[j] == word)
                        {
                            magazine += 'I';
                            flag = true;
                            break;
                        }
                    }

                    if (flag)
                    {
                        continue;
                    }
                    else
                    {
                        cout << "Строка " << count_line+1 << " Ошибка ! Недопустимый символ или выражение" <<endl;
                        return 10;
                    }

                }

                if (magazine.back() == 'I')
                {
                    if (word == operand[1] || word == operand[2] || word == operand[3])
                    {
                        magazine += 'E';
                        continue;
                    }
                    if (word == ")")
                    {
                        magazine += ')';
                        magazine += 'I';
                        continue;
                    }
                    if (word == ";")
                    {
                        if (findCount('(', magazine) == findCount(')', magazine))
                        {
                            magazine = "@";
                            condition = "B";
                            continue;
                        }
                        else 
                        {
                            cout << "Строка " << count_line+1 << " Ошибка ! Неодинаковое кол-во скобок в выражении" << endl;
                            return 11;
                        }
                    }
                    else
                    {
                        cout << "Строка " << count_line+1 << " Ошибка ! Недопустимый символ, выражение или забыта ';'" <<endl;
                        return 12;
                    }
                }
                
            }

            if (condition == "Z")
            {
                cout << "Верный синтаксис !" << endl;
                return 0;
            }
        
        }

    }
    else
    {
        perror("Error opening !");
        return 1;
    }
 
    if (res)
    {
        cout << "Синтаксис верен !" << endl;
        cout << "------------------------------" << endl;

    }
    else
    {
        cout << "Ошибка ! Отсутствует end" << endl;
    }

    in.close();
    return 0;
}
