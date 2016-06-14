# key-value-db
This project is a simple implementation of a hash-map.
<br>
The underlaying data structure of this implementation is a Binary Search Tree.

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
  
## TODO's
1.  Finish BST development
2.  Finish Hash-table development
3.  Complete Unit tests
4.  Test in another linux distribution
  
### Obs: All development and testing was made on Arch-Linux x86_64.
