#pragma once
template <typename T>
inline void vectorRemoveNulls(std::vector<T>* vector)
{
	auto it = vector->begin();
	while(it != vector->end())
	{
		if (!(*it))
		{
			vector->erase(it);
			vectorRemoveNulls(vector);
			return;
		}
		it++;
	}
}