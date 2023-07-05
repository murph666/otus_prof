//
// Created by murph on 05.07.23.
//

#ifndef INC_09_HOMEWORK_COMMANPROCESSOR_H
#define INC_09_HOMEWORK_COMMANPROCESSOR_H

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

class CommandProcessor {
public:
    CommandProcessor() : stop(false) {}

    void startProcessing() {
        m_thread1 = std::thread(&CommandProcessor::processCommands, this);
        m_thread2 = std::thread(&CommandProcessor::processCommands, this);
    }

    void stopProcessing() {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            stop = true;
        }
        m_cv.notify_all();
        m_thread1.join();
        m_thread2.join();
    }

    void addCommand(const std::string& command) {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_commandQueue.push(command);
        }
        m_cv.notify_all();
    }

private:
    void processCommands() {
        while (true) {
            std::string command;
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                m_cv.wait(lock, [this] { return !m_commandQueue.empty() || stop; });
                if (stop) {
                    break;
                }
                command = m_commandQueue.front();
                m_commandQueue.pop();
            }
            // Обработка команды
            std::cout << "Processing command: " << command << std::endl;
        }
    }

    std::thread m_thread1;
    std::thread m_thread2;
    std::queue<std::string> m_commandQueue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool stop;
};

#endif //INC_09_HOMEWORK_COMMANPROCESSOR_H
