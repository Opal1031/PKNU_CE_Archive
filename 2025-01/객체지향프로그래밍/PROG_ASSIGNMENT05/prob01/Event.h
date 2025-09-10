#pragma once

#include<iostream>
#include "Date.h"

using namespace std;

class Event {
private:
	static int event_counter;
	int id;

protected:
	string content;

public:
	Event();
	Event(string cont);
	virtual ~Event();
	int get_id();
	bool contains(string keyword);
	virtual bool relevant_to(Date& day) = 0;
	virtual bool relevant_to_between(Date& theDay1, Date& theDay2) = 0;
	virtual void print(ostream& out);
	virtual void save_print(ostream& out) = 0;
};

class OneDayEvent : public Event {
private:
	Date date;

public:
	OneDayEvent();
	OneDayEvent(Date d, string str);
	bool relevant_to(Date& theDay);
	bool relevant_to_between(Date& theDay1, Date& theDay2);
	void print(ostream& out);
	// save
	void save_print(ostream& out);
};

class PeriodEvent : public Event {
private:
	Date begin, end;

public:
	PeriodEvent();
	PeriodEvent(Date d1, Date d2, string str);
	bool relevant_to(Date& theDay);
	bool relevant_to_between(Date& theDay1, Date& theDay2);
	void print(ostream& out);
	void save_print(ostream& out);
};

class DeadlineEvent : public Event {
private:
	Date deadline;

public:
	DeadlineEvent();
	DeadlineEvent(Date d, string str);
	bool relevant_to(Date& theDay);
	bool relevant_to_between(Date& theDay1, Date& theDay2);
	void print(ostream& out);
	void save_print(ostream& out);
};