//
//  courthouse.cpp
//  FaneuilHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#include "courthouse.h"

void Courthouse::judgeEntered() {
    {
        std::lock_guard<std::mutex> lk(judgeMutex);
        lockedOutput("Judge Entered\n");
        hasJudge = true;
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
}

void Courthouse::judgeWaitForImmigrantsCheckIn() {
    std::unique_lock<std::mutex> lk(immigrantsMutex);
    immigrantsCv.wait(lk, [this](){
    return numImmigrantsToCheckIn == 0;});
}

void Courthouse::judgeConfirms() {
    {
        std::lock_guard<std::mutex> lk(judgeConfirmMutex);
        lockedOutput("Judge is confirming\n");
        isJudgeConfirmed = true;
    }
    judgeConfirmCv.notify_all();
}

bool Courthouse::immigrantArrived() {
    {
        std::unique_lock<std::mutex> lk(judgeMutex);
        std::unique_lock<std::mutex> lk2(judgeConfirmMutex);
        if (hasJudge || isJudgeConfirmed) {
            lockedOutput("Immigrant rejected because they missed the judge\n");
            return false; //You missed your chance today - try again tomorrow
        }
        else {
            {
                std::lock_guard<std::mutex> lk(immigrantsMutex);
                lockedOutput("Immigrant arrived\n");
                ++numImmigrantsToCheckIn;
            }
            return true;
        }
    }
}

void Courthouse::immigrantCheckedIn() {
    {
        std::lock_guard<std::mutex> lk(immigrantsMutex);
        lockedOutput("Immigrant checked in\n");
        --numImmigrantsToCheckIn;
    }
    immigrantsCv.notify_all();
}

bool Courthouse::immigrantGetCertificate() {
    std::unique_lock<std::mutex> lk(judgeConfirmMutex);
    
    //Wait for judge to confirm. If too much time passes, assume no judge is coming and give up
    return immigrantsCv.wait_for(lk, std::chrono::seconds(10), [this](){return isJudgeConfirmed;});    
}

void Courthouse::immigrantLeft() {
    std::unique_lock<std::mutex> lk(judgeMutex);
    lockedOutput("Immigrant left\n");
    judgeCv.wait(lk, [this](){return !hasJudge;});
}

void Courthouse::spectatorArrived() {
    std::unique_lock<std::mutex> lk(judgeMutex);
    lockedOutput("Spectator Arrived\n");
    judgeCv.wait(lk, [this](){return !hasJudge;});
}





