#include <iostream>
#include <cwchar>
#include "imagefreak.h"
#include "composite.h"

using namespace std;

void cb(int status, const char *err_msg) {
    cout << "Status: " << status << endl;
}

int main() {
    //composite_fighter("1");

    PlayerData player1 = {L"JONNY", "1", 123456789};
    PlayerData player2 = {L"CAROLINA", "1", 2345678};
    compositeScore(&player1, &player2, "final", 0, cb);

    return 0;
}
