#pragma once
#include<conio.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<direct.h>
#include<cstdio>

struct Node
{
	int x;
	int y;
	int z;
	Node * next;
	Node * pre;
};

struct Apple
{
	int x;
	int y;
	int z;
};

class Snake
{
public:
	void Init(Node * first, Node * last, int length);
	Snake(int length, CubeKit & cubekit,bool * clockBlink);

	void PrintApple();
	bool IsEatingApple();
	void CreateApple();

	void PrintSnake();
	bool IsEatingSelf();

	Node * GetForwardNode();
	void Move();
	void MoveAndRend();
	void ExDestnation(int d);
	int  AskIfEx();
	void Refresh();

	void fileRead(ifstream & infile, const char * nowPath);
	bool analyzeLine(string line);
	void find_last_line(ifstream & infile);
	//void fileRead(ifstream infile, const char * nowPath);

private:
	bool * _clockBlink;
	CubeKit & _cubekit;
	int _length;
	Node * _tail = new Node;
	Node * _head = new Node;
	Apple _apple = {7,4,4};
	int _destnation = 0;//相对世界的上下左右前后,即接入的数据

	//char * _userInput;
	int _fileInput = -1;
	int _percentage[6] = { 0,0,0,0,0,0 };
	int _nowCur = 0;

	const string _m_x1="RIGHT";
	const string _m_x0="LEFT";
	const string _m_z1="FORWARD";
	const string _m_z0="BACK";
	const string _m_y1="UP";
	const string _m_y0="DOWN";
	const string _m_end="**********";
};


inline void Snake::Init(Node * first, Node * last, int length)
{
	Node * middle = new Node;
	last->next = middle;
	middle->next = first;
	first->pre = middle;
	middle->pre = last;
	middle->x = first->x - 1;
	middle->y = first->y;
	middle->z = first->z;
	--length;
	if (length > 0)
		Init(middle, last, length);
	else
	{
		middle->x = first->x - 1;
		middle->y = first->y;
		middle->z = first->z;
		last->x = middle->x - 1;
		last->y = middle->y;
		last->z = middle->z;
	}
}

inline Snake::Snake(int length, CubeKit & cubekit,bool * clockBlink)
	:_cubekit(cubekit),_clockBlink(clockBlink)
{
	/*
	_apple.x = 7;
	_apple.y = 4;
	_apple.z = 4;
*/
	_length = length;
	_head->x = 4; _head->y = 4; _head->z = 4;
	Init(_head, _tail, _length - 2);//递归


	
}

inline void Snake::PrintApple()
{
	_cubekit.AddPre(_apple.x, _apple.y, _apple.z);
	if(!debugMode)
		cout << "apple :(" << _apple.x << "," << _apple.y << "," << _apple.z << ")" << setw(8) << endl;
}

inline void Snake::CreateApple()
{
	time_t *ttime = new time_t;
	srand((int)time(ttime));

	//防止苹果生成在蛇的位置
	Node *finder = _head;
	bool crash = false;
	while (true)
	{
		srand(rand());
		_apple.x = rand() % 7;
		srand(rand());
		_apple.y = rand() % 7;
		srand(rand());
		_apple.z = rand() % 7;
		for (int count = 1; count < _length; ++count)
		{
			if (finder->x == _apple.x&&finder->y == _apple.y&&finder->z == _apple.z)
			{
				crash = true;
				break;
			}
			finder = finder->pre;
		}
		if (!crash)
			break;
	}
	delete ttime;
}

inline bool Snake::IsEatingApple()
{
	if (_head->x == _apple.x&&
		_head->y == _apple.y&&
		_head->z == _apple.z)
	{
		CreateApple();
		return true;
	}
	return false;
}

inline bool Snake::IsEatingSelf()
{
	bool ans = false;
	Node *finder = _head;
	finder = finder->pre;
	int count = 1;
	while (count < _length)
	{
		if (finder->x == _head->x&&finder->y == _head->y&&finder->z == _head->z)
		{
			ans = true;
			break;
		}
		else
		{
			finder = finder->pre;
		}
		++count;
	}
	return ans;
}

inline void Snake::PrintSnake()
{
	Node *now = new Node;
	now->next = _tail;
	now = now->next;

	for (int i = 0; i < _length; i++)
	{
		_cubekit.AddPre(now->x, now->y, now->z);
		if(!debugMode)
			cout << "(" << now->x << "," << now->y << "," << now->z << ")" << setw(2);
		now = now->next;
	};
}

