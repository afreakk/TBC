#pragma once
#include "MessageSubscriber.h"
#include <string>
template <typename T>
class Messager
{
public:
	void registerSubscriber(MessageSubscriber<T>* newSubscriber, std::string id)
	{
		m_subscribers[id] = newSubscriber;
		newSubscriber->notify(message());
	}
	void removeSubscriber(std::string id)
	{
		m_subscribers.erase(id);
	}
	void notifySubscribers()
	{
		for (auto& subscriber : m_subscribers)
			subscriber.second->notify(message());
	}
	virtual const T message() = 0;
protected:
	std::map< std::string, MessageSubscriber<T>* > m_subscribers;
};

