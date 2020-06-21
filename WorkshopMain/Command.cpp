#include <iostream>
#include <vector> 
#include "Command.h"
#include "TableStruct.h"
using namespace std;


Command::Command() {}

Command::~Command() {}

string Command::CheckNewApplicant(string id) {
	string output;
	OCI_Prepare(this->statement, OTEXT(&this->sqlspecificApplicant[0]));
	OCI_BindString(this->statement, ":ID", &id[0], charLen);

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result)) {
		output = OCI_GetString(this->result, 1);
	}

	return output;
}

void Command::NewApplicant(Applicant applicant) {

	OCI_Prepare(this->statement, OTEXT(&this->sqlnewApplicant[0]));

	OCI_BindString(this->statement, ":ID", &applicant.ID[0], this->charLen);
	OCI_BindString(this->statement, ":FIRST", &applicant.FIRST_NAME[0], this->charLen);
	OCI_BindString(this->statement, ":LAST", &applicant.LAST_NAME[0], this->charLen);
	OCI_BindString(this->statement, ":CONTACT", &applicant.CONTACT[0], this->charLen);
	OCI_BindString(this->statement, ":TYPE", &applicant.TYPE[0], this->charLen);

	Execute();
}

Applicant Command::ApplicantLogin(string id) {
	Applicant applicant;

	OCI_Prepare(this->statement, OTEXT(&this->sqlspecificApplicant[0]));

	OCI_BindString(this->statement, ":ID", &id[0], this->charLen);

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result)) {
		applicant = {
			OCI_GetString(this->result, 1),
			OCI_GetString(this->result, 2),
			OCI_GetString(this->result, 3),
			OCI_GetString(this->result, 4),
			OCI_GetString(this->result, 5)
		};
	}

	return applicant;
}

void Command::NewProgram(Program program) {

	OCI_Prepare(this->statement, OTEXT(&this->sqlnewProgram[0]));

	OCI_BindString(this->statement, ":APPLICANT", &program.APPLICANT_ID.ID[0], this->charLen);
	OCI_BindString(this->statement, ":NAME", &program.NAME[0], this->charLen);
	OCI_BindDate(this->statement, ":DATEA", this->StringToDate(program.DATE_APPLY));
	OCI_BindDate(this->statement, ":DATES", this->StringToDate(program.DATE_START));
	OCI_BindDate(this->statement, ":DATEE", this->StringToDate(program.DATE_END));
	OCI_BindInt(this->statement, ":TOTAL", &program.TOTAL_APPLY);

	this->Execute();
}

vector<FirstAid_Program>Command::ViewProgram(Applicant applicant) {

	FirstAid_Program value;
	vector<FirstAid_Program> output;


	OCI_Prepare(this->statement, OTEXT(&this->sqlviewProgram[0]));

	OCI_BindString(this->statement, ":APPLICANT", &applicant.ID[0], this->charLen);
	OCI_BindDate(this->statement, ":DATE_SYS", this->CurrentDate());

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result)) {
		value.PROGRAM_ID.NAME = OCI_GetString(this->result, 1);
		value.PROGRAM_ID.DATE_START = this->DateToString(OCI_GetDate(this->result, 2));
		value.PROGRAM_ID.DATE_END = this->DateToString(OCI_GetDate(this->result, 3));
		value.PROGRAM_ID.DATE_APPLY = this->DateToString(OCI_GetDate(this->result, 4));
		value.PROGRAM_ID.TOTAL_APPLY = OCI_GetInt(this->result, 5);

		value.DATE_APPROVE = "";
		if (OCI_GetDate(this->result, 6) != nullptr)
			value.DATE_APPROVE = this->DateToString(OCI_GetDate(this->result, 6));

		output.push_back(value);
	}

	return output;
}

Staff Command::StaffLogin(Staff staff) {

	Staff output;
	auto pwd = this->Encrypt(staff.PASSWORD);

	OCI_Prepare(this->statement, OTEXT(&this->sqlstaffLogin[0]));

	OCI_BindString(this->statement, ":EMAIL", &staff.EMAIL[0], this->charLen);
	OCI_BindString(this->statement, ":PWD", &pwd[0], this->charLen);

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result)) {
		output = {
			OCI_GetInt(this->result, 1),
			{OCI_GetInt(this->result,2), OCI_GetString(this->result, 8)},
			OCI_GetString(this->result, 3),
			OCI_GetString(this->result, 4),
			OCI_GetString(this->result, 5),
			OCI_GetString(this->result, 6),
			OCI_GetString(this->result, 7)
		};
	}

	return output;
}

