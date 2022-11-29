#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>

class Account{

    public:
        //Length of username 8-15
        std::vector<char> possChar = {a,A,b,B,c,C};
        Account();
        //Randomize bank acc balance
        Account(std::string user, std::string pass, double bal);
        double deposit();
        double withdraw();
        std::vector<Account> sort(std::vector<Account>);
        void printAcc();


    private:
        double balance;
        std::string username;
        std::string password;


};

#endif