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


//------------------------------------------------------------------------------------------------
//!
//! \param thou  - pointer on your stack
//! \param _size - first size of stack
//! \return 1 if it's ok and 0 if pointer on stack is NULL
//------------------------------------------------------------------------------------------------
int       StackConstruct       (Stack *thou, size_t  _size);

//------------------------------------------------------------------------------------------------
//!
//! \param thou     - pointer on your stack
//! \param new_elem - Value of new element to put into
//! \return 1. Verificate errors inside
//------------------------------------------------------------------------------------------------
int       StackPush            (Stack *thou, Element new_elem);

//------------------------------------------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//! \return 1. Verificate errors inside
//------------------------------------------------------------------------------------------------
int       StackPop             (Stack *thou);

//------------------------------------------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//! \return 1. Verificate errors inside
//------------------------------------------------------------------------------------------------
int       StackDestruct        (Stack *thou);

int       errout               (size_t current_line);

//------------------------------------------------------------------------------------------------
//!
//! \param current_line - current line where you work
//! \param err          - Type of error.
//! \param print_or_no  - True if you want to print message about error. False if you don't
//! \param thou         - pointer on your stack
//! \return             Type of error
//------------------------------------------------------------------------------------------------
int       ErrVerification      (size_t current_line, TypeError err, bool print_or_no, Stack *thou);

//------------------------------------------------------------------------------------------------
//! \note do not touch. Only for automatic work
//------------------------------------------------------------------------------------------------
int       StackResize          (Stack *thou, size_t new_size);

//------------------------------------------------------------------------------------------------
//!
//! \param  thou - pointer on your stack
//!
//! \return MemorySize of your stack
//!
//! \note   It doesn't count Canaries (to gel full size make pluse ( sizeof(canaries_const) * 2 ) )
//------------------------------------------------------------------------------------------------
size_t    GetStackMemorySize   (Stack *thou);

//------------------------------------------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//!
//! \return Type of error or NoError (0) if there is no any problem
//!
//------------------------------------------------------------------------------------------------
TypeError StackOk              (Stack *thou);

//------------------------------------------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//! \return Last element of ur stack
//!
//------------------------------------------------------------------------------------------------
Element   StackTop             (Stack *thou);
void      unit_tests           ();

//------------------------------------------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//!
//! \param output - pointer on your file to output
//!
//! \note Here is fprintf uses
//!
//------------------------------------------------------------------------------------------------
void      StackDump            (Stack *thou, FILE* output);

//------------------------------------------------------------------------------------------------
//!
//! \note do not touch. Only for automatic work.
//!
//------------------------------------------------------------------------------------------------
bool      CheckCanaries        (Stack *thou);

//------------------------------------------------------------------------------------------------
//!
//! \note do not touch. Only for automatic work.
//!
//------------------------------------------------------------------------------------------------
unsigned long Hash             (Stack *thou);

//------------------------------------------------------------------------------------------------
//!
//! \note do not touch. Only for automatic work.
//!
//------------------------------------------------------------------------------------------------
unsigned long ROR              (unsigned long num);

#define asserted || errout(__LINE__)

#endif //STACK_CLION_STACK_LIB_H
