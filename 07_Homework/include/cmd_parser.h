//
// Created by murph on 26.06.23.
//

#ifndef INC_07_HOMEWORK_CMD_PARSER_H
#define INC_07_HOMEWORK_CMD_PARSER_H

#include <string>
#include <stack>
#include <array>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include "logger.h"
#include "intent.h"
#include <list>

class cmd_parser: public ISubject {
public:
    explicit cmd_parser(std::stack<std::string> *arg_batch, const size_t arg_size) : m_cmdBatch(arg_batch),
                                                                                     m_batch_size(arg_size) {
    };

    void Attach(IObserver *observer) override {
        m_list_observer.push_back(observer);
    }
    void Detach(IObserver *observer) override {
        m_list_observer.remove(observer);
    }
    void Notify() override {
        std::list<IObserver *>::iterator iterator = m_list_observer.begin();
        while (iterator != m_list_observer.end()) {
            (*iterator)->Update(m_result);
            ++iterator;
        }
    }

    void exec();

private:
    enum _command_literal_types : size_t {
        CMD_LT_DYNAMIC_BLOCK_BEGIN = 0,
        CMD_LT_DYNAMIC_BLOCK_END,
        CMD_LT_END_OF_FILE,

        CMD_LT_COUNT
    };

    static constexpr std::array<std::string_view, CMD_LT_COUNT> _command_literals = {
            "{",
            "}",
            "EOF"
    };

    std::stack<std::string> *m_cmdBatch;
    size_t m_batch_size;
    std::stack<std::vector<std::string>> m_command_stack;
    std::vector<std::string> m_result;
    Logger m_logger;

    std::list<IObserver *> m_list_observer;

};


#endif //INC_07_HOMEWORK_CMD_PARSER_H
