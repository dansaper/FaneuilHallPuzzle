//
//  courthouse.cpp
//  FaneuilHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#include "courthouse.h"

// extend to case when there can be more than one confirmation with different judges during the day.
void Courthouse::judgeEntered() {
    {
        std::unique_lock<std::mutex> lk(judgeMutex);
        immigrantsAndJudgeClearedCv.wait(lk, [this](){return !hasJudge && isImmigrantsAndJudgeCleared;});
        hasJudge = true;
        isImmigrantsAndJudgeCleared = false;
        isJudgeConfirmed = false;  
        lockedOutput("Judge Entered\n");
    }
    
    judgeCv.notify_all();
}

void Courthouse::judgeLeft() {
    {
        std::lock_guard<std::mutex> lk(judgeMutex);
        lockedOutput("Judge Left\n");
        hasJudge = false;
    }
    
    judgeCv.notify_all();
    if (numImmigrantsPresent == 0) {
        isImmigrantsAndJudgeCleared = true;
        isJudgeConfirmed = false;
        immigrantsAndJudgeClearedCv.notify_all();   // it's possible that the immigrants have all left too, so notify
    }
}

void Courthouse::judgeWaitForImmigrantsCheckIn() {
    lockedOutput("judge waiting to confirm\n");
    std::unique_lock<std::mutex> lk(immigrantsAllPresentMutex);
    immigrantsAllPresentCv.wait(lk, [this](){
        return numImmigrantsToCheckIn == 0;});
}

void Courthouse::judgeConfirms() {
    lockedOutput("judge about to confirm\n");
    {
        std::lock_guard<std::mutex> lk(judgeConfirmedMutex);
        lockedOutput("Judge is confirming\n");
        isJudgeConfirmed = true;
    }
    judgeConfirmedCv.notify_all();
}

bool Courthouse::immigrantArrived() {
    {
        std::unique_lock<std::mutex> lk(judgeMutex);
        // std::unique_lock<std::mutex> lk2(judgeConfirmedMutex);
        // if (hasJudge || isJudgeConfirmed) {
        //     lockedOutput("Immigrant rejected because they missed the judge\n");
        //     return false; //You missed your chance today - try again tomorrow
        // }
        immigrantsAndJudgeClearedCv.wait_for(lk, std::chrono::seconds(1), [this](){return !hasJudge && isImmigrantsAndJudgeCleared;});  
        isJudgeConfirmed = false;  // judge clearly isn't present, so make sure that the isJudgeConfirmed flag is false.
    }
    {
        std::lock_guard<std::mutex> lk(immigrantsCalculateMutex);
        lockedOutput("Immigrant arrived\n");
        ++numImmigrantsToCheckIn;
        ++numImmigrantsPresent; // used later in conjunction with clearing out the house.
    }
    return true;
}

void Courthouse::immigrantCheckedIn() {
    {
        std::lock_guard<std::mutex> lk(immigrantsCalculateMutex);
        lockedOutput("Immigrant checked in\n");
        --numImmigrantsToCheckIn;
    }
    immigrantsAllPresentCv.notify_all();
}

bool Courthouse::immigrantGetCertificate() {
    std::unique_lock<std::mutex> lk(judgeConfirmedMutex);
    
    //Wait for judge to confirm. If too much time passes, assume no judge is coming and give up
    // return judgeConfirmedCv.wait(lk, [this](){return isJudgeConfirmed;});    
    return judgeConfirmedCv.wait_for(lk, std::chrono::seconds(10), [this](){return isJudgeConfirmed;});    
    // auto now = std::chrono::system_clock::now();
    // return immigrantsAllPresentCv.wait_until(lk, now+std::chrono::seconds(10), [this](){return isJudgeConfirmed;});    
}

void Courthouse::immigrantLeft() {
    {
        std::unique_lock<std::mutex> lk(judgeMutex);
        judgeCv.wait(lk, [this](){return !hasJudge;});
        lockedOutput("Immigrant left\n");
    }

    // count down the number of immigrants left.
    {
        std::lock_guard<std::mutex> lk(immigrantsCalculateMutex);
        numImmigrantsPresent--; // this is NOT an atomic integer
        if (numImmigrantsPresent == 0) {
            if (!hasJudge)
                isImmigrantsAndJudgeCleared = false;
            immigrantsAndJudgeClearedCv.notify_all();
        }
    }
}

void Courthouse::spectatorArrived() {
    std::unique_lock<std::mutex> lk(judgeMutex);
    judgeCv.wait(lk, [this](){return !hasJudge;});
    lockedOutput("Spectator Arrived\n");
}





