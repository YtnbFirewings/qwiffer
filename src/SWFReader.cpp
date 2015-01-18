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

#include "SWFReader.h"
#include "BasicTypesReader.h"
#include "SWFCompressor.h"
#include "zlib-1.2.8/zlib.h"
#include "lzma920/C/LzmaLib.h"
#include <cstring>
#include <iostream>

namespace Qwiffer
{
    SWFReader::SWFReader() {}
    SWFReader::~SWFReader() {}
    // One instance throughout execution of program
    SWFReader SWFReader::swfRdr = SWFReader();

    bool SWFReader::Read(unsigned char const * const &pos, const unsigned &len, SWF &out)
    {
        unsigned char const *ptr = nullptr;
        unsigned char *swfBytes;
        UI32 swfLength = len;
        if (*pos == 'C' || *pos == 'Z')
        {
            ptr = &pos[4];
            ReadUI32(&ptr, swfLength);
            swfBytes = new unsigned char[swfLength];
            memcpy(swfBytes, pos, 8);
            swfBytes[0] = 'F';
            int ret;
            if (*pos == 'C' && (ret = DecompressZLIB(&pos[8], len-8, &swfBytes[8], swfLength-8)) != Z_OK)
            {
                delete [] swfBytes;
                return false;
            }
            else if (*pos == 'Z' && (ret = DecompressLZMA(&pos[12], len-12, &swfBytes[8], swfLength-8)) != SZ_OK)
            {
                delete [] swfBytes;
                return false;
            }
        }
        else if (*pos == 'F')
        {
            swfBytes = new unsigned char[swfLength];
            memcpy(swfBytes, pos, swfLength);
        }
        else
            return false;
        unsigned char const *startPos = swfBytes, *currentPos = startPos;
        unsigned maxLength = swfLength;

        if (!swfRdr.ReadSWFHeader(&currentPos, maxLength, out.m_header))
        {
            delete [] swfBytes;
            return false;
        }
        SWFTag tag = SWFTag();
        while (swfRdr.ReadTag(&currentPos, maxLength - (currentPos-startPos), tag))
        {
            out.m_tags.push_back(tag);
            if (tag.m_tagCode == 0 )//&& currentPos > (startPos + maxLength))
                break;
        }
        delete [] swfBytes;
        return true;
    }

    bool SWFReader::ReadSWFHeader(unsigned char const **pos, const unsigned &maxLength, SWF::SWFHeader &out)
    {
        ReadUI8(pos, out.signature[0]);
        ReadUI8(pos, out.signature[1]);
        ReadUI8(pos, out.signature[2]);
        ReadUI8(pos, out.version);
        ReadUI32(pos, out.fileLength);
        if (out.fileLength > maxLength)
            return false;
        ReadRECT(pos, out.frameSize);
        ReadUI16(pos, out.frameRate);
        out.frameRate >>= 8;
        ReadUI16(pos, out.frameCount);
        return true;
    }

    bool SWFReader::ReadTag(unsigned char const **pos, const unsigned &maxLength, SWFTag &out)
    {
        UI16 tagCodeAndLength = 0;
        ReadUI16(pos, tagCodeAndLength);
        out.m_tagCode = (tagCodeAndLength & 0xFFC0) >> 6;
        out.m_length = tagCodeAndLength & 0x3F;
        // Check if m_length == 62
        if (!(out.m_length ^ 0x3F))
            ReadUI32(pos, out.m_length);
        if (out.m_length > maxLength)
            return false;

        if (out.m_length)
        {
            out.m_data = new char[out.m_length];
            ReadBytes(pos, out.m_data, out.m_length);
        }
        return true;
    }
}
