#include <cstdio>
#include "Resources.h"

int main( void ) {
    auto &entries = blob_resource::BlobRegistry::get_entries();
    for ( auto &e : entries ) {
        // fprintf( stderr,
        //          "id=%d, type=%d, name=%s, datasize=%d, path=%s, "
        //          "begin=%p,  data=%.*s\n",
        //          static_cast<int>( e.id ), static_cast<int>( e.type ), e.name, static_cast<int>( e.size ), e.path,
        //          e.data, static_cast<int>( e.size ), e.data );
        fprintf( stderr,
                 "id=%d, type=%d, name=%s, datasize=%d, path=%s, "
                 "begin=%p,  data=%s\n",
                 static_cast<int>( e.id ), static_cast<int>( e.type ), e.name, static_cast<int>( e.size ), e.path,
                 e.data, e.as_c_str() );
    }
    return 0;
}
