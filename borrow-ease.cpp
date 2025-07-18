#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <Windows.h>
#include <iomanip>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib> 
#include <limits>
#include <sstream>

using namespace std;

//colors

void setBlackColor() {
	cout << "\033[30m";
}
void setRedColor() {
    cout << "\033[31m";
}
void setGreenColor() {
    cout << "\033[32m";
}
void setYellowColor() {
	cout << "\033[33m";
}
void setBlueColor() {
	cout << "\033[34m";
}
void setMagentaColor() {
	cout << "\033[35m";
}
void setCyanColor() {
	cout << "\033[36m";
}
void setWhiteColor() {
	cout << "\033[37m";
}
void resetColor() {
	cout << "\033[0m";
}

// Function declarations
void adminHome(), userAccount(), moneyLoanInventory(), inventory(), showAllUser(), searchUser(), listAppliedUser(), login();
void registration(), gadgetLoanInventory(), transactionHistory(), transactionHistoryUser(), recordsUserMoney();
void logout(), viewProducts(), showAllProduct(), generateBarcode(), sortuserAdmin(), recordsUserGadget(), displayDueLoans(), displayDueMoneyLoans(), displayDueGadgetLoans();
void showByCategory(), mainMenu(), listAppliedMoney(), listAppliedGadget(), loadFeedbacks(), saveFeedbacks();
// user
void viewAccountPage(), userPayment(), cashIn(), paywBalanceGadget(), paywBalanceMoney(), viewGadgetLoan(), userHome();
void userViewProducts(), viewMoneyLoan(), applyFormGadget(int tempGadgetLoan), applyFormMoney(int tempMoneyLoan), changePassword();
void saveProduct(), addProduct(), updateProduct(), removeProduct(), feedbackUser(), feedbackAdmin(), deleteUser();


//variable
const int BARCODE_WIDTH = 20;
const int BARCODE_HEIGHT = 5;
char full = 219, lower = 220, upper = 223;
//picking

int option, chk=0, chks=0; char selection; 
int attempt, num=0;
bool foundUser = false;

float finalAmount;

//count
int countUser=0, countMoney=0, countGadgetCateg=0, countProducts=0, countApplied=0, countAppliedMoney=0, countTransactions=0, countFeedbacks=0; char choice;
//login
string userLog, passLog;
//bann and unbanned

//struct variable
struct Users //struct for users
{
	string fullName, address, username, password;
	int userid, age;
	float cash;
	bool status;
};
	Users user[200]; //end of struct for users
struct addMoney{ //struct for money loan
	float moneyPrice, interest, quantityMoney;
};
	addMoney money[200];
struct brandCategory{//struct for brand
	string brandName;
};
	brandCategory brand[200];
struct products{
	string brand, unit, display, body, variant, camera, battery, processor;
	float price, quantityProduct;
};
	products product[200];
struct appliedsMoney{
	string fnameMoney, homeAddressMoney, workAddressMoney, otherNameMoney, workMoney, contactMoney, otherContactMoney, agEMoney, earningsMoney, appliedStatusMoney, validIDMoney, proofBillingMoney, paySlipMoney, intereststatusMoney;
	int userIDMoney, monthsToPayMoney,  monthsPaidMoney;
    float priceLoanMoney, monpayMoney, interestMoney;
	string loanTypeMoney; 
    tm dueDateMoney; 
};
	appliedsMoney appliedMoney[200];
struct applieds{
	string fname, homeAddress, workAddress, otherName, work, contact, otherContact, agE, earnings, brandLoan, unitLoan, appliedStatus, downpayStatus, validID, proofBilling, paySlip;
	int userID, monthsToPay,  monthsPaid;
    float monpay, downpay, priceLoan;
	string loanType; // Added field for loan type (gadget or money)
    tm dueDate; 
};
	applieds applied[200];
struct transac {
    string fnameTrans, statusTrans, typeTrans;
    int userIDTrans, monthsToPayTrans, monthsPaidTrans;
    float priceTrans, userCashTrans;
    string loanTypeTrans;
    tm dateMade;
};
    transac transaction[200];
struct feedb {
    int userIDFeed, starsFeed;
    string usernameFeed, descFeed, titleFeed;
    tm dateMadeFeed;
};
    feedb feedback[200];

void generateBarcode() {
    for (int i = 0; i < BARCODE_HEIGHT; ++i) {
        for (int j = 0; j < BARCODE_WIDTH; ++j) {
            if (rand() % 2 == 0)
                cout << "|";
            else
                cout << " ";
        }
        cout << endl;
    }
}

void loadFeedbacks() {
    ifstream read;
    string stringuserIDFeed;
    string stringstarsFeed;
    read.open("feedbacks.txt");
    
    read >> countFeedbacks;
    read.ignore(); // Ignore newline character
    
    for (int i = 0; i < countFeedbacks; i++) {
        getline(read, stringuserIDFeed, ',');
        feedback[i].userIDFeed = stoi(stringuserIDFeed);
        getline(read, feedback[i].usernameFeed, ',');
        getline(read, stringstarsFeed, ',');
        feedback[i].starsFeed = stoi(stringstarsFeed);
        getline(read, feedback[i].titleFeed, ',');
        getline(read, feedback[i].descFeed, ',');
        
        read >> feedback[i].dateMadeFeed.tm_sec >> feedback[i].dateMadeFeed.tm_min
             >> feedback[i].dateMadeFeed.tm_hour >> feedback[i].dateMadeFeed.tm_mday
             >> feedback[i].dateMadeFeed.tm_mon >> feedback[i].dateMadeFeed.tm_year
             >> feedback[i].dateMadeFeed.tm_wday >> feedback[i].dateMadeFeed.tm_yday
             >> feedback[i].dateMadeFeed.tm_isdst;
        
    }
    
    read.close();
}

void saveFeedbacks() {
    ofstream write;
    write.open("feedbacks.txt", ios::out | ios::trunc);
    
    write << countFeedbacks << endl;
    
    for(int i = 0; i < countFeedbacks; i++) {
        write << feedback[i].userIDFeed << "," << feedback[i].usernameFeed << ","
              << feedback[i].starsFeed << "," << feedback[i].titleFeed << "," << feedback[i].descFeed << "," << endl;
        
        write << feedback[i].dateMadeFeed.tm_sec << " " << feedback[i].dateMadeFeed.tm_min
              << " " << feedback[i].dateMadeFeed.tm_hour << " " << feedback[i].dateMadeFeed.tm_mday
              << " " << feedback[i].dateMadeFeed.tm_mon << " " << feedback[i].dateMadeFeed.tm_year
              << " " << feedback[i].dateMadeFeed.tm_wday << " " << feedback[i].dateMadeFeed.tm_yday
              << " " << feedback[i].dateMadeFeed.tm_isdst << endl;
    }
    
    write.close();
}

void loadTransactions() {
    ifstream read;
    string stringUserID, stringMonpayTrans, stringMonthsToPay, stringMonthsPaid, stringPriceTrans;
    read.open("transactions.txt");
    read >> countTransactions;
    read.ignore(); // Ignore newline character
    
    for (int i = 0; i < countTransactions; i++) {
        getline(read, stringUserID, ',');
        transaction[i].userIDTrans = stoi(stringUserID);
        getline(read, transaction[i].fnameTrans, ',');
        getline(read, transaction[i].loanTypeTrans, ',');
        getline(read, stringMonthsToPay, ',');
        transaction[i].monthsToPayTrans = stoi(stringMonthsToPay);
        getline(read, stringMonthsPaid, ',');
        transaction[i].monthsPaidTrans = stoi(stringMonthsPaid);
        getline(read, stringPriceTrans, ',');
        transaction[i].priceTrans = stof(stringPriceTrans);
        getline(read, transaction[i].typeTrans, ',');
        getline(read, transaction[i].statusTrans);

        read >> transaction[i].dateMade.tm_sec >> transaction[i].dateMade.tm_min >> transaction[i].dateMade.tm_hour
             >> transaction[i].dateMade.tm_mday >> transaction[i].dateMade.tm_mon >> transaction[i].dateMade.tm_year
             >> transaction[i].dateMade.tm_wday >> transaction[i].dateMade.tm_yday >> transaction[i].dateMade.tm_isdst;
        
    }
    
    read.close();
}

void saveTransactions() {
    ofstream write;
    write.open("transactions.txt", ios::out | ios::trunc);
    
    write << countTransactions << endl;
    
    for(int i = 0; i < countTransactions; i++) {
        write << transaction[i].userIDTrans << "," << transaction[i].fnameTrans << "," << transaction[i].loanTypeTrans << ","
              << transaction[i].monthsToPayTrans << "," << transaction[i].monthsPaidTrans << ","
              << transaction[i].priceTrans << "," << transaction[i].typeTrans << "," << transaction[i].statusTrans<< endl;
        
        write << transaction[i].dateMade.tm_sec << " " << transaction[i].dateMade.tm_min << " " << transaction[i].dateMade.tm_hour << " "
              << transaction[i].dateMade.tm_mday << " " << transaction[i].dateMade.tm_mon << " " << transaction[i].dateMade.tm_year << " "
              << transaction[i].dateMade.tm_wday << " " << transaction[i].dateMade.tm_yday << " " << transaction[i].dateMade.tm_isdst << endl;
    }
    
    write.close();
}

void loadApplied() {
    ifstream read;
    string stringUserID;
    string stringpriceLoan;
    string stringMonpay;
    string stringDownpay;
    string stringmonthsToPay; 
    string stringmonthsPaid;
    read.open("applied.txt");
    read >> countApplied;
    read.ignore();
    for (int i = 0; i < countApplied; i++) {
        getline(read, stringUserID, ',');
        applied[i].userID = stoi(stringUserID);
        getline(read, applied[i].fname, ',');
        getline(read, applied[i].agE, ',');
        getline(read, applied[i].homeAddress, ',');
        getline(read, applied[i].contact, ',');
        getline(read, applied[i].work, ',');
        getline(read, applied[i].earnings, ',');
        getline(read, applied[i].workAddress, ',');
        getline(read, applied[i].otherName, ',');
        getline(read, applied[i].otherContact, ',');
        getline(read, applied[i].loanType, ','); 
        getline(read, applied[i].brandLoan, ',');
        getline(read, applied[i].unitLoan, ',');
        getline(read, stringMonpay, ',');
        applied[i].monpay = stoi(stringMonpay);
        getline(read, stringDownpay, ',');
        applied[i].downpay = stoi(stringDownpay);
        getline(read, applied[i].downpayStatus, ',');
        getline(read, stringmonthsToPay, ',');
        applied[i].monthsToPay = stoi(stringmonthsToPay);
        getline(read, stringmonthsPaid, ',');
        applied[i].monthsPaid = stoi(stringmonthsPaid);
        getline(read, stringpriceLoan, ',');
        applied[i].priceLoan = stoi(stringpriceLoan);
        getline(read, applied[i].validID, ',');
        getline(read, applied[i].proofBilling, ',');
        getline(read, applied[i].paySlip, ',');
        getline(read, applied[i].appliedStatus);

        read >> applied[i].dueDate.tm_sec >> applied[i].dueDate.tm_min >> applied[i].dueDate.tm_hour >> 
                applied[i].dueDate.tm_mday >> applied[i].dueDate.tm_mon >> applied[i].dueDate.tm_year >>
                applied[i].dueDate.tm_wday >> applied[i].dueDate.tm_yday >> applied[i].dueDate.tm_isdst;
    }
    read.close(); 
}
void saveApplied(){
    ofstream write;
	write.open("applied.txt", ios::out | ios::trunc);
	write << countApplied << endl;
    for(int i=0; i<countApplied; i++){
        write << applied[i].userID << "," << applied[i].fname << "," << applied[i].agE << "," << applied[i].homeAddress << "," << applied[i].contact << "," << applied[i].work << "," << applied[i].earnings << "," << applied[i].workAddress << "," << applied[i].otherName << "," << applied[i].otherContact << "," << applied[i].loanType << "," << applied[i].brandLoan << "," << applied[i].unitLoan << "," << applied[i].monpay << "," << applied[i].downpay << "," << applied[i].downpayStatus << ',' << applied[i].monthsToPay << ',' << applied[i].monthsPaid << ',' << applied[i].priceLoan << "," << applied[i].validID << "," << applied[i].proofBilling << "," << applied[i].paySlip << "," << applied[i].appliedStatus << endl;

        write << applied[i].dueDate.tm_sec << " " << applied[i].dueDate.tm_min << " " << applied[i].dueDate.tm_hour << " " <<
                applied[i].dueDate.tm_mday << " " << applied[i].dueDate.tm_mon << " " << applied[i].dueDate.tm_year << " " <<
                applied[i].dueDate.tm_wday << " " << applied[i].dueDate.tm_yday << " " << applied[i].dueDate.tm_isdst << endl;
    }
    write.close();
}

void loadAppliedMoney() {
    ifstream read;
    string stringUserIDMoney;
    string stringpriceLoanMoney;
    string stringMonpayMoney;
    string stringinterestMoney;
    string stringmonthsToPayMoney; 
    string stringmonthsPaidMoney;
    read.open("appliedMoney.txt");
    read >> countAppliedMoney;
    read.ignore();
    for (int i = 0; i < countAppliedMoney; i++) {
        getline(read, stringUserIDMoney, ',');
        appliedMoney[i].userIDMoney = stoi(stringUserIDMoney);
        getline(read, appliedMoney[i].fnameMoney, ',');
        getline(read, appliedMoney[i].agEMoney, ',');
        getline(read, appliedMoney[i].homeAddressMoney, ',');
        getline(read, appliedMoney[i].contactMoney, ',');
        getline(read, appliedMoney[i].workMoney, ',');
        getline(read, appliedMoney[i].earningsMoney, ',');
        getline(read, appliedMoney[i].workAddressMoney, ',');
        getline(read, appliedMoney[i].otherNameMoney, ',');
        getline(read, appliedMoney[i].otherContactMoney, ',');
        getline(read, appliedMoney[i].loanTypeMoney, ','); 
        getline(read, stringMonpayMoney, ',');
        appliedMoney[i].monpayMoney = stoi(stringMonpayMoney);
        getline(read, stringinterestMoney, ',');
        appliedMoney[i].interestMoney = stoi(stringinterestMoney);
        getline(read, appliedMoney[i].intereststatusMoney, ','); 
        getline(read, stringmonthsToPayMoney, ',');
        appliedMoney[i].monthsToPayMoney = stoi(stringmonthsToPayMoney);
        getline(read, stringmonthsPaidMoney, ',');
        appliedMoney[i].monthsPaidMoney = stoi(stringmonthsPaidMoney);
        getline(read, stringpriceLoanMoney, ',');
        appliedMoney[i].priceLoanMoney = stoi(stringpriceLoanMoney);
        getline(read, appliedMoney[i].validIDMoney, ',');
        getline(read, appliedMoney[i].proofBillingMoney, ',');
        getline(read, appliedMoney[i].paySlipMoney, ',');
        getline(read, appliedMoney[i].appliedStatusMoney);

        read >> appliedMoney[i].dueDateMoney.tm_sec >> appliedMoney[i].dueDateMoney.tm_min >> appliedMoney[i].dueDateMoney.tm_hour >> 
                appliedMoney[i].dueDateMoney.tm_mday >> appliedMoney[i].dueDateMoney.tm_mon >> appliedMoney[i].dueDateMoney.tm_year >>
                appliedMoney[i].dueDateMoney.tm_wday >> appliedMoney[i].dueDateMoney.tm_yday >> appliedMoney[i].dueDateMoney.tm_isdst;
    }
    read.close(); 
}

void saveAppliedMoney(){
    ofstream write;
	write.open("appliedMoney.txt", ios::out | ios::trunc);
	write << countAppliedMoney << endl;
    for(int i=0; i<countAppliedMoney; i++){
        write << appliedMoney[i].userIDMoney << "," << appliedMoney[i].fnameMoney << "," << appliedMoney[i].agEMoney << "," << appliedMoney[i].homeAddressMoney << "," << appliedMoney[i].contactMoney << "," << appliedMoney[i].workMoney << "," << appliedMoney[i].earningsMoney << "," << appliedMoney[i].workAddressMoney << "," << appliedMoney[i].otherNameMoney << "," << appliedMoney[i].otherContactMoney << "," << appliedMoney[i].loanTypeMoney << "," << appliedMoney[i].monpayMoney << "," << appliedMoney[i].interestMoney << "," << appliedMoney[i].intereststatusMoney <<"," << appliedMoney[i].monthsToPayMoney << "," << appliedMoney[i].monthsPaidMoney <<"," << appliedMoney[i].priceLoanMoney <<"," << appliedMoney[i].validIDMoney <<"," << appliedMoney[i].proofBillingMoney <<"," << appliedMoney[i].paySlipMoney << "," << appliedMoney[i].appliedStatusMoney << endl;

        write << appliedMoney[i].dueDateMoney.tm_sec << " " << appliedMoney[i].dueDateMoney.tm_min << " " << appliedMoney[i].dueDateMoney.tm_hour << " " <<
                appliedMoney[i].dueDateMoney.tm_mday << " " << appliedMoney[i].dueDateMoney.tm_mon << " " << appliedMoney[i].dueDateMoney.tm_year << " " <<
                appliedMoney[i].dueDateMoney.tm_wday << " " << appliedMoney[i].dueDateMoney.tm_yday << " " << appliedMoney[i].dueDateMoney.tm_isdst << endl;
    }
    write.close();
}


// read and save for user
void loadUser(){
	ifstream read;
	string stringAge;
	string stringUserID;
	string stringCash;
	read.open("user.txt");
	read >> countUser;
	read.ignore();
	for(int i = 0; i < countUser; i++){
		getline(read, stringUserID, ',');
		user[i].userid = stoi(stringUserID);
		getline(read, user[i].fullName, ',');
		getline(read, stringAge, ',');
		user[i].age = stoi(stringAge);
		getline(read, user[i].address, ',');
		getline(read, user[i].username, ',');
		getline(read, user[i].password, ',');
		getline(read, stringCash, ',');
		user[i].cash = stof(stringCash);
		read >> user[i].status;
	}
	read.close();
}

void saveUser(){
	ofstream write;
	write.open("user.txt");
	write << countUser <<endl;
	for(int i=0; i<countUser; i++){
		write << user[i].userid << "," << user[i].fullName << "," << user[i].age << "," << user[i].address << ",";
		write << user[i].username << "," << user[i].password << "," << user[i].cash << "," << user[i].status <<endl;
	}
	write.close();
}

//money loan
void saveMoney(){
	ofstream write;
	write.open("money.txt");
	write << countMoney <<endl;
	for(int i=0; i<countMoney; i++){
		write << money[i].moneyPrice << "," << money[i].interest << "," << money[i].quantityMoney << endl;
	}
	write.close();
}
void loadMoney(){
	ifstream read;
	string stringMoneyPrice;
    string stringInterest;
    string stringQuantityMoney;
	read.open("money.txt");
	read >> countMoney;
	read.ignore();
	for(int i = 0; i < countMoney; i++){
		getline(read, stringMoneyPrice, ',');
		money[i].moneyPrice = stof(stringMoneyPrice);
        getline(read, stringInterest, ',');
		money[i].interest = stof(stringInterest);
        getline(read, stringQuantityMoney);
		money[i].quantityMoney = stof(stringQuantityMoney);
	}
	read.close();
}


//gadget loan
void loadBrandName(){
	ifstream read;
	string stringAge;
	read.open("gadget.txt");
	read >> countGadgetCateg;
	read.ignore();
	for(int i = 0; i < countGadgetCateg; i++){
		getline(read, brand[i].brandName);
	}
	read.close();
}
void saveBrandName(){
	ofstream write;
	write.open("gadget.txt");
	write << countGadgetCateg <<endl;
	for(int i=0; i<countGadgetCateg; i++){
		write << brand[i].brandName <<endl;
	}
	write.close();
}
void loadProduct() {
    ifstream read;
    string line;
    string stringPrice;
    string stringQuantityProduct;
    read.open("product.txt");

    read >> countProducts;
    read.ignore(); 

    for (int i = 0; i < countProducts; i++) {
            getline(read, product[i].brand, ',');
            getline(read, product[i].unit, ',');
            getline(read, product[i].display, ',');
            getline(read, product[i].body, ',');
            getline(read, product[i].variant, ',');
            getline(read, product[i].camera, ',');
            getline(read, product[i].battery, ',');
            getline(read, product[i].processor, ',');
            getline(read, stringQuantityProduct, ',');
            product[i].quantityProduct = stof(stringQuantityProduct);
            getline(read, stringPrice);
            product[i].price = stof(stringPrice);
    }

    read.close();
}

void saveProduct(){
	ofstream write;
	write.open("product.txt");
	write << countProducts <<endl;
	for(int i=0; i<countProducts; i++){
		write << product[i].brand <<","<<product[i].unit<<","<<product[i].display <<","<<product[i].body<<",";
		write << product[i].variant<<","<<product[i].camera<<","<<product[i].battery<<","<<product[i].processor<<",";
		write << product[i].quantityProduct<<","<<product[i].price<<endl;
	}
	write.close();
}


void clearscreen()
{
	cout << "\033[2J\033[1;1H";

}
// int main
int main(){
	loadBrandName();
	loadMoney();
	loadUser();
	loadProduct();
    loadApplied();
    loadAppliedMoney();
    loadFeedbacks();
    loadTransactions();
    srand(time(nullptr));
	mainMenu();
    return 0;
}

void mainMenu(){
    loadBrandName();
	loadMoney();
	loadUser();
	loadProduct();
    loadApplied();
    loadAppliedMoney();
    loadFeedbacks();
    loadTransactions();
	system("cls");
	cout<<"========================================================================================================================"<<endl;
	cout<<endl;
	cout<<endl;
	setCyanColor();
	cout<<setw(37)<<lower<<lower<<lower<<setw(15)<<setw(4)<<lower<<lower<<setw(3)<<lower<<lower<<lower<<setw(3)<<lower<<lower<<lower<<setw(15)<<setw(4)<<lower<<lower<<setw(3)<<lower<<setw(4)<<lower<<setw(4)<<lower<<lower<<lower<<lower<<setw(3)<<lower<<lower<<setw(4)<<lower<<lower<<lower<<setw(2)<<lower<<lower<<lower<<lower<<endl;
	cout<<setw(37)<<full<<setw(3)<<full<<setw(2)<<full<<setw(3)<<full<<setw(2)<<full<<setw(3)<<full<<setw(2)<<full<<setw(3)<<full<<setw(2)<<full<<setw(3)<<full<<setw(2)<<full<<setw(4)<<full<<setw(4)<<full<<setw(5)<<full<<setw(3)<<full<<setw(2)<<full<<setw(5)<<full<<endl;
	cout<<setw(37)<<full<<full<<full<<setw(3)<<full<<setw(3)<<full<<setw(2)<<full<<setw(2)<<full<<setw(3)<<full<<setw(2)<<full<<setw(3)<<full<<setw(3)<<full<<setw(2)<<full<<setw(2)<<full<<setw(2)<<full<<setw(4)<<full<<upper<<upper<<setw(3)<<full<<upper<<upper<<full<<setw(3)<<upper<<upper<<lower<<setw(2)<<full<<upper<<upper<<endl;
	cout<<setw(37)<<full<<setw(3)<<full<<setw(2)<<full<<setw(3)<<full<<setw(2)<<full<<setw(3)<<full<<setw(2)<<full<<setw(3)<<full<<setw(2)<<full<<setw(3)<<full<<setw(3)<<full<<setw(2)<<full<<setw(5)<<full<<setw(5)<<full<<setw(3)<<full<<setw(5)<<full<<setw(2)<<full<<endl;
	cout<<setw(37)<<upper<<upper<<upper<<setw(15)<<setw(4)<<upper<<upper<<setw(3)<<upper<<setw(3)<<upper<<setw(2)<<upper<<setw(3)<<upper<<setw(15)<<setw(3)<<upper<<upper<<setw(4)<<upper<<setw(2)<<upper<<setw(5)<<upper<<upper<<upper<<upper<<setw(2)<<upper<<setw(3)<<upper<<setw(2)<<upper<<upper<<upper<<setw(3)<<upper<<upper<<upper<<upper<<endl;
	cout<<endl;
	cout<<endl;
    resetColor();
	cout<<"========================================================================================================================"<<endl;
	cout<<endl;
	cout<<"\t\t\t\t\t\t[1] Login"<<endl;
	cout<<"\t\t\t\t\t\t[2] Registration"<<endl;
	cout<<"\t\t\t\t\t\t[3] Change Password"<<endl;
	cout<<"\t\t\t\t\t\t[4] Exit"<<endl;
	cout<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tSelect option: ";
	cin>>option;
	cout<<"========================================================================================================================"<<endl;
	switch(option){
		case 1: login();break;
		case 2: registration();break;
		case 3: changePassword();break; 
		case 4: cout<<endl<<"\t\t\t\t\t\tPress any key to exit..."; 
			exit(0);
			break;
		default: 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            mainMenu(); 
            break;
	}
}

