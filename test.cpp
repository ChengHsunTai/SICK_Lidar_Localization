#include <stdio.h>
#include <stdint.h>

int main(){
    int32_t x = 1030;
    const char *xstring = (const char *) &x;
    int32_t y = -5200;
    const char *ystring = (const char *) &y;
    printf("%02X", (unsigned char)ystring[1]);
}
