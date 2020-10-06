//
// Created by 1 on 06.10.2020.
//
#include "stack_lib.h"

#define index (*thou).current_free_cell
#define max_index (*thou).max_size
#define ASSERT_OK \
        ErrVerification (__LINE__, StackOk(thou)) == 0


//-----------------------------------------------------------
//!
//! @param thou - pointer on your stack
//!
//! @param output - pointer on your file to output
//!
//! @note Here is fprintf uses
//!
//-----------------------------------------------------------
void StackDump (Stack* thou, FILE* output) {

    ASSERT_OK;

    fprintf (output, "Stack's size : %zu. \n", max_index);

    size_t i = 0;


    for (; i < max_index; i++) {

        fprintf (output, "Element #%zu : %f\n", i,  ((Element*) (thou -> buffer))[i] );

    }


}

void unit_tests () {

    Stack stk;
    StackConstruct (&stk, 10);

    char get_current_char = '\0';
    double temp_var = 0;

    while ( (get_current_char = getchar()) != '.') {
        if ( isdigit(get_current_char) ) {
            StackPush(&stk, get_current_char - '0');
            continue;
        }

        switch (get_current_char) {
            case '+' :
                temp_var += StackTop (&stk);
                StackPop (&stk);
                temp_var += StackTop (&stk);
                StackPop (&stk);
                StackPush (&stk, temp_var);
                break;
        }

    }

    printf ("%g\n", StackTop(&stk) );

    StackDestruct (&stk);

}

//-----------------------------------------------------------
//!
//! @param thou - pointer on your stack
//! @return Last element of ur stack
//!
//-----------------------------------------------------------
Element StackTop (Stack *thou) {

    ASSERT_OK;

    return ((Element*)((*thou).buffer))[index - 1];

}

//-----------------------------------------------------------
//!
//! @param current_line Number of the line where you got error
//! @param err Type of Error.
//! @return Type of Error
//!
//! @note To get the full list of TypeError you should look and TypeError Enum. It prints message into console.
//!
//-----------------------------------------------------------
int ErrVerification (size_t current_line, TypeError err) {

    char *message = (char*) calloc(50, sizeof(char));

    switch (err) {

        case 1 :

            message = "Stack's pointer is NULL";
            break;

        case 2 :

            message = "The same pointers of Stack and Stack's buffer";
            break;

        case 3 :

            message = "Stack buffer's pointer is NULL";
            break;

        case 4 :

            message = "Pop is impossible because of there are none any elements";
            break;

        case 5 :

            message = "Size of stack can not be zero";
            break;

        case 6 :

            message = "Max size can not be less than index of current free cell";
            break;

        case 7 :

            message = "There are uncorrent input into stack";


        default :

            return 0;

    }

    printf("There are an error : number #%d. %s. On %zu line. \n", err, message, current_line);

    free (message);

    return err;

}


//-----------------------------------------------------------
//!
//! @param thou - pointer on your stack
//!
//! @return Type of error or NoError (0) if there is no any problem
//!
//-----------------------------------------------------------
TypeError StackOk (Stack *thou) {

    if ( thou == NULL ) {

        return NullStack;

    } else if ( (void*) thou == (void*) ((*thou).buffer) ) {

        return SamePointers;

    } else if ( (*thou).buffer == NULL ) {

        return NullBuffer;

    } else if ( (*thou).max_size == 0 ) {

        return ZeroSize;

    } else if ( (*thou).max_size < (*thou).current_free_cell ) {

        return PickError;

    } else if ( CheckCanaries(thou) ) {

        return CanariesError;

    }

    return NoError;

}

//-----------------------------------------------------------
//!
//! @param thou - pointer on your stack
//!
//! @return MemorySize of your stack
//!
//! @note It doesn't count Canaries (to gel full size make pluse ( sizeof(canaries_const) * 2 ) )
//-----------------------------------------------------------
size_t GetStackMemorySize (Stack *thou) {

    return max_index * sizeof(Element);

}

void* pointer_begin = NULL;

//-----------------------------------------------------------
//!
//! @param thou - pointer on your stack
//! @param _size - Size of stack you want to set
//!
//! @return 1 if there is no any problem. 0 if there are null buffer
//!
//-----------------------------------------------------------
int StackConstruct (Stack *thou, size_t _size) {

    if (_size == 0) ErrVerification(__LINE__, ZeroSize);

    (*thou).max_size = _size;
    (*thou).min_size = _size;

    (*thou).current_free_cell = 0;

    (*thou).hashcode = 0;

    (*thou).buffer = calloc(_size * sizeof (Element) + 2 * sizeof(canaries_const), sizeof (char));

    pointer_begin = (*thou).buffer;

    ((unsigned long*)(*thou).buffer)[0] = canaries_const;

    ((unsigned long*)(*thou).buffer)[_size + 1] = canaries_const;

    (*thou).buffer += sizeof(canaries_const); // We move our buffer

    //printf("%p\n", ((unsigned long*)(*thou).buffer)[-1]);
    //printf("%p\n", ((unsigned long*)(*thou).buffer)[thou -> max_size]);

    std::fill((Element*)(*thou).buffer, (Element*)(*thou).buffer + max_index, poison);

    if ( (*thou).buffer == NULL ) return 0;

    return 1;

}

