/*-------------------------------------------------------------------
 *  UW CSE 351 Summer 2013 Lab 5 Starter code: 
 *        single doubly-linked free block list with LIFO policy
 *        with support for coalescing adjacent free blocks
 *
 * Terminology:
 * o We will implement an explicit free list allocator
 * o We use "next" and "previous" to refer to blocks as ordered in
 *   the free list.
 * o We use "following" and "preceding" to refer to adjacent blocks
 *   in memory.
 *-------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "memlib.h"
#include "mm.h"

/* Macros for unscaled pointer arithmetic to keep other code cleaner.  
   Casting to a char* has the effect that pointer arithmetic happens at
   the byte granularity (i.e. POINTER_ADD(0x1, 1) would be 0x2).  (By
   default, incrementing a pointer in C has the effect of incrementing
   it by the size of the type to which it points (e.g. BlockInfo).)
   We cast the result to void* to force you to cast back to the 
   appropriate type and ensure you don't accidentally use the resulting
   pointer as a char* implicitly.  You are welcome to implement your
   own pointer arithmetic instead of using these macros.
*/
#define UNSCALED_POINTER_ADD(p,x) ((void*)((char*)(p) + (x)))
#define UNSCALED_POINTER_SUB(p,x) ((void*)((char*)(p) - (x)))


/******** FREE LIST IMPLEMENTATION ***********************************/


/* A BlockInfo contains information about a block, including the size
   and usage tags, as well as pointers to the next and previous blocks
   in the free list.  This is exactly the "explicit free list" structure
   illustrated in the lecture slides.
   
   Note that the next and prev pointers and the boundary tag are only
   needed when the block is free.  To achieve better utilization, mm_malloc
   should use the space for next and prev as part of the space it returns.

   +--------------+
   | sizeAndTags  |  <-  BlockInfo pointers in free list point here
   |  (header)    |
   +--------------+
   |     next     |  <-  Pointers returned by mm_malloc point here
   +--------------+
   |     prev     |
   +--------------+
   |  space and   |
   |   padding    |
   |     ...      |
   |     ...      |
   +--------------+
   | boundary tag |
   |  (footer)    |
   +--------------+
*/
struct BlockInfo {
  // Size of the block (in the high bits) and tags for whether the
  // block and its predecessor in memory are in use.  See the SIZE()
  // and TAG macros, below, for more details.
  size_t sizeAndTags;
  // Pointer to the next block in the free list.
  struct BlockInfo* next;
  // Pointer to the previous block in the free list.
  struct BlockInfo* prev;
};
typedef struct BlockInfo BlockInfo;


/* Pointer to the first BlockInfo in the free list, the list's head. 
   
   A pointer to the head of the free list in this implementation is
   always stored in the first word in the heap.  mem_heap_lo() returns
   a pointer to the first word in the heap, so we cast the result of
   mem_heap_lo() to a BlockInfo** (a pointer to a pointer to
   BlockInfo) and dereference this to get a pointer to the first
   BlockInfo in the free list. */
#define FREE_LIST_HEAD *((BlockInfo **)mem_heap_lo())

/* Size of a word on this architecture. */
#define WORD_SIZE sizeof(void*)

/* Minimum block size (to account for size header, next ptr, prev ptr,
   and boundary tag) */
#define MIN_BLOCK_SIZE (sizeof(BlockInfo) + WORD_SIZE)

/* Alignment of blocks returned by mm_malloc. */
#define ALIGNMENT 8

/* SIZE(blockInfo->sizeAndTags) extracts the size of a 'sizeAndTags' field.
   Also, calling SIZE(size) selects just the higher bits of 'size' to ensure
   that 'size' is properly aligned.  We align 'size' so we can use the low
   bits of the sizeAndTags field to tag a block as free/used, etc, like this:
   
      sizeAndTags:
      +-------------------------------------------+
      | 63 | 62 | 61 | 60 |  . . . .  | 2 | 1 | 0 |
      +-------------------------------------------+
        ^                                       ^
      high bit                               low bit

   Since ALIGNMENT == 8, we reserve the low 3 bits of sizeAndTags for tag
   bits, and we use bits 3-63 to store the size.

   Bit 0 (2^0 == 1): TAG_USED
   Bit 1 (2^1 == 2): TAG_PRECEDING_USED
*/
#define SIZE(x) ((x) & ~(ALIGNMENT - 1))

