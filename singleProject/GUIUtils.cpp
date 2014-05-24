#include "stdafx.h"
#include "GUIUtils.h"

StringDotter::StringDotter()
: m_string("")
{

}
const std::string& StringDotter::getDot()
{
    if (m_string.length() > 2)
        m_string = "";
    else
        m_string += ".";
	return m_string;
}