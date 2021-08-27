/*
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS	// 去除编译时有关安全的 errors 和 warnings
#pragma warning(disable:4244) 
#endif
*/

#include "header.h"
#include "cmdline.h" // 解析命令行参数

#include <fstream>
#include <ctime>

int n, m, iterNum = 0, aliveNum = 0;
bool mp[MAXL][MAXL], tmp[MAXL][MAXL];
std::string fileName;
cmdline::parser argParser;

int main(int argc, char **argv)
{
	argParser.add<int>("length", 'l', "map length", false, 50);
	argParser.add<int>("height", 'h', "map height", false, 50);
	argParser.add<bool>("type", 't', "is rand map", false, true);
	argParser.add<std::string>("config", 'c', "config file path(if type is 0)", false);

	argParser.parse_check(argc, argv);

	Init();
	while (true)
	{
		if (!aliveNum)
			break;
		Iteration();
		PrintMap();
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
			mp[x][y] = 1;
			++aliveNum;
		}
		fin.close();
	}
	else
	{
		srand(time(NULL));

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
			{
				mp[i][j] = rand() * rand() % 2;
				aliveNum += mp[i][j] ? 1 : 0;
			}
	}
}

void CopyMap(bool src[MAXL][MAXL], bool dst[MAXL][MAXL])
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			dst[i][j] = src[i][j];
}

void Iteration()
{
	++iterNum;
	CopyMap(mp, tmp);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			unsigned nearAliveNum = 0;
			for (int k = 0; k < 8; k++)
				nearAliveNum += mp[i + dx[k]][j + dy[k]] ? 1 : 0;
			if (nearAliveNum == 3)
				tmp[i][j] = 1;
			else if (nearAliveNum == 2 && mp[i][j])
				tmp[i][j] = 1;
			else
				tmp[i][j] = 0;
		}
	CopyMap(tmp, mp);
	aliveNum = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			++aliveNum;
}

void PrintMap()
{
	system("cls");
	std::cout << "Iteration num: " << iterNum << std::endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			std::cout.put(mp[i][j] ? 'O' : ' ');
		std::cout.put('\n');
	}
	std::cout << "Input ENTER to continue, or input Super+C to exit.";
	char ch = std::cin.get();
}