void login() {
    int maxAttempts = 3;
    int remainingAttempts = maxAttempts;
    int waitTime = 60; // 1 minute in seconds
    time_t waitStartTime = 0;
    system("cls");

    do {
        if (remainingAttempts == 0) {
            // Check if the user needs to wait
            time_t currentTime = time(nullptr);
            if (currentTime - waitStartTime < waitTime) {
                int remainingTime = waitTime - (currentTime - waitStartTime);
                cout << "\t\t\t\t\t\tYou have reached the maximum login attempts. Please wait for ";
                cout << remainingTime << " seconds before trying again." << endl;
                cout<<"========================================================================================================================"<<endl;
                for (int i = remainingTime; i >= 1; --i) {
                    cout << "\t\t\t\t\t\tRemaining Time: " << i << " seconds\r" << flush;
                    this_thread::sleep_for(std::chrono::seconds(1));
                }
            } else {
                remainingAttempts = maxAttempts;
                waitStartTime = 0;
                main();
                break; // Return to the home menu after displaying the remaining time
            }
        }
        cin.ignore();
        system("cls");
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\t\tLOGIN" << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\tEnter your username: ";
        getline(cin, userLog);
        cout << "\t\t\t\t\tEnter your password: ";
        cin >> passLog;

        cout<<"========================================================================================================================"<<endl;
        cout << "\n\n\t\t\t\t\tLOGGING IN ";
        char x = 219;
        
        for (int i = 0; i <= 30; i++) {
            Sleep(30);
            cout << x;
        }
        
        
        bool foundUser = false;
        int chk = 0;
        for (int i = 0; i < countUser; i++) {
            chk = 0;
            if (user[i].username == userLog && user[i].password == passLog) {
                chk = 1;
				if(user[i].status == 1) {
					chk=1;
					foundUser = true;
					userHome();
				}else{
					cout<<"========================================================================================================================"<<endl;
					cout<<"\t\t\t\t\tYour Account is banned!"<<endl;
					cout<<"========================================================================================================================"<<endl;
				}
			}
        }
         if (!foundUser) {
        cout << "\n\t\t\t\t\t\tUser not found." << endl;
        }
        
        if ("admin" == userLog && "admin123" == passLog) {
            chk = 1;
            adminHome();
            break;
        }
        if (chk != 1) {
            --remainingAttempts;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\tInvalid username/Password!" << endl;
            cout<<"========================================================================================================================"<<endl;

            if (remainingAttempts == 0) {
                waitStartTime = time(nullptr);
                cout << "\t\t\t\t\t\tYou have reached the maximum login attempts." << endl;
                cout << "\t\t\t\t\t\tPlease wait for 1 minute before trying again." << endl;
                cout<<"========================================================================================================================"<<endl;
                for (int i = waitTime; i >= 1; --i) {
                    cout << "\t\t\t\t\t\tRemaining Time: " << i << " seconds\r" << flush;
                    this_thread::sleep_for(std::chrono::seconds(1));
                }
				cout<<"\t\t\t\t\t\tYou can now Login..."<<endl;
				cout<<"========================================================================================================================"<<endl;
				system("pause");
                main();
                break;
            }
	        cout << "\t\t\t\t\tDo you want to login again? [Y/N]: ";
	        cin >> choice;
        }
    } while (choice == 'y' || choice == 'Y');

    if (choice == 'n' || choice == 'N') {
        main(); // Go back to the home menu if the user chooses not to log in again
    } else {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\t\t\t\t\t\tInvalid input!" << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        mainMenu(); 
    }
}
void registration() {
    system("cls");
    cin.ignore();

    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tREGISTRATION" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\tEnter your full name: ";
    getline(cin, user[countUser].fullName);

    // Generate user ID
    user[countUser].userid = countUser + 2000;

    int age;
    bool isValidAge = false;

    do {
        cout << "\t\t\t\tEnter your age: ";
        cin >> age;

        if (age >= 18) {
            isValidAge = true;
            user[countUser].age = age;
        } else {
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\tYour age is not qualified for this registration..." << endl;
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            main();
        }
    } while (!isValidAge);

    cin.ignore();
    cout << "\t\t\t\tEnter your address: ";
    getline(cin, user[countUser].address);

    string tempUsername;
    bool isTaken = false;

    do {
        cout << "\t\t\t\tEnter your preferred username: ";
        getline(cin, tempUsername);

        isTaken = false;
        for (int i = 0; i < countUser; i++) {
            if (user[i].username == tempUsername) {
                isTaken = true;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\tThis username is already taken!" << endl;
                cout << "\t\t\t\tPlease enter another username." << endl;
                cout<<"========================================================================================================================"<<endl;
                break;
            }
        }
    } while (isTaken);

    user[countUser].username = tempUsername;

    cout << "\t\t\t\tEnter your password: ";
    cin >> user[countUser].password;
    user[countUser].cash = 0;
    user[countUser].status = true;

    int option;
    clearscreen:
    terms:
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tTERMS AND CONDITION" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\tThis Term Sheet is to be utilized for disclosure of possible"<<endl;
	cout<<"\t\t\t\tterms and conditions only.  This is not to be construed as"<<endl;
	cout<<"\t\t\t\ta commitment to lend.  Terms and conditions are subject to"<<endl;
	cout<<"\t\t\t\tchange at the sole discretion of [Name of the system]."<<endl;
	cout<<"\t\t\t\tLoan Commitments will embody the requirements for loan closing."<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\tTerms to be followed :: "<<endl;
	cout<<"\t\t\t\tBorrower shall pay a non-refundable loan fee equal to"<<endl;
	cout<<"\t\t\t\t[Percentage of interest], collected and calculated as"<<endl;
	cout<<"\t\t\t\tfollows: (Depends on the interest percentage)"<<endl;
	cout<<"\t\t\t\ti) [Percent] of the Loan amount, whichever "<<endl;
	cout<<"\t\t\t\tis greater, to be paid at the time the Commitment"<<endl;
	cout<<"\t\t\t\t is accepted by Borrower. "<<endl;
	cout<<"\t\t\t\tii) In case of an event of default, the Borrower "<<endl;
	cout<<"\t\t\t\tshall, to the extent permitted by law, be obligated"<<endl;
	cout<<"\t\t\t\tto pay interest at the Additional Rate of Interest"<<endl;
	cout<<"\t\t\t\t(before and after judgment or award) on the overdue"<<endl;
	cout<<"\t\t\t\tamount to the other party on demand, for the period"<<endl;
	cout<<"\t\t\t\tfrom (and including) the original Due Date for payment"<<endl;
	cout<<"\t\t\t\tto (but excluding) the date of actual payment."<<endl;
	cout<<"\t\t\t\tiii) The borrower acknowledges and agrees that "<<endl;
	cout<<"\t\t\t\tthe interest rates set forth in the Transaction "<<endl;
	cout<<"\t\t\t\tDocuments are reasonable and that they accurately"<<endl;
	cout<<"\t\t\t\tforesee the loss that the Lender expects to suffer"<<endl;
	cout<<"\t\t\t\tin the event that the Borrower defaults on his or "<<endl;
	cout<<"\t\t\t\ther obligations. In the case that the borrower fails"<<endl;
	cout<<"\t\t\t\tto make the aforementioned payments, the lender will"<<endl;
	cout<<"\t\t\t\thave the option-but not the obligation-to make up the"<<endl;
	cout<<"\t\t\t\tdifference by directly debiting the borrower's account"<<endl;
	cout<<"\t\t\t\tor in another manner, but only after receiving payment1"<<endl;
	cout<<"\t\t\t\tfor all expenses that it incurred."<<endl;
	cout<<"\t\t\t\tiv) Each payment must be made by the Due Date, per "<<endl;
	cout<<"\t\t\t\tthe Borrower. The borrower acknowledges that the "<<endl;
	cout<<"\t\t\t\tpayment must be paid on the Business Day prior to "<<endl;
	cout<<"\t\t\t\tthe respective Due Date if that date is not a Business Day."<<endl;
	cout<<"\t\t\t\tv) Without regard to any provisions of the applicable law"<<endl;
	cout<<"\t\t\t\tor anything stated in the Transaction Documents, the money"<<endl;
	cout<<"\t\t\t\treturned by the Borrower shall be allocated as follows: "<<endl;
	cout<<"\t\t\t\tfirst, to costs, charges, and expenses and other funds; "<<endl;
	cout<<"\t\t\t\tsecond, to interest on costs, charges, and expenses and "<<endl;
	cout<<"\t\t\t\tother funds; third, to interest on late payments; fourth, "<<endl;
	cout<<"\t\t\t\tto interest payable under the Transaction Documents; and, "<<endl;
	cout<<"\t\t\t\tfinally, to repayment of any principal amounts. The Borrower"<<endl;
	cout<<"\t\t\t\tmust occasionally offer security in a way that is acceptable "<<endl;
	cout<<"\t\t\t\tto the Lender, if requested to do so by the Lender."<<endl;
	cout<<"\t\t\t\tvi) The Borrower acknowledges that any contract or arrangement"<<endl;
	cout<<"\t\t\t\tbetween the Lender and any third parties are independent of "<<endl;
	cout<<"\t\t\t\tthese Standard Terms"<<endl;
	cout<<"\t\t\t\tvii)	Except for changes to the interest rate, the Lender"<<endl;
	cout<<"\t\t\t\tmaintains the right to modify these Standard Terms by "<<endl;
	cout<<"\t\t\t\tnotifying the borrower in advance."<<endl;
	cout<<"\t\t\t\tviii) If a loan is more than 30 days past due, the "<<endl;
	cout<<"\t\t\t\tcorporation maintains the right to levy compound interest"<<endl;
	cout<<"\t\t\t\t(50 Philippine Peso) for each additional 30 days of lateness."<<endl;
	cout<<"\t\t\t\tx) If a loan is failed to be pay above the 30 days past due,"<<endl;
	cout<<"\t\t\t\tlaw according to the Philippine constitution shall be obeyed. "<<endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t[1] Agree [2] Cancel" << endl;
    cout << "\t\t\t\t\t\tSelect option : ";
    cin >> option;
    cout<<"========================================================================================================================"<<endl;
    switch (option) {
        case 1:
            cout << "\t\t\t\t\t\tSuccessfully Registered!" << endl;
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            countUser++;
            saveUser();
            main();
            return;
        case 2:
            cout << "\t\t\t\t\t\tCancel Registration..." << endl;
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            return;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("PAUSE");
            goto terms;
    }
}

void changePassword() {
    string username;
    string currentPassword;
    string newPassword;

    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t\tCHANGE PASSWORD" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\tEnter your username: ";
    cin >> username;
    cout << "\t\t\t\t\tEnter your current password: ";
    cin >> currentPassword;

    int userIndex = -1;

    for (int i = 0; i < countUser; i++) {
        if (user[i].username == username && user[i].password == currentPassword) {
            userIndex = i;
            break;
        }
    }

    if (userIndex != -1) {
        cout << "\t\t\t\t\tEnter your new password: ";
        cin >> newPassword;
        user[userIndex].password = newPassword;
        saveUser();
        cout << "\t\t\t\t\tPassword changed successfully!" << endl;
        cout<<"========================================================================================================================"<<endl;
        system("pause");
        main();
    } else {
        cout << "\t\t\t\t\tInvalid username or current password." << endl;
        cout<<"========================================================================================================================"<<endl;
        system("pause");
        main();
    }
}
//admin
void adminHome(){
	system("cls");
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\t\tADMIN HOME"<<endl;
    cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t[1] User Account"<<endl;
	cout<<"\t\t\t\t\t[2] Inventory"<<endl;
	cout<<"\t\t\t\t\t[3] Transaction History"<<endl;
	cout<<"\t\t\t\t\t[4] View Loan Applications"<<endl;
	cout<<"\t\t\t\t\t[5] View Feedback"<<endl;
    cout<<"\t\t\t\t\t[6] View Due Loans"<<endl;
    cout<<"\t\t\t\t\t[7] Logout"<<endl;
    cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\tSelect option : ";
	cin>>option;
	cout<<"========================================================================================================================"<<endl;
	switch(option){
		case 1: userAccount();break;
		case 2: inventory();break; 
		case 3: transactionHistory();break; 
        case 4: listAppliedUser();break;
		case 5: feedbackAdmin();break;
        case 6: displayDueLoans();break;
		case 7: logout();break;
		default: 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			adminHome(); 
	}
}
void userAccount(){
	system("cls");
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\t\tUSER ACCOUNTS"<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\t[1] Show All Users "<<endl;
	cout<<"\t\t\t\t\t\t[2] Delete a User"<<endl;
	cout<<"\t\t\t\t\t\t[3] Back"<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tSelect Option : ";
	cin>>option;
	cout<<"========================================================================================================================"<<endl;
	switch(option){
		case 1: showAllUser();break;
		case 2: deleteUser();break;
		case 3: adminHome();break; 
		default: 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			userAccount();
	}
}
void showAllUser(){
	system("cls");
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tSHOW ALL USER ACCOUNTS"<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\tUser ID"<<"\t\t\tUsername"<<"\t\t\t\tStatus"<<endl;
	cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
	for(int i=0; i<countUser; i++){
		chk=0;
		if(countUser!= 0){
			chk=1;
			cout<<"\t\t\t"<<user[i].userid<<"\t\t\t"<<user[i].username<<"\t\t\t\t\t"<<"Active"<<endl;
		}
	}
	if(chk != 1){
		cout<<"\t\t\t\t\t\tNo Record Found!"<<endl;
	}
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\t[1] View Search Options"<<endl;
    cout<<"\t\t\t\t\t\t[2] Sort Users"<<endl;
	cout<<"\t\t\t\t\t\t[3] Back"<<endl;
    cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tSelect Option : ";
	cin>>option;
	switch(option){
		case 1: 
            searchUser();
            break;
        case 2:
            sortuserAdmin();
		case 3: 
            userAccount();
            break;
		default: 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			userAccount();
		}
}

void deleteUser() {
    char choice;
    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t\tREMOVE A USER\n";
    cout<<"========================================================================================================================"<<endl;
    cout <<  "\t\t\tAccount No." << "\t\t\tUsername" << "\t\t\t\tStatus" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < countUser; i++) {
        chk = 0;
        if (countUser != 0) {
            chk = 1;
            cout << "\t\t\t" << i + 1 << "\t\t\t" << user[i].username << "\t\t\t\t\t" << "Active" << endl;
        }
    }
    if (chk != 1) {
        cout << "\t\t\t\t\t\tNo Record Found!" << endl;
    }
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tEnter Number to be deleted : ";
    cin >> num;
    cout<<"========================================================================================================================"<<endl;
    cout<<"\t\t\t\t\t\tAre you sure you want to delete that user?[Y/N]: ";
    cin>>choice;
    if (choice == 'Y' || choice == 'y'){
    int index = -1;
        for (int i = 0; i < countUser; i++) {
            if (i + 1 == num) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            for (int i = index; i < countUser - 1; i++) {
                user[i] = user[i + 1];
            }
            countUser--;
            cout << "\n\t\t\t\t\t\tUser deleted successfully!\n";
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            saveUser(); // Save the updated user data
            userAccount(); // Display the updated list of users
        }
        else {
            cout << "\n\t\t\t\t\t\tRecord not found!\n";
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            system("cls");
            userAccount(); // Show the user list again
        }
    } else if (choice == 'N' || choice == 'n'){
        cout << "\n\t\t\t\t\t\tCanceled deletion of that user\n";
        cout<<"========================================================================================================================"<<endl;
        system("pause");
        userAccount();
    } else {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\t\t\t\t\t\tInvalid input!" << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        userAccount();
    }
    
}

void searchUser(){
	string tempUser;
    string tempType;
	int tempAccount;
    int tempUserID;
    system("cls");
    bool foundUser;
    cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tSEARCH USERS"<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\t[1] Search by UserID"<<endl;
	cout<<"\t\t\t\t\t\t[2] Search by Username"<<endl;
	cout<<"\t\t\t\t\t\t[3] Back"<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tSelect option : ";
	cin>>option;
	switch(option){
		case 1:	
            system("cls");
            cout<<"========================================================================================================================"<<endl;
	        cout<<"\t\t\t\t\t\tSEARCH USER ID"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\t\tSearch User ID: ";
            cin>>tempUserID;
            
            foundUser = false;
            for(int i=0; i<countUser; i++){
                if(tempUserID == user[i].userid){
                        if (user[i].userid >= 2000 && user[i].userid < 3000) {
                            foundUser = true;
                            system("cls");
                            cout<<"========================================================================================================================"<<endl;
                            cout << "\t\t\t\t\t\t\tSHOWING USER ID. " << tempUserID << endl;
                            cout<<"========================================================================================================================"<<endl;
                            cout << "\t\t\t\t\t\tUserID: " << user[i].userid << endl;
                            cout << "\t\t\t\t\t\tUsername: " << user[i].username << endl;
                            cout << "\t\t\t\t\t\tPassword: " << user[i].password << endl;
                            cout << "\t\t\t\t\t\tFull Name: " << user[i].fullName << endl;
                            cout << "\t\t\t\t\t\tAge: " << user[i].age << endl;
                            cout << "\t\t\t\t\t\tAddress: " << user[i].address << endl;
                            cout << "\t\t\t\t\t\tBalance: " << user[i].cash << endl;
                            if (user[i].status == 1) {
                                tempType = "Active";
                            } else if (user[i].status == 0) {
                                tempType = "Inactive";
                            }
                            cout << "\t\t\t\t\t\tStatus: " << tempType << endl;
                            cout<<"========================================================================================================================"<<endl;
                        }
                    }
                    
                }
            if(!foundUser){
                cout<<endl<<"\t\t\t\t\t\tNo Record Found!"<<endl;
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                searchUser();
            }
        break;
		case 2: 
                system("cls");
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\t\tSEARCH USER NAME"<<endl;
				cout<<"========================================================================================================================"<<endl;
                cin.ignore();
				cout<<"\t\t\t\t\t\tEnter Username: ";
				getline(cin, tempUser);
                system("cls");
                foundUser = false;
				for(int i=0; i<countUser; i++){
					if(tempUser == user[i].username){
                        foundUser = true;
						system("cls");
                        cout<<"========================================================================================================================"<<endl;
                        cout<<"\t\t\t\t\t\tSHOWING USERNAME: "<<tempUser<<endl;
                        cout<<"========================================================================================================================"<<endl;
                        cout<<"\t\t\t\t\t\tUserID: "<<user[i].userid<<endl;
                        cout<<"\t\t\t\t\t\tUsername: "<<user[i].username<<endl;
                        cout<<"\t\t\t\t\t\tPassword: "<<user[i].password<<endl;
                        cout<<"\t\t\t\t\t\tFull Name: "<<user[i].fullName<<endl;
                        cout<<"\t\t\t\t\t\tAge: "<<user[i].age<<endl;
                        cout<<"\t\t\t\t\t\tAddress: "<<user[i].address<<endl;
                        cout<<"\t\t\t\t\t\tBalance: "<<user[i].cash<<endl;
                        if (user[i].status == 1){
                            tempType = "Active";
                        } else if (user[i].status == 0){
                            tempType = "Inactive";
                        }
                        cout<<"\t\t\t\t\t\tStatus: "<<tempType<<endl;
                        cout<<"========================================================================================================================"<<endl;
					}
				}
                if(!foundUser){
                    cout<<"========================================================================================================================"<<endl;
                    cout<<"\t\t\t\t\t\tSEARCH USER NAME"<<endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout<<endl<<"\t\t\t\t\t\tNo Record Found!"<<endl;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tPress Enter to continue...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    searchUser();
                }
			break;
		case 3: showAllUser();break;
		default: 
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\t\tSEARCH USER NAME"<<endl;
			cout<<"========================================================================================================================"<<endl;
            cout<<endl<<"\t\t\t\t\t\tNo Record Found!"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			searchUser();
    }
	cout<<"\t\t\t\t\t\t[1] Back"<<endl;
    cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tSelect Option : ";
	cin>>option;
	cout<<"========================================================================================================================"<<endl;
	switch(option){
		case 1: searchUser();break;
		default: 
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\t\t\tSEARCH USER NAME"<<endl;
			cout<<"========================================================================================================================"<<endl;
            cout<<endl<<"\t\t\t\t\t\tNo Record Found!"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			searchUser();
	}
}

void listAppliedUser() {
    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tLIST OF APPLIED USERS\n";
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t[1] Money Applications\n";
    cout << "\t\t\t\t\t\t[2] Gadget Applications\n";
    cout << "\t\t\t\t\t\t[3] Money Applications Records\n";
    cout << "\t\t\t\t\t\t[4] Gadget Applications Records\n";
    cout << "\t\t\t\t\t\t[5] Back\n";
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tSelect Option : ";
    int option;
    cin >> option;
    switch (option) {
        case 1:
            listAppliedMoney();
            break;
        case 2:
            listAppliedGadget();
            break;
        case 3:
            recordsUserMoney();
            break;
        case 4:
            recordsUserGadget();
            break;
        case 5:
            adminHome();
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            userAccount();

    }
}

void recordsUserGadget() {
    system("cls");
    loadApplied();
    int tempNum;
    char choice;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tGADGET REQUIREMENTS RECORDS"<<endl;
	cout<<"========================================================================================================================"<<endl;
    cout <<  "\t\t\tNo." << "\tUser" << "\tProduct" << "\t\tValid ID" << "\tProof of Billing" << "\tPay Slip" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < countApplied; i++) {
        chk = 0;
        if (countApplied != 0) {
            chk = 1;
            cout << "\t\t\t" << i + 1 << "\t" << applied[i].fname << "\t" << applied[i].unitLoan << "\t\t[" << applied[i].validID << "]\t\t[" << applied[i].proofBilling << "]\t\t[" << applied[i].paySlip <<"]"<< endl;
        }
    }
    if (chk != 1) {
        cout << "\t\t\t\t\t\tNo Record Found!" << endl;
    }
	cout<<"[1] View More"<<endl;
    cout<<"[2] Back"<<endl;
    cout<<"========================================================================================================================"<<endl;
    cout<<"Select option: ";
    cin>>option;
    switch(option){
        case 1:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\t\tGADGET REQUIREMENTS RECORDS"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout <<  "\t\t\tNo." << "\tUser" << "\tProduct" << "\t\tValid ID" << "\tProof of Billing" << "\tPay Slip" << endl;
            cout << "---------------------------------------------------------------------------------------------------------------------\n";
            for (int i = 0; i < countApplied; i++) {
                chk = 0;
                if (countApplied != 0) {
                    chk = 1;
                        cout << "\t\t\t" << i + 1 << "\t" << applied[i].fname << "\t" << applied[i].unitLoan << "\t\t[" << applied[i].validID << "]\t\t[" << applied[i].proofBilling << "]\t\t[" << applied[i].paySlip <<"]"<< endl;
                }
            }
            if (chk != 1) {
                cout << "\t\t\t\t\t\tNo Record Found!" << endl;
            }
            cout<<"========================================================================================================================"<<endl;
            cout<<"Select number: ";
            cin>>tempNum;
            tempNum--;
            if (tempNum >= 0 && tempNum < countApplied){
            system("cls");
                cout<<"\t\t\t\t\t\tGADGET REQUIREMENTS RECORDS"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout <<  "\t\t\tNo." << "\tUser" << "\tProduct" << "\t\tValid ID" << "\tProof of Billing" << "\tPay Slip" << endl;
                cout << "---------------------------------------------------------------------------------------------------------------------\n";
                cout << "\t\t\t" << tempNum + 1<< "." << "\t" << applied[tempNum].fname << "\t" << applied[tempNum].unitLoan << "\t\t[" << applied[tempNum].validID << "]\t\t[" << applied[tempNum].proofBilling << "]\t\t[" << applied[tempNum].paySlip <<"]"<< endl;
                if (chk != 1) {
                    cout << "\t\t\t\t\t\tNo Record Found!" << endl;
                }
            } else {
                cout << "\t\t\t\t\t\tNo Record Found!" << endl;
                cout<<"========================================================================================================================"<<endl;
                system("pause");
                recordsUserGadget();
            }
            cout<<"[1] Update Valid ID"<<endl;
            cout<<"[2] Update Billing"<<endl;
            cout<<"[3] Update Pay Slip"<<endl;
            cout<<"[4] Update All"<<endl;
            cout<<"[5] Back"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"Select option: ";
            cin>>option;
            switch(option){
                case 1:
                    if (applied[tempNum].validID == "X"){
                        cout<<"Are you sure user submitted two Valid IDs?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                            cout<<"PROCESSING"<<endl;
                            applied[tempNum].validID = "/";
                            saveApplied();
                            system("pause");
                            recordsUserGadget();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserGadget();
                        }
                    } else if (applied[tempNum].validID == "/") {
                        cout<<"Are you sure you want to undo?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                        cout<<"PROCESSING"<<endl;
                        applied[tempNum].validID = "X";
                        saveApplied();
                        system("pause");
                        recordsUserGadget();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserGadget();
                        }
                    }
                    break;
                case 2:
                    if (applied[tempNum].proofBilling == "X"){
                        cout<<"Are you sure user submitted Proof of Billing?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                            cout<<"PROCESSING"<<endl;
                            applied[tempNum].proofBilling = "/";
                            saveApplied();
                            system("pause");
                            recordsUserGadget();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserGadget();
                        }
                    } else if (applied[tempNum].proofBilling == "/") {
                        cout<<"Are you sure you want to undo?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                        cout<<"PROCESSING"<<endl;
                        applied[tempNum].proofBilling = "X";
                        saveApplied();
                        system("pause");
                        recordsUserGadget();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserGadget();
                        }
                    }
                    break;   
                case 3:
                    if (applied[tempNum].paySlip == "X"){
                        cout<<"Are you sure user submitted a Payslip?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                            cout<<"PROCESSING"<<endl;
                            applied[tempNum].paySlip = "/";
                            saveApplied();
                            system("pause");
                            recordsUserGadget();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserGadget();
                        }
                    } else if (applied[tempNum].paySlip == "/") {
                        cout<<"Are you sure you want to undo?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                        cout<<"PROCESSING"<<endl;
                        applied[tempNum].paySlip = "X";
                        saveApplied();
                        system("pause");
                        recordsUserGadget();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserGadget();
                        }
                    }
                    break;
                case 4:
                    if (applied[tempNum].paySlip == "X"){
                        cout<<"Are you sure user submitted a All Requirements?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                            cout<<"PROCESSING"<<endl;
                            applied[tempNum].validID = "/";
                            applied[tempNum].proofBilling = "/";
                            applied[tempNum].paySlip = "/";
                            saveApplied();
                            system("pause");
                            recordsUserGadget();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserGadget();
                        }
                    } else if (applied[tempNum].paySlip == "/") {
                        cout<<"Are you sure you want to undo?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                        cout<<"PROCESSING"<<endl;
                        applied[tempNum].validID = "X";
                        applied[tempNum].proofBilling = "X";
                        applied[tempNum].paySlip = "X";
                        saveApplied();
                        system("pause");
                        recordsUserGadget();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserGadget();
                        }
                    }
                    break;
                case 5:
                    recordsUserGadget();
                    break;
                default:
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "\t\t\t\t\t\tInvalid input!" << endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tPress Enter to continue...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    recordsUserGadget();                
            }
        case 2:
            listAppliedUser();
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            recordsUserGadget();  
    }
}