/* TAG_USED is the bit mask used in sizeAndTags to mark a block as used. */
#define TAG_USED 1 

/* TAG_PRECEDING_USED is the bit mask used in sizeAndTags to indicate
   that the block preceding it in memory is used. (used in turn for
   coalescing).  If the previous block is not used, we can learn the size
   of the previous block from its boundary tag */
#define TAG_PRECEDING_USED 2


/* Find a free block of the requested size in the free list.  Returns
   NULL if no free block is large enough. */
static void * searchFreeList(size_t reqSize) {   
  BlockInfo* freeBlock;

  freeBlock = FREE_LIST_HEAD;
  while (freeBlock != NULL){
    if (SIZE(freeBlock->sizeAndTags) >= reqSize) {
      return freeBlock;
    } else {
      freeBlock = freeBlock->next;
    }
  }
  return NULL;
}
           
/* Insert freeBlock at the head of the list.  (LIFO) */
static void insertFreeBlock(BlockInfo* freeBlock) {
  BlockInfo* oldHead = FREE_LIST_HEAD;
  freeBlock->next = oldHead;
  if (oldHead != NULL) {
    oldHead->prev = freeBlock;
  }
  //  freeBlock->prev = NULL;
  FREE_LIST_HEAD = freeBlock;
}      

/* Remove a free block from the free list. */
static void removeFreeBlock(BlockInfo* freeBlock) {
  BlockInfo *nextFree, *prevFree;
  
  nextFree = freeBlock->next;
  prevFree = freeBlock->prev;

  // If the next block is not null, patch its prev pointer.
  if (nextFree != NULL) {
    nextFree->prev = prevFree;
  }

  // If we're removing the head of the free list, set the head to be
  // the next block, otherwise patch the previous block's next pointer.
  if (freeBlock == FREE_LIST_HEAD) {
    FREE_LIST_HEAD = nextFree;
  } else {
    prevFree->next = nextFree;
  }
}

/* Coalesce 'oldBlock' with any preceeding or following free blocks. */
static void coalesceFreeBlock(BlockInfo* oldBlock) {
  BlockInfo *blockCursor;
  BlockInfo *newBlock;
  BlockInfo *freeBlock;
  // size of old block
  size_t oldSize = SIZE(oldBlock->sizeAndTags);
  // running sum to be size of final coalesced block
  size_t newSize = oldSize;

  // Coalesce with any preceding free block
  blockCursor = oldBlock;
  while ((blockCursor->sizeAndTags & TAG_PRECEDING_USED)==0) { 
    // While the block preceding this one in memory (not the
    // prev. block in the free list) is free:

    // Get the size of the previous block from its boundary tag.
    size_t size = SIZE(*((size_t*)UNSCALED_POINTER_SUB(blockCursor, WORD_SIZE)));
    // Use this size to find the block info for that block.
    freeBlock = (BlockInfo*)UNSCALED_POINTER_SUB(blockCursor, size);
    // Remove that block from free list.
    removeFreeBlock(freeBlock);

    // Count that block's size and update the current block pointer.
    newSize += size;
    blockCursor = freeBlock;
  }
  newBlock = blockCursor;

  // Coalesce with any following free block.
  // Start with the block following this one in memory
  blockCursor = (BlockInfo*)UNSCALED_POINTER_ADD(oldBlock, oldSize);
  while ((blockCursor->sizeAndTags & TAG_USED)==0) {
    // While the block is free:

    size_t size = SIZE(blockCursor->sizeAndTags);
    // Remove it from the free list.
    removeFreeBlock(blockCursor);
    // Count its size and step to the following block.
    newSize += size;
    blockCursor = (BlockInfo*)UNSCALED_POINTER_ADD(blockCursor, size);
  }
  
  // If the block actually grew, remove the old entry from the free
  // list and add the new entry.
  if (newSize != oldSize) {
    // Remove the original block from the free list
    removeFreeBlock(oldBlock);

    // Save the new size in the block info and in the boundary tag
    // and tag it to show the preceding block is used (otherwise, it
    // would have become part of this one!).
    newBlock->sizeAndTags = newSize | TAG_PRECEDING_USED;
    // The boundary tag of the preceding block is the word immediately
    // preceding block in memory where we left off advancing blockCursor.
    *(size_t*)UNSCALED_POINTER_SUB(blockCursor, WORD_SIZE) = newSize | TAG_PRECEDING_USED;  

    // Put the new block in the free list.
    insertFreeBlock(newBlock);
  }
  return;
}

