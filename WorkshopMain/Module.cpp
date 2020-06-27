#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include "Command.h"
#include "Module.h"
#include "TableStruct.h"
using namespace std;

Module::Module() {
	this->command.Connect();
}

Module::~Module() {}

template<class DataType> void Module::PrintElement(DataType data){
	cout << left << setw(8) << "|" << setw(15) << data;
}

void Module::PrintLine(int columnnum) {
	cout << "\n\n" << string(23 * columnnum, '-') << "\n\n";
}



void Module::HeaderModule(string module) {
	system("CLS");
	cout << "\t\t---------------------------------------------\n";
	cout << "\t\t---------------------------------------------\n";
	cout << "\t\t------First Aid Kits Application System------\n";
	cout << "\t\t" << module << "\n\n";
	cout << "\t\t---------------------------------------------\n";
	cout << "\n\n";
}

void Module::IndexModule() {
repeatFunction:
	HeaderModule("Index Module");

	cout << "\t\tAvailable Action :\n\n";
	cout << "\t\t1 = Staff Login\n";
	cout << "\t\t2 = Applicant\n";
	cout << "\t\t3 = Exit\n";
	cout << "\t\tEnter your option [1, 2, 3] : ";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << this->validint;
		cout << "\t\t";
		system("PAUSE");;
		goto repeatFunction;
	}
	
	switch (this->choose) {
	case 1:
		this->StaffLoginModule();
		break;
	case 2:
		this->ApplicantIndexModule();
		break;
	case 3:
		this->ExitModule();
		break;
	default:
		cout << this->validcom;
		cout << "\t\t";
		system("PAUSE");;
		goto repeatFunction;
		break;
	}
}

void Module::ExitModule() {
	HeaderModule("Exit Module");
	exit(NULL);
}

void Module::ApplicantIndexModule() {
repeatFunction:
	HeaderModule("Applicant Index Module");

	cout << "\t\tAvailable Action :\n\n";
	cout << "\t\t1 = First Time Applicant\n";
	cout << "\t\t2 = Applicant Login\n";
	cout << "\t\t3 = Exit\n";
	cout << "\t\tEnter your option [1, 2, 3] : ";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << this->validint;
		cout << "\t\t";
		system("PAUSE");;
		goto repeatFunction;
	}

	switch (this->choose){
	case 1:
		this->NewApplicantModule();
		break;
	case 2:
		this->ApplicantLoginModule();
		break;
	case 3:
		this->IndexModule();
		break;
	default:
		cout << this->validcom;
		cout << "\t\t";
		system("PAUSE");;
		goto repeatFunction;
		break;
	}

}

void Module::NewApplicantModule() {
	HeaderModule("New Applicant Module");
	
repeatId:
	cout << "\t\tYour Matric No  : ";
	cin >> this->applicant.ID;

	if (!this->command.CheckNewApplicant(this->applicant.ID).empty()) {
		repeatErr:
		cout << "\t\tThis Matric Number Already Register\n\n";
		cout << "\t\t1               = Try Again\n";
		cout << "\t\t2 or any number = Back to Main Menu\n";
		cout << "\t\t Your Choose [1, 2] : ";
		cin >> this->choose;

		if (!this->command.ValidInteger(this->choose)) {
			cout << validint;
			cout << "\t\t";
			system("PAUSE");;
			goto repeatErr;
		}

		switch (this->choose){
		case 1:
			goto repeatId;
			break;
		default:
			this->ApplicantIndexModule();
			break;
		}
	}

	if (this->applicant.ID.size() == 4) 
		this->applicant.TYPE = "Officer";
	else if (this->applicant.ID.size() == 10)
		this->applicant.TYPE = "Student";
	else {
		cout << "\t\tCombination not valid staff = 4 and student = 10\n";
		goto repeatId;
	}
	
	cout << "\t\tYour First Name : ";
	cin >> this->applicant.FIRST_NAME;
	
	cout << "\t\tYour Last Name  : ";
	cin >> this->applicant.LAST_NAME;

	repeatEmail:
	cout << "\t\tYour Contect Info\n";
	cout << "\t\t[your email]    : ";
	cin >> this->applicant.CONTACT;

	if (!this->command.ValidEmail(this->applicant.CONTACT)) {
		cout << validemail;
		cout << "\t\t";
		system("PAUSE");;
		goto repeatEmail;
	}

	this->command.NewApplicant(this->applicant);

	cout << "\t\tNew Record Save...Welcome " << this->applicant.FIRST_NAME << endl;
	cout << "\t\tYou Are " << this->applicant.TYPE << endl;
	cout << "\t\t";
	system("PAUSE");;

	this->ApplicantIndexModule();
}

