
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include<Windows.h>
#include<ctime>
using namespace std;

string ledgernames[50] = {""};    //this is for ledger name storing that print if user says to print all ledgers
int index = 0;

class journal
{
private:
	string from;
	string to;
	string date;
	long long int amount;
	ofstream in;
	int count;
public:
	journal()
	{
		count = 0;
		from = to = "";
		amount = 0;
	}
	~journal()
	{
	}
	void get_entries()
	{
		in.open("journal.txt");
		display_logo();				//funtion call for design first name etc for journal
		int i = 0;
		while (i == 0)
		{
			++count;
			in << endl;
			system("cls");
			debit();


			credit();


			string disc;			//variable for taking discription of journal entry

			cout << "\n\n\tENTER DESCRIPTION:   ";
			cin.ignore();
			getline(cin, disc);
		//	cin.ignore();
			in <<setw(11)<<"|(" <<setw(50) << disc<<")" << endl;

				for (int j = 125; j > 0; j--)
				{
					in << "-";
				}

				cout << "\n\n\n\n              PRESS 1 TO EXIT 0 TO CONTINUE:  ";
				cin >> i;
				system("cls");
		}
		in.close();

	}
	void credit()
	{
		in << setw(10) << "|";
		cout << "\n\n\tENTER CREDIT ENTRY:  ";
  cin >> to;

		in << setw(40) <<"to "<< to;
		cout << "\n\n\tENTER CREDIT AMOUNT:   ";
		cin >> amount;

		in << setw(50) << amount << endl;
	}
	void debit()
	{
		cout << "\n\n\tENTER DATE OF ENTRY:   ";
		cin.clear();
		//cin.ignore();
		cin.clear();
		//cin.fill();

		getline(cin, date);
		if (count > 1)
		{
			getline(cin, date);
		}

		in << date;
		cout << "\n\n\tENTER DEBIT ENTRY:   ";
		cin.clear();
	//	cin.ignore();
		cin.clear();

		getline(cin, from);
		in << setw(20) << from;
		cout << "\n\n\tENTER DEBIT AMOUNT:  ";
		cin >> amount;
		in << setw(70) << amount << endl;
	}
	void display_logo()
	{
		string name;
		cout << "\n\n\tENTER NAME FOR JOURNAL:   ";

		cin.ignore();
		cin.clear();
		getline(cin, name);
		cout << "\n\n\tENTER DATE OF JOURNAL:   ";

		//cin.ignore();
		getline(cin, date);

		in << setw(50) << name << endl;
		in << setw(50) << "JOURNAL" << endl;
		in << setw(50) << date << endl;
			for (int j = 125; j > 0; j--)
			{
				in << "-";
			}

			in << endl;
			in << setw(10) << "DATE|" << setw(25) << "DESCRIPTION" << setw(50) << "|DEBIT" << setw(20) << "|CREDIT" << endl;

			for (int j = 125; j > 0; j--)
			{
				in << "-";
			}

	}

};


long long int trial_debit_sum=0, trial_credit_sum=0;			//global variable for trial total
class ledger_trial
{

private:
	//static int count;
	ofstream out_file,out_file_trial;
	ifstream in_file;
	string filename, account_name;
	long long int debit_sum, credit_sum ;
	string entery, date, entry;
	long long int amount, amount1, balance_cd;
	bool flag=true;

public:

