#pragma once

class MerkleNode
{
public:
	MerkleNode()
	: m_hash(0)
	, m_parent(nullptr)
	, m_leftChild(nullptr)
	, m_rightChild(nullptr)
	{
	}

	MerkleNode * GetSibling()
	{
		if (!m_parent)
			return nullptr;
		
		if (!m_parent->m_leftChild || !m_parent->m_rightChild)
			return nullptr;

		if (this == m_parent->m_leftChild)
			return m_parent->m_rightChild;
		else
			return m_parent->m_leftChild;
	}

	int m_hash;
	MerkleNode *m_parent;
	MerkleNode *m_leftChild;
	MerkleNode *m_rightChild;
};