#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

//��ͼ
//0:�յ�		1��ǽ��	3�����ӵ�Ŀ�ĵ�	4������
//6:��		7�����Ӻ�Ŀ�ĵ��غ�		9����վ��Ŀ�ĵ�

int g_map[2][10][12] =
{
	{
		{1,1,1,1,1,0,0,0,0,0,0,0},
		{1,0,0,0,1,0,1,1,1,0,0,0},
		{1,0,4,0,1,0,1,1,1,1,1,1},
		{1,0,4,6,1,0,1,0,0,0,3,1},
		{1,1,1,4,1,1,1,0,0,0,3,1},
		{0,1,0,0,0,0,0,0,0,0,3,1},
		{0,1,0,0,0,1,0,0,0,0,0,1},
		{0,1,0,0,0,1,0,0,0,0,0,1},
		{0,1,1,1,1,1,0,0,0,0,0,1},
		{0,0,0,0,0,0,1,1,1,1,1,1},
    },
	{
		{0,1,1,1,1,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,0,0,0},
		{0,1,0,0,0,0,1,1,1,1,1,1},
		{1,1,4,1,1,0,1,1,0,0,0,1},
		{1,0,6,0,1,0,0,1,0,0,0,1},
		{1,0,0,1,1,1,0,0,0,0,0,1},
		{1,0,0,0,4,0,0,4,0,0,0,1},
		{1,0,3,3,1,0,4,0,0,0,1,1},
		{1,1,3,3,1,0,0,0,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,0},
	},
};

int g_nCurrentLevel = 0;	//��ǰ�ؿ�

void DrapMap();				//��ӡ��ͼ
POINT GetGamerPosition();	//��ȡ�������
void Up();					//����
void Down();				//����
void Left();				//����
void Right();			    //����

int GetSpaceBox();			//�����������

void SetColor(int nColor);			//������ɫ

int main()
{
	//���ñ���
	SetConsoleTitle(L"������");
	//���ô��ڵĴ�С
	system("mode con cols=26 lines=12");
	while (1)
	{
		//��ȡʣ�����ӵĸ���
		if (GetSpaceBox() == 0)
		{
			g_nCurrentLevel++;
		}

		//����
		system("cls");
		//��ӡ��ͼ
		DrapMap();

		//getchar();
		//scanf();    ��������Ҫ���س���������
		char ch = _getch();
		switch (ch)
		{
		case 'w':case 72:	//����
			Up();
			break;
		case 's':case 80:	//����
			Down();
			break;
		case 'a':case 75:	//����
			Left();
			break;
		case 'd':case 77:	//����
			Right();
			break;
		}
	}

	return 0;
}

/*===========================================*/
//��ӡ��ͼ
void DrapMap()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			switch (g_map[g_nCurrentLevel][i][j])
			{
			case 0:		//�յ�
				printf("  ");
				break;
			case 1:		//ǽ��
				SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
				printf("��");
				break;
			case 3:		//���ӵ�Ŀ�ĵ�
				SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				printf("��");
				break;
			case 4:		//����
				SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				printf("��");
				break;
			case 6:		//��
				SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				printf("��");
				break;
			case 7:		//������Ŀ�ĵ��غ�
				SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				printf("��");
				break;
			case 9:		//��վ��Ŀ�ĵ�
				SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				printf("��");
				break;
			}
		}
		printf("\n");
	}
}

//��ȡ�������
POINT GetGamerPosition()
{
	POINT pos = { -1,-1 };
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (g_map[g_nCurrentLevel][i][j] == 6 || g_map[g_nCurrentLevel][i][j] == 9)
			{
				pos.x = i;
				pos.y = j;
				return pos;
			}
		}
	}
	return pos;
}

