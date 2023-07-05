//
// Created by murph on 05.07.23.
//

#ifndef INC_09_HOMEWORK_CONSOLLER_H
#define INC_09_HOMEWORK_CONSOLLER_H

#include <iostream>
#include <vector>
#include "intent.h"

class Consoler: public IObserver {
public:
    Consoler() {
        std::cout << "Consoller:" << std::endl;
    }

    void Update(const std::vector<std::string> &message_from_subject) override{
        std::cout << "bulk:";
        for (const auto& message : message_from_subject) {
            std::cout << (message == *message_from_subject.begin() ? " " : ", ") << message;

        }
        std::cout << std::endl;
    }

};

#endif //INC_09_HOMEWORK_CONSOLLER_H
