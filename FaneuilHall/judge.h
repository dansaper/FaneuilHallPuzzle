//
//  judge.h
//  FaneuilHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#ifndef __FaneuilHall__judge__
#define __FaneuilHall__judge__

#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include "visitor.h"
#include "courthouse.h"

class Judge: public Visitor {
    
private:
 	int delayEnter = 0, delayConfirm = 0, delayLeave = 0;
 public:
	Judge()  {};
	Judge(int dEnter, int dConfirm, int dLeave)  {
		delayEnter =(dEnter);
		delayConfirm =(dConfirm);
		delayLeave= (dLeave);
  	};
    virtual void visit(std::shared_ptr<Courthouse>&);
    
    void enter();
    void confirm();
    void leave();
};


#endif /* defined(__FaneuilHall__judge__) */
