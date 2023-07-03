#pragma once

namespace lolibox
{

	namespace util
	{

		std::chrono::time_point<std::chrono::system_clock> CurrentTime();
		std::string CurrentTimeStr();

	}

}