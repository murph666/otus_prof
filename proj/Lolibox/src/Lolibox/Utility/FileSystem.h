#pragma once

#include <glm/glm.hpp>

namespace lolibox
{

	namespace util
	{
		constexpr const char* FS_OPEN_FILTER_IMAGE = "All Formats (*.*)\0*.*\0PNG (*.PNG)\0*.PNG\0JPEG (*.JPEG;*.JPG;*.JPE)\0*.JPEG;*.JPG;*.JPE";
		constexpr const char* FS_SAVE_FILTER_IMAGE_PNG = "PNG (*.PNG)\0*.PNG";

		std::string FileToString(const std::string& path);

		std::string OpenFileName(const char* filter = nullptr);

		std::string SaveFileName(const char* filter, const char* extension);

	}

}