void Module::ApplicantLoginModule() {
repeatFunction:
	HeaderModule("Applicant Login Module");

	cout << "\t\tEnter your Matric No : ";
	cin >> this->applicant.ID;

	this->applicant = this->command.ApplicantLogin(this->applicant.ID);

	if (this->applicant.ID.empty()){
		repeatTry:
		cout << "\t\tThis Matric Number Is Not Register\n\n";
		cout << "\t\t1               = Try Again\n";
		cout << "\t\t2 or any number = Back to Main Menu\n";
		cout << "\t\t Your Choose [1, 2] : ";
		cin >> this->choose;
		
		if (!this->command.ValidInteger(this->choose)) {
			cout << validint;
			cout << "\t\t";
			system("PAUSE");;
			goto repeatTry;
		}

		switch (this->choose) {
		case 1:
			goto repeatFunction;
			break;
		default:
			this->ApplicantIndexModule();
			break;
		}
	}
	
	cout << "\t\tYou Are " << this->applicant.TYPE << endl;
	cout << "\t\t";
	system("PAUSE");;

	this->ApplicantMenuModule();

}

void Module::ApplicantMenuModule() {
repeatFunction:
	HeaderModule("Applicant Menu Module");

	cout << "\t\tAvailable Action :\n\n";
	cout << "\t\t1 = Make an application\n";
	cout << "\t\t2 = Return first aid kit\n";
	cout << "\t\t3 = View application status\n";
	cout << "\t\t4 = Summary\n";
	cout << "\t\t5 = Exit\n";
	cout << "\t\tEnter your option [1, 2, 3, 4, 5] : ";
	cin >> this->choose;
	
	if (!this->command.ValidInteger(this->choose)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");
		goto repeatFunction;
	}

	switch (this->choose) {
	case 1:
		this->NewProgramModule();
		break;
	case 2:
		this->ReturnFirstaidModule();
		break;
	case 3:
		this->ViewProgramStatusModule();
		break;
	case 4:
		this->ReportModuleApplicant();
		break;
	case 5:
		this->IndexModule();
		break;
	default:
		cout << this->validcom;
		cout << "\t\t";system("PAUSE");;
		goto repeatFunction;
		break;
	}

}

void Module::NewProgramModule() {
	HeaderModule("New Program Module");
	
	cout << "\t\tEnter program name   : ";
	cin >> this->program.NAME;

	repeatDateStart:
	cout << "\t\tEnter program start date\n";
	cout << "\t\tFormat [DD/MM/YYYY]  :";
	cin >> this->program.DATE_START;

	if (!this->command.ValidDate(this->program.DATE_START)) {
		cout << "\t\tInvalid date format\n";
		cout << "\t\t";
		system("PAUSE");;
		goto repeatDateStart;
	}

	if ( this->command.BetweenDate(this->program.DATE_START) < 7 ||
		 this->command.CompareDate(this->program.DATE_START) == 1) {
		cout << "\t\t***Cannot apply when the program date is already pass   ***\n";
		cout << "\t\t***Program date must at least 7 day from the application***\n";
		cout << "\t\t";system("PAUSE");
		goto repeatDateStart;
	}

	repeatDateEnd:
	cout << "\t\tEnter program end date\n";
	cout << "\t\tFormat [DD/MM/YYYY]  :";
	cin >> this->program.DATE_END;

	if (!this->command.ValidDate(this->program.DATE_END)) {
		cout << this->validdate;
		cout << "\t\t";system("PAUSE");;
		goto repeatDateEnd;
	}

	if (this->command.CompareDate(this->program.DATE_START, this->program.DATE_END) == 1) {
		cout << "\t\t***Program end program must be the same as start or later***\n";
		cout << "\t\t";system("PAUSE");;
		goto repeatDateEnd;
	}

	repeatTotal:
	cout << "\t\tTotal apply          :";
	cin >> this->program.TOTAL_APPLY;

	if (!this->command.ValidInteger(this->program.TOTAL_APPLY)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatTotal;
	}

	if (this->program.TOTAL_APPLY <= 0 || this->program.TOTAL_APPLY >= 4) {
		cout << "\t\t***Min 1 Max 3***\n";
		cout << "\t\t";system("PAUSE");;
		goto repeatTotal;
	}

	this->program.APPLICANT_ID.ID = this->applicant.ID;
	this->program.DATE_APPLY = this->command.DateToString(this->command.CurrentDate());

	this->command.NewProgram(this->program);

	cout << "\t\tNew application by " << this->applicant.TYPE << endl;
	cout << "\t\t" << this->applicant.FIRST_NAME << " ID is " << this->applicant.ID<< "\n";
	cout << "\t\t";system("PAUSE");;

	this->ApplicantMenuModule();
}

