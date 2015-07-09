//
//  visitor.h
//  FaneuliHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#ifndef __FaneuliHall__visitor__
#define __FaneuliHall__visitor__

#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include "courthouse.h"

class Visitor {
  
public:
    std::shared_ptr<Courthouse> courthouse;
    
    virtual void visit(std::shared_ptr<Courthouse>) = 0;
    
};

#endif /* defined(__FaneuliHall__visitor__) */
