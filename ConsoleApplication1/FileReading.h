#pragma once
#include<conio.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
static int last_position = 0;//记录当前已经处理掉的文件位置
void linePrint(string line)
{
	std::cout << "**** " << line << " ****" << std::endl;
}

void find_last_line(ifstream &infile)
{
	infile.seekg(0, ios::end);
	int filesize = infile.tellg();
	for (int n = last_position; n < filesize; n++)
	{
		infile.seekg(last_position, ios::beg);
		string line;
		getline(infile, line);
		linePrint(line);//输出最新行的内容


		if (infile.tellg() > 0)//这里必须加入这个判断，因为在频繁更新目标文件时，会导致该函数返回-1
		{
			n = last_position = infile.tellg();
		}
	}
}