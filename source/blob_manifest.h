#ifndef BLOB_MANIFEST_H
#define BLOB_MANIFEST_H

#define BLOB_RESOURCE_MANIFEST( ACTION )                     \
    ACTION( IMAGE_METADATA, ID_BOOT, "data/boot.bin" )       \
    ACTION( IMAGE_METADATA, ID_KERNEL, "data/kernel.bin" )   \
    ACTION( IMAGE_METADATA, ID_CONFIG, "data/config.json" )  \
    ACTION( GPU_ACCELERATED, ID2_BOOT, "data/boot.bin" )     \
    ACTION( GPU_ACCELERATED, ID2_KERNEL, "data/kernel.bin" ) \
    ACTION( GPU_ACCELERATED, ID2_CONFIG, "data/config.json" )

#endif