//����
void Up()
{
	POINT pos = GetGamerPosition();

	//1.�˵�ǰ���ǿյ�
	if (g_map[g_nCurrentLevel][pos.x - 1][pos.y] == 0)
	{
		g_map[g_nCurrentLevel][pos.x - 1][pos.y] = 6;//�յظ�Ϊ��
		//ԭ���˵�λ�û�ԭ
		if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
			g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
		else
			g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
	}
	//2.�˵�ǰ����Ŀ�ĵ�
	if (g_map[g_nCurrentLevel][pos.x - 1][pos.y] == 3)
	{
		g_map[g_nCurrentLevel][pos.x - 1][pos.y] = 9;//��վ��Ŀ�ĵ�
		//ԭ���˵�λ�û�ԭ
		if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
			g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
		else
			g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
	}
	//3.�˵�ǰ��������
	if (g_map[g_nCurrentLevel][pos.x - 1][pos.y] == 4)
	{
		//a.���ӵ�ǰ���ǿյ�
		if (g_map[g_nCurrentLevel][pos.x - 2][pos.y] == 0)
		{
			g_map[g_nCurrentLevel][pos.x - 2][pos.y] = 4;
			g_map[g_nCurrentLevel][pos.x - 1][pos.y] = 6;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
		//b.���ӵ�ǰ����Ŀ�ĵ�
		if (g_map[g_nCurrentLevel][pos.x - 2][pos.y] == 3)
		{
			g_map[g_nCurrentLevel][pos.x - 2][pos.y] = 7;
			g_map[g_nCurrentLevel][pos.x - 1][pos.y] = 6;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
	}
	//4.�˵�ǰ�������Ӻ�Ŀ�ĵص��غ�
	if (g_map[g_nCurrentLevel][pos.x - 1][pos.y] == 7)
	{
		//a.���ӵ�ǰ���ǿյ�
		if (g_map[g_nCurrentLevel][pos.x - 2][pos.y] == 0)
		{
			g_map[g_nCurrentLevel][pos.x - 2][pos.y] = 4;
			g_map[g_nCurrentLevel][pos.x - 1][pos.y] = 9;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
		//b.���ӵ�ǰ����Ŀ�ĵ�
		if (g_map[g_nCurrentLevel][pos.x - 2][pos.y] == 3)
		{
			g_map[g_nCurrentLevel][pos.x - 2][pos.y] = 7;
			g_map[g_nCurrentLevel][pos.x - 1][pos.y] = 9;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
	}
}

//����
void Down()
{
	POINT pos = GetGamerPosition();

	//1.�˵�ǰ���ǿյ�
	if (g_map[g_nCurrentLevel][pos.x + 1][pos.y] == 0)
	{
		g_map[g_nCurrentLevel][pos.x + 1][pos.y] = 6;//�յظ�Ϊ��
		//ԭ���˵�λ�û�ԭ
		if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
			g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
		else
			g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
	}
	//2.�˵�ǰ����Ŀ�ĵ�
	if (g_map[g_nCurrentLevel][pos.x + 1][pos.y] == 3)
	{
		g_map[g_nCurrentLevel][pos.x + 1][pos.y] = 9;//��վ��Ŀ�ĵ�
		//ԭ���˵�λ�û�ԭ
		if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
			g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
		else
			g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
	}
	//3.�˵�ǰ��������
	if (g_map[g_nCurrentLevel][pos.x + 1][pos.y] == 4)
	{
		//a.���ӵ�ǰ���ǿյ�
		if (g_map[g_nCurrentLevel][pos.x + 2][pos.y] == 0)
		{
			g_map[g_nCurrentLevel][pos.x + 2][pos.y] = 4;
			g_map[g_nCurrentLevel][pos.x + 1][pos.y] = 6;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
		//b.���ӵ�ǰ����Ŀ�ĵ�
		if (g_map[g_nCurrentLevel][pos.x + 2][pos.y] == 3)
		{
			g_map[g_nCurrentLevel][pos.x + 2][pos.y] = 7;
			g_map[g_nCurrentLevel][pos.x + 1][pos.y] = 6;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
	}
	//4.�˵�ǰ�������Ӻ�Ŀ�ĵص��غ�
	if (g_map[g_nCurrentLevel][pos.x + 1][pos.y] == 7)
	{
		//a.���ӵ�ǰ���ǿյ�
		if (g_map[g_nCurrentLevel][pos.x + 2][pos.y] == 0)
		{
			g_map[g_nCurrentLevel][pos.x + 2][pos.y] = 4;
			g_map[g_nCurrentLevel][pos.x + 1][pos.y] = 9;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
		//b.���ӵ�ǰ����Ŀ�ĵ�
		if (g_map[g_nCurrentLevel][pos.x + 2][pos.y] == 3)
		{
			g_map[g_nCurrentLevel][pos.x + 2][pos.y] = 7;
			g_map[g_nCurrentLevel][pos.x + 1][pos.y] = 9;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
	}
}

//����
void Left()
{
	POINT pos = GetGamerPosition();

	//1.�˵�ǰ���ǿյ�
	if (g_map[g_nCurrentLevel][pos.x][pos.y - 1] == 0)
	{
		g_map[g_nCurrentLevel][pos.x][pos.y - 1] = 6;//�յظ�Ϊ��
		//ԭ���˵�λ�û�ԭ
		if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
			g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
		else
			g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
	}
	//2.�˵�ǰ����Ŀ�ĵ�
	if (g_map[g_nCurrentLevel][pos.x][pos.y - 1] == 3)
	{
		g_map[g_nCurrentLevel][pos.x][pos.y - 1] = 9;//��վ��Ŀ�ĵ�
		//ԭ���˵�λ�û�ԭ
		if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
			g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
		else
			g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
	}
	//3.�˵�ǰ��������
	if (g_map[g_nCurrentLevel][pos.x][pos.y - 1] == 4)
	{
		//a.���ӵ�ǰ���ǿյ�
		if (g_map[g_nCurrentLevel][pos.x][pos.y - 2] == 0)
		{
			g_map[g_nCurrentLevel][pos.x][pos.y - 2] = 4;
			g_map[g_nCurrentLevel][pos.x][pos.y - 1] = 6;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
		//b.���ӵ�ǰ����Ŀ�ĵ�
		if (g_map[g_nCurrentLevel][pos.x][pos.y - 2] == 3)
		{
			g_map[g_nCurrentLevel][pos.x][pos.y - 2] = 7;
			g_map[g_nCurrentLevel][pos.x][pos.y - 1] = 6;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
	}
	//4.�˵�ǰ�������Ӻ�Ŀ�ĵص��غ�
	if (g_map[g_nCurrentLevel][pos.x][pos.y - 1] == 7)
	{
		//a.���ӵ�ǰ���ǿյ�
		if (g_map[g_nCurrentLevel][pos.x][pos.y - 2] == 0)
		{
			g_map[g_nCurrentLevel][pos.x][pos.y - 2] = 4;
			g_map[g_nCurrentLevel][pos.x][pos.y - 1] = 9;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
		//b.���ӵ�ǰ����Ŀ�ĵ�
		if (g_map[g_nCurrentLevel][pos.x][pos.y - 2] == 3)
		{
			g_map[g_nCurrentLevel][pos.x][pos.y - 2] = 7;
			g_map[g_nCurrentLevel][pos.x][pos.y - 1] = 9;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
	}
}

//����
void Right()
{
	POINT pos = GetGamerPosition();

	//1.�˵�ǰ���ǿյ�
	if (g_map[g_nCurrentLevel][pos.x][pos.y + 1] == 0)
	{
		g_map[g_nCurrentLevel][pos.x][pos.y + 1] = 6;//�յظ�Ϊ��
		//ԭ���˵�λ�û�ԭ
		if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
			g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
		else
			g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
	}
	//2.�˵�ǰ����Ŀ�ĵ�
	if (g_map[g_nCurrentLevel][pos.x][pos.y + 1] == 3)
	{
		g_map[g_nCurrentLevel][pos.x][pos.y + 1] = 9;//��վ��Ŀ�ĵ�
		//ԭ���˵�λ�û�ԭ
		if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
			g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
		else
			g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
	}
	//3.�˵�ǰ��������
	if (g_map[g_nCurrentLevel][pos.x][pos.y + 1] == 4)
	{
		//a.���ӵ�ǰ���ǿյ�
		if (g_map[g_nCurrentLevel][pos.x][pos.y + 2] == 0)
		{
			g_map[g_nCurrentLevel][pos.x][pos.y + 2] = 4;
			g_map[g_nCurrentLevel][pos.x][pos.y + 1] = 6;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
		//b.���ӵ�ǰ����Ŀ�ĵ�
		if (g_map[g_nCurrentLevel][pos.x][pos.y + 2] == 3)
		{
			g_map[g_nCurrentLevel][pos.x][pos.y + 2] = 7;
			g_map[g_nCurrentLevel][pos.x][pos.y + 1] = 6;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
	}
	//4.�˵�ǰ�������Ӻ�Ŀ�ĵص��غ�
	if (g_map[g_nCurrentLevel][pos.x][pos.y + 1] == 7)
	{
		//a.���ӵ�ǰ���ǿյ�
		if (g_map[g_nCurrentLevel][pos.x][pos.y + 2] == 0)
		{
			g_map[g_nCurrentLevel][pos.x][pos.y + 2] = 4;
			g_map[g_nCurrentLevel][pos.x][pos.y + 1] = 9;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
		//b.���ӵ�ǰ����Ŀ�ĵ�
		if (g_map[g_nCurrentLevel][pos.x][pos.y + 2] == 3)
		{
			g_map[g_nCurrentLevel][pos.x][pos.y + 2] = 7;
			g_map[g_nCurrentLevel][pos.x][pos.y + 1] = 9;
			//ԭ���˵�λ�û�ԭ
			if (g_map[g_nCurrentLevel][pos.x][pos.y] == 9)
				g_map[g_nCurrentLevel][pos.x][pos.y] = 3;
			else
				g_map[g_nCurrentLevel][pos.x][pos.y] = 0;
		}
	}
}

//����������ӵĸ���
int GetSpaceBox()
{
	int nCount = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (g_map[g_nCurrentLevel][i][j] == 4)
				nCount++;
		}
	}
	return nCount;
}

//������ɫ
void SetColor(int nColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, nColor);
}