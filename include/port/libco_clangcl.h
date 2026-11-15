#pragma once

// Force-included into extern/libco/libco.c when building with clang-cl.
// libco's settings.h only defines alignas for C when __STDC__ is set, which clang-cl does not do.
#if !defined(__cplusplus) && !defined(alignas)
#define alignas(bytes) __declspec(align(bytes))
#endif
