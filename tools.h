#define swap(x,y) do {*x = *x ^ *y; *y = *y ^ *x; *x = *x ^ *y;} while(0)
