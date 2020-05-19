#include <iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<map>
using namespace std;

multimap<int,string> savedReservations;
multimap<int, string> getSavedReservation(){
	return savedReservations;
}
class Person
{
	protected:
		string name, family, phone;
		int age;
	public:	
		//////////////////constructor///////////////
		Person(){}
		Person(string name, string family, string phone, int age){
			this->name=name;
			this->family=family;
			this->phone=phone;
			this->age=age;
		}
		//////////////////setter////////////////////
		void setName(string name){
			this->name=name;
		}
		void setFamily(string family){
			this->family=family;
		}
		void setPhone(string phone){
			this->phone=phone;
		}
		void setAge(int age){
			this->age=age;
		}
		/////////////////getter////////////////////
		string getName()const{
			return name;
		}
		string getFamily()const{
			return family;
		}
		string getPhone()const{
			return phone;
		}
		int getAge()const{
			return age;
		}
		////////////////functions///////////////////
		void report()const{
			cout<<name<<setw(4)<<family<<setw(6)<<phone<<setw(10)<<age<<"\n";
		}		
};
class Doctor:public Person
{
	private:
		string proficiency;
		int codeDoctor;
	public:	
		///////////////constructor//////////////////
		Doctor(){}
		Doctor(string name, string family, string phone,int age, int codeDoctor, string proficiency):Person(name,family,phone,age){
			this->proficiency=proficiency;
			this->codeDoctor=codeDoctor;
		}
		//////////////////setter////////////////////
		void setProficiency(string proficiency){
			this->proficiency=proficiency;
		}
		void setCodeDoctor(int codeDoctor){
			this->codeDoctor=codeDoctor;
		}
		/////////////////getter////////////////////
		string getProficiency()const{
			return proficiency;
		}
		int getCodeDoctor()const{
			return codeDoctor;
		}
		////////////////functions///////////////////
		void report()const{
			cout<<name<<setw(6)<<family<<setw(10)<<phone<<setw(8)<<age<<setw(6)<<proficiency<<setw(8)<<codeDoctor<<"\n";
		}
};
//////////////   Doctor   ///////////////
vector<Doctor> listDoctor, listDoctorTemp;
fstream outputFileDoc;
void writeDoctor(){
	string name, family, phone, proficiency;
	int age,codeDoctor;
	cout<<"\nenter name:";
	cin>>name;
	cout<<"\nenter family:";
	cin>>family;
	cout<<"\nenter phone:";
	cin>>phone;
	cout<<"\nenter age:";
	cin>>age;
	cout<<"\nenter proficiency:";
	cin>>proficiency;
	cout<<"\nenter codeDoctor:";
	cin>>codeDoctor;
	listDoctor.push_back(Doctor(name,family,phone,age,codeDoctor,proficiency));
	outputFileDoc.open("doctor.csv",ios::app);
	outputFileDoc<<name+","+family+","+phone+","+to_string(age)+","+proficiency+","+to_string(codeDoctor)+"\n";
	
}
void displayAllDoc(){
	cout<<"*************** Hospital Managment System ***************\n\n";
	cout<<"#########################################################\n";
	cout<<"#################   Report doctors   ####################\n";
	cout<<"#########################################################\n";
	cout<<"=========================================================\n";
	cout<<"=Name   Family   Phone   Age    Proficiency   codeDoctor=\n";
	cout<<"=========================================================\n";
	for(int i=0;i<listDoctor.size();i++){
		cout<<i+1<<".";
		listDoctor[i].report();
	}
}
void displayOneDoc(int codeDoctor){
	cout<<"*************** Hospital Managment System ***************\n\n";
	cout<<"#########################################################\n";
	cout<<"##################   Report doctor  #####################\n";
	cout<<"#########################################################\n";
	cout<<"=========================================================\n";
	cout<<"=Name   Family    Phone   Age   Proficiency   codeDoctor=\n";
	cout<<"=========================================================\n";
	for(int i=0;i<listDoctor.size();i++){
		if(listDoctor[i].getCodeDoctor()==codeDoctor){
			listDoctor[i].report();
		}
	}
}
void modifyDoc(int code){
	string name, family, phone;
	int choice, age;
	for(int i=0;i<listDoctor.size();i++){
		if(listDoctor[i].getCodeDoctor()==code){
			cout<<"*************** Hospital Managment System ***************\n\n";
			cout<<"#########################################################\n";
			cout<<"##################   Modify Doctor   ####################\n";
			cout<<"#########################################################\n";
			cout<<"1.Name\n";
			cout<<"2.Family\n";
			cout<<"3.Phone\n";
			cout<<"4.Age\n";
			cout<<"\nenter choice(1|2|3|4):";
			cin>>choice;
			switch(choice){
				case 1:
					cout<<"enter new name:";
					cin>>name;
					listDoctor[i].setName(name);
					break;
				case 2:
					cout<<"enter new family:";
					cin>>family;
					listDoctor[i].setFamily(family);
					break;
				case 3:
					cout<<"enter new phone:";
					cin>>phone;
					listDoctor[i].setPhone(phone);
					break;
				case 4:
					cout<<"enter new age:";
					cin>>age;
					listDoctor[i].setAge(age);
					break;
				default:
					cout<<"invalid choice.\n";				
			}
		}
	}
}
void deleteAllDoc(){
	listDoctor.clear();
}
void deleteOneDoc(int code){
	for(int i=0;i<listDoctor.size();i++){
		if(listDoctor[i].getCodeDoctor()!=code){
			listDoctorTemp.push_back(listDoctor[i]);
		}
	}
	listDoctor=listDoctorTemp;
	vector<Doctor>().swap(listDoctorTemp);
}
vector<Doctor> getDoctorList(){
	return listDoctor;
}