vector<Item> Command::ItemList() {

	Item value;
	vector<Item> output;

	OCI_Prepare(this->statement, OTEXT(&this->sqlitemList[0]));

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result)) {
		value = {
			OCI_GetInt(this->result, 1),
			OCI_GetString(this->result, 2),
			OCI_GetInt(this->result, 4),
			OCI_GetInt(this->result, 3)
		};
		output.push_back(value);
	}

	return output;

}

void Command::ItemNew(Item item) {
	OCI_Prepare(this->statement, OTEXT(&this->sqlnewItem[0]));

	OCI_BindString(this->statement, ":NAME", &item.NAME[0], this->charLen);
	OCI_BindInt(this->statement, ":MAXL", &item.MAX_LIMIT);
	OCI_BindInt(this->statement, ":DATEL", &item.DATE_LIMIT);

	this->Execute();
}

void Command::RefillContent(Content content) {

	auto date = !content.DATE_EXP.empty() ? this->StringToDate(content.DATE_EXP) : OCI_DateCreate(NULL);

	OCI_Prepare(this->statement, OTEXT(&this->sqlrefillContent[0]));

	OCI_BindInt(this->statement, ":ITEM", &content.ITEM_ID.ID);
	OCI_BindInt(this->statement, ":STAFF", &content.STAFF_ID.ID);
	OCI_BindDate(this->statement, ":DATE_IN", this->CurrentDate());
	OCI_BindDate(this->statement, ":DATE_EXP", date);
	OCI_BindInt(this->statement, ":TOTAL", &content.TOTAL);

	Execute();
}

void Command::AidNew() {
	int state = 2;
	OCI_Prepare(this->statement, OTEXT(&this->sqlaidNew[0]));

	OCI_BindInt(this->statement, ":STATUS", &state);

	Execute();
}

vector<Program> Command::ApplicationList() {
	Program value;
	vector<Program> output;
	OCI_Prepare(this->statement, OTEXT(&this->sqlapplicationList[0]));

	OCI_BindDate(this->statement, ":DATE_SYS", this->CurrentDate());

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result)) {
		value.ID = OCI_GetInt(this->result, 1);
		value.NAME = OCI_GetString(this->result, 2);
		value.DATE_START = this->DateToString(OCI_GetDate(this->result, 3));
		value.DATE_END = this->DateToString(OCI_GetDate(this->result, 4));
		value.DATE_APPLY = this->DateToString(OCI_GetDate(this->result, 5));
		value.TOTAL_APPLY = OCI_GetInt(this->result, 6);
		
		output.push_back(value);
	}

	return output;
}

void Command::NewStaff(Staff staff) {

	auto pwd = this->Encrypt(staff.PASSWORD);

	OCI_Prepare(this->statement, OTEXT(&this->sqlnewStaff[0]));

	OCI_BindInt(this->statement, ":ROLE", &staff.ROLE_ID.ID);
	OCI_BindString(this->statement, ":FIRST", &staff.FIRSTNAME[0], this->charLen);
	OCI_BindString(this->statement, ":LAST", &staff.LASTNAME[0], this->charLen);
	OCI_BindDate(this->statement, ":BIRTHDATE", this->StringToDate(staff.BIRTHDATE));
	OCI_BindString(this->statement, ":EMAIL", &staff.EMAIL[0], this->charLen);
	OCI_BindString(this->statement, ":PWD", &pwd[0], this->charLen);

	this->Execute();
}

int Command::AvailableFirstaid() {
	int output;

	OCI_Prepare(this->statement, OTEXT(&this->sqlavailablefirstaid[0]));

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result))
		output = OCI_GetInt(this->result, 1);

	return output;

}

