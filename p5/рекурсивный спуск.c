//
//  main.c
//  calc
//
//  Created by fix on 21/03/16.
//  Copyright (c) 2016 Anatoly Filinov. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>

int sum();
int mult();
int brace();
int number();

int brace() {
    int c;
    if ((c = getc(stdin)) != EOF && c == '(') {
        int r = sum();
        getc(stdin);
        return r;
    } else
        ungetc(c, stdin);
    return number();
}

int mult() {
    int c;
    int result = brace();
    while (1) {
        c = getc(stdin);
        if (c == '*') {
            result *= brace();
        } else if (c == '/') {
            result /= brace();
        } else if (!isblank(c)) {
            ungetc(c, stdin);
            break;
        }
    }
    return result;
}

int number() {
    int c;
    int result = 0;
    while ((c = getc(stdin)) != EOF && isdigit(c))
        result = result * 10 + c - '0';
    ungetc(c, stdin);
    return result;
}

int sum() {
    int c;
    int result = mult();
    while (1) {
        c = getc(stdin);
        if (c == '+') {
            result += mult();
        } else if (c == '-') {
            result -= mult();
        } else if (!isblank(c)) {
            ungetc(c, stdin);
            break;
        }
    }
    return result;
}

int main(int argc, const char * argv[]) {
    printf("%d\n", sum());
    return 0;
}
