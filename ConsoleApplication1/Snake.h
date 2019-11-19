#pragma once
#include<conio.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
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
	Snake(int length, CubeKit & cubekit,bool * clockBlink,char * puserInput);

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


private:
	char * _userInput;
	bool * _clockBlink;
	CubeKit & _cubekit;
	int _length;
	Node * _tail = new Node;
	Node * _head = new Node;
	Apple _apple = {7,4,4};
	int _destnation = 0;//相对世界的上下左右前后,即接入的数据
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

inline Snake::Snake(int length, CubeKit & cubekit,bool * clockBlink,char * userInput)
	:_cubekit(cubekit),_clockBlink(clockBlink),_userInput(userInput)
{/*
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

	switch (_destnation)
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

inline int Snake::AskIfEx()//用户输入
{
	//打这段代码的时候遇到了学校里一只猫
	//第一次知道什么叫"键盘被猫踩了"的感觉

	//已弃用键盘类型
	/*switch (*_userInput)
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
	}*/

	return *puserInput;

	//else
	//{
	//	if (*_clockBlink)
	//	{
	//		return _destnation;
	//		//刷新为缺省方向
	//	}
	//	
	//}
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