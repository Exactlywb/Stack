//
// Created by 1 on 06.10.2020.
//

#ifndef STACK_CLION_STACK_LIB_H
#define STACK_CLION_STACK_LIB_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <string>


typedef double Element;
const Element poison = NAN;
const unsigned long canaries_const = 0xBADDEAD;

struct Stack {

    size_t max_size          = 0;
    size_t current_free_cell = 0;
    void*  buffer            = NULL;
    size_t min_size          = 0;
    unsigned long hashcode   = 0;

};

enum TypeError {

    NoError,
    NullStack,
    SamePointers,
    NullBuffer,
    PopError,
    ZeroSize,
    PickError,
    CanariesError

};

int       StackConstruct       (Stack *thou, size_t  _size);
int       StackPush            (Stack *thou, Element new_elem);
int       StackPop             (Stack *thou);
int       StackDestruct        (Stack *thou);
int       errout               (size_t current_line);
int       ErrVerification      (size_t current_line, TypeError err);
int       StackResize          (Stack *thou, size_t new_size);
size_t    GetStackMemorySize   (Stack *thou);
TypeError StackOk              (Stack *thou);
Element   StackTop             (Stack *thou);
void      unit_tests           ();
void      StackDump            (Stack *thou, FILE* output);
bool      CheckCanaries        (Stack *thou);
unsigned long Hash             (Stack *thou);
unsigned long ROR              (unsigned long num);

#define asserted || errout(__LINE__)

#endif //STACK_CLION_STACK_LIB_H
