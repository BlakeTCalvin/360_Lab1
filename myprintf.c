#include <stdio.h>

typedef unsigned int u32;

char *ctable = "0123456789ABCDEF";
int  BASE = 10; 

int rpu(u32 x)
{  
    char c;
    if (x){
       c = ctable[x % BASE];
       rpu(x / BASE);
       putchar(c);
    }
}

int printu(u32 x)
{
   (x==0)? putchar('0') : rpu(x);
   putchar(' ');
}

// printd function
int printd(int x) {
    if (x<0) {
        putchar('-');
        x = x*-1;
    }
    printu(x);
}

//printx function
int printx(u32 x) {
    BASE = 16;
    printu(x);
}

//printo function
int printo(u32 x) {
    BASE = 8;
    printu(x);
}

char* prints(char *s) {
    while (*s) {
        putchar(*s);
        s++;
    }
}

char myprintf(char *fmt, ...) {
    char *cp = fmt;
    int *ip = (int *)&fmt + 1;
    while (*cp) {
        if (*cp != '%') {
            putchar(*cp);
            cp++;
        }
        else {
            cp++;
            switch (*cp) {
                case 'c':
                    putchar(*ip);
                    break;
                case 's':
                    prints(*ip);
                    break;
                case 'u':
                    printu(*ip);
                    break;
                case 'd':
                    printd(*ip);
                    break;
                case 'o':
                    printo(*ip);
                    break;
                case 'x':
                    printx(*ip);
                    break;
            }
            cp++;
            ip++;
        }
    }
}

int main(int argc, char *argv[], char *env[]) {
    prints("Hello\n\n");
    myprintf("Character is: %c. String is: %s. Unsigned Decimal Integer is: %u. Signed Decimal Integer is: %d. Signed Octal is: %o. Unsigned Hexadecimal Integer is: %x.", 'c', "Hello", 35, 35, 50, 10);
    printf("\n");
}