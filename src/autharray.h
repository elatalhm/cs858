#pragma once

#include "merkleNode.h"

register long secureReg asm ("x19");

class AuthArray
{
public:
	AuthArray(unsigned int size);
	~AuthArray();

	int Read(unsigned int index);
	void Write(unsigned int index, int value);

	void BadWrite(unsigned int index, int value);

private:
	inline int Hash(int a);
	inline int Hash(int a, int b);
	inline void UpdateMerkleProof(unsigned int index);
	inline void VerifyMerkleProof(unsigned int index);
	inline void HashAll();
	int *m_data;
	MerkleNode **m_merkleArray;
	MerkleNode *m_leftMerkle;
	MerkleNode *m_rightMerkle;
	unsigned int m_size;
};