void printSavedReservation(int code){
	cout<<"*************** Hospital Managment System ***************\n\n\n";
	cout<<"#########################################################\n";
	cout<<"##################   Report doctor   ####################\n";
	cout<<"#########################################################\n";
	multimap<int, string> list=getSavedReservation();
	for(multimap<int ,string>::iterator it=list.begin();it!=list.end();it++){
		if(code==it->first){
			cout<<it->second<<"\n";
		}
	}
}

class Patient:public Person
{
	private:
		string diseaseType, doctorName;
		int codePatient;
		vector<Doctor> reserves;
	public:	
		///////////////constructor//////////////////
		Patient(){}
		Patient(string name, string family, string phone, int age, string diseaseType,int codePatient, string doctorName):Person(name, family, phone, age){
			this->diseaseType=diseaseType;
			this->codePatient=codePatient;
			this->doctorName=doctorName;
		}
		//////////////////setter////////////////////
		void setdiseaseType(string diseaseType){
			this->diseaseType=diseaseType;
		}
		void setCodePatient(int codePatient){
			this->codePatient=codePatient;
		}
		void setDoctorName(string doctorName){
			this->doctorName=doctorName;
		}
		/////////////////getter////////////////////
		string getDiseaseType()const{
			return diseaseType;
		}
		int getCodePatient()const{
			return codePatient;
		}
		string getDoctorName()const{
			return doctorName;
		}
		/////////////functions////////////////////
		void report()const{
			cout<<name<<setw(4)<<family<<setw(6)<<phone<<setw(10)<<age<<setw(10)<<diseaseType<<setw(6)<<codePatient<<setw(6)<<doctorName<<"\n";
		}
		string selectDoctor(string ,string ,string);
};

