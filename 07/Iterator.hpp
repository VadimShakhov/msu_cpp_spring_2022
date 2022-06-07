#pragma once


#include <iterator>


template <class T>
class Iterator
    : public std::iterator<std::random_access_iterator_tag, T>
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
private:
    pointer ptr_;
public:
    explicit Iterator(pointer ptr)
        : ptr_(ptr)
    {
    }

    reference operator*() const
    {
        return *ptr_;
    }

    difference_type operator-(const Iterator<value_type>& other) const
    {
        return std::distance(ptr_, other.ptr_);
    }

    Iterator& operator++()
    {
        ++ptr_;
        return *this;
    }

    Iterator& operator--()
    {
        --ptr_;
        return *this;
    }

    Iterator& operator+=(difference_type n)
    {
        ptr_ += n;
        return *this;
    }

    Iterator& operator-=(difference_type n)
    {
        ptr_ -= n;
        return *this;
    }

    Iterator operator+(difference_type n) const
    {
        Iterator sum = *this;
        sum += n;
        return sum;
    }

    friend Iterator operator+(difference_type n, Iterator it)
    {
        Iterator sum = it;
        return sum + n;
    }

    Iterator operator-(difference_type n) const
    {
        Iterator dif = *this;
        dif -= n;
        return dif;
    }

    reference operator[](difference_type n) const
    {
        return *(*this + n);
    }

    bool operator==(const Iterator<value_type>& other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<value_type>& other) const
    {
        return !(*this == other);
    }

    bool operator<(const Iterator<value_type>& other) const
    {
        return other - *this > 0;
    }

    bool operator>(const Iterator<value_type>& other) const
    {
        return other < *this;
    }

    bool operator>=(const Iterator<value_type>& other) const
    {
        return !(*this < other);
    }

    bool operator<=(const Iterator<value_type>& other) const
    {
        return !(*this > other);
    }
}; 
