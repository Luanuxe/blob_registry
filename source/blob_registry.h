#pragma once

#if defined( __cplusplus )

#include <stdint.h>
#include <array>
#include <cstddef>
#include <type_traits>
#include <utility>

#include "blob_manifest.h"

namespace blob_resource {

struct __attribute__( ( aligned( __alignof__( size_t ) ) ) ) BinaryBlob {
    size_t        length; /* 对应汇编的 .c_size_t */
    const uint8_t data[]; /* 对应汇编的 .incbin, 紧随其后 */
};
static_assert( std::is_standard_layout<BinaryBlob>::value );

enum class BlobType
{
    IMAGE_METADATA,
    GPU_ACCELERATED,
};

namespace _BlobInternal {
extern "C" {
#define DECLARE_SYMBOLS( TYPE, NAME, PATH ) extern const BinaryBlob _blob_##NAME##_metadata;
BLOB_RESOURCE_MANIFEST( DECLARE_SYMBOLS )
#undef DECLARE_SYMBOLS
}
}  // namespace _BlobInternal

/* 使用连续自增ID */
enum class BlobID
{
#define GEN_ENUM( TYPE, NAME, PATH ) NAME,
    BLOB_RESOURCE_MANIFEST( GEN_ENUM )
#undef GEN_ENUM
};

struct BlobEntry {
    BlobID         id;
    BlobType       type;
    const char    *name;
    const char    *path;
    const uint8_t *data;
    size_t         size;

    /* BinaryBlob::data之后会在size之外补充两个最大size字符的0（8个字节）,
     * 以确保使用任何字符类型的 `const CharT` 永远不会访问到意外的数据 */
    template <typename CharT = char>
    __attribute__( ( always_inline ) ) inline const CharT *as_c_str() const {
        static_assert(
            std::is_same<CharT, char>::value || std::is_same<CharT, wchar_t>::value ||
                std::is_same<CharT, char16_t>::value || std::is_same<CharT, char32_t>::value,
            "BlobEntry::as_c_str<T>(): T must be a standard character type (char, wchar_t, char16_t, char32_t)." );
        return reinterpret_cast<const CharT *>( data );
    }
    __attribute__( ( always_inline ) ) inline std::pair<const uint8_t *, size_t> get() const { return { data, size }; }
};

/* template <size_t N> 用于实现一个链接时陷阱, 将长度N编码到类型信息里, 避免so和bin编译时使用了不同的
 * blob_manifest.h 头文件导致blob数量不一致进而导致abi不一致 */
template <size_t N>
struct __attribute__( ( visibility( "hidden" ) ) ) BlobRegistryImpl {
    using Entries = std::array<BlobEntry, N>;
    static inline const Entries &get_entries() {
        static const Entries entries = {
#define GEN_ENTRY( TYPE, NAME, PATH )                      \
    BlobEntry{                                             \
        BlobID::NAME,                                      \
        BlobType::TYPE,                                    \
        #NAME,                                             \
        PATH,                                              \
        ( _BlobInternal::_blob_##NAME##_metadata ).data,   \
        ( _BlobInternal::_blob_##NAME##_metadata ).length, \
    },
            BLOB_RESOURCE_MANIFEST( GEN_ENTRY )
#undef GEN_ENTRY
        };
        return entries;
    }
    static inline const BlobEntry &get_blob( BlobID id ) { return get_entries().at( static_cast<size_t>( id ) ); }
    static inline const BlobEntry *get_blob( uint32_t id ) {
        const Entries &entries = get_entries();
        if ( id < entries.size() ) {
            return &get_entries()[id];
        }
        return nullptr;
    }
};

#define BLOB_COUNT( TYPE, NAME, PATH ) +1
using BlobRegistry = BlobRegistryImpl<0 BLOB_RESOURCE_MANIFEST( BLOB_COUNT )>;
#undef BLOB_COUNT


}  // namespace blob_resource

#endif
