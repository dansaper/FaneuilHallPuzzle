//
//  judge.cpp
//  FaneuilHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#include "judge.h"

void Judge::visit(std::shared_ptr<Courthouse>& c) {
    courthouse = c;
    std::this_thread::sleep_for(std::chrono::milliseconds(delayEnter));
    enter();
    std::this_thread::sleep_for(std::chrono::milliseconds(delayConfirm));
    confirm();
    std::this_thread::sleep_for(std::chrono::milliseconds(delayLeave));
    leave();
}

void Judge::enter() {
    courthouse->judgeEntered();
}

void Judge::confirm() {
    courthouse->judgeWaitForImmigrantsCheckIn();
    courthouse->judgeConfirms();
}

void Judge::leave() {
    courthouse->judgeLeft();
}