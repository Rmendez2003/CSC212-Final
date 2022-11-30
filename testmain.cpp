#include "bank.h"
#include <iostream>

int main(int argc, char**argv){

    std::vector<Account> accList;
    Account acc1("TestAcc","Password123");
    acc1.accGenerator();
    return 0;
}
