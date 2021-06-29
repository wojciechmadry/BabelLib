General information
---
babelLib is header file library, which have a lot of different function like algorithm/math etc.

babelLib is on **Open-source** license

How to include
---
To include this library to your project, only what you need to do to copy:

`babel.hpp`
`babLib` to your project and put `#include "babel.hpp"` in your program.

How to use
---
All babel function/namespaces are in namespace `babel`

List of namespaces `babel::`:
* `VERSION` - Actual version of babelLib
* `CONCEPTS` - All concepts I use in this library.
* `ALGO` - 
  Functions in this namespace are contained in other namespaces :
  * `CRYPT` encryption `SHA256` 
  * `STRING` string operation like: `str_to_upper/lower`
  * `VECTOR` Container operator like: `sum`, `normalize`, `mean`
  * `MATH` Math function like: `FFT`, `distance`, constant value (`e`, `pi`)
  * `CAST` Function like: `string_to`, `asType`
* `TIME` - Function or class to measure time like: `timer`, `measure_time`
* `ANY` - Class `PolAny` and `VoidAny`. They are very similar to std::any.
* `CHAR` - Class `ASCII_CHAR` it jus wrapped char with function like: `is_alphabetical`, `is_lower` etc.
* `CONTAINER` - My implementation of `std::list` and `std::vector`,
  I don't use them, because std container are better.
* `FILE_SYS` - Function to operate on files like: `scan_folder`, `load_txt` etc.
* `GRAPHICS` - Two class `RGB` and `CMYK` and convert between them.
  A very early version of these functions.
* `MATH` - Mathematical function like: `factorial`, `distance`, `lcm` etc. (Now `MATH` is in namespace `ALGO`)
* `MATRIX` - VERY underdeveloped matrix operations.
* `OPT` - My implementation of `std::optional`
* `REQ` - It is a `std::queue` of _lambda functions_, which are queued and called when you want to do it.
* `TEXT` - Class to improvement searching in big `std::string`, but it takes a lot more memory.
* `VARIADIC` - Has close `holder`, which store `variadic arguments` into `std::vector`.
* `WINDOWS` - Available only in _Windows_, simple windows function (like resolution of screen, search available discs)
* `WRAPER` - Class `wrap`, nothing special just wrap data `T`
* `SYSTEM` - Simple system function like number of threads etc.
* `ITERATOR` - Iterator like enumerate, range

Docs
---
Every _(almost)_ function have description, and some example of use.
![alt text](https://gitlab.com/woitys1999/babellib/-/raw/master/Screen/descr.PNG)

I'm working on put this description in one docs file.


