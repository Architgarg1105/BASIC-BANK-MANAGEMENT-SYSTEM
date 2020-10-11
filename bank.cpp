#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	int retdeposit() const;
	char rettype() const;
};

void account::create_account()//to create new account
{
	//system("CLS");
	cout<<"\n\t\t\tEnter the Account No. : ";
	cin>>acno;
	cout<<"\n\n\t\t\tEnter the Name of the Account holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\t\t\tEnter Type of the Account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tEnter The Initial amount : ";
	cin>>deposit;
	cout<<"\n\n\t\t\tAccount Created..";
}

void account::show_account() const //to display account info (const is used to avoid accidental changes)
{
	cout<<"\n\t\t\tAccount No. : "<<acno;
	cout<<"\n\t\t\tAccount Holder Name : ";
	cout<<name;
	cout<<"\n\t\t\tType of Account : "<<type;
	cout<<"\n\t\t\tBalance amount : "<<deposit;
}


void account::modify()//to modify the existing account info
{
	cout<<"\n\t\t\tAccount No. : "<<acno;
	cout<<"\n\t\t\tModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\t\t\tModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tModify Balance amount : ";
	cin>>deposit;
}


void account::dep(int x)//to perform deposition in account
{
	deposit+=x;
}

void account::draw(int x)//to perfrom withdrawl in account
{
	if(x>deposit)
		cout<<"Not enough balance!";
	else
		deposit-=x;
}

void account::report() const//to display the field info(s)
{
	cout<<"\t\t\t\t\t\t\t\t\t\t"<<"       "<<acno<<setw(10)<<" "<<name<<setw(15)<<" "<<type<<setw(6)<<deposit<<endl;
}

int account::retacno() const//to return the account number 
{
	return acno;
}

int account::retdeposit() const//to return the total deposit
{
	return deposit;
}

char account::rettype() const//to return the type of account
{
	return type;
}


//function declaration
void write_account();//to write in file and create account
void display_sp(int);//balance enquiry
void modify_account(int);//to modify details of existing account
void delete_account(int);//to delete an existing account
void display_all();//to display the details of all account holders
void deposit_withdraw(int, int);//to withdraw or deposit ammount in an existing account

int main()
{
	char ch;
	int num;
	do
	{
	//system("CLS");
	cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\t\t======================\n";
	cout<<"\t\t\t\t\t\t\t\t\t\t\t\tBANK MANAGEMENT SYSTEM";
	cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t======================\n";

		cout<<"\t\t\t\t\t\t\t\t\t\t\t\t    ::MAIN MENU::\n";
		cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t1. NEW ACCOUNT";
		cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t2. DEPOSIT AMOUNT";
		cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t3. WITHDRAW AMOUNT";
		cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t4. BALANCE ENQUIRY";
		cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t6. CLOSE AN ACCOUNT";
		cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t7. MODIFY AN ACCOUNT";
		cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t8. EXIT";
		cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\t\tSelect Your Option (1-8): ";
		cin>>ch;

		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			//system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			//system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			//system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			//system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
		 	//system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
		 	//system("CLS");
			cout<<"\n\n\t\t\tBrought To You By code-projects.org";
			break;
		 default :cout<<"\a";//escape character
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return 0;
}


void write_account()//write in account.dat file
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);//to open file account.dat in append mode
	ac.create_account();//to create an account
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));//reinterpret_cast to type cast object ac into character pointer and write in file account.dat
	outFile.close();
}

void display_sp(int n)//for balance enquiry
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)//if account.dat is empty
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\tBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)//if account having account number (n) exits
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\n\t\t\tAccount number does not exist";
}



void modify_account(int n)//to modify an existing account
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)//if file is empty
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));//to read existing data
		if(ac.retacno()==n)//if account found
		{
			ac.show_account();//to display details
			cout<<"\n\n\t\t\tEnter The New Details of account"<<endl;
			ac.modify();//to modify details
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);//to move back to the position of account which is need to be modified
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));//to overwrite the existing details of account which is modified
		    cout<<"\n\n\t\t\tRecord Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}



void delete_account(int n)//to delete an existing account
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)//if file is empty 
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);//creating new file
	inFile.seekg(0,ios::beg);//to move to the begining 
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)//excluding the account details that needs to be deleted
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));//writing data in temp.dat from account.dat
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\nRecord Deleted ..";
}


void display_all()//to display details of every account holder
{
	//system("CLS");
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\t\t        ACCOUNT HOLDER LIST\n\n";
	cout<<"\t\t\t\t\t\t\t\t\t\t     ====================================================\n";
	cout<<"\t\t\t\t\t\t\t\t\t\t     A/c no.      NAME                 Type  Balance\n";
	cout<<"\t\t\t\t\t\t\t\t\t\t     ====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();//to get info
	}
	inFile.close();
}


void deposit_withdraw(int n, int option)//to perform withdrawl and deposit operation
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)//if file is empty
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)//if account if found
		{
			ac.show_account();
			if(option==1)//to perform desposit operation
			{
				cout<<"\n\n\t\t\tTO DEPOSITSS AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);//calling desposit function 
			}
		    if(option==2)//to perfrom withdrwal operation
			{
				cout<<"\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if(bal<0)
					cout<<"Insufficient balance";
				else
					ac.draw(amt);//calling withdrawl function
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);//moving back to the calculated position
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));//writing in file account.dat
			cout<<"\n\n\t\t\tRecord Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}
//End of the bank management system program
