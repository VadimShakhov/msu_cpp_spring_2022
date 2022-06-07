#pragma once


template<class T, class Alloc>
Vector<T, Alloc>::Vector(){
    data_ = allocator_.allocate(0);
    capacity_ = 0;
    size_ = 0;
}

template<class T, class Alloc>
Vector<T, Alloc>::Vector(size_type count){
    data_ = allocator_.allocate(count);
    size_ = count;
    capacity_ = count;
}

template<class T, class Alloc>
Vector<T, Alloc>::Vector(size_type count, const_reference defaultValue){
    data_ = allocator_.allocate(count);
    capacity_ = count;
    size_ = count;
    for (size_type i=0; i<count; i++)
        data_[i] = defaultValue;
}

template<class T, class Alloc>
Vector<T, Alloc>::Vector(std::initializer_list<value_type> init){
    size_ = init.size();
    capacity_ = size_;
    data_ = allocator_.allocate(size_);
    auto current = init.begin();
    const auto end = init.end();
    for (size_t i = 0; current != end; i++)
    {
        data_[i] = *current++;
    }
}

template<class T, class Alloc>
Vector<T, Alloc>::~Vector(){
    allocator_.deallocate(data_, capacity_);
}

template<class T, class Alloc>
Vector<T, Alloc>::reference Vector<T, Alloc>::operator[](size_type pos){
    return data_[pos];
}

template<class T, class Alloc>
void Vector<T, Alloc>::push_back(const_reference value){
    if (size_ < capacity_)
        data_[size_++] = value;
    else{
        capacity_ = size_*2 + 1;
        auto new_data = allocator_.allocate(capacity_);
        for (size_type i=0; i<size_; i++)
            new_data[i] = data_[i];
        allocator_.deallocate(data_, size_);
        new_data[size_++] = value;
        data_ = new_data;
    }
}

template<class T, class Alloc>
void Vector<T, Alloc>::pop_back(){
    if (size_ != 0)
        size_--;
}

template<class T, class Alloc>
template< class... Args >
void Vector<T, Alloc>::emplace_back(Args&&... args){
    this->push_back(T(args...));
}

template<class T, class Alloc>
bool Vector<T, Alloc>::empty() const noexcept{
    return size_ == 0;
}

template<class T, class Alloc>
Vector<T, Alloc>::size_type Vector<T, Alloc>::size() const noexcept{
    return size_;
}

template<class T, class Alloc>
Vector<T, Alloc>::size_type Vector<T, Alloc>::capacity() const noexcept{
    return capacity_;
}

template<class T, class Alloc>
void Vector<T, Alloc>::reserve(size_type new_cap){
    if (new_cap <= capacity_)
        return;
    auto old_cap = capacity_;
    capacity_ = new_cap;
    auto new_data = allocator_.allocate(capacity_);
    for (size_type i=0; i<size_; i++)
        new_data[i] = data_[i];
    allocator_.deallocate(data_, old_cap);
    data_ = new_data;
}

template<class T, class Alloc>
void Vector<T, Alloc>::clear() noexcept{
    allocator_.deallocate(data_, capacity_);
    data_ = allocator_.allocate(capacity_);
    size_ = 0;
}

template<class T, class Alloc>
void Vector<T, Alloc>::resize(size_type count, const_reference value){
    if (count <= size_){
        size_ = count;
        return;
    }

    if (capacity_ >= count){
        for (size_type i=count; i<count; i++)
            data_[i] = value;
        size_ = count;
        return;
    }

    auto new_data = allocator_.allocate(count);
    for (size_type i=0; i<size_; i++)
        new_data[i] = data_[i];
    for (size_type i=size_; i<count; i++){
        new_data[i] = value;
    }
    allocator_.deallocate(data_, capacity_);
    data_ = new_data;
    size_ = capacity_ = count;
}

template<class T, class Alloc>
void Vector<T, Alloc>::resize(size_type count){
    this->resize(count, value_type());
}

template<class T, class Alloc>
Vector<T, Alloc>::iterator Vector<T, Alloc>::begin() noexcept{
    return iterator(data_);
}

template<class T, class Alloc>
Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rbegin() noexcept{
    return reverse_iterator(iterator(data_ + size_));
}

template<class T, class Alloc>
Vector<T, Alloc>::iterator Vector<T, Alloc>::end() noexcept{
    return iterator(data_ + size_);
}

template<class T, class Alloc>
Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rend() noexcept{
    return reverse_iterator(iterator(data_));
}
