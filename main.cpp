/*
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS	// 去除编译时有关安全的 errors 和 warnings
#pragma warning(disable:4244) 
#endif
*/

#if defined (_WIN32)
#define CLEARWINDOW system("cls")
#define SLEEP(SLEEPTIME) _sleep(SLEEPTIME)
#else
#include <unistd.h>
#define CLEARWINDOW system("clear")
#define SLEEP(SLEEPTIME) usleep(SLEEPTIME * 1000)
#endif

#include "header.h"
#include "cmdline.h" // 解析命令行参数

#include <fstream>
#include <map>
#include <algorithm>
#include <ctime>

int n, m, iterNum = 0, aliveNum = 0;
std::map<std::pair<int, int>, bool> aliveCells; // 用 map 来存储活细胞，pair 来表示其横纵坐标
std::string fileName;
cmdline::parser argParser;

int main(int argc, char **argv)
{
	std::ios::sync_with_stdio(false); // 加速 io

	argParser.add<int>("length", 'l', "map length", false, 50);
	argParser.add<int>("height", 'h', "map height", false, 50);
	argParser.add<bool>("type", 't', "is rand map", false, true);
	argParser.add<std::string>("config", 'c', "config file path(if rand map disabled)", false);
	argParser.add<bool>("useSleep", '\0', "Use sleep instead of getchar", false, false);
	argParser.add<unsigned>("sleepTime", '\0', "Sleep time(ms) (if useSleep option enabled)", false, 500);

	argParser.parse_check(argc, argv);

	Init();
	while (true)
	{
		if (!aliveNum)
			break;
		PrintMap();
		Iteration();
	}

	return 0;
}

void Init()
{
	n = argParser.get<int>("height");
	m = argParser.get<int>("length");

	if (argParser.get<bool>("type") == false)
	{
		unsigned x, y;

		fileName = argParser.get<std::string>("config");
		std::ifstream fin(fileName);
		if (!fin.is_open())
		{
			std::cerr << "Cannot open config file. Exiting..." << std::endl;
			exit(1);
		}
		while (std::cin >> x >> y)
		{
			aliveCells[std::make_pair(x, y)] = 1;
			++aliveNum;
		}
		fin.close();
	}
	else
	{
		srand(time(NULL));

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				aliveCells[std::make_pair(i, j)] = (rand() * rand() % 2) ? 1 : 0;
				aliveNum += aliveCells[std::make_pair(i, j)] ? 1 : 0;
			}
	}
}

void Iteration()
{
	std::map<std::pair<int, int>, bool> another;
	another.clear();
	++iterNum;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			unsigned nearAliveNum = 0;
			for (int k = 0; k < 8; k++)
				nearAliveNum += (aliveCells[std::make_pair(i + dx[k], j + dy[k])] ? 1 : 0);
			if (nearAliveNum == 3)
				another[std::make_pair(i, j)] = 1;
			else if (nearAliveNum == 2 && aliveCells[std::make_pair(i, j)])
				another[std::make_pair(i, j)] = 1;
			else
				another[std::make_pair(i, j)] = 0;
		}
	aliveCells.clear();
	aliveCells = another;
	aliveNum = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			aliveNum += (aliveCells[std::make_pair(i, j)] ? 1 : 0);
}

void PrintMap()
{
	CLEARWINDOW;
	std::cout << "Iteration num: " << iterNum << std::endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			std::cout.put(aliveCells[std::make_pair(i, j)] ? 'O' : ' ');
		std::cout.put('\n');
	}
	if (argParser.get<bool>("useSleep") == false) {
		std::cout << "Input ENTER to continue, or input Super+C to exit." << std::endl;
		char ch = std::cin.get();
	}
	else {
		int sleepTime = argParser.get<unsigned>("sleepTime");
		SLEEP(sleepTime);
	}
}
