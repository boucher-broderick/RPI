#include <iostream>
#include "date.h"

Date::Date()
{
	day = 1;
	month = 1;
	year = 1900;
}

Date::Date(int aMonth, int aDay, int aYear)
{
	day = aDay;
	month = aMonth;
	year = aYear;
}

void Date::getDate() const
{
	std::cout << month << "/" << day << "/" << year << std::endl;
}