void recordsUserMoney() {
    system("cls");
    loadApplied();
    int tempNum;
    char choice;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tMONEY REQUIREMENTS RECORDS"<<endl;
	cout<<"========================================================================================================================"<<endl;
    cout <<  "\t\t\tNo." << "\tUser" << "\tMoney" << "\t\tValid ID" << "\tProof of Billing" << "\tPay Slip" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < countAppliedMoney; i++) {
        chk = 0;
        if (countAppliedMoney != 0) {
            chk = 1;
                cout << "\t\t\t" << i + 1 << "\t" << appliedMoney[i].fnameMoney << "\t" << appliedMoney[i].priceLoanMoney << "\t\t[" << appliedMoney[i].validIDMoney << "]\t\t[" << appliedMoney[i].proofBillingMoney << "]\t\t[" << appliedMoney[i].paySlipMoney <<"]"<< endl;
        }
    }
    if (chk != 1) {
        cout << "\t\t\t\t\t\tNo Record Found!" << endl;
    }
	cout<<"[1] View More"<<endl;
    cout<<"[2] Back"<<endl;
    cout<<"========================================================================================================================"<<endl;
    cout<<"Select option: ";
    cin>>option;
    switch(option){
        case 1:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\t\tMONEY REQUIREMENTS RECORDS"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout <<  "\t\t\tNo." << "\tUser" << "\tMoney" << "\t\tValid ID" << "\tProof of Billing" << "\tPay Slip" << endl;
            cout << "---------------------------------------------------------------------------------------------------------------------\n";
            for (int i = 0; i < countAppliedMoney; i++) {
                chk = 0;
                if (countAppliedMoney != 0) {
                    chk = 1;
                        cout << "\t\t\t" << i + 1 << "\t" << appliedMoney[i].fnameMoney << "\t" << appliedMoney[i].priceLoanMoney << "\t\t[" << appliedMoney[i].validIDMoney << "]\t\t[" << appliedMoney[i].proofBillingMoney << "]\t\t[" << appliedMoney[i].paySlipMoney <<"]"<< endl;
                }
            }
            if (chk != 1) {
                cout << "\t\t\t\t\t\tNo Record Found!" << endl;
            }
            cout<<"========================================================================================================================"<<endl;
            cout<<"Select number: ";
            cin>>tempNum;
            tempNum--;
            if (tempNum >= 0 && tempNum < countAppliedMoney){
            system("cls");
                cout<<"\t\t\t\t\t\tMONEY REQUIREMENTS RECORDS"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout <<  "\t\t\tNo." << "\tUser" << "\tMoney" << "\t\tValid ID" << "\tProof of Billing" << "\tPay Slip" << endl;
                cout << "---------------------------------------------------------------------------------------------------------------------\n";
                cout << "\t\t\t" << tempNum + 1<< ".\t" << appliedMoney[tempNum].fnameMoney << "\t" << appliedMoney[tempNum].priceLoanMoney << "\t\t[" << appliedMoney[tempNum].validIDMoney << "]\t\t[" << appliedMoney[tempNum].proofBillingMoney << "]\t\t[" << appliedMoney[tempNum].paySlipMoney <<"]"<< endl;
                if (chk != 1) {
                    cout << "\t\t\t\t\t\tNo Record Found!" << endl;
                }
            } else {
                cout << "\t\t\t\t\t\tNo Record Found!" << endl;
                cout<<"========================================================================================================================"<<endl;
                system("pause");
                recordsUserMoney();
            }
            cout<<"[1] Update Valid ID"<<endl;
            cout<<"[2] Update Billing"<<endl;
            cout<<"[3] Update Pay Slip"<<endl;
            cout<<"[4] Update All"<<endl;
            cout<<"[5] Back"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"Select option: ";
            cin>>option;
            switch(option){
                case 1:
                    if (applied[tempNum].validID == "X"){
                        cout<<"Are you sure user submitted two Valid IDs?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                            cout<<"PROCESSING"<<endl;
                            appliedMoney[tempNum].validIDMoney = "/";
                            saveApplied();
                            system("pause");
                            recordsUserMoney();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserMoney();
                        }
                    } else if (appliedMoney[tempNum].validIDMoney == "/") {
                        cout<<"Are you sure you want to undo?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                        cout<<"PROCESSING"<<endl;
                        appliedMoney[tempNum].validIDMoney = "X";
                        saveAppliedMoney();
                        system("pause");
                        recordsUserMoney();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserMoney();
                        }
                    }
                    break;
                case 2:
                    if (appliedMoney[tempNum].proofBillingMoney == "X"){
                        cout<<"Are you sure user submitted Proof of Billing?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                            cout<<"PROCESSING"<<endl;
                            appliedMoney[tempNum].proofBillingMoney = "/";
                            saveAppliedMoney();
                            system("pause");
                            recordsUserMoney();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserMoney();
                        }
                    } else if (appliedMoney[tempNum].proofBillingMoney == "/") {
                        cout<<"Are you sure you want to undo?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                        cout<<"PROCESSING"<<endl;
                        appliedMoney[tempNum].proofBillingMoney = "X";
                        saveAppliedMoney();
                        system("pause");
                        recordsUserMoney();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserMoney();
                        }
                    }
                    break;   
                case 3:
                    if (appliedMoney[tempNum].paySlipMoney == "X"){
                        cout<<"Are you sure user submitted a Payslip?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                            cout<<"PROCESSING"<<endl;
                            appliedMoney[tempNum].paySlipMoney = "/";
                            saveAppliedMoney();
                            system("pause");
                            recordsUserMoney();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserMoney();
                        }
                    } else if (appliedMoney[tempNum].paySlipMoney == "/") {
                        cout<<"Are you sure you want to undo?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                        cout<<"PROCESSING"<<endl;
                        appliedMoney[tempNum].paySlipMoney = "X";
                        saveAppliedMoney();
                        system("pause");
                        recordsUserMoney();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserMoney();
                        }
                    }
                    break;
                case 4:
                    if (appliedMoney[tempNum].paySlipMoney == "X"){
                        cout<<"Are you sure user submitted a All Requirements?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                            cout<<"PROCESSING"<<endl;
                            appliedMoney[tempNum].validIDMoney = "/";
                            appliedMoney[tempNum].proofBillingMoney = "/";
                            appliedMoney[tempNum].paySlipMoney = "/";
                            saveAppliedMoney();
                            system("pause");
                            recordsUserMoney();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserMoney();
                        }
                    } else if (appliedMoney[tempNum].paySlipMoney == "/") {
                        cout<<"Are you sure you want to undo?[Y/N]:";
                        cin>>choice;
                        if (choice == 'Y' || choice == 'y'){
                        cout<<"PROCESSING"<<endl;
                        appliedMoney[tempNum].validIDMoney = "X";
                        appliedMoney[tempNum].proofBillingMoney = "X";
                        appliedMoney[tempNum].paySlipMoney = "X";
                        saveAppliedMoney();
                        system("pause");
                        recordsUserMoney();
                        } else if (choice == 'N' || choice == 'n'){
                            cout<<"CANCELING"<<endl;
                            system("pause");
                            recordsUserMoney();
                        }
                    }
                    break;
                case 5:
                    recordsUserMoney();
                    break;
                default:
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "\t\t\t\t\t\tInvalid input!" << endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tPress Enter to continue...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    recordsUserMoney();                
            }
        case 2:
            listAppliedUser();
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            recordsUserGadget();  
    }
}

void listAppliedGadget() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char x = 0;
    loadApplied();
    bool Found = false;
    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tAPPLIED USERS GADGET LOAN\n";
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t[1] Approved\n";
    cout << "\t\t\t\t\t\t[2] Rejected\n";
    cout << "\t\t\t\t\t\t[3] Pending\n";
    cout << "\t\t\t\t\t\t[4] Back\n";
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tSelect Option : ";
    int option;
    int choice;
    cin >> option;
    switch (option) {
        case 1:
        system("cls");
        loadApplied();
                // Get the current date
                

                for (int i = 0; i < countApplied; i++) {
                if (applied[i].appliedStatus == "Approved") {
                    tm dueDate = applied[i].dueDate;
                    // Calculate the difference in days
                    time_t due_time = mktime(&dueDate);
                    double seconds = difftime(due_time, now);
                    int days = seconds / (60 * 60 * 24);

                    if (days >= 0 && days <= 3) {
                        Found = true;
                        cout << "\t\t\t\t[NOTICE] There are " << i + 1<< " Close to Due Loan [NOTICE]"<<endl;
                    }
                }
            }
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tAPPROVED USER LOANS\n";
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\tFullname\tLoan Type\tStatus\t\n";
            cout << "----------------------------------------------------------------------------------------------------------------------\n";
            Found = false;
            for (int i = 0; i < countApplied; i++) {
                if (applied[i].appliedStatus == "Approved") {
                    Found = true;
                    cout << "\t\t\t\t" << i + 1 << ".) " << applied[i].fname << "\t" << applied[i].loanType << "\t" << applied[i].appliedStatus <<endl;
                } 
            }
            if (!Found){
                    cout<<"\t\t\t\t\t\tNo Approved Loans Found!"<<endl;
                    system("pause");
                    listAppliedGadget();
            } 
            
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\t[1] View More\n";
            cout << "\t\t\t\t\t\t[2] Back\n";
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tSelect Option : ";
            cin>>choice;
            switch (choice) {
                case 1:
                system("cls");
                int tempAppliedLoan;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tAPPROVED LOANS\n";
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\tFullname\tLoan Type\tStatus\t\n";
                cout << "----------------------------------------------------------------------------------------------------------------------\n";
                Found = false;
                for (int i = 0; i < countApplied; i++) {
                    if (applied[i].appliedStatus == "Approved") {
                        Found = true;
                        cout << "\t\t\t\t" << i + 1 << ".) " << applied[i].fname << "\t" << applied[i].loanType << "\t" << applied[i].appliedStatus <<endl;
                    } 
                }
                if (!Found){
                        cout<<"\t\t\t\t\t\tNo Approved Loans Found!"<<endl;
                        system("pause");
                        listAppliedGadget();
                    }
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tSelect a number : ";
                cin >> tempAppliedLoan;
                tempAppliedLoan--;
                if (tempAppliedLoan >= 0 && tempAppliedLoan < countApplied) {
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tSELECTED LOAN\n";
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tFull Name: " << applied[tempAppliedLoan].fname << endl;
                    cout << "\t\t\t\t\t\tLoan Type: " << applied[tempAppliedLoan].loanType << endl;
                    cout << "\t\t\t\t\t\tMonthly Payment: " << applied[tempAppliedLoan].monpay << endl;
                    cout << "\t\t\t\t\t\tMonth Due: " << applied[tempAppliedLoan].dueDate.tm_year + 1900 << "-" << applied[tempAppliedLoan].dueDate.tm_mon + 1 << "-" << applied[tempAppliedLoan].dueDate.tm_mday << endl;
                    cout << "\t\t\t\t\t\tDown Payment: " << applied[tempAppliedLoan].downpay << endl;
                    cout << "\t\t\t\t\t\tStatus: " << applied[tempAppliedLoan].appliedStatus << endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\t[1] Back\n";
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tSelect Option : ";
                    cin >> choice;
                    switch(choice){
                        case 1:
                            listAppliedGadget();
                            break;
                        default:
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                            cout << "\t\t\t\t\t\tInvalid input!" << endl;
                            cout<<"========================================================================================================================"<<endl;
                            cout << "\t\t\t\t\t\tPress Enter to continue...";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            listAppliedGadget();
                    }
                case 2:
                    listAppliedGadget();
                    break;
                default:
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                listAppliedGadget();
                } 
            }
        case 2:
        system("cls");
        loadApplied();
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tREJECTED USER LOANS\n";
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\tFullname\tLoan Type\tStatus\t\n";
            cout << "----------------------------------------------------------------------------------------------------------------------\n";
            Found = false;
            for (int i = 0; i < countApplied; i++) {
                if (applied[i].appliedStatus == "Rejected") {
                        Found = true;
                        cout << "\t\t\t\t" << i + 1 << ".) " << applied[i].fname << "\t" << applied[i].loanType << "\t" << applied[i].appliedStatus <<endl;
                } 
            }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo Rejected Loans Found!"<<endl;
                system("pause");
                listAppliedGadget();
            }
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\t[1] View More\n";
            cout << "\t\t\t\t\t\t[2] Back\n";
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tSelect Option : ";
            cin>>choice;
            switch (choice) {
                case 1:
                system("cls");
                int tempAppliedLoan;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tREJECTED USER LOANS\n";
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\tFullname\tLoan Type\ttatus\t\n";
                cout << "----------------------------------------------------------------------------------------------------------------------\n";
                Found = false;
                for (int i = 0; i < countApplied; i++) {
                    if (applied[i].appliedStatus == "Rejected") {
                        Found = true;
                        cout << "\t\t\t\t" << i + 1 << ".) " << applied[i].fname << "\t" << applied[i].loanType << "\t" << applied[i].appliedStatus <<endl;
                    } 
                }
                if (!Found){
                        cout<<"\t\t\t\t\t\tNo Rejected Loans Found!"<<endl;
                        system("pause");
                        listAppliedGadget();
                    }
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tSelect a number : ";
                cin >> tempAppliedLoan;
                tempAppliedLoan--;
                if (tempAppliedLoan >= 0 && tempAppliedLoan < countApplied) {
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tSELECTED LOAN\n";
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tFull Name: " << applied[tempAppliedLoan].fname << endl;
                    cout << "\t\t\t\t\t\tLoan Type: " << applied[tempAppliedLoan].loanType << endl;
                    cout << "\t\t\t\t\t\tMonthly Payment: " << applied[tempAppliedLoan].monpay << endl;
                    cout << "\t\t\t\t\t\tMonth Due: " << applied[tempAppliedLoan].dueDate.tm_year + 1900 << "-" << applied[tempAppliedLoan].dueDate.tm_mon + 1 << "-" << applied[tempAppliedLoan].dueDate.tm_mday << endl;
                    cout << "\t\t\t\t\t\tDown Payment: " << applied[tempAppliedLoan].downpay << endl;
                    cout << "\t\t\t\t\t\tStatus: " << applied[tempAppliedLoan].appliedStatus << endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\t[1] Back\n";
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tSelect Option : ";
                    cin >> choice;
                    switch(choice){
                        case 1:
                            listAppliedGadget();
                            break;
                    }
                case 2:
                    listAppliedGadget();
                    break;
                default:
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                listAppliedGadget();
                } 
            }
        case 3:
        system("cls");
        loadApplied();
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPENDING USER LOANS\n";
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\tFullname\tLoan Type\tStatus\t\n";
            cout << "----------------------------------------------------------------------------------------------------------------------\n";
            Found = false;
            for (int i = 0; i < countApplied; i++) {
                if (applied[i].appliedStatus == "Pending") {
                    Found = true;
                    cout << "\t\t\t\t" << i + 1 << ".) " << applied[i].fname << "\t" << applied[i].loanType << "\t" << applied[i].appliedStatus<<endl;
                } 
            }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo Pending Loans Found!"<<endl;
                system("pause");
                listAppliedGadget();
            }
            cout << "\t\t\t\t\t\t[1] View More\n";
            cout << "\t\t\t\t\t\t[2] Back\n";
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tSelect Option : ";
            cin>>choice;
            switch (choice) {
                case 1:
                system("cls");
                int tempAppliedLoan;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPENDING USER LOANS\n";
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\tFullname\tLoan Type\tStatus\t\n";
                cout << "----------------------------------------------------------------------------------------------------------------------\n";
                Found = false;
                for (int i = 0; i < countApplied; i++) {
                    if (applied[i].appliedStatus == "Pending") {
                        Found = true;
                       cout << "\t\t\t\t" << i + 1 << ".) " << applied[i].fname << "\t" << applied[i].loanType << "\t" << applied[i].appliedStatus <<endl;
                    } 
                }
                if (!Found){
                        cout<<"\t\t\t\t\t\tNo Pending Loans Found!"<<endl;
                        system("pause");
                        listAppliedGadget();
                    }
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tSelect a number : ";
                cin >> tempAppliedLoan;
                tempAppliedLoan--;
                if (tempAppliedLoan >= 0 && tempAppliedLoan < countApplied) {
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tSELECTED LOAN\n";
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tFull Name: " << applied[tempAppliedLoan].fname << endl;
                    cout << "\t\t\t\t\t\tLoan Type: " << applied[tempAppliedLoan].loanType << endl;
                    cout << "\t\t\t\t\t\tMonthly Payment: " << applied[tempAppliedLoan].monpay << endl;
                    cout << "\t\t\t\t\t\tMonth Due: " << applied[tempAppliedLoan].dueDate.tm_year + 1900 << "-" << applied[tempAppliedLoan].dueDate.tm_mon + 1 << "-" << applied[tempAppliedLoan].dueDate.tm_mday << endl;
                    cout << "\t\t\t\t\t\tDown Payment: " << applied[tempAppliedLoan].downpay << endl;
                    cout << "\t\t\t\t\t\tStatus: " << applied[tempAppliedLoan].appliedStatus << endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\t[1] Approve"<<endl;
                    cout << "\t\t\t\t\t\t[2] Reject"<<endl;
                    cout << "\t\t\t\t\t\t[3] Back"<<endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tSelect Option : ";
                    cin >> choice;
                    switch(choice){
                        case 1:
                            applied[tempAppliedLoan].appliedStatus = "Approved";
                            cout<<"\n\n\t\t\t\t\t\tPROCESSING";
                            x=219;
                        
                            for(int i=0; i<=30; i++){
                                Sleep(30);
                                cout<<x;
                            }
                            cout<<"\t\t\t\t\t\tProcess Compelete!"<<endl;
                            cout<<endl;
                            saveApplied();
                            system("PAUSE");
                            listAppliedGadget();
                            break;
                        case 2:
                            applied[tempAppliedLoan].appliedStatus = "Rejected";
                            cout<<"\n\n\t\t\t\t\t\tPROCESSING";
                            x=219;
                        
                            for(int i=0; i<=30; i++){
                                Sleep(30);
                                cout<<x;
                            }
                            cout<<"\t\t\t\t\t\tProcess Compelete!"<<endl;
                            cout<<endl;
                            saveApplied();
                            system("PAUSE");
                            listAppliedGadget();
                            break;
                        case 3:
                            listAppliedGadget();
                            break;
                    }
                case 2:
                    listAppliedGadget();
                    break;
                default:
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                listAppliedGadget();
                break;
            }
        }
        case 4:
            listAppliedUser();
            break;  
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            adminHome();
    }
}

void displayDueLoans() {
    system("cls");
    int choice;
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t\tDUE LOANS\n";
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t\t[1] Due Money Loans "<<endl;
    cout << "\t\t\t\t\t\t[2] Due Gadget Loans "<<endl;
    cout << "\t\t\t\t\t\t[3] Back "<<endl;
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t\tSelect option: ";
    cin >> choice;
    switch(choice){
        case 1:
            displayDueMoneyLoans();
        case 2:
            displayDueGadgetLoans();
        case 3:
            adminHome();
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            adminHome();
    }   
        
}

void displayDueGadgetLoans(){
    system("cls");
    int tempAppliedLoan;
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t\tCLOSE DUE GADGET LOANS\n";
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\tFullname\tStatus\tTill Due\tDueDate\n";
    cout << "----------------------------------------------------------------------------------------------------------------------\n";
    bool Found = false;

    // Get the current date
    time_t now = time(0);
    tm *ltm = localtime(&now);

    for (int i = 0; i < countApplied; i++) {
        if (applied[i].appliedStatus == "Approved") {
            tm dueDate = applied[i].dueDate;
            // Calculate the difference in days
            time_t due_time = mktime(&dueDate);
            double seconds = difftime(due_time, now);
            int days = seconds / (60 * 60 * 24);

            if (days >= 0 && days <= 3) {
                Found = true;
                cout << "\t\t\t\t" << i + 1 << ".) " << applied[i].fname << "\t"  << applied[i].appliedStatus << "\t" << days << " Day(s) till due\t";
                cout << applied[i].dueDate.tm_year + 1900 << "-" << applied[i].dueDate.tm_mon + 1 << "-" << applied[i].dueDate.tm_mday << endl;
            }
        }
    }
    if (!Found){
        cout << "\t\t\t\t\t\tNo Due Loans Yet!" << endl;
        system("pause");
        adminHome();
    }
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t\t[1] Back\n";
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t\tSelect Option : ";
    cin >> choice;
    switch(choice){
        case 1:
            adminHome();
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            adminHome();
        break;
    }
}

void displayDueMoneyLoans(){
    system("cls");
    int tempAppliedMoneyLoan;
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t\tCLOSE DUE MONEY LOANS\n";
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\tFullname\tStatus\tTill Due\tDueDate\n";
    cout << "----------------------------------------------------------------------------------------------------------------------\n";
    bool Found = false;

    // Get the current date
    time_t now = time(0);
    tm *ltm = localtime(&now);

    for (int i = 0; i < countAppliedMoney; i++) {
        if (appliedMoney[i].appliedStatusMoney == "Approved") {
            tm dueDate = appliedMoney[i].dueDateMoney;
            // Calculate the difference in days
            time_t due_time = mktime(&dueDate);
            double seconds = difftime(due_time, now);
            int days = seconds / (60 * 60 * 24);

            if (days >= 0 && days <= 3) {
                Found = true;
                cout << "\t\t\t\t" << i + 1 << ".) " << appliedMoney[i].fnameMoney << "\t" << appliedMoney[i].loanTypeMoney << "\t" << appliedMoney[i].appliedStatusMoney << "\t" << days << " Day(s) till due\t";
                cout << applied[i].dueDate.tm_year + 1900 << "-" << appliedMoney[i].dueDateMoney.tm_mon + 1 << "-" << appliedMoney[i].dueDateMoney.tm_mday << endl;
            }
        }
    }
    if (!Found){
        cout << "\t\t\t\t\t\tNo Due Loans Yet!" << endl;
        system("pause");
        adminHome();
    }
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t\t[1] Back\n";
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t\tSelect Option : ";
    cin >> choice;
    switch(choice){
        case 1:
            adminHome();
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            adminHome();
        break;
    }
}   

void feedbackAdmin() {
    loadFeedbacks();
    system("cls");
    option = 0;
    int tempFeedback = 0;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tVIEW FEEDBACKS"<<endl;
    cout<<"========================================================================================================================\n";
    cout << "\t\t\t\tNo.\tUserID\tUserName\tAbout\tDate & Time"<<endl;
    for (int i = 0; i < countFeedbacks; i++){
        chk=0;
        chk=1;
        cout << "\t\t\t\t" << i + 1 << ". \t" << feedback[i].userIDFeed << "\t" << feedback[i].usernameFeed << "\t\t" << feedback[i].titleFeed << "\t" <<
        feedback[i].dateMadeFeed.tm_year + 1900 << "-"
        << setfill('0') << to_string(feedback[i].dateMadeFeed.tm_mon + 1) << "-"
        << setfill('0') << to_string(feedback[i].dateMadeFeed.tm_mday) << " "
        << setfill('0') << to_string(feedback[i].dateMadeFeed.tm_hour) << ":"
        << setfill('0') << to_string(feedback[i].dateMadeFeed.tm_min) << endl;
    }
    if (chk != 1){
        cout << "\t\t\t\t\t\tNo Feedback(s) Found!"<<endl;
        system("pause");
        adminHome();
    }
    cout<<"========================================================================================================================\n";
    cout << "\t\t\t\t\t\t[1] View more"<<endl;
    cout << "\t\t\t\t\t\t[2] Back"<<endl;
    cout<<"========================================================================================================================\n";
    cout << "\t\t\t\t\t\tSelect option: ";
    cin >> option;
    switch(option){
        case 1:
            system("cls");
            cout<<"========================================================================================================================\n";
            cout << "\t\t\t\t\tVIEW FEEDBACKS"<<endl;
            cout<<"========================================================================================================================\n";
            cout << "\t\t\t\t\t\tNo.\tUserID\tUserName\tAbout\tDate & Time"<<endl;
            for (int i = 0; i < countFeedbacks; i++){
                chk=0;
                chk=1;
                cout << "\t\t\t\t\t\t" << i + 1 << ". \t" << feedback[i].userIDFeed << "\t" << feedback[i].usernameFeed << "\t\t" << feedback[i].titleFeed << "\t" <<
                feedback[i].dateMadeFeed.tm_year + 1900 << "-"
                << setfill('0') << to_string(feedback[i].dateMadeFeed.tm_mon + 1) << "-"
                << setfill('0') << to_string(feedback[i].dateMadeFeed.tm_mday) << " "
                << setfill('0') << to_string(feedback[i].dateMadeFeed.tm_hour) << ":"
                << setfill('0') << to_string(feedback[i].dateMadeFeed.tm_min) << endl;
            }
            if (chk != 1){
                cout << "\t\t\t\t\t\tNo Feedback(s) Found!"<<endl;
                system("pause");
                adminHome();
            }
            cout<<"========================================================================================================================\n";
            cout << "\t\t\t\t\t\tSelect option: ";
            cin>>tempFeedback;
            tempFeedback--;
            if (tempFeedback >= 0 && tempFeedback < countFeedbacks) {
                cout<<"========================================================================================================================\n";
                cout << "\t\t\t\t\tSELECTED FEEDBACK"<<endl;
                cout<<"========================================================================================================================\n";
                for (int i = 0; i < countFeedbacks; i++){
                    cout << "\t\t\t\t\t\tFeedback No: " << countFeedbacks << endl;
                    cout << "\t\t\t\t\t\tFeedback Stars: " << feedback[i].starsFeed << endl;
                    cout << "\t\t\t\t\t\tDate & Time: " << feedback[i].dateMadeFeed.tm_year + 1900 << "-"
                    << setfill('0') << to_string(feedback[i].dateMadeFeed.tm_mon + 1) << "-"
                    << setfill('0') << to_string(feedback[i].dateMadeFeed.tm_mday) << " "
                    << setfill('0') << to_string(feedback[i].dateMadeFeed.tm_hour) << ":"
                    << setfill('0') << to_string(feedback[i].dateMadeFeed.tm_min) << endl;
                    cout << "\t\t\t\t\t\tUser ID: " << feedback[i].userIDFeed << endl;
                    cout << "\t\t\t\t\t\tUser Name: " << feedback[i].usernameFeed << endl;
                    cout << "\t\t\t\t\t\tAbout: " << feedback[i].titleFeed << endl;
                    cout << "\t\t\t\t\t\tDescription: " << feedback[i].descFeed << endl;
                    cout<<"========================================================================================================================\n";
                    cout << "\t\t\t\t\t\t[1] Back"<<endl;
                    cout<<"========================================================================================================================\n";
                    cout << "\t\t\t\t\t\tSelect option: ";
                    cin>>option;
                    switch(option){
                        case 1:
                            feedbackAdmin();
                            break;
                        default:
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "\t\t\t\t\t\tInvalid input!" << endl;
                            cout << "========================================================================================================================" << endl;
                            cout << "\t\t\t\t\t\tPress Enter to continue...";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            feedbackAdmin();
                            break;

                    }
                }
            }
        case 2:
            adminHome();
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            feedbackAdmin();
            break;
    }
}

