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
		string sqlviewProgram = "select distinct PROGRAM.NAME, PROGRAM.DATE_START,  PROGRAM.DATE_END,   PROGRAM.DATE_APPLY, PROGRAM.TOTAL_APPLY, FIRSTAID_PROGRAM.DATE_APPROVE  from PROGRAM left join FIRSTAID_PROGRAM on PROGRAM.ID = FIRSTAID_PROGRAM.PROGRAM_ID where PROGRAM.APPLICANT_ID = :APPLICANT and PROGRAM.DATE_START >= :DATE_SYS order by PROGRAM.DATE_START";
		string sqlstaffLogin = "select STAFF.ID, STAFF.ROLE_ID, STAFF.FIRSTNAME, STAFF.LASTNAME, STAFF.BIRTHDATE, STAFF.EMAIL, STAFF.PASSWORD, ROLE.TITLE from STAFF join ROLE on STAFF.ROLE_ID = ROLE.ID where STAFF.EMAIL = :EMAIL and STAFF.PASSWORD = :PWD order by STAFF.ID";
		string sqlitemList = "select ITEM.ID, ITEM.NAME, ITEM.DATE_LIMIT, SUM(CONTENT.TOTAL) from ITEM left join CONTENT on ITEM.ID = CONTENT.ITEM_ID group by ITEM.ID, ITEM.NAME, ITEM.DATE_LIMIT order by ITEM.ID";
		string sqlapplicationList = "select PROGRAM.ID,  PROGRAM.NAME, PROGRAM.DATE_START,  PROGRAM.DATE_END,   PROGRAM.DATE_APPLY, PROGRAM.TOTAL_APPLY from PROGRAM where PROGRAM.DATE_START >= :DATE_SYS and PROGRAM.ID not in (select PROGRAM_ID from FIRSTAID_PROGRAM) order by PROGRAM.DATE_START";
		string sqlavailablefirstaid = "select count(STATUS) from FIRSTAID where STATUS = 2";
		string sqlitemListFilterZero = "select CONTENT.ID, ITEM.NAME, ITEM.DATE_LIMIT, SUM(CONTENT.TOTAL) TOTAL from ITEM left join CONTENT on ITEM.ID = CONTENT.ITEM_ID where TOTAL != 0 group by CONTENT.ID, ITEM.NAME, ITEM.DATE_LIMIT order by CONTENT.ID";
		string sqlfirstaidSingleEmpty = "select * from FIRSTAID where STATUS = 2";
		string sqlcheckFirstaidEmpty = "select count (*) from FIRSTAID_CONTENT where FIRSTAID_ID = :FIRSTAID and CONTENT_ID = :CONTENT";
		string sqlBorrowFirstaid = "select FIRSTAID_PROGRAM.ID, FIRSTAID_PROGRAM.FIRSTAID_ID, FIRSTAID_PROGRAM.PROGRAM_ID, PROGRAM.NAME, (select STATUS from FIRSTAID where ID = FIRSTAID_PROGRAM.FIRSTAID_ID) as STATUS from PROGRAM join FIRSTAID_PROGRAM on FIRSTAID_PROGRAM.PROGRAM_ID = PROGRAM.ID where PROGRAM.APPLICANT_ID = :ID and FIRSTAID_PROGRAM.DATE_RETURN is NULL";
		string sqlAllFirstAid = "select * from FIRSTAID";
		string sqlAllStaff = "select (select TITLE from ROLE where ID = ROLE_ID) as ROLE , FIRSTNAME,LASTNAME,BIRTHDATE,EMAIL from STAFF";
		string sqlConditionRemoveItem = "select count(FIRSTAID_CONTENT.ID) as COUNT from FIRSTAID_CONTENT join CONTENT on CONTENT.ID = FIRSTAID_CONTENT.CONTENT_ID join ITEM on ITEM.ID = CONTENT.ITEM_ID where ITEM.NAME = :NAME";
		string sqlBorrowFirstaid_NoParam = "select PROGRAM.NAME, FIRSTAID_PROGRAM.DATE_APPROVE from FIRSTAID_PROGRAM join PROGRAM on FIRSTAID_PROGRAM.PROGRAM_ID = PROGRAM.ID where FIRSTAID_PROGRAM.DATE_RETURN is NULL";
		string sqlGenerateReport_Staff = "select  PROGRAM.APPLICANT_ID, to_char(PROGRAM.DATE_START, 'mm Month'),FIRSTAID_PROGRAM.DATE_APPROVE, FIRSTAID_PROGRAM.DATE_RETURN from PROGRAM left join FIRSTAID_PROGRAM on PROGRAM.ID = FIRSTAID_PROGRAM.PROGRAM_ID";
		string sqlGenerateReport_Applicant = "select  PROGRAM.APPLICANT_ID, to_char(PROGRAM.DATE_START, 'mm Month'),FIRSTAID_PROGRAM.DATE_APPROVE, FIRSTAID_PROGRAM.DATE_RETURN from PROGRAM left join FIRSTAID_PROGRAM on PROGRAM.ID = FIRSTAID_PROGRAM.PROGRAM_ID where PROGRAM.APPLICANT_ID = :APPLICANT";
		string sqlItemLimit = "select MAX_LIMIT from ITEM where NAME = :NAME";

		string sqlnewApplicant = "insert into APPLICANT values (:ID, :FIRST, :LAST, :CONTACT, :TYPE)";
		string sqlnewProgram = "insert into PROGRAM (APPLICANT_ID, NAME, DATE_APPLY , DATE_START, DATE_END, TOTAL_APPLY) values (:APPLICANT, :NAME, :DATEA, :DATES, :DATEE,  :TOTAL)";
		string sqlnewItem = "insert into ITEM values (NULL, :NAME, :MAXL, :DATEL)";
		string sqlrefillContent = "insert into CONTENT values (NULL, :ITEM, :STAFF, :DATE_IN, :DATE_EXP, :TOTAL)";
		string sqlaidNew = "insert into FIRSTAID values(null, :STATUS)";
		string sqlnewStaff = "insert into STAFF values (null, :ROLE, :FIRST, :LAST, :BIRTHDATE, :EMAIL, :PWD)";
		string sqlassigntFirstaidContent = "insert into FIRSTAID_CONTENT values (NULL, :FIRST, :CONTENT, :TOTAL)";
		string sqlprogramApprove = "insert into FIRSTAID_PROGRAM (PROGRAM_ID, FIRSTAID_ID, STAFF_ID, DATE_APPROVE) values (:PROGRAMID, :FIRSTID, :STAFFID, :DATE_APPROVE)";

		string sqlupdateFirstaidEmpty = "update FIRSTAID_CONTENT set TOTAL = :TOTAL where FIRSTAID_ID = :FIRSTAID and CONTENT_ID = :CONTENT";
		string sqlupdateItemTotal = "update CONTENT set TOTAL = TOTAL - :TOTAL where ID = :ID";
		string sqlupdateFirstaidStatus = "update FIRSTAID set STATUS = :STATUS where ID = :ID";
		string sqlupdateReturnFirstAid = "update FIRSTAID set STATUS = 2 where ID in(select FIRSTAID_ID from FIRSTAID_PROGRAM where PROGRAM_ID in(select ID from PROGRAM where NAME = :NAME))";
		string sqlupdateReturnDate = "update FIRSTAID_PROGRAM set DATE_RETURN = :DATER where PROGRAM_ID = (select ID from PROGRAM where NAME = :NAME)";

		string sqlremoveContent = "delete from FIRSTAID_CONTENT where FIRSTAID_ID in(select FIRSTAID_ID from FIRSTAID_PROGRAM where PROGRAM_ID in(select ID from PROGRAM where NAME = :NAME))";
		string sqlremoveStaff = "delete from STAFF where EMAIL = :EMAIL";
		string sqlremoveFirstaid = "delete from FIRSTAID where ID = :ID";
		string sqlremoveItemContent = "delete from CONTENT where ITEM_ID = (select ID from ITEM where NAME = :NAME)";
		string sqlremoveItem = "delete from ITEM where NAME = :NAME";

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

		//check if tthe first aid is valid or not
		//input firstaid_content data
		//output 0, 1
		int CheckFirstaidEmpty(FirstAid_Content);



		//update the value of the item in the repo
		//ipnut  id and total
		//output nill
		void UpdateFirstaidEmpty(FirstAid_Content);

		//update the value of the item in the repo
		//ipnut  id and total
		//output nill
		void UpdateItemTotal(FirstAid_Content);
		

		//Update to status of the first aid after being borrow
		//input program name
		//output null
		void UpdateFirstaidStatus(FirstAid_Content);

		//approve the applicant application
		//input firstaid_program data
		//output null
		void ProgramApprove(FirstAid_Program);

		//list of first aid that been borrow by user
		//input applicant id
		//output list of first adi and program name
		vector<FirstAid_Program> BorrowFirstaid(Applicant);

		vector<FirstAid_Program> BorrowFirstaid();

		//Update to status of the first aid after being return
		//input program name
		//output null
		void UpdateReturnFirstAid(Program);

		//list of all the first aid box
		//input null
		//output null
		vector<FirstAid> AllFirstaid();

		//remove all the content in the first aid
		//input first aid program name
		//output null
		void RemoveContent(Program);


		//list of all the STAFF
		//input null
		//output null
		vector<Staff> AllStaff();

		//remove  staff
		//input staff
		//output null
		void RemoveStaff(Staff);


		//remove  first aid
		//input first aid program name
		//output null
		void RemoveFirstAid(int);

		//update return date of first aid
		//input program 
		//output null
		void UpdateReturnDate(Program);


		//check the condition of item that want to bee remove
		//input item
		//output 0 @ 1
		int ConditionRemoveItem(Item);


		//remove  item
		//input item in the content
		//output null
		void RemoveItemContent(Item);


		//remove  item in item
		//input item 
		//output null
		void RemoveItem(Item);

		//Report generation
		//input null
		//output list of data
		vector<FirstAid_Program>GenerateReport();


		//Report generation
		//input applicant 
		//output list of data
		vector<FirstAid_Program>GenerateReport(Applicant);

		//item limit in first aid
		//input item name
		//output  of limit
		int ItemLimit(string);
};		

#endif

