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
    printf("0x");
    printu(x);
}

//printo function
int printo(u32 x) {
    BASE = 8;
    printf("0");
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
    //********* CHECKLIST 1 *************

    // test myprintf
    myprintf("test myprintf\n");
    myprintf("\n");

    // print argc and argv[]
    myprintf("argc=%d\n", argc);
    for (int i=0; i<argc; i++) {
        myprintf("argv[%d]=%s\n", i, argv[i]);
    }
    myprintf("\n");

    // myprintf demo
    myprintf("cha=%c\nstring=%s\nunsigned=%u\nsigned=%d\nhex=%x\noct=%o\n", 'A', "this is a test", 123, -123, 123, 123);
    myprintf("\n");

    // *********** CHECKLIST 2 **************
    /* How do you write printd(int x) function?
    Since printd is meant to be signed, i first check to see if the int value we are passed is a positive or negative by throwing a conditional to check if its lower than 0. if that conditional is true, then it's negative and we must throw a '-' before printing out the integer. Then afterwards, i multiply the negative number by -1 to turn it back positive. Now we are out of the conditional and we can just print out the integer as is. (It goes through conditional if negative and we add a '-' and turn it positive then print out integer, but if not just print it as it comes in.)

    How do you let int *ip point at each item to be printed?
    Since a normal printf function has parameters of just ("some string", some variables or values to be passed into the string), then all we have to do is just set *ip equal to the second parameter to be passed in. So we just need to set *ip equal to the first parameter + 1 to get to next parameter, hence the int *ip = (int *)&fmt + 1. then each time we find a % sign, we know that theres a parameter to be passed in. So, we just print out the *ip value and then just increment *ip by 1 to move to next parameter for it to be printed later (if there is another one afterwards).
    */
}