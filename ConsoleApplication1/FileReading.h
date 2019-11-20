#pragma once
#include<conio.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>

//static int last_position = 0;
int percentage[6] = { 0,0,0,0,0,0 };
int nowCur = 0;
//
string m_x1("RIGHT");
string m_x0("LEFT");
string m_z1("FORWARD");
string m_z0("BACK");
string m_y1("UP");
string m_y0("DOWN");
string m_end("**********");
//
//void linePrint(string line)
//{
//	std::cout << "**** " << line << " ****" << std::endl;
//}

bool analyzeLine(string line)
{
	//cout << line << endl;
	//bool completeFlag = false;
	if (line[0] <= '9' && line[0] >= '0')//数字
	{
		if (percentage[nowCur] == 0)
		{
			int count = 0;
			while (count < 3)
			{
				if (line[++count] == '.')
				{
					count--;
					break;
				}
			}
			int i = 0;
			while (count >= 0)
			{
				percentage[nowCur] += (int)pow(10, i)*((int)line[count] - '0');
				count--;
				i++;
			}
		}
		else
		{

		}
	}
	else
	{
		if (line[0] == m_x1[0]&& line[1] == m_x1[1])//暂时想不出如何优化这部分
		{
			nowCur = 0;
		}
		else if (line[0] == m_x0[0] && line[1] == m_x0[1])
		{
			nowCur = 5;
		}
		else if (line[0] == m_z1[0]&& line[1] == m_z1[1])
		{
			nowCur = 1;
		}
		else if (line[0] == m_z0[0] && line[1] == m_z0[1])
		{
			nowCur = 2;
		}
		else if (line[0] == m_y1[0] && line[1] == m_y1[1])
		{
			nowCur = 3;
		}
		else if (line[0] == m_y0[0] && line[1] == m_y0[1])
		{
			nowCur = 4;
		}
		else if (line[0] == m_y0[0] && line[1] == m_y0[1])
		{
			nowCur = 4;
		}
		else if (line[0] == m_end[0] && line[1] == m_end[1])
		{
			int max = 0;
			for (int i = 0; i < 6; i++)
			{
				max = (percentage[max] > percentage[i]) ? max : i;
			}
			*pfileInput = max;
			cout << "    "<< *pfileInput << endl;
			for (int i = 0; i < 6; i++)
			{
				percentage[i] = 0;
			}
			return true;
		}
		else
		{
			cout << "********************Error Input********************" << endl;
			//system("pause");
		}
	}
	return false;
}

void find_last_line(ifstream &infile)
{
	infile.seekg(0, ios::end);
	int filesize = infile.tellg();

	for(int n=0;n<filesize;)
	{
		infile.seekg(n, ios::beg);//移位至待读取内容处
		string line;
		getline(infile, line);
		if (analyzeLine(line))
		{
			break;
		}
		n = infile.tellg();
	}
}

