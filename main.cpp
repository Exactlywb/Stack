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

    unit_tests();

    Stack stk = {};

    StackConstruct (&stk, 1);

    StackPop (&stk);



    //StackDestruct (&stk);

    return 0;

}


