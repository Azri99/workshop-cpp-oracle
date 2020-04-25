//Connection Purpose
#ifndef CONN_H
#define CONN_H

#include <iostream>
#include <ocilib.h> 
using namespace std;

class Connection
{
protected:
	const int		charLen   = 30;
	const otext    *db		  = "XE";
	const otext    *user	  = "WORKSHOP";
	const otext    *pwd		  = "Azri0011";
	OCI_Connection *conn	  = NULL;
	OCI_Statement  *statement = NULL;
	OCI_Resultset  *result	  = NULL;
public:
	Connection();
	~Connection();

	//Initialization & Connection & Statement
	void Connect();

	//Execute SQL Statement
	void Execute();

	//validate integer from other kind of data type
	//input int   @ else
	//output true @ false
	bool ValidInteger(int);
	
	//validate if email true or false
	//input data email
	//output true @ false
	bool ValidEmail(string);


	//validate if date true or false
	//input data date
	//output true @ false
	bool ValidDate(string);

	//encode & decode string
	//input string  (raw)
	//output string (encode)
	string Encrypt(string);

	//Return current date from system
	//input none
	//output address of currentdate format (DD/MM/YYYY)
	OCI_Date *CurrentDate();
	
	//convert string to date address
	//input string format           (DD/MM/YYYY)
	//output address of date format (DD/MM/YYYY)
	OCI_Date *StringToDate(string);

	//convert date address to string
	//input date address
	//output address of date format(DD / MM / YYYY)
	string DateToString(OCI_Date*);
	
	//input is usrdate
	//output :
	// -1 if sysdate < usrdate
	//  0 if they are =
	//  1 if sysdate > usrdate
	int CompareDate(string);

	//input  (sysdate, usrdate)
	int CompareDate(string, string);

	//beza hari dalam system dengan usrdate
	//input usrdate
	//output usrdate - sysdate
	int BetweenDate(string);

	//input  (sysdate, usrdate)
	int BetweenDate(string, string);


};
#endif // !CONN_H
