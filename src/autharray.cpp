#include "autharray.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>

register unsigned long secureReg asm ("x19");

AuthArray::AuthArray(unsigned int size)
{
	// TODO ensure size is a power of 2

	m_data = new int[size];
	// m_data = (int*) calloc(size, sizeof(int));
	m_merkleArray = new MerkleNode*[size];
	m_size = size;

	HashAll();
}

AuthArray::~AuthArray()
{
	// TODO zero array
	//delete[] m_data;
}

int AuthArray::Read(unsigned int index)
{
	register int result asm ("r0") = m_data[index];
	VerifyMerkleProof(index);
	return result;
}

void AuthArray::Write(unsigned int index, int value)
{
	m_data[index] = value;
	UpdateMerkleProof(index);
}

// violate integrity here
void AuthArray::BadWrite(unsigned int index, int value) 
{
	m_data[index] = value;
}

void AuthArray::UpdateMerkleProof(unsigned int index)
{
	MerkleNode *current = m_merkleArray[index];
	current->m_hash = Hash(m_data[index]);

	while (current->m_parent)
	{
		int siblingHash = current->GetSibling()->m_hash;
		int parentHash_ = 0;
		if (current == current->m_parent->m_leftChild)
			parentHash_ = Hash(current->m_hash, siblingHash);
		else
			parentHash_ = Hash(siblingHash, current->m_hash);
		
		current->m_parent->m_hash = parentHash_;

		current = current->m_parent;
	}
}

void AuthArray::VerifyMerkleProof(unsigned int index)
{
	MerkleNode *current = m_merkleArray[index];

	while (current->m_parent)
	{
		int siblingHash = current->GetSibling()->m_hash;
		int parentHash_ = 0;
		if (current == current->m_parent->m_leftChild)
			parentHash_ = Hash(current->m_hash, siblingHash);
		else
			parentHash_ = Hash(siblingHash, current->m_hash);
		
		if (parentHash_ != current->m_parent->m_hash)
		{
			std::cout << "Merkle proof verification failed!\n";
			exit(-1);
		}

		current = current->m_parent;
	}

	// now current is either m_rightMerkle or m_leftMerkle
	// verify root hash
	if (Hash(m_leftMerkle->m_hash, m_rightMerkle->m_hash) != secureReg)
		exit(-1);
}

// bottom-up breadth-first traversal
void AuthArray::HashAll()
{
	// calculate Merkle tree hashes and store them in mem except root hash
	// store root hash in secure reg

	std::queue<MerkleNode *> todo;

	for (unsigned int i = 0; i < m_size; ++i)
	{
		m_merkleArray[i] = new MerkleNode();
		m_merkleArray[i]->m_hash = Hash(m_data[i]);
		todo.push(m_merkleArray[i]);
	}

	while (todo.size() > 2)
	{
		unsigned int count = todo.size();
		for (unsigned int i = 0; (i + 1) < count; i+=2)
		{
			MerkleNode *left = todo.front();
			todo.pop();
			MerkleNode *right = todo.front();
			todo.pop();
			MerkleNode *parent = new MerkleNode;
			todo.push(parent);
			left->m_parent = right->m_parent = parent;
			parent->m_leftChild = left;
			parent->m_rightChild = right;
			parent->m_hash = Hash(left->m_hash, right->m_hash);
		}
	}

	// now todo queue has the left and right nodes of the root
	MerkleNode *left = todo.front();
	todo.pop();
	MerkleNode *right = todo.front();
	todo.pop();

	m_leftMerkle = left;
	m_rightMerkle = right;

	// last hash; store it in secure register
	secureReg = Hash(left->m_hash, right->m_hash);
}

__attribute__ ((always_inline))
int AuthArray::Hash(int left, int right)
{
	// return H(left || right)
}

int AuthArray::Hash(int a)
{
	// return H(a)
	// used for leaf nodes
}