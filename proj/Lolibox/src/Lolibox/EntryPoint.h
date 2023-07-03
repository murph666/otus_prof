#pragma once

#include "Application.h"

extern lolibox::Application* lolibox::CreateApp();

int main(int argc, char** argv)
{
	auto app = lolibox::CreateApp();
	app->Run();
	delete app;

	return 0;
}

