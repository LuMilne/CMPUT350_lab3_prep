#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <memory>

// Your implementation here
template <typename T> 
class UniquePtr {
    public:
        // -----
        // Initialization
        // -----
        // Default initialize empty
        UniquePtr() {
            ptr = nullptr;
        }
        // Pass raw pointer
        UniquePtr(T* p) {
            ptr.reset(p);
        }
        
        // -----
        // Destruction
        // -----
        ~UniquePtr() {
            // Free and delete if not empty
            if (ptr) {
                ptr.reset();
            }
        }

        // -----
        // Operators
        // -----
        T& operator*() const {
            // Return dereferenced value
            return *ptr;
        }
        T* operator->() const {
            // Return unique pointer
            return ptr;
        }

        // -----
        // Functions
        // -----
        T* get() const {
            // Return raw pointer
            return ptr.get();
        }

        T* release() {
            // Release ownership
            return ptr.release();
        }

        void reset(T* newptr = nullptr) {
            // Destroy current and take ownership of new pointer
            ptr.reset(newptr);
        }

        void swap(UniquePtr<T>& other) {
            assert(this != &other); // Cannot self-move
            // Exchange ownership
            UniquePtr<T> temp;
            temp.reset(other.release());    // temp(owns nullptr) <-- other(owns otherptr)
            other.reset(this->release());   // other(owns nullptr) <-- this(owns thisptr)
            this->reset(temp.release());    // this(owns nullptr) <-- temp(owns otherptr)
            // this(owns otherptr), other(owns thisptr), temp(owns nullptr)
        }

        operator bool() const {
            return ptr != nullptr;
        }

    private:
        std::unique_ptr<T> ptr;
};


// -----
// Creating a Unique Pointer
// -----
template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args) {
    // Bind as an rvalue and pass to constructor
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}



#endif
