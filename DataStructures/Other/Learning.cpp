
#include <iostream>
#include <string>
using namespace std;
//This allows you to not have to put std::cout before 
// standard character output

int main()
{
	cout <<"Hello World" << endl;
	//cout prints whatever is in the <<

	int a;
	cout << "Please enter your age:" << endl;
	cin >> a;
	int b = 18;
	if (a > b)
	{
		cout << "You are " << a << " and you are older than me" << endl;
		//endl inserts a line inbetween
	}
	//Indentation does not matter
string data;
cin.getline(data);
cout << data;


return 0;
// This tells the program to end
}