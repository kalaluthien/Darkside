#ifndef __W_LAMBDA_UTILS_H__
#define __W_LAMBDA_UTILS_H__

// Stringify
#define STRINGIFY(...) _LAMBDA_UTILS_STRINGIFY_LAZY(__VA_ARGS__)
#define _LAMBDA_UTILS_STRINGIFY_LAZY(...) #__VA_ARGS__

// Counting
#define _LAMBDA_UTILS_NUM_OF_ARGS(...) \
  _LAMBDA_UTILS_NUM_OF_ARGS_MAX_9(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define _LAMBDA_UTILS_NUM_OF_ARGS_MAX_9(_9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N

// Concatenation
#define CONCAT(A, B) _LAMBDA_UTILS_CONCAT_LAZY(A, B)
#define _LAMBDA_UTILS_CONCAT_LAZY(A, B) A ## B

#define _LAMBDA_UTILS_AT_(N, ...) CONCAT(_LAMBDA_UTILS_AT_, N)(__VA_ARGS__)
#define _LAMBDA_UTILS_AT_0(_0, ...) _0
#define _LAMBDA_UTILS_AT_1(_0, _1, ...) _1
#define _LAMBDA_UTILS_AT_2(_0, _1, _2, ...) _2
#define _LAMBDA_UTILS_AT_3(_0, _1, _2, _3, ...) _3
#define _LAMBDA_UTILS_AT_4(_0, _1, _2, _3, _4, ...) _4
#define _LAMBDA_UTILS_AT_5(_0, _1, _2, _3, _4, _5, ...) _5
#define _LAMBDA_UTILS_AT_6(_0, _1, _2, _3, _4, _5, _6, ...) _6
#define _LAMBDA_UTILS_AT_7(_0, _1, _2, _3, _4, _5, _6, _7, ...) _7
#define _LAMBDA_UTILS_AT_8(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) _8
#define _LAMBDA_UTILS_AT_9(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) _9

#define _LAMBDA_UTILS_UNTIL_(N, ...) CONCAT(_LAMBDA_UTILS_UNTIL_, N)(__VA_ARGS__)
#define _LAMBDA_UTILS_UNTIL_0(_0, ...)
#define _LAMBDA_UTILS_UNTIL_1(_0, _1, ...)
#define _LAMBDA_UTILS_UNTIL_2(_0, _1, _2, ...) _1
#define _LAMBDA_UTILS_UNTIL_3(_0, _1, _2, _3, ...) _1, _2
#define _LAMBDA_UTILS_UNTIL_4(_0, _1, _2, _3, _4, ...) _1, _2, _3
#define _LAMBDA_UTILS_UNTIL_5(_0, _1, _2, _3, _4, _5, ...) _1, _2, _3, _4
#define _LAMBDA_UTILS_UNTIL_6(_0, _1, _2, _3, _4, _5, _6, ...) _1, _2, _3, _4, _5
#define _LAMBDA_UTILS_UNTIL_7(_0, _1, _2, _3, _4, _5, _6, _7, ...) _1, _2, _3, _4, _5, _6
#define _LAMBDA_UTILS_UNTIL_8(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) _1, _2, _3, _4, _5, _6, _7
#define _LAMBDA_UTILS_UNTIL_9(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) _1, _2, _3, _4, _5, _6, _7, _8

#define GET_LAST(...) \
  _LAMBDA_UTILS_AT_(\
      _LAMBDA_UTILS_NUM_OF_ARGS(__VA_ARGS__), NULL, __VA_ARGS__, NULL)

#define GET_INIT(...) \
  _LAMBDA_UTILS_UNTIL_(\
      _LAMBDA_UTILS_NUM_OF_ARGS(__VA_ARGS__), NULL, __VA_ARGS__, NULL)

#endif // __W_LAMBDA_UTILS_H__
