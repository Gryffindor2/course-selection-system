#pragma once
#include<stdio.h>


extern void testDir(const char* dir);
extern void clearScreen();
extern void getPassword(char* password);
extern void printhelp();
extern void printError(int type);
extern int sort(db* courses, const char* key, bool ascending);
extern int choose(db* currentCourse, char* username, char* id, classst table[7][5], char* classname);
extern void loginSuccessfully(const char* username);
extern void printHello();
extern db* import(db* database, const char* filename);
extern void changePassword(db* database, const char* username);
extern db* userAdd(db* database);
extern void listuser(db* database);
extern void userDel(db*& database, db* courseDatabase, const char* username);
extern void listCourse(db* database, char* username, classst table[7][5]);
extern db* addCourse(db* database);
extern void printDetailed(db* database);
extern void exportData(db* database, const char* filename);
extern void chooseCourse(db* courses, char* username, char* id, classst table[7][5]);
extern void dropCourse(db* courses, char* username, char* key);
extern void initClassTable(char* username, classst table[7][5], db* courses);
extern void drawClassTable(classst table[7][5]);
extern float getTotalCredit();
extern void setTotalCredit(float credit);
extern void creditStatistic(db* database, const char* username);
extern void update(db* database, const char* key);
extern void courseDel(db*& courses, char* key);