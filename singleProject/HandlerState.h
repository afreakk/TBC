#pragma once
namespace OIS
{
	class KeyEvent;
};
template<typename T>
class HandlerState
{
public:
	HandlerState(T thisState) :m_state(thisState), m_originalState(m_state){}
	virtual ~HandlerState()
	{
	}
	virtual void update()=0;
	virtual void keyPressed(const OIS::KeyEvent&){}
	virtual void keyReleased(const OIS::KeyEvent&){}
	T getState()
	{
		return m_state;
	}
	T getOriginalState()
	{
		return m_originalState;
	}
	void setState(T newState)
	{
		m_state = newState;
	}
protected:
	T m_state;
	const T m_originalState;
};