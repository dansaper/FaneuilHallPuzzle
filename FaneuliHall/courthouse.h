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

class Courthouse {
    std::mutex judgeMutex;
    std::condition_variable judgeCv;
    bool hasJudge = false;
public:
    
    std::mutex outputMutex;
    
    void lockedOutput(std::string s) {
        std::lock_guard<std::mutex> lk(outputMutex);
        std::cout << s;
    }

    
    void judgeEntered();
    void judgeLeft();

    std::mutex immigrantsMutex;
    std::condition_variable immigrantsCv;
    int numImmigrantsToCheckIn = 0;
    
    bool immigrantArrived();
    void immigrantCheckedIn();
    void immigrantLeft();
    
    void spectatorArrived();
    
    std::mutex judgeConfirmMutex;
    std::condition_variable judgeConfirmCv;
    bool judgeConfirmed = false;
};



#endif /* defined(__FaneuilHall__courthouse__) */
