#pragma once


#include <cstdio>
#include <algorithm>
#include <mutex>
#include <thread>


using num_type = uint64_t;

const size_t chunk = 64;

// Считывает num_typeы из in, разбивает их на чанки, сортирует чанки и записывает в new_in 
void first_read(FILE *in, FILE *new_in);

// Сливает две ленты (бинарики с num_type) в out
void merge(FILE *lenta1, FILE *lenta2, FILE *out);

// Сливает ленту lenta1 размера size1 (в единицах num_type) и ленту lenta2
// размера size2 в out
void merge(FILE *lenta1, size_t size1, FILE *lenta2, size_t size2, FILE *out);

// Сортирует in, используя ленты с именами lenta1_name и lenta2_name
void sort(FILE *in, std::string lenta1_name, std::string lenta2_name);

// Сортирует в 2 потока файл с именем in_name и записывает в файл с именем out_name
void two_thread_sort(std::string in_name, std::string out_name);
