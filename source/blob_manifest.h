#ifndef BLOB_MANIFEST_H
#define BLOB_MANIFEST_H

#define BLOB_RESOURCE_MANIFEST( ACTION )                             \
    ACTION( IMAGE_METADATA, ID_BOOT, 0x0001, "data/boot.bin" )       \
    ACTION( IMAGE_METADATA, ID_KERNEL, 0x0002, "data/kernel.bin" )   \
    ACTION( IMAGE_METADATA, ID_CONFIG, 0x0003, "data/config.json" )  \
    ACTION( GPU_ACCELERATED, ID2_BOOT, 0x1001, "data/boot.bin" )     \
    ACTION( GPU_ACCELERATED, ID2_KERNEL, 0x1002, "data/kernel.bin" ) \
    ACTION( GPU_ACCELERATED, ID2_CONFIG, 0x1003, "data/config.json" )

#endif
