#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <map>
#include "log.h"
#define LEVEL LOG_LEVEL_WARNING
using namespace std;

class ThreeDoor{
private:
    int correctDoor;
    int doorNum;
    map<int,float> remainDoors;
    int selectedDoor = -1;
    int deletedDoor = -1;

public:
    ThreeDoor(int n) {
        doorNum = n;
        correctDoor = ensureCorrectDoor(n);
        // remainDoors = new int[n];
        for(int i = 0; i < n ; i ++) 
            remainDoors[i] = 1.0 / n;
    }
    void startGame();
    int ensureCorrectDoor(int n);
    void selectDoor();
    void deleteDoor();
    void retryProbability();
    void displayAllProbabilities();
    bool isWin = false;
    void displayRemain();
    void getAllProbabilities();
    void displayGameProcess(int a);
};

