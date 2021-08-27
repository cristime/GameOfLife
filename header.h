#pragma once

const int MAXL = 1e4 + 10,				// 10,000
	MAXFILELEN = (1 << 8) - 1,			// 255
	dx[] = {-1, 0, 1, -1, 1, -1, 0, 1}, // 每一行的偏移值
	dy[] = {-1, -1, -1, 0, 0, 1, 1, 1}; // 每一列的偏移值

void Init();
void Iteration();
void CopyMap(bool src[MAXL][MAXL], bool dst[MAXL][MAXL]);
void PrintMap();