void listAppliedMoney() {
    char x = 0;
    bool Found = false;
    loadAppliedMoney();
    system("cls");
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t\tAPPLIED USERS MONEY LOAN\n";
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t\t[1] Approved\n";
    cout << "\t\t\t\t\t\t[2] Rejected\n";
    cout << "\t\t\t\t\t\t[3] Pending\n";
    cout << "\t\t\t\t\t\t[4] Back\n";
    cout << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t\tSelect Option : ";
    int option;
    int choice;
    cin >> option;
    switch (option) {
        case 1:
        system("cls");
        loadAppliedMoney();
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\t\t\tAPPROVED USERS\n";
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\tFullname\tLoan Type\tStatus\t\n";
            cout << "------------------------------------------------------------------------------------------------------------------------\n";
            Found = false;
            for (int i = 0; i < countAppliedMoney; i++) {
                if (appliedMoney[i].appliedStatusMoney == "Approved") {
                    Found = true;
                    cout << "\t\t\t\t"<< i + 1 << ".) " << appliedMoney[i].fnameMoney << "\t" << appliedMoney[i].loanTypeMoney << "\t\t" << appliedMoney[i].appliedStatusMoney <<endl;
                } 
            }
            if (!Found) {
                cout<<"\t\t\t\t\t\tNo Approved Loans Found!"<<endl;
                system("PAUSE");
                listAppliedMoney();
                }
            
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\t\t\t[1] View More\n";
            cout << "\t\t\t\t\t\t[2] Back\n";
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\t\t\tSelect Option : ";
            cin>>choice;
            switch (choice) {
                case 1:
                system("cls");
                int tempAppliedLoan;
                cout << "========================================================================================================================" << endl;
                cout << "\t\t\t\t\t\tAPPROVED USERS\n";
                cout << "========================================================================================================================" << endl;
                cout << "\t\t\t\t\t\tFullname\t\tLoan Type\t\tStatus\t\n";
                cout << "------------------------------------------------------------------------------------------------------------------------\n";
                Found = false;
                for (int i = 0; i < countAppliedMoney; i++) {
                    if (appliedMoney[i].appliedStatusMoney == "Approved") {
                        Found = true;
                        cout << "\t\t\t\t" << i + 1 << ".) " << appliedMoney[i].fnameMoney << "\t" << appliedMoney[i].loanTypeMoney << "\t\t" << appliedMoney[i].appliedStatusMoney <<endl;
                    } 
                }
                if (!Found) {
                    cout<<"\t\t\t\t\t\tNo Approved Loans Found!"<<endl;
                    system("PAUSE");
                    listAppliedMoney();
                    }
                cout << "========================================================================================================================" << endl;
                cout << "\t\t\t\t\t\tSelect a number : ";
                cin >> tempAppliedLoan;
                tempAppliedLoan--;
                if (tempAppliedLoan >= 0 && tempAppliedLoan < countAppliedMoney) {
                    cout << "========================================================================================================================" << endl;
                    cout << "\t\t\t\t\t\tSELECTED USER\n";
                    cout << "========================================================================================================================" << endl;
                    cout << "\t\t\t\t\t\tFull Name: " << appliedMoney[tempAppliedLoan].fnameMoney << endl;
                    cout << "\t\t\t\t\t\tLoan Type: " << appliedMoney[tempAppliedLoan].loanTypeMoney << endl;
                    cout << "\t\t\t\t\t\tMonthly Payment: " << appliedMoney[tempAppliedLoan].monpayMoney << endl;
                    cout << "\t\t\t\t\t\tDown Payment: " << appliedMoney[tempAppliedLoan].interestMoney << endl;
                    cout << "\t\t\t\t\t\tStatus: " << appliedMoney[tempAppliedLoan].appliedStatusMoney << endl;
                    cout << "========================================================================================================================" << endl;
                    cout << "\t\t\t\t\t\t[1] Back\n";
                    cout << "========================================================================================================================" << endl;
                    cout << "\t\t\t\t\t\tSelect Option : ";
                    cin >> choice;
                    switch(choice){
                        case 1:
                            listAppliedMoney();
                            break;
                    }
                case 2:
                    listAppliedMoney();
                    break;
                default:
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout <<  "\t\t\t\t\t\tInvalid input!" << endl;
                cout << "========================================================================================================================" << endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                listAppliedMoney();
                break;
                } 
            }
        case 2:
        system("cls");
        loadAppliedMoney();
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\t\t\tREJECTED USERS\n";
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\tFullname\tLoan Type\tStatus\t\n";
            cout << "------------------------------------------------------------------------------------------------------------------------\n";
            Found = false;
            for (int i = 0; i < countAppliedMoney; i++) {
                if (appliedMoney[i].appliedStatusMoney == "Rejected") {
                    Found = true;
                    cout << "\t\t\t\t" << i + 1 << ".) " << appliedMoney[i].fnameMoney << "\t" << appliedMoney[i].loanTypeMoney << "\t\t" << appliedMoney[i].appliedStatusMoney <<endl;                
                } 
            }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo Rejected Loans Found!"<<endl;
                system("PAUSE");
                listAppliedMoney();
                }
            
            cout << "\t\t\t\t\t\t[1] View More\n";
            cout << "\t\t\t\t\t\t[2] Back\n";
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\t\t\tSelect Option : ";
            cin>>choice;
            switch (choice) {
                case 1:
                system("cls");
                int tempAppliedLoan;
                cout << "========================================================================================================================" << endl;
                cout << "\t\t\t\t\t\tREJECTED USERS\n";
                cout << "========================================================================================================================" << endl;
                cout << "\t\t\t\tFullname\tLoan Type\tStatus\t\n";
                cout << "------------------------------------------------------------------------------------------------------------------------\n";
                Found = false;
                for (int i = 0; i < countAppliedMoney; i++) {
                    if (appliedMoney[i].appliedStatusMoney == "Rejected") {
                        Found = true;
                        cout << "\t\t\t\t" <<i + 1 << ".) " << appliedMoney[i].fnameMoney << "\t" << appliedMoney[i].loanTypeMoney << "\t\t" << appliedMoney[i].appliedStatusMoney <<endl;                    
                    } 
                }
                if (!Found){
                    cout<<"\t\t\t\t\t\tNo Rejected Loans Found!"<<endl;
                    system("PAUSE");
                    listAppliedMoney();
                    }
                cout << "========================================================================================================================" << endl;
                cout << "\t\t\t\t\t\tSelect a number : ";
                cin >> tempAppliedLoan;
                tempAppliedLoan--;
                if (tempAppliedLoan >= 0 && tempAppliedLoan < countAppliedMoney) {
                    cout << "========================================================================================================================" << endl;
                    cout << "\t\t\t\t\t\tSELECTED USER\n";
                    cout << "========================================================================================================================" << endl;
                    cout << "\t\t\t\t\t\tFull Name: " << appliedMoney[tempAppliedLoan].fnameMoney << endl;
                    cout << "\t\t\t\t\t\tLoan Type: " << appliedMoney[tempAppliedLoan].loanTypeMoney << endl;
                    cout << "\t\t\t\t\t\tMonthly Payment: " << appliedMoney[tempAppliedLoan].monpayMoney << endl;
                    cout << "\t\t\t\t\t\tDown Payment: " << appliedMoney[tempAppliedLoan].interestMoney << endl;
                    cout << "\t\t\t\t\t\tStatus: " << appliedMoney[tempAppliedLoan].appliedStatusMoney << endl;
                    cout << "========================================================================================================================" << endl;
                    cout << "\t\t\t\t\t\t[1] Back\n";
                    cout << "========================================================================================================================" << endl;
                    cout << "\t\t\t\t\t\tSelect Option : ";
                    cin >> choice;
                    switch(choice){
                        case 1:
                            listAppliedMoney();
                            break;
                    }
                case 2:
                    listAppliedMoney();
                    break;
                default:
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout << "========================================================================================================================" << endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                listAppliedMoney();
                break;
                } 
            }
        case 3:
        system("cls");
        loadAppliedMoney();
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\t\t\tPENDING USERS\n";
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\tFullname\tLoan Type\tStatus\t\n";
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            Found = false;
            for (int i = 0; i < countAppliedMoney; i++) {
                    Found = true;
                    if (appliedMoney[i].appliedStatusMoney == "Pending") {
                        cout << "\t\t\t\t"<<i + 1 << ".) " << appliedMoney[i].fnameMoney << "\t" << appliedMoney[i].loanTypeMoney << "\t\t" << appliedMoney[i].appliedStatusMoney <<endl;                    
                    }
                }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo Pending Loans Found!"<<endl;
                system("PAUSE");
                listAppliedMoney();
            }
            
            cout << "\t\t\t\t\t\t[1] View More\n";
            cout << "\t\t\t\t\t\t[2] Back\n";
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\t\t\tSelect Option : ";
            cin>>choice;
            switch (choice) {
                case 1:
                system("cls");
                int tempAppliedLoan;
                cout << "========================================================================================================================" << endl;
                cout << "\t\t\t\t\t\tPENDING USERS\n";
                cout << "========================================================================================================================" << endl;
                cout << "\t\t\t\tFullname\tLoan Type\tStatus\t\n";
                cout << "========================================================================================================================" << endl;
                Found = false;
                for (int i = 0; i < countAppliedMoney; i++) {
                        if (appliedMoney[i].appliedStatusMoney == "Pending") {
                            Found = true;
                            cout << "\t\t\t\t" << i + 1 << ".) " << appliedMoney[i].fnameMoney << "\t" << appliedMoney[i].loanTypeMoney << "\t\t" << appliedMoney[i].appliedStatusMoney <<endl;                    
                        } 
                    }
                    if (!Found){
                            cout<<"\t\t\t\t\t\tNo Pending Loans Found!"<<endl;
                            system("PAUSE");
                            listAppliedMoney();
                        }
                cout << "========================================================================================================================" << endl;
                cout << "\t\t\t\t\t\tSelect a number : ";
                cin >> tempAppliedLoan;
                tempAppliedLoan--;
                if (tempAppliedLoan >= 0 && tempAppliedLoan < countAppliedMoney) {
                    cout << "========================================================================================================================" << endl;
                    cout << "\t\t\t\t\t\tSELECTED USER\n";
                    cout << "========================================================================================================================" << endl;
                    cout << "\t\t\t\t\t\tFull Name: " << appliedMoney[tempAppliedLoan].fnameMoney << endl;
                    cout << "\t\t\t\t\t\tLoan Type: " << appliedMoney[tempAppliedLoan].loanTypeMoney << endl;
                    cout << "\t\t\t\t\t\tMonthly Payment: " << appliedMoney[tempAppliedLoan].monpayMoney << endl;
                    cout << "\t\t\t\t\t\tDown Payment: " << appliedMoney[tempAppliedLoan].interestMoney << endl;
                    cout << "\t\t\t\t\t\tStatus: " << appliedMoney[tempAppliedLoan].appliedStatusMoney << endl;
                    cout << "========================================================================================================================" << endl;
                    cout << "\t\t\t\t\t\t[1] Approve\n";
                    cout << "\t\t\t\t\t\t[2] Reject\n";
                    cout << "\t\t\t\t\t\t[3] Back\n";
                    cout << "========================================================================================================================" << endl;
                    cout << "\t\t\t\t\t\tSelect Option : ";
                    cin >> choice;
                    switch(choice){
                        case 1:
                            appliedMoney[tempAppliedLoan].appliedStatusMoney = "Approved";
                            cout<<"\n\n\t\t\t\t\t\tPROCESSING";
                            x=219;
                        
                            for(int i=0; i<=30; i++){
                                Sleep(30);
                                cout<<x;
                            }
                            cout<<"\t\t\t\t\t\tProcess Compelete!"<<endl;
                            cout<<endl;
                            saveAppliedMoney();
                            cout << "========================================================================================================================" << endl;
                            system("PAUSE");
                            listAppliedMoney();
                            break;
                        case 2:
                            appliedMoney[tempAppliedLoan].appliedStatusMoney = "Rejected";
                            cout<<"\n\n\t\t\t\t\t\tPROCESSING";
                            x=219;
                        
                            for(int i=0; i<=30; i++){
                                Sleep(30);
                                cout<<x;
                            }
                            cout<<"\t\t\t\t\t\tProcess Compelete!"<<endl;
                            cout<<endl;
                            saveAppliedMoney();
                            cout << "========================================================================================================================" << endl;
                            system("PAUSE");
                            listAppliedMoney();
                            break;
                        case 3:
                            listAppliedMoney();
                            break;
                    }
                case 2:
                    listAppliedMoney();
                    break;
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout << "========================================================================================================================" << endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                listAppliedMoney();
                break;
            }
        }
        case 4:
            listAppliedUser();
            break;  
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout << "========================================================================================================================" << endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            listAppliedMoney();
            break; 
    }
}

void inventory(){
	system("cls");
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tPRODUCT INVENTORY"<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tType of Loan: "<<endl;
	cout<<"\t\t\t\t\t\t[1] Money Loan"<<endl;
	cout<<"\t\t\t\t\t\t[2] Gadget Loan"<<endl;
	cout<<"\t\t\t\t\t\t[3] Back"<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tSelect Option : ";
	cin>>option;
	cout<<"========================================================================================================================"<<endl;
	switch(option){
		case 1: moneyLoanInventory();break;
		case 2: gadgetLoanInventory();break;
		case 3: adminHome();break;
		default: 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			inventory();
	}
}
void moneyLoanInventory(){
    loadMoney();
	int index = -1;   
    float interest = 1;
    money[countMoney].moneyPrice = 1;
	system("cls");
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tMoney\t\tInterest\tQuantity"<<endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
	for(int i=0; i<countMoney; i++){
		chk=0;
		if(countMoney != 0){
			chk=1;
			cout<<"\t\t\t\t\t["<<i+1<<"] \t"<<money[i].moneyPrice<<" pesos\t"<<money[i].interest<<" %\t"<<money[i].quantityMoney<<endl;
		}
	}
	if (chk != 1){
		cout<<"\t\t\t\t\t\tNo Item Found!"<<endl;
	}
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\t[1] Add Money"<<endl;
	cout<<"\t\t\t\t\t\t[2] Update Money"<<endl;
	cout<<"\t\t\t\t\t\t[3] Remove Money"<<endl;
	cout<<"\t\t\t\t\t\t[4] Back"<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tSelect Option : ";
	cin>>option;
	cout<<"========================================================================================================================"<<endl;
	switch(option){
		case 1: 
            system("cls");
            cout<<"\t\t\t\t\t\tADD MONEY"<<endl;
			cout<<"========================================================================================================================"<<endl;
			cout<<"\t\t\t\t\t\tAdd price : ";
            cin>>money[countMoney].moneyPrice;
            cout<<"\t\t\t\t\t\tAdd Interest[will turn into percentage] : ";
			cin>>interest;
            cout<<"\t\t\t\t\t\tQuantity : ";
			cin>>money[countMoney].quantityMoney;
            interest = interest / 100;
            money[countMoney].interest = interest;
			countMoney++;
			saveMoney();
			if(countMoney > 0){
				cout<<endl<<"\t\t\t\t\t\tAdded Successfully!"<<endl;
				cout<<"========================================================================================================================"<<endl;
				system("pause");
			}else if (countMoney <= 0){
				cout<<endl<<"\t\t\t\t\t\tError adding new items!"<<endl;
				cout<<"========================================================================================================================"<<endl;
				system("pause");
			}
			moneyLoanInventory(); 
		case 2: 
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\t\tUPDATE"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\t\tMoney\t\tInterest\tQuantity"<<endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            for(int i=0; i<countMoney; i++){
                chk=0;
                if(countMoney != 0){
                    chk=1;
                    cout<<"\t\t\t\t\t\t"<<i+1<<".) "<<money[i].moneyPrice<<" pesos\t"<<money[i].interest<<" %\t"<<money[i].quantityMoney<<endl;
                }
            }
            if (chk != 1){
                cout<<"\t\t\t\t\t\tNo Item Found!"<<endl;
            }
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\t\t[1] Update Money "<<endl;
            cout<<"\t\t\t\t\t\t[2] Update Interest"<<endl;
            cout<<"\t\t\t\t\t\t[3] Update Quantity"<<endl;
            cout<<"\t\t\t\t\t\t[4] Back"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\t\tSelect option";
            cin>>option;
            switch(option){
                case 1:
                    system("cls");
                    cout<<"========================================================================================================================"<<endl;
                    cout<<"\t\t\t\t\t\tUPDATE MONEY"<<endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout<<"\t\t\t\t\t\tMoney\t\tInterest\tQuantity"<<endl;
                    cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                    for(int i=0; i<countMoney; i++){
                        chk=0;
                        if(countMoney != 0){
                            chk=1;
                            cout<<"\t\t\t\t\t\t"<<i+1<<".) "<<money[i].moneyPrice<<" pesos\t"<<money[i].interest<<" %\t"<<money[i].quantityMoney<<endl;
                        }
                    }
                    if (chk != 1){
                        cout<<"\t\t\t\t\t\tNo Item Found!"<<endl;
                    }
                    cout<<"========================================================================================================================"<<endl; 
                    cout<<"\t\t\t\t\t\tEnter number to be updated: ";	
                    cin>>num;
                    cout<<"========================================================================================================================"<<endl;
                    for (int i = 0; i<countMoney; i++){
                        if (i + 1 == num){
                            index = i;
                            break;
                        }
                    }
                    if (index != -1){
                        cout << "\t\t\t\t\t\tEnter updated money: ";
                        cin>>money[index].moneyPrice;
                        cout<<endl<<"\t\t\t\t\t\tRecord updated successfully!"<<endl;
                        cout<<"========================================================================================================================"<<endl; 
                        system("pause");
                        saveMoney();
                        moneyLoanInventory();
                    }else{
                        cout<<"\t\t\t\t\t\tRecord not found!" << endl;
                        cout<<"========================================================================================================================"<<endl; 
                        system("pause");
                        moneyLoanInventory();
                    } 
                    break;
                case 2:
                    system("cls");
                    cout<<"========================================================================================================================"<<endl;
                    cout<<"\t\t\t\t\t\tUPDATE INTEREST"<<endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout<<"\t\t\t\t\t\tMoney\t\tInterest\tQuantity"<<endl;
                    cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                    for(int i=0; i<countMoney; i++){
                        chk=0;
                        if(countMoney != 0){
                            chk=1;
                            cout<<"\t\t\t\t\t\t"<<i+1<<".) "<<money[i].moneyPrice<<" pesos\t"<<money[i].interest<<" %\t"<<money[i].quantityMoney<<endl;
                        }
                    }
                    if (chk != 1){
                        cout<<"\t\t\t\t\t\tNo Item Found!"<<endl;
                    }
                    cout<<"========================================================================================================================"<<endl; 
                    cout<<"\t\t\t\t\t\tEnter number to be updated: ";	
                    cin>>num;
                    cout<<"========================================================================================================================"<<endl;
                    for (int i = 0; i<countMoney; i++){
                        if (i + 1 == num){
                            index = i;
                            break;
                        }
                    }
                    if (index != -1){
                        cout << "\t\t\t\t\t\tEnter updated interest: ";
                        cin>>money[index].interest;
                        interest = money[index].interest / 100;
                        money[index].interest = interest;
                        cout<<endl<<"\t\t\t\t\t\tRecord updated successfully!"<<endl;
                        cout<<"========================================================================================================================"<<endl; 
                        system("pause");
                        saveMoney();
                        moneyLoanInventory();
                    }else{
                        cout<<"\t\t\t\t\t\tRecord not found!" << endl;
                        cout<<"========================================================================================================================"<<endl; 
                        system("pause");
                        moneyLoanInventory();
                    } 
                    break;
                case 3:
                    system("cls");
                    cout<<"========================================================================================================================"<<endl;
                    cout<<"\t\t\t\t\t\tUPDATE QUANTITY"<<endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout<<"\t\t\t\t\t\tMoney\t\tInterest\tQuantity"<<endl;
                    cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                    for(int i=0; i<countMoney; i++){
                        chk=0;
                        if(countMoney != 0){
                            chk=1;
                            cout<<"\t\t\t\t\t\t"<<i+1<<".) "<<money[i].moneyPrice<<" pesos\t"<<money[i].interest<<" %\t"<<money[i].quantityMoney<<endl;
                        }
                    }
                    if (chk != 1){
                        cout<<"\t\t\t\t\t\tNo Item Found!"<<endl;
                    }
                    cout<<"========================================================================================================================"<<endl; 
                    cout<<"\t\t\t\t\t\tEnter number to be updated: ";	
                    cin>>num;
                    cout<<"========================================================================================================================"<<endl;
                    for (int i = 0; i<countMoney; i++){
                        if (i + 1 == num){
                            index = i;
                            break;
                        }
                    }
                    if (index != -1){
                        cout << "\t\t\t\t\t\tEnter updated quantity: ";
                        cin>>money[index].quantityMoney;
                        cout<<endl<<"\t\t\t\t\t\tRecord updated successfully!"<<endl;
                        cout<<"========================================================================================================================"<<endl; 
                        system("pause");
                        saveMoney();
                        moneyLoanInventory();
                    }else{
                        cout<<"\t\t\t\t\t\tRecord not found!" << endl;
                        cout<<"========================================================================================================================"<<endl; 
                        system("pause");
                        moneyLoanInventory();
                    } 
                    break;
                case 4:
                    moneyLoanInventory();break;    
                default: 
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "\t\t\t\t\t\tInvalid input!" << endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tPress Enter to continue...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    moneyLoanInventory();
                }
		case 3: cout<<"\t\t\t\t\t\tREMOVE MONEY"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\t\tMoney\t\tInterest\tQuantity"<<endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                for(int i=0; i<countMoney; i++){
                    chk=0;
                    if(countMoney != 0){
                        chk=1;
                        cout<<"\t\t\t\t\t\t"<<i+1<<".) "<<money[i].moneyPrice<<" pesos\t"<<money[i].interest<<" %\t"<<money[i].quantityMoney<<endl;
                    }
                }
                if (chk != 1){
                    cout<<"\t\t\t\t\t\tNo Item Found!"<<endl;
                }
			cout<<"========================================================================================================================"<<endl; 
			cout<<"\t\t\t\t\t\tEnter Number to be deleted : ";
			cin>>num;  
			cout<<"========================================================================================================================"<<endl;
			for (int i = 0; i < countMoney; i++){
				if (i + 1 == num){
					index = i;
					break;
				}
			}
			if (index != -1){
				for (int i = index; i<countMoney - 1; i++){
					money[i] = money[i + 1];
				}
				countMoney--;
				cout<<endl<<"\t\t\t\t\t\tItem deleted successfully!"<<endl;
				cout<<"========================================================================================================================"<<endl; 
				system("pause");
				saveMoney();
				moneyLoanInventory();
			}else{
				cout<<endl<<"\t\t\t\t\t\tRecord not found!" << endl;
				cout<<"========================================================================================================================"<<endl; 
				system("pause");
				system("cls");
				moneyLoanInventory();
			}
			break;
		case 4: inventory();break;
		default: 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			moneyLoanInventory();
	}
}
void gadgetLoanInventory(){
	int num=0;
	int index = -1;   
	system("cls");
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tGADGET INVENTORY"<<endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"\t\t\t\t\t\tList of Brand(s) Available:"<<endl;
	for(int i=0; i<countGadgetCateg; i++){
		chk=0;
		if(countGadgetCateg != 0){
			chk=1;
			cout<<"\t\t\t\t\t\t"<<i+1<<".) "<<brand[i].brandName<<endl;
		}
	}
	if (chk != 1){
		cout<<"\t\t\t\t\t\tNo Item Found!"<<endl;
	}
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\t[1] Add Brand"<<endl;
	cout<<"\t\t\t\t\t\t[2] Update Brand"<<endl;
	cout<<"\t\t\t\t\t\t[3] Remove Brand"<<endl;
	cout<<"\t\t\t\t\t\t[4] View Products"<<endl;
	cout<<"\t\t\t\t\t\t[5] Back"<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tSelect Option : ";
	cin>>option;
	cout<<"========================================================================================================================"<<endl;
	switch(option){
		case 1: 
            system("cls");
			cout<<"\t\t\t\t\t\tADD CATEGORY"<<endl;
			cout<<"========================================================================================================================"<<endl;
            cin.ignore(); 
			cout<<"\t\t\t\t\t\tAdd Name of the brand : ";
			getline(cin, brand[countGadgetCateg].brandName);
			countGadgetCateg++;
			saveBrandName();
			if(countGadgetCateg > 0){
				cout<<"\t\t\t\t\t\tAdded Successfully!"<<endl;
				cout<<"========================================================================================================================"<<endl;
			}else if (countGadgetCateg <= 0){
				cout<<"\t\t\t\t\t\tError adding new items!"<<endl;
				cout<<"========================================================================================================================"<<endl;
			}
			system("pause");
			gadgetLoanInventory(); 
			break;
		case 2: 
            system("cls");
            cout<<"\t\t\t\t\t\tUPDATE CATEGORY"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\t\tGADGET INVENTORY"<<endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            for(int i=0; i<countGadgetCateg; i++){
                chk=0;
                if(countGadgetCateg != 0){
                    chk=1;
                    cout<<"\t\t\t\t\t\t["<<i+1<<"] "<<brand[i].brandName<<endl;
                }
            }
            if (chk != 1){
                cout<<"\t\t\t\t\t\tNo Item Found!"<<endl;
            }
			cout<<"========================================================================================================================"<<endl; 
			cout<<"\t\t\t\t\t\tEnter number to be updated: ";	
			cin>>num;
			cout<<"========================================================================================================================"<<endl;
			for (int i = 0; i<countGadgetCateg; i++){
				if (i + 1 == num){
					index = i;
					break;
				}
			}
			if (index != -1){
				cout << "\t\t\t\t\t\tEnter updated category: ";
				cin>>brand[index].brandName;
				cout<<endl<<"\t\t\t\t\t\tRecord updated successfully!"<<endl;
				cout<<"========================================================================================================================"<<endl; 
				system("pause");
				saveMoney();
				gadgetLoanInventory();
			}else{
				cout<<endl<<"\t\t\t\t\t\tRecord not found!" << endl;
				cout<<"========================================================================================================================"<<endl; 
				system("pause");
				system("cls");
				gadgetLoanInventory();
			} 
			break;
		case 3: 
            system("cls");
            cout<<"\\t\t\t\t\t\tREMOVE BRAND"<<endl;
			cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\t\tGADGET INVENTORY"<<endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            for(int i=0; i<countGadgetCateg; i++){
                chk=0;
                if(countGadgetCateg != 0){
                    chk=1;
                    cout<<"\t\t\t\t\t\t["<<i+1<<"] "<<brand[i].brandName<<endl;
                }
            }
            if (chk != 1){
                cout<<"\t\t\t\t\t\tNo Item Found!"<<endl;
            }
			cout<<"========================================================================================================================"<<endl; 
			cout<<"\t\t\t\t\t\tEnter number to be deleted : ";
			cin>>num;  
			cout<<"========================================================================================================================"<<endl;
			for (int i = 0; i < countGadgetCateg; i++){
				if (i + 1 == num){
					index = i;
					break;
				}
			}
			if (index != -1){
				for (int i = index; i<countGadgetCateg - 1; i++){
					brand[i] = brand[i + 1];
				}
				countGadgetCateg--;
				cout<<endl<<"\t\t\t\t\t\tItem deleted successfully!"<<endl;
				cout<<"========================================================================================================================"<<endl; 
				system("pause");
				saveBrandName();
				gadgetLoanInventory();
			}else{
				cout<<"\t\t\t\t\t\tRecord not found!" << endl;
				cout<<"========================================================================================================================"<<endl; 
				system("cls");
				gadgetLoanInventory();
			}
			break;
		case 4: showAllProduct();break;
		case 5: inventory();break;
		default: 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			gadgetLoanInventory();
	}
}

void showAllProduct() {
    int option;
	int opt;
    loadProduct();
    system("cls");
    cout << "\t\t\t\t\t\tSHOW ALL PRODUCTS" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\tNo." << "\tBrand" << "\tUnit" << "\tPrice" << "\tQuantity" << endl;
   cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
		for (int i = 0; i < countProducts; i++) {
			cout << "\t\t\t\t" << i + 1 << "\t" << product[i].brand << "\t" << product[i].unit << "\t" << product[i].price << "\t" << product[i].quantityProduct<< endl;
		}
    if (countProducts == 0) {
        cout << "\t\t\t\t\t\tNo Items Found!" << endl;
    }
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t[1] Add Products" << endl;
    cout << "\t\t\t\t\t\t[2] Update Products" << endl;
    cout << "\t\t\t\t\t\t[3] Remove Products" << endl;
    cout << "\t\t\t\t\t\t[4] View Products" << endl;
    cout << "\t\t\t\t\t\t[5] Back" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tSelect Option: ";
    cin >> option;
    cout<<"========================================================================================================================"<<endl;

    switch (option) {
        case 1: addProduct(); break;
        case 2: updateProduct(); break;
        case 3: removeProduct(); break;
        case 4: system("cls");
			cout<<"========================================================================================================================"<<endl;
			cout << "\t\t\t\t\t\tCHOOSE WHAT TYPE TO SHOW" << endl;
			cout<<"========================================================================================================================"<<endl;
			cout << "\t\t\t\t\t\t[1] Show Product by Unit Name" << endl;
			cout << "\t\t\t\t\t\t[2] Show Product by Brand" << endl;
			cout << "\t\t\t\t\t\t[3] Back" << endl;
			cout<<"========================================================================================================================"<<endl;
			cout << "\t\t\t\t\t\tSelect Option: ";
			cin >> opt;
			cout<<"========================================================================================================================"<<endl;
			switch (opt) {
				case 1:
					viewProducts(); break;
				case 2:
					showByCategory(); break;
				case 3:
					showAllProduct(); break;
				default: 
					cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "\t\t\t\t\t\tInvalid input!" << endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tPress Enter to continue...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
					showAllProduct();
			}
			
        case 5: gadgetLoanInventory(); break;
        default: 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            showAllProduct();
    }
}