void Module::ViewProgramStatusModule() {

	HeaderModule("View Program Status Module");

	auto result = this->command.ViewProgram(this->applicant);
	
	cout << "\t\tApprove Application\n";
	cout << endl;
	this->PrintElement("Program Name");
	this->PrintElement("Date Apply");
	this->PrintElement("Date Start");
	this->PrintElement("Day Left");
	this->PrintElement("Total Apply");
	this->PrintElement("Approve Date");
	this->PrintLine(6);

	for (auto x : result) {
		if (!x.DATE_APPROVE.empty()) {
			cout << endl;
			this->PrintElement(x.PROGRAM_ID.NAME);
			this->PrintElement(x.PROGRAM_ID.DATE_APPLY);
			this->PrintElement(x.PROGRAM_ID.DATE_START);
			this->PrintElement(this->command.BetweenDate(x.PROGRAM_ID.DATE_START));
			this->PrintElement(x.PROGRAM_ID.TOTAL_APPLY);
			this->PrintElement(x.DATE_APPROVE);
			this->PrintLine(6);
		}
	}


	cout << "\n\n\t\tPending Application\n";
	cout << endl;
	this->PrintElement("Program Name");
	this->PrintElement("Date Apply");
	this->PrintElement("Date Start");
	this->PrintElement("Day Left");
	this->PrintElement("Total Apply");
	this->PrintElement("Approve Date");
	this->PrintLine(6);

	for (auto x : result) {
		if (x.DATE_APPROVE.empty()) {
			cout << endl;
			this->PrintElement(x.PROGRAM_ID.NAME);
			this->PrintElement(x.PROGRAM_ID.DATE_APPLY);
			this->PrintElement(x.PROGRAM_ID.DATE_START);
			this->PrintElement(this->command.BetweenDate(x.PROGRAM_ID.DATE_START));
			this->PrintElement(x.PROGRAM_ID.TOTAL_APPLY);
			this->PrintElement(x.DATE_APPROVE);
			this->PrintLine(6);
		}
	}

	cout << "\n\n\t\t***        End of the list       ***\n\t\t";
	system("PAUSE");

	this->ApplicantMenuModule();
	
}

void Module::StaffLoginModule() {
	repeatFunction:
	HeaderModule("Staff Login Module");

	repeatEmail:
	cout << "\t\tEnter email    : ";
	cin >> this->staff.EMAIL;

	if (!this->command.ValidEmail(this->staff.EMAIL)) {
		cout << this->validemail;
		cout << "\t\t";system("PAUSE");;
		goto repeatEmail;
	}

	cout << "\t\tEnter password : ";
	cin >> this->staff.PASSWORD;

	this->staff = this->command.StaffLogin(this->staff);
	if (this->staff.EMAIL.empty()) {
		repeatTry:
		cout << "\t\tWrong Credential\n\n";
		cout << "\t\t1               = Try Again\n";
		cout << "\t\t2 or any number = Back to Main Menu\n";
		cout << "\t\t Your Choose [1, 2] : ";
		cin >> this->choose;

		if (!this->command.ValidInteger(this->choose)) {
			cout << this->validint;
			cout << "\t\t";
			system("PAUSE");;
			goto repeatTry;
		}
		switch (this->choose) {
		case 1:
			goto repeatFunction;
			break;
		default:
			this->IndexModule();
			break;
		}
	}

	cout << "\t\tYou are " << this->staff.ROLE_ID.TITLE << "\n";
	cout << "\t\t";
	system("PAUSE");;

	this->StaffIndexModule();

}

void Module::StaffIndexModule() {
	repeatFunction:
	HeaderModule("Staff Index Module");

	cout << "\t\tAvailable Action :\n\n";
	cout << "\t\t1 = Item Inventory\n";
	cout << "\t\t2 = Application\n";
	cout << "\t\t3 = Staff\n";
	cout << "\t\t4 = Sumary\n";
	cout << "\t\t5 = Exit\n";
	cout << "\t\tEnter your option [1, 2, 3, 4, 5] : ";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatFunction;
	}

	switch (this->choose) {
	case 1:
		this->ItemInventoryModule();
		break;
	case 2:
		this->ApplicationModule();
		break;
	case 3:
		this->StaffListModule();
		break;
	case 4:
		this->ReportModuleStaff();
		break;
	case 5:
		this->IndexModule();
		break;
	default:
		cout << "\t\t***Invalid Combination***\n";
		cout << "\t\t";system("PAUSE");;
		goto repeatFunction;
		break;
	}

}

