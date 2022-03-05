#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif 
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"datastruct.h"
#include"encryption.h"

extern bool isSubStr(const char* s1, const char* s2);
extern void generateConfigFile(char* destination, const char* name);

//database operation
//The type represent the data type. 0 is for account, 1 is for course, 2 is for pure text.


//返回首元素
db* returnToHead(db* database)
{
	if (database == NULL)
	{
		return NULL;
	}
	db* current = database;
	while (current->previous != NULL)
	{
		current = current->previous;
	}
	return current;
}

void closeDatabase(db* database)
{
	db* current = returnToHead(database);
	while (current != NULL)
	{
		db* temp = current->next;
		free(current->data);
		free(current);
		current = temp;
	}
	return;
}
//在current之后插入一个元素，类型由type决定
db* insert(db*& current, int type)
{
	db* database = (db*)malloc(sizeof(db));
	if (current == NULL)
	{
		database->next = NULL;
		database->previous = NULL;
		current = database;
	}
	else
	{
		db* temp = current->next;
		current->next = database;
		database->next = temp;
		if (database->next != NULL)
			database->next->previous = database;
		database->previous = current;
	}
	if (type == 0)
		database->data = malloc(sizeof(user));
	else  if (type == 1)
		database->data = malloc(sizeof(course));
	else if (type == 2)
		database->data = malloc(sizeof(char[20]));
	return database;
}
//将database写到filename指定的文件中，类型由type决定
void fresh(const char* filename, db* database, int type)
{
	db* current = returnToHead(database);
	FILE* fp = fopen(filename, "w");
	while (current != NULL)
	{
		if (type == 0)
		{
			fprintfc(fp, "%s %s", readDataOfUser(current)->username, readDataOfUser(current)->password);
		}
		else if (type == 1)
		{
			fprintfc(fp, "%s %s %s", readDataOfClass(current)->id,
				readDataOfClass(current)->name,
				readDataOfClass(current)->classroom);
			fprintfc(fp, "%d %.1f %d %d", readDataOfClass(current)->Compulsory,
				readDataOfClass(current)->credit,
				readDataOfClass(current)->max,
				readDataOfClass(current)->current);
			fprintfc(fp, "%s %s %s %s", readDataOfClass(current)->teachers[0],
				readDataOfClass(current)->teachers[1],
				readDataOfClass(current)->teachers[2],
				readDataOfClass(current)->teachers[3]);
			fprintfc(fp, "%d %d %d %d %d %d", readDataOfClass(current)->times[0],
				readDataOfClass(current)->times[1],
				readDataOfClass(current)->times[2],
				readDataOfClass(current)->times[3],
				readDataOfClass(current)->times[4],
				readDataOfClass(current)->times[5]);
		}
		else if (type == 2)
		{
			fprintfc(fp, "%s", readString(current));
		}
		current = current->next;
	}
	fclose(fp);
	return;
}
//删除node，返回删除后数据库中的一个元素
db* delNode(db* node)
{
	if (node == NULL)
		return NULL;
	else
	{
		if (node->previous == NULL && node->next == NULL)
		{
			free(node->data);
			free(node);
			return NULL;
		}
		if (node->previous == NULL)
		{
			db* nex = node->next;
			node->next->previous = NULL;
			free(node->data);
			free(node);
			return nex;
		}
		if (node->next == NULL)
		{
			db* pre = node->previous;
			node->previous->next = NULL;
			free(node->data);
			free(node);
			return pre;
		}
		db* pre = node->previous;
		db* nex = node->next;
		node->previous->next = nex;
		node->next->previous = pre;
		free(node->data);
		free(node);
		return nex;
	}
}
//从filename读取database，返回数据库中的一个元素，类型由type决定
db* openDataBase(const char* filename, int type)
{
	db* database = NULL;
	db* current = NULL;
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL)
		fp = fopen(filename, "w+");
	if (type == 0)
	{
		user tempUser;
		while (fscanfc(fp, "%s %s", &(tempUser.username), &(tempUser.password)) > 0)
		{
			current = insert(current, 0);
			if (database == NULL)
			{
				database = current;
			}
			user* destination = readDataOfUser(current);
			strcpy(destination->username, tempUser.username);
			strcpy(destination->password, tempUser.password);
		}
	}
	else if (type == 1)
	{
		course tempCourse;
		while (fscanfc(fp, "%s %s %s", tempCourse.id, tempCourse.name, tempCourse.classroom) > 0)
		{
			current = insert(current, 1);
			if (database == NULL)
			{
				database = current;
			}
			course* destination = readDataOfClass(current);
			strcpy(destination->id, tempCourse.id);
			strcpy(destination->name, tempCourse.name);
			strcpy(destination->classroom, tempCourse.classroom);
			fscanfc(fp, "%d %f %d %d", &destination->Compulsory, &destination->credit, &destination->max, &destination->current);
			int count = fscanfc(fp, "%s %s %s %s", tempCourse.teachers[0], tempCourse.teachers[1], tempCourse.teachers[2], tempCourse.teachers[3]);
			for (int i = 0; i < 4; i++)
			{
				if (count >= i + 1)
				{
					strcpy(destination->teachers[i], tempCourse.teachers[i]);
				}
				else
				{
					strcpy(destination->teachers[i], "");
				}
			}
			fscanfc(fp, "%d %d %d %d %d %d", destination->times,
				destination->times + 1,
				destination->times + 2,
				destination->times + 3,
				destination->times + 4,
				destination->times + 5);
			char confFilename[30] = { 0 };
			generateConfigFile(confFilename, readDataOfClass(current)->id);
			readDataOfClass(current)->stu = openDataBase(confFilename, 2);
			readDataOfClass(current)->needToBeChoosen = 0;
		}
	}
	else if (type == 2)
	{
		char s[10];
		while (fscanfc(fp, "%s", s) > 0)
		{
			current = insert(current, 2);
			if (database == NULL)
			{
				database = current;
			}
			char* destination = readString(current);
			strcpy(destination, s);
		}
	}
	fclose(fp);
	return database;
}
//交换node1和node2
void swapNode(db*& node1, db*& node2)
{
	void* cpyDataOfNode2 = node2->data;
	node2->data = node1->data;
	node1->data = cpyDataOfNode2;
}

