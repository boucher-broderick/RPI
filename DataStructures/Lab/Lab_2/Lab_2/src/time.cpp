#include <iostream>
#include "time.h"
#include <iomanip>  
#include <string> 


Time::Time() {
	second = 0;
	minute = 0;
	hour = 0;
}

Time::Time(int ahour, int amin, int asec) {
	second = asec;
	minute = amin;
	hour = ahour;
}

int Time::getSecond() const {
	return second;
}

int Time::getMinute() const {
	return minute;
}

int Time::getHour() const {
	return hour;
}

void Time::setSecond(int asec) {
	second = asec;
}

void Time::setMinute(int amin) {
	minute = amin;
}

void Time::setHour(int ahour) {
	hour = ahour;
}

void Time::PrintAMPM() {
	std::string x = " am";
	int temphour = hour;
	if (hour == 0) {
		temphour = 12;
	}
	if (hour > 11) {
		if (hour > 12) {
			temphour -= 12;
		}
		x = " pm";
	}
	std::string s = std::to_string(second);
	std::string m = std::to_string(minute);
	std::string h =std::to_string(temphour);
	std::string s1;
	std::string s2;
	std::string s3;
	if (s.size() == 1) {  s= "0"+s; }
	if (m.size() == 1) {m= "0" + m; }
	if (h.size() == 1) { h= "0" + h; }


	std::cout << h << ":" << m << ":" << s << x << std::endl;
}

bool IsEarlierThan(const Time& t1, const Time& t2) {
	if (t1.getHour() > t2.getHour())
		return false;
	else if (t1.getHour() == t2.getHour() && t1.getMinute() > t2.getMinute())
		return false;
	else if (t1.getHour() == t2.getHour() && t1.getMinute() == t2.getMinute() && t1.getSecond() > t2.getSecond())
		return false;
	else
		return true;
}