void Module::StaffAddModule() {

	HeaderModule("Staff Add Module");

	Staff newStaff;

	newStaff.ROLE_ID.ID = 22;
	if (this->staff.ROLE_ID.TITLE == "Doctor") {
		repeatRole:
		cout << "\t\tRole\n";
		cout << "\t\t[1=Doctor, 2=Nurse] : ";
		cin >> this->choose;

		if (!this->command.ValidInteger(this->choose)) {
			cout << this->validint;
			cout << "\t\t";system("PAUSE");;
			goto repeatRole;
		}

		if(this->choose < 1 || this->choose > 2){
			cout << this->validcom;
			cout << "\t\t";system("PAUSE");;
			goto repeatRole;
		}

		this->choose == 1 ? newStaff.ROLE_ID.ID = 21 : newStaff.ROLE_ID.ID = 22;
	}

	cout << "\t\tFirst name : ";
	cin >> newStaff.FIRSTNAME;

	cout << "\t\tLast name : ";
	cin >> newStaff.LASTNAME;

	reBirth:
	cout << "\t\tBirthdate\n";
	cout << "\t\t[DD/MM/YYYY] : ";
	cin >> newStaff.BIRTHDATE;

	if (!this->command.ValidDate(newStaff.BIRTHDATE)) {
		cout << this->validdate;
		cout << "\t\t";system("PAUSE");;
		goto reBirth;
	}

	rePass:
	cout << "\t\tPassword  : ";
	cin >> newStaff.PASSWORD;

	if (!this->command.ValidPassword(newStaff.PASSWORD)) {
		cout << "\t\tPassword must contain at least:\n";
		cout << "\t\t8 to 10 charter\n";
		cout << "\t\tCapital and Lower\n";
		cout << "\t\tNumber\n";
		cout << "\t\tSpecial Character\n";
		cout << "\t\t"; system("PAUSE");;
		goto rePass;
	}

	newStaff.EMAIL = newStaff.FIRSTNAME + newStaff.LASTNAME[0] + "@utem.edu.my";

	this->command.NewStaff(newStaff);
	cout << "\t\tRecord save\n";
	cout << "\t\tWelcome " << newStaff.FIRSTNAME << " " << newStaff.EMAIL <<endl;
	cout << "\t\t";
	system("PAUSE");

	this->StaffListModule();
}

void Module::ItemInventoryModule() {
	repeatFunction:
	HeaderModule("Item Inventory Module");

	if (this->staff.ROLE_ID.TITLE == "Nurse") {
		cout << "\t\tDo not have access to the inventory\n";
		cout << "\t\tOnly can be access by Doctor\n";
		
		cout << "\t\t";
		system("PAUSE");
		this->StaffIndexModule();
	}

	cout << "\t\t1 = Inventory list\n";
	cout << "\t\t2 = First Aid List\n";
	cout << "\t\t3 = Exit\n";
	cout << "\t\tEnter your option [1, 2, 3] : ";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatFunction;
	}

	switch (this->choose){
	case 1:
		this->ItemListModule();
		break;
	case 2:
		this->FirstAidListModule();
		break;
	case 3:
		this->StaffIndexModule();
		break;
	default:
		goto repeatFunction;
		break;
	}

}

void Module::ItemListModule() {
	HeaderModule("Item List Module");

	auto result = this->command.ItemList();

	this->PrintElement("Name");
	this->PrintElement("Number In Stock");
	this->PrintLine(2);

	for (auto x : result) {
		cout << endl;
		this->PrintElement(x.NAME);
		this->PrintElement(x.MAX_LIMIT);
		this->PrintLine(2);
	}

	repeatChoose:
	cout << "\n";
	cout << "\t\tChoose you operation\n";
	cout << "\t\t1 = Add New\n";
	cout << "\t\t2 = Refill\n";
	cout << "\t\t3 = Delete\n";
	cout << "\t\t4 = Exit\n";
	cout << "\t\tYour actoin :";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatChoose;
	}

	switch (this->choose){
	case 1:
		this->ItemAddModule();
		break;
	case 2:
		this->RefillItemModule();
		break;
	case 3:
		this->ItemRemoveModule();
		break;
	case 4:
		this->ItemInventoryModule();
		break;
	default:
		cout << this->validcom;
		cout << "\t\t";system("PAUSE");;
		goto repeatChoose;
		break;
	}
}

void Module::ItemAddModule() {
	HeaderModule("Item Add Module");

	cout << "\t\tItem name             : ";
	cin >> this->item.NAME;

	repeatMax:
	cout << "\t\tMax item in first aid :";
	cin >> this->item.MAX_LIMIT;

	if (!this->command.ValidInteger(this->item.MAX_LIMIT)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatMax;
	}

	repeatDateL:
	cout << "\t\tHave a date limit\n";
	cout << "\t\t[1 = Yes, 2 = No]     :";
	cin >> this->item.DATE_LIMIT;
	
	if (!this->command.ValidInteger(this->item.DATE_LIMIT)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatDateL;
	}

	if (this->item.DATE_LIMIT < 1 || this->item.DATE_LIMIT > 2) {
		cout << this->validcom;
		cout << "\t\t";system("PAUSE");;
		goto repeatDateL;
	}

	this->command.ItemNew(this->item);

	cout << "\t\tNew Item Added\n";
	cout << "\t\t";
	system("PAUSE");
	this->ItemListModule();

}

