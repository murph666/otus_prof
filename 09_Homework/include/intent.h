//
// Created by murph on 05.07.23.
//

#ifndef INC_09_HOMEWORK_INTENT_H
#define INC_09_HOMEWORK_INTENT_H

#include <string>

class IObserver {
public:
    virtual ~IObserver()= default;
    virtual void Update(const std::vector<std::string> &message_from_subject) = 0;
};


class ISubject {
public:
    virtual ~ISubject(){};
    virtual void Attach(IObserver *observer) = 0;
    virtual void Detach(IObserver *observer) = 0;
    virtual void Notify() = 0;
};

#endif //INC_09_HOMEWORK_INTENT_H
