#include "Allocator.hpp"

void Allocator::makeAllocator(size_t maxSize)
{
    if (maxSize == 0)
        throw std::invalid_argument("0");

    if (memory != nullptr) delete[] memory;

    memory = new char[maxSize];
    offset = memory;
    allSpace = maxSize;
    freeSpace = maxSize;
}

char* Allocator::alloc(size_t size)
{
    if (size == 0)
        throw std::invalid_argument("0");

    if (size > freeSpace) return nullptr;
    freeSpace -= size;
    char *offset_old = offset;
    offset += size;
    return offset_old;
}

void Allocator::reset()
{
    freeSpace = allSpace;
    offset = memory;
}

char* Allocator::get_offset(){return offset;}
char* Allocator::get_memory(){return memory;}
size_t Allocator::get_freeSpace(){return freeSpace;}
size_t Allocator::get_allSpace(){return allSpace;}

Allocator::~Allocator()
{
    if (memory != nullptr) delete[] memory;
} 
