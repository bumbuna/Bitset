#ifndef BITSET_H
#define BITSET_H

typedef unsigned int _u32;
typedef _u32* _u32ptr;


#define SET_ARRAY_DEFAULT_CAPACITY 256
#define _U32BITS 32
#define _U32BYTES 4
#define SET_ARRAY_DEFAULT_SIZE (SET_ARRAY_DEFAULT_CAPACITY/_U32BITS)

struct bitset {
	int complement:1;
	int capacity;
	_u32    defaultArray[SET_ARRAY_DEFAULT_SIZE];
	_u32ptr array;
};

struct bitset* bitsetCreate(void);

void bitsetDelete(struct bitset*);

void bitsetAddMember(struct bitset*, int);

void bitsetRemoveMember(struct bitset*, int);

int bitsetCompare(struct bitset*, struct bitset*);

int bitsetIsMember(struct bitset*, int);

int bitsetUnion(struct bitset*, struct bitset*);

int bitsetDisjoint(struct bitset*, struct bitset*);

int bitsetDifference(struct bitset*, struct bitset*);

void bitsetForeach(struct bitset*, int (*)(void*,int), void*);

void bitsetComplement(struct bitset*);

void bitsetInvert(struct bitset*);

int bitsetEqual(struct bitset*, struct bitset*);

int bitsetSize(struct bitset*);
#endif //BITSET_H