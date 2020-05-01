#include <iostream>
#include <string>
#include <iomanip>
#include "Command.h"
#include "Module.h"
#include "TableStruct.h"
using namespace std;

Module::Module() {
	this->command.Connect();
}

Module::~Module() {}

template<class DataType> void Module::PrintElement(DataType data){
	cout << left << setw(5) << "|" << setw(15) << data;
}

void Module::PrintLine(int columnnum) {
	cout << "\n\n" << string(20 * columnnum, '-') << "\n\n";
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
	cout << "\t\t1 = Staff Login (DEV)\n";
	cout << "\t\t2 = Applicant(DEV)\n";
	cout << "\t\t3 = Exit\n";
	cout << "\t\tEnter your option [1, 2, 3] : ";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << "\t\t***Invalid Integer***\n";
		Sleep(1000);
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
		cout << "\t\t***Invalid Combination***\n";
		Sleep(1000);
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
	cout << "\t\t1 = First Time Applicant(YES)\n";
	cout << "\t\t2 = Applicant Login(YES)\n";
	cout << "\t\t3 = Exit\n";
	cout << "\t\tEnter your option [1, 2, 3] : ";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << "\t\t***Invalid Integer***\n";
		Sleep(1000);
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
		cout << "\t\t***Invalid Combination***\n";
		Sleep(1000);
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
			cout << "\t\t***Invalid Integer***\n";
			Sleep(1000);
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
		cout << "\t\t***Invalid Email***\n";
		Sleep(1000);
		goto repeatEmail;
	}

	this->command.NewApplicant(this->applicant);

	cout << "\t\tNew Record Save...Welcome " << this->applicant.FIRST_NAME << endl;
	cout << "\t\tYou Are " << this->applicant.TYPE << endl;
	Sleep(1000);

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
			cout << "\t\t***Invalid Integer***\n";
			Sleep(1000);
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
	Sleep(1000);

	this->ApplicantMenuModule();

}

void Module::ApplicantMenuModule() {
repeatFunction:
	HeaderModule("Applicant Menu Module");

	cout << "\t\tAvailable Action :\n\n";
	cout << "\t\t1 = Make an application (YES)\n";
	cout << "\t\t2 = Return first aid kit (NOT)\n";
	cout << "\t\t3 = View application status (YES)\n";
	cout << "\t\t4 = Exit\n";
	cout << "\t\tEnter your option [1, 2, 3, 4, 5] : ";
	cin >> this->choose;
	
	if (!this->command.ValidInteger(this->choose)) {
		cout << "\t\t***Invalid Integer***\n";
		Sleep(1000);
		goto repeatFunction;
	}

	switch (this->choose) {
	case 1:
		this->NewProgramModule();
		break;
	case 2:
		break;
	case 3:
		this->ViewProgramStatusModule();
		break;
	case 4:
		this->IndexModule();
		break;
	default:
		cout << "\t\t***Invalid Combination***\n";
		Sleep(1000);
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
		Sleep(1000);
		goto repeatDateStart;
	}

	if ( this->command.BetweenDate(this->program.DATE_START) < 7 ||
		 this->command.CompareDate(this->program.DATE_START) == 1) {
		cout << "\t\t***Cannot apply when the program date is already pass   ***\n";
		cout << "\t\t***Program date must at least 7 day from the application***\n";
		Sleep(1000);
		goto repeatDateStart;
	}

	repeatDateEnd:
	cout << "\t\tEnter program end date\n";
	cout << "\t\tFormat [DD/MM/YYYY]  :";
	cin >> this->program.DATE_END;

	if (!this->command.ValidDate(this->program.DATE_END)) {
		cout << "\t\tInvalid date format\n";
		Sleep(1000);
		goto repeatDateEnd;
	}

	if (this->command.CompareDate(this->program.DATE_START, this->program.DATE_END) == 1) {
		cout << "\t\t***Program end program must be the same as start or later***\n";
		Sleep(1000);
		goto repeatDateEnd;
	}

	repeatTotal:
	cout << "\t\tTotal apply          :";
	cin >> this->program.TOTAL_APPLY;

	if (!this->command.ValidInteger(this->program.TOTAL_APPLY)) {
		cout << "\t\t***Invalid Integer***\n";
		Sleep(1000);
		goto repeatTotal;
	}

	if (this->program.TOTAL_APPLY <= 0 || this->program.TOTAL_APPLY >= 4) {
		cout << "\t\t***Min 1 Max 3***\n";
		Sleep(1000);
		goto repeatTotal;
	}

	this->program.APPLICANT_ID.ID = this->applicant.ID;
	this->program.DATE_APPLY = this->command.DateToString(this->command.CurrentDate());

	this->command.NewProgram(this->program);

	cout << "\t\tNew application by " << this->applicant.TYPE << endl;
	cout << "\t\t" << this->applicant.FIRST_NAME << " ID is " << this->applicant.ID;
	Sleep(1000);

	this->ApplicantMenuModule();
}

