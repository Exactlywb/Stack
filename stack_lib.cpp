//
// Created by 1 on 12.10.2020.
//

#include "MyStack.h"

FILE* output = fopen (OUTPUT_FILE, "w");

void unit_tests () {

    Stack stk = {};

    StackConstruct (&stk, 10);

    size_t in_elements = 0;

    printf ("Enter how many number you will enter : ");
    scanf ("%zu", &in_elements);

    Element temp = 0;

    while ( in_elements-- ) {

        scanf ("%lg", &temp);

        StackPush (&stk, temp);

    }

    printf ("Enter operations you will enter : ");
    scanf ("%zu", &in_elements);

    char new_operator = '\0';

    while ( in_elements-- ) {

        scanf ("%c", &new_operator);

        if ( (new_operator) == '\n' ) {

            in_elements++;
            continue;

        }

        Element res = 0;

        switch (new_operator) {

            case '+' :
                res = StackTop (&stk);
                StackPop(&stk);
                res += StackTop (&stk);
                StackPop (&stk);
                StackPush (&stk, res);
                break;

            case '-' :
                res = StackTop (&stk);
                StackPop(&stk);
                res -= StackTop (&stk);
                StackPop (&stk);
                StackPush (&stk, res);
                break;
            case '*' :
                res = StackTop (&stk);
                StackPop(&stk);
                res *= StackTop (&stk);
                StackPop (&stk);
                StackPush (&stk, res);
                break;
            case '/' :
                Element res = StackTop (&stk);
                StackPop(&stk);
                res /= StackTop (&stk);
                StackPop  (&stk);
                StackPush (&stk, res);
                break;

        }

    }

    printf ("%lg\n", StackTop (&stk) );

}

void StackConstruct (Stack* thou, const size_t set_size) {

    assert (set_size != 0);

    thou->max_size = set_size;
    thou->data     = (void*)calloc(set_size * sizeof(Element) + 2 * sizeof(CANARY), sizeof(char));
    assert (thou->data);

    *((unsigned long*)(thou->data)) = CANARY;
    thou->data = ((unsigned long*)(thou->data) + 1);
    *(unsigned long*)((Element*)(thou->data) + (thou->max_size)) = CANARY;

    thou->size = 0;
    thou->HashSum =  Hash(thou);

    ASSERT_OK;

}

Element StackTop (Stack *thou) {

    ASSERT_OK;

    return ((Element*)(thou->data))[(thou->size) - 1];

}

void StackPush (Stack *thou, const Element new_elem) {

    ASSERT_OK;

    if ( ( (thou->size) + 1 ) >= (thou->max_size) ) {

        StackResize (thou, (thou->max_size) * 2);

    }

    *((Element*) thou->data + (thou->size++)) = new_elem;

    thou->HashSum = Hash(thou);

    ASSERT_OK;

}

void StackPop (Stack *thou) {

    ASSERT_OK;

    ((Element*)(thou->data))[--(thou->size)] = POISON;

    thou->HashSum = Hash(thou);

    ASSERT_OK;

}

TypeError StackOk (Stack *thou) {

    if (thou == nullptr) {
        return NullStack;
    }

    if (thou->data == nullptr) {
        return NullBuffer;
    }

    if (thou->max_size == 0) {
        return ZeroSize;
    }

    if (thou->size > thou->max_size) {
        return PickError;
    }

    if ( *((unsigned long*)thou->data - 1) != CANARY || *(unsigned long*)((Element*)(thou->data) + (thou->max_size)) != CANARY) {
        //printf("%p\n", *((unsigned long*)(thou->data) - 1) );
        //printf("%p\n", *((unsigned long*)((thou->data) + thou->max_size)) );
        return CanariesError;
    }

    if ( thou->HashSum != Hash(thou) ) {
        return HashError;
    }

    return NoError;

}

void ErrVerification (size_t current_line, TypeError err, Stack* thou, bool PrintOrNo) {

    char* message = (char*)calloc(50, sizeof(char));

    switch (err) {

        case  NullStack:

            message = "Stack's pointer is NULL";
            break;

        case  NullBuffer:

            message = "Stack buffer's pointer is NULL";
            break;

        case  PopError:

            message = "Pop is impossible because of there are none any elements";
            break;

        case  ZeroSize:

            message = "Size of stack can not be zero";
            break;

        case  PickError:

            message = "Max size can not be less than index of current free cell";
            break;

        case CanariesError:

            message = "There is uncorrect input into stack";
            break;

        case HashError:

            message  = "Something bad with Hash!";
            break;

        default :

            message = "There is no errors";

    }

    if (PrintOrNo && err != NoError) {

        StackDump (thou, err, message);

        printf("There is an error : %s. On line %d\n", message, current_line);

    }

    free(message);

}

void StackResize (Stack* thou, const size_t new_size) {

    ASSERT_OK;

    thou->data = ((unsigned long*)(thou->data) - 1);
    (thou->data) = (void*)realloc(thou->data, sizeof(Element) * new_size + 2 * sizeof(unsigned long));

    (thou->max_size) = new_size;

    *((unsigned long*)(thou->data)) = CANARY;
    thou->data = ((unsigned long*)(thou->data) + 1);
    *(unsigned long*)((Element *) (thou->data) + (thou->max_size)) = CANARY;

    thou->HashSum = Hash(thou);

    ASSERT_OK;

}

void StackDump  (Stack *thou, TypeError err, const char* message) {

    fprintf (output, "Stack pointer = [%p]\n", thou);

    fprintf (output, "# Stack's max size : %zu. \n", thou->max_size);
    fprintf (output, "# Stack's current size : %zu. \n", thou->size);

    fprintf (output, "%s\n", message);

    fprintf (output, "* HashSum      = [%llu]\n", (thou->HashSum));
    fprintf (output, "* True HashSum = [%llu]\n", Hash(thou));

    fprintf (output, "* Data pointer = [%p]\n", (thou->data));

    fprintf (output, "* Left Canary  = [%p]\n", *((unsigned long*)thou->data - 1));
    fprintf (output, "* Right Canary = [%p]\n", *((Element*)thou->data + thou->max_size));

    fprintf (output, "### DATA PRINT : \n");
    for (size_t i = 0; i < (thou->max_size); i++) {

        fprintf (output, "#%zu. %lg;\n", (i + 1), *((Element*)(thou->data) + i) );

    }

    fprintf (output, "============================\n");

}

unsigned long long Hash (Stack* thou) {
    long long saveHash = thou->HashSum;
    thou->HashSum = 0;
    long long Hash_ = 0;

    char* stackBuff = (char*) thou;
    for (size_t i = 0; i < sizeof(*thou); ++i) {
        Hash_ = ROR(Hash_) + stackBuff[i];
    }

    char* dataBuff = (char*) thou->data;
    for (size_t i = 0; i < sizeof(*(Element*) thou->data); ++i) {
        Hash_ = ROR(Hash_) + dataBuff[i];
    }

    thou->HashSum = saveHash;

    return Hash_;
}

unsigned long long ROR (unsigned long long num) {

    return (num >> 1 | num << 63);

}

void StackDestruct (Stack* thou) {
    ASSERT_OK;

    free ((void*)((unsigned long long*) thou->data - 1));
    thou->data = NULL;
    free (thou);
    thou = NULL;

}