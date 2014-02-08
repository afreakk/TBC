#pragma once
#include "stdafx.h"
#include "MessageSubscriber.h"
template <typename T>
class Messager
{
public:
	void registerSubscriber(MessageSubscriber<T>* newSubscriber, string id)
	{
		m_subscribers[id] = newSubscriber;
		newSubscriber->notify(message());
	}
	void removeSubscriber(string id)
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
	std::map< string, MessageSubscriber<T>* > m_subscribers;
};

