#pragma once

enum EventCode
{
	SKIP, QUIT, MV_L, MV_R, MV_U, MV_D
};

struct EventHandleResult
{
	EventCode code;
};

class EventHandler
{
public:
	virtual void setNext(EventHandler* next) = 0;
	virtual EventHandleResult handle() = 0;
};

class BaseEventHandler: public EventHandler
{
public:
	BaseEventHandler();
	~BaseEventHandler();
	void setNext(EventHandler* next) override;
	EventHandleResult handle() override;
private:
	EventHandler* next;
};