	ledger_trial()
	{
		//count++;
		debit_sum = credit_sum = 0;
		trial_credit_sum = trial_debit_sum = 0;
		balance_cd = 0;
		out_file_trial.open("Trial.txt", ios::app);
	}
	~ledger_trial()
	{

	}
	void start()
	{
		string ledger_name; //for concontination
		debit_sum = credit_sum = 0;
		balance_cd = 0;				//for delete the data of previous ledger
		filename = account_name =entery=date=entry= "";
		cout << "\n\n\n\n              ENTER LEDGER NAME   ";
  cin >> filename;

		ledger_name = filename;
		ledger_name = ledger_name + ".txt";			//concentinate the string with txt

		ledgernames[index++]=ledger_name;

		out_file.open(ledger_name.c_str());			//create file for ledger
		in_file.open("journal.txt");				//open file for searching and catching data

		//taking data from journal and design the ledger
		getline(in_file, account_name);
		out_file << account_name << endl;
		out_file << setw(50) <<filename<<endl;
		out_file << setw(50) << "LEDGER" << endl;

		//for line
			for (int j = 86; j > 0; j--)
			{
				out_file << "-";
			}

		out_file << endl;
		out_file  << "Date" << setw(20) << "Particular" ;
		out_file << setw(15) << "Amount" << setw(10) << "Date" << setw(20) << "Particular" << setw(15) << "Amount" << endl;

		//for line
			for (int j = 86; j > 0; j--)
			{
				out_file << "-";
			}

		out_file << endl;
		get_entries();				//new function call

	}
	void get_entries()
	{
		string waste;				//for waste lines
		for (int i = 0; i < 5;i++)
			getline(in_file, waste);		//remove waste lines that is catching from journal file
		//cout << waste << endl;
		do
		{
			in_file >> date >> entery >> amount;			//taking debit entries from journal file
		//	cout << date << " " << entery << amount << endl;
			for (int i = 0; i < 2; i++)
				in_file >> waste;

			in_file >> entry >> amount1;					//taking credit entries from journal file
			//cout << entry << amount1<<endl;
			//checking filename with jounral entries

			if (entery == filename)
			{
				out_file << setw(10) << date << setw(20) << entery << setw(10) << amount1<<"|" << endl;		//
				debit_sum += amount;			//it will sum of ledger entries from debit side
			}
			else if (entry == filename)
			{
				out_file << setw(41)<<"|"<<setw(9) << date << setw(20) << entry << setw(15) << amount << endl;
				credit_sum += amount1;			//it will sum of ledger entries from credit side
			}


			for (int i = 0; i < 3; i++)
			{
				getline(in_file, waste);
			}
		} while (!in_file.eof());
		total();			//function call
		trial();

	}
	void total()
	{
		//this function is doing last step that is total and finish ledger with balance carry down
		if (debit_sum > credit_sum)
		{
			flag = true;
			balance_cd = debit_sum - credit_sum;
			
			for (int j = 86; j > 0; j--)
			{
				out_file << "-";
			}
			out_file << endl;
			out_file << setw(10) << "Total" << setw(10) << debit_sum - credit_sum << endl;

			for (int j = 86; j > 0; j--)
			{
				out_file << "-";
			}

			out_file << endl;
		}
		else
		{
			flag = false;
			balance_cd = credit_sum - debit_sum;

				for (int j = 86; j > 0; j--)
				{
					out_file << "-";
				}

			out_file << endl;
			out_file << setw(55) << "Total " << setw(15) <<credit_sum - debit_sum << endl;

				for (int j = 86; j > 0; j--)
				{
					out_file << "-";
				}

			out_file << endl;
			out_file.close();		//ledger file is done and now it is closed
			in_file.close();		//journal file is also close we toke all wanted material from journal files
		}
	}
	void design()
	{
		//this is function that is for journal
		//design that will help to desiggn trial
		//for balance and taking info from journal


		string name_of_account,date_of_trial;
		ifstream in_file_design;

		in_file_design.open("journal.txt", ios::in);		//open file for dates and name
		getline(in_file_design, name_of_account);

		out_file_trial << name_of_account << endl;
		out_file_trial << setw(50) << "TRIAL" << endl;

		getline(in_file_design, date_of_trial);
		getline(in_file_design, date_of_trial);


		out_file_trial << setw(50) << date_of_trial << endl;
		in_file_design.close();						//close file

			for (int j = 50; j > 0; j--)
			{
				out_file_trial << "-";
			}

		out_file_trial << endl;


		out_file_trial<< setw(10) << "Ledger name" << setw(15) << "DR Amount" << setw(15) << "CR Amount" << endl;

			for (int j = 50; j > 0; j--)
			{
				out_file_trial << "-";
			}

		out_file_trial << endl;
	}
	void trial()
	{
		//it will decide on the basis of flag that balance cd is on debit side or credit side
		if (flag == true)
		{
			trial_debit_sum += balance_cd;			//here we are doing sum of total for trial
			out_file_trial << setw(10) << filename << setw(15) << balance_cd << endl;
		}
		else
		{
			trial_credit_sum += balance_cd;			//here we are doing sum of total for trial
			out_file_trial << setw(10) << filename << setw(30) << balance_cd << endl;
		}
	}
	void total_trial()
	{

		//it is the design part for trial that disignes total part of trial
		for (int j = 50; j > 0; j--)
		{
			out_file_trial << "-";
		}
		out_file_trial << endl;

		out_file_trial << setw(10) << "TOTAL" << setw(15) << trial_debit_sum << setw(15) << trial_credit_sum << endl;

			for (int j = 50; j > 0; j--)
			{
				out_file_trial << "-";
			}

		out_file_trial << endl;
		out_file_trial.close();				//here means file closed
	}
};
int main()
{
	system("Color 8e");
	int oneSecond = 1000;
	cout << "\t**      **      ";
	cout << "\n\t**      ** ******* **      ****** ******** ****** *** ***********";
	cout << "\n\t**      ** **      **      **     **    ** **  **  ** ***      ";
	cout << "\n\t**  **  ** *****   **      **     **    ** **  **  ** **********    ";
	cout << "\n\t**  **  ** **      **      **     **    ** **  **  ** ***             ";
	cout << "\n\t********** ******* ******* ****** ******** **      ** ************     ";
	cout << "\n\n\t\t\t        ********  *****        ";
	cout << "\n\t\t\t           **     *   *      ";
	cout << "\n\t\t\t           **     *****    ";

	cout << "\n\n\t -------------------- Apollo Vehicle Managment System -------------------------";

	char date[10];
	_strdate(date);
	char time[10];
	_strtime(time);
	cout << "\n\n\t\tDate: " << date << "  Time: " << time << endl;
	cout << endl << endl << endl << endl << endl;
	cout << "\n\n\n\t Loading Data just few seconds" << endl;

	cout << "\n\t Please wait";

	for (int i = 0; i<5; i++)
	{
		Sleep(500);
		cout << ". ";  //-- generate "...."------
	}
	Sleep(1000);
	system("cls");


	cout << "\n\n\n\n              PRESS '1' FOR THE JOURNAL ENTRIES for THE FIRST TIME: ";
	int number;
	cin >> number;
	journal j;


	if (number==1)
	j.get_entries();
	system("cls");

	string printer_of_journal_ledger;

	cout << "\n\n\n\n              ENTER 1 TO SEE YOUR JOURNAL, else 0 : ";
	cin >> number;
	system("cls");
	if (number == 1)
	{
		ifstream infile;
		infile.open("journal.txt", ios::in);
		do
		{
			getline(infile, printer_of_journal_ledger);
			cout << printer_of_journal_ledger << endl;
		} while (!infile.eof());
		infile.close();
		cout << endl;
		for (int i = 0; i<5; i++)
		{
			Sleep(oneSecond);
			cout << ". ";  //-- generate "...."------
		}

	}


	ledger_trial t[50];
	t[0].design();
	system("cls");

	int i;
	for ( i = 1; i < 50; i++)
	{
		cout << "\n\n\n\n              IF YOU WANT TO ADD T-Accounts / LEDGERS ENTER 1, else 0:   ";
		cin >> number;
		system("cls");
		if (number == 0)
			break;
		t[i].start();
	}

	t[i].total_trial();

	cout <<" \n\n\n\n              IF YOU WANT TO SEE YOUR T-Accounts / LEDGERS ENTER 1, else 0:";
	cin >> number;
	if (number == 0)
		exit;
	//printe ledger for user
	ifstream infile;
	for (int i = 0; i < index; i++)
	{
		infile.open(ledgernames[i].c_str(),ios::in);
		do
		{
			getline(infile, printer_of_journal_ledger);
			cout << printer_of_journal_ledger << endl;

		} while (!infile.eof());
		infile.close();
		cout << "\n\n\n\n";
	}
	 for (int i = 0; i<5; i++)
		{
			Sleep(oneSecond);
			cout << ". ";  //-- generate "...."------
		}
}

