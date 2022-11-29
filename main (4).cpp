#include "bank.h"
#include <iostream>

int main(int argc, char**argv){

    std::vector<Account> accList;
    Account acc1("TestAcc","Password123", 1000);
    accList.push_back(acc1);
    accList[0].deposit();


    return 0;
}