# CWR

CWR is a standalone, high performance, set of C++ containers / tools.

### Table of contents

* [Motivation](#motivation)
* [Contribute](#contribute)
* [Benchmarks](#benchmarks)
* [Documentation](#documentation)

# Motivation
Why make this when there are so many other libraries that promise to do the same?

There were multiple reasons I decided to embark on this project, some of them being
<br>
#### Performance 
I've found that in many other libraries that have the same promises as this, the performance. While better than STL; Still leaves a lot to be desired. 
<br>
#### Bloat
In many of the other libraries like this, I've found that they nearly always require Boost (Massive), 
or some other random library that hasn't been used / maintained since 2008. Which makes the process of actually going and using the replacement
very troublesome. 
<br>
#### Learning
As it stands, I have a lot to learn in C++. And I believe doing this will allow me to learn a lot
so I'm going to go ahead and do it. 

# Contribute

Thinking of contributing? Great! Follow these steps to get you up and running!

todo :)

# Benchmarks
There's a lot of talk about numbers and performance when talking about this library compared to others.
But how does it compare to other similar libraries?

Todo :)

# Documentation
This library has a massive amount of tools / containers to use. This is a (non exhaustive) list of them.

## Containers
There are two main types of containers in this library,
* Linear - All of it's data is in a contiguous block of memory.
* Chunk - All of it's data in in chunks of memory

Note - All containers are linear by default, and have a `chunk_` prefix if they're a chunk variant.

### cwr::vector
Like most containers, this has a `linear` and `chunk` variant.

```c++
// Linear Vector
auto numbers = cwr::vector<int>();
numbers.reserve(50);
for (auto i = 0; i < 50; i++)
    numbers.push_back(i);
```

```c++
// Chunk Vector
// For the most part - Used the same as Linear vector, but has an extra method.
auto numbers = cwr::chunk_vector<int>();
numbers.capacity_per_chunk(4); // This method tells the vector how many of each element we can store within a single chunk
numbers.reserve(50); // Creates 13 chunks of memory
for (auto i = 0; i < 50; i++)
    numbers.push_back(i);
```

### cwr::string
We provide two strings, `linear` and `chunk`, the main difference between them is.
<br>
`cwr::string` Has all characters stored in the same block of memory, making it really good for string operations / iteration.
<br>
`cwr::chunk_string` Has all of it's characters stored in different "blocks" of memory. Making it good for re-using / strings where the size can change a lot

```c++
const auto name = cwr::string("Slim Shady / Eminem");
```

```c++
auto name = cwr::chunk_string("Ice Cube");
name = "C++ Is a language where the user is given a lot of control over what happens in the program, which is one of the reasons I like it so much.";
// In this example, the string gets stored in chunks. But you could imagine that if you were reading a file for example.
// Using this string would be a lot more efficient since you wouldn't be moving the old chars and allocating memory, instead just new memory and such
```

### More to come - If you have any suggestions for what containers to add, I'm all ears!