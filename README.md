# key-value-db
This project contains different implementations of hash maps
<br>
Currently developed:
  1.  Using a Binary Search Tree as underlying data structure
  2.  Using a Dynamic resizing array as underlying data structure

## Dependencies:
  This project depends on:
  1.  [googletest](https://github.com/google/googletest) 
  2.  [valgrind](http://valgrind.org/)

## How to build
1.  `$./configure.sh`
  This step will simply init the git submodule for googletest
2.  `$make`

## Tests
To Run all unit tests, use:
<br>
 `$make test`
 
To Run all tests using valgrind, use:
<br>
  `$make test-valgrind`
  
### Obs: All development and testing was made on Arch-Linux x86_64.