vector<Item> Command::ItemListFilterZero() {

	Item value;
	vector<Item> output;

	OCI_Prepare(this->statement, OTEXT(&this->sqlitemListFilterZero[0]));

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result)) {
		value = {
			OCI_GetInt(this->result, 1),
			OCI_GetString(this->result, 2),
			OCI_GetInt(this->result, 4),
			OCI_GetInt(this->result, 3)
		};
		output.push_back(value);
	}

	return output;

}

int Command::FirstaidSingleEmpty() {
	int output = 0;

	OCI_Prepare(this->statement, OTEXT(&this->sqlfirstaidSingleEmpty[0]));
	
	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	if(OCI_FetchNext(this->result)) output = OCI_GetInt(this->result, 1);

	return output;
}

void Command::UpdateItemTotal(FirstAid_Content faidContent) {
	OCI_Prepare(this->statement, OTEXT(&this->sqlupdateItemTotal[0]));
	OCI_BindInt(this->statement, ":TOTAL", &faidContent.TOTAL);
	OCI_BindInt(this->statement, ":ID", &faidContent.CONTENT_ID.ID);
	this->Execute();
}


void Command::AssigntFirstaidContent(FirstAid_Content faidContent) {
	OCI_Prepare(this->statement, OTEXT(&this->sqlassigntFirstaidContent[0]));

	OCI_BindInt(this->statement, ":FIRST", &faidContent.FIRSTAID_ID.ID);
	OCI_BindInt(this->statement, ":CONTENT", &faidContent.CONTENT_ID.ID);
	OCI_BindInt(this->statement, ":TOTAL", &faidContent.TOTAL);

	this->Execute();

}

int Command::CheckFirstaidEmpty(FirstAid_Content faidContent) {
	int output;

	OCI_Prepare(this->statement, OTEXT(&this->sqlcheckFirstaidEmpty[0]));

	OCI_BindInt(this->statement, ":FIRSTAID", &faidContent.FIRSTAID_ID.ID);
	OCI_BindInt(this->statement, ":CONTENT", &faidContent.CONTENT_ID.ID);

	this->Execute();
	this->result = OCI_GetResultset(this->statement);


	if (OCI_FetchNext(this->result)) output = OCI_GetInt(this->result, 1);


	return output;
}


void Command::UpdateFirstaidEmpty(FirstAid_Content faidContent) {
	
	OCI_Prepare(this->statement, OTEXT(&this->sqlupdateFirstaidEmpty[0]));


	OCI_BindInt(this->statement, ":FIRSTAID", &faidContent.FIRSTAID_ID.ID);
	OCI_BindInt(this->statement, ":CONTENT", &faidContent.CONTENT_ID.ID);
	OCI_BindInt(this->statement, ":TOTAL", &faidContent.TOTAL);

	this->Execute();
}

void Command::UpdateFirstaidStatus(FirstAid_Content faidContent) {
	OCI_Prepare(this->statement, OTEXT(&this->sqlupdateFirstaidStatus[0]));

	OCI_BindInt(this->statement, ":ID", &faidContent.FIRSTAID_ID.ID);
	OCI_BindInt(this->statement, ":STATUS", &faidContent.FIRSTAID_ID.STATUS);

	this->Execute();
}

void Command::ProgramApprove(FirstAid_Program faidProgram) {
	OCI_Prepare(this->statement, OTEXT(&this->sqlprogramApprove[0]));

	OCI_BindInt(this->statement, ":PROGRAMID", &faidProgram.PROGRAM_ID.ID);
	OCI_BindInt(this->statement, ":FIRSTID", &faidProgram.FIRSTAID_ID.ID);
	OCI_BindInt(this->statement, ":STAFFID", &faidProgram.STAFF_ID.ID);
	OCI_BindDate(this->statement, ":DATE_APPROVE", this->CurrentDate());
	
	this->Execute();
}


