#include "pch.h"
#include "NativeMessages.h"

namespace lolibox
{

	namespace native
	{

		int showErrorMessageBox(std::string title, std::string content)
		{
			/*int mbID = MessageBoxA(
				NULL,
				(LPCSTR)content.c_str(),
				(LPCSTR)title.c_str(),
				MB_ICONERROR | MB_OK
			);

			return mbID;*/

            return 0; // FIXME: implement
		}

	}

}