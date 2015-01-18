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

#include "BasicTypesReader.h"

namespace Qwiffer
{
    void ReadSI8(unsigned char const **pos, SI8 &out) { out = *(*pos)++; }
    void ReadUI8(unsigned char const **pos, UI8 &out) { out = *(*pos)++; }

    void ReadSI16(unsigned char const **pos, SI16 &out) { out = *(*pos)++; out |= (*(*pos)++ << 8); }
    void ReadUI16(unsigned char const **pos, UI16 &out) { out = *(*pos)++; out |= (*(*pos)++ << 8); }

    void ReadSI32(unsigned char const **pos, SI32 &out)
    {
        out = *(*pos)++;
        out |= (*(*pos)++ << 8);
        out |= (*(*pos)++ << 16);
        out |= (*(*pos)++ << 24);
    }

    void ReadUI32(unsigned char const **pos, UI32 &out)
    {
        out = *(*pos)++;
        out |= (*(*pos)++ << 8);
        out |= (*(*pos)++ << 16);
        out |= (*(*pos)++ << 24);
    }

    void ReadRECT(unsigned char const **pos, RECT &out)
    {
        uint8_t index = 0;
        out.Nbits = ReadBits(pos, index, 5, index);
        out.Xmin = ReadBits(pos, index, out.Nbits, index);
        out.Xmax = ReadBits(pos, index, out.Nbits, index);
        out.Ymin = ReadBits(pos, index, out.Nbits, index);
        out.Ymax = ReadBits(pos, index, out.Nbits, index);
        if (index != 0)
            (ReadBits(pos, index, CHAR_BIT - index, index) == 0);
    }

    unsigned ReadBits(unsigned char const **pos, const uint8_t &index, const uint8_t &bitCount, uint8_t &outIndex)
    {
        unsigned outValue = 0;
        uint8_t currentBitsUnread = sizeof(uint8_t) * CHAR_BIT - index;
        uint8_t bitsLeft = bitCount;
        uint8_t readLength = 0;
        while (bitsLeft > 0)
        {
            readLength = currentBitsUnread <= bitsLeft ? currentBitsUnread : bitsLeft;
            outValue |= ReadBitsFromChar(*(*pos), CHAR_BIT - currentBitsUnread, readLength) << (bitsLeft - readLength);
            bitsLeft -= readLength;
            currentBitsUnread -= readLength;
            if (currentBitsUnread == 0)
            {
                ++(*pos);
                currentBitsUnread = CHAR_BIT;
            }
        }
        outIndex = CHAR_BIT - currentBitsUnread;
        return outValue;
    }

    uint8_t ReadBitsFromChar(const uint8_t &value, const uint8_t &index, const uint8_t &len)
    {
        uint8_t bitCount = sizeof(uint8_t) * CHAR_BIT;
        if (index > (bitCount - 1) || len > (bitCount - index))
            return -1;
        // return  (value >> (bitCount - (index + len))) & (UCHAR_MAX >> (bitCount - len));
        return (value >> (bitCount - (index + len))) & (UCHAR_MAX >> (index + (bitCount - (index + len))));
    }

    void ReadBytes(unsigned char const **pos, char *&out, const unsigned &length)
    {
        for (unsigned i = 0; i < length; ++i)
            out[i] = *(*pos)++;
    }
}
