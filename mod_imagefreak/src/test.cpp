#include <iostream>
#include <cwchar>
#include <cstdlib>
#include "imagefreak.h"
#include "composite.h"

using namespace std;

void cb(int status, const char *err_msg) {
    cout << "Status: " << status << endl;
}

int main() {
    const clock_t start = clock();

    //for (int i = 0; i < 100; i++)
        //compositeFighter("1", NULL);

    PlayerData player1 = {L"JONNY", "2", 123456789};
    PlayerData player2 = {L"CAROLINA", "2", 2345678};
    compositeScore(&player1, &player2, "test", 0, cb);

    cout << float(clock() - start) / CLOCKS_PER_SEC;

    return 0;
}
