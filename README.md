# Parallel bruteforce attack
The art of password decrypting has surely been one of the most hot topics in programming for a long time. What we are trying to achieve in this work are results that can show whether or not this problem lends itself well to a parallel programming approach, and what of the aforementioned approaches works best. We will present three different algorithms implemented with different directives introduced by the OpenMP API.

## Usage
In order to run the program with ```main.cpp```, the user must pass some arguments to it. In order, they are

1. a list of passwords to test
2. the number of tries per password 

So, some sample execution arguments can be:
```
williazz Kg575EAq 5
```
