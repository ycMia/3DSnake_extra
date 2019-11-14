#pragma once

#include"pch.h"
//std::locale loc = std::locale::global(std::locale(""));
bool debugMode = false;//为true时不会进行蛇/苹果的坐标刷新
bool clockBlink = false;
bool * pclockBlink = &clockBlink;

char userInput = '0';
char * puserInput = &userInput;


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
#include<direct.h>

char nowPath[MAX_PATH];//将会在FileReading运行时赋值

using namespace std;


//void askUser()
//{
//	while (true)
//	{
//		if (_kbhit())
//		{
//			*puserInput = _getch();
//		}
//	}
//}
//替代为使用FileReading.h输入数据

void snakeWork()//---------------蛇的工作----------------
{
	CubeKit ck;
	Snake snake(4, ck , pclockBlink,puserInput);

	ck.Check();
	//cout << "begin" << endl;
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
	ifstream infile;
	_getcwd(nowPath, MAX_PATH);
	strcat_s(nowPath, "\\shuchu.txt");
	cout <<endl<< nowPath << endl;
	while (true)
	{
		ifstream infile;

		infile.open(nowPath, ios::in);
		if (!infile)
			cout << "nai" << endl;
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
			//cout << *pclockBlink << endl;
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
	//thread tAskUser(askUser);
	
	//ts.hardware_concurrency();
	while (true);
	return 0;

}