#pragma once


template<class T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type count)
    {
        return new value_type[count]();
    }
    void deallocate(pointer ptr, size_type){
        delete[] ptr;
    }
};

