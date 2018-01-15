#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

int myCompare (const void * a, const void * b ) {
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;

    return strcmp(pa,pb);
}

int main() {
    int i;
    const char *input[] = {"ana","maria","data","elena","melania","carla"};

    int stringLen = sizeof(input) / sizeof(char *);
    qsort(input, stringLen, sizeof(char *), myCompare);

    for (i=0; i<stringLen; ++i)
        cout<<input[i]<<endl;
}
