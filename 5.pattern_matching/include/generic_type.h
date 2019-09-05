#ifndef __W_GENERIC_TYPE_H__
#define __W_GENERIC_TYPE_H__

#if __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////

#define CONCAT_(x, y) x ## _ ## y
#define CONCAT(x, y) CONCAT_(x, y)

#define INSTANCE_OF(T, ...) \
typedef struct T(__VA_ARGS__) T(__VA_ARGS__);\
struct T(__VA_ARGS__) T##_of(__VA_ARGS__)

#define AS(T, V) ( *((T *)&V) )

////////////////////////////////////////////////////
// Pair Type Decl
////////////////////////////////////////////////////

#define pair(T1, T2) CONCAT(pair, CONCAT(T1, T2))
#define pair_of(T1, T2) { T1 fst; T2 snd; }

#define DECL_PAIR(T1, T2) INSTANCE_OF(pair, T1, T2)

////////////////////////////////////////////////////
// Maybe Type Decl
////////////////////////////////////////////////////

#define maybe(T) CONCAT(maybe, T)
#define maybe_of(T) \
{\
  enum { Nothing, Just } match_tag;\
  union { void *Nothing; T Just; } match_val;\
}

#define DECL_MAYBE(T) INSTANCE_OF(maybe, T)

////////////////////////////////////////////////////
// List Type Decl
////////////////////////////////////////////////////

#define list(T) CONCAT(list, T)
#define list_of(T) \
{\
  enum { Nil, Cons } match_tag;\
  union { void *Nil; struct { T head; void *tail; } Cons; } match_val;\
}

#define DECL_LIST(T) INSTANCE_OF(list, T)
#define IMPORT_LIST(T, func) func##_of(T)

/* list(T) list_push(T, list(T) *); */
#define list_push(T) CONCAT(list_push, T)
#define list_push_of(T) \
static list(T) list_push(T)(T x, list(T) *xs) \
{\
  list(T) l;\
  l.match_tag = Cons;\
  l.match_val.Cons.head = x;\
  AS(list(T) *, l.match_val.Cons.tail) = xs;\
  return l;\
}

/* T list_head(list(T) *); */
#define list_head(T) CONCAT(list_head, T)
#define list_head_of(T) \
static T list_head(T)(list(T) *l)\
{\
  return l->match_val.Cons.head;\
}

/* list(T) *list_tail(list(T) *); */
#define list_tail(T) CONCAT(list_tail, T)
#define list_tail_of(T) \
static list(T) *list_tail(T)(list(T) *l)\
{\
  return AS(list(T) *, l->match_val.Cons.tail);\
}

////////////////////////////////////////////////////

#if __cplusplus
}
#endif

#endif // __W_GENERIC_TYPE_H__