void Module::RefillItemModule() {
	repeatFunction:
	HeaderModule("Refill Item Module");
	
	auto result = this->command.ItemList();



	this->PrintElement("Choose");
	this->PrintElement("Name");
	this->PrintLine(2);

	auto i = 1;
	for (auto x : result) {
		cout << endl;
		this->PrintElement(i);
		this->PrintElement(x.NAME);
		this->PrintLine(2);
		i++;
	}

	cout << "\t\tYour Choose : ";
	cin >> this->choose;



	if (!this->command.ValidInteger(this->choose)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatFunction;
	}

	if (this->choose < 1 || this->choose > i - 1) {
		goto repeatFunction;
	}

	repeatTotal:
	cout << "\t\tHow many You want to add : ";
	cin >> this->content.TOTAL;

	if (!this->command.ValidInteger(this->content.TOTAL)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatTotal;
	}

	if (this->content.TOTAL <= 0 || this->content.TOTAL > 100) {
		cout << "\t\tValue To big (>100) or small (<=0)\n";
		cout << "\t\t";system("PAUSE");;
		goto repeatTotal;
	}

	this->content.DATE_EXP = "";
	if (result[this->choose-1].DATE_LIMIT == 1) {
		repeatDate:
		cout << "\t\tEnter Expired date : ";
		cin >> this->content.DATE_EXP;

		if (!this->command.ValidDate(this->content.DATE_EXP)) {
			cout << this->validdate;
			cout << "\t\t";system("PAUSE");;
			goto repeatDate;
		}

		if (this->command.CompareDate(this->content.DATE_EXP) == 1) {
			cout << "\t\tDate need to be higher\n";
			cout << "\t\t"; system("PAUSE");
			goto repeatDate;
		}

	}

	this->content.STAFF_ID.ID = this->staff.ID;;
	this->content.ITEM_ID.ID = result[this->choose-1].ID;

	this->command.RefillContent(this->content);

	cout << "\t\tNew Stock Added\n\n\t\t";
	system("PAUSE");
	this->ItemListModule();

}

void Module::AidAddModule() {
repeatFunction:
 	HeaderModule("Aid Add Module");

	cout << "\t\tHow many new first aid : ";
	cin >> this->faid.STATUS;

	if (!this->command.ValidInteger(this->faid.STATUS)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatFunction;
	}

	if (this->faid.STATUS <= 0 || this->faid.STATUS > 100) {
		cout << "\t\tValue out of range (< 0) or (> 100)\n";
		goto repeatFunction;
	}

	for (int i = 0; i < faid.STATUS; i++){
		this->command.AidNew();
		cout << "\t\tNew Item Added\n";
		Sleep(500);
	}

	cout << "\t\tProcess Done\n\t\t";
	system("PAUSE");

	this->FirstAidListModule();
}

void Module::ApplicationModule() {
	repeatFunction:
	HeaderModule("Application Module");

	cout << "\t\t1 = List of application\n";
	cout << "\t\t2 = Exit\n";
	cout << "\t\tEnter your option [1, 2] : ";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatFunction;
	}

	switch (this->choose){
	case 1:
		this->ApplicationListModule();
	case 2:
		this->StaffIndexModule();
	default:
		cout << this->validcom;
		cout << "\t\t";system("PAUSE");;
		goto repeatFunction;
		break;
	}
}

void Module::ApplicationListModule() {
	HeaderModule("Application List Module");

	unordered_map<string, int>programMapKeyName;
	unordered_map<int, int>programMapKeyId;

	auto result = this->command.ApplicationList();

	if (result.size() == 0) {
		cout << "\t\tList is empty\n\n";
		cout << "\t\t";system("PAUSE");;
		this->ApplicationModule();
	}

	this->PrintElement("Name");
	this->PrintElement("Date Apply");
	this->PrintElement("Date Start");
	this->PrintElement("Date End");
	this->PrintElement("Total Apply");
	this->PrintLine(5);

	for (auto x : result) {

		programMapKeyName.insert(make_pair(x.NAME, x.ID));
		programMapKeyId.insert(make_pair(x.ID, x.TOTAL_APPLY));
		cout << endl;
		this->PrintElement(x.NAME);
		this->PrintElement(x.DATE_APPLY);
		this->PrintElement(x.DATE_START);
		this->PrintElement(x.DATE_END);
		this->PrintElement(x.TOTAL_APPLY);
		this->PrintLine(5);
	}



	repeatAsk:
	cout << "\n\t\tProve applicantion? [1 = Yes, 2= No] :";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatAsk;
	}

	switch (this->choose){
	case 1:
		reProgram:
		cout << "\t\tEnter program name : ";
		cin >> this->program.NAME;

		if (programMapKeyName.find(this->program.NAME) == programMapKeyName.end())
			goto reProgram;

		

		for (int i = 0;
			i < programMapKeyId.find(programMapKeyName.find(this->program.NAME)->second)->second;
			i++) {
			this->program.ID = programMapKeyName.find(this->program.NAME)->second;
			this->FirstAidRefillModule();
		}

		this->ApplicationModule();
		break;
	case 2:
		cout << "\t\t";
		system("PAUSE");
		this->ApplicationModule();
		break;
	default:
		cout << this->validcom;
		cout << "\t\t";system("PAUSE");;
		goto repeatAsk;
	}

}

