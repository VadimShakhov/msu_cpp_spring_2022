#pragma once


#include <stdexcept>

class Allocator
{
    public:
        void makeAllocator(size_t maxSize);
        char* alloc(size_t size);
        void reset();
        
        //Возвращают значения соответствующих атрибутов
        char* get_offset();
        char* get_memory();
        size_t get_freeSpace();
        size_t get_allSpace();
    
        ~Allocator();
        
    private:
        char *offset = nullptr; // Указатель на левую граицу свободной памяти
        char *memory = nullptr; // Указатель на начало всей памяти
        size_t freeSpace = 0; // Количество свободного места
        size_t allSpace = 0; // Количество всей выделенной памяти
}; 
