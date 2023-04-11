#include "superhero.h"

std::ostream& operator<<(std::ostream& ostr, Superhero& h){
	std::string v;
	if(h.isGood()) v= "Superhero ";
	else v= "Supervillan ";
	ostr << v << h.getName() << " has power " << h.getPower() << std::endl;
	return ostr;
}

 bool Superhero::operator==(const std::string& guess){
 	if(name == guess)
 		return true;
 	else 
 		return false;
 } 
	

bool Superhero::operator!=(const std::string& guess){
	if(name != guess)
 		return true;
 	else 
 		return false;
}

bool Superhero::operator>(Superhero & h){
	if(power=="Water" && (h.getPower()=="Fire" || h.getPower()=="Flexible" || h.getPower()=="Invisible")) { return true; }
	else if(power=="Fire" && (h.getPower()=="Wood" || h.getPower()=="Laser" || h.getPower()=="Speed")) { return true;}
	else if(power=="Wood" && (h.getPower()=="Water" || h.getPower()=="Flying" || h.getPower()=="Flexible")) { return true; }
	else if(power=="Flexible" && (h.getPower()=="Fire" || h.getPower()=="Invisible" || h.getPower()=="Speed")) { return true; }
	else if(power=="Flying" && (h.getPower()=="Fire" || h.getPower()=="Water" || h.getPower()=="Laser")) { return true; }
	else if(power=="Invisible" && (h.getPower()=="Fire" || h.getPower()=="Wood" || h.getPower()=="Speed" || h.getPower()=="Flying")) { return true; }
	else if(power=="Laser" && (h.getPower()=="Water" || h.getPower()=="Invisible" || h.getPower()=="Flexible" || h.getPower()=="Speed")) { return true; }
	else if(power=="Speed" && (h.getPower()=="Water" || h.getPower()=="Wood" || h.getPower()=="Flying")) { return true; }
	else { return false; }
}

