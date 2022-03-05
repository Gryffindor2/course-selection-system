#include<string.h>
//s2是否为s1的子串
bool isSubStr(const char* s1, const char* s2)
{
	for (int i = 0; i + strlen(s2) <= strlen(s1); i++)
	{
		for (int j = 0; j < strlen(s2); j++)
		{
			char c1, c2;
			
			if (s2[j] <= 'Z' && s2[j] >= 'A')
				c1 = s2[j] + 32;
			else
				c1 = s2[j];
			if (s1[i + j] <= 'Z' && s1[i + j] >= 'A')
				c2 = s1[i + j] + 32;
			else
				c2 = s1[i + j];
			if (c1 != c2 )
			{
				break;
			}
			if (j == strlen(s2) - 1)
			{
				return true;
			}
		}
	}
	return false;
}