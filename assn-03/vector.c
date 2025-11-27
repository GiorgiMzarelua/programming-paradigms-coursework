#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation)
{
  assert(elemSize > 0);
  assert(initialAllocation >= 0);
  v->log_length = 0;
  if(initialAllocation == 0){
    initialAllocation = 4;
  }
  v->alloc_length = initialAllocation;
  v->freeFn = freeFn;
  v->elem_size = elemSize;
  v->init_alloc = initialAllocation;
  v->elems = malloc(v->alloc_length * v->elem_size);
  assert(v->elems != NULL);
}

void VectorDispose(vector *v)
{
  if (v->freeFn != NULL) {
        for (int i = 0; i < v->log_length; i++) {
            void *elemToFree = (char *) v->elems + i * v->elem_size;
            v->freeFn(elemToFree);
        }
    }
    free(v->elems); 
}

int VectorLength(const vector *v)
{ 
  return v->log_length;
}

void *VectorNth(const vector *v, int position)
{ 
  assert(position >= 0);
  assert(position < v->log_length);
  void* ans = (char*)v->elems + position * v->elem_size;
  return ans;
}

void VectorReplace(vector *v, const void *elemAddr, int position)
{
  assert(position >= 0);
  assert(position < v->log_length);
  if(v->freeFn != NULL){
    v->freeFn((char*)v->elems + position * v->elem_size);
  }
  memcpy((char*)v->elems + position * v->elem_size, elemAddr, v->elem_size);
}

void VectorInsert(vector *v, const void *elemAddr, int position)
{
  assert(position >= 0);
  assert(position <= v->log_length);
  if(v->log_length == v->alloc_length){
    v->alloc_length += v->init_alloc;
    v->elems = realloc(v->elems, v->alloc_length * v->elem_size);
    assert(v->elems != NULL);
  }  
  int forTakeSize = v->elem_size * (v->log_length - position);
  if(forTakeSize != 0) memmove((char*)v->elems + (position + 1) * v->elem_size, (char*)v->elems + position * v->elem_size, forTakeSize);
  memcpy((char*)v->elems + position * v->elem_size, elemAddr, v->elem_size);
  v->log_length++;

}

void VectorAppend(vector *v, const void *elemAddr)
{
  if(v->log_length == v->alloc_length){
    v->alloc_length += v->init_alloc;
    v->elems = realloc(v->elems, v->alloc_length * v->elem_size);
    assert(v->elems != NULL);
  }  
  memcpy((char*)v->elems + v->log_length * v->elem_size, elemAddr, v->elem_size);
  v->log_length++;
}

void VectorDelete(vector *v, int position)
{
  assert(position >= 0);
  assert(position < v->log_length);
  if(v->freeFn != NULL){
    v->freeFn((char*)v->elems + position * v->elem_size);
  }
  int forTakeSize = v->elem_size * (v->log_length - position);
  if(forTakeSize != 0) memmove((char*)v->elems + position * v->elem_size, (char*)v->elems + (position + 1) * v->elem_size, forTakeSize);
  v->log_length--;
}

void VectorSort(vector *v, VectorCompareFunction compare)
{
  assert(compare != NULL);
  qsort(v->elems, v->log_length, v->elem_size, compare);
}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData)
{
  assert(mapFn != NULL);
  for(int i = 0; i < v->log_length; i++){
    mapFn((char*)v->elems + v->elem_size * i, auxData);
  }
}

static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted)
{
  assert(startIndex >= 0);
  assert(startIndex <= v->log_length); 
  assert(key != NULL);
  assert(searchFn != NULL);
  if (isSorted == true) {
    void* found = bsearch(key, v->elems, v->log_length, v->elem_size, searchFn);
    if (found == NULL) return kNotFound;
    return ((char*)found - (char*)v->elems) / v->elem_size;
  }
  for (int i = startIndex; i < v->log_length; i++) {
    void* elemAddr = (char*)v->elems + i * v->elem_size;
    if (searchFn(key, elemAddr) == 0) {  
      return i;
    }
  }
  return kNotFound;
}