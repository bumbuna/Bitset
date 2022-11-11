#include "bitset.h"
#include "stdio.h"
#include "assert.h"

int main(int argc, char const *argv[])
{
	struct bitset *set = bitsetCreate();
	for(int i = 0; i < 256; i++) {
		bitsetAddMember(set, i);
	}
	assert(bitsetSize(set)==256);
	for(int i = 0; i < 20; i++) bitsetRemoveMember(set, i);
	assert(bitsetSize(set) == 236);
	bitsetForeach(set, (void*) printf, "%d, ");
	printf("\n");
	return 0;
}