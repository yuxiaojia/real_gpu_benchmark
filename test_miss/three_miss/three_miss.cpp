#include "hip/hip_runtime.h"
#define HCC_ENABLE_PRINTF
#include <stdio.h>
#include <stdlib.h>

// define enough entries to fit all of addresses we want to access
#define CACHE_ENTRIES 4194304

// kernel code
// Access pattern: a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, a, q, a
// Access count: 19
// If you have a 4MB cache with 16-way associativity, and each cache
// line is 64B with FIFO replacement policy, you will observe:
// 16 misses, 1 hit, and q miss, a miss
// total 18 misses, 1 hit

__global__ void kernel(int * arr) {
  // every array location is 4B wide, so given a cache of size N and associativity M, we can figure out which addresses map to which indices

  uint64_t a = 0, b = 0, c = 0;
  asm volatile(
	       /*
		 Ensure any initializing code is not being cached before code we care about.
	       */
	       "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
	       "buffer_wbinvl1\n\t"
               "flat_load_dwordx2 %[out0], %[in1] glc\n\t"
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "flat_load_dwordx2 %[out2], %[in3] glc\n\t"
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "flat_load_dwordx2 %[out4], %[in5] glc\n\t"
               "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
               "s_nop 0\n\t"
               : [out0]"=v"(a), [out2]"=v"(b), [out4]"=v"(c)
	       : [in1]"v"((uint64_t *)&arr[0]), [in3]"v"((uint64_t *)&arr[65536]), [in5]"v"((uint64_t *)&arr[131072])
               :"memory"
               );
}

// host code
int main(){
    int *arr = (int *)calloc(sizeof(int), CACHE_ENTRIES);
    //uint64_t *dummy = (uint64_t *)calloc(sizeof(uint64_t), 1);

    int *arr_align = NULL;
    int *arr_g;

    hipMallocManaged(&arr_align, (CACHE_ENTRIES+0x40)*sizeof(int));
    //std::cout << arr_g<<"\n";
    arr_g = (int *)(((((unsigned long long)arr_align) >> 6) << 6) + 0x40);

    // initialize arr_g with arr
    hipMemcpy(arr_g, arr, CACHE_ENTRIES*sizeof(int), hipMemcpyHostToDevice);

    // just want 1 GPU thread to run our kernel
    hipLaunchKernelGGL(kernel, dim3(1), dim3(1), 0, 0,  arr_g);

    // copy dummy value back to ensure compiler doesn't optimize out anything
    //hipMemcpy(dummy, dummy_g, 1*sizeof(uint64_t), hipMemcpyDeviceToHost);
    //printf("Dummy value = %lu\n", dummy[0]);

    hipFree(arr_g);
    //hipFree(dummy_g);
    free(arr);
    //free(dummy);
    return 0;
}
