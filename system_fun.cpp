#include<io.h>
#include<direct.h>
#include<Windows.h>
//dir�������򴴽�
void testDir(const char* dir)
{
	if (_access(dir, 0) == -1)
	{
		_mkdir(dir);
	}
}
//����
void clearScreen()
{
	system("cls");
	return;
}
//���������ַ���ɫ��Ϊcolor
void changeCharColor(short color)
{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}