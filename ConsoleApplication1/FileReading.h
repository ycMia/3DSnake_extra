#pragma once
#include<conio.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
static int last_position = 0;//��¼��ǰ�Ѿ���������ļ�λ��
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
		linePrint(line);//��������е�����


		if (infile.tellg() > 0)//��������������жϣ���Ϊ��Ƶ������Ŀ���ļ�ʱ���ᵼ�¸ú�������-1
		{
			n = last_position = infile.tellg();
		}
	}
}