#include "autharray.h"

// #define do_inline_asm(asm_string, pre, post) do {           \
//         uint64_t start;                                     \
//         uint64_t end;                                       \
//         register unsigned long a asm ("r13") = UINT64_MAX;  \
//         register unsigned long b asm ("r12") = 3;           \
//         do {                                                \
//             start = rdtscp();                               \
//             for (int i = 0 ; i < r; ++i) {                  \
//                 register long rax asm ("rax") = a;          \
//                 asm volatile(                               \
//                     pre                                     \
//                     repeat100(asm_string"       ;\n")       \
//                     post                                    \
//                     : [a] "+r" (a)                          \
//                     : [b] "r" (b)                           \
//                     : "rax", "rdx");                        \
//                 a = rax;                                    \
//             }                                               \
//             end = rdtscp();                                 \
//         } while(f);                                         \
//     } while(0)


AuthArray::AuthArray(unsigned int size)
{
	m_data = new int[2 * size];

	// TODO
	// zero array
	// calculate Merkle tree hashes and store them in mem except root hash
	// store root hash in secure reg
}

AuthArray::~AuthArray()
{
	// TODO zero array
    delete[] m_data;
}

int AuthArray::Read(unsigned int index)
{
	int result = m_data[index];
	// calculate Merkle tree hashes and compare root hash to one stored in secure register
	return result;
}

void AuthArray::Write(unsigned int index, int value)
{
	m_data[index] = value;
	// calculate Merkle tree hashes and store root hash in secure reg
}

void AuthArray::Hash()
{
	// calculate Merkle tree hashes and store them in mem except root hash
	// store root hash in secure reg
}