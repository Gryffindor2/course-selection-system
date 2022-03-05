#pragma once
#include"datastruct.h"
extern db* returnToHead(db* database);
extern void closeDatabase(db* database);
extern db* insert(db*& current, int type);
extern void fresh(const char* filename, db* database, int type);
extern db* delNode(db* node);
extern db* openDataBase(const char* filename, int type);
extern void swapNode(db*& node1, db*& node2);
extern db* lookUp(db* database, const char* key, int symble, bool fromBegin);
extern int countName(db* database, const char* key);
