#include <iostream> 
#include <regex>
#include <ocilib.h> 
#include "Connection.h"
using namespace std;

void err_handler(OCI_Error *err) {
	int err_type = OCI_ErrorGetType(err);
	cout << endl;

	err_type == OCI_ERR_WARNING ? cout << "> WARNING : " : cout << "> ERROR   : ";
	cout << OCI_ErrorGetString(err);

	cout << endl;
	system("PAUSE");
}

Connection::Connection() {}

Connection::~Connection() {
	OCI_Cleanup();
}

void Connection::Connect() {
	OCI_Initialize(err_handler, NULL, OCI_ENV_DEFAULT);

	this->conn = OCI_ConnectionCreate(this->db, this->user, this->pwd, OCI_ENV_DEFAULT);
	this->statement = OCI_CreateStatement(this->conn);
}

void Connection::Execute() {
	OCI_Execute(this->statement);
	OCI_Commit(this->conn);
}

bool Connection::ValidInteger(int integer) {
	bool valid = true;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		valid = false;
	}
	return valid;
}

bool Connection::ValidEmail(string email) {
	const regex pattern("(\\w+)(\\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return regex_match(email, pattern);
}

bool Connection::ValidDate(string date) {
	const regex pattern("\\d{2}/\\d{2}/\\d{4}");
	return regex_match(date, pattern);
}

bool Connection::ValidPassword(string password) {
	const regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[#$^+=!*()@%&]).{8,10}$");
	return regex_match(password, pattern);
}

string Connection::Encrypt(string toEncrypt) {
	string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] + 3;

	return output;
}

OCI_Date *Connection::CurrentDate() {
	OCI_Date *date = OCI_DateCreate(NULL);
	
	OCI_DateSysDate(date);
	
	return this->StringToDate(this->DateToString(date));
}

OCI_Date *Connection::StringToDate(string toDate) {
	OCI_Date *date = OCI_DateCreate(NULL);

	OCI_DateFromText(date, &toDate[0], "DD/MM/YYYY");
	
	return date;
}

string Connection::DateToString(OCI_Date *toString) {
	string date;
	OCI_DateToText(toString, "DD/MM/YYYY", charLen, &date[0]);
	return &date[0];
}

int Connection::CompareDate(string date) {
	OCI_Date *sysdate, *usrdate;

	sysdate = OCI_DateCreate(NULL);
	OCI_DateSysDate(sysdate);

	sysdate = this->CurrentDate();
	usrdate = this->StringToDate(date);
	
	return OCI_DateCompare(sysdate, usrdate);
}

int Connection::CompareDate(string date, string date2) {
	OCI_Date *usrdate, *usrdate2;

	usrdate = this->StringToDate(date);
	usrdate2 = this->StringToDate(date2);

	return OCI_DateCompare(usrdate, usrdate2);
}

int Connection::BetweenDate(string date) {
	OCI_Date *sysdate, *usrdate;

	sysdate = this->CurrentDate();
	usrdate = this->StringToDate(date);

	return OCI_DateDaysBetween(usrdate, sysdate);
}

int Connection::BetweenDate(string date, string date2) {
	OCI_Date *sysdate, *usrdate;

	sysdate = this->StringToDate(date2);
	usrdate = this->StringToDate(date);

	return OCI_DateDaysBetween(usrdate, sysdate);
}