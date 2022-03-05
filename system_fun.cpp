#include<io.h>
#include<direct.h>
#include<Windows.h>
//dir不存在则创建
void testDir(const char* dir)
{
	if (_access(dir, 0) == -1)
	{
		_mkdir(dir);
	}
}
//清屏
void clearScreen()
{
	system("cls");
	return;
}
//将命令行字符颜色改为color
void changeCharColor(short color)
{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}