#include <cstdlib>
int main() {
    long double *a = new long double [10];
    a+=3;
    
    
    free((long double* )(a+=3));
    free((long double* )(a+=2));
    free((long double* )(a+=1));
    delete [] a;
    
    return 0;
}
