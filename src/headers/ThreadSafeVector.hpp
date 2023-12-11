#pragma once
#include <iostream>
#include <vector>
#include <mutex>

namespace AANetwork {
    template <typename T>
    class ThreadSafeVector {
    public:
        ThreadSafeVector() = default;

        void push_back(const T& value) {
            std::lock_guard<std::mutex> lock(mutex_);
            data_.push_back(value);
        }

         void write(size_t pos, const T& value) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (pos < data_.size() - 1) 
            {
                data_[pos] = value;
            }
        }

        void erase(typename std::vector<T>::iterator iter) {
            std::lock_guard<std::mutex> lock(mutex_);
            data_.erase(iter);
        }

        /*void iterate() {
            std::lock_guard<std::mutex> lock(mutex_);
            for (const auto& element : data_) {
            }
        }*/

        void resize(size_t newSize) {
            std::lock_guard<std::mutex> lock(mutex_);
            data_.resize(newSize);
        }

        size_t size() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return data_.size();
        }

        typename std::vector<T>::iterator begin() {
            std::lock_guard<std::mutex> lock(mutex_);
            return data_.begin();
        }

        typename std::vector<T>::iterator end() {
            std::lock_guard<std::mutex> lock(mutex_);
            return data_.end();
        }

        // Operator[] for element access by index
        T& operator[](size_t index) {
            std::lock_guard<std::mutex> lock(mutex_);
            return data_[index];
        }

        // Const version of Operator[] for const object
        const T& operator[](size_t index) const {
            std::lock_guard<std::mutex> lock(mutex_);
            return data_[index];
        }

        T pop_front() 
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!data_.empty())
            {
                T poppedElement = std::move(data_.front());
                data_.erase(data_.begin());
                return poppedElement;
            }
            else
            {
                return T();
            }
        }

    private:
        std::vector<T> data_;
        mutable std::mutex mutex_;
    };
}