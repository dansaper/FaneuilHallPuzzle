//
//  courthouse.h
//  FaneuilHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#ifndef __FaneuilHall__courthouse__
#define __FaneuilHall__courthouse__

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <random>
#include <chrono>

class Courthouse {
private:
    std::mutex judgeMutex;
    std::condition_variable judgeCv;
    std::mutex outputMutex;

    std::mutex immigrantsCalculateMutex;    // used when calculating and comparing immigrant counts, numImmigrantsToCheckIn and numImmigrantsPresent

    std::mutex immigrantsAllPresentMutex;
    std::condition_variable immigrantsAllPresentCv;
    // ** Why don't we use an atomic_integer for numImmigrantsToCheckIn?  We must be certain that the code used to increment and compare numImmigrantsToCheckIn is locked down.
    int numImmigrantsToCheckIn = 0;
    
    std::mutex judgeConfirmedMutex;
    std::condition_variable judgeConfirmedCv;
    bool isJudgeConfirmed = false;

    std::mutex immigrantsAndJudgeClearedMutex;  // used to block new immigrants from enetering after confirmation
    std::condition_variable immigrantsAndJudgeClearedCv;
    bool isImmigrantsAndJudgeCleared = true;    // set to false when the judge enters, true again when the courthouse is cleared
    bool hasJudge = false;

    // sßtd::atomic_int numImmigrantsPresent = 0;   // used to block new immigrants from enetering after confirmation, countdown from the number who checkedin to zero
    int numImmigrantsPresent = 0;   // used to block new immigrants from enetering after confirmation, countdown from the number who checkedin to zero
public:
    
    
    void lockedOutput(std::string s) {
        std::lock_guard<std::mutex> lk(outputMutex);
        std::cout << s;
    }

    
    void judgeEntered();
    void judgeLeft();
    void judgeConfirms();
    void judgeWaitForImmigrantsCheckIn();

    bool immigrantArrived();
    void immigrantCheckedIn();
    void immigrantLeft();
    bool immigrantGetCertificate();
    
    void spectatorArrived();
    
};



#endif /* defined(__FaneuilHall__courthouse__) */
