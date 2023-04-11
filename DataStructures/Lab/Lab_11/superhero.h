#include <string>
#include <iostream>

class Superhero {
public:
	Superhero(std::string h, std::string n, std::string p)
	{
		hero=h;
		name=n;
		power=p;
		isgood=true;
	}
	 bool operator==(const std::string& guess); 
	 bool operator!=(const std::string& guess);
	 void operator-(){ if(isgood) isgood=false; else isgood=true; }
	 bool operator>(Superhero & h);

	

	 std::string getName() const { return hero; } 
	 std::string getPower() const { return power; } 
	 bool isGood() { return isgood; }

private:
	std::string hero, name, power;
	bool isgood;
};

 std::ostream& operator<<(std::ostream& ostr, Superhero& h);