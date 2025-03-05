#include <windows.h>
#include <codecvt>
#include <tchar.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Task
{
	TCHAR* date;
	TCHAR* time;
	int priority;
	TCHAR* tags;
	TCHAR* commentary;

public:
	Task() : Task(nullptr, nullptr, -1, nullptr, nullptr)
	{

	}

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

	TCHAR* GetTags()
	{
		return tags;
	}

	TCHAR* GetDate()
	{
		return date;
	}

	TCHAR* GetTime()
	{
		return time;
	}

	int GetPriorityNum()
	{
		return priority;
	}

	LPCWSTR GetPriority()
	{
		LPCWSTR text;
		if (priority == 0) text = TEXT("Низький");
		else if (priority == 1) text = TEXT("Середній");
		else text = TEXT("Високий");

		return text;
	}

	void SaveToFile()
	{
		const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());
		wofstream out(TEXT("Список справ.txt"), ios::app | ios::binary);
		out.imbue(utf8_locale);

		out << "Commentary: " << GetCommentary() << endl;
		out << "Tags: " << GetTags() << endl;
		out << "Priority: " << GetPriority() << endl;
		out << "Complete Date: " << GetDate() << endl;
		out << "Complete Time: " << GetTime() << endl << endl;

		out.close();
	}
};