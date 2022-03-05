#pragma once
typedef struct node
{
	struct node* previous;
	void* data;
	struct node* next;
} db;
typedef struct courseinfo
{
	db* stu;
	char id[7];
	char name[20];
	int Compulsory;//1 is Compulsory
	float credit;
	int times[6];
	int max;
	int current;
	char classroom[15];
	char teachers[4][10];
	int needToBeChoosen;
}course;
typedef struct userinfo
{
	char username[10];
	char password[10];
}user;
typedef struct Classst
{
	bool occupied;
	char name[10];
}classst;


inline course* readDataOfClass(db* database)
{
	return (course*)database->data;
}
inline user* readDataOfUser(db* database)
{
	return (user*)database->data;
}
inline char* readString(db* database)
{
	return (char*)database->data;
}