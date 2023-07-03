#pragma once

#include "PingPong.h"

#include <Lolibox.h>

class ImageRenderer : public lolibox::RenderModule
{
public:
	ImageRenderer();
	~ImageRenderer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnUiUpdate() override;

private:
	void Draw();

	std::unique_ptr<PingPong> m_PingPong;
};

