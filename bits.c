/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~(x & ~y) & ~(~x & y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  return (x >> 31) & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int ss = src << 3;
  int ds = dst << 3;
  int byte_val = (x >> ss) & 0xFF;
  int mask = ~(0xFF << ds);
  return (x & mask) | (byte_val << ds);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int mask = ~(((1 << 31) >> n) << 1);
  return (x >> n) & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = 0x0F | (0x0F << 8);
  mask = mask | (mask << 16);
  return ((x & mask) << 4) | ((x >> 4) & mask);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int a = ~x;
  int low = a & (~a + 1);
  int b = a ^ low;
  return b & (~b + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return ~x & 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int sn = n & 31;
  int shift = (32 + (~sn + 1)) & 31;
  int mask = ~(((1 << 31) >> sn) << 1);
  int right = (x >> sn) & mask;
  int left = x << shift;
  return right | left;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int half = 1 << (n + ~0);
  int q = x >> n;
  int adj = half + (q & 1) + ~0;
  return ((x + adj) >> n) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int half = (x & y) + ((x ^ y) >> 1);
  int odd = (x ^ y) & 1;
  int xneg = x >> 31;
  int yneg = y >> 31;
  int ds = xneg ^ yneg;
  int xmy = x + ~y + 1;
  int gt_ss = ~(xmy >> 31) & 1;
  int gt_ds = ~xneg & 1;
  int gt = (ds & gt_ds) | (~ds & gt_ss);
  return half + (odd & gt);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sa = a >> 31, sb = b >> 31;
  int xors = sa ^ sb;
  int d = a + ~b + 1;
  int alt = (xors & (sa & 1)) | (~xors & ((d >> 31) & 1));
  int cond = ~alt + 1;
  int t = (a ^ b) & cond;
  int lo = b ^ t;
  int hi = a ^ t;
  int sx = x >> 31;
  int sl = lo >> 31, sh = hi >> 31;
  int dxl = x + ~lo + 1;
  int dhx = hi + ~x + 1;
  int xl = sx ^ sl;
  int hx = sh ^ sx;
  int xge_lo = (~xl & ((dxl >> 31) + 1)) | (xl & (sx + 1));
  int hi_ge_x = (~hx & ((dhx >> 31) + 1)) | (hx & (sh + 1));
  return xge_lo & hi_ge_x;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int int_max = ~(1 << 31);
  int int_min = 1 << 31;
  int sx = x >> 31;
  int t = x << 2;
  int back = t >> 2;
  int of_shift = ((back ^ x) | (~(back ^ x) + 1)) >> 31;
  int r = t + x;
  int same_tx = ~((t ^ x) >> 31);
  int diff_tr = (t ^ r) >> 31;
  int of_add = same_tx & diff_tr;
  int of = of_shift | of_add;
  int sat = int_max ^ ((int_max ^ int_min) & sx);
  return r ^ ((r ^ sat) & of);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int s1 = x + y;
  int s2 = s1 + z;
  int sx = (x >> 31) & 1;
  int sy = (y >> 31) & 1;
  int sz = (z >> 31) & 1;
  int ss1 = (s1 >> 31) & 1;
  int ss2 = (s2 >> 31) & 1;
  int nsx = sx ^ 1;
  int nsy = sy ^ 1;
  int nsz = sz ^ 1;
  int nss1 = ss1 ^ 1;
  int nss2 = ss2 ^ 1;
  int pos1 = nsx & nsy & ss1;
  int neg1 = sx & sy & nss1;
  int pos2 = nss1 & nsz & ss2;
  int neg2 = ss1 & sz & nss2;
  int pos_tot = pos1 + pos2;
  int neg_tot = neg1 + neg2;
  int K = pos_tot + (~neg_tot + 1);
  int Kn = (K >> 31) & 1;
  int Kz = !K;
  int Kp = (Kn ^ 1) & (Kz ^ 1);
  return Kp + (~Kn + 1);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;
  if (exp == 0xFFu) return uf;
  if (!(exp | frac)) return uf;

  unsigned M = exp ? (frac | 0x800000u) : frac;
  int iexp = exp;
  int E;
  if (iexp) E = iexp - 150;
  else E = -149;
  unsigned M3 = M + M + M;
  E = E - 1;

  unsigned t = M3;
  int p = 0;
  if (t >> 16) { p += 16; t >>= 16; }
  if (t >> 8)  { p += 8;  t >>= 8; }
  if (t >> 4)  { p += 4;  t >>= 4; }
  if (t >> 2)  { p += 2;  t >>= 2; }
  if (t >> 1)  { p += 1; }

  int Eb = E + p + 127;
  if (Eb >= 255) return sign | 0x7F800000u;

  unsigned Mn;
  if (Eb <= 0) {
    int k = -(E + 149);
    if (k <= 0) return sign;
    if (k >= 32) return sign;
    Mn = M3 >> k;
    unsigned r = (M3 >> (k - 1)) & 1;
    unsigned s = (M3 & ((1u << (k - 1)) - 1)) != 0;
    if (r && (s || (Mn & 1))) Mn++;
    if (Mn >= (1u << 23)) return sign | (1u << 23) | (Mn & 0x7FFFFFu);
    return sign | Mn;
  }

  int sh = p - 23;
  if (sh <= 0) {
    Mn = M3;
  } else {
    Mn = M3 >> sh;
    unsigned r = (M3 >> (sh - 1)) & 1;
    unsigned s = (M3 & ((1u << (sh - 1)) - 1)) != 0;
    if (r && (s || (Mn & 1))) {
      Mn++;
      if (Mn >= (1u << 24)) { Mn >>= 1; Eb++; }
    }
  }
  if (Eb >= 255) return sign | 0x7F800000u;
  unsigned uEb = Eb;
  return sign | (uEb << 23) | (Mn & 0x7FFFFFu);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;

  if (exp == 0xFFu) return uf;
  if (exp == 0) return sign;

  int iexp = exp;
  int E = iexp - 127;
  if (E >= 23) return uf;

  if (E < 0) {
    if (E == -1 && frac) return sign | 0x3F800000u;
    return sign;
  }

  unsigned M = frac | 0x800000u;
  int shift = 23 - E;
  unsigned ipart = M >> shift;
  unsigned rem = M & ((1u << shift) - 1);
  unsigned half = 1u << (shift - 1);
  if (rem > half || (rem == half && (ipart & 1))) ipart++;

  int p = 0;
  unsigned v = ipart;
  if (v >> 16) { p += 16; v >>= 16; }
  if (v >> 8)  { p += 8;  v >>= 8; }
  if (v >> 4)  { p += 4;  v >>= 4; }
  if (v >> 2)  { p += 2;  v >>= 2; }
  if (v >> 1)  { p += 1; v >>= 1; }

  int Eb = p + 127;
  unsigned mant;
  if (p <= 23) mant = (ipart << (23 - p)) & 0x7FFFFFu;
  else mant = (ipart >> (p - 23)) & 0x7FFFFFu;
  unsigned uEb = Eb;
  return sign | (uEb << 23) | mant;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign = 0;
  unsigned ux = x;
  if (x < 0) {
    sign = 0x80000000u;
    ux = -x;
  }
  if (ux == 0) return 0;

  int p = 0;
  unsigned t = ux;
  if (t >> 16) { p += 16; t >>= 16; }
  if (t >> 8)  { p += 8;  t >>= 8; }
  if (t >> 4)  { p += 4;  t >>= 4; }
  if (t >> 2)  { p += 2;  t >>= 2; }
  if (t >> 1)  { p += 1; }

  int Eb = p + 127;
  unsigned mant;
  if (p <= 23) mant = (ux << (23 - p)) & 0x7FFFFFu;
  else {
    int sh = p - 23;
    mant = (ux >> sh) & 0x7FFFFFu;
    unsigned rem = ux & ((1u << sh) - 1);
    unsigned half = 1u << (sh - 1);
    if (rem > half || (rem == half && (mant & 1))) {
      mant++;
      if (mant == 0x800000u) { mant = 0; Eb++; }
    }
  }
  if (Eb >= 255) return sign | 0x7F800000u;
  unsigned uEb = Eb;
  return sign | (uEb << 23) | mant;
}


// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1 = 0x55 | (0x55 << 8);
  m1 = m1 | (m1 << 16);
  int m2 = 0x33 | (0x33 << 8);
  m2 = m2 | (m2 << 16);
  int m4 = 0x0F | (0x0F << 8);
  m4 = m4 | (m4 << 16);
  int m8 = 0xFF | (0xFF << 16);
  int m16 = 0xFF | (0xFF << 8);
  int t = (x & m1) + ((x >> 1) & m1);
  t = (t & m2) + ((t >> 2) & m2);
  t = (t + (t >> 4)) & m4;
  t = (t + (t >> 8)) & m8;
  t = (t + (t >> 16)) & m16;
  return t & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int m1 = 0x55 | (0x55 << 8);
  m1 = m1 | (m1 << 16);
  int m2 = 0x33 | (0x33 << 8);
  m2 = m2 | (m2 << 16);
  int m4 = 0x0F | (0x0F << 8);
  m4 = m4 | (m4 << 16);
  int m8 = 0xFF << 8;
  x = ((x & m1) << 1) | ((x >> 1) & m1);
  x = ((x & m2) << 2) | ((x >> 2) & m2);
  x = ((x & m4) << 4) | ((x >> 4) & m4);
  x = ((x & 0xFF) << 24) | ((x & m8) << 8) | ((x >> 8) & m8) | ((x >> 24) & 0xFF);
  return x;
}
