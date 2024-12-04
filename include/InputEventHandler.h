#pragma once
#include <EventHandler.h>

class InputEventHandler: public BaseEventHandler
{
public:
	InputEventHandler();
	~InputEventHandler();
	EventHandleResult handle() override;
};