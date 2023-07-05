//
// Created by murph on 26.06.23.
//

#include <stack>
#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "cmd_parser.h"

int main([[maybe_unused]]int argc, [[maybe_unused]] const char* const* argv) {
    std::stack<std::string> batch;
    size_t batch_size = 3;

    cmd_parser cmdParser(&batch, batch_size);
    Logger logger;
    cmdParser.Attach(&logger);

    std::string cmd;
    while (std::getline(std::cin, cmd)) {
        if (!cmd.empty()) {
            batch.push(cmd);
            cmdParser.exec();
        }
    }
    return EXIT_SUCCESS;
}