#include "hashset.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void HashSetNew(hashset *h, int elemSize, int numBuckets,
		HashSetHashFunction hashfn, HashSetCompareFunction comparefn, HashSetFreeFunction freefn)
{
  assert(elemSize > 0);
  assert(numBuckets > 0);
  assert(hashfn != NULL);
  assert(comparefn != NULL);
  h->nBuckets = numBuckets;
  h->freefn = freefn;
  h->hashfn = hashfn;
  h->count = 0;
  h->comparefn = comparefn;
  h->buckets = malloc(h->nBuckets * sizeof(vector));
  for(int i = 0; i < numBuckets; i++){
	VectorNew(&h->buckets[i], elemSize, freefn, 10);
  }
}

void HashSetDispose(hashset *h)
{
  for(int i = 0; i < h->nBuckets; i++){
	VectorDispose(&h->buckets[i]);
  }
  free(h->buckets);
}

int HashSetCount(const hashset *h)
{ 
  return h->count;
}

void HashSetMap(hashset *h, HashSetMapFunction mapfn, void *auxData)
{
  assert(mapfn != NULL);
  for(int i = 0; i < h->nBuckets; i++){
	VectorMap(&h->buckets[i], mapfn, auxData);
  }
}

void HashSetEnter(hashset *h, const void *elemAddr)
{
  assert(elemAddr != NULL);
  int hashCode = h->hashfn(elemAddr, h->nBuckets);
  assert(hashCode >= 0);
  assert(hashCode < h->nBuckets);
  int pos = VectorSearch(&h->buckets[hashCode], elemAddr, h->comparefn, 0, false);
  if(pos == -1){
	VectorAppend(&h->buckets[hashCode], elemAddr);
	h->count++;
	return;
  }
  VectorReplace(&h->buckets[hashCode], elemAddr, pos);
}

void *HashSetLookup(const hashset *h, const void *elemAddr)
{ 
  assert(elemAddr != NULL);
  int hashCode = h->hashfn(elemAddr, h->nBuckets);
  assert(hashCode >= 0);
  assert(hashCode < h->nBuckets);
  int pos = VectorSearch(&h->buckets[hashCode], elemAddr, h->comparefn, 0, false);  
  if(pos == -1){
	return NULL;
  }
  return VectorNth(&h->buckets[hashCode], pos); 
}
