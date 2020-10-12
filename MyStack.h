//
// Created by 1 on 12.10.2020.
//

#ifndef STACK_LAST_VERSION_MYSTACK_H
#define STACK_LAST_VERSION_MYSTACK_H

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <assert.h>
#include <cctype>

typedef double Element;
const Element POISON = NAN;

const unsigned long CANARY = 0xBADDEAD;

const char OUTPUT_FILE[] = "output.txt";

enum TypeError {

    NoError,
    NullStack,
    NullBuffer,
    PopError,
    ZeroSize,
    PickError,
    CanariesError,
    HashError

};

struct Stack {

    size_t max_size            = 0;
    size_t size                = 0;
    void* data                 = nullptr;
    unsigned long long HashSum = 0;

};

//--------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//! \param set_size - new size you want to set
//--------------------------------------------------------------
void      StackConstruct   (Stack* thou, const size_t set_size );

//--------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//! \param new_elem - new element you want to put into stack
//--------------------------------------------------------------
void      StackPush        (Stack* thou, const Element new_elem);

//--------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//! \return Last (the highest) element in stack
//--------------------------------------------------------------
Element   StackTop         (Stack* thou);

//--------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//! \note  Move stack's size (index on the current free cell) and fill it poison
//--------------------------------------------------------------
void      StackPop         (Stack* thou);

//--------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//! \return Error about your stack. (NoError if there is no any error. Look at the enum TypError)
//--------------------------------------------------------------
TypeError StackOk          (Stack* thou);

//--------------------------------------------------------------
//!
//! \param current_line - current line where you got the error
//! \param err  - Error you got
//! \param thou - pointer on your stack
//! \param PrintOrNo - bool var : if you want to print yours erors into console you should put 'true'. If you don't you should put 'false'.
//--------------------------------------------------------------
void      ErrVerification  (size_t current_line, TypeError err, Stack* thou, bool PrintOrNo);

//--------------------------------------------------------------
//!
//! \note Do not touch. Only for automatic work
//--------------------------------------------------------------
void      StackResize      (Stack* thou, const size_t new_size);

//--------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//! \param err  - Type of error you got
//! \param message - message you want to get. (Look into Err Verification and enum TypeError)
//--------------------------------------------------------------
void      StackDump        (Stack* thou, TypeError err, const char* message);

//--------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//! \return Just HashSum. Check Sum hash algorithm.
//! \note it works by ROR func
//--------------------------------------------------------------
unsigned long long Hash    (Stack* thou);

unsigned long long ROR     (unsigned long long num);

//--------------------------------------------------------------
//!
//! \param thou - pointer on your stack
//! \note  To make free your memory.
//--------------------------------------------------------------
void      StackDestruct    (Stack* thou);

void      unit_tests       ();

#define ASSERT_OK                                   \
        ErrVerification(__LINE__, StackOk(thou), thou, true);

#endif //STACK_LAST_VERSION_MYSTACK_H