void Module::FirstAidRefillModule() {
	HeaderModule("Firstaid Refill Module");

	unordered_set<string> duplicate;

	auto itemList = this->command.ItemListFilterZero();

	auto firstEmpty = this->command.FirstaidSingleEmpty();

	if (itemList.size() == 0 || firstEmpty == 0) {
		cout << "\t\tNo available item or first aid\n";
		cout << "\t\tPlease check the invetory\n\t\t";
		system("PAUSE");
		this->ApplicationListModule();

	}

	cout << "\t\tList of available aid\n";
	cout << "\t\tIf the item your need is not here (It maybe out of stock)\n";
	
	cout << endl;
	this->PrintElement("Name");
	this->PrintElement("Stock");
	this->PrintLine(3);

	for (auto x : itemList) {
		if (duplicate.insert(x.NAME).second) {
			cout << endl;
			this->PrintElement(x.NAME);
			this->PrintElement(x.MAX_LIMIT);
			this->PrintLine(3);
		}
	}
	duplicate.clear();
	for (auto x : itemList) {
		if (duplicate.insert(x.NAME).second) {
		reItem:
			cout << "Enter value for " << x.NAME << " : ";
			cin >> this->faidContent.TOTAL;

			if (!this->command.ValidInteger(this->faidContent.TOTAL)) {
				cout << this->validint;
				cout << "\t\t";system("PAUSE");;
				goto reItem;
			}
			if (this->faidContent.TOTAL <= 0 ||this->faidContent.TOTAL > this->command.ItemLimit(x.NAME)) {
				cout << this->validcom;
				cout << "\t\tMax in the box is " << this->command.ItemLimit(x.NAME) << endl;
				cout << "\t\t"; system("PAUSE");;
				goto reItem;
			}
			if (this->faidContent.TOTAL > x.MAX_LIMIT) {
				cout << this->validcom;
				cout << "\t\tMax is " << x.MAX_LIMIT << endl;
				cout << "\t\t";system("PAUSE");;
				goto reItem;
			}

			this->faidContent.CONTENT_ID.ID = x.ID;
			this->faidContent.FIRSTAID_ID.ID = firstEmpty;

			if (this->command.CheckFirstaidEmpty(this->faidContent) == 0)
				this->command.AssigntFirstaidContent(this->faidContent);
			else
				this->command.UpdateFirstaidEmpty(this->faidContent);
			
			this->command.UpdateItemTotal(this->faidContent);
		}
	}

	this->faidContent.FIRSTAID_ID.STATUS = 1;
	this->command.UpdateFirstaidStatus(this->faidContent);

	this->faidProgram.FIRSTAID_ID.ID = this->faidContent.FIRSTAID_ID.ID;
	this->faidProgram.PROGRAM_ID.ID = this->program.ID;
	this->faidProgram.STAFF_ID.ID = this->staff.ID;

	this->command.ProgramApprove(this->faidProgram);

	cout << "\t\tFirstaid is refill\n\t\t";

	system("PAUSE");

}

