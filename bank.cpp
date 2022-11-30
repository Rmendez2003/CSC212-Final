#include "bank.h"
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib> //for randomizing balance on acc

//Default Constructor
Account::Account(){
    std::string userName, passWord;
};

//Parametarized constructor
Account::Account(std::string user, std::string pass){
    srand(time(NULL)+ (user[0] + user[2]));
    this->username = user;
    this->password = pass;
    this->balance = rand() % (100000-0) + 0;
};


//Prints all most updated information of account
void Account::printAcc(){
    //Current date/time based on current system
    time_t now = std::time(0);

    //Convert now to string form
    char* dt = std::ctime(&now);
    std::cout << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Username: " << this->username << std::endl;
    std::cout << "Password: " << this->password << std::endl;
    std::cout << "Current Balance as of " << dt << "is: " << this->balance << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << std::endl;

};

//Deposits user inputted amount into account
long double Account::deposit(){
    bool depositTrue = false;
    long double depositAmount;
    int count = 0;

    //Ensures that user inputs a valid positive number
    while(depositTrue == false){
        if (count == 0){
            std::cout << "Enter the amount you would like to deposit" << std::endl;
            count++;

        }else{
            std::cout << "Amount has to be more than $0 dollars, try again." << std::endl;
        }
        std::cin >> depositAmount;
        if (depositAmount > 0){
            depositTrue = true;
            this->balance += depositAmount;
        }
    }

    return this->balance;
};


//Withdraws amount specified by the user from the account
long double Account::withdraw(){
    bool withdrawTrue = false;
    long double withdrawAmount;
    int count = 0;

    //Checks that desired withdrawal amount is not more than the balance available
    while(withdrawTrue == false){
        if (count == 0){
            std::cout << "Enter the amount you would like to withdraw" << std::endl;
            count++;

        }else{
            std::cout << "The current balance is " << this->balance << std::endl;
            std::cout << "Amount cannot be more than the available balance, try again." << std::endl;
        }
        std::cin >> withdrawAmount;
        if (withdrawAmount  <= this-> balance){
            withdrawTrue = true;
            this->balance -= withdrawAmount;
        }
    }

    return this->balance;
};

//Generates user specified amount of accounts, with random usernames, passwords, and amounts
//Side Note: We created this because creating 1,000 objects of type account by hand did not sound pleasing
std::vector<Account> Account::accGenerator(){
    int count = 0;

    //Asks user how many accounts they want to generate
    int accNum;
    std::cout << "Enter the number of accounts that you would like to generate: ";
    std::cin >> accNum;
    srand(time(NULL)+count+1);//Ensures that it is actually random everytime rand is called, otherwise it wasn't truly random, chances of duplicaton are almost impossible
    while(count < accNum){
        std::string randUserName = "";
        std::string randPass = "";
        //Populating the username
        for (int i = 0; i < (rand() % (15-5) + 5); i++){
            randUserName += possChar[(rand() % (51-0) + 0)];
            randPass += possChar[(rand() % (51-0) + 0)];
        }
        Account acc1(randUserName,randPass);

        //Pushes newly random created account into a vector of accounts
        unsortedAcc.push_back(acc1);
        count += 1;
    }

    return unsortedAcc;
};



