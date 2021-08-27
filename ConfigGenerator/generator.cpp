#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int WIDTH = 4;
priority_queue<pair<int, int>> gameMap;
vector<pair<int, int>> temp;
string op, fileName;
int length, height, x, y;

void printHelp();
void printMap();
int searchForValue(int, int);

int main(int argc, char **argv)
{
    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
    {
        printHelp();
        return 0;
    }
    cout << "Enter config file name: ";
    cin >> fileName;
    cout << "Enter map length: ";
    cin >> length;
    cout << "Enter map height: ";
    cin >> height;
    while (true)
    {
        printMap();
        cin >> op;
        if (op == "QUIT")
            break;
        else
        {
            cin >> x >> y;
            if (op == "ADD")
            {
                if (searchForValue(x, y))
                    continue;
                gameMap.push(make_pair(x, y));
            }
            else
            {
                int t = searchForValue(x, y);
                if (!t)
                    continue;
                temp.clear();
                for (int i = 0; i < t; i++)
                {
                    temp.push_back(gameMap.top());
                    gameMap.pop();
                }
                gameMap.pop();
                for (vector<pair<int, int>>::iterator it = temp.begin(); it != temp.end(); ++it)
                    gameMap.push(*it);
            }
        }
    }
    ofstream fout(fileName.c_str());
    while (!gameMap.empty())
        fout << gameMap.top().first << ' ' << gameMap.top().second << endl;
    fout.close();
    return 0;
}

void printHelp()
{
    cout << "When you enter the program, you need enter three values." << endl;
    cout << "OP(ADD | DELETE | QUIT)" << endl;
    cout << "If you enter QUIT, you needn't enter the following two values." << endl;
    cout << "Else you will enter two integers: x, y" << endl;
}

void printMap()
{
    for (int i = 0; i <= length; i++)
        cout << setw(WIDTH) << i << ' ';
    for (int i = 1; i <= height; i++)
        for (int j = 0; j <= length; j++)
        {
            if (!j)
                cout << setw(WIDTH) << i << ' ';
            else
            {
                int pd = 0;

                if (pd)
                    cout << setw(WIDTH) << 'o' << ' ';
                else
                    cout << setw(WIDTH) << ' ' << ' ';
            }
        }
}

int searchForValue(int i, int j)
{
    int pd = 0, popNum = 0;
    temp.clear();
    while (!gameMap.empty() && gameMap.top().first <= i && gameMap.top().second <= j)
    {
        if (gameMap.top().first == i && gameMap.top().second == j)
        {
            pd = 1;
            break;
        }
        temp.push_back(gameMap.top());
        gameMap.pop();
        ++popNum;
    }
    for (vector<pair<int, int>>::iterator it = temp.begin(); it != temp.end(); ++it)
        gameMap.push(*it);
    return (pd ? popNum : pd);
}