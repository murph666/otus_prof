//
// Created by murph on 04.07.23.
//

#ifndef INC_07_HOMEWORK_LOGGER_H
#define INC_07_HOMEWORK_LOGGER_H
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <filesystem>


class Logger {
public:
    Logger() {
        std::filesystem::path directoryPath("log");
        std::filesystem::create_directory(directoryPath);
    }

    ~Logger() {
        if (m_logfile.is_open()) {
            m_logfile.close();
        }
    }


    void writeLog(const std::string& message) {
        if (m_logfile.is_open()) {
            m_logfile << message << std::endl;
        }
    }

    void writeLog(const std::vector<std::string>& messages) {
        std::string currentTimeFormatted = getCurrentTimeFormatted();
        std::cout << "Текущее время в формате HHmmssddMMYYYY: " << currentTimeFormatted << std::endl;
        m_filename = std::string("log/log") + currentTimeFormatted;
        m_logfile.open(m_filename, std::ios::app);
        for (const auto& message : messages) {
            m_logfile << message << std::endl;
        }
        m_logfile.close();
    }

    static std::string getCurrentTimeFormatted() {
        auto currentTime = std::chrono::system_clock::now(); // Получение текущего времени
        auto roundedTime = std::chrono::time_point_cast<std::chrono::seconds>(currentTime); // Округление времени до минут

        // Преобразование времени в строку с нужным форматом
        std::time_t currentTime_t = std::chrono::system_clock::to_time_t(roundedTime);
        std::tm* currentTime_tm = std::localtime(&currentTime_t);
        std::ostringstream oss;
        oss << std::put_time(currentTime_tm, "%H%M%s%d%m%Y");

        return oss.str();
    }


private:
    std::ofstream m_logfile;
    std::string m_filename;
};

#endif //INC_07_HOMEWORK_LOGGER_H
