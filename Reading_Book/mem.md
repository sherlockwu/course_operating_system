# Virtual Mem Development
From whole mem -> seg -> page 

## Address Spaces 
1. The abstraction of memory which each program has: code, stack, heap 
2. Then, goals to realize this abstraction
	* transparency (truly only know the virtual mem)
	* efiiciency (with hardware)
	* protection 	
3. Other policies: how to manage the mem system(pages...)	


## Mem API 
* stack: automatic/ short-live mem
* heap: long-live/ explicitly handled mem
* sizeof is a compiler operator
* mem leak: forget to free mem, then run out of mem
* Underlying:
	* mem library makes it easy
	* lib call system call for larger heap things
	* mmap() create a swap space / realloc() reallocate another space with copying the old contents  

## Mechanism: Address Translation 
In part of LDE, support the programmer's view of mem while providing protection. (no process can access mem space of other proceseses)
* Assump: a process own a contiguous physical mem & small enough
* Mechanism: 
	* base and bounds for each process
	* use MMU accelerate
		* cal and check
		* raise exceptions
	* OS: 
		* keep free list to allocate space for processes
		* save and resotre base & bound when context switch 
		* may need to realloc space for a process	   


## Segmentation
* internal seg is too big between the stack and the heap
	* code, stack, seg is not defined to be placed contiguously 
* Extend base&bounds to each segmentation
* Cal physical addr:
	* top bits determine the segmentation 
	* the left is offset
	* notice the stack grow negatively
* Can support code segmentation sharing
* Big issue of OS: need to manage the external segs with strategy to allocating mem space 

## Ref
