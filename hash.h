#ifndef HASH_H
#define HASH_H

// #include "variablehash.h"
// #include "labelhash.h"

#define NAME(P)((P) -> name)
#define NEXT(P)((P) -> next)

#define NHASH 4
#define MULTIPLICADOR 31

//----------------------------------------

unsigned int hash(char *str);

//----------------------------------------

#endif