inline Node * Snake::GetForwardNode()//不关坐标系的事
{
	Node * pnode = new Node;

	switch (_fileInput)
	{
	case 0:
		pnode->x = _head->x + 1;
		pnode->y = _head->y;
		pnode->z = _head->z;
		break;
	case 1:
		pnode->x = _head->x;
		pnode->y = _head->y;
		pnode->z = _head->z + 1;
		break;
	case 2:
		pnode->x = _head->x;
		pnode->y = _head->y;
		pnode->z = _head->z - 1;
		break;
	case 3:
		pnode->x = _head->x;
		pnode->y = _head->y + 1;
		pnode->z = _head->z;
		break;
	case 4:
		pnode->x = _head->x;
		pnode->y = _head->y - 1;
		pnode->z = _head->z;
		break;
	case 5:
		pnode->x = _head->x - 1;
		pnode->y = _head->y;
		pnode->z = _head->z;
		break;
	default:
		break;
	}
	return pnode;
	//已弃用键盘输入

	switch (*puserInput)
	{
	case 0:
		pnode->x = _head->x + 1;
		pnode->y = _head->y;
		pnode->z = _head->z;
		break;
	case 1:
		pnode->x = _head->x;
		pnode->y = _head->y;
		pnode->z = _head->z + 1;
		break;
	case 2:
		pnode->x = _head->x;
		pnode->y = _head->y;
		pnode->z = _head->z - 1;
		break;
	case 3:
		pnode->x = _head->x;
		pnode->y = _head->y + 1;
		pnode->z = _head->z;
		break;
	case 4:
		pnode->x = _head->x;
		pnode->y = _head->y - 1;
		pnode->z = _head->z;
		break;
	case 5:
		pnode->x = _head->x - 1;
		pnode->y = _head->y;
		pnode->z = _head->z;
		break;
	default:
		break;
	}
	return pnode;
}

inline void Snake::Move()
{
	Node *node = GetForwardNode();
	node->pre = _head->pre;
	Node *con = _head;
	_head = node;
	node = con;
	_head->pre = node;
	node->next = _head;
	if (IsEatingApple())
		_length++;
	else
	{
		_tail = _tail->next;
		_tail->pre = NULL;
	}
}

inline void Snake::MoveAndRend()
{
	Move();
	Refresh();
	_cubekit.ClearPre();
	PrintSnake();
	PrintApple();
	_cubekit.printSnake();

	*_clockBlink = false;
}

inline void Snake::ExDestnation(int d)
{
	_destnation = d;
}

inline int Snake::AskIfEx()//输入
{
	return _fileInput;

	//已弃用键盘输入
	switch (*puserInput)
	{
	case 'd':
		return 0;
	case 'w':
		return 1;
	case 's':
		return 2;
	case 'u':
		return 3;
	case 'j':
		return 4;
	case 'a':
		return 5;
	default:
		return _destnation;
		break;
	}
	
}

inline void Snake::Refresh()//防止超过立方
{
	Node *finder = _head;
	for (int count = 1; count < _length; ++count)
	{
		if (finder->x < 0)
		{
			finder->x += 8;
		}
		if (finder->y < 0)
		{

			finder->y += 8;
		}
		if (finder->z < 0)
		{
			finder->z += 8;
		}
		finder->x = finder->x % 8;
		finder->y = finder->y % 8;
		finder->z = finder->z % 8;
		finder = finder->pre;
	}
}

inline void Snake::fileRead(ifstream & infile, const char * nowPath)
{
	infile.open(nowPath, ios::in);
	find_last_line(infile);
	infile.close();
	if (remove(nowPath) == 0)
	{
		cout << "删除成功" << endl;
	}
	else
	{
		//cout << "删除失败" << endl;
	}
}

//static int last_position = 0;

//void Snkae::linePrint(string line)
//{
//	std::cout << "**** " << line << " ****" << std::endl;
//}

bool Snake::analyzeLine(string line)
{
	//cout << line << endl;
	//bool completeFlag = false;
	if (line[0] <= '9' && line[0] >= '0')//数字
	{
		if (_percentage[_nowCur] == 0)
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
				_percentage[_nowCur] += (int)pow(10, i)*((int)line[count] - '0');
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
		if (line[0] == _m_x1[0] && line[1] == _m_x1[1])//暂时想不出如何优化这部分
		{
			_nowCur = 0;
		}
		else if (line[0] == _m_x0[0] && line[1] == _m_x0[1])
		{
			_nowCur = 5;
		}
		else if (line[0] == _m_z1[0] && line[1] == _m_z1[1])
		{
			_nowCur = 1;
		}
		else if (line[0] == _m_z0[0] && line[1] == _m_z0[1])
		{
			_nowCur = 2;
		}
		else if (line[0] == _m_y1[0] && line[1] == _m_y1[1])
		{
			_nowCur = 3;
		}
		else if (line[0] == _m_y0[0] && line[1] == _m_y0[1])
		{
			_nowCur = 4;
		}
		else if (line[0] == _m_y0[0] && line[1] == _m_y0[1])
		{
			_nowCur = 4;
		}
		else if (line[0] == _m_end[0] && line[1] == _m_end[1])
		{
			int max = 0;
			for (int i = 0; i < 6; i++)
			{
				max = (_percentage[max] > _percentage[i]) ? max : i;
			}
			_fileInput = max;
			cout << "    " << _fileInput << endl;
			for (int i = 0; i < 6; i++)
			{
				_percentage[i] = 0;
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

void Snake::find_last_line(ifstream &infile)
{
	infile.seekg(0, ios::end);
	int filesize = infile.tellg();

	for (int n = 0; n < filesize;)
	{
		infile.seekg(n, ios::beg);//移位至n处
		string line;
		getline(infile, line);
		if (analyzeLine(line))
		{
			break;
		}
		n = infile.tellg();
	}
}