/*symble refers to the field you want to search
1 refers to username (accurate)
3 refers to id (accurate), 4 refers to name, 5 refer to  accurate name search
6 refers to search a string*/
db* lookUp(db* database, const char* key, int symble, bool fromBegin)
{
	db* current = NULL;
	if (fromBegin)
		current = returnToHead(database);
	else
		current = database;
	while (current != NULL)
	{
		if (symble == 1)
		{
			if (_stricmp(readDataOfUser(current)->username, key) == 0)
				return current;
			current = current->next;
		}
		else if (symble == 3)
		{
			if (_stricmp(readDataOfClass(current)->id, key) == 0)
				return current;
			else
				current = current->next;
		}
		else if (symble == 4)
		{
			if (isSubStr(readDataOfClass(current)->name, key) == true)
				return current;
			else
				current = current->next;
		}
		else if (symble == 5)
		{
			if (_stricmp(readDataOfClass(current)->name, key) == 0)
				return current;
			else
				current = current->next;
		}
		else if (symble == 6)
		{
			if (_stricmp(readString(current), key) == 0)
			{
				return current;
			}
			else
			{
				current = current->next;
			}
		}
		else
			return NULL;
	}
	return NULL;
}
//统计名字为key的课程数量
int countName(db* database, const char* key)
{
	int sum = 0;
	db* current = returnToHead(database);
	while (current!=NULL)
	{
		if (strcmp(readDataOfClass(current)->name,key)==0)
		{
			sum++;
		}
		current = current->next;
	}
	return sum;
}