//////////////   Patient   ///////////////
vector<Patient> listPatient, listPatientTemp;
fstream outputFilePat;
void writePatient(){
	Patient p;
	string name, family, phone, diseaseType, doctorName;
	int age, codePatient;
	cout<<"\nenter name:";
	cin>>name;
	cout<<"\nenter family:";
	cin>>family;
	cout<<"\nenter phone:";
	cin>>phone;
	cout<<"\nenter age:";
	cin>>age;
	cout<<"\nenter disease Type:";
	cin>>diseaseType;
	cout<<"\nenter code patient:";
	cin>>codePatient;
	doctorName=p.selectDoctor(name, family, diseaseType);
	listPatient.push_back(Patient(name,family,phone,age,diseaseType,codePatient,doctorName));
	outputFilePat.open("Patient.csv",ios::app);
	outputFilePat<<name+","+family+","+phone+","+to_string(age)+","+diseaseType+","+to_string(codePatient)+","+doctorName+"\n";
}
void displayAllPat(){
	cout<<"**************** Hospital Managment System ***************\n\n";
	cout<<"##########################################################\n";
	cout<<"##################   Report patient   ####################\n";
	cout<<"##########################################################\n";
	cout<<"==========================================================\n";
	cout<<"=Name Family Phone Age diseaseType doctorName codePatient=\n";
	cout<<"==========================================================\n";
	for(int i=0;i<listPatient.size();i++){
		cout<<i+1<<".";
		listPatient[i].report();
	}
}
void displayOnePat(int code){
	cout<<"**************** Hospital Managment System ***************\n\n";
	cout<<"##########################################################\n";
	cout<<"###################   Report ptients  ####################\n";
	cout<<"##########################################################\n";
	cout<<"==========================================================\n";
	cout<<"=Name Family Phone Age diseaseType doctorName codePatient=\n";
	cout<<"==========================================================\n";
	for(int i=0;i<listPatient.size();i++){
		if(listPatient[i].getCodePatient()==code){
			listPatient[i].report();
		}
	}
}
void modifyPat(int code){
	string name, family, phone;
	int choice, age;
	for(int i=0;i<listPatient.size();i++){
		if(listPatient[i].getCodePatient()==code){
			cout<<"**************** Hospital Managment System ***************\n\n";
			cout<<"##########################################################\n";
			cout<<"###################   Modify menu  #######################\n";
			cout<<"##########################################################\n";
			cout<<"1.Name\n";
			cout<<"2.Family\n";
			cout<<"3.Phone\n";
			cout<<"4.Age\n";
			cout<<"\nenter choice(1|2|3|4):";
			cin>>choice;
			switch(choice){
				case 1:
					cout<<"enter new name:";
					cin>>name;
					listPatient[i].setName(name);
					break;
				case 2:
					cout<<"enter new family:";
					cin>>family;
					listPatient[i].setFamily(family);
					break;
				case 3:
					cout<<"enter new phone:";
					cin>>phone;
					listPatient[i].setPhone(phone);
					break;
				case 4:
					cout<<"enter new age:";
					cin>>age;
					listPatient[i].setAge(age);
					break;
				default:
					cout<<"invalid choice.\n";
					break;				
			}
		}
	}
}
void deleteAllPat(){
	listPatient.clear();
}
void deleteOnePat(int code){
	for(int i=0;i<listPatient.size();i++){
		if(listPatient[i].getCodePatient()!=code){
			listPatientTemp.push_back(listPatient[i]);
		}
	}
	listPatient=listPatientTemp;
	vector<Patient>().swap(listPatientTemp);
}
vector<Patient> getPatientList(){
	return listPatient;
}
string Patient::selectDoctor(string name, string family, string diseaseType){
	string doctorName;
	int code;
	cout<<"\nenter the code of doctor to reserve:";
	cin>>code;
	vector<Doctor> list=getDoctorList();
	for(int i=0;i<list.size();i++){	
		if(list[i].getCodeDoctor()==code){
			doctorName=list[i].getName();
			doctorName+=" ";
			doctorName+=list[i].getFamily();
			reserves.push_back(list[i]);
			savedReservations.insert(pair<int, string>(code,name+","+family+","+diseaseType));
			return doctorName;
		}
	}
}
//////////////// menu/////////////////////////

