#include<conio.h>
#include<stdio.h>
//½«ÃÜÂëÐ´Èëpassword
void getPassword(char* password)
{
	char c = '\0';
	int i = 0;
	while (true)
	{
		c = _getch();
		if (c == '\r')
		{
			if (i == 0)
			{
				continue;
			}
			else
			{
				printf("\n");
				password[i] = '\0';
				break;
			}
		}
		else if (c == '\b')
		{
			if (i > 0)
			{
				i--;
				printf("\b \b");
			}
			continue;
		}
		else if (c == ' ' || c == '\t')
		{
			printf("\a");
			continue;
		}
		else if (i == 19)
		{
			continue;
		}
		password[i] = c;
		putchar('*');
		i++;
	}
}