void addProduct() {
    system("cls");
    cout << "\t\t\t\t\t\tADD PRODUCTS" << endl;
    cout<<"========================================================================================================================"<<endl;
    cin.ignore();
    cout << "\t\t\t\t\t\tBrand: ";
    getline(cin, product[countProducts].brand);
    for (int i = 0; i < countGadgetCateg; i++) {
        chk = 0;
        if (product[countProducts].brand == brand[i].brandName) {
            chk = 1;
            cout << "\t\t\t\t\t\tUnit: ";
            getline(cin, product[countProducts].unit);
            cout << "\t\t\t\t\t\tDisplay: ";
            getline(cin, product[countProducts].display);
            cout << "\t\t\t\t\t\tBody: ";
            getline(cin, product[countProducts].body);
            cout << "\t\t\t\t\t\tVariant: ";
            getline(cin, product[countProducts].variant);
            cout << "\t\t\t\t\t\tCamera: ";
            getline(cin, product[countProducts].camera);
            cout << "\t\t\t\t\t\tBattery: ";
            getline(cin, product[countProducts].battery);
            cout << "\t\t\t\t\t\tProcessor: ";
            getline(cin, product[countProducts].processor);
            cout << "\t\t\t\t\t\tPrice: ";
            cin >> product[countProducts].price;
            cout << "\t\t\t\t\t\tQuantity: ";
            cin >> product[countProducts].quantityProduct;
            countProducts++;
            saveProduct();
            if (countProducts > 0) {
                cout << "\t\t\t\t\t\tAdded Successfully!" << endl;
            } else {
                cout << "\t\t\t\t\t\tError adding new items!" << endl;
            }
            system("pause");
            showAllProduct();
            return;
        }
    }
    if (chk != 1) {
        cout << "\t\t\t\t\t\tThe brand is not existing!!" << endl;
        system("pause");
        showAllProduct();
    }
}

void updateProduct() {
	system("cls");
    int option, num, index = -1;
    cout << "\t\t\t\t\t\tUPDATE PRODUCTS" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t[1] Brand" << endl;
    cout << "\t\t\t\t\t\t[2] Unit" << endl;
    cout << "\t\t\t\t\t\t[3] Display" << endl;
    cout << "\t\t\t\t\t\t[4] Body" << endl;
    cout << "\t\t\t\t\t\t[5] Variant" << endl;
    cout << "\t\t\t\t\t\t[6] Camera" << endl;
    cout << "\t\t\t\t\t\t[7] Battery" << endl;
    cout << "\t\t\t\t\t\t[8] Processor" << endl;
    cout << "\t\t\t\t\t\t[9] Price" << endl;
    cout << "\t\t\t\t\t\t[10] Quantity" << endl;
    cout << "\t\t\t\t\t\tEnter spec to be updated: ";
    cin >> option;
    cout<<"========================================================================================================================"<<endl;
	cout << "\t\t\t\t\t\tPRODUCTS" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\tNo." << "\tBrand" << "\tUnit" << "\tPrice" << "\tQuantity" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
    for (int i = 0; i < countProducts; i++) {
        cout << "\t\t\t\t" << i + 1 << "\t" << product[i].brand << "\t" << product[i].unit << "\t" << product[i].price << "\t" << product[i].quantityProduct<< endl;
    }
    if (countProducts == 0) {
        cout << "\t\t\t\t\t\tNo Items Found!" << endl;
    }
	cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tEnter number of product to be updated: ";
    cin >> num;
    for (int i = 0; i < countProducts; i++) {
        if (i + 1 == num) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        cin.ignore();
        switch (option) {
            case 1: 
                cout << "\t\t\t\t\t\tEnter updated Brand: ";
                getline(cin, product[index].brand);
                cout << "\t\t\t\t\t\tSucessfully updated brand!";
                system("cls");
                showAllProduct();
            case 2: 
                cout << "\t\t\t\t\t\tEnter updated Unit: ";
                getline(cin, product[index].unit);
                cout << "\t\t\t\t\t\tSucessfully updated Unit!";
                system("cls");
                showAllProduct();
            case 3: 
                cout << "\t\t\t\t\t\tEnter updated Display: ";
                getline(cin, product[index].display);
                cout << "\t\t\t\t\t\tSucessfully updated Display!";
                system("cls");
                showAllProduct();
            case 4: 
                cout << "\t\t\t\t\t\tEnter updated Body: ";
                getline(cin, product[index].body);
                cout << "\t\t\t\t\t\tSucessfully updated Body!";
                system("cls");
                showAllProduct();
            case 5: 
                cout << "\t\t\t\t\t\tEnter updated Variant: ";
                getline(cin, product[index].variant);
                cout << "\t\t\t\t\t\tSucessfully updated Variant!";
                system("cls");
                showAllProduct();
            case 6: 
                cout << "\t\t\t\t\t\tEnter updated Camera: ";
                getline(cin, product[index].camera);
                cout << "\t\t\t\t\t\tSucessfully updated Camera!";
                system("cls");
                showAllProduct();
            case 7: 
                cout << "\t\t\t\t\t\tEnter updated Battery: ";
                getline(cin, product[index].battery);
                cout << "\t\t\t\t\t\tSucessfully updated Battery!";
                system("cls");
                showAllProduct();
            case 8: 
                cout << "\t\t\t\t\t\tEnter updated Processor: ";
                getline(cin, product[index].processor);
                cout << "\t\t\t\t\t\tSucessfully updated Processor!";
                system("cls");
                showAllProduct();
            case 9: 
                cout << "\t\t\t\t\t\tEnter updated Price: ";
                cin >> product[index].price;
                cout << "\t\t\t\t\t\tSucessfully updated Price!";
                system("cls");
                showAllProduct();
            case 10: 
                cout << "\t\t\t\t\t\tEnter updated Quantity: ";
                cin >> product[index].quantityProduct;
                cout << "\t\t\t\t\t\tSucessfully updated Quantity!";
                system("cls");
                showAllProduct();
            default:
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                showAllProduct();
                return;
        }
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tRecord updated successfully!" << endl;
        cout<<"========================================================================================================================"<<endl;
        saveProduct();
        viewProducts();
    } else {
        cout << "\t\t\t\t\t\tRecord not found!" << endl;
        cout<<"========================================================================================================================"<<endl;
        system("cls");
        viewProducts();
    }
}

void removeProduct() {
	system("cls");
    int num, index = -1;
	cout << "\t\t\t\t\t\tPRODUCTS" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\tNo." << "\tBrand" << "\tUnit" << "\tPrice" << "\tQuantity" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
    for (int i = 0; i < countProducts; i++) {
        cout << "\t\t\t\t" << i + 1 << "\t" << product[i].brand << "\t" << product[i].unit << "\t" << product[i].price << "\t" << product[i].quantityProduct<< endl;
    }
    if (countProducts == 0) {
        cout << "\t\t\t\t\t\tNo Items Found!" << endl;
    }
	cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tREMOVE PRODUCT" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tEnter Number to be deleted: ";
    cin >> num;
    cout<<"========================================================================================================================"<<endl;
    for (int i = 0; i < countProducts; i++) {
        if (i + 1 == num) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < countProducts - 1; i++) {
            product[i] = product[i + 1];
        }
        countProducts--;
        cout << "\t\t\t\t\t\tItem deleted successfully!" << endl;
        cout<<"========================================================================================================================"<<endl;
        system("pause");
        saveProduct();
        showAllProduct();
    } else {
        cout << "\t\t\t\t\t\tRecord not found!" << endl;
        cout<<"========================================================================================================================"<<endl;
        system("cls");
        showAllProduct();
    }
}

void viewProducts() {
	system("cls");
    string viewProduct;
    int option, chk = 0;
    cin.ignore();
    cout << "\t\t\t\t\t\tVIEW PRODUCT BY UNIT NAME" << endl;
    cout<<"========================================================================================================================"<<endl;
	cout << "\t\t\t\t\t\tAvailable Products:" << endl;
	for (int i = 0; i < countProducts; i++) {
        if (countProducts != 0) {
            cout << "\t\t\t\t\t\t[" << i + 1 << "] " << product[i].unit << endl;
        }
    }

    if (countProducts == 0) {
        cout << "\t\t\t\t\t\tNo Item Found!" << endl;
    }


    cout << "\t\t\t\t\t\tEnter the unit name: ";
    getline(cin, viewProduct);
    cout<<"========================================================================================================================"<<endl;
    for (int i = 0; i < countProducts; i++) {
        if (viewProduct == product[i].unit) {
            chk = 1;
            cout << "\t\t\t\t\t\tBrand : " << product[i].brand << endl;
            cout << "\t\t\t\t\t\tUnit : " << product[i].unit << endl;
            cout << "\t\t\t\t\t\tDisplay : " << product[i].display << endl;
            cout << "\t\t\t\t\t\tBody : " << product[i].body << endl;
            cout << "\t\t\t\t\t\tVariant : " << product[i].variant << endl;
            cout << "\t\t\t\t\t\tCamera : " << product[i].camera << endl;
            cout << "\t\t\t\t\t\tBattery : " << product[i].battery << endl;
            cout << "\t\t\t\t\t\tProcessor : " << product[i].processor << endl;
            cout << "\t\t\t\t\t\tPrice : " << product[i].price << endl;
            cout << "\t\t\t\t\t\tQuantity : " << product[i].quantityProduct << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\t[1] Back" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tSelect option: ";
            cin >> option;
            cout<<"========================================================================================================================"<<endl;
            if (option == 1) {showAllProduct(); return;}
            
        }
    }
    if (chk != 1) {
        cout << "\t\t\t\t\t\tNo Items Found!" << endl;
        system("pause");
        showAllProduct();
    }
}

void showByCategory() {
    int tempProducts;
    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tSHOW PRODUCT BY BRAND" << endl;
    cout<<"========================================================================================================================"<<endl;

    // Display the list of brands
    for (int i = 0; i < countGadgetCateg; i++) {
        if (countGadgetCateg != 0) {
            cout << "\t\t\t\t\t\t[" << i + 1 << "] " << brand[i].brandName << endl;
        }
    }

    if (countGadgetCateg == 0) {
        cout << "\t\t\t\t\t\tNo Item Found!" << endl;
    }

    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tSelect Number of Brand: ";
    cin >> tempProducts;
    tempProducts = tempProducts - 1;

    if (tempProducts >= 0 && tempProducts < countGadgetCateg) {
        clearscreen();
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\t" << brand[tempProducts].brandName << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t" << "No." << "\t" << "Brand" << "\t" << "Unit" << "\t" << "Price" << "\t" << "Quantity"<< endl;
       cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;

        bool productFound = false;
        for (int i = 0; i < countProducts; i++) {
            if (product[i].brand == brand[tempProducts].brandName) {
                productFound = true;
                cout << "\t\t\t\t" << i + 1 << "\t" << product[i].brand << "\t" << product[i].unit << "\t" << product[i].price << "\t" << product[i].quantityProduct<< endl;
            }
        }

        if (!productFound) {
            cout << "\t\t\t\t\t\tNo Product Found!" << endl;
        }
    } else {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\t\t\t\t\t\tInvalid input!" << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t[1] Back" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tSelect Option : ";
    int option;
    cin >> option;
    cout<<"========================================================================================================================"<<endl;

    switch (option) {
        case 1:
            showAllProduct();
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            showAllProduct();
    }
}
void transactionHistory(){
    loadTransactions();
	system("cls");
    int tempTransaction =0;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tTRANSACTION HISTORY"<<endl;
	cout<<"========================================================================================================================"<<endl;
    cout<<"\t\t\t\tNo.\tLoan Type\tAmount\t\tStatus"<<endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
    chk =0;
    for (int i = 0; i < countTransactions; i++){
        chk=1;
        cout << "\t\t\t\t" << i + 1 << ". \t" << transaction[i].loanTypeTrans << "\t" << transaction[i].priceTrans << "\t" << transaction[i].statusTrans << endl;
    }
    if (chk!= 1){
        cout<<"\t\t\t\t\t\tNo Transactions made yet."<<endl;

    }
	cout<<"\t\t\t\t\t\t[1] View More"<<endl;
    cout<<"\t\t\t\t\t\t[2] Back"<<endl;
    cout<<"========================================================================================================================"<<endl;
    cout<<"\t\t\t\t\t\tSelect Option: ";
	cin>>option;
	switch(option){
        case 1:
        system("cls");
        cout<<"========================================================================================================================"<<endl;
        cout<<"\\t\t\t\t\t\tTRANSACTION HISTORY"<<endl;
        cout<<"========================================================================================================================"<<endl;
        cout<<"\t\t\t\tNo.\tLoan Type\tAmount\t\tStatus"<<endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
        chk =0;
        for (int i = 0; i < countTransactions; i++){
            chk=1;
            cout << "\t\t\t\t" <<i + 1 << ". \t" << transaction[i].loanTypeTrans << "\t" << transaction[i].priceTrans << "\t" << transaction[i].statusTrans << endl;
        }
        if (chk!= 1){
            cout<<"\t\t\t\t\t\tNo Transactions made yet."<<endl;

        }
        cout<<"========================================================================================================================"<<endl;
        cout<<"\t\t\t\t\t\tSelect number: ";
        cin>>tempTransaction;
            tempTransaction--;
            if (tempTransaction >= 0 && tempTransaction < countTransactions) {
                system("cls");
                cout<<"\t\t\t\t\t\tSELECTED TRANSACTION"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\t\tUser ID: "<< transaction[tempTransaction].userIDTrans << endl;
                cout<<"\t\t\t\t\t\tName: "<< transaction[tempTransaction].fnameTrans << endl;
                cout<<"\t\t\t\t\t\tLoan Type: "<< transaction[tempTransaction].loanTypeTrans << endl;
                cout<<"\t\t\t\t\t\tMonths to pay: "<< transaction[tempTransaction].monthsToPayTrans << " Month(s)" << endl;
                cout<<"\t\t\t\t\t\tMonths Paid: "<< transaction[tempTransaction].monthsPaidTrans << " Month(s)" << endl;
                cout<<"\t\t\t\t\t\tTransacation Date & Time: " << transaction[tempTransaction].dateMade.tm_year + 1900 << "-" // year is since 1900
                << "  " << setfill('0') << transaction[tempTransaction].dateMade.tm_mon + 1 << "-" // month (0-based)
                << "  " << setfill('0') << transaction[tempTransaction].dateMade.tm_mday << " " // day of the month
                << "  " << setfill('0') << transaction[tempTransaction].dateMade.tm_hour << ":" // hour (24-hour format)
                << "  " << setfill('0') << transaction[tempTransaction].dateMade.tm_min << endl;
                cout<<"\t\t\t\t\t\tTransaction Type: "<< transaction[tempTransaction].typeTrans << endl;
                cout<<"\t\t\t\t\t\tTransacation Status: "<< transaction[tempTransaction].statusTrans << endl;
                cout << "\t\t\t\t\t\t[1] Back" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tSelect Option : ";
                cin >> option;
                switch (option) {
                    case 1:
                        transactionHistory();
                        break;
                    default:
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "\t\t\t\t\t\tInvalid input!" << endl;
                        cout<<"========================================================================================================================"<<endl;
                        cout << "\t\t\t\t\t\tPress Enter to continue...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        transactionHistory();
                }
            }else {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                transactionHistory();
            }
            
            break;
		case 2: 
            adminHome();
            break;
		default: 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			transactionHistory();
			break;
 	}
}

void logout(){
	cout<<"\t\t\t\t\t\tDo you want to Logout?"<<endl;
	cout<<"\t\t\t\t\t\t[1] Yes";
	cout<<"\t\t[2] No : ";
	cin>>option;
	cout<<"========================================================================================================================"<<endl;
	if (option == 1){
		cout<<"\n\n\t\t\t\t\t\tLoging out ";
   		char x=219;
     
    	for(int i=0; i<=30; i++){
    		Sleep(30);
     		cout<<x;
		}
		cout<<endl;
		main();
	}else {
		cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\t\t\t\t\t\tInvalid input!" << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		adminHome();
	}
}
//user
void userHome(){
	system("cls");
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tUSER HOME"<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\t[1] View Loan Categories"<<endl;
	cout<<"\t\t\t\t\t\t[2] View Account"<<endl;
	cout<<"\t\t\t\t\t\t[3] Pay"<<endl;
	cout<<"\t\t\t\t\t\t[4] Transaction history"<<endl;
    cout<<"\t\t\t\t\t\t[5] Send a Feedback"<<endl;
	cout<<"\t\t\t\t\t\t[6] Logout"<<endl;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tSelect option : ";
	cin>>option;
	switch(option){
		case 1: userViewProducts(); break;
		case 2: viewAccountPage();break;
		case 3: userPayment();break;
		case 4: transactionHistoryUser();break;
		case 5: feedbackUser();break;
        case 6: logout();break;
		default: 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			userHome();
			break;
	}
}

void feedbackUser() {
    loadFeedbacks();
    loadUser();
    system("cls");
    string tempTitle, tempDesc;
    int option;
    char choice, anotherchoice, anotherchoice1;
    bool foundUser = false;

    for (int i = 0; i < countUser; i++) {
        if (user[i].username == userLog) {
            foundUser = true;
            int currentUserID = user[i].userid;

            feedback[countFeedbacks].userIDFeed = currentUserID;
            feedback[countFeedbacks].usernameFeed = user[i].username;
        }
    }

    if (!foundUser) {
        cout << "\t\t\t\t\t\tUser not found." << endl;
        return;
    }

    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tSEND A FEEDBACK" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tStar Rating" << endl;
    cout << "\t\t\t\t[1] * * * * * - Very Satisfactory" << endl;
    cout << "\t\t\t\t[2] * * * * o - Satisfactory" << endl;
    cout << "\t\t\t\t[3] * * * o o - Okay" << endl;
    cout << "\t\t\t\t[4] * * o o o - Not Satisfied" << endl;
    cout << "\t\t\t\t[5] * o o o o - Disappointed" << endl;
    cout << "\t\t\t\t\t\tSelect option: ";
    cin >> option;

    switch (option) {
        case 1:
            feedback[countFeedbacks].starsFeed = 5;
            break;
        case 2:
            feedback[countFeedbacks].starsFeed = 4;
            break;
        case 3:
            feedback[countFeedbacks].starsFeed = 3;
            break;
        case 4:
            feedback[countFeedbacks].starsFeed = 2;
            break;
        case 5:
            feedback[countFeedbacks].starsFeed = 1;
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            feedbackUser(); 
    }

    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tSEND A FEEDBACK" << endl;
    cout<<"========================================================================================================================"<<endl;
    cin.ignore(); // Clear input buffer
    cout << "\t\t\t\tAbout what is your feedback? [Title]: ";
    getline(cin, tempTitle);
    feedback[countFeedbacks].titleFeed = tempTitle;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\tTell us more about your experience [Description]: ";
    getline(cin, tempDesc);
    feedback[countFeedbacks].descFeed = tempDesc;

    time_t currentTime = time(0); // Get current time in seconds since epoch
    tm* currentTimeStruct = localtime(&currentTime); // Convert time_t to tm
    feedback[countFeedbacks].dateMadeFeed = *currentTimeStruct; // Set current time

    countFeedbacks++;
        int currentCount = countFeedbacks - 1;
        saveFeedbacks();
        loadFeedbacks();

        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tOVERVIEW OF THE FEEDBACK" << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tStar Rating: " << feedback[currentCount].starsFeed << endl;
        cout << "\t\t\t\t\t\tTitle: " << feedback[currentCount].titleFeed << endl;
        cout << "\t\t\t\t\t\tDescription: " << feedback[currentCount].descFeed << endl;
        cout << "\t\t\t\t\t\tDate & Time made: " << feedback[currentCount].dateMadeFeed.tm_year + 1900 << "-"
            << "  " << setfill('0') << feedback[currentCount].dateMadeFeed.tm_mon + 1 << "-"
            << "  " << setfill('0') << feedback[currentCount].dateMadeFeed.tm_mday << " "
            << "  " << setfill('0') << feedback[currentCount].dateMadeFeed.tm_hour << ":"
            << "  " << setfill('0') << feedback[currentCount].dateMadeFeed.tm_min << endl;
        cout << "\t\t\t\t\t\tAre you sure you would like to send this feedback?[Y/N]: ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y'){
            cout << "\n\n\t\t\t\t\t\tSENDING, PLEASE WAIT";
            char x = 219;

            for (int i = 0; i <= 30; i++) {
                Sleep(30);
                cout << x;
            }
            cout << "\n\n\t\t\t\t\t\tSENT SUCCESSFULLY!"<<endl;
            system("pause");
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tWould like to send another feedback?[Y/N]: ";
            cin >> anotherchoice;
            if (anotherchoice == 'Y' || anotherchoice == 'y'){
                feedbackUser();
            } else if (anotherchoice == 'N' || anotherchoice == 'n'){
                userHome();
            }
        } else if (choice == 'N' || choice == 'n'){
            countFeedbacks--;
            saveFeedbacks();
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tWould you like to try again?[Y/N]: ";
            cin >> anotherchoice1;
            if (anotherchoice1 == 'Y' || anotherchoice1 == 'y'){
                feedbackUser();
            } else if (anotherchoice1 == 'N' || anotherchoice1 =='n'){
                userHome();
            }
        }
}

void viewAccountPage() {
    loadApplied();
    int num = 0;
    int index = -1;
    int checker = 0;
    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tMY ACCOUNT" << endl;
    cout<<"========================================================================================================================"<<endl;
    foundUser = false;

    for (int i = 0; i < countUser; i++) {
        if (user[i].username == userLog) {
            foundUser = true;
            index = i; // set the correct index here
            cout << "\t\t\t\t\t\tFullname: " << user[i].fullName << endl;
            cout << "\t\t\t\t\t\tAge: " << user[i].age << endl;
            cout << "\t\t\t\t\t\tAddress: " << user[i].address << endl;
            cout << "\t\t\t\t\t\tCash: " << user[i].cash << endl;
            break;
        }
    }

    if (!foundUser) {
        cout << "\t\t\t\t\t\tUser not found." << endl;
        return;
    }

    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t[1] Edit My Details" << endl;
    cout << "\t\t\t\t\t\t[2] View Loans" << endl;
    cout << "\t\t\t\t\t\t[3] Back" << endl;
    cout << endl << "\t\t\t\t\t\tSelect option: ";
    cin >> option;
    switch (option) {
        case 1:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tUPDATE MY DETAILS" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\t[1] Fullname" << endl;
            cout << "\t\t\t\t\t\t[2] Age" << endl;
            cout << "\t\t\t\t\t\t[3] Address" << endl;
            cout << "\t\t\t\t\t\t[4] Back" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tEnter number to be updated: ";
            cin >> option;
            cout<<"========================================================================================================================"<<endl;

            if (index != -1) { // check if a valid user was found
                cin.ignore(); // to clear the newline character left by cin

                switch (option) {
                    case 1:
                        cout << "\t\t\t\t\t\tEnter updated Fullname: ";
                        getline(cin, user[index].fullName);
                        break;
                    case 2:
                        cout << "\t\t\t\t\t\tEnter updated Age: ";
                        cin >> user[index].age;
                        cin.ignore(); // clear the newline character left by cin
                        break;
                    case 3:
                        cout << "\t\t\t\t\t\tEnter updated Address: ";
                        getline(cin, user[index].address);
                        break;
                    case 4:
                        viewAccountPage();
                        return;
                    default:
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "\t\t\t\t\t\tInvalid input!" << endl;
                        cout<<"========================================================================================================================"<<endl;
                        cout << "\t\t\t\t\t\tPress Enter to continue...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        viewAccountPage();
                }

                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tRecord updated successfully!" << endl;
                cout<<"========================================================================================================================"<<endl;
				system("pause");
                saveUser();
                viewAccountPage();
            } else {
                cout << "\t\t\t\t\t\tRecord not found!" << endl;
                cout<<"========================================================================================================================"<<endl;
				system("pause");
                system("cls");
                viewAccountPage();
            }
            break;
        case 2:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tVIEW GADGET LOAN" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\tBrand\tUnit\t\tPrice\tStatus" << endl;
           cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;

            foundUser = false;

            for (int i = 0; i < countUser; i++) {
                if (user[i].username == userLog) {
                    foundUser = true;
                    int currentUserID = user[i].userid;
                    
                    bool hasExistingLoan = false;
                    for (int j = 0; j < countApplied; j++) {
                        if (applied[j].userID == currentUserID && applied[j].loanType == "Gadget") {
                            hasExistingLoan = true;
                            cout << "\t\t\t\t" << j + 1 << ". "  << applied[j].brandLoan << "\t" << applied[j].unitLoan <<"\t"<< applied[j].priceLoan <<"\t" << applied[j].appliedStatus <<endl;
                        }
                    }

                    if (!hasExistingLoan) {
                        cout<<"\t\t\t\t\t\tNo gadget loans yet."<<endl;
                    }
                    cout<<"========================================================================================================================"<<endl;
                }
            }

            if (!foundUser) {
                cout << "\t\t\t\t\t\tUser not found." << endl;
            }
            cout << "\t\t\t\t\t\t[1] View More" << endl;
            cout << "\t\t\t\t\t\t[2] Back" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tSelect Option : ";
            cin >> option;
            switch (option) {
                case 1: {
                    system("cls");
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tVIEW GADGET LOAN" << endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\tBrand\tUnit\tPrice\tStatus" << endl;
                   cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;

                    foundUser = false;

                    for (int i = 0; i < countUser; i++) {
                        if (user[i].username == userLog) {
                            foundUser = true;
                            int currentUserID = user[i].userid;
                            
                            bool hasExistingLoan = false;
                            for (int j = 0; j < countApplied; j++) {
                                if (applied[j].userID == currentUserID && applied[j].loanType == "Gadget") {
                                    hasExistingLoan = true;
                                    cout << "\t\t\t\t" << j + 1 << ". \t\t\t\t"  << applied[j].brandLoan << "\t" << applied[j].unitLoan <<"\t"<< applied[j].priceLoan <<"\t" << applied[j].appliedStatus <<endl;
                                }
                            }

                            if (!hasExistingLoan) {
                                cout<<"\t\t\t\t\t\tNo gadget loans yet."<<endl;
                            }
                            cout<<"========================================================================================================================"<<endl;
                        }
                    }

                    if (!foundUser) {
                        cout << "\t\t\t\t\t\tUser not found." << endl;
                    }
                    int tempGadgetLoan;
                    cout << "\t\t\t\t\t\tSelect a number : ";
                    cin >> tempGadgetLoan;
                    tempGadgetLoan--;
                    if (tempGadgetLoan >= 0 && tempGadgetLoan < countGadgetCateg) {
                        system("cls");
                        cout<<"========================================================================================================================"<<endl;
                        cout << "\t\t\t\t\t\tGADGET DETAILS" << endl;
                        cout<<"========================================================================================================================"<<endl;
                        cout << "\t\t\t\t\t\tBrand: " << product[tempGadgetLoan].brand << endl;
                        cout << "\t\t\t\t\t\tUnit: " << product[tempGadgetLoan].unit << endl;
                        cout << "\t\t\t\t\t\tPrice: " << product[tempGadgetLoan].price << " pesos" << endl;
                        cout << "\t\t\t\t\t\tDescription: " << product[tempGadgetLoan].display << ", " << product[tempGadgetLoan].body << ", " 
                            << product[tempGadgetLoan].variant << ", " << product[tempGadgetLoan].camera << ", " 
                            << product[tempGadgetLoan].battery << ", " << product[tempGadgetLoan].processor << endl;
                        cout<<"========================================================================================================================"<<endl;
                        cout << "\t\t\t\t\t\t[1] Back" << endl;
                        cout << "\t\t\t\t\t\tSelect Option : ";
                        cin >> option;
                        switch (option) {
                            case 1:
                                viewAccountPage();
                                break;
                            default:
                                cin.clear(); 
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                                cout<<"========================================================================================================================"<<endl;
                                cout << "\t\t\t\t\t\tPress Enter to continue...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                viewGadgetLoan();
                        }
                    } else {
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "\t\t\t\t\t\tInvalid input!" << endl;
                        cout<<"========================================================================================================================"<<endl;
                        cout << "\t\t\t\t\t\tPress Enter to continue...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        viewGadgetLoan();
                    }
                }
                case 2: 
                    viewAccountPage();
                    break;   
                default:
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "\t\t\t\t\t\tInvalid input!" << endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tPress Enter to continue...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    viewAccountPage();
                }
                    
        case 3:
            system("cls");
            userHome();
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            viewAccountPage();
            break;        
        }
}
void userPayment(){
    loadUser();
    system("cls");
    int indexs = -1;
    string paynumber;
    int option = 0;
    int choice = 0;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tPAY FOR LOAN" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t[1] Cash IN" << endl;
    cout << "\t\t\t\t\t\t[2] Pay Money Loan" << endl;
    cout << "\t\t\t\t\t\t[3] Pay Gadget Loan" << endl;
    cout << "\t\t\t\t\t\t[4] Back" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tSelect Option: ";
    cin >> option;
    switch(option){
        case 1:
            cashIn();
            break;
        case 2:
           paywBalanceMoney();
           break;
        case 3:
            paywBalanceGadget();
            break;
        case 4:
            userHome();
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            userHome();
            break;
        }
}

