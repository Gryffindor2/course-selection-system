#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include<stdio.h>
#include<string.h>
#include"datastruct.h"
#include"consts.h"
#include"extern_functions.h"
#include"database.h"
//this flag is to indicate the permision of the current user
//0 refers to not logging in, 1 refers to student, 2 refers to teacher.
int permision = 0;
float totalCredit = 10.0f;

int main(int argc, char* argv[])
{
	testDir("./data");
	printHello();
	db* users = openDataBase(USERFILE, 0);
	db* courses = openDataBase(COURSEFILE, 1);
	getTotalCredit();
	classst classTable[7][5];
login:
	char password[20], username[20];
	db* userToLogIn = NULL;
	while (permision==0)
	{
         printf("user name:");
		 scanf("%s", username);
		 if (strcmp(username, "quit") == 0)
			 return 0;
		 else if (strcmp(username, "help") == 0)
		 {
			 printhelp();
			 continue;
		 }
		 else if (strcmp(username, "admin") == 0)
		 {
			 userToLogIn = lookUp(users, "admin", 1, true);
			 if (userToLogIn == NULL)
			 {
				 db* target = insert(users, 0);
				 strcpy(readDataOfUser(target)->username, "admin");
				 strcpy(readDataOfUser(target)->password, "admin");
				 userToLogIn = target;
			 }
		 }
		 else
		 {
			userToLogIn = lookUp(users, username, 1,true);
			if (userToLogIn ==NULL)
			{
				 printf("No such user!\n");
				 continue;
			 }
		 }			 
		 while (permision == 0)
		 {
			 printf("password:");
			 getPassword(password);
			 if (strcmp(password, readDataOfUser(userToLogIn)->password) == 0)
			 {
				 loginSuccessfully(username);
				 if (strcmp(password, "admin") == 0)
				 {
					 printf("*REMEMBER TO CHANGE THE DEFAULT PASSWORD*\n");
					 changePassword(users, "admin");
				 }
			 }
			 else
				 printf("wrong password.\n");
		 }
	}
//main loop
	char command[70],s[30], o1[20], o2[20];
	while (true)
	{
		int match = 0;
		printf("> ");
		do {
			gets_s(command);
			int i = 0;
			while (command[i]!='\0')
			{
				if (command[i] <= 'Z' && command[i] >= 'A')
					command[i] += 32;
				i++;
			}
			match = sscanf(command, "%s%s%s", s, o1, o2);
		} while (match<=-1);
		if (strcmp(s, "import") == 0)
		{
			if (permision == 2)
			{
				if (match == 2);
				else if (match == 1)
				{
					printf("From which file?\n");
					scanf("%s", o1);
				}
				else
				{
					printError(0);
					continue;
				}
				courses = import(courses, o1);
				if (courses != NULL)
				{
					fresh(COURSEFILE, courses, 1);
					listCourse(courses, username, classTable);
				}
			}
			else
			{
				printError(1);
			}
		}
		else if (strcmp(s, "update") == 0)
		{
			if (permision == 2)
			{
				if (match == 2);
				else if (match == 1)
				{
					printf("Key?\n");
					scanf("%s", o1);
				}
				else
				{
					printError(0);
					continue;
				}
				update(courses,o1);
			}
			else
			{
				printError(1);
			}
		}
		else if (strcmp(s, "quit") == 0)
		{
			if (match == 1)
			{
				clearScreen();
				return 0;
			}
			else
				printError(0);
		}
		else if (strcmp(s, "logout") == 0)
		{
			if (match == 1)
			{
				clearScreen();
				permision = 0;
				goto login;
			}
			else
				printError(0);
		}
		else if (strcmp(s, "usradd") == 0)
		{
			if (permision == 2)
			{
				if (match == 1)
				{
					users = userAdd(users);
					listuser(users);
				}
				else
					printError(0);
			}
			else
				printError(1);
		}
		else if (strcmp(s, "changecredit") == 0)
		{
			float creditToChange;
			if (permision == 2)
			{
				if (match == 1)
				{
					printf("credit:");
					int res = scanf("%f", &creditToChange);
					if (res != 1)
					{
						printError(0);
						continue;
					}
				}
				else if (match == 2)
				{
					int res = sscanf(o1, "%f", &creditToChange);
					if (res != 1 || creditToChange < 0)
					{
						printError(0);
						continue;
					}
				}
				else
				{
					printError(0);
					continue;
				}
				setTotalCredit(creditToChange);
			}
			else
				printError(1);
		}
		else if (strcmp(s, "clear") == 0)
		{
			if (match == 1)
			{
				clearScreen();
				continue;
			}
			else
				printError(0);
		}
		else if (strcmp(s, "passwd") == 0)
		{
			changePassword(users, username);
		}
		else if (strcmp(s, "help") == 0)
		{
			if (match == 1)
				printhelp();
			else
				printError(0);
		}
		else if (strcmp(s, "usrlist") == 0)
		{
			if (permision==2)
			{
				listuser(users);
			}
			else
			{
				printError(1);
			}
		}
		else if (strcmp(s, "usrdel") == 0)
		{
			if (permision == 2)
			{
				if (match == 2);
				else if (match == 1)
				{
					printf("user to  delete:\n");
					scanf("%s", o1);
				}
				else
				{
					printError(0);
					continue;
				}
				userDel(users,courses, o1);
				listuser(users);
			}
			else
				printError(1);
		}
		else if (strcmp(s, "courselist") == 0)
		{
			if (match == 1);	
			else if (match == 3)
			{
				bool ascending = true;
				if (strcmp(o1, "+s") == 0 || strcmp(o1, "s") == 0)
				{
					ascending = true;
				}
				else if (strcmp(o1, "-s") == 0)
				{
					ascending = false;
				}
				else
				{
					printError(0);
					continue;
				}
				if (sort(courses, o2, ascending) == -1)
				{
					printf("Invalid key\n");
					continue;
				}
			}
			else
			{
				printError(0);
				continue;
			}
			initClassTable(username, classTable, courses);
			listCourse(courses, username,classTable);
		}
		else if (strcmp(s, "addcourse") == 0)
		{
			if (permision == 2)
			{
				if (match == 1)
				{
					courses = addCourse(courses);
					listCourse(courses, username, classTable);
				}
				else
					printError(0);
			}
			else
				printError(1);
		}
		else if (strcmp(s, "search")==0)
		{
			if (match == 2);
			else if (match==1)
			{
				printf("key:");
				char id[10];
				scanf("%s", id);
				strcpy(o1, id);
			}
			else
			{
				printf("Syntax error\n");
				continue;
			}
			bool found = false;
			db* temp = lookUp(courses, o1, 3,true),*occupied=NULL;
			if (temp == NULL);
			else
			{
				found = true;
				printDetailed(temp);
				occupied = temp;
			}
			temp= lookUp(courses, o1, 4, true);
			while (temp!=NULL)
			{
				if (temp!=occupied)
				{
					found = true;
					printDetailed(temp);
				}
				temp =temp->next;
				temp = lookUp(temp, o1, 4, false);
			} 
			if (!found)
			{
				printf("No such course!\n");
			}
		}
		else if (strcmp(s, "export") == 0)
		{
			if (match == 1)
			{
				printf("destination:");
				char filename[10];
				scanf("%s", o1);
			}
			if (match == 2);
			else
			{
				printf("Syntax error\n");
				continue;
			}
			exportData(courses,o1);
		}
		else if (strcmp(s, "choose") == 0)
		{
			if (permision==2)
			{
				printf("This function is made for students.\n");
			}
			else
			{
				if (match == 2);
				else if (match == 1)
				{
					printf("id:");
					char id[10];
					scanf("%s", id);
					strcpy(o1,id);
				}
				else
				{
					printError(0);
					continue;
				}
				initClassTable(username, classTable, courses);
				chooseCourse(courses,username,o1,classTable);
			}
		}
		else if (strcmp(s, "drop") == 0)
		{
			if (permision == 2)
			{
				printf("This function is made for students.\n");
			}
			else
			{
				if (match == 2);
				else if (match == 1)
				{
					printf("id:");
					char id[10];
					scanf("%s", id);
					strcpy(o1, id);
				}
				else
				{
					printError(0);
					continue;
				}
				dropCourse(courses, username, o1);
			}
		}
		else if (strcmp(s, "creditsta") == 0)
		{
			if (permision == 2)
			{
				printf("The needed credit of elective classes is %.1f.\n",totalCredit);
			}
			else
			{
				if (match == 1)
				{
					creditStatistic(courses,username);
				}
				else
				{
					printError(0);
					continue;
				}
			}
		}
		else if (strcmp(s, "table") == 0)
		{
			if (permision == 2)
			{
				printf("This function is made for students.\n");
			}
			else
			{
				if (match == 1)
				{
					initClassTable(username, classTable, courses);
					drawClassTable(classTable);
				}
				else
				{
					printError(0);
					continue;
				}
			}
		}
		else if (strcmp(s, "delcourse") == 0)
		{
			if (permision == 2)
			{
				if (match == 2);
				else if (match == 1)
				{
					printf("course to  delete:\n");
					scanf("%s", o1);
				}
				else
				{
					printError(0);
					continue;
				}
				courseDel(courses, o1);
				fresh(COURSEFILE, courses, 0);
				listCourse(courses,username,classTable);
			}
			else
				printError(1);
		}
		else if (strcmp(s, "credit") == 0)
		{
			if (match == 1)
			{
				printf("%.1f", totalCredit);
			}
			else
			{
				printError(0);
			}
		}
		else
		{
			printError(2);
		}
		printf("\n");
	}
	return -1;//occurs error
}