#pragma once

class StringDotter
{
public:
	StringDotter();
	const std::string& getDot();
private:
	std::string m_string;
};