void paywBalanceGadget(){
    loadUser();
    loadApplied();
    loadTransactions();
    char x =0;
    option =0;
    int pick = 0;
    int indexes = -1;
    foundUser = false;
            for (int i = 0; i < countUser; i++) {
                if (user[i].username == userLog) {
                    foundUser = true;
                        indexes = i; // set the correct index here
                        
                    if (indexes != -1) {
                        system("cls");
                        cout << "======================================================================================================================" << endl;
                        cout << "\t\t\t\t\t\tPAY WITH BALANCE" << endl;
                        cout << "======================================================================================================================" << endl;
                        cout << "\t\t\t\t\t       Current Balance: " << user[indexes].cash <<endl;
                        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "\t\t\t\t\t\tVIEW GADGET LOAN" << endl;
                        cout << "=====================================================================================================================" << endl;
                        cout << "Unit\t\tDownpayment\tDownpayment Status\tMonthly\t\tMonth Status\t\tDueDate" << endl;
                        cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
                                int currentUserID = user[indexes].userid;
                                
                                for (int i = 0; i < countUser; i++) {
                                if (user[i].username == userLog) {
                                    foundUser = true;
                                    int currentUserID = user[i].userid;
                                    
                                    
                                    bool hasExistingLoan = false;
                                    
                                    for (int j = 0; j < countApplied; j++) {
                                        if (applied[j].userID == currentUserID && applied[j].loanType == "Gadget" && applied[j].appliedStatus != "Pending") {
                                            hasExistingLoan = true;
                                            cout << j + 1 << ".) "  << applied[j].unitLoan << "\t" << applied[j].downpay <<"\t\t" << applied[j].downpayStatus <<"\t\t" << applied[j].monpay << " " << applied[j].monthsToPay <<" more months to go\t" << applied[j].monthsPaid << " Months paid";
                                            cout << "\t\t" << applied[j].dueDate.tm_year + 1900 << "-" << applied[j].dueDate.tm_mon + 1 << "-" << applied[j].dueDate.tm_mday << endl;
                                            break;
                                        } else if (applied[j].userID == currentUserID && applied[j].appliedStatus == "Pending"){
                                            hasExistingLoan = true;
                                            cout <<"\t\t\t\t\t\tGadget loans are being processed, Please wait."<<endl;
                                            system("pause");
                                            userPayment();
                                            break;
                                        } 
                                    }
                                    if (!hasExistingLoan){
                                            cout <<"\t\t\t\t\t\tNo Gadget Loans yet."<<endl;
                                            system("pause");
                                            userPayment();
                                        }
                                    
                                    
                                    int tempGadgetLoan;
                                    float finalPrice = 0;
                                    cout << "Select a number : ";
                                    cin >> tempGadgetLoan;
                                    tempGadgetLoan--;
                                    if (tempGadgetLoan >= 0 && tempGadgetLoan < countGadgetCateg) {
                                        system("cls");
                                        cout << "======================================================================================================================" << endl;
                                        cout << "\t\t\t\t\t\tGADGET DETAILS" << endl;
                                        cout << "======================================================================================================================" << endl;
                                        cout << "Brand: " << applied[tempGadgetLoan].brandLoan << endl;
                                        cout << "Unit: " << applied[tempGadgetLoan].unitLoan << endl;
                                        finalPrice = applied[tempGadgetLoan].priceLoan + applied[tempGadgetLoan].downpay;
                                        cout << "Downpayment: " << applied[tempGadgetLoan].downpay << " pesos" << endl;
                                        cout << "Downpayment Status: " << applied[tempGadgetLoan].downpayStatus << endl;
                                        cout << "Monthly: " << applied[tempGadgetLoan].monpay << " pesos" << endl;
                                        cout << "Months Left: " << applied[tempGadgetLoan].monthsToPay << " months" << endl;
                                        cout << "Final Price: " << finalPrice << " pesos" << endl;
                                        cout << "======================================================================================================================" << endl;
                                        cout << "[1] Pay Downpayment" << endl;
                                        cout << "[2] Pay Monthly" << endl;
                                        cout << "[3] Back" << endl;
                                        cout << "Select Option : ";
                                        cin >> option;
                                        switch (option) {
                                            case 1:
                                                system("cls");
                                                cout << "======================================================================================================================" << endl;
                                                cout << "\t\t\t\t\t\tPAY DOWNPAYMENT" << endl;
                                                cout << "======================================================================================================================" << endl;
                                                cout << "\t\t\t\t\t\tCurrent Balance: " << user[indexes].cash <<endl;
                                                cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
                                                cout << "======================================================================================================================" << endl;
                                                cout << "\t\t\t\t\t\tGADGET DETAILS" << endl;
                                                cout << "======================================================================================================================" << endl;
                                                cout << "Brand: " << applied[tempGadgetLoan].brandLoan << endl;
                                                cout << "Unit: " << applied[tempGadgetLoan].unitLoan << endl;
                                                finalPrice = applied[tempGadgetLoan].priceLoan + applied[tempGadgetLoan].downpay;
                                                cout << "Downpayment: " << applied[tempGadgetLoan].downpay << " pesos" << endl;
                                                cout << "Downpayment Status: " << applied[tempGadgetLoan].downpayStatus << endl;
                                                cout << "Monthly: " << applied[tempGadgetLoan].monpay << " pesos" << endl;
                                                cout << "Months Left: " << applied[tempGadgetLoan].monthsToPay << " months" << endl;
                                                cout << "Final Price: " << finalPrice << " pesos" << endl;
                                                cout << "======================================================================================================================" << endl;
                                                cout << "[1] Pay Downpayment" << endl;
                                                cout << "[2] Back" << endl;
                                                cout << "Select option: ";
                                                cin >> pick;
                                                switch (pick) {
                                                    case 1:
                                                        if (applied[tempGadgetLoan].downpayStatus == "Paid"){
                                                            cout << "======================================================================================================================" << endl;
                                                            cout << "\t\t\tThe selected Loan's Downpayment is already paid."<<endl;
                                                            cout << "======================================================================================================================" << endl;
                                                            system("pause");
                                                            userPayment();
                                                            break;
                                                        }
                                                        cout << "======================================================================================================================" << endl;
                                                        cout << "\t\t\t\t\t\t[NOTICE]Payment is getting processed, please wait[NOTICE]"<<endl;
                                                        cout<<"\n\n\t\tPROCESSING";
                                                        x =219;
                                                    
                                                        for(int i=0; i<=30; i++){
                                                            Sleep(30);
                                                            cout<<x;
                                                        }
                                                        cout<<endl;
                                                        if (user[indexes].cash >= applied[tempGadgetLoan].downpay){
                                                            applied[tempGadgetLoan].downpayStatus = "Paid";
                                                            user[indexes].cash = user[indexes].cash - applied[tempGadgetLoan].downpay;
                                                            transaction[countTransactions].userIDTrans = applied[tempGadgetLoan].userID;
                                                            transaction[countTransactions].fnameTrans = applied[tempGadgetLoan].fname;
                                                            transaction[countTransactions].loanTypeTrans = applied[tempGadgetLoan].loanType;
                                                            transaction[countTransactions].statusTrans = "Sucessful";
                                                            transaction[countTransactions].monthsToPayTrans = applied[tempGadgetLoan].monthsToPay;
                                                            transaction[countTransactions].monthsPaidTrans = applied[tempGadgetLoan].monthsPaid;
                                                            transaction[countTransactions].userCashTrans = user[indexes].cash;
                                                            transaction[countTransactions].typeTrans = "Downpayment";
                                                            transaction[countTransactions].priceTrans = applied[tempGadgetLoan].downpay;
                                                            time_t currentTime = time(0); // Get current time in seconds since epoch
                                                            tm* currentTimeStruct = localtime(&currentTime); // Convert time_t to tm
                                                            transaction[countTransactions].dateMade = *currentTimeStruct; // Get current time
                                                            countTransactions++;
                                                            saveTransactions();
                                                            saveApplied();
                                                            loadApplied();
                                                            saveUser();
                                                            loadUser();
                                                            cout<<"\t\t\t\t\t\t\n\n[NOTICE]Payment Sucessful![NOTICE]\n\n";
                                                            cout << "\t\t\t\t\t\tCurrent Balance: " << user[indexes].cash <<endl;
                                                        }else {
                                                            cout<<"\t\t\t\t\t\t\n\n[NOTICE]Payment Failed, Insufficient Balance[NOTICE]\n\n"<<endl;
                                                            cout << "\t\t\t\t\t\tCurrent Balance: " << user[indexes].cash <<endl;
                                                            transaction[countTransactions].userIDTrans = applied[tempGadgetLoan].userID;
                                                            transaction[countTransactions].fnameTrans = applied[tempGadgetLoan].fname;
                                                            transaction[countTransactions].loanTypeTrans = applied[tempGadgetLoan].loanType;
                                                            transaction[countTransactions].statusTrans = "Failed";
                                                            transaction[countTransactions].monthsToPayTrans = applied[tempGadgetLoan].monthsToPay;
                                                            transaction[countTransactions].monthsPaidTrans = applied[tempGadgetLoan].monthsPaid;
                                                            transaction[countTransactions].userCashTrans = user[indexes].cash;
                                                            transaction[countTransactions].typeTrans = "Downpayment";
                                                            transaction[countTransactions].priceTrans = applied[tempGadgetLoan].downpay;
                                                            time_t currentTime = time(0); // Get current time in seconds since epoch
                                                            tm* currentTimeStruct = localtime(&currentTime); // Convert time_t to tm
                                                            transaction[countTransactions].dateMade = *currentTimeStruct; // Get current time
                                                            countTransactions++;
                                                            saveTransactions();
                                                        }
                                                        
                                                        cout << "======================================================================================================================" << endl;
                                                        system("pause");
                                                        userPayment();
                                                        break;
                                                    case 2:
                                                        userPayment();
                                                        break;
                                                    default:
                                                        cin.clear(); 
                                                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                                                        cout << "\t\t\t\t\t\tInvalid input!" << endl;
                                                        cout<<"========================================================================================================================"<<endl;
                                                        cout << "\t\t\t\t\t\tPress Enter to continue...";
                                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                        userPayment();

                                                        }
                                        case 2:
                                            loadUser();
                                            loadApplied();
                                            system("cls");
                                            cout << "======================================================================================================================" << endl;
                                            cout << "\t\t\t\t\t\tPAY MONTHLY DUE" << endl;
                                            cout << "======================================================================================================================" << endl;
                                            cout << "\t\t\t\t\t\tCurrent Balance: " << user[indexes].cash <<endl;
                                            cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
                                            cout << "======================================================================================================================" << endl;
                                            cout << "\t\t\t\t\t\tGADGET DETAILS" << endl;
                                            cout << "======================================================================================================================" << endl;
                                            cout << "Brand: " << applied[tempGadgetLoan].brandLoan << endl;
                                            cout << "Unit: " << applied[tempGadgetLoan].unitLoan << endl;
                                            finalPrice = applied[tempGadgetLoan].priceLoan + applied[tempGadgetLoan].downpay;
                                            cout << "Downpayment: " << applied[tempGadgetLoan].downpay << " pesos" << endl;
                                            cout << "Downpayment Status: " << applied[tempGadgetLoan].downpayStatus << endl;
                                            cout << "Monthly: " << applied[tempGadgetLoan].monpay << " pesos" << endl;
                                            cout << "Months Left: " << applied[tempGadgetLoan].monthsToPay << " months" <<endl;
                                            cout << "Final Price: " << finalPrice << " pesos" << endl;
                                            cout << "======================================================================================================================" << endl;
                                            cout << "[1] Pay Month " << applied[tempGadgetLoan].monthsPaid + 1 << endl;
                                            cout << "[2] Back" << endl;
                                            cout << "Select option: ";
                                            cin >> pick;
                                            switch (pick) {
                                                case 1:
                                                    if (applied[tempGadgetLoan].monthsToPay == 0){
                                                        cout << "======================================================================================================================" << endl;
                                                        cout << "\t\t\tThe selected Loan's Monthly Payments are already paid."<<endl;
                                                        cout << "======================================================================================================================" << endl;
                                                        system("pause");
                                                        userPayment();
                                                        break;
                                                    }
                                                    cout << "======================================================================================================================" << endl;
                                                    cout << "\t\t\t\t[NOTICE]Payment is getting processed, please wait[NOTICE]"<<endl;
                                                    cout<<"\n\n\t\t\t\tPROCESSING";
                                                    x =219;
                                                
                                                    for(int i=0; i<=30; i++){
                                                        Sleep(30);
                                                        cout<<x;
                                                    }
                                                    cout<<endl;
                                                    if (user[indexes].cash >= applied[tempGadgetLoan].monpay){
                                                        applied[tempGadgetLoan].monthsPaid++;
                                                        applied[tempGadgetLoan].monthsToPay--;
                                                        user[indexes].cash = user[indexes].cash - applied[tempGadgetLoan].monpay;
                                                        transaction[countTransactions].userIDTrans = applied[tempGadgetLoan].userID;
                                                        transaction[countTransactions].fnameTrans = applied[tempGadgetLoan].fname;
                                                        transaction[countTransactions].loanTypeTrans = applied[tempGadgetLoan].loanType;
                                                        transaction[countTransactions].statusTrans = "Sucessful";
                                                        transaction[countTransactions].monthsToPayTrans = applied[tempGadgetLoan].monthsToPay;
                                                        transaction[countTransactions].monthsPaidTrans = applied[tempGadgetLoan].monthsPaid;
                                                        transaction[countTransactions].userCashTrans = user[indexes].cash;
                                                        transaction[countTransactions].typeTrans = "Monthly";
                                                        transaction[countTransactions].priceTrans = applied[tempGadgetLoan].monpay;
                                                        time_t currentTime = time(0); // Get current time in seconds since epoch
                                                        tm* currentTimeStruct = localtime(&currentTime); // Convert time_t to tm
                                                        transaction[countTransactions].dateMade = *currentTimeStruct; // Get current time
                                                        countTransactions++;
                                                        saveTransactions();
                                                        cout<<"\n\n\t\t\t\t\t[NOTICE]Payment Sucessful![NOTICE]\n\n";
                                                        tm dueDate = applied[tempGadgetLoan].dueDate;
                                                        dueDate.tm_mon++; 
                                                        mktime(&dueDate); // Normalize dueDate
                                                        applied[tempGadgetLoan].dueDate = dueDate;

                                                        saveApplied();
                                                        loadApplied();
                                                        saveUser();
                                                        loadUser();
                                                        cout << "\t\t\t\t\t\tCurrent Balance: " << user[indexes].cash <<endl;
                                                        cout << "\t\t\t\t\tThe next due date is: " << applied[tempGadgetLoan].dueDate.tm_year + 1900 << "-" << applied[tempGadgetLoan].dueDate.tm_mon + 1 << "-" << applied[tempGadgetLoan].dueDate.tm_mday<<endl;
                                                    }else {
                                                        cout<<"\t\t\t\t\t\t\n\n[NOTICE]Payment Failed, Insufficient Balance[NOTICE]\n\n"<<endl;
                                                        cout << "\t\t\t\t\t\tCurrent Balance: " << user[indexes].cash <<endl;
                                                        transaction[countTransactions].userIDTrans = applied[tempGadgetLoan].userID;
                                                        transaction[countTransactions].fnameTrans = applied[tempGadgetLoan].fname;
                                                        transaction[countTransactions].loanTypeTrans = applied[tempGadgetLoan].loanType;
                                                        transaction[countTransactions].statusTrans = "Failed";
                                                        transaction[countTransactions].monthsToPayTrans = applied[tempGadgetLoan].monthsToPay;
                                                        transaction[countTransactions].monthsPaidTrans = applied[tempGadgetLoan].monthsPaid;
                                                        transaction[countTransactions].userCashTrans = user[indexes].cash;
                                                        transaction[countTransactions].typeTrans = "Monthly";
                                                        transaction[countTransactions].priceTrans = applied[tempGadgetLoan].monpay;
                                                        time_t currentTime = time(0); // Get current time in seconds since epoch
                                                        tm* currentTimeStruct = localtime(&currentTime); // Convert time_t to tm
                                                        transaction[countTransactions].dateMade = *currentTimeStruct; // Get current time
                                                        countTransactions++;
                                                        saveTransactions();
                                                    }
                                                    
                                                    cout << "======================================================================================================================" << endl;
                                                    system("pause");
                                                    userPayment();
                                                    break;
                                                case 2:
                                                    userPayment();
                                                    break;
                                                default:
                                                cin.clear(); 
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                                                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                                                cout<<"========================================================================================================================"<<endl;
                                                cout << "\t\t\t\t\t\tPress Enter to continue...";
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                userPayment();
                                                break;
                                            }          
                                        case 3:
                                            userPayment();
                                            break;
                                        default:
                                            cin.clear(); 
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                                            cout << "\t\t\t\t\t\tInvalid input!" << endl;
                                            cout<<"========================================================================================================================"<<endl;
                                            cout << "\t\t\t\t\t\tPress Enter to continue...";
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            userPayment();
                                            break;
                                    }
                                    } else {
                                        cin.clear(); 
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                                        cout << "\t\t\t\t\t\tInvalid input!" << endl;
                                        cout<<"========================================================================================================================"<<endl;
                                        cout << "\t\t\t\t\t\tPress Enter to continue...";
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        userPayment();
                                    }

                                    if (!hasExistingLoan) {
                                        cout<<"\t\t\t\t\t\tNo gadget loans yet."<<endl;
                                    }
                                    cout<<"========================================================================================================================"<<endl;
                                }

                            }
                        }
                    }
                }

        if (!foundUser) {
            cout << "User not found." << endl;
        }
                
}
void paywBalanceMoney(){
    loadUser();
    loadAppliedMoney();
    char x =0;
    option =0;
    int pick = 0;
    int indexes = -1;
    foundUser = false;
            for (int i = 0; i < countUser; i++) {
                if (user[i].username == userLog) {
                    foundUser = true;
                        indexes = i; // set the correct index here
                        
                    if (indexes != -1) {
                        system("cls");
                        cout << "======================================================================================================================" << endl;
                        cout << "\t\t\t\t\t\tPAY WITH BALANCE" << endl;
                        cout << "======================================================================================================================" << endl;
                        cout << "\t\t\t\t\t       Current Balance: " << user[indexes].cash <<endl;
                        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "\t\t\t\t\t\tVIEW MONEY LOAN" << endl;
                        cout << "=====================================================================================================================" << endl;
                        cout << "Money\t\tInterest\tInterest Status\tMonthly\t\tMonth Status\t\tDueDate" << endl;
                        cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
                                int currentUserID = user[indexes].userid;
                                
                                for (int i = 0; i < countUser; i++) {
                                if (user[i].username == userLog) {
                                    foundUser = true;
                                    int currentUserID = user[i].userid;
                                    
                                    bool hasExistingLoan = false;
                                    for (int j = 0; j < countAppliedMoney; j++) {
                                        if (appliedMoney[j].userIDMoney == currentUserID && appliedMoney[j].loanTypeMoney == "Money" && appliedMoney[j].appliedStatusMoney != "Pending") {
                                            hasExistingLoan = true;
                                            cout << j + 1 << ".) "  << appliedMoney[j].priceLoanMoney << "\t" << appliedMoney[j].interestMoney <<"\t\t" << appliedMoney[j].intereststatusMoney <<"\t\t" << appliedMoney[j].monpayMoney << " " << appliedMoney[j].monthsToPayMoney <<" more months to go\t" << appliedMoney[j].monthsPaidMoney << " Months paid";
                                            cout << "\t\t" << appliedMoney[j].dueDateMoney.tm_year + 1900 << "-" << appliedMoney[j].dueDateMoney.tm_mon + 1 << "-" << appliedMoney[j].dueDateMoney.tm_mday << endl;
                                            break;
                                        } else if (appliedMoney[j].userIDMoney == currentUserID && appliedMoney[j].appliedStatusMoney == "Pending"){
                                            hasExistingLoan = true;
                                            cout <<"\t\t\t\t\t\tMoney loans are being processed, Please wait."<<endl;
                                            system("pause");
                                            userPayment();
                                            break;
                                        }
                                    }
                                    if (!hasExistingLoan){
                                            cout<<"\t\t\t\t\t\tNo Money Loans yet."<<endl;
                                            system("pause");
                                            userPayment();
                                        }
                                    
                                    int tempMoneyLoan;
                                    float finalPrice = 0;
                                    cout << "\t\t\t\t\t\tSelect a number : ";
                                    cin >> tempMoneyLoan;
                                    tempMoneyLoan--;
                                    if (tempMoneyLoan >= 0 && tempMoneyLoan < countMoney) {
                                        system("cls");
                                        cout << "======================================================================================================================" << endl;
                                        cout << "\t\t\t\t\t\tMONEY DETAILS" << endl;
                                        cout << "======================================================================================================================" << endl;
                                        cout << "Money: " << appliedMoney[tempMoneyLoan].priceLoanMoney << endl;
                                        finalPrice = appliedMoney[tempMoneyLoan].priceLoanMoney + appliedMoney[tempMoneyLoan].interestMoney;
                                        cout << "Interest: " << appliedMoney[tempMoneyLoan].interestMoney << " pesos" << endl;
                                        cout << "Interest Status: " << appliedMoney[tempMoneyLoan].intereststatusMoney << endl;
                                        cout << "Monthly: " << appliedMoney[tempMoneyLoan].monpayMoney << " pesos" << endl;
                                        cout << "Months Left: " << appliedMoney[tempMoneyLoan].monthsToPayMoney << " months" << endl;
                                        cout << "Final Price: " << finalPrice << " pesos" << endl;
                                        cout << "======================================================================================================================" << endl;
                                        cout << "[1] Pay Interest" << endl;
                                        cout << "[2] Pay Monthly" << endl;
                                        cout << "[3] Back" << endl;
                                        cout << "Select Option : ";
                                        cin >> option;
                                        switch (option) {
                                            case 1:
                                                system("cls");
                                                cout << "======================================================================================================================" << endl;
                                                cout << "\t\t\t\t\t\tPAY INTEREST" << endl;
                                                cout << "======================================================================================================================" << endl;
                                                cout << "\t\t\t\t\t\tCurrent Balance: " << user[indexes].cash <<endl;
                                                cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
                                                cout << "======================================================================================================================" << endl;
                                                cout << "\t\t\t\t\t\tGADGET DETAILS" << endl;
                                                cout << "======================================================================================================================" << endl;
                                                cout << "Money: " << appliedMoney[tempMoneyLoan].priceLoanMoney << endl;
                                                finalPrice = appliedMoney[tempMoneyLoan].priceLoanMoney + appliedMoney[tempMoneyLoan].interestMoney;
                                                cout << "Interest: " << appliedMoney[tempMoneyLoan].interestMoney << " pesos" << endl;
                                                cout << "Interest Status: " << appliedMoney[tempMoneyLoan].intereststatusMoney << endl;
                                                cout << "Monthly: " << appliedMoney[tempMoneyLoan].monpayMoney << " pesos" << endl;
                                                cout << "Months Left: " << appliedMoney[tempMoneyLoan].monthsToPayMoney << " months" << endl;
                                                cout << "Final Price: " << finalPrice << " pesos" << endl;
                                                cout << "======================================================================================================================" << endl;
                                                cout << "[1] Pay Interest" << endl;
                                                cout << "[2] Back" << endl;
                                                cout << "Select option: ";
                                                cin >> pick;
                                                switch (pick) {
                                                    case 1:
                                                        if (appliedMoney[tempMoneyLoan].intereststatusMoney == "Paid"){
                                                            cout << "======================================================================================================================" << endl;
                                                            cout << "\t\t\tThe selected Loan's Interest is already paid."<<endl;
                                                            cout << "======================================================================================================================" << endl;
                                                            system("pause");
                                                            userPayment();
                                                            break;
                                                        }
                                                        cout << "======================================================================================================================" << endl;
                                                        cout << "\t\t\t\t\t\t[NOTICE]Payment is getting processed, please wait[NOTICE]"<<endl;
                                                        cout<<"\n\n\t\tPROCESSING";
                                                        x =219;
                                                    
                                                        for(int i=0; i<=30; i++){
                                                            Sleep(30);
                                                            cout<<x;
                                                        }
                                                        cout<<endl;
                                                        if (user[indexes].cash >= appliedMoney[tempMoneyLoan].interestMoney){
                                                            appliedMoney[tempMoneyLoan].intereststatusMoney = "Paid";
                                                            user[indexes].cash = user[indexes].cash - appliedMoney[tempMoneyLoan].interestMoney;
                                                            transaction[countTransactions].userIDTrans = appliedMoney[tempMoneyLoan].userIDMoney;
                                                            transaction[countTransactions].fnameTrans = appliedMoney[tempMoneyLoan].fnameMoney;
                                                            transaction[countTransactions].loanTypeTrans = appliedMoney[tempMoneyLoan].loanTypeMoney;
                                                            transaction[countTransactions].statusTrans = "Sucessful";
                                                            transaction[countTransactions].monthsToPayTrans = appliedMoney[tempMoneyLoan].monthsToPayMoney;
                                                            transaction[countTransactions].monthsPaidTrans = appliedMoney[tempMoneyLoan].monthsPaidMoney;
                                                            transaction[countTransactions].userCashTrans = user[indexes].cash;
                                                            transaction[countTransactions].typeTrans = "Interest";
                                                            transaction[countTransactions].priceTrans = appliedMoney[tempMoneyLoan].interestMoney;
                                                            time_t currentTime = time(0); // Get current time in seconds since epoch
                                                            tm* currentTimeStruct = localtime(&currentTime); // Convert time_t to tm
                                                            transaction[countTransactions].dateMade = *currentTimeStruct; // Get current time
                                                            countTransactions++;
                                                            saveTransactions();
                                                            saveAppliedMoney();
                                                            loadAppliedMoney();
                                                            saveUser();
                                                            loadUser();
                                                            cout<<"\t\t\t\t\t\t\n\n[NOTICE]Payment Sucessful![NOTICE]\n\n";
                                                            cout << "\t\t\t\t\t\tCurrent Balance: " << user[indexes].cash <<endl;
                                                            
                                                        }else {
                                                            cout<<"\t\t\t\t\t\t\n\n[NOTICE]Payment Failed, Insufficient Balance[NOTICE]\n\n"<<endl;
                                                            cout << "\t\t\t\t\t\tCurrent Balance: " << user[indexes].cash <<endl;
                                                            transaction[countTransactions].userIDTrans = appliedMoney[tempMoneyLoan].userIDMoney;
                                                            transaction[countTransactions].fnameTrans = appliedMoney[tempMoneyLoan].fnameMoney;
                                                            transaction[countTransactions].loanTypeTrans = appliedMoney[tempMoneyLoan].loanTypeMoney;
                                                            transaction[countTransactions].statusTrans = "Failed";
                                                            transaction[countTransactions].monthsToPayTrans = appliedMoney[tempMoneyLoan].monthsToPayMoney;
                                                            transaction[countTransactions].monthsPaidTrans = appliedMoney[tempMoneyLoan].monthsPaidMoney;
                                                            transaction[countTransactions].userCashTrans = user[indexes].cash;
                                                            transaction[countTransactions].typeTrans = "Interest";
                                                            transaction[countTransactions].priceTrans = appliedMoney[tempMoneyLoan].interestMoney;
                                                            time_t currentTime = time(0); // Get current time in seconds since epoch
                                                            tm* currentTimeStruct = localtime(&currentTime); // Convert time_t to tm
                                                            transaction[countTransactions].dateMade = *currentTimeStruct; // Get current time
                                                            countTransactions++;
                                                            saveTransactions();
                                                        }
                                                        
                                                        cout << "======================================================================================================================" << endl;
                                                        system("pause");
                                                        userPayment();
                                                        break;
                                                    case 2:
                                                        userPayment();
                                                        break;
                                                    default:
                                                        cin.clear(); 
                                                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                                                        cout << "\t\t\t\t\t\tInvalid input!" << endl;
                                                        cout<<"========================================================================================================================"<<endl;
                                                        cout << "\t\t\t\t\t\tPress Enter to continue...";
                                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                        userPayment();

                                                        }
                                        case 2:
                                            loadUser();
                                            loadAppliedMoney();
                                            system("cls");
                                            cout << "======================================================================================================================" << endl;
                                            cout << "\t\t\t\t\t\tPAY MONTHLY DUE" << endl;
                                            cout << "======================================================================================================================" << endl;
                                            cout << "\t\t\t\t\t\tCurrent Balance: " << user[indexes].cash <<endl;
                                            cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
                                            cout << "======================================================================================================================" << endl;
                                            cout << "\t\t\t\t\t\tMONEY DETAILS" << endl;
                                            cout << "======================================================================================================================" << endl;
                                            cout << "Money: " << appliedMoney[tempMoneyLoan].priceLoanMoney << endl;
                                                finalPrice = appliedMoney[tempMoneyLoan].priceLoanMoney + appliedMoney[tempMoneyLoan].interestMoney;
                                                cout << "Interest: " << appliedMoney[tempMoneyLoan].interestMoney << " pesos" << endl;
                                                cout << "Interest Status: " << appliedMoney[tempMoneyLoan].intereststatusMoney << endl;
                                                cout << "Monthly: " << appliedMoney[tempMoneyLoan].monpayMoney << " pesos" << endl;
                                                cout << "Months Left: " << appliedMoney[tempMoneyLoan].monthsToPayMoney << " months" << endl;
                                                cout << "Final Price: " << finalPrice << " pesos" << endl;
                                            cout << "======================================================================================================================" << endl;
                                            cout << "[1] Pay Month " << appliedMoney[tempMoneyLoan].monthsPaidMoney + 1 << endl;
                                            cout << "[2] Back" << endl;
                                            cout << "Select option: ";
                                            cin >> pick;
                                            switch (pick) {
                                                case 1:
                                                    if (appliedMoney[tempMoneyLoan].monthsToPayMoney == 0){
                                                        cout << "======================================================================================================================" << endl;
                                                        cout << "\t\t\tThe selected Loan's Monthly Payments are already paid."<<endl;
                                                        cout << "======================================================================================================================" << endl;
                                                        system("pause");
                                                        userPayment();
                                                        break;
                                                    }
                                                    cout << "======================================================================================================================" << endl;
                                                    cout << "\t\t\t\t[NOTICE]Payment is getting processed, please wait[NOTICE]"<<endl;
                                                    cout<<"\n\n\t\t\t\tPROCESSING";
                                                    x =219;
                                                
                                                    for(int i=0; i<=30; i++){
                                                        Sleep(30);
                                                        cout<<x;
                                                    }
                                                    cout<<endl;
                                                    if (user[indexes].cash >= appliedMoney[tempMoneyLoan].monpayMoney){
                                                        appliedMoney[tempMoneyLoan].monthsPaidMoney++;
                                                        appliedMoney[tempMoneyLoan].monthsToPayMoney--;
                                                        user[indexes].cash = user[indexes].cash - appliedMoney[tempMoneyLoan].monpayMoney;
                                                        transaction[countTransactions].userIDTrans = appliedMoney[tempMoneyLoan].userIDMoney;
                                                        transaction[countTransactions].fnameTrans = appliedMoney[tempMoneyLoan].fnameMoney;
                                                        transaction[countTransactions].loanTypeTrans = appliedMoney[tempMoneyLoan].loanTypeMoney;
                                                        transaction[countTransactions].statusTrans = "Sucessful";
                                                        transaction[countTransactions].monthsToPayTrans = appliedMoney[tempMoneyLoan].monthsToPayMoney;
                                                        transaction[countTransactions].monthsPaidTrans = appliedMoney[tempMoneyLoan].monthsPaidMoney;
                                                        transaction[countTransactions].userCashTrans = user[indexes].cash;
                                                        transaction[countTransactions].typeTrans = "Monthly";
                                                        transaction[countTransactions].priceTrans = appliedMoney[tempMoneyLoan].monpayMoney;
                                                        time_t currentTime = time(0); // Get current time in seconds since epoch
                                                        tm* currentTimeStruct = localtime(&currentTime); // Convert time_t to tm
                                                        transaction[countTransactions].dateMade = *currentTimeStruct; // Get current time
                                                        countTransactions++;
                                                        saveTransactions();
                                                        cout<<"\n\n\t\t\t\t\t[NOTICE]Payment Sucessful![NOTICE]\n\n";
                                                        tm dueDate = appliedMoney[tempMoneyLoan].dueDateMoney;
                                                        dueDate.tm_mon++; 
                                                        mktime(&dueDate); // Normalize dueDate
                                                        appliedMoney[tempMoneyLoan].dueDateMoney = dueDate;

                                                        saveAppliedMoney();
                                                        loadAppliedMoney();
                                                        saveUser();
                                                        loadUser();
                                                        cout << "\t\t\t\t\t\tCurrent Balance: " << user[indexes].cash <<endl;
                                                        cout << "\t\t\t\t\tThe next due date is: " << appliedMoney[tempMoneyLoan].dueDateMoney.tm_year + 1900 << "-" << appliedMoney[tempMoneyLoan].dueDateMoney.tm_mon + 1 << "-" << appliedMoney[tempMoneyLoan].dueDateMoney.tm_mday<<endl;
                                                    }else {
                                                        cout<<"\t\t\t\t\t\t\n\n[NOTICE]Payment Failed, Insufficient Balance[NOTICE]\n\n"<<endl;
                                                        cout << "\t\t\t\t\t\tCurrent Balance: " << user[indexes].cash <<endl;
                                                        transaction[countTransactions].userIDTrans = appliedMoney[tempMoneyLoan].userIDMoney;
                                                        transaction[countTransactions].fnameTrans = appliedMoney[tempMoneyLoan].fnameMoney;
                                                        transaction[countTransactions].loanTypeTrans = appliedMoney[tempMoneyLoan].loanTypeMoney;
                                                        transaction[countTransactions].statusTrans = "Failed";
                                                        transaction[countTransactions].monthsToPayTrans = appliedMoney[tempMoneyLoan].monthsToPayMoney;
                                                        transaction[countTransactions].monthsPaidTrans = appliedMoney[tempMoneyLoan].monthsPaidMoney;
                                                        transaction[countTransactions].userCashTrans = user[indexes].cash;
                                                        transaction[countTransactions].typeTrans = "Monthly";
                                                        transaction[countTransactions].priceTrans = appliedMoney[tempMoneyLoan].monpayMoney;
                                                        time_t currentTime = time(0); // Get current time in seconds since epoch
                                                        tm* currentTimeStruct = localtime(&currentTime); // Convert time_t to tm
                                                        transaction[countTransactions].dateMade = *currentTimeStruct; // Get current time
                                                        countTransactions++;
                                                        saveTransactions();
                                                    }
                                                    
                                                    cout << "======================================================================================================================" << endl;
                                                    system("pause");
                                                    userPayment();
                                                    break;
                                                case 2:
                                                    userPayment();
                                                    break;
                                                default:
                                                cin.clear(); 
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                                                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                                                cout<<"========================================================================================================================"<<endl;
                                                cout << "\t\t\t\t\t\tPress Enter to continue...";
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                userPayment();
                                            }          
                                        case 3:
                                            userPayment();
                                            break;
                                        default:
                                        cin.clear(); 
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                                        cout << "\t\t\t\t\t\tInvalid input!" << endl;
                                        cout<<"========================================================================================================================"<<endl;
                                        cout << "\t\t\t\t\t\tPress Enter to continue...";
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        userPayment();
                                    }
                                    } else {
                                        cout << "\t\t\t\t\t\tInvalid Input!" << endl;
                                        system("pause");
                                        userPayment();
                                    }

                                    if (!hasExistingLoan) {
                                        cout<<"\t\t\t\t\t\tNo gadget loans yet."<<endl;
                                    }
                                    cout<<"========================================================================================================================"<<endl;
                                }

                            }
                        }
                    }
                }

        if (!foundUser) {
            cout << "User not found." << endl;
        }
                
}

