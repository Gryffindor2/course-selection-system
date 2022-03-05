#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif 
#define MAIN

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"datastruct.h"
#include"consts.h"
#include"database.h"
#include"encryption.h"

extern int permision;
extern float totalCredit;
extern void changeCharColor(short color);
extern void generateConfigFile(char* destination, const char* name);
extern void getPassword(char* password);
//the functions bellow are the main commands

//帮助信息
void printhelp()
{
	switch (permision)
	{
	case 0:
		printf("\tHELP DOCUMENTATION\n");
		printf("You must log in before using this system. The teacher owns the admin ");
		printf("account, which has the maximum permissions. The admin account is also unchangable");
		printf(". The students' account should be created by the teacher. If you do not want");
		printf(" to use this program, you can enter quit to stop this program.\n\n");
		break;
	case 1:
		printf("passwd\t\t\t\t\t\t//change password\n");
		printf("export [filename]\t\t\t\t//export course info\n");
		printf("courselist [s/+s/-s] [sort key]\t\t\t//list all the courses, sorted by the key\n");
		printf("choose [coursename(partial)/id]\t\t\t//choose a course\n");
		printf("drop [coursename(partial)/id]\t\t\t//drop a course\n");
		printf("search [coursename(partial)/id]\t\t\t//search a course to see its detailed information\n");
		printf("table\t\t\t\t\t\t//view course table\n");
		printf("creditsta\t\t\t\t\t//credit statistics\n");
		printf("clear\t\t\t\t\t\t//clear screen\n");
		printf("logout\t\t\t\t\t\t//log out\n");
		printf("quit\t\t\t\t\t\t//quit the system\n");
		break;
	case 2:
		printf("passwd\t\t\t\t\t\t//change password\n");
		printf("courselist [s/+s/-s] [sort key]\t\t\t//list all the courses, sorted by the key\n");
		printf("search [coursename(partial)/id]\t\t\t//search a course to see its detailed information\n");
		printf("import [filename]\t\t\t\t//import course info\n");
		printf("export [filename]\t\t\t\t//export course info\n");
		printf("usrlist\t\t\t\t\t\t//list all the users\n");
		printf("usrdel [username]\t\t\t\t//delete a user\n");
		printf("usradd\t\t\t\t\t\t//add a user\n");
		printf("delcourse [coursename(partial)/id]\t\t//delete a course\n");
		printf("update [coursename(partial)/id]\t\t\t//change a course\n");
		printf("addcourse\t\t\t\t\t//add a course\n");
		printf("changecredit [credit]\t\t\t\t//change total credit\n");
		printf("clear\t\t\t\t\t\t//clear screen\n");
		printf("logout\t\t\t\t\t\t//log out\n");
		printf("quit\t\t\t\t\t\t//quit the system\n");
		break;
	}
	return;
}
//0 for Syntax error, 1 for inadequate permision, 2 for invalid input
void printError(int type)
{
	changeCharColor(RED);
	if (type == 0)
		printf("Syntax error\n");
	if (type == 1)
		printf("Permision inadequate.\n");
	if (type == 2)
		printf("Invalid input\n");
	changeCharColor(WHITE);
	return;
}
//courses为排序数据库，key为排序字段，ascending代表是否升序，返回失败类型
int sort(db* courses, const char* key, bool ascending)
{
	db* i = returnToHead(courses);
	db* j = NULL;
	db* m = NULL;
	if (strcmp(key, "id") == 0)
	{
		while (i != NULL)
		{
			m = i;
			j = i->next;
			while (j != NULL)
			{
				if ((strcmp(readDataOfClass(m)->id, readDataOfClass(j)->id) > 0 && ascending) ||
					(strcmp(readDataOfClass(m)->id, readDataOfClass(j)->id) < 0 && !ascending))
					m = j;
				j = j->next;
			}
			swapNode(i, m);
			i = i->next;
		}
	}
	else if (strcmp(key, "name") == 0)
	{
		while (i != NULL)
		{
			m = i;
			j = i->next;
			while (j != NULL)
			{
				if ((strcmp(readDataOfClass(m)->name, readDataOfClass(j)->name) > 0 && ascending) ||
					(strcmp(readDataOfClass(m)->name, readDataOfClass(j)->name) < 0 && !ascending))
					m = j;
				j = j->next;
			}
			swapNode(i, m);
			i = i->next;
		}
	}
	else if (strcmp(key, "compusory") == 0)
	{
		while (i != NULL)
		{
			m = i;
			j = i->next;
			while (j != NULL)
			{
				if ((readDataOfClass(m)->Compulsory > readDataOfClass(j)->Compulsory && ascending) ||
					(readDataOfClass(m)->Compulsory < readDataOfClass(j)->Compulsory && !ascending))
					m = j;
				j = j->next;
			}
			swapNode(i, m);
			i = i->next;
		}
	}
	else if (strcmp(key, "credit") == 0)
	{
		while (i != NULL)
		{
			m = i;
			j = i->next;
			while (j != NULL)
			{
				if ((readDataOfClass(m)->credit > readDataOfClass(j)->credit && ascending) ||
					(readDataOfClass(m)->credit < readDataOfClass(j)->credit && !ascending))
					m = j;
				j = j->next;
			}
			swapNode(i, m);
			i = i->next;
		}
	}
	else if (strcmp(key, "max") == 0)
	{
		while (i != NULL)
		{
			m = i;
			j = i->next;
			while (j != NULL)
			{
				if ((readDataOfClass(m)->max > readDataOfClass(j)->max && ascending) ||
					(readDataOfClass(m)->max < readDataOfClass(j)->max && !ascending))
					m = j;
				j = j->next;
			}
			swapNode(i, m);
			i = i->next;
		}
	}
	else if (strcmp(key, "current") == 0)
	{
		while (i != NULL)
		{
			m = i;
			j = i->next;
			while (j != NULL)
			{
				if ((readDataOfClass(m)->current > readDataOfClass(j)->current && ascending) ||
					(readDataOfClass(m)->current < readDataOfClass(j)->current && !ascending))
					m = j;
				j = j->next;
			}
			swapNode(i, m);
			i = i->next;
		}
	}
	else if (strcmp(key, "classroom") == 0)
	{
		while (i != NULL)
		{
			m = i;
			j = i->next;
			while (j != NULL)
			{
				if ((strcmp(readDataOfClass(m)->classroom, readDataOfClass(j)->classroom) > 0 && ascending) ||
					(strcmp(readDataOfClass(m)->classroom, readDataOfClass(j)->classroom) < 0 && !ascending))
					m = j;
				j = j->next;
			}
			swapNode(i, m);
			i = i->next;
		}
	}
	else
		return -1;
}
//为username选择currentCourse，id为课程id，classname为课程名，table为课表，返回失败类型
int choose(db* currentCourse, char* username, char* id, classst table[7][5], char* classname)
{
	if (readDataOfClass(currentCourse)->current >= readDataOfClass(currentCourse)->max)
	{
		return -2;
	}
	char userFilename[30] = { 0 }, selectedFilename[30] = { 0 };
	generateConfigFile(userFilename, username);
	db* userDatabase = openDataBase(userFilename, 2);
	if (lookUp(userDatabase, id, 6, true) != NULL)
	{
		closeDatabase(userDatabase);
		return -1;
	}
	for (int i = 0; i < 6; i++)
	{
		int time = readDataOfClass(currentCourse)->times[i];
		if (time != 0 && table[(int)time / 10 - 1][time % 10 - 1].occupied == 1)
		{
			strcpy(classname, table[(int)time / 10 - 1][time % 10 - 1].name);
			return -3;
		}
	}

	userDatabase = insert(userDatabase, 2);
	strcpy(readString(userDatabase), id);
	fresh(userFilename, userDatabase, 2);
	closeDatabase(userDatabase);

	readDataOfClass(currentCourse)->current++;
	db* selectedDatabase = readDataOfClass(currentCourse)->stu;
	selectedDatabase = insert(readDataOfClass(currentCourse)->stu, 2);
	strcpy(readString(selectedDatabase), username);
	strcpy(userFilename, "");
	generateConfigFile(selectedFilename, id);
	fresh(selectedFilename, selectedDatabase, 2);
	fresh(COURSEFILE, currentCourse, 1);
	return 0;
}
//为username退掉currentCourse，id为课程id，返回失败类型
int drop(db* currentCourse, const char* username, char* id)
{

	char userFilename[30] = { 0 }, selectedFilename[30] = { 0 };
	generateConfigFile(userFilename, username);
	generateConfigFile(selectedFilename, id);
	db* userDatabase = openDataBase(userFilename, 2);
	db* courseTodel = lookUp(userDatabase, id, 6, true);
	if (courseTodel == NULL)
	{
		closeDatabase(userDatabase);
		return -1;
	}
	userDatabase = delNode(courseTodel);
	fresh(userFilename, userDatabase, 2);
	closeDatabase(userDatabase);

	db* selectedDatabase = readDataOfClass(currentCourse)->stu;
	readDataOfClass(currentCourse)->current--;

	readDataOfClass(currentCourse)->stu = delNode(lookUp(selectedDatabase, username, 6, true));
	fresh(selectedFilename, readDataOfClass(currentCourse)->stu, 2);
	return 0;
}
void loginSuccessfully(const char* username)
{
	if (strcmp(username, "admin") == 0)
		permision = 2;
	else
		permision = 1;
	printf("login successfully. Hello %s.\n", username);
}
void printHello()
{
	printf("                 ┌─────────────────────────────────────────────────┐\n");
	printf("                 │     Welcome to this Course selection system     │\n");
	printf("                 │                please log in                    │\n");
	printf("                 │                                                 │\n");
	printf("                 │  *If this is your first time to use this prog-  │\n");
	printf("                 │   gram, we will create a default administrator  │\n");
	printf("                 │   account for you. Please login with user name  │\n");
	printf("                 │   admin and password admin. You can enter help  │\n");
	printf("                 │   for more information.                         │\n");
	printf("                 └─────────────────────────────────────────────────┘\n");
	return;
}
//从filename导入课程，写入database数据库，返回数据库中的一个节点
db* import(db* database, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("No such file!\n");
		return NULL;
	}
	char line[50], id[7], name[20], classroom[15];
	int compulsory, number;
	float credit;
	char teacher[4][10];
	int times[6];
	db* current = NULL;
	while (!feof(fp))
	{
		fgets(line, 50, fp);
		sscanf(line, "%s%s%s", id, name, classroom);
		fgets(line, 50, fp);
		sscanf(line, "%d%f%d", &compulsory, &credit, &number);
		fgets(line, 50, fp);
		int count = sscanf(line, "%s%s%s%s", teacher[0], teacher[1], teacher[2], teacher[3]);
		fgets(line, 50, fp);
		int numberOfClasses = sscanf(line, "%d%d%d%d%d%d", times, times + 1, times + 2, times + 3, times + 4, times + 5);
		current = lookUp(database, id, 3, true);
		if (current == NULL)
		{
			if (countName(database, name) >= 4)
			{
				changeCharColor(RED);
				printf("There have already been enough courses named %s.", name);
				changeCharColor(WHITE);
				continue;
			}
			else
			{
				current = insert(database, 1);
				printf("import class with id %s.\n", id);
			}
		}
		else
		{
			changeCharColor(YELLOW);
			printf("class with id %s already exists, the old record will be overwritten.\n", id);
			closeDatabase(readDataOfClass(current)->stu);
			changeCharColor(WHITE);
		}
		for (int i = 0; i < 6; i++)
		{
			if (numberOfClasses >= i + 1)
				readDataOfClass(current)->times[i] = times[i];
			else
				readDataOfClass(current)->times[i] = 0;
		}
		readDataOfClass(current)->credit = credit;
		readDataOfClass(current)->current = 0;
		readDataOfClass(current)->max = number;
		readDataOfClass(current)->Compulsory = compulsory;
		strcpy(readDataOfClass(current)->id, id);
		strcpy(readDataOfClass(current)->name, name);
		strcpy(readDataOfClass(current)->classroom, classroom);
		readDataOfClass(current)->needToBeChoosen = 0;
		for (int i = 0; i < 4; i++)
		{
			if (count >= i + 1)
				strcpy(readDataOfClass(current)->teachers[i], teacher[i]);
			else
				strcpy(readDataOfClass(current)->teachers[i], "");
		}
		readDataOfClass(current)->stu = NULL;
	}
	fclose(fp);
	return current;
}
//为username更改密码，用户数据库为database
void changePassword(db* database, const char* username)
{
	char newPassword[20], repeatPassword[20];
	bool acked = false;
	while (!acked)
	{
		printf("New password:\n");
		getPassword(newPassword);
		printf("Repeat password:\n");
		getPassword(repeatPassword);
		if (strcmp(newPassword, repeatPassword) == 0)
		{
			acked = true;
		}
	}
	db* destination = lookUp(database, username, 1, true);
	strcpy(readDataOfUser(destination)->password, newPassword);
	fresh(USERFILE, database, 0);
	printf("Password changed successfully!\n");
	return;
}
//向database中添加用户，返回数据库中的一个节点
db* userAdd(db* database)
{
	char userToAdd[20], password[20];
	while (true)
	{
		printf("User name?\n");
		scanf("%s", userToAdd);
		if (strcmp(userToAdd, "quit") == 0 ||
			strcmp(userToAdd, "help") == 0 ||
			strcmp(userToAdd, "admin") == 0)
		{
			printf("Ilegal name!\n");
			continue;
		}
		else if (lookUp(database, userToAdd, 1, true) != NULL)
		{
			printf("User already exists!\n");
			continue;
		}
		else
			break;
	}
	printf("Password?(no longer than 20 characters)\n");
	scanf("%s", password);
	database = insert(database, 0);
	strcpy(readDataOfUser(database)->username, userToAdd);
	strcpy(readDataOfUser(database)->password, password);
	printf("Add user %s successfully!\n", userToAdd);
	fresh(USERFILE, database, 0);
	return database;
}
//列出所有用户
void listuser(db* database)
{
	printf("┌"); for (int i = 1; i <= 26; i++)printf("─"); printf("┐"); printf("\n");
	printf("│%-13s%-13s│\n", "username", "password");
	printf("├"); for (int i = 1; i <= 26; i++)printf("─"); printf("┤"); printf("\n");
	db* current = returnToHead(database);
	while (current != NULL)
	{
		printf("│%-13s%-13s│\n", readDataOfUser(current)->username, readDataOfUser(current)->password);
		current = current->next;
	}
	printf("└"); for (int i = 1; i <= 26; i++)printf("─"); printf("┘"); printf("\n");
	return;
}
//从database中删除username
void userDel(db*& database,db* courseDatabase, const char* username)
{
	db* destination = lookUp(database, username, 1, true);
	if (destination == NULL)
	{
		printf("No such user!\n");
	}
	else
	{
		char userConfFile[30] = { 0 };
		generateConfigFile(userConfFile, username);
		db* selectionDatabase = openDataBase(userConfFile, 2);
		db* current = returnToHead(selectionDatabase);
		while (current!=NULL)
		{
			drop(lookUp(courseDatabase, readString(current),3,true), username, readString(current));
			current = current->next;
		}
		closeDatabase(selectionDatabase);
		database = delNode(destination);
		fresh(USERFILE, database, 0);
		remove(userConfFile);
		printf("Deleted successfully!\n");
	}
	return;
}
//列出所有课程，username为当前用户，table为课程表
void listCourse(db* database, char* username, classst table[7][5])
{
	if (database == NULL)
	{
		printf("Cueerntly no course!\n");
		return;
	}
	db* current = returnToHead(database);
	char userFilename[20] = { 0 };
	bool timeAvaliable = true;
	generateConfigFile(userFilename, username);
	db* userdatabase = openDataBase(userFilename, 2);
	printf("┌"); for (int i = 1; i <= 91; i++)printf("─"); printf("┐"); printf("\n");
	printf("│%-8s%-21s%-11s%-7s%-16s%-8s%-10s%-10s│\n",
		"id", "name", "compulsory", "credit", "classroom", "number", "selected", "teacher");
	printf("├"); for (int i = 1; i <= 91; i++)printf("─"); printf("┤"); printf("\n");
	char currentProcessing[20] = { 0 };
	int needTo = 1;
	while (current != NULL)
	{
		readDataOfClass(current)->needToBeChoosen = 0;
		current = current->next;
	}
	current = returnToHead(database);
	while (current != NULL)
	{
		strcpy(currentProcessing, readDataOfClass(current)->name);
		if (readDataOfClass(current)->needToBeChoosen == 0 && strcmp(username, "admin") != 0)
		{
			db* tc = current;
			while (tc != NULL)
			{
				if (lookUp(readDataOfClass(tc)->stu, username, 6, true) != NULL)
				{
					needTo = 2;
					break;
				}
				else
				{
					tc = tc->next;
					tc = lookUp(tc, currentProcessing, 5, false);
				}
			}
			tc = current;
			while (tc != NULL)
			{
				readDataOfClass(tc)->needToBeChoosen = needTo;
				tc = tc->next;
				tc = lookUp(tc, currentProcessing, 5, false);
			}
			needTo = 1;

		}
		for (int i = 0; i < 6; i++)
		{
			int time = readDataOfClass(current)->times[i];
			if (time != 0 && table[(int)time / 10 - 1][time % 10 - 1].occupied == 1)
			{
				timeAvaliable = false;
				break;
			}
		}
		printf("│%-8s%-21s", readDataOfClass(current)->id, readDataOfClass(current)->name);
		if (readDataOfClass(current)->Compulsory == 0)
			printf("%-11s", "no");
		else
			printf("%-11s", "yes");
		printf("%-7.1f", readDataOfClass(current)->credit);
		printf("%-16s", readDataOfClass(current)->classroom);
		printf("%-8d", readDataOfClass(current)->max);
		if (permision == 1)
		{
			printf("%-4d", readDataOfClass(current)->current);
			char userFilename[30] = { 0 };
			generateConfigFile(userFilename, username);
			db* userDatabase = openDataBase(userFilename, 2);
			if (lookUp(userDatabase, readDataOfClass(current)->id, 6, true) != NULL)
			{
				changeCharColor(GREEN);
				printf("%-6s", "(*)");
				changeCharColor(WHITE);
			}
			else
			{
				if (readDataOfClass(current)->needToBeChoosen == 1)
				{
					if (readDataOfClass(current)->Compulsory == 1)
					{
						changeCharColor(RED);
						printf("%-6s", timeAvaliable ? "(*)" : "(-)");
						changeCharColor(WHITE);
					}
					else
					{
						if (timeAvaliable == false)
						{
							changeCharColor(RED);
							printf("%-6s", "(-)");
							changeCharColor(WHITE);
						}
						else
						{
							printf("%-6s", "");
						}
					}
				}
				else
				{
					printf("%-6s", "");
				}
			}
			closeDatabase(userDatabase);
		}
		else
			printf("%-10d", readDataOfClass(current)->current);
		if (strlen(readDataOfClass(current)->teachers[1]) == 0)
			printf("%-10s", readDataOfClass(current)->teachers[0]);
		else
			printf("%-7s%s", readDataOfClass(current)->teachers[0], "...");
		printf("│\n");
		current = current->next;
		timeAvaliable = true;
	}
	printf("└"); for (int i = 1; i <= 91; i++)printf("─"); printf("┘"); printf("\n");
	return;
}
//在database中手动添加课程，返回数据库中的一个节点
db* addCourse(db* database)
{
	char id[10], name[20], classroom[20], teacher[4][10];
	int compulsory, res, max, time[6] = { 0 };
	float credit;
	printf("id:");
	scanf("%s", id);
	if (lookUp(database, id, 3, true) != NULL)
	{
		printf("This course already exists.\n");
		return database;
	}
	printf("name:");
	scanf("%s", name);
	if (countName(database, name) >= 4)
	{
		printf("There have already been enough courses named %s.\n", name);
		return database;
	}
	printf("If compulsory? 1 for yes, 0 for no:");
	res = scanf("%d", &compulsory);
	if (res != 1 || (compulsory != 0 && compulsory != 1))
	{
		printError(2);
		return database;
	}
	printf("classroom:");
	scanf("%s", classroom);
	printf("Maximum number of people:");
	res = scanf("%d", &max);
	if (res != 1 || max <= 0)
	{
		printError(2);
		return database;
	}
	printf("Credit:");
	res = scanf("%f", &credit);
	if (res != 1 || credit <= 0)
	{
		printError(2);
		return database;
	}
	printf("Time( Ten digits are the number of weekdays and one digit is the number of sections.\nPrint 0 to stop):\n");
	for (int i = 0; i < 6; i++)
	{
		int a;
		res = scanf("%d", &a);
		if (a == 0)
		{
			break;
		}
		if (res != 1 ||
			a / 10 > 7 || a / 10 < 1 ||
			a % 10 > 5 || a % 10 < 1)
		{
			printError(2);
			i--;
		}
		else
		{
			time[i] = a;
		}
	}
	printf("teachers:\n");
	char line[50];
	getchar();
	gets_s(line);
	int count = sscanf(line, "%s%s%s%s", teacher[0], teacher[1], teacher[2], teacher[3]);

	db* current = insert(database, 1);
	readDataOfClass(current)->Compulsory = compulsory;
	strcpy(readDataOfClass(current)->classroom, classroom);
	for (int i = 0; i < 6; i++)
	{
		readDataOfClass(current)->times[i] = time[i];
	}
	readDataOfClass(current)->credit = credit;
	readDataOfClass(current)->current = 0;
	readDataOfClass(current)->max = max;
	readDataOfClass(current)->Compulsory = compulsory;
	strcpy(readDataOfClass(current)->id, id);
	strcpy(readDataOfClass(current)->name, name);
	strcpy(readDataOfClass(current)->classroom, classroom);
	readDataOfClass(current)->needToBeChoosen = 0;
	for (int i = 0; i < 4; i++)
	{
		if (count >= i + 1)
			strcpy(readDataOfClass(current)->teachers[i], teacher[i]);
		else
			strcpy(readDataOfClass(current)->teachers[i], "");
	}
	readDataOfClass(current)->stu = NULL;
	fresh(COURSEFILE, database, 1);
	printf("Add successfully\n");
	return current;
}
//打印database指向课程的详细信息
void printDetailed(db* database)
{
	printf("course id:\t\t%s\n", readDataOfClass(database)->id);
	printf("course name:\t\t%s\n", readDataOfClass(database)->name);
	if (readDataOfClass(database)->Compulsory == 0)
		printf("if compulsory:\t\tno\n");
	else
		printf("if compulsory:\t\tyes\n");
	printf("credit:\t\t\t%.1f\n", readDataOfClass(database)->credit);
	printf("classroom:\t\t%s\n", readDataOfClass(database)->classroom);
	printf("total number:\t\t%d\n", readDataOfClass(database)->max);
	printf("currently selected:\t%d\n", readDataOfClass(database)->current);
	printf("name list:\n");
	db* stu = returnToHead(readDataOfClass(database)->stu);
	while (stu != NULL)
	{
		printf("%s ", readString(stu));
		stu = stu->next;
	}
	printf("\n");
	printf("teachers:\t\t");
	int i = 0;
	while (strlen(readDataOfClass(database)->teachers[i]) != 0)
	{
		printf("%s  ", readDataOfClass(database)->teachers[i]);
		i++;
	}
	printf("\ntime table:\n");
	int tab[7][5] = { 0 }, a;
	for (i = 0; i < 6; i++)
	{
		a = readDataOfClass(database)->times[i];
		if (a != 0)
		{
			tab[(int)a / 10 - 1][a % 10 - 1] = 1;
		}
	}
	printf("\tMon Tue Wed Thu Fri Sat Sun\n");
	for (i = 0; i <= 4; i++)
	{
		printf("\t");
		for (int j = 0; j <= 6; j++)
		{
			if (tab[j][i] == 1)
			{
				printf("[*] ");
			}
			else
			{
				printf("[ ] ");
			}
		}
		printf("\n");
	}
}
//将database中的所有课程导出到filename
void exportData(db* database, const char* filename)
{
	FILE* fp = fopen(filename, "w");
	database = returnToHead(database);
	while (database != NULL)
	{
		fprintf(fp, "course id:\t\t%s\n", readDataOfClass(database)->id);
		fprintf(fp, "course name:\t\t%s\n", readDataOfClass(database)->name);
		if (readDataOfClass(database)->Compulsory == 0)
			fprintf(fp, "if compulsory:\t\tno\n");
		else
			fprintf(fp, "if compulsory:\t\tyes\n");
		fprintf(fp, "credit:\t\t\t%d\n", readDataOfClass(database)->credit);
		fprintf(fp, "classroom:\t\t%s\n", readDataOfClass(database)->classroom);
		fprintf(fp, "total number:\t\t%d\n", readDataOfClass(database)->max);
		fprintf(fp, "currently selected:\t%d\n", readDataOfClass(database)->current);
		fprintf(fp, "name list:\n");
		db* stu = returnToHead(readDataOfClass(database)->stu);
		while (stu != NULL)
		{
			fprintf(fp, "%s ", readString(stu));
			stu = stu->next;
		}
		fprintf(fp, "\n");
		fprintf(fp, "teachers:\t\t");
		int i = 0;
		while (strlen(readDataOfClass(database)->teachers[i]) != 0)
		{
			fprintf(fp, "%s  ", readDataOfClass(database)->teachers[i]);
			i++;
		}
		fprintf(fp, "\ntime table:\n");
		int tab[7][5] = { 0 }, a;
		for (i = 0; i < 6; i++)
		{
			a = readDataOfClass(database)->times[i];
			if (a != 0)
			{
				tab[(int)a / 10 - 1][a % 10 - 1] = 1;
			}
		}
		fprintf(fp, "\tMon Tue Wed Thu Fri Sat Sun\n");
		for (i = 0; i <= 4; i++)
		{
			fprintf(fp, "\t");
			for (int j = 0; j <= 6; j++)
			{
				if (tab[j][i] == 1)
				{
					fprintf(fp, "[*] ");
				}
				else
				{
					fprintf(fp, "[ ] ");
				}
			}
			fprintf(fp, "\n");
		}
		database = database->next;
		fprintf(fp, "---------------------------------------\n");
	}
	fclose(fp);
	return;
}
//为username选择关键字为id的课程，courses为课程数据库，table为课表
void chooseCourse(db* courses, char* username, char* id, classst table[7][5])
{
	char clashname[20];
	db* classDatabase = lookUp(courses, id, 3, true);
	if (classDatabase != NULL)
	{
		if (lookUp(courses, id, 4, true) != NULL)
		{
			printf("Multiple choices exist, please use id.\n");
			return;
		}
	}
	else
	{
		db* db1 = lookUp(courses, id, 4, true);
		if (db1 == NULL)
		{
			printf("No such class!\n");
			return;
		}
		else
		{
			if (lookUp(db1->next, id, 4, false) == NULL)
			{
				classDatabase = db1;
			}
			else
			{
				printf("Multiple choices exist, please use id.\n");
				return;
			}
		}
	}
	int result = choose(classDatabase, username, readDataOfClass(classDatabase)->id, table, clashname);
	if (result == -1)
	{
		printf("Already choosen.\n");
	}
	else if (result == -2)
	{
		printf("There have already been enough students.\n");
	}
	else if (result == -3)
	{
		printf("The time of the class clashes with that of %s.\n", clashname);
	}
	else
	{
		printf("Select %s successfully.\n", readDataOfClass(classDatabase)->name);
	}
	return;
}
//为username退掉关键字为id的课程，courses为课程数据库
void dropCourse(db* courses, char* username, char* key)
{
	db* classDatabase = lookUp(courses, key, 3, true);//search id
	int selected = 0;
	db* db1 = NULL;
	if (classDatabase != NULL && lookUp(readDataOfClass(classDatabase)->stu, username, 6, true) != NULL)
	{
		selected = 1;
	}
	else
	{
		db1 = lookUp(courses, key, 4, true);
		if (db1 == NULL)
		{
			printf("No such class!\n");
			return;
		}
		else
		{
			db* db2 = db1;
			while (db2 != NULL)
			{
				db2 = lookUp(db2->next, key, 4, false);
				if (db2 == NULL)
				{
					if (lookUp(readDataOfClass(db1)->stu, username, 6, true) != NULL)
					{
						classDatabase = db1;
						selected = 1;
					}
				}
				else
				{
					if (strcmp(readDataOfClass(db1)->name, readDataOfClass(db2)->name) != 0)
					{
						printf("Multiple choices exist, please use id.\n");
						return;
					}
					else if (selected == 0)
					{
						if (lookUp(readDataOfClass(db2)->stu, username, 6, true) != NULL)
						{
							selected = 1;
							classDatabase = db2;
						}
					}
				}
			}
		}
	}
	if (selected == 0)
	{
		printf("Haven't been choosen.\n");
		return;
	}
	int result = drop(classDatabase, username, readDataOfClass(classDatabase)->id);
	if (result == -1)
	{
		printf("Haven't been choosen.\n");
	}
	else
	{
		printf("Drop %s successfully.\n", readDataOfClass(classDatabase)->name);
	}
	return;
}
void initClassTable(char* username, classst table[7][5], db* courses)
{
	char userConfigFilename[30] = { 0 };
	generateConfigFile(userConfigFilename, username);
	db* userdatabase = openDataBase(userConfigFilename, 2);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			table[i][j].occupied = 0;
		}
	}
	userdatabase = returnToHead(userdatabase);
	while (userdatabase != NULL)
	{
		db* current = lookUp(courses, readString(userdatabase), 3, true);
		for (int i = 0; i < 7; i++)
		{
			int time = readDataOfClass(current)->times[i];
			if (time != 0)
			{
				table[(int)time / 10 - 1][time % 10 - 1].occupied = 1;
				strcpy(table[(int)time / 10 - 1][time % 10 - 1].name, readDataOfClass(current)->name);
			}
		}
		userdatabase = userdatabase->next;
	}
}
//画出table
void drawClassTable(classst table[7][5])
{
	printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (table[j][i].occupied == 1)
			{
				if (strlen(table[j][i].name) <= 13)
				{
					printf("[%-13s]", table[j][i].name);
				}
				else
				{
					printf("[");
					for (int l = 0; l < 11; l++)
					{
						printf("%c", table[j][i].name[l]);
					}
					printf("...]");
				}
			}
			else
			{
				printf("[%-13s]", "");
			}
		}
		printf("\n");
	}
}
//返回选修课所需学分
float getTotalCredit()
{
	char filename[30] = { 0 };
	generateConfigFile(filename, "_credit");
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		totalCredit = 20;
	}
	else
	{
		fscanfc(fp, "%f", &totalCredit);
	}
	return totalCredit;
}
//将选修课所需学分改为credit
void setTotalCredit(float credit)
{
	char filename[30] = { 0 };
	generateConfigFile(filename, "_credit");
	FILE* fp = fopen(filename, "w");
	fprintfc(fp, "%f", credit);
	printf("Changed successfully.\n");
	fclose(fp);
	totalCredit = credit;
	return;
}
//统计username的学分，database为课程数据库
void creditStatistic(db* database, const char* username)
{
	int  t = 0;
	float credit = 0.0f;
	char userFilename[30] = { 0 };
	generateConfigFile(userFilename, username);
	db* userDatabase = returnToHead(openDataBase(userFilename, 2));
	db* current = userDatabase;
	while (current != NULL)
	{
		db* tc = lookUp(database, readString(current), 3, true);
		if (readDataOfClass(tc)->Compulsory == 0)
		{
			credit += readDataOfClass(tc)->credit;
		}
		current = current->next;
	}
	char currentProcessing[20] = { 0 };
	int needTo = 1;
	current = returnToHead(database);
	while (current != NULL)
	{
		readDataOfClass(current)->needToBeChoosen = 0;
		current = current->next;
	}
	current = returnToHead(database);
	while (current != NULL)
	{
		strcpy(currentProcessing, readDataOfClass(current)->name);
		if (readDataOfClass(current)->needToBeChoosen == 0)
		{
			db* tc = current;
			while (tc != NULL)
			{
				if (lookUp(userDatabase, readDataOfClass(tc)->id, 6, true) != NULL)
				{
					needTo = 2;
					break;
				}
				else
				{
					tc = tc->next;
					tc = lookUp(tc, currentProcessing, 5, false);
				}
			}
			tc = current;
			while (tc != NULL)
			{
				readDataOfClass(tc)->needToBeChoosen = needTo;
				needTo++;
				tc = tc->next;
				tc = lookUp(tc, currentProcessing, 5, false);
			}
		}
		userDatabase = returnToHead(userDatabase);
		if (readDataOfClass(current)->needToBeChoosen == 1 &&
			readDataOfClass(current)->Compulsory == 1)
		{
			changeCharColor(RED);
			printf("Class %s needs to be chosen.\n", readDataOfClass(current)->name);
			t = 1;
			changeCharColor(WHITE);
		}
		current = current->next;
		needTo = 1;
	}
	if (t == 0)
	{
		printf("All the compulsory courses are chosen.\n");
	}
	printf("Total credit of elective courses is %.1f. Your credit is ", totalCredit);
	if (totalCredit > credit)
	{
		changeCharColor(RED);
		printf("%.1f", credit);
		changeCharColor(WHITE);
		printf(".\n");
		changeCharColor(RED);
		printf("Your credit of elective courses is not enough.\n");
		changeCharColor(WHITE);
	}
	else
	{
		printf("%.1f.\nYour credit of elective courses is enough.\n", credit);
	}
	closeDatabase(userDatabase);
	return;
}
//修改database中id为key的课程
void update(db* database, const char* key)
{
	char clashname[20];
	db* classDatabase = lookUp(database, key, 3, true);
	if (classDatabase != NULL)
	{
		if (lookUp(database, key, 4, true) != NULL)
		{
			printf("Multiple choices exist, please use id.\n");
			return;
		}
	}
	else
	{
		db* db1 = lookUp(database, key, 4, true);
		if (db1 == NULL)
		{
			printf("No such class!\n");
			return;
		}
		else
		{
			if (lookUp(db1->next, key, 4, false) == NULL)
			{
				classDatabase = db1;
			}
			else
			{
				printf("Multiple choices exist, please use id.\n");
				return;
			}
		}
	}
	printf("The field to change:");
	char target[20];
	scanf("%s", target);
	if (strcmp(target, "id") == 0)
	{
		printf("The id field is unchangable, please create a new class to change it.\n");
		return;
	}
	else if (strcmp(target, "name") == 0)
	{
		char name[20];
		printf("name:");
		scanf("%s", name);
		strcpy(readDataOfClass(classDatabase)->name, name);
	}
	else if (strcmp(target, "compulsory") == 0)
	{
		int compulsory;
		printf("If compulsory? 1 for yes, 0 for no:");
		int res = scanf("%d", &compulsory);
		if (res != 1 || (compulsory != 0 && compulsory != 1))
		{
			printError(2);
			return;
		}
		readDataOfClass(classDatabase)->Compulsory = compulsory;
	}
	else if (strcmp(target, "classroom") == 0)
	{
		char classroom[20];
		printf("classroom:");
		scanf("%s", classroom);
		printf("Maximum number of people:");
		strcpy(readDataOfClass(classDatabase)->classroom, classroom);
	}
	else if (strcmp(target, "max") == 0)
	{
		int max, res;
		printf("Maximum number of people:");
		res = scanf("%d", &max);
		if (res != 1 || max <= 0)
		{
			printError(2);
			return;
		}
		readDataOfClass(classDatabase)->max = max;
	}
	else if (strcmp(target, "credit") == 0)
	{
		int res;
		float credit;
		printf("Credit:");
		res = scanf("%f", &credit);
		if (res != 1 || credit <= 0)
		{
			printError(2);
			return;
		}
		readDataOfClass(classDatabase)->credit = credit;

	}
	else if (strcmp(target, "teacher") == 0)
	{
		char teacher[4][10];
		printf("teachers:\n");
		char line[50];
		getchar();
		gets_s(line);
		int count = sscanf(line, "%s%s%s%s", teacher[0], teacher[1], teacher[2], teacher[3]);
		for (int i = 0; i < 4; i++)
		{
			if (count >= i + 1)
				strcpy(readDataOfClass(classDatabase)->teachers[i], teacher[i]);
			else
				strcpy(readDataOfClass(classDatabase)->teachers[i], "");
		}
	}
	else if (strcmp(target, "time") == 0)
	{
		int res, a, time[6] = { 0 };
		printf("Time( Ten digits are the number of weekdays and one digit is the number of sections.\nPrint 0 to stop):\n");
		for (int i = 0; i < 6; i++)
		{
			int a;
			res = scanf("%d", &a);
			if (a == 0)
			{
				break;
			}
			if (res != 1 ||
				a / 10 > 7 || a / 10 < 1 ||
				a % 10 > 5 || a % 10 < 1)
			{
				printError(2);
				i--;
			}
			else
			{
				time[i] = a;
			}
		}
		for (int i = 0; i < 6; i++)
		{
			readDataOfClass(classDatabase)->times[i] = time[i];
		}
	}
	else
	{
		printError(2);
		return;
	}
	printf("Update %s successfully!",readDataOfClass(classDatabase)->name);
	fresh(COURSEFILE, classDatabase, 1);
	return;
}
//删除courses中关键字为key的课程
void courseDel(db*& courses, char* key)
{
	char clashname[20];
	db* classDatabase = lookUp(courses, key, 3, true);
	if (classDatabase != NULL)
	{
		if (lookUp(courses, key, 4, true) != NULL)
		{
			printf("Multiple choices exist, please use id.\n");
			return;
		}
	}
	else
	{
		db* db1 = lookUp(courses, key, 4, true);
		if (db1 == NULL)
		{
			printf("No such class!\n");
			return;
		}
		else
		{
			if (lookUp(db1->next, key, 4, false) == NULL)
			{
				classDatabase = db1;
			}
			else
			{
				printf("Multiple choices exist, please use id.\n");
				return;
			}
		}
	}
	char studentFilename[30] = { 0 }, classFilename[30] = { 0 };
	db* selectedDatabase = readDataOfClass(classDatabase)->stu;
	db* current = returnToHead(selectedDatabase);
	while (current != NULL)
	{
		drop(classDatabase, readString(current), readDataOfClass(classDatabase)->id);
		current = current->next;
	}
	generateConfigFile(classFilename, readDataOfClass(classDatabase)->id);
	remove(classFilename);
	courses = delNode(classDatabase);
	printf("Deleted successfully.\n");
}