//-----------------------------------------------------------
//!
//! @param thou - pointer on your stack
//! @param new_elem - new element you want to add
//!
//! @return 1. If there are some problems it prints into console.
//!
//-----------------------------------------------------------
int StackPush (Stack *thou, Element new_elem) {

    ASSERT_OK;

    if ( index >= (max_index - 1) ) {

        StackResize (thou, max_index * 2) asserted;

    }

    ((Element*)(*thou).buffer)[index++] = new_elem;

    ASSERT_OK;

    thou -> hashcode = Hash(thou);

    return 1;

}

//-----------------------------------------------------------
//!
//! @note do not touch. Only for automatic work.
//!
//-----------------------------------------------------------
int StackResize (Stack *thou, size_t new_size) {


    //printf("%p\n", ((unsigned long*)(*thou).buffer)[-1]);

    //printf("%p\n", ((unsigned long*)(*thou).buffer)[thou -> max_size]);

    ASSERT_OK;

    if ( new_size < 0 ) printf ("New size of buffer's stack can not be negative number.\n");

    if ( (new_size < max_index && 4 * new_size > max_index) ) return 1;

    (*thou).buffer = (Element*) realloc(pointer_begin, sizeof(Element) * (new_size) + sizeof(canaries_const) * 2);

    pointer_begin  = (*thou).buffer;

    ((unsigned long*)(*thou).buffer)[0] = canaries_const;

    ((unsigned long*)(*thou).buffer)[new_size + 1] = canaries_const;

    (*thou).buffer += sizeof(canaries_const);

    printf("%p\n", ((unsigned long*)(*thou).buffer)[new_size]);

    max_index = new_size;

    std::fill((Element*)(*thou).buffer + index, (Element*)(*thou).buffer + max_index, poison);
    //printf("%p\n", ((unsigned long*)(*thou).buffer)[new_size]);

    return 1;

}

#define PopErrorVerification \
    if (index == 0)  return ErrVerification(__LINE__, PopError)

//-----------------------------------------------------------
//!
//! @param thou - pointer on your stack
//!
//! @return 1. If there are some problems it prints into console
//!
//-----------------------------------------------------------
int StackPop (Stack *thou) {

    ASSERT_OK;

    thou -> hashcode = Hash(thou);

    PopErrorVerification;

    ((Element*)(*thou).buffer)[--index] = poison;

    if (index < max_index) StackResize(thou, index);

    return 1;

}

#undef PopErrorVerification

//-----------------------------------------------------------
//!
//! @param thou - pointer on your stack
//!
//! @return 1. If there are some troubles it prints into console.
//!
//-----------------------------------------------------------
int StackDestruct (Stack *thou) {

    ASSERT_OK;

    free( (thou -> buffer) - sizeof(canaries_const) );

    (*thou).buffer            = NULL;
    (*thou).max_size          = 0;
    (*thou).current_free_cell = 0;

    return 1;

}

int errout (size_t current_line) {

    printf ("ERROR ON %zu", current_line);

    return 1;

}

//-----------------------------------------------------------
//!
//! @param thou - pointer on your stack
//!
//! @return true or false if there are an error or are not.
//!
//-----------------------------------------------------------
bool CheckCanaries (Stack *thou) {

    if (  ( *( (unsigned long*)( (thou -> buffer) - sizeof(canaries_const) ) ) != canaries_const ) || ( *( (unsigned long*)( (thou -> buffer) + (thou -> max_size) ) ) != canaries_const ) ) return true;

    return false;

}

unsigned long Hash (Stack* thou) {

    unsigned long current_hash_code = 0;

    char* stackBuff = (char*) thou;

    for (int i = 0; i < sizeof(*thou); i++) {

        current_hash_code = ROR(current_hash_code) + stackBuff[i];

    }

    return current_hash_code;

}

size_t ROL (size_t num) {

    return (num << 1 | num >> 31);

}

unsigned long ROR (unsigned long num) {


    return (num >> 1 | num << 31);

}


#undef index
#undef ASSERT_OK
#undef max_index
