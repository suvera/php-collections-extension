#if !defined(NO_MEM_TRACK) && !defined(MEM_TRACK_INCLUDED)
#define MEM_TRACK_INCLUDED

// operator new
void *operator new(size_t size)
{
    //cout << "new called with " << size << "\n";
    //return malloc(size);
    return emalloc(size);
}

// operator delete
void operator delete(void *p)
{
    //cout << "delete called" << "\n";
    //free(p);
    efree(p);
}

// operator new[]
void *operator new[](size_t size)
{
    //cout << "new[] called with " << size << "\n";
    //return malloc(size);
    return emalloc(size);
}

// operator delete[]
void operator delete[](void *p)
{
    //cout << "delete[] called" << "\n";
    //free(p);
    efree(p);
}

#include <new>
#include <limits>
#include <cstddef>

template <class T>
struct eMallocator {
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T* const_pointer;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    // Its member type other is the equivalent allocator type to allocate elements of type Type
    template <class U> struct rebind {
        typedef eMallocator<U> other;
    };

    eMallocator() throw() {
    }

    eMallocator(const eMallocator&) throw() {
    }

    template <class U> eMallocator(const eMallocator<U>&) throw() {
    }

    ~eMallocator() throw() {
    }

    // Returns the actual address of x
    pointer address(reference x) const {
        return &x;
    }

    // Return address
    const_pointer address(const_reference x) const {
        return &x;
    }

    // Allocate block of storage
    pointer allocate(size_type s, void const * = 0) {
        if (0 == s)
            return NULL;

        pointer temp = (pointer) emalloc(s * sizeof(T));

        if (temp == NULL)
            //throw std::runtime_error("std::bad_alloc: Failed to allocate the requested storage space.");
            throw std::bad_alloc();

        return temp;
    }

    // Release block of storage
    void deallocate(pointer p, size_type) {
        efree(p);
    }

    // Maximum size possible to allocate
    size_type max_size() const throw() {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    // Construct an object
    void construct(pointer p, const_reference val) {
        new((void *)p) T(val);
    }

    template< class U, class... Args >
    void construct(U* p, Args&&... args ) {
        ::new((void *)p) U(std::forward<Args>(args)...);
    }

    // Destroy an object
    void destroy(pointer p) {
        p->~T();
    }

    template< class U >
    void destroy( U* p ) {
        p->~U();
    }
};

#endif