void Module::ReturnFirstaidModule() {
	HeaderModule("Return Firstaid Module");

	unordered_set<string> duplicate;
	auto result = this->command.BorrowFirstaid(this->applicant);

	if (result.size() == 0) {
		cout << "\t\tNo first aid in your possession\n\t\t";
		system("PAUSE");
		this->ApplicantMenuModule();
	}
		
	cout << endl;
	this->PrintElement("Program Name");
	this->PrintElement("Firstaids");
	this->PrintLine(2);

	int count = 0;
	for (auto x : result) {

		if (duplicate.insert(x.PROGRAM_ID.NAME).second && x.FIRSTAID_ID.STATUS == 1) {
			cout << endl;
			this->PrintElement(x.PROGRAM_ID.NAME);
			this->PrintElement(count_if(result.begin(), result.end(),
				[&](const FirstAid_Program&s) {return s.PROGRAM_ID.NAME == x.PROGRAM_ID.NAME; }));
			this->PrintLine(2);
			count++;
		}
	}

	reProgramName:
	cout << "\t\tWhich program you want to return\n";
	cout << "\t\tEnter program name : ";

	cin >> this->program.NAME;

	if (duplicate.find(this->program.NAME) == duplicate.end()) {
		cout << this->validcom;
		cout << "\t\t";system("PAUSE");;
		goto reProgramName;
	}

	this->command.UpdateReturnFirstAid(this->program);
	this->command.RemoveContent(this->program);
	this->command.UpdateReturnDate(this->program);

	cout << "\t\tReturn Success\n\t\t";
	system("PAUSE");
	this->ApplicantMenuModule();
}


void Module::FirstAidListModule() {
	HeaderModule("FirstAid List Module");

	auto result = this->command.AllFirstaid();
	auto result_program = this->command.BorrowFirstaid();

	cout << endl;
	this->PrintElement("Total first aid");
	this->PrintElement("Available");
	this->PrintElement("Not Available");
	this->PrintLine(3);
	
	cout << endl;
	this->PrintElement(result.size());
	this->PrintElement(count_if(result.begin(), result.end(),
		[&](const FirstAid&s) {return s.STATUS == 2; }));
	this->PrintElement(count_if(result.begin(), result.end(),
		[&](const FirstAid&s) {return s.STATUS == 1; }));
	this->PrintLine(3);

	if (result_program.size() != 0) {
		cout << endl;
		this->PrintElement("Program");
		this->PrintElement("Approve Date");
		this->PrintLine(2);
		for (auto x : result_program) {
			cout << endl;
			this->PrintElement(x.PROGRAM_ID.NAME);
			this->PrintElement(x.DATE_APPROVE);
			this->PrintLine(2);
		}
	}



repeatChoose:
	cout << "\n";
	cout << "\t\tChoose you operation\n";
	cout << "\t\t1 = Add New\n";
	cout << "\t\t2 = Exit\n";
	cout << "\t\tYour action :";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatChoose;
	}

	switch (this->choose) {
	case 1:
		this->AidAddModule();
		break;
	case 2:
		this->ItemInventoryModule();
		break;
	default:
		cout << this->validcom;
		cout << "\t\t";system("PAUSE");;
		goto repeatChoose;
		break;
	}
}

void Module::StaffListModule() {
	HeaderModule("Staff List Module");

	auto result = this->command.AllStaff();

	cout << endl;
	this->PrintElement("First name");
	this->PrintElement("Last Name");
	this->PrintElement("Position");
	this->PrintElement("Email address");
	this->PrintLine(4);
	for (auto x : result) {
		cout << endl;
		this->PrintElement(x.FIRSTNAME);
		this->PrintElement(x.LASTNAME);
		this->PrintElement(x.ROLE_ID.TITLE);
		this->PrintElement(x.EMAIL);
		this->PrintLine(4);
	}

	if (this->staff.ROLE_ID.TITLE == "Nurse") {
		cout << "\t\t";
		system("PAUSE");
		this->StaffIndexModule();
	}

repeatChoose:
	cout << "\n";
	cout << "\t\tChoose you operation\n";
	cout << "\t\t1 = Add New\n";
	cout << "\t\t2 = Remove\n";
	cout << "\t\t3 = Exit\n";
	cout << "\t\tYour actoin :";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << this->validint;
		cout << "\t\t";system("PAUSE");;
		goto repeatChoose;
	}

	switch (this->choose) {
	case 1:
		this->StaffAddModule();
		break;
	case 2:
		this->StaffRemoveModule();
	case 3:
		this->StaffIndexModule();
		break;
	default:
		cout << this->validcom;
		cout << "\t\t";system("PAUSE");;
		goto repeatChoose;
		break;
	}
}

void Module::StaffRemoveModule() {
	repeatFuntion:
	HeaderModule("Staff Remove Module");
	
	Staff remove;
	unordered_set<string> hold;
	auto result = this->command.AllStaff();
	

	cout << endl;
	this->PrintElement("Email address");
	this->PrintLine(1);
	for (auto x : result) {
		if (x.EMAIL != this->staff.EMAIL) {
			cout << endl;
			hold.insert(x.EMAIL);
			this->PrintElement(x.EMAIL);
			this->PrintLine(1);
		}
	}

	cout << "\t\tEnter the email to remove : ";
	cin >> remove.EMAIL;

	if (hold.find(remove.EMAIL) == hold.end()) {
		cout << "Not found\n";
		cout << "\t\t";system("PAUSE");;
		goto repeatFuntion;
	}

	this->command.RemoveStaff(remove);
	cout << "\t\tDone Remove\n";
	cout << "\t\t";
	system("PAUSE");
	this->StaffListModule();
}


