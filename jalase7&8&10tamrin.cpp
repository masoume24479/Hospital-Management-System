#include <iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<fstream>
#include<map>
#include<sstream>
#include <conio.h>
using namespace std;
fstream outputFile;
string doctorFile="Doctors.csv";
string patientFile="Patients.csv";
string PDFile="PD.csv";

multimap<int,string> savedReservations;
multimap<int, string> getSavedReservation(){
	return savedReservations;
}

long int getSizeOfFile(string fileName){
	long int size=0;
	ifstream iFile(fileName);
	iFile.seekg(0,ios::end);
	size=iFile.tellg();
	return size;
}
class CSVReader{
	private:
		string fileName;
		char delimeter;
	public:
		CSVReader(string fileName,char delimeter=','){
			this->fileName=fileName;
			this->delimeter=delimeter;
		}
		vector<vector<string>> getData(){
			vector<vector<string>> dataList;
			vector<string> vec;
			ifstream file(fileName);
			string line="",word;
			while(getline(file,line)){
				vec.clear();
				stringstream s (line);
				while(getline(s ,word,delimeter)){
					vec.push_back(word);
				}
				dataList.push_back(vec);
			}
			file.close();
			
			return dataList;
		}
};
class Person{
	protected:
		string name, family, phone;
		int age;
	public:	
		//////////////////constructor///////////////
		Person(){}
		~Person(){cout<<"destructor of class person called.\n";}
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
			cout<<name<<setw(6)<<family<<setw(6)<<phone<<setw(6)<<age<<"\n";
		}
};
class Employee:public Person{
	protected:
		int codeEmployee;
	public:	
		/////////constructor//////////////////
		Employee(){}
		~Employee(){cout<<"destructor of class Employee called.\n";}
		Employee(string name, string family, string phone, int age,int codeEmployee):Person(name,family,phone,age){
			this->codeEmployee=codeEmployee;		
		}
		//////////setter//////////////////
		void setEmpCode(int cedeEmployee){
			this->codeEmployee=cedeEmployee;
		}
		///////////getter//////////////
		int getCodeEmp(){
			return codeEmployee;
		}
		//////////functions/////////////////
		void report()const{
			cout<<name<<setw(6)<<family<<setw(6)<<phone<<setw(4)<<age<<setw(6)<<codeEmployee<<"\n";
		}
};
class Doctor:public Employee{
	private:
		string proficiency;
	public:	
		///////////////constructor//////////////////
		Doctor(){}
		Doctor(int codeDoctor, string name, string family, string phone, int age, string proficiency):Employee(name,family,phone,age,codeDoctor){
			this->proficiency=proficiency;
		}
		//////////////////setter////////////////////
		void setProficiency(string proficiency){
			this->proficiency=proficiency;
		}
		/////////////////getter////////////////////
		string getProficiency()const{
			return proficiency;
		}
		void report()const{
			cout<<codeEmployee<<setw(6)<<name<<setw(6)<<family<<setw(10)<<phone<<setw(8)<<age<<setw(6)<<proficiency<<setw(8)<<"\n";
		}
		void saveReservation();
		friend ostream &operator <<(ostream &out, const Doctor &obj){
			out<<obj.codeEmployee<<" , "<<obj.name<<" , "<<obj.family<<" , "<<obj.phone<<" , "<<obj.age<<" , "<<obj.proficiency<<"\n";
			return out;
		}
		friend istream &operator <<(istream &in, Doctor &obj){
			in>>obj.codeEmployee;
			in>>obj.name;
			in>>obj.family;
			in>>obj.phone;
			in>>obj.age;
			in>>obj.proficiency;
			return in;
		}
};
class Patient:public Person{
	private:
		//int codeDoctor;
		string illnessType,doctorName;
		int codePatient;
		vector<Doctor> reserves;
	public:	
		///////////////constructor//////////////////
		Patient(){}
		Patient(int codePatient,string name, string family, string phone, int age, string doctorName,string illnessType):Person(name, family, phone, age){
			this->illnessType=illnessType;
			this->doctorName=doctorName;
			this->codePatient=codePatient;
		}
		//////////////////setter////////////////////
		void setDoctorName(string doctorName){
			this->doctorName=doctorName;
		}
		void setIllnessType(string illnessType){
			this->illnessType=illnessType;
		}
		void setCodePatient(int codePatient){
			this->codePatient=codePatient;
		}
		/////////////////getter////////////////////
		string getDoctorName()const{
			return doctorName;
		}
		string getIllnessType()const{
			return illnessType;
		}
		int getCodePatient()const{
			return codePatient;
		}
		/////////////functions////////////////////
		void report()const{
			cout<<codePatient<<setw(6)<<name<<setw(4)<<family<<setw(6)<<phone<<setw(10)<<age<<setw(6)<<doctorName<<setw(6)<<illnessType<<"\n";
		}
		string selectDoctor(int);
		friend ostream &operator <<(ostream &out, const Patient &obj){
			out<<obj.codePatient<<setw(6)<<obj.name<<" , "<<obj.family<<" , "<<obj.phone<<" , "<<obj.age<<" , "<<obj.doctorName<<" , "<<obj.illnessType<<"\n";
			return out;
		}
		friend istream &operator <<(istream &in, Patient &obj){
			in>>obj.codePatient;
			in>>obj.name;
			in>>obj.family;
			in>>obj.phone;
			in>>obj.age;
			in>>obj.doctorName;
			in>>obj.illnessType;
			return in;
		}
};
class PD{
	int codeDoctor,codePatient;
	CSVReader *reader, *reader2;
	public:
		void insert(int codeDoctor, int codePatient){
			outputFile.open(PDFile,ios::app);
			outputFile<<codeDoctor+" , "+codePatient<<"\n";
		}
		void showPatientList(int codeDoctor){
			reader=new CSVReader(PDFile);
			vector<vector<string>> dataList=reader->getData();//pointer needs -> to access functions 
			vector<string> vec1;
			for(vector<string> vec:dataList){
				if(codeDoctor==stoi(vec[0])){
					vec1.push_back(vec[1]);
				}
			}
			reader2=new CSVReader(patientFile);
			vector<vector<string>> dataList1=reader2->getData();
			for(vector<string> vec:dataList1){
				for(int i=0;i<vec1.size();i++){
					if(stoi(vec[0])==stoi(vec1[i])){
						for(int i=0;i<2;i++){
							cout<<vec[i]<<" ";
						}
					}
					cout<<"\n";
				}
			}
		}
		
};
class Phone{
	private:
		string phone;
	public:
		string getPhone(){
			
			string msg1="phone number can not be less than 11 digits.try again.\n";
			string msg2="phone number can not start number except 0.try again.\n";
			string msg3="phone number can not contain letter.try again.\n";
		
		start:
			try{
				phone.clear();
				cout<<"\nenter phone number:";
				cin>>phone;
				if(phone.length()<11){
					throw msg1;
				}	
				if(phone[0]!='0'){
					throw msg2;
				}
				for(int i=0;i<phone.length();i++){
					if(phone[i]<48||phone[i]>57){
						throw msg3;
					}
				}
			}
			catch(string msg){
				cout<<msg;
				goto start;
			}
			return phone;
		}
};				
class Name{
	private:
		string name;
	public:
		string getName(){
			string msg1="name should contain letter.try again.\n";
		start:
			try{
				name.clear();
				cout<<"\nenter name:";
				cin>>name;
				for(int i=0;i<name.length();i++){
					if((name[i]<97&&name[i]>90)||name[i]>122||name[i]<65){
						throw msg1;
					}
				}
			}
			catch(string msg){
				cout<<msg;
				goto start;
			}
			return name;
		}		
};
class Family{
	private:
		string family;
	public:
		string getFamily(){
			string msg1="family should contain letter.try again.\n";
		start:
			try{
				family.clear();
				cout<<"\nenter family:";
				cin>>family;
				for(int i=0;i<family.length();i++){
					if((family[i]<97&&family[i]>90)||family[i]>122||family[i]<65){
						throw msg1;
					}
				}
			}
			catch(string msg){
				cout<<msg;
				goto start;
			}
			return family;
		}		
};
class Age{
	private:
		int age;
	public:
		int getAge(string part){
			string msg1="age should be between 18 and 120.try again.\n";
			string msg2="age should be between 0 and 120.try again.\n";
		start:
			try{
				cout<<"\nenter age:";
				cin>>age;
				if(part=="doctor"){
					if(age>120||age<18){
						throw msg1;
					}
				}
				if(part=="patient"){
					if(age>120||age<0){
						throw msg2;
					}
				}
				
			}
			catch(string msg){
				cout<<msg;
				goto start;
			}
			return age;
		}		
};
class Password{
	private:
		string pass, username;
		fstream passFile;
	public:
		void inputPass(){
			char ch;
			cout<<"\nenter username:";
			cin>>username;
			cout<<"\nenter password:";
			string msg1="\npassword can not be less than 8 characters.try again.\n";
		START:
			try{
				ch=_getch();
				int count=0;
				while(ch!=13){
					if(ch==8){
						cout<<"\b \b";
						pass.pop_back();
					}
					else{
						cout<<"*";
						pass.push_back(ch);
					}
					ch=_getch();
					count++;
				}
				if(count<8){
					throw msg1;
				}
			}
			catch(string msg){
				cout<<msg;
				goto START;
			}
			passFile.open("password.csv",ios::app);
			passFile<<username+","+pass<<"\n";
		}
		string verifyPass(string username ){
			CSVReader reader("password.csv");
			vector<vector<string>> dataList=reader.getData();
			for(vector<string> vec:dataList){
				for(string data:vec){
					if(data==username){
						return vec[1];
					}
				}
			}
		}	
};

