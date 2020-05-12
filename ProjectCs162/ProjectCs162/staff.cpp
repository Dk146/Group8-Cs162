#include "Staff.h"

void Staff::setUser(string _user)
{
	s_user = _user;
}

void Staff::setName(string _name)
{
	s_name = _name;
}

void Staff::setPass(string _pass)
{
	s_pass = _pass;
}

void Staff::setGender(bool _gender)
{
	s_gender = _gender;
}

string Staff::getUser()
{
	return s_user;
}

string Staff::getName()
{
	return s_name;
}

string Staff::getPass()
{
	return s_pass;
}

bool Staff::getGender()
{
	return s_gender;
}