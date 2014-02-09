#pragma once
template <typename T>
class MessageSubscriber
{
public:
	virtual void notify(T) = 0;

};

