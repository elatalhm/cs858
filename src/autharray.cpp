#include "autharray.h"

#define do_inline_asm(asm_string, pre, post) do {           \
        uint64_t start;                                     \
        uint64_t end;                                       \
        register unsigned long a asm ("r13") = UINT64_MAX;  \
        register unsigned long b asm ("r12") = 3;           \
        do {                                                \
            start = rdtscp();                               \
            for (int i = 0 ; i < r; ++i) {                  \
                register long rax asm ("rax") = a;          \
                asm volatile(                               \
                    pre                                     \
                    repeat100(asm_string"       ;\n")       \
                    post                                    \
                    : [a] "+r" (a)                          \
                    : [b] "r" (b)                           \
                    : "rax", "rdx");                        \
                a = rax;                                    \
            }                                               \
            end = rdtscp();                                 \
        } while(f);                                         \
    } while(0)


AuthArray::AuthArray(unsigned int size) 
{

__asm [volatile] (code_template 
		: output_operand_list 
		[: input_operand_list 
		[: clobbered_register_list]] 
	);
}

AuthArray::~AuthArray() 
{
	
}

int AuthArray::Read(unsigned int index) 
{
	
}

void AuthArray::Write(unsigned int index, int value) 
{
	
}
