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
#endif