void Module::ViewProgramStatusModule() {

	HeaderModule("View Program Status Module");

	auto result = this->command.ViewProgram(this->applicant);
	
	cout << endl;
	this->PrintElement("Program Name");
	this->PrintElement("Date Apply");
	this->PrintElement("Date Start");
	this->PrintElement("Day Left");
	this->PrintElement("Total Apply");
	this->PrintElement("Approve Date");
	this->PrintLine(6);

	for (auto x : result) {
		cout << endl;
		this->PrintElement(x.PROGRAM_ID.NAME);
		this->PrintElement(x.PROGRAM_ID.DATE_APPLY);
		this->PrintElement(x.PROGRAM_ID.DATE_START);
		this->PrintElement(this->command.BetweenDate(x.PROGRAM_ID.DATE_START));
		this->PrintElement(x.PROGRAM_ID.TOTAL_APPLY);
		this->PrintElement(x.DATE_APPROVE);
		this->PrintLine(6);

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
		cout << "\t\t***Invalid Email***\n";
		Sleep(1000);
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
			cout << "\t\t***Invalid Integer***\n";
			Sleep(1000);
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

	cout << "\t\tYou are " << this->staff.ROLE_ID.TITLE;
	Sleep(1000);

	this->StaffIndexModule();

}

void Module::StaffIndexModule() {
	repeatFunction:
	HeaderModule("Staff Index Module");

	cout << "\t\tAvailable Action :\n\n";
	cout << "\t\t1 = Item Inventory(DEV)\n";
	cout << "\t\t2 = Application(DEV)\n";
	cout << "\t\t3 = Staff(DEV)\n";
	cout << "\t\t4 = Exit\n";
	cout << "\t\tEnter your option [1, 2, 3, 4, 5] : ";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << "\t\t***Invalid Integer***\n";
		Sleep(1000);
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
		this->StaffAddModule();
		break;
	case 4:
		this->IndexModule();
		break;
	default:
		cout << "\t\t***Invalid Combination***\n";
		Sleep(1000);
		goto repeatFunction;
		break;
	}

}

void Module::StaffAddModule() {
	HeaderModule("Staff Add Module");

	Staff newStaff;

	if (this->staff.ROLE_ID.ID == 1) {
		cout << "\t\tRole\n";
		cout << "[1=Doctor, 2=Nurse] : ";
		cin >> newStaff.ROLE_ID.ID;
	}
	else {
		newStaff.ROLE_ID.ID = 2;
	}

	cout << "\t\tFirst name : ";
	cin >> newStaff.FIRSTNAME;

	cout << "\t\tLast name : ";
	cin >> newStaff.LASTNAME;

	reBirth:
	cout << "\t\tBirthdate\n";
	cout << "\t\t[DD/MM/YYYY] : \n";
	cin >> newStaff.BIRTHDATE;

	if (!this->command.ValidDate(newStaff.BIRTHDATE)) {
		cout << "\t\t***Invalid Date Format***\n";
		Sleep(1000);
		goto reBirth;
	}

	cout << "\t\tPassword  : ";
	cin >> newStaff.PASSWORD;

	newStaff.EMAIL = newStaff.FIRSTNAME + newStaff.LASTNAME[0] + "@utem.edu.my";

	//will add command hire;

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

	cout << "\t\t1 = Inventory list(YES)\n";
	cout << "\t\t2 = Inventory New(YES)\n";
	cout << "\t\t3 = Refill Inventory(YES)\n";
	cout << "\t\t4 = First Aid Add (YES)\n";
	cout << "\t\t5 = Exit\n";
	cout << "\t\tEnter your option [1, 2, 3, 4, 5] : ";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << "\t\t***Invalid Integer***\n";
		Sleep(1000);
		goto repeatFunction;
	}

	switch (this->choose){
	case 1:
		this->ItemListModule();
		break;
	case 2:
		this->ItemAddModule();
		break;
	case 3:
		this->RefillItemModule();
		break;
	case 4:
		this->AidAddModule();
		break;
	case 5:
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

	this->PrintElement("Id");
	this->PrintElement("Name");
	this->PrintElement("Number In Stock");
	this->PrintLine(3);

	for (auto x : result) {
		cout << endl;
		this->PrintElement(x.ID);
		this->PrintElement(x.NAME);
		this->PrintElement(x.MAX_LIMIT);
		this->PrintLine(3);
	}

	cout << "\t\t";
	system("PAUSE");
	this->ItemInventoryModule();
}

