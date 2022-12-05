#ifndef BANK_HPP
#define BANK_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_set>

//defines account to hold coordinate information along with balance and width
class Account{

    public:
        //Character Vector to be used for randomizing of Usernames and Passwords
        std::vector<char> possChar = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','$','@','#','!','?','%'};
		std::string username;
        std::string password;
        std::vector<Account> unsortedAcc;
        sf::Color colour = sf::Color::White;
        int balance;
        int width = 3;
        int x_location = 0;
        int y_location = 0;

	//Constructor for random username and password
	Account(sf::Image Image, int &xOffset){
		//assign random balance for rectangle from 5 to 50 from the top of the window
		this->balance = rand() % (Image.getSize().y - 50) + 5;

		//assign x offset
		this->x_location = xOffset;
		xOffset += 4;
		this->y_location = Image.getSize().y - this->balance;

		//assign account number and password
		std::string randUserName = "";
		std::string randPass = "";
		//srand(time(NULL)+count+1);//Ensures that it is actually random everytime rand is called, otherwise it wasn't truly random, chances of duplicaton are almost impossible
		for (int i = 0; i < (rand() % (15-5) + 5); i++){
			randUserName += possChar[(rand() % (possChar.size()-0) + 0)];
		}
		for (int i = 0; i < (rand() % (15-5) + 5); i++){
			randPass += possChar[(rand() % (possChar.size()-0) + 0)];
		}
	}

		//constructor for user to enter defined username and password
        Account(std::vector<Account> &acc_vec, sf::Image Image, int &xOffset, char* userInfo[], std::vector<sf::Color> &accColor, int &curr){ 
			this->balance = 0;
			this->username = userInfo[curr];
			this->password = userInfo[curr+1];
			curr += 2;

			this->x_location = xOffset;
			xOffset += 4;

			this->colour = accColor[accColor.size()-1];
			accColor.pop_back();
		};

        //Method to deposit into any account
        void deposit(int amount, sf::Image Image){
			this->balance += amount;
			if(this->balance > 1000){
				this->balance = 1000;
			}
			if(this->balance < 5){
				this->balance = 5;
			}
			this->y_location = Image.getSize().y - this->balance;
		};

        //Method to withdraw into any account
        void withdraw(int amount, sf::Image Image){
			this->balance -= amount;
			if(this->balance < 5){
				this->balance = 5;
			}
			this->y_location = Image.getSize().y - this->balance;
		};

        //Prints all info of acc (username, password, and current balance as of date adn time)
        void printAcc(){
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

        //Function to create randomized X (user inputted) number of accounts with random usernames and passwords
        void accGenerator(std::vector<Account> &acc_vec, sf::Image Image, int &xOffset){
			while (xOffset < Image.getSize().x - 49)  // 7 times 4+3 (offset + width) so we can add 7 more accounts 
			{
				Account temp(Image, xOffset);
				acc_vec.push_back(temp);
			}
		};
};

#endif
