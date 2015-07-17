//
//  spectator.cpp
//  FaneuilHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#include "spectator.h"


void Spectator::visit(std::shared_ptr<Courthouse>& c) {
    courthouse = c;
    enter();
    spectate();
    leave();
}

void Spectator::enter() {
    return courthouse->spectatorArrived();
}

void Spectator::spectate() {
    courthouse->lockedOutput("Spectating\n");
    // std::this_thread::sleep_for(std::chrono::seconds(5));
    courthouse->lockedOutput("Ending spectating\n");
}

void Spectator::leave() {
    
}