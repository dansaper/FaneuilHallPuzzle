//
//  immigrant.cpp
//  FaneuilHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#include "immigrant.h"

void Immigrant::visit(std::shared_ptr<Courthouse>& c) {
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
    if (courthouse->immigrantGetCertificate())
    {
        courthouse->lockedOutput("Immigrant got certificate!\n");
    }
    else {
        courthouse->lockedOutput("No Judge, so Immigrant is rejected!\n");
    }
    
}

void Immigrant::leave() {
    courthouse->lockedOutput("Immigrant Left\n");
}
