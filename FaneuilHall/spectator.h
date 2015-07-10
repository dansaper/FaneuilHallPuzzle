//
//  spectator.h
//  FaneuilHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#ifndef __FaneuilHall__spectator__
#define __FaneuilHall__spectator__

#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "visitor.h"
#include "courthouse.h"

class Spectator: public Visitor {
    
public:
    virtual void visit(std::shared_ptr<Courthouse>);
    
    void enter();
    void spectate();
    void leave();
};

#endif /* defined(__FaneuilHall__spectator__) */
