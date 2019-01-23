# Array

### Assignment

Implement a variable-length array type, called Array. Implementation should be a work-alike of the std::vector, only reasonably simpler.

#### Required functionality:
- Support for any contained type, using a template.
- Safe default constructor, copy constructor, copy assignment operator and destructor.
- implementations of empty, push_back, pop_back, back, front, swap, size, clear, assignable version of operator[] that behave as usual with STL containers. Note that you will have to implement 2 overloaded variants of operator[] and several other accessor functions — one for accessing constant array elements (that returns a const-reference) and the second for mutable contents.
- swap that swaps contents of 2 Arrays in O(1)
- append that adds content from another array to the end, i.e. a.append(b) causes a to contain contents from original a followed by b.
- reserve that pre-allocates memory for contents, so that successive pushing to the back of the array doesn’t need to reallocate the array frequently. Note that any other action than adding elements (eg. copying the array, popping elements, downsizing) is free to remove the effect of reserve preallocation.
- resize that changes the number of elements stored in the array. Note the difference between reserve and resize — resize should construct the objects, reseve should never construct anything; just prepare the memory.

You can optionally implement following features to patch up other inefficiencies in the code:

- Move semantics, i.e. the “rule of five”, optionally with emplace_back.
- begin, end, and associated iterators, to make the container compatible with the usual range-based for loops.

#### General requirements:

- Make sure your code is portable to all major C++ compilers (gcc, msvc, clang) and does not produce warnings — use -Wall with gcc and clang. (Notice: clang installation in the computer lab is somehow slightly broken; generally if your code passes through gcc -Wall without warnings, you can assume you won’t have any problems with clang.)
- Do not use STL, your solution should be based on “raw” programming with low-level memory primitives.
- Produce a reasonably short, neat, well-formatted and commented code. Use an automatic code formatter, i.e. astyle or clang-format. Check your code with automatic linter for common errors, e.g. cppcheck.
- Code should never crash, UNLESS subjected to usage that is documented as an invalid action that causes undefined behavior (i.e. out-of-bounds access by library user)
- Code should not leak memory. You can use valgrind to check for memory leaks automatically.
- The implementation should be as efficient as possible — Do not allocate memory unnecessarily (esp. not on construction of empty container), use correct const-antness, references, etc.
