#include "pch.h"
#include "FileSystem.h"

#include "Lolibox/Logger.h"
#include "Lolibox/Application.h"
#include <nfd.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include <stb_image.h>

namespace lolibox
{
	 
	namespace util
	{

		std::string FileToString(const std::string& path)
		{
			std::string os;
			std::ifstream in(path.c_str());
			
			if (in)
			{
				os.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
				in.close();
				return os;
			}
			else
			{
				Logger::Error("Could not read file '%s'", path.c_str());
				in.close();
				return {};
			}
		}

		std::string OpenFileName(const char* filter)
		{
			/*SDL_SysWMinfo wmInfo;
			SDL_VERSION(&wmInfo.version);
			SDL_GetWindowWMInfo(Application::GetInstance().GetWindow()->GetNativeWindow(), &wmInfo);
			HWND hwnd = wmInfo.info.win.window;

			OPENFILENAMEA ofn;
			CHAR szFile[260] = { 0 };
			CHAR currentDir[256] = { 0 };
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			if (GetCurrentDirectoryA(256, currentDir))
				ofn.lpstrInitialDir = currentDir;
			ofn.lpstrFilter = filter;
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

			if (GetOpenFileNameA(&ofn) == TRUE)
				return ofn.lpstrFile;*/

            // TODO: Implement

            NFD_Init();

            nfdchar_t *outPath = nullptr;
            nfdfilteritem_t filterItem {"Images", "*.jpg;*.png;*.bmp"};

            nfdresult_t result = NFD_OpenDialog(&outPath, &filterItem, 1, nullptr);
            if (result == NFD_OKAY)
            {
                puts("Success!");
                puts(outPath);
//                NFD_FreePath(outPath);
                return outPath;
            }
            else if (result == NFD_CANCEL)
            {
                puts("User pressed cancel.");
            }
            else
            {
                printf("Error: %s\n", NFD_GetError());
            }

            NFD_Quit();
            return {};

		}

		std::string SaveFileName(const char* filter, const char* extension)
		{
			/*SDL_SysWMinfo wmInfo;
			SDL_VERSION(&wmInfo.version);
			SDL_GetWindowWMInfo(Application::GetInstance().GetWindow()->GetNativeWindow(), &wmInfo);
			HWND hwnd = wmInfo.info.win.window;

			OPENFILENAMEA ofn;
			CHAR szFile[260] = { 0 };
			CHAR currentDir[256] = { 0 };
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = szFile;
			ofn.lpstrDefExt = extension;
			ofn.nMaxFile = sizeof(szFile);
			if (GetCurrentDirectoryA(256, currentDir))
				ofn.lpstrInitialDir = currentDir;
			ofn.lpstrFilter = filter;
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
			if (GetSaveFileNameA(&ofn) == TRUE)
				return ofn.lpstrFile;*/

            // TODO: Implement

			return {};
		}

	}

}
