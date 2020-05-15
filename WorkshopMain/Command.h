#ifndef CMD_H
#define CMD_H

#include <iostream>
#include <vector> 
#include "Connection.h"
#include "TableStruct.h"
using namespace std;

class Command : public Connection
{
	private:
		string sqlspecificApplicant = "select * from APPLICANT where ID = :ID";
		string sqlviewProgram = "select PROGRAM.NAME, PROGRAM.DATE_START,  PROGRAM.DATE_END,   PROGRAM.DATE_APPLY, PROGRAM.TOTAL_APPLY, FIRSTAID_PROGRAM.DATE_APPROVE  from PROGRAM left join FIRSTAID_PROGRAM on PROGRAM.ID = FIRSTAID_PROGRAM.PROGRAM_ID where PROGRAM.APPLICANT_ID = :APPLICANT and PROGRAM.DATE_START >= :DATE_SYS order by PROGRAM.DATE_START";
		string sqlstaffLogin = "select STAFF.ID, STAFF.ROLE_ID, STAFF.FIRSTNAME, STAFF.LASTNAME, STAFF.BIRTHDATE, STAFF.EMAIL, STAFF.PASSWORD, ROLE.TITLE from STAFF join ROLE on STAFF.ROLE_ID = ROLE.ID where STAFF.EMAIL = :EMAIL and STAFF.PASSWORD = :PWD order by STAFF.ID";
		string sqlitemList = "select ITEM.ID, ITEM.NAME, ITEM.DATE_LIMIT, SUM(CONTENT.TOTAL) from ITEM left join CONTENT on ITEM.ID = CONTENT.ITEM_ID group by ITEM.ID, ITEM.NAME, ITEM.DATE_LIMIT order by ITEM.ID";
		string sqlapplicationList = "select PROGRAM.NAME, PROGRAM.DATE_START,  PROGRAM.DATE_END,   PROGRAM.DATE_APPLY, PROGRAM.TOTAL_APPLY from PROGRAM where PROGRAM.DATE_START >= :DATE_SYS order by PROGRAM.DATE_START";
		string sqlavailablefirstaid = "select count(STATUS) from FIRSTAID where STATUS = 2";
		string sqlitemListFilterZero = "select CONTENT.ID, ITEM.NAME, ITEM.DATE_LIMIT, SUM(CONTENT.TOTAL) TOTAL from ITEM left join CONTENT on ITEM.ID = CONTENT.ITEM_ID where TOTAL != 0 group by CONTENT.ID, ITEM.NAME, ITEM.DATE_LIMIT order by CONTENT.ID";
		string sqlfirstaidSingleEmpty = "select * from FIRSTAID where STATUS = 2";
		string sqlcheckFirstaidEmpty = "select count (*) from FIRSTAID_CONTENT where FIRSTAID_ID = :FIRSTAID and CONTENT_ID = :CONTENT";


		string sqlnewApplicant = "insert into APPLICANT values (:ID, :FIRST, :LAST, :CONTACT, :TYPE)";
		string sqlnewProgram = "insert into PROGRAM (APPLICANT_ID, NAME, DATE_APPLY , DATE_START, DATE_END, TOTAL_APPLY) values (:APPLICANT, :NAME, :DATEA, :DATES, :DATEE,  :TOTAL)";
		string sqlnewItem = "insert into ITEM values (NULL, :NAME, :MAXL, :DATEL)";
		string sqlrefillContent = "insert into CONTENT values (NULL, :ITEM, :STAFF, :DATE_IN, :DATE_EXP, :TOTAL)";
		string sqlaidNew = "insert into FIRSTAID values(null, :STATUS)";
		string sqlnewStaff = "insert into STAFF values (null, :ROLE, :FIRST, :LAST, :BIRTHDATE, :EMAIL, :PWD)";
		string sqlassigntFirstaidContent = "insert into FIRSTAID_CONTENT values (NULL, :FIRST, :CONTENT, :TOTAL)";

		string sqlupdateFirstaidEmpty = "update FIRSTAID_CONTENT set TOTAL = :TOTAL where FIRSTAID_ID = :FIRSTAID and CONTENT_ID = :CONTENT";
		string sqlupdateItemTotal = "update CONTENT set TOTAL = TOTAL - :TOTAL where ID = :ID";
		string sqlupdateFirstaidStatus = "update FIRSTAID set STATUS = :STATUS where ID = :ID";
public:
		Command();
		~Command();
		
		//Periksa sama ada pemohon tu dah daftar ke belum
		//input ID pemohon
		//output ID pemohon @ NULL
		string CheckNewApplicant(string);

		//Daftar pemohon baru
		//input maklumat pemohon
		//output tiada
		void NewApplicant(Applicant);
		
		//Login pemohon berdaftar
		//input ID pemohon
		//output maklumat pemohon @ NULL
		Applicant ApplicantLogin(string);
		
		//Mohon first aid untuk program
		//input maklumat program
		//output tiada
		void NewProgram(Program);

		//Tengok Status Permohonan yang masih valid
		//inpnut maklumat program
		//output semua maklumat program
		//vector<FirstAid_Program> ViewProgram(Applicant);
		vector<FirstAid_Program> ViewProgram(Applicant);

		//Login staff berdaftar
		//input email & password staff
		//output staff pemohon @ NULL
		Staff StaffLogin(Staff);
		
		//List of item
		//input none
		//output list of item 
		vector<Item> ItemList();

		//Letak item baru
		//input item
		//output NULL
		void ItemNew(Item);

		//Put how many item in the stock
		//Item must be availble in item
		//input content information
		//output NULL
		void RefillContent(Content);

		//Add one new first aid
		//input number of new first aid
		//out put null
		void AidNew();

		//list of applicantion make bu applicant
		//input null
		//output list of program/applicant
		vector<Program>ApplicationList();

		//Add new staff
		//input staff information
		//output null
		void NewStaff(Staff);

		//number of first aid box availabel @ not in use
		//input none
		//output int
		int AvailableFirstaid();

		//List of item filter by total of item in inventory 0
		//input none
		//output list of item 
		vector<Item> ItemListFilterZero();

		//get the ID of the available first aid
		//input none
		//output int / id
		int FirstaidSingleEmpty();

		//refill first add with new content;
		//input first aid content
		//output null
		void AssigntFirstaidContent(FirstAid_Content);

		int CheckFirstaidEmpty(FirstAid_Content);
		void UpdateFirstaidEmpty(FirstAid_Content);

		void UpdateItemTotal(int, int);
		void UpdateFirstaidStatus(int, int);
};		

#endif


