#pragma once


#include "Allocator.hpp"
#include "Iterator.hpp"


template<class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using allocator_type = Alloc;
    using pointer = Alloc::pointer;
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
private:
    pointer data_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0;
    Alloc allocator_;
public:
    Vector();
    explicit Vector(size_type count);
    Vector(size_type count, const_reference defaultValue);
    Vector(std::initializer_list<value_type> init);
    ~Vector();
    
    reference operator[](size_type pos);
    
    void push_back(const_reference value);
    void pop_back();
    template< class... Args >
    void emplace_back(Args&&... args);
    
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type capacity() const noexcept;
    void reserve(size_type new_cap);

    void clear() noexcept;
    void resize(size_type count);
    void resize(size_type count, const_reference value);
    
    iterator begin() noexcept;
    reverse_iterator rbegin() noexcept;
    iterator end() noexcept;
    reverse_iterator rend() noexcept;
};

#include "Vector.tpp"
