#include "pch.h"
#include "Time.h"

namespace lolibox
{

	namespace util
	{

		std::chrono::time_point<std::chrono::system_clock> CurrentTime()
		{
			return std::chrono::system_clock::now();
		}

		std::string CurrentTimeStr()
		{
			std::stringstream ss;
			ss << "Fix Me PLEASE!" << std::endl;
            // FIXME: Implement

			return ss.str();
		}

	}

}

