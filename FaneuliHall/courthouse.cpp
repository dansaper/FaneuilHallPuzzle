//
//  courthouse.cpp
//  FaneuliHall
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


bool Courthouse::immigrantArrived() {
    {
        std::unique_lock<std::mutex> lk(judgeMutex);
        std::unique_lock<std::mutex> lk2(judgeConfirmMutex);
        if (hasJudge || judgeConfirmed) {
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

void Courthouse::immigrantLeft() {
    {
        std::unique_lock<std::mutex> lk(judgeMutex);
        lockedOutput("Immigrant left\n");
        judgeCv.wait(lk, [this](){return !hasJudge;});
    }
}

void Courthouse::spectatorArrived() {
    {
        std::unique_lock<std::mutex> lk(judgeMutex);
        lockedOutput("Spectator Arrived\n");
        judgeCv.wait(lk, [this](){return !hasJudge;});
    }
}





