#pragma once

class AuthArray
{
	AuthArray(unsigned int size);
	~AuthArray();

	int Read(unsigned int index);
	void Write(unsigned int index, int value);
};