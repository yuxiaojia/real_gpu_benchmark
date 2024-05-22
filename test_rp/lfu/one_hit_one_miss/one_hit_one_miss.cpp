#include "hip/hip_runtime.h"
#define HCC_ENABLE_PRINTF
#include <stdio.h>
#include <stdlib.h>

// define enough entries to fit all of addresses we want to access
#define CACHE_ENTRIES 4194304

// kernel code
// Access pattern: a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, a, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, b
// Access count: 35
// If you have a 4MB cache with 16-way associativity, and each cache
// line is 64B with FIFO replacement policy, you will observe:


__global__ void kernel(int * arr) {
  // every array location is 4B wide, so given a cache of size N and associativity M, we can figure out which addresses map to which indices

  uint64_t a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, o = 0, p = 0;
  uint64_t a_1 = 0;
  uint64_t a_2 = 0, b_1 = 0, c_1 = 0, d_1 = 0, e_1 = 0, f_1 = 0, g_1 = 0, h_1 = 0, i_1 = 0, j_1 = 0, k_1 = 0, l_1 = 0, m_1 = 0, n_1 = 0, o_1 = 0, p_1 = 0;
  uint64_t q = 0, b_2 = 0;
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
              "flat_load_dwordx2 %[out6], %[in7] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out8], %[in9] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out10], %[in11] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out12], %[in13] glc\n\t" 
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out14], %[in15] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out16], %[in17] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out18], %[in19] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out20], %[in21] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out22], %[in23] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out24], %[in25] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out26], %[in27] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out28], %[in29] glc\n\t" 
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out30], %[in31] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out32], %[in33] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out34], %[in35] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out36], %[in37] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out38], %[in39] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out40], %[in41] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out42], %[in43] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out44], %[in45] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out46], %[in47] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out48], %[in49] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out50], %[in51] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out52], %[in53] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out54], %[in55] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out56], %[in57] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out58], %[in59] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out60], %[in61] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out62], %[in63] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out64], %[in65] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out66], %[in67] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
              "flat_load_dwordx2 %[out68], %[in69] glc\n\t"
              "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"

               "s_nop 0\n\t"
               : [out0]"=v"(a), [out2]"=v"(b), [out4]"=v"(c), [out6]"=v"(d), [out8]"=v"(e), [out10]"=v"(f), [out12]"=v"(g), [out14]"=v"(h), [out16]"=v"(i), [out18]"=v"(j),
                 [out20]"=v"(k), [out22]"=v"(l), [out24]"=v"(m), [out26]"=v"(n), [out28]"=v"(o), [out30]"=v"(p), [out32]"=v"(q), [out34]"=v"(r), [out36]"=v"(a), [out38]"=v"(b), [out40]"=v"(c), [out42]"=v"(d), [out44]"=v"(e), [out46]"=v"(f), [out48]"=v"(g), [out50]"=v"(h), [out52]"=v"(i), [out54]"=v"(j),
                 [out56]"=v"(k), [out58]"=v"(l), [out60]"=v"(m), [out62]"=v"(n), [out64]"=v"(o), [out66]"=v"(p), [out68]"=v"(q)
              : [in1]"v"((uint64_t *)&arr[0]), [in3]"v"((uint64_t *)&arr[65536]), [in5]"v"((uint64_t *)&arr[131072]), [in7]"v"((uint64_t *)&arr[196608]), [in9]"v"((uint64_t *)&arr[262144]),
                [in11]"v"((uint64_t *)&arr[327680]), [in13]"v"((uint64_t *)&arr[393216]), [in15]"v"((uint64_t *)&arr[458752]), [in17]"v"((uint64_t *)&arr[524288]), [in19]"v"((uint64_t *)&arr[589824]),
                [in21]"v"((uint64_t *)&arr[655360]), [in23]"v"((uint64_t *)&arr[720896]), [in25]"v"((uint64_t *)&arr[786432]), [in27]"v"((uint64_t *)&arr[851968]),
                [in29]"v"((uint64_t *)&arr[917504]), [in31]"v"((uint64_t *)&arr[983040]), [in33]"v"((uint64_t *)&arr[1048576]), [in35]"v"((uint64_t *)&arr[983041]),[in37]"v"((uint64_t *)&arr[0]), [in39]"v"((uint64_t *)&arr[65536]), [in41]"v"((uint64_t *)&arr[131072]), [in43]"v"((uint64_t *)&arr[196608]), [in45]"v"((uint64_t *)&arr[262144]),
                [in47]"v"((uint64_t *)&arr[327680]), [in49]"v"((uint64_t *)&arr[393216]), [in51]"v"((uint64_t *)&arr[458752]), [in53]"v"((uint64_t *)&arr[524288]), [in55]"v"((uint64_t *)&arr[589824]),
                [in57]"v"((uint64_t *)&arr[655360]), [in59]"v"((uint64_t *)&arr[720896]), [in61]"v"((uint64_t *)&arr[786432]), [in63]"v"((uint64_t *)&arr[851968]),
                [in65]"v"((uint64_t *)&arr[917504]), [in67]"v"((uint64_t *)&arr[983040]), [in69]"v"((uint64_t *)&arr[1048576])
               :"memory"
               );
}

// host code
int main(){
    int *arr = (int *)calloc(sizeof(int), CACHE_ENTRIES);
    //uint64_t *dummy = (uint64_t *)calloc(sizeof(uint64_t), 1);

    int *arr_g;
    //uint64_t *dummy_g;

    hipMallocManaged(&arr_g, CACHE_ENTRIES*sizeof(int));
    //hipMallocManaged(&dummy_g, CACHE_ENTRIES*sizeof(uint64_t));

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
