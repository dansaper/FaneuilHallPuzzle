//
//  main.cpp
//  FaneuilHall
//
//  Created by Daniel Saper on 7/9/15.
//  Copyright (c) 2015 Daniel Saper. All rights reserved.
//

// Question:  What happens if the application is interrupted while a lock is held by a thread?
// In Java, InterruptedException is thrown, which can be caught and processed.

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include "courthouse.h"
#include "visitor.h"
#include "immigrant.h"
#include "judge.h"
#include "spectator.h"

// void WaitRandom(int maxMilli) {
//     std::mt19937_64 eng{std::random_device{}()};  //  seed 
//     std::uniform_int_distribution<> dist{1, maxMilli};
//     std::this_thread::sleep_for(std::chrono::milliseconds{dist(eng)});
// }


int main(int argc, const char * argv[]) {
    //  OBSOLETE: We ignore the case where multiple judges could come
    //  OBSOLETE: This would require tracking which immigrants were confirmed, instead of assuming everyone who is inside did
    
    std::shared_ptr<Courthouse> courthouse = std::make_shared<Courthouse>();
    
    std::vector<std::unique_ptr<Visitor>> visitors;
    
    for (int i = 1; i < 3; ++i) {
        visitors.push_back(std::move(std::make_unique<Immigrant>()));
    }
    
    for (int i = 1; i < 3; ++i) {
        visitors.push_back(std::move(std::make_unique<Spectator>()));
    }
    
    // visitors.push_back(std::move(std::make_unique<Judge>()));
    visitors.push_back(std::move(std::make_unique<Judge>(10, 10, 10)));

    
    for (int i = 1; i < 3; ++i) {
        visitors.push_back(std::move(std::make_unique<Immigrant>()));
    }
    for (int i = 1; i < 3; ++i) {
        visitors.push_back(std::move(std::make_unique<Spectator>()));
    }
    
    std::vector<std::thread> visitorThreads;
    for (std::unique_ptr<Visitor>& visitor: visitors) {
        // std::thread t([&courthouse](std::unique_ptr<Visitor> v){v->visit(courthouse);}, std::move(visitor));
        visitorThreads.push_back(std::thread([&courthouse](std::unique_ptr<Visitor> v){v->visit(courthouse);}, std::move(visitor)));
    }
    for (auto& t: visitorThreads) 
        t.join();
        // t.detach();
    
    
    // std::this_thread::sleep_for(std::chrono::seconds(15));
}
