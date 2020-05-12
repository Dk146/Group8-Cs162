#include "include.h"

#ifndef staff
#define staff

class Staff
{
private:
	string s_user, s_pass, s_name;
	bool s_gender;
public: 
	void setUser(string _user);
	void setPass(string _pass);
	void setName(string _name);
	void setGender(bool _gender);
	string getUser();
	string getPass();
	string getName();
	bool getGender();
};


#endif
