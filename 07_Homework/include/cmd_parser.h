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

class cmd_parser {
public:
    explicit cmd_parser(std::stack<std::string> *arg_batch, const size_t arg_size) : m_cmdBatch(arg_batch),
                                                                                     m_batch_size(arg_size) {

    };

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

    static void print_result(const std::vector<std::string> &node) {
        std::cout << "bulk:";
        for (auto &i: node) {
            std::cout << (i == *node.begin() ? " " : ", ") << i;
        }
        std::cout << std::endl;
    }

    std::stack<std::string> *m_cmdBatch;
    size_t m_batch_size;
    std::stack<std::vector<std::string>> m_command_stack;
    std::vector<std::string> m_result;
    Logger m_logger;
};


#endif //INC_07_HOMEWORK_CMD_PARSER_H
