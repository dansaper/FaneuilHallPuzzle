//
//  immigrant.cpp
//  FaneuilHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#include "immigrant.h"

void Immigrant::visit(std::shared_ptr<Courthouse> c) {
    courthouse = c;
    
    if (enter()) {
        checkIn();
        sitDown();
        swear();
        getCertificate();
        leave();
    }
}

bool Immigrant::enter() {
    return courthouse->immigrantArrived();
}

void Immigrant::checkIn() {
    courthouse->immigrantCheckedIn();
}

void Immigrant::sitDown() {
    courthouse->lockedOutput("Immigrant sat down\n");
}

void Immigrant::swear() {
    courthouse->lockedOutput("Immigrant swore\n");
}

void Immigrant::getCertificate() {
    {
        std::unique_lock<std::mutex> lk(courthouse->judgeConfirmMutex);
        
        //Wait for judge to confirm. If too much time passes, assume no judge is coming and give up
        if (courthouse->immigrantsCv.wait_for(lk, std::chrono::seconds(10), [this](){return courthouse->judgeConfirmed;})) {
            courthouse->lockedOutput("Immigrant got certificate!\n");
        }
        else {
            courthouse->lockedOutput("No Judge, so Immigrant is rejected!\n");
        }
    }
    
}

void Immigrant::leave() {
    courthouse->lockedOutput("Immigrant Left\n");
}
