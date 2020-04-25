#ifndef TBLSTRUCT_H
#define TBLSTRUCT_H

#include <iostream>
using namespace std;

struct Role {
	int ID;
	string TITLE;
};

struct Staff {
	int ID ;
	Role ROLE_ID ;
	string FIRSTNAME ;
	string LASTNAME ;
	string BIRTHDATE ;
	string EMAIL ;
	string PASSWORD ;
};




struct FirstAid{
	int ID ;
	int STATUS ;
};

struct Item {
	int ID;
	string NAME;
	int MAX_LIMIT;
	int DATE_LIMIT;
};


struct Content{
	int ID ;
	Item ITEM_ID ;
	Staff STAFF_ID ;
	string DATE_IN;
	string DATE_EXP;
	int TOTAL;
};

struct FirstAid_Content{
	int ID ;
	FirstAid FIRSTAID_ID ;
	Content CONTENT_ID ;
	int TOTAL ;
};

struct Applicant{
	string ID ;
	string FIRST_NAME ;
	string LAST_NAME ;
	string CONTACT ;
	string TYPE ;
};

struct Program{
	int ID ;
	Applicant APPLICANT_ID ;
	string NAME ;
	string DATE_START ;
	string DATE_END ;
	string DATE_APPLY ;
	int TOTAL_APPLY ;
};

struct FirstAid_Program {
	int ID;
	Program PROGRAM_ID;
	FirstAid FIRSTAID_ID;
	Staff STAFF_ID ;
	string DATE_APPROVE ;
	string DATE_RETURN ;
	string DATE_PICKUP ;
};

#endif 