void cashIn(){
    loadUser();
    float CashIn = 0;
    int indexs = -1;
    int choice =0;
    string paynumber;
        system("cls");
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tCASH IN" << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tPayment Methods: " <<endl;
        cout << "\t\t\t\t\t\t[NOTICE] These are our only way of payment methods on borrow ease "<<endl;
        cout << "\t\t\t\t\t\tcurrently, Please excuse us for your inconvenience [NOTICE]" << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\t[1] Gcash" << endl;
        cout << "\t\t\t\t\t\t[2] Paymaya" << endl;
        cout << "\t\t\t\t\t\t[3] Back" << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tSelect Option: ";
        cin >> choice;
        switch(choice){
            case 1:
            system("cls");
                foundUser = false;

                for (int i = 0; i < countUser; i++) {
                    if (user[i].username == userLog) {
                        foundUser = true;
                        indexs = i; // set the correct index here

                

                if (!foundUser) {
                    cout << "\t\t\t\t\t\tUser not found." << endl;
                }
                if (indexs != -1) {
                    system("cls");
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tGCASH"<< endl;
                    cout<<"========================================================================================================================"<<endl;
                    cin.ignore();
                    cout<<"\t\t\t\t\t\tInput your Gcash Number: ";
                    getline(cin, paynumber);
                    cout<<"\t\t\t\t\t\tHow much to cash in: ";
                    cin>> CashIn;
                    user[indexs].cash = CashIn + user[indexs].cash ;
                    saveUser();
                    cout<<"\t\t\t\t\t\tPlease scan the barcode to confirm payment."<<endl;
                    cout<<"========================================================================================================================"<<endl;
                    generateBarcode();
                    cout<<"========================================================================================================================"<<endl;
                    system("pause");
                    userHome();
                    break;
                }
            }
        }
            case 2:
            system("cls");
                foundUser = false;

                for (int i = 0; i < countUser; i++) {
                    if (user[i].username == userLog) {
                        foundUser = true;
                        indexs = i; // set the correct index here
                

                if (!foundUser) {
                    cout << "\t\t\t\t\t\tUser not found." << endl;
                }
                if (indexs != -1) {
                    system("cls");
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tPAYMAYA"<< endl;
                    cout<<"========================================================================================================================"<<endl;
                    cin.ignore();
                    cout<<"\t\t\t\t\t\tInput your Gcash Number: ";
                    getline(cin, paynumber);
                    cout<<"\t\t\t\t\t\tHow much to cash in: ";
                    cin>> CashIn;
                    user[indexs].cash = CashIn + user[indexs].cash ;
                    saveUser();
                    cout<<"\t\t\t\t\t\tPlease scan the barcode to confirm payment."<<endl;
                    cout<<"========================================================================================================================"<<endl;
                    generateBarcode();
                    cout<<"========================================================================================================================"<<endl;
                    system("pause");
                    userHome();
                    break;
                }
            }
        }
            case 3:
                userPayment();
                break;
            default:
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                userPayment();
                break;
            }
}

void userViewProducts() {
    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tVIEW LOAN CATEGORIES" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t[1] Money Loan" << endl;
    cout << "\t\t\t\t\t\t[2] Gadget Loan" << endl;
    cout << "\t\t\t\t\t\t[3] Back" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tSelect Option : ";
    cin >> option;
    switch (option) {
        case 1:
            viewMoneyLoan();
            break;
        case 2:
            viewGadgetLoan();
            break;
        case 3:
            userHome();
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            userViewProducts();
            break;
    }
}

void viewGadgetLoan() {
    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tVIEW GADGET LOAN" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\tBrand\tUnit\tPrice\tQuantity" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------"<<endl;
    chk=0;
    for (int i = 0; i < countProducts; i++) {
        if (product[i].quantityProduct > 0){
            chk=1;
        cout << "\t\t\t\t" << i + 1 << ". " << product[i].brand << " \t" << product[i].unit << " \t" << product[i].price << " \t" << product[i].quantityProduct<< endl;
        }
    }
    if(chk != 1){
                cout<<"\t\t\t\t\t\tNo Gadget Loan yet."<<endl;
    }
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t[1] View More" << endl;
    cout << "\t\t\t\t\t\t[2] Back" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tSelect Option : ";
    cin >> option;

    switch (option) {
        case 1: {
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tVIEW GADGET LOAN" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\tBrand\tUnit\tPrice\tQuantity" << endl;
            cout << "------------------------------------------------------------------------------------------------------------------------"<<endl;
            chk=0;
            for (int i = 0; i < countProducts; i++) {
                if (product[i].quantityProduct > 0){
                chk=1;
                cout << "\t\t\t\t" << i + 1 << ". " << product[i].brand << " \t" << product[i].unit << " \t" << product[i].price << " \t" << product[i].quantityProduct<< endl;
                }
            }
            if(chk != 1){
                cout<<"\t\t\t\t\t\tNo Gadget Loan yet."<<endl;
            }
            int tempGadgetLoan;
            cout << "\t\t\t\t\t\tSelect a number : ";
            cin >> tempGadgetLoan;
            tempGadgetLoan--;
            if (tempGadgetLoan >= 0 && tempGadgetLoan < countGadgetCateg) {
                system("cls");
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tGADGET DETAILS" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tBrand: " << product[tempGadgetLoan].brand << endl;
                cout << "\t\t\t\t\t\tUnit: " << product[tempGadgetLoan].unit << endl;
                cout << "\t\t\t\t\t\tPrice: " << product[tempGadgetLoan].price << " pesos" << endl;
                cout << "\t\t\t\t\t\tQuantity: " << product[tempGadgetLoan].quantityProduct << endl;
                cout << "\t\t\t\t\t\tDescription: " << product[tempGadgetLoan].display << ", " << product[tempGadgetLoan].body << ", " 
                     << product[tempGadgetLoan].variant << ", " << product[tempGadgetLoan].camera << ", " 
                     << product[tempGadgetLoan].battery << ", " << product[tempGadgetLoan].processor << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\t[1] Apply" << endl;
                cout << "\t\t\t\t\t\t[2] Back" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tSelect Option : ";
                cin >> option;
                switch (option) {
                    case 1:
                        applyFormGadget(tempGadgetLoan);
                        break;
                    case 2:
                        viewGadgetLoan();
                        break;
                    default:
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "\t\t\t\t\t\tInvalid input!" << endl;
                        cout<<"========================================================================================================================"<<endl;
                        cout << "\t\t\t\t\t\tPress Enter to continue...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        viewGadgetLoan();
                        break;
                }
            } else {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                viewGadgetLoan();
            }
            break;
        }
        case 2:
            userViewProducts();
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            viewGadgetLoan();
            break;
    }
}

void applyFormGadget(int tempGadgetLoan) {
    loadApplied();
    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tAPPLY GADGET LOAN" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tPersonal Information" << endl;

    foundUser = false;

    for (int i = 0; i < countUser; i++) {
    if (user[i].username == userLog) {
        foundUser = true;
        int currentUserID = user[i].userid;
        
        applied[countApplied].userID = currentUserID;
        applied[countApplied].brandLoan = product[tempGadgetLoan].brand;
        applied[countApplied].unitLoan = product[tempGadgetLoan].unit;
        applied[countApplied].priceLoan = product[tempGadgetLoan].price;
        // Get the current time
        time_t now = time(0);
        tm *currentTime = localtime(&now);

        // Set the due date to next month
        tm dueDate = *currentTime;
        dueDate.tm_mon += 1; // Increment month by 1
        mktime(&dueDate); // Normalize due date

        // Assign the due date to the applied loan
        applied[countApplied].dueDate = dueDate;
        saveApplied();
        
        bool hasExistingLoan = false;
        for (int j = 0; j < countApplied; j++) {
            if (applied[j].userID == currentUserID) {
                hasExistingLoan = true;
                break;
            }
        }

        if (hasExistingLoan) {
            char choice;
            cout << "\t\t\t\t\t\tYou already have an existing gadget loan."<<endl;
			cout << "\t\t\t\t\t\tAre you sure you want to apply for another one? [Y/N]"<<endl;
			cout<<"========================================================================================================================"<<endl;
			cout << "\t\t\t\t\t\tSelect Option: ";
            cin >> choice;
            if (choice != 'y' && choice != 'Y') {
                cout << "\t\t\t\t\t\tCanceling..." << endl;
                system("pause");
                userHome();
                return;
            } else {
                cout<<"========================================================================================================================"<<endl;
            }
        }
        break;
        }
    }

    
    cin.ignore();
    cout << "\t\t\t\t\t\tFullname: ";
    getline(cin,applied[countApplied].fname);
    cout << "\t\t\t\t\t\tAge: ";
    getline(cin,applied[countApplied].agE);
    cout << "\t\t\t\t\t\tAddress: ";
    getline(cin,applied[countApplied].homeAddress);
    cout << "\t\t\t\t\t\tEnter your Contact : ";
    getline(cin,applied[countApplied].contact);
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tWork Information" << endl;
    cout << "\t\t\t\t\t\tEnter your work : ";
    getline(cin,applied[countApplied].work);
    cout << "\t\t\t\t\t\tEnter monthly Salary : ";
    cin >> applied[countApplied].earnings;
    cout << "\t\t\t\t\t\tEnter work Address : ";
    cin.ignore();
    getline(cin,applied[countApplied].workAddress);
    cout << endl <<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tCharacter Reference : " << endl;
    cout << "\t\t\t\t\t\tEnter the name of other contact : ";
    getline(cin,applied[countApplied].otherName);
    cout << "\t\t\t\t\t\tEnter the number of their number : ";
    cin >> applied[countApplied].otherContact;
    cout<<"========================================================================================================================"<<endl;
    applied[countApplied].loanType = "Gadget";
    applied[countApplied].appliedStatus = "Pending";
    cout << "\t\t\t\t\t\tAre you sure you want to apply? [Y/N] : ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        system("cls");
        int months = 0;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tVIEW MONTHLY PAYMENT" << endl;
        cout<<"========================================================================================================================"<<endl;
        float monthly3 = product[tempGadgetLoan].price / 3;
        float monthly6 = product[tempGadgetLoan].price / 6;
        float monthly9 = product[tempGadgetLoan].price / 9;
        float monthly12 = product[tempGadgetLoan].price / 12;
        float down = 1;
        cout << "\t\t\t\t\t\t[1] 3 Months Monthly Payment " << monthly3 << endl; 
        cout << "\t\t\t\t\t\t[2] 6 Months Monthly Payment " << monthly6 << endl; 
        cout << "\t\t\t\t\t\t[3] 9 Months Monthly Payment " << monthly9 << endl; 
        cout << "\t\t\t\t\t\t[4] 12 Months Monthly Payment " << monthly12 << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "Select Option : ";
        cin >> option;
        if (option == 1){
            system("cls");
            months = 3;
            down = product[tempGadgetLoan].price * .20;
            cout << "=============================================================================================" << endl;
            cout << "\t\t\t\t\t\tYou will pay " << down << " for the Down Payment and " << monthly3 <<endl;
            cout << "\t\t\t\t\t\tEvery month for " << months << " months" << endl;
            applied[countApplied].downpayStatus = "Not yet paid";
            applied[countApplied].monthsPaid = 0;
            applied[countApplied].monthsToPay = months;
            applied[countApplied].monpay = monthly3;
            applied[countApplied].downpay = down;
            system("pause");
        }
        else if (option == 2){
            system("cls");
            months = 6;
            down = product[tempGadgetLoan].price * .30;
            cout << "=============================================================================================" << endl;
            cout << "\t\t\t\t\t\tYou will pay " << down << " for the Down Payment and " << monthly6 << endl;
            cout<<"\t\t\t\t\t\tEvery month for " << months << " months" << endl;
            applied[countApplied].downpayStatus = "Not yet paid";
            applied[countApplied].monthsPaid = 0;
            applied[countApplied].monthsToPay = months;
            applied[countApplied].monpay = monthly6;
            applied[countApplied].downpay = down;
            system("pause");
        }
        else if (option == 3){
            system("cls");
            months = 9;
            down = product[tempGadgetLoan].price * .35;
            cout << "=============================================================================================" << endl;
            cout << "\t\t\t\t\t\tYou will pay " << down << " for the Down Payment and " << monthly9 << endl;
            cout << "\t\t\t\t\t\tEvery month for " << months << " months" << endl;
            applied[countApplied].downpayStatus = "Not yet paid";
            applied[countApplied].monthsPaid = 0;
            applied[countApplied].monthsToPay = months;
            applied[countApplied].monpay = monthly9;
            applied[countApplied].downpay = down;
            system("pause");
        }
        else if (option == 4){
            system("cls");
            months = 12;
            down = product[tempGadgetLoan].price * .40;
            cout << "=============================================================================================" << endl;
            cout << "\t\t\t\t\t\tYou will pay " << down << " for the Down Payment and " << monthly12 << endl;
            cout << "\t\t\t\t\t\tEvery month for " << months << " months" << endl;
            applied[countApplied].downpayStatus = "Not yet paid";
            applied[countApplied].monthsPaid = 0;
            applied[countApplied].monthsToPay = months;
            applied[countApplied].monpay = monthly12;
            applied[countApplied].downpay = down;
            system("pause");
        }
        else {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            viewGadgetLoan();
        }
        cout << "=============================================================================================" << endl;
        cout << "\t\t\t\t\t\tThe Following Requirements needed are: " << endl;
        cout << "\t\t\t\t\t\t[1] Two valid id's" << endl;
        cout << "\t\t\t\t\t\t[2] Proof of billing" << endl;
        cout << "\t\t\t\t\t\t[3] Payslip" << endl;
        cout << "=============================================================================================" << endl;
        cout << "\t\t\t\t\t\tAfter you passed all the requirements. " <<endl;
        cout<< "\t\t\t\t\t\tPlease wait for the approval. Thank you!" << endl;
        cout << "=============================================================================================" << endl;
        product[countProducts].quantityProduct--;
        applied[countApplied].validID = "X";
        applied[countApplied].proofBilling = "X";
        applied[countApplied].paySlip = "X";
        countApplied++;
        saveApplied();
        system("pause");
        userHome();
        return;
    } else {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\t\t\t\t\t\tInvalid input!" << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        userHome();
    }
    
}

void viewMoneyLoan() {
    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tVIEW MONEY LOAN" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\tMoney\tInterest\tQuantity" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------"<<endl;
    chk = 0;
    
    for (int i = 0; i < countMoney; i++) {
        if (money[i].quantityMoney > 0){
            chk=1;
        cout << "\t\t\t\t" << + 1 << ". " << money[i].moneyPrice << " pesos\t" << money[i].interest << "\t" << money[i].quantityMoney << endl;
        }
    }
    if(chk != 1){
        cout<<"\t\t\t\t\t\tNo Money Loan yet."<<endl;
    }
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\t[1] View More" << endl;
    cout << "\t\t\t\t\t\t[2] Back" << endl;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tSelect Option : ";
    cin >> option;

    switch (option) {
        case 1: {
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tVIEW MONEY LOAN" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\tMoney\tInterest\tQuantity" << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            chk = 0;
            for (int i = 0; i < countMoney; i++) {
                if (money[i].quantityMoney > 0){
                    chk=1;
                cout << "\t\t\t\t" << + 1 << ". " << money[i].moneyPrice << " pesos\t" << money[i].interest << "\t" << money[i].quantityMoney << endl;
                }
            }
            if(chk != 1){
                cout<<"\t\t\t\t\t\tNo Money Loan yet."<<endl;
            }
            int tempMoneyLoan;
            cout << "\t\t\t\t\t\tSelect a number : ";
            cin >> tempMoneyLoan;
            tempMoneyLoan--;
            if (tempMoneyLoan >= 0 && tempMoneyLoan < countMoney) {
                system("cls");
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tGADGET DETAILS" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tMoney: " << money[tempMoneyLoan].moneyPrice << endl;
                cout << "\t\t\t\t\t\tInterest: " << money[tempMoneyLoan].interest << endl;
                cout << "\t\t\t\t\t\tQuantity: " << money[tempMoneyLoan].quantityMoney << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\t[1] Apply" << endl;
                cout << "\t\t\t\t\t\t[2] Back" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tSelect Option : ";
                cin >> option;
                switch (option) {
                    case 1:
                        applyFormMoney(tempMoneyLoan);
                        break;
                    case 2:
                        viewMoneyLoan();
                        break;
                    default:
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "\t\t\t\t\t\tInvalid input!" << endl;
                        cout<<"========================================================================================================================"<<endl;
                        cout << "\t\t\t\t\t\tPress Enter to continue...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        viewMoneyLoan();
                }
            } else {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                viewMoneyLoan();
            }
            break;
        }
        case 2:
            userViewProducts();
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            viewMoneyLoan();
            break;
    }
}