/* Get more heap space of size at least reqSize. */
static void requestMoreSpace(size_t reqSize) {
  size_t pagesize = mem_pagesize();
  size_t numPages = (reqSize + pagesize - 1) / pagesize;
  BlockInfo *newBlock;
  size_t totalSize = numPages * pagesize;
  size_t prevLastWordMask;

  void* mem_sbrk_result = mem_sbrk(totalSize);
  if ((size_t)mem_sbrk_result == -1) {
    printf("ERROR: mem_sbrk failed in requestMoreSpace\n");
    exit(0);
  }
  newBlock = (BlockInfo*)UNSCALED_POINTER_SUB(mem_sbrk_result, WORD_SIZE);

  /* initialize header, inherit TAG_PRECEDING_USED status from the
     previously useless last word however, reset the fake TAG_USED
     bit */
  prevLastWordMask = newBlock->sizeAndTags & TAG_PRECEDING_USED;
  newBlock->sizeAndTags = totalSize | prevLastWordMask;
  // Initialize boundary tag.
  ((BlockInfo*)UNSCALED_POINTER_ADD(newBlock, totalSize - WORD_SIZE))->sizeAndTags = 
    totalSize | prevLastWordMask;

  /* initialize "new" useless last word
     the previous block is free at this moment
     but this word is useless, so its use bit is set
     This trick lets us do the "normal" check even at the end of
     the heap and avoid a special check to see if the following
     block is the end of the heap... */
  *((size_t*)UNSCALED_POINTER_ADD(newBlock, totalSize)) = TAG_USED;

  // Add the new block to the free list and immediately coalesce newly
  // allocated memory space
  insertFreeBlock(newBlock);
  coalesceFreeBlock(newBlock);
}

/* Initialize the allocator. */
int mm_init () {
  // Head of the free list.
  BlockInfo *firstFreeBlock;

  // Initial heap size: WORD_SIZE byte heap-header (stores pointer to head
  // of free list), MIN_BLOCK_SIZE bytes of space, WORD_SIZE byte heap-footer.
  size_t initSize = WORD_SIZE+MIN_BLOCK_SIZE+WORD_SIZE;
  size_t totalSize;

  void* mem_sbrk_result = mem_sbrk(initSize);
  //  printf("mem_sbrk returned %p\n", mem_sbrk_result);
  if ((ssize_t)mem_sbrk_result == -1) {
    printf("ERROR: mem_sbrk failed in mm_init, returning %p\n", 
           mem_sbrk_result);
    exit(1);
  }

  firstFreeBlock = (BlockInfo*)UNSCALED_POINTER_ADD(mem_heap_lo(), WORD_SIZE);

  // Total usable size is full size minus heap-header and heap-footer words
  // NOTE: These are different than the "header" and "footer" of a block!
  // The heap-header is a pointer to the first free block in the free list.
  // The heap-footer is used to keep the data structures consistent (see
  // requestMoreSpace() for more info, but you should be able to ignore it).
  totalSize = initSize - WORD_SIZE - WORD_SIZE;

  // The heap starts with one free block, which we initialize now.
  firstFreeBlock->sizeAndTags = totalSize | TAG_PRECEDING_USED;
  firstFreeBlock->next = NULL;
  firstFreeBlock->prev = NULL;
  // boundary tag
  *((size_t*)UNSCALED_POINTER_ADD(firstFreeBlock, totalSize - WORD_SIZE)) = totalSize | TAG_PRECEDING_USED;
  
  // Tag "useless" word at end of heap as used.
  // This is the is the heap-footer.
  *((size_t*)UNSCALED_POINTER_SUB(mem_heap_hi(), WORD_SIZE - 1)) = TAG_USED;

  // set the head of the free list to this new free block.
  FREE_LIST_HEAD = firstFreeBlock;
  return 0;
}

