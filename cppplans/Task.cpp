#include <tchar.h>
#include <vector>
#include <iostream>

using namespace std;

class Task
{
	TCHAR* date;
	TCHAR* time;
	int priority;
	//vector<TCHAR*> tags;
	TCHAR* tags;
	TCHAR* commentary;

public:
	Task(TCHAR* Date, TCHAR* Time, int Prio, TCHAR* Tags, TCHAR* Comment)
	{
		date = Date;
		time = Time;
		priority = Prio;
		tags = Tags;
		commentary = Comment;
	}

	TCHAR* GetCommentary()
	{
		return commentary;
	}
};