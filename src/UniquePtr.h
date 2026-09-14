#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

// Your implementation here
template <typename T> 
class UniquePtr {
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
        // Delete and free if not empty
        if (ptr) {
            ptr.reset();
            delete ptr;
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
        UniquePtr<T> temp.reset(other.release());
        other.reset(this->release());
        this->reset(temp.release());
    }

    operator bool() const {
        return ptr != nullptr;
    }

    std::unique_ptr<T> ptr;
};
/*
template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args) {

}
*/
#endif
