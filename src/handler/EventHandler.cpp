#include <stdio.h>
#include <EventHandler.h>

using namespace std;

BaseEventHandler::BaseEventHandler()
{
}

BaseEventHandler::~BaseEventHandler()
{
}

void BaseEventHandler::setNext(EventHandler* next)
{
	this->next = next;
}

EventHandleResult BaseEventHandler::handle()
{
	if (next != NULL)
	{
		return next->handle();
	}
	return EventHandleResult();
}