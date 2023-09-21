#include "leitura.hpp"

int main () 
{
     setlocale(LC_ALL, "pt_BR.UTF-8");

    double timespent = 0.0;

    clock_t begin = clock();

    readPrincipal();
    
    clock_t end = clock();

    timespent += (double)(end - begin) / CLOCKS_PER_SEC;

    cout << timespent << endl;
    
    return 0;

}