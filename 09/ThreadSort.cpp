#include "ThreadSort.hpp"

std::mutex mutex;

void first_read(FILE *in, FILE *new_in){
    while(true){
        std::unique_lock<std::mutex> lock(mutex);
        num_type *nums = new num_type[chunk];
        auto count = fread(nums, sizeof(num_type), chunk, in);
        lock.unlock();

        if (count == 0){
            delete[] nums;
            return;
        }

        std::sort(nums, nums + count);

        fwrite(nums, sizeof(num_type), count, new_in);

        delete[] nums;
    }
}

void merge(FILE *lenta1, FILE *lenta2, FILE *out){
    num_type num1;
    bool lenta1_not_end = (bool) fread(&num1, sizeof(num_type), 1, lenta1);

    num_type num2;
    bool lenta2_not_end = (bool) fread(&num2, sizeof(num_type), 1, lenta2);

    if (!lenta1_not_end && !lenta2_not_end)
        return;

    while (lenta1_not_end && lenta2_not_end){
        if (num1 <= num2){
            fwrite(&num1, sizeof(num_type), 1, out);
            lenta1_not_end = (bool) fread(&num1, sizeof(num_type), 1, lenta1);
        }
        else{
            fwrite(&num2, sizeof(num_type), 1, out);
            lenta2_not_end = (bool) fread(&num2, sizeof(num_type), 1, lenta2);
        }
    }

    if (lenta1_not_end){
        fwrite(&num1, sizeof(num_type), 1, out);
        num_type* nums = new num_type[chunk];
        auto count = fread(nums, sizeof(num_type), chunk, lenta1);
        while(count > 0){
            fwrite(nums, sizeof(num_type), count, out);
            count = fread(nums, sizeof(num_type), chunk, lenta1);
        }
        delete[] nums;
    }
    if (lenta2_not_end){
        fwrite(&num2, sizeof(num_type), 1, out);
        num_type* nums = new num_type[chunk];
        auto count = fread(nums, sizeof(num_type), chunk, lenta2);
        while(count > 0){
            fwrite(nums, sizeof(num_type), count, out);
            count = fread(nums, sizeof(num_type), chunk, lenta2);
        }
        delete[] nums;
    }
}

void merge(FILE *lenta1, size_t size1, FILE *lenta2, size_t size2, FILE *out){
    size_t l1 = 0, l2 = 0;
    num_type num1;
    fread(&num1, sizeof(num_type), 1, lenta1);
    num_type num2;
    fread(&num2, sizeof(num_type), 1, lenta2);

    while (l1<size1 && l2<size2){
        if (num1 <= num2){
            fwrite(&num1, sizeof(num_type), 1, out);
            l1++;
            if (l1<size1) 
                fread(&num1, sizeof(num_type), 1, lenta1);
        }
        else{
            fwrite(&num2, sizeof(num_type), 1, out);
            l2++;
            if (l2<size2) 
                fread(&num2, sizeof(num_type), 1, lenta2);
        }
    }
    
    if (l1<size1){
        for (; l1<size1-1; l1++){
            fwrite(&num1, sizeof(num_type), 1, out);
            fread(&num1, sizeof(num_type), 1, lenta1);
        }
        fwrite(&num1, sizeof(num_type), 1, out);
    }
    if (l2<size2){
        for (; l2<size2-1; l2++){
            fwrite(&num2, sizeof(num_type), 1, out);
            fread(&num2, sizeof(num_type), 1, lenta2);
        }
        fwrite(&num2, sizeof(num_type), 1, out);
    }
}


void sort(FILE *in, std::string lenta1_name, std::string lenta2_name){
    rewind(in);
    FILE *lenta1 = fopen(lenta1_name.c_str(), "w+b");
    FILE *lenta2 = fopen(lenta2_name.c_str(), "w+b");

    size_t counter = 1;
    int64_t num_ser = -1;
    size_t series1_size = 0;
    size_t series2_size = 0;
    while(num_ser != 0){
        num_ser = -1;
        do{
            series1_size = 0;
            series2_size = 0;
            num_type num;
            for (; series1_size<chunk*counter; series1_size++){
                if (fread(&num, sizeof(num_type), 1, in))
                    fwrite(&num, sizeof(num_type), 1, lenta1);
                else break;
            }
            for (; series2_size<chunk*counter; series2_size++){
                if (fread(&num, sizeof(num_type), 1, in))
                    fwrite(&num, sizeof(num_type), 1, lenta2);
                else break;
            }
            num_ser++;
        }while(series1_size == chunk*counter && series2_size == chunk*counter);

        rewind(lenta1);
        rewind(lenta2);
        rewind(in);

        for (int64_t i=0; i<num_ser; i++){
            merge(lenta1, chunk*counter, lenta2, chunk*counter, in);
        }
        merge(lenta1, series1_size, lenta2, series2_size, in);

        counter *= 2;
        rewind(lenta1);
        rewind(lenta2);
        rewind(in);
    }

    fclose(lenta1);
    fclose(lenta2);
    remove(lenta1_name.c_str());
    remove(lenta2_name.c_str());
}

void two_thread_sort(std::string in_name, std::string out_name){
    FILE *in = fopen(in_name.c_str(), "rb");
    FILE *in1 = fopen("in1.bin", "w+b");
    FILE *in2 = fopen("in2.bin", "w+b");

    std::thread read1(first_read, in, in1);
    std::thread read2(first_read, in, in2);
    read1.join();
    read2.join();
    fclose(in);

    std::thread sort1(sort, in1, "lenta1.bin", "lenta2.bin");
    std::thread sort2(sort, in2, "lenta3.bin", "lenta4.bin");
    sort1.join();
    sort2.join();

    FILE *out = fopen(out_name.c_str(), "w+b");
    
    rewind(in1);
    rewind(in2);
    merge(in1, in2, out);

    fclose(in1);
    fclose(in2);
    fclose(out);
    remove("in1.bin");
    remove("in2.bin");
}
