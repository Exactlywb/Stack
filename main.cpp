#include "stack_lib.h"

//!TODO Stack
//!TODO ASSERTS AND ERRORS // looks like done.
//!TODO REALLOCATION //done
//!TODO FIX REPEATS //done
//!TODO STACK DUMP //done
//!TODO Beauty code //done
//!TODO Canaries // done (Have to describe the error) //done
//!TODO Documentation // done
//!TODO Look at your errors // looks like done. break me.
//!TODO Hash // done (Have to switch on)

int main() {

    //unit_tests();
    Stack stk = {};

    StackConstruct (&stk, 5) asserted;

    FILE *output = NULL;
    output = fopen ("logs.txt", "w");
    StackDump (&stk, output);

    StackPush (&stk, 2);
    StackPush (&stk, 32345);
    StackPush (&stk, 5);
    StackPush (&stk, 1);
    StackPush (&stk, 2);
    StackPush (&stk, 2);
    StackPush (&stk, 2);

    StackPop  (&stk);

    printf("%f", ( (Element*)(stk.buffer) ) [0]);

    StackPop  (&stk);

    StackDump (&stk, output);


    StackDestruct (&stk);

    fclose(output);
    return 0;

}