void Module::ItemAddModule() {
	HeaderModule("Item Add Module");

	cout << "\t\tItem name             : ";
	cin >> this->item.NAME;

	repeatMax:
	cout << "\t\tMax item in first aid :";
	cin >> this->item.MAX_LIMIT;

	if (!this->command.ValidInteger(this->item.MAX_LIMIT)) {
		cout << "\t\t***Invalid Integer***\n";
		Sleep(1000);
		goto repeatMax;
	}

	repeatDateL:
	cout << "\t\tHave a date limit\n";
	cout << "\t\t[1 = Yes, 2 = No]     :";
	cin >> this->item.DATE_LIMIT;
	
	if (!this->command.ValidInteger(this->item.DATE_LIMIT)) {
		cout << "\t\t***Invalid Integer***\n";
		Sleep(1000);
		goto repeatDateL;
	}

	if (this->item.DATE_LIMIT < 1 || this->item.DATE_LIMIT > 2) {
		cout << "\t\tInvalid Choose\n";
		Sleep(1000);
		goto repeatDateL;
	}

	this->command.ItemNew(this->item);

	cout << "\t\tNew Item Added\n";
	cout << "\t\t";
	system("PAUSE");
	this->ItemInventoryModule();
}

void Module::RefillItemModule() {
	repeatFunction:
	HeaderModule("Refill Item Module");
	
	auto result = this->command.ItemList();

	auto i = 1;
	for (auto x : result) {
		cout << "\t\t" << i << " = " << x.ID << "|" << x.NAME << endl;
		i++;
	}
	
	cout << "\t\tYour Choose : ";
	cin >> this->choose;



	if (!this->command.ValidInteger(this->choose)) {
		cout << "\t\t***Invalid Integer***\n";
		Sleep(1000);
		goto repeatFunction;
	}

	if (this->choose < 1 || this->choose > i - 1) {
		goto repeatFunction;
	}

	repeatTotal:
	cout << "\t\tHow many You want to add : ";
	cin >> this->content.TOTAL;

	if (!this->command.ValidInteger(this->content.TOTAL)) {
		cout << "\t\t***Invalid Integer***\n";
		Sleep(1000);
		goto repeatTotal;
	}

	if (this->content.TOTAL < 0 || this->content.TOTAL > 100) {
		cout << "\t\tValue To big (>100) or small (<0)\n";
		Sleep(1000);
		goto repeatTotal;
	}

	this->content.DATE_EXP = "";
	if (result[this->choose-1].DATE_LIMIT == 1) {
		repeatDate:
		cout << "\t\tEnter Expired date : ";
		cin >> this->content.DATE_EXP;

		if (!this->command.ValidDate(this->content.DATE_EXP)) {
			cout << "\t\tInvalid date format\n";
			Sleep(1000);
			goto repeatDate;
		}

	}

	this->content.STAFF_ID.ID = this->staff.ID;;
	this->content.ITEM_ID.ID = result[this->choose-1].ID;

	this->command.RefillContent(this->content);

	cout << "\t\tNew Stock Added\n\n\t\t";
	system("PAUSE");

	this->ItemInventoryModule();
}

void Module::AidAddModule() {
repeatFunction:
 	HeaderModule("Aid Add Module");

	cout << "\t\tHow many new first aid : ";
	cin >> this->faid.STATUS;

	if (!this->command.ValidInteger(this->faid.STATUS)) {
		cout << "\t\t***Invalid Integer***\n";
		Sleep(1000);
		goto repeatFunction;
	}

	if (this->faid.STATUS < 0 || this->faid.STATUS > 100) {
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

	this->ItemInventoryModule();
}

void Module::ApplicationModule() {
	repeatFunction:
	HeaderModule("Application Module");

	cout << "\t\t1 =List of application\n";
	cout << "\t\tEnter your option [1, 2, 3, 4, 5] : ";
	cin >> this->choose;

	if (!this->command.ValidInteger(this->choose)) {
		cout << "\t\t***Invalid Integer***\n";
		Sleep(1000);
		goto repeatFunction;
	}

	switch (this->choose){
	case 1:
		this->ApplicationListModule();
	default:
		goto repeatFunction;
		break;
	}
}

void Module::ApplicationListModule() {
	HeaderModule("Application List Module");

	auto result = this->command.ApplicationList();


	this->PrintElement("Name");
	this->PrintElement("Date Apply");
	this->PrintElement("Date Start");
	this->PrintElement("Date End");
	this->PrintElement("Total Apply");
	this->PrintLine(5);

	for (auto x : result) {
		cout << endl;
		this->PrintElement(x.NAME);
		this->PrintElement(x.DATE_APPLY);
		this->PrintElement(x.DATE_START);
		this->PrintElement(x.DATE_END);
		this->PrintElement(x.TOTAL_APPLY);
		this->PrintLine(5);
	}

	cout << "\t\t";
	system("PAUSE");

	this->ApplicationModule();

}