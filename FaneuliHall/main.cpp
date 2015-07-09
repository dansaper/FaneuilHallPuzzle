//
//  main.cpp
//  FaneuliHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include "courthouse.h"
#include "visitor.h"
#include "immigrant.h"
#include "judge.h"
#include "spectator.h"

int main(int argc, const char * argv[]) {
    //We ignore the case where multiple judges could come
    //  This would require tracking which immigrants were confirmed, instead of assuming everyone who is inside did
    
    std::shared_ptr<Courthouse> courthouse = std::make_shared<Courthouse>();
    
    std::vector<std::unique_ptr<Visitor>> visitors;
    
    for (int i = 1; i < 3; ++i) {
        visitors.push_back(std::move(std::make_unique<Immigrant>()));
    }
    
    for (int i = 1; i < 3; ++i) {
        visitors.push_back(std::move(std::make_unique<Spectator>()));
    }
    
    visitors.push_back(std::move(std::make_unique<Judge>()));

    
    for (int i = 1; i < 3; ++i) {
        visitors.push_back(std::move(std::make_unique<Immigrant>()));
    }
    for (int i = 1; i < 3; ++i) {
        visitors.push_back(std::move(std::make_unique<Spectator>()));
    }
    
    for (std::unique_ptr<Visitor>& visitor: visitors) {
        std::thread t([&courthouse](std::unique_ptr<Visitor> v){v->visit(courthouse);}, std::move(visitor));
        t.detach();
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(15));
}
