#include "bitset.h"
#include "stdlib.h"
#include "string.h"

struct bitset* bitsetCreate(void) {
	struct bitset *newBitset = calloc(1, sizeof(struct bitset));
	if(!newBitset) {
		return NULL;
	}
	newBitset->capacity = SET_ARRAY_DEFAULT_CAPACITY;
	newBitset->array = newBitset->defaultArray;
	return newBitset;
}

void bitsetDelete(struct bitset* set) {
	if(set) {
		if(set->array != set->defaultArray) {
			free(set->array);
		}
		free(set);
	}
}

void bitsetAddMember(struct bitset* set, int m) {
	if(!set) return;
	if(set->capacity <= m) {
		int newCapacity = (m/_U32BITS+(m%_U32BITS ? 0 : 1)) * _U32BITS;
		_u32ptr newArray = malloc(newCapacity/_U32BYTES);
		memcpy(newArray, set->array, set->capacity/_U32BYTES);
		memset(&newArray[set->capacity/_U32BYTES], 0, (newCapacity-set->capacity)/_U32BYTES);
		if(set->array != set->defaultArray) {
			free(set->array);
		}
		set->array = newArray;
		set->capacity = newCapacity;
	}
	set->array[m/_U32BITS] |= ((_u32)1 << (m%_U32BITS));
}

void bitsetRemoveMember(struct bitset* set, int m) {
	if(!set) return;
	if(set->capacity <= m) return;
	set->array[m/_U32BITS] &= ~((_u32)1 << (m%_U32BITS));
}

int bitsetCompare(struct bitset*, struct bitset*);

int bitsetIsMember(struct bitset* set, int m) {
	if(!set) return 0;
	if(set->capacity <= m) return 0;
	return (set->array[m/_U32BITS] & ~((_u32)1 << (m%_U32BITS))) ? !set->complement : set->complement;
}

int bitsetUnion(struct bitset*, struct bitset*);

int bitsetDisjoint(struct bitset*, struct bitset*);

int bitsetDifference(struct bitset*, struct bitset*);

void bitsetForeach(struct bitset* set, int (*fun)(void*,int), void* data) {
	if(!set||!fun) return;
	for(int i = 0; i < set->capacity; i++) {
		if(bitsetIsMember(set, i)) {
			if(!(*fun)(data, i)) {
				break;
			}
		}
	}
}

void bitsetComplement(struct bitset* set) {
	if(!set) return;
	set->complement = ~set->complement;
}

void bitsetInvert(struct bitset* set) {
	if(!set) return;
	const int u32s = set->capacity/_U32BITS;
	for(int i = 0; i < u32s; i++) {
		set->array[i] = ~set->array[i];
	}
}

int bitsetEqual(struct bitset*, struct bitset*);

int bitsetSize(struct bitset* set) {
	if(!set) return 0;
	/* onsies[i] = bits set to 1 in integer i*/
	static char onsies[256] = {
		0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
		4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
	};
	int count = 0;
	unsigned char *a = (void*) set->array;
	int bytes = set->capacity/_U32BITS*_U32BYTES;
	for(int i = 0; i < bytes; i++) {
		count += onsies[a[i]];
	}
	return count;
}