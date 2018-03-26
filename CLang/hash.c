#include <stdlib.h>

// #include <hashcode.h>


size_t hash(unsigned char * str) {
    size_t hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}