vector<FirstAid_Program> Command::BorrowFirstaid(Applicant applicant) {
	vector<FirstAid_Program> output;
	FirstAid_Program temp;
	OCI_Prepare(this->statement, OTEXT(&this->sqlBorrowFirstaid[0]));

	OCI_BindString(this->statement, ":ID", &applicant.ID[0], this->charLen);

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result)){
		temp.ID = OCI_GetInt(this->result, 1);
		temp.FIRSTAID_ID.ID = OCI_GetInt(this->result, 2);
		temp.PROGRAM_ID.ID = OCI_GetInt(this->result, 3);
		temp.PROGRAM_ID.NAME = OCI_GetString(this->result, 4);
		temp.FIRSTAID_ID.STATUS = OCI_GetInt(this->result, 5);

		output.push_back(temp);
	}

	return output;
}

vector<FirstAid_Program> Command::BorrowFirstaid() {
	vector<FirstAid_Program> output;
	FirstAid_Program temp;
	OCI_Prepare(this->statement, OTEXT(&this->sqlBorrowFirstaid_NoParam[0]));

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result)) {
		temp.PROGRAM_ID.NAME = OCI_GetString(this->result, 1);
		temp.DATE_APPROVE = this->DateToString(OCI_GetDate(this->result, 2));

		output.push_back(temp);
	}

	return output;
}


void Command::UpdateReturnFirstAid(Program program) {
	OCI_Prepare(this->statement, OTEXT(&this->sqlupdateReturnFirstAid[0]));

	OCI_BindString(this->statement, ":NAME", &program.NAME[0], this->charLen);

	this->Execute();
}

vector<FirstAid>Command::AllFirstaid() {
	vector<FirstAid> output;
	
	OCI_Prepare(this->statement, OTEXT(&this->sqlAllFirstAid[0]));

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result)){
		output.push_back({
			OCI_GetInt(this->result, 1),
			OCI_GetInt(this->result, 2)
		});
	}
	return output;
}

void Command::RemoveContent(Program program) {
	OCI_Prepare(this->statement, OTEXT(&this->sqlremoveContent[0]));

	OCI_BindString(this->statement, ":NAME", &program.NAME[0], this->charLen);

	this->Execute();
}

vector<Staff>Command::AllStaff() {
	vector<Staff> output;
	OCI_Prepare(this->statement, OTEXT(&this->sqlAllStaff[0]));

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result)){
		
		output.push_back({
			0,
			{0,OCI_GetString(this->result, 1)},
			OCI_GetString(this->result, 2),
			OCI_GetString(this->result, 3),
			this->DateToString(OCI_GetDate(this->result, 4)),
			OCI_GetString(this->result, 5),
			""
		});
	}
	return output;
}

void Command::RemoveStaff(Staff staff) {
	OCI_Prepare(this->statement, OTEXT(&this->sqlremoveStaff[0]));

	OCI_BindString(this->statement, ":EMAIL", &staff.EMAIL[0], this->charLen);

	this->Execute();
}

void Command::RemoveFirstAid(int code) {
	OCI_Prepare(this->statement, OTEXT(&this->sqlremoveFirstaid[0]));

	OCI_BindInt(this->statement, ":ID", &code);

	this->Execute();
}

void Command::UpdateReturnDate(Program program) {
	OCI_Prepare(this->statement, OTEXT(&this->sqlupdateReturnDate[0]));

	OCI_BindDate(this->statement, ":DATER", this->CurrentDate());
	OCI_BindString(this->statement, ":NAME", &program.NAME[0], this->charLen);

	this->Execute();
}

int Command::ConditionRemoveItem(Item item) {
	int output = 0;
	OCI_Prepare(this->statement, OTEXT(&this->sqlConditionRemoveItem[0]));

	OCI_BindString(this->statement, ":NAME", &item.NAME[0], this->charLen);

	this->Execute();
	this->result = OCI_GetResultset(this->statement);

	while (OCI_FetchNext(this->result)){
		output = OCI_GetInt(this->result, 1);
	}

	return output;
}


void Command::RemoveItemContent(Item item) {
	OCI_Prepare(this->statement, OTEXT(&this->sqlremoveItemContent[0]));

	OCI_BindString(this->statement, ":NAME", &item.NAME[0], this->charLen);

	this->Execute();
}

void Command::RemoveItem(Item item) {
	OCI_Prepare(this->statement, OTEXT(&this->sqlremoveItem[0]));

	OCI_BindString(this->statement, ":NAME", &item.NAME[0], this->charLen);

	this->Execute();
}