void Module::ItemRemoveModule() {
	repeatFunction:
	HeaderModule("Item Remove Module");

	unordered_set<string> temp;
	auto result = this->command.ItemList();

	
	cout << endl;
	this->PrintElement("List Of Item");
	this->PrintLine(1);
	for (auto x : result) {
		temp.insert(x.NAME);
		this->PrintElement(x.NAME);
		this->PrintLine(1);
	}


	cout << "\n\t\tEnter item name to remove : ";
	cin >> this->item.NAME;

	if (temp.find(this->item.NAME) == temp.end()) {
		cout << "\t\tItem not found\n";
		cout << "\t\t";system("PAUSE");;
		goto repeatFunction;
	}

	if (this->command.ConditionRemoveItem(this->item) > 0) {
		cout << "\t\tCannot be deleted\n\t\tBeen used by applicant\n";
		cout << "\t\t";system("PAUSE");;
		system("PAUSE");
		this->ItemListModule();
	}

	this->command.RemoveItemContent(this->item);
	this->command.RemoveItem(this->item);

	cout << "\t\tItem Deleted\n";
	cout << "\t\t";system("PAUSE");;
	system("PAUSE");

	this->ItemListModule();
}

void Module::ReportModuleStaff() {
	HeaderModule("Report Module Staff");
	
	map<string, int> applicantNumberOfBorrow;
	map<string, int> frequentMonthBorrow;
	
	auto result = this->command.GenerateReport();

	for (auto x : result) {
		if(applicantNumberOfBorrow.find(x.PROGRAM_ID.APPLICANT_ID.ID) == applicantNumberOfBorrow.end())
			applicantNumberOfBorrow.insert(make_pair(x.PROGRAM_ID.APPLICANT_ID.ID, count_if(result.begin(), result.end(), 
					[&](FirstAid_Program&s) {return s.PROGRAM_ID.APPLICANT_ID.ID == x.PROGRAM_ID.APPLICANT_ID.ID; })));

		if(frequentMonthBorrow.find(x.PROGRAM_ID.DATE_START) == frequentMonthBorrow.end())
			frequentMonthBorrow.insert(make_pair(x.PROGRAM_ID.DATE_START, count_if(result.begin(), result.end(),
				[&](FirstAid_Program&s) {return s.PROGRAM_ID.DATE_START == x.PROGRAM_ID.DATE_START; })));
	}

	cout << "\t\tProgram base on month";
	this->PrintLine(2);
	this->PrintElement("Month");
	this->PrintElement("Graph");
	this->PrintLine(2);
	for (auto x : frequentMonthBorrow) {
		cout << endl;
		this->PrintElement(x.first);
		this->PrintElement(string(x.second, '#'));
		this->PrintLine(2);
	}

	cout << "\t\tProgram Approve";
	this->PrintLine(3);
	this->PrintElement("Approve");
	this->PrintElement("Not Approve");
	this->PrintElement("Program Total");
	this->PrintLine(3);
	this->PrintElement(count_if(result.begin(), result.end(),
			[&](FirstAid_Program&s) {return !s.DATE_APPROVE.empty(); }));
	this->PrintElement(count_if(result.begin(), result.end(),
			[&](FirstAid_Program&s) {return s.DATE_APPROVE.empty(); }));
	this->PrintElement(result.size());
	this->PrintLine(3);

	cout << "\t\tWho who most borrow";
	this->PrintLine(2);
	this->PrintElement("Matric");
	this->PrintElement("Borrow time");
	this->PrintLine(2);
	for (auto x : applicantNumberOfBorrow) {
		this->PrintElement(x.first);
		this->PrintElement(x.second);
		this->PrintLine(2);
	}
	system("PAUSE");
	this->StaffIndexModule();
}

void Module::ReportModuleApplicant() {
	HeaderModule("Report Module Applicant");

	auto result = this->command.GenerateReport(this->applicant);
	cout << "\t\tProgram Approve";
	this->PrintLine(3);
	this->PrintElement("Approve");
	this->PrintElement("Not Approve");
	this->PrintElement("Program Total");
	this->PrintLine(3);
	this->PrintElement(count_if(result.begin(), result.end(),
		[&](FirstAid_Program&s) {return !s.DATE_APPROVE.empty(); }));
	this->PrintElement(count_if(result.begin(), result.end(),
		[&](FirstAid_Program&s) {return s.DATE_APPROVE.empty(); }));
	this->PrintElement(result.size());
	this->PrintLine(3);

	system("PAUSE");
	this->ApplicantMenuModule();
}