// Adding examine_heap()
/* Print the heap by iterating through it as an implicit free list. */
static void examine_heap() {
    BlockInfo *block;

      /* print to stderr so output isn't buffered and not output if we crash */
      fprintf(stderr, "FREE_LIST_HEAD: %p\n", (void *)FREE_LIST_HEAD);

        for(block = (BlockInfo *)UNSCALED_POINTER_ADD(mem_heap_lo(), WORD_SIZE); /* first block on heap */
                  SIZE(block->sizeAndTags) != 0 && block < mem_heap_hi();
                        block = (BlockInfo *)UNSCALED_POINTER_ADD(block, SIZE(block->sizeAndTags))) {

              /* print out common block attributes */
              fprintf(stderr, "%p: %ld %ld %ld\t",
                      (void *)block,
                          SIZE(block->sizeAndTags),
                              block->sizeAndTags & TAG_PRECEDING_USED,
                                  block->sizeAndTags & TAG_USED);

                  /* and allocated/free specific data */
                  if (block->sizeAndTags & TAG_USED) {
                          fprintf(stderr, "ALLOCATED\n");
                              } else {
                                      fprintf(stderr, "FREE\tnext: %p, prev: %p\n",
                                                (void *)block->next,
                                                      (void *)block->prev);
                                          }
                    }
          fprintf(stderr, "END OF HEAP\n\n");
}


// TOP-LEVEL ALLOCATOR INTERFACE ------------------------------------


