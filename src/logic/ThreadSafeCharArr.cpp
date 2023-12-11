#pragma once
#include <iostream>
#include <mutex>
#include <string>
#include <cstring>

namespace AANetwork{
    class ThreadSafeCharArray {
    public:
        ThreadSafeCharArray(size_t size) 
        : bufferSize(size) 
        {
            buffer = new char[bufferSize];
        }

        ~ThreadSafeCharArray() {
            delete[] buffer;
        }

        void write(const char* data, size_t datasize)
        {
            std::lock_guard<std::mutex> lock(mutexWrite);
            std::memset(buffer, 0, bufferSize);
            std::strncpy(buffer, data, bufferSize - 1);
            buffer[datasize - 1] = '\0';
        }

        std::string read() 
        {
            std::lock_guard<std::mutex> lock(mutexRead);
            return std::string(buffer);
        }

    private:
        char* buffer;
        size_t bufferSize;
        std::mutex mutexWrite;
        std::mutex mutexRead;
    };
}