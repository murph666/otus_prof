#include <stack>
#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>



namespace hm {

    using cmd_t = std::string;
    using cmd_node_t = std::vector<cmd_t>;
    using batch_size_t = size_t;

    class cmd_batch {
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

    public:
        explicit cmd_batch(batch_size_t batch_size) : m_batch_size(batch_size) {}

        batch_size_t parse_command(const std::string& cmd) {
            if (m_command_stack.empty()) {
                m_command_stack.emplace();
            }

            auto it = std::find_if(_command_literals.begin(), _command_literals.end(),[=](const std::string_view& i) { return i == cmd; });

            if (it == _command_literals.end()) {
                /* add command to current stack node and pop stack if size > 1 or return result if full */
                auto& cur = m_command_stack.top();
                cur.emplace_back(cmd);

                if (cur.size() == m_batch_size) {
                    if (m_command_stack.size() > 1) {
                        m_result.insert(m_result.begin(), cur.begin(), cur.end());
                        m_command_stack.pop();
                    } else if (m_command_stack.size() == 1) {
                        print_result(cur);
                        m_result.clear();
                        cur.clear();
                    }
                }

                return m_command_stack.size();
            }

            switch (it - _command_literals.begin()) {
                case CMD_LT_DYNAMIC_BLOCK_BEGIN: { /* return last result and push stack */
                    auto& cur = m_command_stack.top();
                    if (m_command_stack.size() == 1 && !cur.empty()) {
                        print_result(cur);
                        cur.clear();
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
                        print_result(m_result);
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
                        print_result(m_result);
                        m_result.clear();
                        cur.clear();
                    }
                    break;
                }
            }

            return m_command_stack.size();
        }

    private:
        static void print_result(const cmd_node_t& node) {
            std::cout << "bulk:";
            for (auto& i: node) {
                std::cout << (i == *node.begin() ? " " : ", ") << i;
            }
            std::cout << std::endl;
        }

    private:
        batch_size_t m_batch_size;
        std::stack<cmd_node_t> m_command_stack; //LIFO
        cmd_node_t m_result;
    };
}


int main([[maybe_unused]]int argc, [[maybe_unused]] const char* const* argv) {
    hm::cmd_t cmd;
//    hm::batch_size_t size = std::stoi(argv[1]);
    hm::batch_size_t size = 3;
    auto batch = hm::cmd_batch(size);

    while (cmd != "q") {
        std::cin >> cmd;
        if (!cmd.empty()) {
            batch.parse_command(cmd);
        }
    }

    return EXIT_SUCCESS;
}
