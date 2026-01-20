#include "blob_manifest.h"

.section .note.GNU-stack,"",@progbits

#if defined(__SIZEOF_SIZE_T__)
    /* 编译器直接告诉我们 size_t 多大 */
    #if __SIZEOF_SIZE_T__ == 8
        .macro .c_size_t value
            .quad \value
        .endm
        .equ ALIGN_LOG2, 3
    #elif __SIZEOF_SIZE_T__ == 4
        .macro .c_size_t value
            .long \value
        .endm
        .equ ALIGN_LOG2, 2
    #else
        #error "Unsupported size_t width!"
    #endif
#else
    /* 回退方案：如果编译器太老，假设 size_t == pointer */
    #if defined(__SIZEOF_POINTER__) && __SIZEOF_POINTER__ == 8
        .macro .c_size_t value
            .quad \value
        .endm
        .equ ALIGN_LOG2, 3
    #else
        .macro .c_size_t value
            .long \value
        .endm
        .equ ALIGN_LOG2, 2
    #endif
#endif

#define ASM_EXPORT_BLOB(NAME, PATH)      \
    .section .rodata, "a"              ; \
    .balign (1 << ALIGN_LOG2)          ; \
    .global NAME                       ; \
    .type NAME, @object                ; \
NAME:                                  ; \
    .c_size_t NAME##_len               ; \
.L_binary_##NAME##_data:                 ; \
    .incbin PATH                       ; \
.L_binary_##NAME##_end:                  ; \
    .equ NAME##_len, (.L_binary_##NAME##_end - .L_binary_##NAME##_data) ; \
    .quad 0                             ;   \
    .size NAME, . - NAME               ;

#define GENERATE_ASM_ENTRY(TYPE, NAME, PATH) \
    ASM_EXPORT_BLOB(_blob_##NAME##_metadata, PATH)

BLOB_RESOURCE_MANIFEST(GENERATE_ASM_ENTRY)
