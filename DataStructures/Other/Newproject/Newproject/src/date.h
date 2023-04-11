class Date
{
public:
	Date();
	Date(int aMonth, int aDay, int aYear);


	void getDate() const;


private:
	int day;
	int month;
	int year;
};