void applyFormMoney(int tempMoneyLoan) {
    loadAppliedMoney();
    system("cls");
    int reference = 1;
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tAPPLY MONEY LOAN" << endl;
    cout<<"========================================================================================================================"<<endl;
    
    cout << "\t\t\t\t\t\tPersonal Information" << endl;

   foundUser = false;

    for (int i = 0; i < countUser; i++) {
    if (user[i].username == userLog) {
        foundUser = true;
        int currentUserID = user[i].userid;
        
        appliedMoney[countAppliedMoney].userIDMoney = currentUserID;
        appliedMoney[countAppliedMoney].priceLoanMoney = money[tempMoneyLoan].moneyPrice;
        appliedMoney[countAppliedMoney].interestMoney = money[tempMoneyLoan].interest;
        // Get the current time
        time_t now = time(0);
        tm *currentTime = localtime(&now);

        // Set the due date to next month
        tm dueDate = * currentTime;
        dueDate.tm_mon += 1; // Increment month by 1
        mktime(&dueDate); // Normalize due date

        // Assign the due date to the applied loan
        appliedMoney[countAppliedMoney].dueDateMoney = dueDate;
        saveAppliedMoney();
        
        bool hasExistingLoan = false;
        for (int j = 0; j < countAppliedMoney; j++) {
            if (applied[j].userID == currentUserID) {
                hasExistingLoan = true;
                break;
            }
        }

        if (hasExistingLoan) {
            char choice;
            cout << "\t\t\t\t\t\tYou already have an existing money loan. Are you sure you want to apply for another one? [Y/N]: ";
            cin >> choice;
            if (choice != 'y' && choice != 'Y') {
                cout << "\t\t\t\t\t\tCanceling..." << endl;
                system("pause");
                userHome();
                return;
            } else {
                cout<<"========================================================================================================================"<<endl;
            }
        }
        break;
        }
    }

    
    cin.ignore();
    cout << "\t\t\t\t\t\tFullname: ";
    getline(cin,appliedMoney[countAppliedMoney].fnameMoney);
    cout << "\t\t\t\t\t\tAge: ";
    getline(cin,appliedMoney[countAppliedMoney].agEMoney);
    cout << "\t\t\t\t\t\tAddress: ";
    getline(cin,appliedMoney[countAppliedMoney].homeAddressMoney);
    cout << "\t\t\t\t\t\tEnter your Contact : ";
    getline(cin,appliedMoney[countAppliedMoney].contactMoney);
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tWork Information" << endl;
    cout << "\t\t\t\t\t\tEnter your work : ";
    getline(cin,appliedMoney[countAppliedMoney].workMoney);
    cout << "\t\t\t\t\t\tEnter monthly Salary : ";
    getline(cin,appliedMoney[countAppliedMoney].earningsMoney);
    cout << "\t\t\t\t\t\tEnter work Address : ";
    cin.ignore();
    getline(cin,appliedMoney[countAppliedMoney].workAddressMoney);
    cout << endl <<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tCharacter Reference : " << endl;
    cout << "\t\t\t\t\t\tEnter the name of other contact : ";
    getline(cin,appliedMoney[countAppliedMoney].otherNameMoney);
    cout << "\t\t\t\t\t\tEnter the number of their number : ";
    getline(cin,appliedMoney[countAppliedMoney].otherContactMoney);
    appliedMoney[countAppliedMoney].loanTypeMoney = "Money";
    appliedMoney[countAppliedMoney].appliedStatusMoney = "Pending";
    cout<<"========================================================================================================================"<<endl;
    cout << "\t\t\t\t\t\tAre you sure you want to apply? [Y/N] : ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        system("cls");
        float months = 0;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tVIEW MONTHLY PAYMENT" << endl;
        cout<<"========================================================================================================================"<<endl;
        float monthly3 = money[tempMoneyLoan].moneyPrice / 3;
        float monthly6 = money[tempMoneyLoan].moneyPrice / 6;
        float monthly9 = money[tempMoneyLoan].moneyPrice / 9;
        float monthly12 = money[tempMoneyLoan].moneyPrice / 12;
        cout << "\t\t\t\t\t\t[1] 3 Months Monthly Payment " << monthly3 << endl; 
        cout << "\t\t\t\t\t\t[2] 6 Months Monthly Payment " << monthly6 << endl; 
        cout << "\t\t\t\t\t\t[3] 9 Months Monthly Payment " << monthly9 << endl; 
        cout << "\t\t\t\t\t\t[4] 12 Months Monthly Payment " << monthly12 << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tSelect Option : ";
        cin >> option;
        if (option == 1){
            system("cls");
            months = 3;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tYou will pay " << appliedMoney[countAppliedMoney].interestMoney << " for the Interest and " << monthly3 << endl;
            cout << "\t\t\t\t\t\tEvery month for " << months << " months" << endl;
            cout<<"========================================================================================================================"<<endl;
            appliedMoney[countAppliedMoney].intereststatusMoney = "Not yet paid";
            appliedMoney[countAppliedMoney].monthsPaidMoney = 0;
            appliedMoney[countAppliedMoney].monthsToPayMoney = months;
            appliedMoney[countAppliedMoney].monpayMoney = monthly3;
            system("pause");
        }
        else if (option == 2){
            system("cls");
            months = 6;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tYou will pay " << appliedMoney[countAppliedMoney].interestMoney << " for the Interest and " << monthly6 << endl;
            cout << "\t\t\t\t\t\tEvery month for " << months << " months" << endl;
            cout<<"========================================================================================================================"<<endl;
            appliedMoney[countAppliedMoney].intereststatusMoney = "Not yet paid";
            appliedMoney[countAppliedMoney].monthsPaidMoney = 0;
            appliedMoney[countAppliedMoney].monthsToPayMoney = months;
            appliedMoney[countAppliedMoney].monpayMoney = monthly6;
            system("pause");
        }
        else if (option == 3){
            system("cls");
            months = 9;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tYou will pay " << appliedMoney[countAppliedMoney].interestMoney << " for the Interest and " << monthly9 << endl;
            cout << "\t\t\t\t\t\tEvery month for " << months << " months" << endl;
            cout<<"========================================================================================================================"<<endl;
            appliedMoney[countAppliedMoney].intereststatusMoney = "Not yet paid";
            appliedMoney[countAppliedMoney].monthsPaidMoney = 0;
            appliedMoney[countAppliedMoney].monthsToPayMoney = months;
            appliedMoney[countAppliedMoney].monpayMoney = monthly9;
            system("pause");
        }
        else if (option == 4){
            months = 12;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tYou will pay " << appliedMoney[countAppliedMoney].interestMoney << " for the Interest and " << monthly12 << endl;
            cout << "\t\t\t\t\t\tEvery month for " << months << " months" << endl;
            cout<<"========================================================================================================================"<<endl;
            appliedMoney[countAppliedMoney].intereststatusMoney = "Not yet paid";
            appliedMoney[countAppliedMoney].monthsPaidMoney = 0;
            appliedMoney[countAppliedMoney].monthsToPayMoney = months;
            appliedMoney[countAppliedMoney].monpayMoney = monthly12;
            system("pause");
        }
        else {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            viewMoneyLoan();
        }
        
        cout << "\t\t\t\t\t\tThe Following Requirements needed are: " << endl;
        cout << "\t\t\t\t\t\t[1] Two valid id's" << endl;
        cout << "\t\t\t\t\t\t[2] Proof of billing" << endl;
        cout << "\t\t\t\t\t\t[3] Payslip" << endl;
        cout << "=============================================================================================" << endl;
        cout << "\t\t\t\t\t\tAfter you passed all the requirements. Please wait for the approval. Thank you!" << endl;
        cout << "=============================================================================================" << endl;
        money[countMoney].quantityMoney--;
        appliedMoney[countAppliedMoney].validIDMoney = "X";
        appliedMoney[countAppliedMoney].proofBillingMoney = "X";
        appliedMoney[countAppliedMoney].paySlipMoney = "X";
        countAppliedMoney++;
        saveAppliedMoney();
        system("pause");
        userHome();
        return;
    } else {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\t\t\t\t\t\tInvalid input!" << endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\t\t\t\t\t\tPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        userHome();
        return;
    }
    
}

void transactionHistoryUser(){
    loadUser();
	loadTransactions();
	system("cls");
    int index = -1;
    int tempTransaction =0;
	cout<<"========================================================================================================================"<<endl;
	cout<<"\t\t\t\t\t\tTRANSACTION HISTORY"<<endl;
	cout<<"========================================================================================================================"<<endl;
    cout<<"\t\t\t\tNo.\tLoan Type\tAmount\tStatus"<<endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
    foundUser = false;

    for (int i = 0; i < countUser; i++) {
        if (user[i].username == userLog) {
            foundUser = true;
            int currentUserID = user[i].userid;

            bool hasTransaction = false;
            for(int j = 0; j < countTransactions; j++){
                if(transaction[j].userIDTrans == currentUserID) {
                	hasTransaction = true;
                cout << "\t\t\t\t" << j + 1 << ". " << transaction[j].loanTypeTrans << "\t" << transaction[j].priceTrans << "\t" << transaction[j].statusTrans << endl;
            }
                
            if (!hasTransaction) {
                cout<<"\t\t\t\t\t\tNo transactions for this user yet."<<endl;
                system("pause");
                userHome();
            }
            cout<<"========================================================================================================================"<<endl;
        } 
        }
    }
    if (!foundUser) {
        cout << "\t\t\t\t\t\tUser not found." << endl;
    }
	cout<<"\t\t\t\t\t\t[1] View More"<<endl;
    cout<<"\t\t\t\t\t\t[2] Back"<<endl;
    cout<<"\t\t\t\t\t\tSelect Option: ";
	cin>>option;
	switch(option){
        case 1:
        system("cls");
        cout<<"========================================================================================================================"<<endl;
        cout<<"\t\t\t\t\t\tTRANSACTION HISTORY"<<endl;
        cout<<"========================================================================================================================"<<endl;
        cout<<"\t\t\t\tNo.\tLoan Type\tAmount\tStatus"<<endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
        chk =0;
        foundUser = false;

        for (int i = 0; i < countUser; i++) {
            if (user[i].username == userLog) {
                foundUser = true;
                int currentUserID = user[i].userid;

                bool hasTransaction = false;
                for(int j = 0; j < countTransactions; j++){
                    hasTransaction = true;
                    if(transaction[j].userIDTrans == currentUserID) {
                    cout << "\t\t\t\t" << i + 1 << ". " << transaction[j].loanTypeTrans << "\t" << transaction[j].priceTrans << "\t" << transaction[j].statusTrans << endl;
                }
                    
                if (!hasTransaction) {
                    cout<<"\t\t\t\t\t\tNo transactions for this user yet."<<endl;
                    system("pause");
                    userHome();
                }
                cout<<"========================================================================================================================"<<endl;
            } 
            }
        }
        if (!foundUser) {
            cout << "\t\t\t\t\t\tUser not found." << endl;
        }
        cout<<"========================================================================================================================"<<endl;
        cout<<"\t\t\t\t\t\tSelect number: ";
        cin>>tempTransaction;
            tempTransaction--;
            if (tempTransaction >= 0 && tempTransaction < countTransactions) {
                system("cls");
                cout<<"\t\t\t\t\t\tSELECTED TRANSACTION"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\t\tUser ID: "<< transaction[tempTransaction].userIDTrans << endl;
                cout<<"\t\t\t\t\t\tName: "<< transaction[tempTransaction].fnameTrans << endl;
                cout<<"\t\t\t\t\t\tLoan Type: "<< transaction[tempTransaction].loanTypeTrans << endl;
                cout<<"\t\t\t\t\t\tMonths to pay: "<< transaction[tempTransaction].monthsToPayTrans << " Month(s)" << endl;
                cout<<"\t\t\t\t\t\tMonths Paid: "<< transaction[tempTransaction].monthsPaidTrans << " Month(s)" << endl;
                cout<<"\t\t\t\t\t\tTransacation Date & Time: " << transaction[tempTransaction].dateMade.tm_year + 1900 << "-" // year is since 1900
                << "  " << setfill('0') << transaction[tempTransaction].dateMade.tm_mon + 1 << "-" // month (0-based)
                << "  " << setfill('0') << transaction[tempTransaction].dateMade.tm_mday << " " // day of the month
                << "  " << setfill('0') << transaction[tempTransaction].dateMade.tm_hour << ":" // hour (24-hour format)
                << "  " << setfill('0') << transaction[tempTransaction].dateMade.tm_min << endl;
                cout<<"\t\t\t\t\t\tTransaction Type: "<< transaction[tempTransaction].typeTrans << endl;
                cout<<"\t\t\t\t\t\tTransacation Status: "<< transaction[tempTransaction].statusTrans << endl;
                cout << "\t\t\t\t\t\t[1] Back" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tSelect Option : ";
                cin >> option;
                switch (option) {
                    case 1:
                        transactionHistoryUser();
                        break;
                    default:
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "\t\t\t\t\t\tInvalid input!" << endl;
                        cout<<"========================================================================================================================"<<endl;
                        cout << "\t\t\t\t\t\tPress Enter to continue...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        transactionHistoryUser();
                }
            }else {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                transactionHistoryUser();
            }
            
            break;
		case 2: 
            userHome();
            break;
		default: 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			userHome();
 	}
}

void sortuserAdmin(){
    loadUser();
    bool Found = false;
    option = 0;
    int sortNumber = 0;
    string sortString;
    string tempStatus;
    system("cls");
    cout<<"========================================================================================================================"<<endl;
    cout<<"\t\t\t\t\tSORTING USERS"<<endl;
    cout<<"========================================================================================================================"<<endl;
    cout<<"\t\t\tNo.\tUser ID\tFull Name\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
    Found = false;
    for (int i = 0; i < countUser; i++){
        if(countUser != 0){
            Found = true;
            if (user[i].status == 1){
                tempStatus = "Active";
            } else if (user[i].status == 0){
                tempStatus = "Inactive";
            }
            cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<tempStatus<<endl;
        }
    }
    if (!Found){
        cout<<"\t\t\t\t\t\tNo record found"<<endl;
        system("pause");
        showAllUser();
    }
    cout<<"========================================================================================================================"<<endl;
    cout<<"[1] Sort by No"<<endl;
    cout<<"[2] Sort by UserID"<<endl;
    cout<<"[3] Sort by Full Name"<<endl;
    cout<<"[4] Sort by Age"<<endl;
    cout<<"[5] Sort by Address"<<endl;
    cout<<"[6] Sort by Username"<<endl;
    cout<<"[7] Sort by Password"<<endl;
    cout<<"[8] Sort by Cash"<<endl;
    cout<<"[9] Sort by Status"<<endl;
    cout<<"[10] Back"<<endl;
    cout<<"========================================================================================================================"<<endl;
    cout<<"Select option: ";
    cin>>option;
    switch(option){
        case 1:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\tSORTING BY NO."<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\tNo.\tUserID\tFullName\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            Found = false;
            for (int i = 0; i < countUser; i++){
                if(countUser != 0){
                    Found = true;
                    if (user[i].status == 1){
                        tempStatus = "Active";
                    } else if (user[i].status == 0){
                        tempStatus = "Inactive";
                    }
                    cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<tempStatus<<endl;
                }
            }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo record found"<<endl;
                system("pause");
                sortuserAdmin();
            }
            cout<<"========================================================================================================================"<<endl;
            cout<<"Sort by[1>]: ";
            cin>>sortNumber;
            sortNumber--;
            if (sortNumber >= 0 && sortNumber < countUser){
                system("cls");
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\tSORTING BY NO."<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\tNo.\tUserID\tFullName\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                Found = false;
                for (int i = 0; i < countUser; i++){
                    if(countUser != 0 && i == sortNumber){
                        i = sortNumber;
                        Found = true;
                        if (user[i].status == 1){
                            tempStatus = "Active";
                        } else if (user[i].status == 0){
                            tempStatus = "Inactive";
                        }
                        cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<tempStatus<<endl;
                    }
                    
                }
            } else {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                sortuserAdmin();
            }
            if (!Found){
                    cout<<"\t\t\t\t\t\tNo record found"<<endl;
                    system("pause");
                    sortuserAdmin();
                }
            
            cout<<"Displaying "<<sortNumber + 1<<endl;
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            sortuserAdmin();
        case 2:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\tSORTING BY USERID"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\tNo.\tUser ID\tFull Name\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            Found = false;
            for (int i = 0; i < countUser; i++){
                if(countUser != 0){
                    Found = true;
                    if (user[i].status == 1){
                        tempStatus = "Active";
                    } else if (user[i].status == 0){
                        tempStatus = "Inactive";
                    }
                    cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<user[i].status<<endl;
                }
            }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo record found"<<endl;
                system("pause");
                sortuserAdmin();
            }
            cout<<"========================================================================================================================"<<endl;
            cout<<"Sort by: ";
            cin>>sortNumber;
            if (sortNumber >= 0){
                system("cls");
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\tSORTING BY USERID"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\tNo.\tUserID\tFullName\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                Found = false;
                for (int i = 0; i < countUser; i++){
                    if(user[i].userid == sortNumber){
                        Found = true;
                            if (user[i].status == 1){
                                tempStatus = "Active";
                            } else if (user[i].status == 0){
                                tempStatus = "Inactive";
                            }
                            cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<tempStatus<<endl;
                        }
                    }
            } else {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                sortuserAdmin();
            }
            if (!Found){
                    cout<<"\t\t\t\t\t\tNo record found"<<endl;
                    system("pause");
                    sortuserAdmin();
                }
            cout<<"Displaying user(s) with "<<sortNumber<<" user id"<<endl;
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            sortuserAdmin();
        case 3:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\tSORTING BY FULL NAME"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\tNo.\tUser ID\tFull Name\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            Found = false;
            for (int i = 0; i < countUser; i++){
                if(countUser != 0){
                    Found = true;
                    cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<user[i].status<<endl;
                }
            }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo record found"<<endl;
                system("pause");
                sortuserAdmin();
            }
            cout<<"========================================================================================================================"<<endl;
            cin.ignore();
            cout<<"Sort by: ";
            getline(cin, sortString);
            if (sortString == sortString) {
                system("cls");
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\tSORTING BY FULL NAME"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\tNo.\tUserID\tFullName\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                Found = false;
                for (int i = 0; i < countUser; i++){
                    if(user[i].fullName == sortString){
                        Found = true;
                            if (user[i].status == 1){
                                tempStatus = "Active";
                            } else if (user[i].status == 0){
                                tempStatus = "Inactive";
                            }
                            cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<tempStatus<<endl;
                        }
                    }
                } else {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "\t\t\t\t\t\tInvalid input!" << endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tPress Enter to continue...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    sortuserAdmin();
                }
            if (!Found){
                    cout<<"\t\t\t\t\t\tNo record found"<<endl;
                    system("pause");
                    sortuserAdmin();
                }
            cout<<"Displaying user(s) "<<sortString<<" as full name"<<endl;
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            sortuserAdmin();
        case 4:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\tSORTING BY AGE"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\tNo.\tUser ID\tFull Name\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            Found = false;
            for (int i = 0; i < countUser; i++){
                if(countUser != 0){
                    Found = true;
                    cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<user[i].status<<endl;
                }
            }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo record found"<<endl;
                system("pause");
                showAllUser();
            }
            cout<<"========================================================================================================================"<<endl;
            cout<<"Sort by: ";
            cin>>sortNumber;
            if (sortNumber >= 0){
                system("cls");
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\tSORTING BY AGE"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\tNo.\tUserID\tFullName\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                Found = false;
                for (int i = 0; i < countUser; i++){
                    if(user[i].age == sortNumber){
                        Found = true;
                            if (user[i].status == 1){
                                tempStatus = "Active";
                            } else if (user[i].status == 0){
                                tempStatus = "Inactive";
                            }
                            cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<tempStatus<<endl;
                        }
                    }
            } else {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                sortuserAdmin();
            }
            if (!Found){
                    cout<<"\t\t\t\t\t\tNo record found"<<endl;
                    system("pause");
                    sortuserAdmin();
                }
            cout<<"Displaying user(s) "<<sortNumber<<" of age"<<endl;
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            sortuserAdmin();
        case 5:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\tSORTING BY ADDRESS"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\tNo.\tUser ID\tFull Name\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            Found = false;
            for (int i = 0; i < countUser; i++){
                if(countUser != 0){
                    Found = true;
                    cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<user[i].status<<endl;
                }
            }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo record found"<<endl;
                system("pause");
                showAllUser();
            }
            cout<<"========================================================================================================================"<<endl;
            cin.ignore();
            cout<<"Sort by: ";
            getline(cin, sortString);
            if (sortString == sortString) {
                system("cls");
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\tSORTING BY ADDRESS"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\tNo.\tUserID\tFullName\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                Found = false;
                for (int i = 0; i < countUser; i++){
                    if(user[i].address == sortString){
                        Found = true;
                            if (user[i].status == 1){
                                tempStatus = "Active";
                            } else if (user[i].status == 0){
                                tempStatus = "Inactive";
                            }
                            cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<tempStatus<<endl;
                        }
                    }
            } else {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                sortuserAdmin();
            }
            if (!Found){
                    cout<<"\t\t\t\t\t\tNo record found"<<endl;
                    system("pause");
                    sortuserAdmin();
                }
            cout<<"Displaying user(s) "<<sortString<<" as an address"<<endl;
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            sortuserAdmin();
        case 6:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\tSORTING BY USERNAME"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\tNo.\tUser ID\tFull Name\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            Found = false;
            for (int i = 0; i < countUser; i++){
                if(countUser != 0){
                    Found = true;
                    cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<user[i].status<<endl;
                }
            }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo record found"<<endl;
                system("pause");
                showAllUser();
            }
            cout<<"========================================================================================================================"<<endl;
            cin.ignore();
            cout<<"Sort by: ";
            getline(cin, sortString);
            if (sortString == sortString) {
                system("cls");
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\tSORTING BY USERNAME"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\tNo.\tUserID\tFullName\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                Found = false;
                for (int i = 0; i < countUser; i++){
                    if(user[i].username == sortString){
                        Found = true;
                            if (user[i].status == 1){
                                tempStatus = "Active";
                            } else if (user[i].status == 0){
                                tempStatus = "Inactive";
                            }
                            cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<tempStatus<<endl;
                        }
                    }
            } else {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                sortuserAdmin();
            }
            if (!Found){
                    cout<<"\t\t\t\t\t\tNo record found"<<endl;
                    system("pause");
                    sortuserAdmin();
                }
            cout<<"Displaying user(s) "<<sortString<<" as username"<<endl;
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            sortuserAdmin();
        case 7:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\tSORTING BY PASSWORD"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\tNo.\tUser ID\tFull Name\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            Found = false;
            for (int i = 0; i < countUser; i++){
                if(countUser != 0){
                    Found = true;
                    cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<user[i].status<<endl;
                }
            }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo record found"<<endl;
                system("pause");
                showAllUser();
            }
            cout<<"========================================================================================================================"<<endl;
            cin.ignore();
            cout<<"Sort by: ";
            getline(cin, sortString);
            if (sortString == sortString) {
                system("cls");
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\tSORTING BY PASSWORD"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\tNo.\tUserID\tFullName\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                Found = false;
                for (int i = 0; i < countUser; i++){
                    if(user[i].password == sortString){
                        Found = true;
                            if (user[i].status == 1){
                                tempStatus = "Active";
                            } else if (user[i].status == 0){
                                tempStatus = "Inactive";
                            }
                            cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<tempStatus<<endl;
                        }
                    }
                } else {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "\t\t\t\t\t\tInvalid input!" << endl;
                    cout<<"========================================================================================================================"<<endl;
                    cout << "\t\t\t\t\t\tPress Enter to continue...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    sortuserAdmin();
                }
            if (!Found){
                    cout<<"\t\t\t\t\t\tNo record found"<<endl;
                    system("pause");
                    sortuserAdmin();
                }
            cout<<"Displaying user(s) "<<sortString<<" as password"<<endl;
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            sortuserAdmin();
        case 8:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\tSORTING BY CASH"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\tNo.\tUser ID\tFull Name\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            Found = false;
            for (int i = 0; i < countUser; i++){
                if(countUser != 0){
                    Found = true;
                    cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<user[i].status<<endl;
                }
            }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo record found"<<endl;
                system("pause");
                showAllUser();
            }
            cout<<"========================================================================================================================"<<endl;
            cout<<"Sort by: ";
            cin>>sortNumber;
            if (sortNumber >= 0){
                system("cls");
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\tSORTING BY CASH"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\tNo.\tUserID\tFullName\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                Found = false;
                for (int i = 0; i < countUser; i++){
                    if(user[i].cash == sortNumber){
                        Found = true;
                            if (user[i].status == 1){
                                tempStatus = "Active";
                            } else if (user[i].status == 0){
                                tempStatus = "Inactive";
                            }
                            cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<tempStatus<<endl;
                        }
                    }
            } else {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                sortuserAdmin();
            }
            if (!Found){
                    cout<<"\t\t\t\t\t\tNo record found"<<endl;
                    system("pause");
                    sortuserAdmin();
                }
            cout<<"Displaying user(s) "<<sortNumber<<" of cash"<<endl;
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            sortuserAdmin();
        case 9:
            system("cls");
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\t\t\tSORTING BY STATUS"<<endl;
            cout<<"========================================================================================================================"<<endl;
            cout<<"\t\t\tNo.\tUser ID\tFull Name\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
            Found = false;
            for (int i = 0; i < countUser; i++){
                if(countUser != 0){
                    Found = true;
                    cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<user[i].status<<endl;
                }
            }
            if (!Found){
                cout<<"\t\t\t\t\t\tNo record found"<<endl;
                system("pause");
                showAllUser();
            }
            cout<<"========================================================================================================================"<<endl;
            cout<<"Sort by: ";
            cin>>sortNumber;
            if (sortNumber >= 0){
                system("cls");
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\t\t\tSORTING BY CASH"<<endl;
                cout<<"========================================================================================================================"<<endl;
                cout<<"\t\t\tNo.\tUserID\tFullName\tAge\tAddress\tUsername\tPassword\tCash\tStatus"<<endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------"<<endl;
                Found = false;
                for (int i = 0; i < countUser; i++){
                    if(user[i].cash == sortNumber){
                        Found = true;
                            if (user[i].status == 1){
                                tempStatus = "Active";
                            } else if (user[i].status == 0){
                                tempStatus = "Inactive";
                            }
                            cout<<"\t\t\t"<<i +1<<"\t"<<user[i].userid<<"\t"<<user[i].fullName<<"\t"<<user[i].age<<"\t"<<user[i].address<<"\t"<<user[i].username<<"\t"<<user[i].password<<"\t"<<user[i].cash<<"\t"<<tempStatus<<endl;
                        }
                    }
            } else {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\t\t\t\t\t\tInvalid input!" << endl;
                cout<<"========================================================================================================================"<<endl;
                cout << "\t\t\t\t\t\tPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                sortuserAdmin();
            }
            if (!Found){
                    cout<<"\t\t\t\t\t\tNo record found"<<endl;
                    system("pause");
                    sortuserAdmin();
                }
            cout<<"Displaying user(s) "<<sortNumber<<" of cash"<<endl;
            cout<<"========================================================================================================================"<<endl;
            system("pause");
            sortuserAdmin();
        case 10:
            showAllUser();
            break;
        default:
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\t\t\t\t\t\tInvalid input!" << endl;
            cout<<"========================================================================================================================"<<endl;
            cout << "\t\t\t\t\t\tPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            showAllUser();
        }
        
}
