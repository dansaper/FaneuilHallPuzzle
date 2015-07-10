//
//  immigrant.h
//  FaneuilHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#ifndef __FaneuilHall__immigrant__
#define __FaneuilHall__immigrant__

#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "visitor.h"
#include "courthouse.h"

class Immigrant: public Visitor {
    
public:
    virtual void visit(std::shared_ptr<Courthouse>);

    bool enter();
    void checkIn();
    void sitDown();
    void swear();
    void getCertificate();
    void leave();
};



#endif /* defined(__FaneuilHall__immigrant__) */
