/* 
 * CS:APP Data Lab 
 * 
 * Hunter Irving, irvingha, (nickname: H Dawg)
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
 /* 1. & the operands and store the result
  * 2. & bit-flipped versions of the operands and store the result
  *   (we have now isolated the bits that we want to be set in the result of this XOR)
  * 3. return the & of bit-flipped versions of the results from steps 1 and 2
  */

  int w = x & y;
  int z = (~x) & (~y);
  int a = (~w) & (~z);
  return a;
}

/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  /* make a mask with first 8 odd bits set to 1 (1010 1010) */
  int mask = 0xAA;

  /* copy the mask into the next 8 bits, first 16 odd bits are now 1 (1010 1010 1010 1010) */
  mask = mask | (mask << 8);

  /* copy the mask again to fill out all 32 of the bits we will be comparing against x */
  mask = mask | (mask << 16);

  /* if all the even bits of x are truly 1s, x will now be set to 0xFFFFFFFF... otherwise it won't */
  x = mask | x;

  /* flip all the bits of x (0xFFFFFFFF becomes 0x00000000) then use ! to return 1 if all even bits were set to 1 in the original x */
  return(!(~x));
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int mask = 0x1 << 31; //1000 0000 ... 0000 0000
  mask = (mask >> (n)) << 1; //1111 1100 ... 0000 0000
  mask = ~ mask; //0000 0011 ... 1111 1111
  return (x >> n) & mask; //chop off unwanted 1's
}

/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  /* make a mask by right shifting the sign bit across the field (1111...1111 if sb = 1, 0000...0000 otherwise) */
  int mask = x >> 31;

  /* XOR to get almost right answer.. now we need to add 1 only if the input was negative, add zero otherwise */
  int y = x ^ mask;

  /* use this to only add one if original number was negative */
  return y + (mask & 1);
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  /* load y with -x */
  int y = (~x) + 1;

  /* set z to all 0's if x == 0, all 1's if x != 0
   * this works because (0 | -0) always leaves sb = 0
   * anything else will make sb = 1
   */
  int z = (x | y) >> 31;

  /* 0xFFFFFFFF becomes 0x0, 0x0 becomes 0x1 */
  return z + 1;
}

/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  //1. shift a single one down to the most significant bit (1000....0000)
  //2. flip bits to get 0111....1111 (aka TMax)

  return ~(1 << 31);
}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
 /* this doesn't work
  * int mask = x >> 31;
  * int y = x ^ mask;
  * y = y + (mask & 1); //y holds abs val of x
  *
  * int mask = y >> n; //if y would fit, z will now be 0
  * return ! mask; */

  /* (32 - n) == (33 + ~n) ..there's that inherent -1 when flipping bits of n
   * 32 bits - n bits = number of bits left over when we're trying to fit into n bits */
  int left = 0x21 + (~n);
  
  /* take x crammed into n bits, shift it down and back so sign extension happens */
  int y = (x << left) >> left;
  
  /* does y == x ? */
  return !(y ^ x);
}

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *   Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  // x >> n; //works for all pos numbers
  //(x >> n) + 1; //when a number is neg and not evenly divisible by a power of 2
  //int y = x >> n;
  //int mask = x >> 31; //(0000... if pos, 1111... if neg)  
  return 2;
  //int drops = x << (31 - n)
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* 1. flip bits
   * 2. add one
   * 3. shoutout to Joel Swanson */

  return (~x) + 1;
}

/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  /* if number is pos and  > 0, result of x>>31 is 0, result of !x is 0
   * if number is neg, result of x>>31 is 1, result of !x is 0
   * if number is zero, result of x>>31 is 0, result of !x is 1
   * we want to output 1 for pos, 0 for neg, 0 for zero
   * 0 0 1
   * 1 0 0
   * 0 1 0
   * XOR gives us the opposite of what we want, so use ! to negate that */

  return !((x >> 31) ^ (!x));
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  return 2;
}

/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x) {
  return 2;
}

/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  return 2;
}

/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  return 2;
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}