void reportMenu(){
	int choice, c;
	do{
		system("cls");
		cout<<"*************** Hospital Managment System ***************\n\n";
		cout<<"#########################################################\n";
		cout<<"##################   Report Menu   ######################\n";
		cout<<"#########################################################\n";
		cout<<"\n1.Doctor report";
		cout<<"\n2.Patient report";
		cout<<"\n3.Back to main menu";
		cout<<"\n\nenter your choice(1|2|3):";
		cin>>choice;
		switch(choice){
			case 1:
				do{
					cout<<"*************** Hospital Managment System ***************\n\n";
					cout<<"#########################################################\n";
					cout<<"##################   Report Menu   ######################\n";
					cout<<"#########################################################\n";
					cout<<"\n1.All doctors record";
					cout<<"\n2.A doctor record";
					cout<<"\n3.Patient list";
					cout<<"\n4.Back to report menu";
					cout<<"\n\nenter your choice(1|2|3|4):";
					cin>>c;
					switch(c){
						case 1:
							system("cls");
							displayAllDoc();
							break;
						case 2:
							int code;
							cout<<"Enter doctor code to report:";
							cin>>code;
							system("cls");
							displayOneDoc(code);
							break;
						case 3:
							cout<<"Enter doctor code to report:";
							cin>>code;
							system("cls");
							printSavedReservation(code);
							break;
						case 4:
							break;
						default:
							cout<<"invalid choice.try again.";
							system("cls");		
					}
				}while(c!=4);
				break;
			case 2:
				do{
					cout<<"*************** Hospital Managment System ***************\n\n";
					cout<<"#########################################################\n";
					cout<<"##################   Report Menu   ######################\n";
					cout<<"#########################################################\n";
					cout<<"\n1.All patient record";
					cout<<"\n2.A patient record";
					cout<<"\n3.Back to report menu";
					cout<<"\n\nenter your choice(1|2|3):";
					cin>>c;
					switch(c){
						case 1:
							system("cls");
							displayAllPat();
							break;
						case 2:
							int code;
							cout<<"Enter patient code to report:";
							cin>>code;
							system("cls");
							displayOnePat(code);
							break;
						case 3:
							break;
						default:
							cout<<"invalid choice.try again.";
							system("cls");
							break;		
					}
				}while(c!=3);
				break;
			case 3:
				break;
			default:
				cout<<"invalid choice.try again.";
				system("cls");
				break;	
		}
	}while(choice!=3);
}
void entryMenu(){
	int choice;
	do{
		system("cls");
		cout<<"*************** Hospital Managment System ***************\n\n\n";
		cout<<"#########################################################\n";
		cout<<"###################   Entry Menu   ######################\n";
		cout<<"#########################################################\n";
		cout<<"\n1.Doctor";
		cout<<"\n2.Patient";
		cout<<"\n3.Back to main menu";
		cout<<"\n\nenter your choice(1|2|3):";
		cin>>choice;
		switch(choice){
			case 1:
				do{
				system("cls");
				cout<<"*************** Hospital Managment System ***************\n\n\n";
				cout<<"#########################################################\n";
				cout<<"##################   Doctor Menu   ######################\n";
				cout<<"#########################################################\n";
				cout<<"\n1.Add a doctor";
				cout<<"\n2.Modify a doctor";
				cout<<"\n3.Delete all doctors";
				cout<<"\n4.Delete a doctor";
				cout<<"\n5.Back to report menu";
				cout<<"\n\nenter your choice(1|2|3|4|5):";
				cin>>choice;
				switch(choice){
					case 1:
						writeDoctor();
						break;
					case 2:
						int code;
						cout<<"Enter doctor code to modify:";
						cin>>code;
						modifyDoc(code);
						break;
					case 3:
						deleteAllDoc();
						break;
					case 4:
						cout<<"Enter doctor code to delete:";
						cin>>code;
						deleteOneDoc(code);
						break;
					case 5:
						break;	
					default:
						cout<<"invalid choice.try again.";		
				}
				}while(choice!=5);
				break;
			case 2:
				do{
					system("cls");
					cout<<"*************** Hospital Managment System ***************\n\n\n";
					cout<<"#########################################################\n";
					cout<<"##################   Patient Menu   #####################\n";
					cout<<"#########################################################\n";
					cout<<"\n1.Add a patient";
					cout<<"\n2.Modify a patient";
					cout<<"\n3.Delete all patients";
					cout<<"\n4.Delete a patient";
					cout<<"\n5.Back to report menu";
					cout<<"\n\nenter your choice(1|2|3|4|5|6):";
					cin>>choice;
					switch(choice){
						case 1:
							writePatient();
							break;
						case 2:
							int code;
							cout<<"Enter patient code to modify:";
							cin>>code;
							modifyPat(code);
							break;
						case 3:
							deleteAllPat();
							break;
						case 4:
							cout<<"Enter patient code to delete:";
							cin>>code;
							deleteOnePat(code);
							break;	
						case 5:
							break;	
						default:
							cout<<"invalid choice.try again.";
							break;		
					}
				}while(choice!=5);
				break;
			case 3:
				break;
			default:
				cout<<"invalid choice.try again.";
				break;	
		}
	}while(choice!=3);
}

int main() {
	int choice;
	do{
		system("cls");
		cout<<"*************** Hospital Managment System ***************\n\n";
		cout<<"#########################################################\n";
		cout<<"##################   Main Menu   ########################\n";
		cout<<"#########################################################\n";
		cout<<"\n1.Reports";
		cout<<"\n2.add/delete/modify";
		cout<<"\n3.exit";
		cout<<"\n\nenter your choice(1|2|3):";
		cin>>choice;
		switch(choice){
			case 1:
				reportMenu();
				break;
			case 2:
				entryMenu();
				break;
			case 3:
				break;	
			default:
				cout<<"invalid choice.try again.\n";
		}
	}while(choice!=3);
	
}