/* Allocate a block of size size and return a pointer to it. */
void* mm_malloc (size_t size) {
  size_t reqSize;
  BlockInfo * ptrFreeBlock = NULL; //fucking use this.
  //what is the ptr head initially pointing to?
  //need to add space if its null?
  //then add space, increment pointer an amount, build the first block etc and return
  //ONLY if it's null.
  //
  //1. how do we stick something in the _heap_ and not just a local variable? How do we get it out of the stackfram
  //sbrk adds heap space but how do we get there?
  //2. 
  size_t blockSize;
  size_t precedingBlockUseTag;
  void * ptrToReturn;
  size_t savedSize = size;

  // Zero-size requests get NULL.
  if (size == 0) {
    return NULL;
  }

  // Add one word for the initial size header.
  // Note that we don't need to boundary tag when the block is used!
  size += WORD_SIZE;
  if (size <= MIN_BLOCK_SIZE) {
    // Make sure we allocate enough space for a blockInfo in case we
    // free this block (when we free this block, we'll need to use the
    // next pointer, the prev pointer, and the boundary tag).
    reqSize = MIN_BLOCK_SIZE;
  } else {
    // Round up for correct alignment
    reqSize = ALIGNMENT * ((size + ALIGNMENT - 1) / ALIGNMENT);
  }
  //reqSize needs to include space for header and footer for when it becomes freed (because laziness)
  //looks like code already implements this... 

  // Implement mm_malloc.  You can change or remove any of the above
  // code.  It is included as a suggestion of where to start.
  // You will want to replace this return statement...\
  /* starting actual implementation pseudocode */
  //first create footer memory block if heap is null //do we need to?
  //yes, first need to allocate space on the heap, then create a free block,
  //and then alloc into it.

  if (FREE_LIST_HEAD == NULL) {
    //just to start off lets allocate a full 1024 bytes
    //so alloc 1024 + reqSize + enough wordsize for header and footer. header and footer space
    //not included in size. 
    size_t amountOfSpaceToRequest =  reqSize + 2 * WORD_SIZE /*space for the allocated block*/ + 1024; //space for free block
    requestMoreSpace(amountOfSpaceToRequest);
    //min size for alloced block is 4*wordsize because I want to be able to just make an alloced block a freeblock if i want to

    //now make allocated block at the beginning of the heap
    //first make size and header

    //actually fuckit just make the whole thing a free block, and then the rest of the method can assume theres a big enough free block to use
    //to make a free block we need to first make a blockinfo.
    //lets just make variables for each thing and then set the parts of a blockinfo equal to them
    size_t header;
    /* should be whole size of the heap at this point - 2 words (one for header and one for footer) */
    header = mem_heap_hi() - mem_heap_lo();
    header = header - 2 * WORD_SIZE;
    printf("size of header = %d\n", header);
    BlockInfo* prev = NULL;
    BlockInfo* next = NULL;
    BlockInfo * ptrFreeBlock = {header, prev, next};
    //stick it in the heap!
    insertFreeBlock(ptrFreeBlock);

    //now need to set footer block
    //since it's the first in the heap, we can just get a pointer to the last part of the heap..
    //but lets just iterate through...
    size_t * footerPtr = FREE_LIST_HEAD;
    // 
    int i;
    //could reduce this by makign i increment by word size but yolo
    for (i = 0; i < header; i++) {
      footerPtr = UNSCALED_POINTER_ADD(footerPtr, 1);
    }
    //now footerPtr should be at the last word
    *footerPtr = header;
    //and now our heap should be one giant free block == 1024 + reqszied
  }


  BlockInfo * blockToModify = searchFreeList(reqSize);
  if (blockToModify == NULL) {
    //allocate more space etc because a freeblock big enough wasnt found.
    //easiest way to do this is probably just add space, turn it into a free block, and then call malloc again
    requestMoreSpace(reqSize);
    BlockInfo * blockToAdd;
    blockToAdd->sizeAndTags = reqSize - WORD_SIZE;
    //poop
    insertFreeBlock(blockToAdd);
    ptrToReturn = mm_malloc(savedSize);

  } else {
    //oh fuck here we go
    //need to save the blocktomodifys prev and next for its smaller version if there is enough space shit.
    //lets jsut save em for now...in a blockinfo!
    BlockInfo * savedBlockToModify;
    savedBlockToModify->sizeAndTags = (*blockToModify).sizeAndTags;
    savedBlockToModify->next = (*blockToModify).next;
    savedBlockToModify->prev = (*blockToModify).prev;


    //now we need to squish down the blockToModify by at least 4 words
    //and big enough to hold a header and the __size.

    //first lets make the pieces of the alloced block
    //step one of the conversion process: convert the old block's header to the new block
    size_t allocBlockHeader = (size | 1);
    blockToModify->sizeAndTags = allocBlockHeader;
    //pointer to return will be the same as a pointer to the freed blocks next field.
    ptrToReturn = &((*blockToModify).next);
    //now need to move/make a new free block at the end if there is enough space.
    //can quickly find if there is enough by subtracting the old headers.
    if ((*savedBlockToModify).sizeAndTags - allocBlockHeader >= 4 * WORD_SIZE) {
      //make the smaller block
      size_t * ptrToSmallerFreeBlockHeader = ptrToReturn;
      //move pointer down to were new header is
      UNSCALED_POINTER_ADD(ptrToSmallerFreeBlockHeader, size); //size already includes the word size
      //set new free header value
      size_t smallerFreeBlockHeader = ((*savedBlockToModify).sizeAndTags - allocBlockHeader + 1);
      *ptrToSmallerFreeBlockHeader = smallerFreeBlockHeader;
      //POOP ERROR
      //set prev and next variables
      UNSCALED_POINTER_ADD(ptrToSmallerFreeBlockHeader, WORD_SIZE);
      *ptrToSmallerFreeBlockHeader = ((*savedBlockToModify).next);
      UNSCALED_POINTER_ADD(ptrToSmallerFreeBlockHeader, WORD_SIZE);
      *ptrToSmallerFreeBlockHeader = ((*savedBlockToModify).prev);
      //now need to go to the end and set the footer...
      //the footer should still be there so we just need to find it and update it to its old value
      while (*ptrToSmallerFreeBlockHeader != (*savedBlockToModify).sizeAndTags) {
        UNSCALED_POINTER_ADD(ptrToSmallerFreeBlockHeader, WORD_SIZE);
      }
      //when it finishes it should be at the old footer of the free block
      *ptrToSmallerFreeBlockHeader = smallerFreeBlockHeader;
      //and it should be all set up
    } else {
      //update the list so prev and next point to the right things. hey we can just call remove free block probably...
      removeFreeBlock(blockToModify);
    }
  }

  //main body will "turn" the first availrable free block of at least size into allocated block




  return ptrToReturn;
}

/* Free the block referenced by ptr. */
void mm_free (void *ptr) {
  size_t payloadSize;
  BlockInfo * blockInfo;
  BlockInfo * followingBlock;

  // Implement mm_free.  You can change or remove the declaraions
  // above.  They are included as minor hints.

}


// Implement a heap consistency checker as needed.
int mm_check() {
  examine_heap();  //lolwhut
  return 0;
}

// Extra credit.
void* mm_realloc(void* ptr, size_t size) {
  // ... implementation here ...
  return NULL;
}
