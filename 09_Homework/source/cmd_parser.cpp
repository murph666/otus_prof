//
// Created by murph on 26.06.23.
//

#include "cmd_parser.h"

void cmd_parser::exec() {
    if (m_command_stack.empty()) {
        m_command_stack.emplace();
    }

    auto temp_cmd = m_cmdBatch->top();

    auto it = std::find_if(_command_literals.begin(), _command_literals.end(),[=](
            std::basic_string_view<char> i) { return i == temp_cmd;});

    if (it == _command_literals.end()) {
        /* add command to current stack node and pop stack if size > 1 or return result if full */
        auto& cur = m_command_stack.top();
        cur.emplace_back(temp_cmd);

        if (cur.size() == m_batch_size) {
            if (m_command_stack.size() > 1) {
                m_result.insert(m_result.begin(), cur.begin(), cur.end());
                m_command_stack.pop();
            } else if (m_command_stack.size() == 1) {
//                m_logger.writeLog(cur);
                Notify();
                m_result.clear();
                cur.clear();
            }
        }
    }

    switch (it - _command_literals.begin()) {
        case CMD_LT_DYNAMIC_BLOCK_BEGIN: { /* return last result and push stack */
            auto& cur = m_command_stack.top();
            if (m_command_stack.size() == 1 && !cur.empty()) {
                m_result.insert(m_result.end(), cur.begin(), cur.end());
                Notify();
                m_result.clear();
            }
            m_command_stack.emplace();
            break;
        }
        case CMD_LT_DYNAMIC_BLOCK_END: { /* pop stack or return result if stack with 1 element */
            if (m_command_stack.size() > 1) {
                auto& cur = m_command_stack.top();
                m_result.insert(m_result.end(), cur.begin(), cur.end());
                m_command_stack.pop();
            }
            if (m_command_stack.size() == 1) {
                Notify();
                m_result.clear();
                m_command_stack.top().clear();
            }

            break;
        }
        case CMD_LT_END_OF_FILE: { /* return result if stack with 1 element or pop stack */
            if (m_command_stack.size() > 1) {
                m_command_stack.pop();
            } else if (m_command_stack.size() == 1) {
                auto& cur = m_command_stack.top();
                m_result.insert(m_result.end(), cur.begin(), cur.end());
                Notify();
                m_result.clear();
                cur.clear();
            }
            break;
        }
    }
}

