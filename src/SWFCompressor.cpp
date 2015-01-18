/*
Copyright 2015 Yixin Zhang

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "SWFCompressor.h"
#include "zlib-1.2.8/zlib.h"
#include "lzma920/C/LzmaLib.h"
#include <cassert>

namespace Qwiffer
{
    int DecompressZLIB(unsigned char const *src, const unsigned &srcLen, unsigned char *dest, const unsigned &destLen)
    {
        int ret;
        z_stream strm;

        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = 0;
        strm.next_in = Z_NULL;
        ret = inflateInit(&strm);
        if (ret != Z_OK)
            return ret;

        do
        {
            strm.avail_in = srcLen - strm.total_in;
            strm.next_in = (Bytef *)&src[strm.total_in];
            strm.avail_out = destLen - strm.total_out;
            strm.next_out = &dest[strm.total_out];
            ret = inflate(&strm, Z_FINISH);
            assert(ret != Z_STREAM_ERROR);
            switch (ret)
            {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
		// cleanup
                (void)inflateEnd(&strm);
                return ret;
            case Z_STREAM_END:
                ret = Z_OK;
                break;
            }
        } while (strm.total_in < srcLen && ret != Z_OK);

        (void)inflateEnd(&strm);
        return ret;
    }

    int DecompressLZMA(unsigned char const *src, const unsigned &srcLen, unsigned char *dest, const unsigned &destLen)
    {
        SRes ret = LzmaUncompress(dest, (size_t *)&destLen, &src[LZMA_PROPS_SIZE], (size_t *)&srcLen, src, LZMA_PROPS_SIZE);
        assert(ret == SZ_OK);
        return ret;
    }
}
