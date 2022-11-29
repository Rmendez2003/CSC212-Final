#include "bank.h"
#include <string>
#include <vector>
#include <iostream>
#include <ctime>

Account::Account(){
    std::string userName, passWord;
};

Account::Account(std::string user, std::string pass, double bal){
    this->username = user;
    this->password = pass;
    this->balance = bal;
};

void Account::printAcc(){
    // current date/time based on current system
   time_t now = std::time(0);

   // convert now to string form
   char* dt = std::ctime(&now);
   std::cout << std::endl;
    std::cout << "-----------------------------" << std::endl;
    // std::cout << "Username: " << this->username << std::endl;
    // std::cout << "Password: " << this->password << std::endl;
    std::cout << "Current Balance as of " << dt << "is: " << this->balance << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << std::endl;

};

double Account::deposit(){
    bool depositTrue = false;
    double depositAmount;
    int count = 0;
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

double Account::withdraw(){
    bool withdrawTrue = false;
    double withdrawAmount;
    int count = 0;
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

