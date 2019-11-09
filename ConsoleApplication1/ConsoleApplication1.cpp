#pragma once

#include"pch.h"

#include"COM.h"
#include"Snake.h"
#include"FileReading.h"

#include<conio.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<thread>//c++ 11 标准多线程
#include<time.h>

using namespace std;

bool clockBlink = false;
bool * pclockBlink = &clockBlink;

char userInput = '0';
char * puserInput  = &userInput;

void askUser()
{
	while (true)
	{
		if (_kbhit())
		{
			*puserInput = _getch();
		}
	}
}

void snakeWork()//---------------蛇的工作----------------
{
	CubeKit ck;
	Snake snake(4, ck , pclockBlink,puserInput);

	ck.Check();
	cout << "begin" << endl;
	int count = 0;
	while (true)
	{
		if (snake.IsEatingSelf())
		{
			cout << "******************************************" << endl;
			cout << " *           You're eating yourself       *" << endl;
			cout << "******************************************" << endl;
		}

		snake.ExDestnation(snake.AskIfEx());
		if (*pclockBlink)
		{
			snake.MoveAndRend();
		}
	}

}

void fileRead()//---------------文件读取----------------
{
	cout << "文件已定位为shuchu.txt" << endl;

	int position = 0;
	ifstream infile("shuchu.txt");
	
	while (true)
	{
		find_last_line(infile);
	}
}

void mClock()//---------------时间----------------
{
	clock_t start, finish;
	double duration;
	start = clock();
	while (true)
	{
		finish = clock();
		duration = (int)((finish - start) / CLOCKS_PER_SEC);
		if (duration >= 1)
		{
			*pclockBlink = true;
			cout << *pclockBlink << endl;
			//发送响应,在Move执行后关闭该响应
			start = clock();
		}
	}
}

int main()
{
	thread ts(snakeWork);
	thread tfr(fileRead);
	thread tc    (mClock);
	thread taskUser(askUser);
	
	//ts.hardware_concurrency();
	while (true);
	return 0;

}