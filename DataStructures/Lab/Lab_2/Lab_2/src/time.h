class Time
{
public:
	Time();
	Time(int asec, int amin, int ahour);

	// Read Only
	int getSecond() const;
	int getMinute() const;
	int getHour() const;

	//Change
	void setSecond(int asec);
	void setMinute(int amin);
	void setHour(int ahour);
	

	//Print
	void PrintAMPM();

	
private:
	int second;
	int minute;
	int hour;


};

// compare
bool IsEarlierThan(const Time & t1, const Time & t2);
