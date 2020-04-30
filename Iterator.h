#pragma once
template <class KEY, class T>
class Iterator
{

public:
	virtual bool has_next() = 0;
	virtual KEY next_key() = 0;
	virtual T next_data() = 0;
	

	
	
};
