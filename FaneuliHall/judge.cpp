//
//  judge.cpp
//  FaneuilHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#include "judge.h"

void Judge::visit(std::shared_ptr<Courthouse> c) {
    courthouse = c;
    enter();
    confirm();
    leave();
}

void Judge::enter() {
    courthouse->judgeEntered();
}

void Judge::confirm() {
    {
        std::unique_lock<std::mutex> lk(courthouse->immigrantsMutex);
        courthouse->immigrantsCv.wait(lk, [this](){
            return courthouse->numImmigrantsToCheckIn == 0;});
    }
    {
        std::lock_guard<std::mutex> lk(courthouse->judgeConfirmMutex);
        courthouse->lockedOutput("Judge is confirming\n");
        courthouse->judgeConfirmed = true;
    }
    courthouse->judgeConfirmCv.notify_all();
}

void Judge::leave() {
    courthouse->judgeLeft();
}