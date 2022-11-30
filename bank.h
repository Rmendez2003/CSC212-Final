#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>

class Account{

    public:
        //Character Vector to be used for randomizing of Usernames and Passwords
        std::vector<char> possChar = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        //Constructor
        Account();
        Account(std::string user, std::string pass);

        //Method to deposit into any account
        long double deposit();

        //Method to withdraw into any account
        long double withdraw();

        //Prints all info of acc (username, password, and current balance as of date adn time)
        void printAcc();

        //Function to create randomized X (user inputted) number of accounts with random usernames and passwords
        std::vector<Account> accGenerator();

    private:
        long double balance;
        std::string username;
        std::string password;
        std::vector<Account> unsortedAcc;



};

#endif
