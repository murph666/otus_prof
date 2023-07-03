#include "ImageRenderer.h"

#include <Lolibox.h>
#include <Lolibox/EntryPoint.h>

class App : public lolibox::Application
{
public:
	App() : lolibox::Application("Image Processor")
	{
		m_ImageRenderer = std::make_shared<ImageRenderer>();
		AttachRenderModule(m_ImageRenderer);
	}

private:
	std::shared_ptr<ImageRenderer> m_ImageRenderer;
};


lolibox::Application* lolibox::CreateApp()
{
	return new App();
}
