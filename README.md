# Stack implementation. Ilab MIPT 1st course

* 3rd project of Ilab course
* Lecturer: Ilya Dedinskiy

## Project description

***Stack*** is a linear data structure which follows a particular order in which the operations are performed. The order may be LIFO or FILO.

<p align = "center"><img src = "pictures/stack.png" width = "400"></p>

In addition to designing the stack itself, we had to implemented strong stack error handlings.

## Stack protection

To protect stack data I used a few features:

* Canaries --- method when we put two values which mustn't be changed at the edges of the buffer and handle if they have changed.

* Hash --- we evaluate hash-value using ROR algorithm based on current stack status.

## Stack amortization

In my stack implementation we use amortization algorithm such that we double the buffer size if necessary. The algorithm complexity is ```O(1)```

```cpp
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
```

## How to build

After git clone:

```
mkdir build
cd build/
cmake ..
make
./stack_last_version
```
