//
//  judge.h
//  FaneuliHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#ifndef __FaneuliHall__judge__
#define __FaneuliHall__judge__

#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include "visitor.h"
#include "courthouse.h"

class Judge: public Visitor {
    
public:
    virtual void visit(std::shared_ptr<Courthouse>);
    
    void enter();
    void confirm();
    void leave();
};


#endif /* defined(__FaneuliHall__judge__) */
