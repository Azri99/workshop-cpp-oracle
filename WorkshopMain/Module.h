#ifndef MODULE_H
#define MODULE_H

#include <iostream>
#include "Command.h"
#include "TableStruct.h"

using namespace std;

class Module{
private:
	int				 choose;
	Command			 command;
	Applicant		 applicant;
	Program			 program;
	Staff			 staff;
	Item			 item;
	Content			 content;
	FirstAid		 faid;
public:

	Module();
	~Module();
	
	//Print data2 dalam satu line
	template<class DataType> void PrintElement(DataType);
	
	//print line untuk seperate column
	void PrintLine(int);

	//Header
	void HeaderModule(string);
	
	//Index Module
	void IndexModule();

	//Exit Module 
	//Tamat la kisahh benda ni
	void ExitModule();
	
	////////////////////////
	//Applicant Module Start
	
	//Applicant Index Module
	//Menu utama untuk pemohon
	void ApplicantIndexModule();
	
	//New Applicant Module
	//First time jadi nak daftar dulu baru mohon 
	void NewApplicantModule();

	//Applicant Login Module
	//Dah daftar so kita log masuk la apa lagi
	void ApplicantLoginModule();

	//Applicant Menu Module
	//Fikir la nak buat apa wahai pemohon(applicant)
	void ApplicantMenuModule();

	//New Program Module
	//pinjam first adi untuk module tu
	void NewProgramModule();
	
	//Tengok status permohonan
	void ViewProgramStatusModule();


	//////////////////////
	//Applicant Module End


	//////////////////////
	//Staff Module Start


	//Staff Login Module
	//kita log masuk la apa lagi
	void StaffLoginModule();

	//Staff Index Module
	//Menu utama untuk staff
	void StaffIndexModule();

	//Item Iventory
	//Nak letak barang baru @ Nak Refill barang tu
	//Hanya boleh diaccess oleh Doctor-Type
	void ItemInventoryModule();
	
	//Item List Inventory
	//Listkan semua barang yang ada dalam inventory
	//Hanya boleh diaccess oleh Doctor-Type
	void ItemListModule();

	//Item Add Module
	//Add new item in the inventory
	void ItemAddModule();

	//RefillItemModile
	//Untuk tambah berepa banyak barang ada dalam tu
	void RefillItemModule();

	//Simply Add New First Aid To Inventory
	void AidAddModule();

	void ApplicationModule();

	void ApplicationListModule();
};

#endif // !MODULE_H