void showData(string fileName){
	CSVReader reader(fileName);
	vector<vector<string>> dataList=reader.getData();
	for(vector<string> vec:dataList){
		for(string data:vec){
			
			cout<<data<<setw(6);
		}
		cout<<"\n";
	}
}
void showOneData(string fileName, int code){
	CSVReader reader(fileName);
	vector<vector<string>> dataList=reader.getData();
	for(vector<string> vec:dataList){
		if(vec[0]==to_string(code)){
			for(int i=0;i<vec.size();i++){
				cout<<vec[i]<<setw(6);
			}
			cout<<"\n";
		}
		cout<<"\n";
	}
}
PD *pd;
//////////////   Doctor   ///////////////
vector<Doctor> listDoctor, listDoctorTemp;
fstream outputFileDoc;
void writeDoctor(){
	string name, family, phone, proficiency;
	int age,codeDoctor;
	Name n;	
	Family f;
	Phone p;
	Age a;
	Password pass;
	name=n.getName();
	family=f.getFamily();
	phone=p.getPhone();
	age=a.getAge("doctor");
	cout<<"\nenter proficiency:";
	cin>>proficiency;
	cout<<"\nenter codeDoctor:";
	cin>>codeDoctor;
	pass.inputPass();
	
	
	Doctor doctor(codeDoctor,name,family,phone,age,proficiency);
	ofstream out(doctorFile);
	out<<doctor;
	out.close();
}
void displayAllDoc(){
	cout<<"******************* Hospital Managment System ***********************\n\n";
	cout<<"#####################################################################\n";
	cout<<"#######################   Report doctors   ##########################\n";
	cout<<"#####################################################################\n";
	cout<<"=====================================================================\n";
	cout<<"=Name      Family      Phone      Age     Proficiency     codeDoctor=\n";
	cout<<"=====================================================================\n";
	
	showData(doctorFile);
	
	
	/*for(int i=0;i<listDoctor.size();i++){
		cout<<i+1<<".";
		listDoctor[i].report();
	}*/
}
void displayOneDoc(int codeDoctor){
	cout<<"******************* Hospital Managment System ***********************\n\n";
	cout<<"#####################################################################\n";
	cout<<"#######################    Report doctor   ##########################\n";
	cout<<"#####################################################################\n";
	cout<<"=====================================================================\n";
	cout<<"=Name      Family      Phone      Age     Proficiency     codeDoctor=\n";
	cout<<"=====================================================================\n";
	for(int i=0;i<listDoctor.size();i++){
		if(codeDoctor==listDoctor[i].getCodeEmp()){
			listDoctor[i].report();
		}
	}
}
void modifyDoc(int code){
	string name, family, phone;
	int choice, age;
	for(int i=0;i<listDoctor.size();i++){
		if(listDoctor[i].getCodeEmp()==code){
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
	remove("doctor.csv");
	listDoctor.clear();
}
void deleteOneDoc(int code){
	
	CSVReader reader("doctor.csv");
	vector<vector<string>> vec=reader.getData();
	for(vector<string> dataList:vec){
		for(string data:dataList){
			cout<<data<<"\t";
		}
		cout<<"\n";
	}
	
	fstream newFile;
	ifstream curFile("doctor.csv");
	
	newFile.open("newDoctor.csv",ios::out);
	cout<<"1\n";
	int codeDoctor,index,i,count=0;
	string line,word;
	vector<string> row;
	cout<<"2\n";
	char delimeter=',';
	while(!curFile.eof()){
		row.clear();
		getline(curFile,line);
		stringstream s(line);
		cout<<"3\n";
		while(getline(s,word,delimeter)){
			cout<<"word"<<word<<"\n";
			row.push_back(word);
		}
		int rowSize=row.size();
		cout<<"rowSize:"<<rowSize<<"\n";
		//codeDoctor=stoi(row[5]);
		//cout<<"codeDoctor:"<<codeDoctor<<"\n";
		if(row[5]!=to_string(code)){
			if(!curFile.eof()){
				for(i=0;i<rowSize-1;i++){
					newFile<<row[i]<<",";
				}
				newFile<<row[rowSize-1]<<"\n";
			}
		}
		else{
			count=1;
		}
		if(curFile.eof()){
			break;
		}
	}
	cout<<"5\n";
	if(count==1){
		cout<<"doctor deleted.\n";
	}
	else{
		cout<<"doctor not found.\n";
	}
	newFile.close();
	curFile.close();
	cout<<"4\n";
	remove("doctor.csv");
	rename("newDoctor.csv","doctor.csv");
}
vector<Doctor> getDoctorList(){
	return listDoctor;
}
void printSavedPatients(int code){
	cout<<"*************** Hospital Managment System ***************\n\n\n";
	cout<<"#########################################################\n";
	cout<<"##################   Report doctor   ####################\n";
	cout<<"#########################################################\n";
	
	pd=new PD();
	pd->showPatientList(code);
	
	//showData(reservationFile);
	/*
	multimap<int, string> list=getSavedReservation();
	for(multimap<int ,string>::iterator it=list.begin();it!=list.end();it++){
		if(code==it->first){
			cout<<it->second<<"\n";
		}
	}
	*/
}
//////////////   Patient   ///////////////
vector<Patient> listPatient, listPatientTemp;
fstream outputFilePat;
void writePatient(){
	Patient p;
	Name n;
	Family f;
	Phone ph;
	Age a;
	
	string name, family, phone, doctorName, illnessType;
	int age,codePatient;

	name=n.getName();
	family=f.getFamily();
	phone=ph.getPhone();
	age=a.getAge("patient");
	cout<<"illness type:";
	cin>>illnessType;
	cout<<"code patient:";
	cin>>codePatient;
	doctorName=p.selectDoctor(codePatient);
	//Doctor doctor;
	/*
	outputFilePat.open(reservationFile,ios::app);
	outputFilePat<<name+","+family+","+to_string(codeDoctor)+"\n";
	*/
	Patient patient(codePatient,name,family,phone,age,doctorName,illnessType);
	ofstream out(patientFile);
	out<<patient;
	out.close();
	
	/*listPatient.push_back(Patient(name,family,phone,age,diseaseType,codePatient,doctorName));
	outputFilePat.open("Patient.csv",ios::out);
	outputFilePat<<name+","+family+","+phone+","+to_string(age)+","+to_string(codePatient)+","+doctorName+"\n";
	*/
}
void displayAllPat(){
	Person p;
	cout<<"****************** Hospital Managment System ***************\n\n\n";
	cout<<"############################################################\n";
	cout<<"####################   Report patient   ####################\n";
	cout<<"############################################################\n";
	cout<<"============================================================\n";
	cout<<"=Name Family Phone   Age doctorName illnessType codePatient=\n";
	cout<<"============================================================\n";
	
	showData(patientFile);
	/*
	for(int i=0;i<listPatient.size();i++){
		cout<<i+1;
		listPatient[i].report();
	}
	*/
}
void displayOnePat(int codePatient){
	Person p;
	cout<<"****************** Hospital Managment System ***************\n\n\n";
	cout<<"############################################################\n";
	cout<<"#####################   Report patients  ###################\n";
	cout<<"############################################################\n";
	cout<<"============================================================\n";
	cout<<"=Name Family Phone   Age doctorName illnessType codePatient=\n";
	cout<<"============================================================\n";
	for(int i=0;i<listDoctor.size();i++){
		if(codePatient==listPatient[i].getCodePatient()){
			listDoctor[i].report();
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
string Patient::selectDoctor(int codePatient){
	int code;
	showData(doctorFile);
	ifstream in(doctorFile);
	Doctor doctor;
	long int size=getSizeOfFile(doctorFile);
	in.seekg(0);
	pd=new PD();
	
	cout<<"enter code doctor to reserve:";
	cin>>code;
	
	for(int i=0;i<size;i++){
		in>> doctor;
		if(code==doctor.getCodeEmp()){
			//doctor.saveReservation(name, family);
			pd->insert(code,codePatient);
			return (doctor.getName()+" "+doctor.getFamily());
		}
	}
	
	in.close();
	
	
	
	
	
	/*string doctorName;
	int code;
	bool find=false;
	cout<<"\nenter the code of doctor to reserve:";
	cin>>code;
	vector<Doctor> list=getDoctorList();
	for(int i=0;i<list.size();i++){
		if(list[i].getCodeEmp()==code){
			find=true;
			doctorName=list[i].getName();
			doctorName+=" ";
			doctorName+=list[i].getFamily();
			reserves.push_back(list[i]);
			savedReservations.insert(pair<int, string>(code,name+","+family+","+diseaseType));
			return doctorName;
		}
	}
	if(find==false){
		cout<<"there is not this code in available doctors.\n";
		return "false";
	}*/
}
////////////////Employee///////////////////////

//////////////// menu/////////////////////////
void reportMenu(){
	int choice, c;
	do{
		//system("cls");
		cout<<"*************** Hospital Managment System ***************\n\n";
		cout<<"#########################################################\n";
		cout<<"##################   Report Menu   ######################\n";
		cout<<"#########################################################\n";
		cout<<"\n1.Doctor report";
		cout<<"\n2.Patient report";
		cout<<"\n3.Employee report";
		cout<<"\n4.Back to main menu";
		cout<<"\n\nenter your choice(1|2|3|4):";
		cin>>choice;
		switch(choice){
			case 1:
				do{
					cout<<"*************** Hospital Managment System ***************\n\n";
					cout<<"#########################################################\n";
					cout<<"##################   Report Menu   ######################\n";
					cout<<"#########################################################\n";
					cout<<"\n1.All doctors records";
					cout<<"\n2.A doctor record";
					cout<<"\n3.Patients list";
					cout<<"\n4.Back to report menu";
					cout<<"\n\nenter your choice(1|2|3|4):";
					cin>>c;
					switch(c){
						case 1:
							//system("cls");
							displayAllDoc();
							break;
						case 2:
							int code;
							cout<<"Enter doctor code to report:";
							cin>>code;
							//system("cls");
							displayOneDoc(code);
							break;
						case 3:
							cout<<"Enter doctor code to report:";
							cin>>code;
							//system("cls");
							printSavedPatients(code);
							break;
						case 4:
							break;
						default:
							cout<<"invalid choice.try again.";
							//system("cls");		
					}
				}while(c!=4);
				break;
			case 2:
				do{
					cout<<"*************** Hospital Managment System ***************\n\n";
					cout<<"#########################################################\n";
					cout<<"##################   Report Menu   ######################\n";
					cout<<"#########################################################\n";
					cout<<"\n1.All patients records";
					cout<<"\n2.A patient record";
					cout<<"\n3.Back to report menu";
					cout<<"\n\nenter your choice(1|2|3):";
					cin>>c;
					switch(c){
						case 1:
							//system("cls");
							displayAllPat();
							break;
						case 2:
							int code;
							cout<<"Enter patient code to report:";
							cin>>code;
							//system("cls");
							displayOnePat(code);
							break;
						case 3:
							break;
						default:
							cout<<"invalid choice.try again.";
							//system("cls");
							break;		
					}
				}while(c!=3);
				break;
			case 3:
				do{
					cout<<"*************** Hospital Managment System ***************\n\n";
					cout<<"#########################################################\n";
					cout<<"##################   Report Menu   ######################\n";
					cout<<"#########################################################\n";
					cout<<"\n1.All doctors records";
					cout<<"\n2.A doctor record";
					cout<<"\n3.Patients list";
					cout<<"\n4.Back to report menu";
					cout<<"\n\nenter your choice(1|2|3|4):";
					cin>>c;
					switch(c){
						case 1:
							//system("cls");
							displayAllDoc();
							break;
						case 2:
							int code;
							cout<<"Enter doctor code to report:";
							cin>>code;
							//system("cls");
							displayOneDoc(code);
							break;
						case 3:
							cout<<"Enter doctor code to report:";
							cin>>code;
							//system("cls");
							printSavedPatients(code);
							break;
						case 4:
							break;
						default:
							cout<<"invalid choice.try again.";
							//system("cls");		
					}
				}while(c!=4);
				break;
			case 4:
				break;
			default:
				cout<<"invalid choice.try again.";
				//system("cls");
				break;	
		}
	}while(choice!=4);
}
void entryMenu(){
	int choice;
	do{
		int count=0,code;
		Password p;
		string username,password;
		//system("cls");
		cout<<"*************** Hospital Managment System ***************\n\n\n";
		cout<<"#########################################################\n";
		cout<<"###################   Entry Menu   ######################\n";
		cout<<"#########################################################\n";
		cout<<"\n1.Patient";
		cout<<"\n2.Doctor";
		cout<<"\n3.Employee";
		cout<<"\n4.Back to main menu";
		cout<<"\n\nenter your choice(1|2|3|4):";
		cin>>choice;
		switch(choice){
			case 1:
				do{
					cout<<"*************** Hospital Managment System ***************\n\n\n";
					cout<<"#########################################################\n";
					cout<<"##################   Patient Menu   #####################\n";
					cout<<"#########################################################\n";	
					cout<<"\n5.Back to report menu";
					cout<<"\n\nenter your choice(1-6):";
					cin>>choice;
					switch(choice){
						case 5:
							break;	
						default:
							cout<<"invalid choice.try again.";
							break;		
					}
					//system("cls");
				}while(choice!=5);
				break;
			case 2:		
				while(count<=3){
					cout<<"enter username:";
					cin>>username;
					cout<<"enter password:";
					char ch=_getch();
					while(ch!=13){
						if(ch==8){
							cout<<"\b \b";
							password.pop_back();
						}
						else{
							cout<<"*";
							password.push_back(ch);
						}
						ch=_getch();
					}
					if(p.verifyPass(username)==password){
						do{
							//system("cls");
							cout<<"\n*************** Hospital Managment System ***************\n\n\n";
							cout<<"#########################################################\n";
							cout<<"##################   Doctor Menu   ######################\n";
							cout<<"#########################################################\n";
							cout<<"\n5.Back to report menu";
							cout<<"\n\nenter your choice(1-5):";
							cin>>choice;
							switch(choice){	
								case 5:
									break;	
								default:
									cout<<"invalid choice.try again.";		
							}
						}while(choice!=5);
					}
					else{
						count++;
						cout<<"username or password is incorrect.try again.\n";
						cout<<"you can try "<<3-count<<"times.\n";
					}	
				}
				cout<<"you are out of try.access denied.\n";
				break;
			case 3:
				do{
					//system("cls");
					cout<<"*************** Hospital Managment System ***************\n\n\n";
					cout<<"#########################################################\n";
					cout<<"##################   Employee Menu   ####################\n";
					cout<<"#########################################################\n";
					cout<<"\n1.Add a doctor";
					cout<<"\n2.Modify a doctor";
					cout<<"\n3.Delete all doctors";
					cout<<"\n4.Delete a doctor";
					cout<<"\n5.Add a patient";
					cout<<"\n6.Modify a patient";
					cout<<"\n7.Delete all patients";
					cout<<"\n8.Delete a patient";
					cout<<"\n9.Back to entry menu";
					cout<<"\n\nenter your choice(1-9):";
					cin>>choice;
					switch(choice){
						case 1:
							writeDoctor();
							break;
						case 2:
							//int code;
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
							writePatient();
							break;
						case 6:
							//int code;
							cout<<"Enter patient code to modify:";
							cin>>code;
							modifyPat(code);
							break;
						case 7:
							deleteAllPat();
							break;
						case 8:
							cout<<"Enter patient code to delete:";
							cin>>code;
							deleteOnePat(code);
							break;	
						case 9:
							break;	
						default:
							cout<<"invalid choice.try again.";
							break;
					}
				}while(choice!=9);
				break;
			case 4:
				break;
			default:
				cout<<"invalid choice.try again.";
				break;	
		}
	}while(choice!=4);
}
int main() {
	int choice;
	do{
		//system("cls");
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
