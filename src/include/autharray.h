#pragma once

class AuthArray
{
public:
	AuthArray(unsigned int size);
	~AuthArray();

	int Read(unsigned int index);
	void Write(unsigned int index, int value);

private:
	inline void Hash();
	int *m_data;
};