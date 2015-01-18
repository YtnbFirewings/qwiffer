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

#ifndef QWIFFER_BASICTYPESREADER_H
#define QWIFFER_BASICTYPESREADER_H

#include "BasicTypes.h"

namespace Qwiffer
{
    void ReadSI8(unsigned char const **pos, SI8 &out);
    void ReadUI8(unsigned char const **pos, UI8 &out);

    void ReadSI16(unsigned char const **pos, SI16 &out);
    void ReadUI16(unsigned char const **pos, UI16 &out);

    void ReadSI32(unsigned char const **pos, SI32 &out);
    void ReadUI32(unsigned char const **pos, UI32 &out);

    void ReadRECT(unsigned char const **pos, RECT &out);

    unsigned ReadBits(unsigned char const **pos, const uint8_t &index, const uint8_t &bitCount, uint8_t &outIndex);
    uint8_t ReadBitsFromChar(const uint8_t &value, const uint8_t &index, const uint8_t &len);

    void ReadBytes(unsigned char const **pos, char *&out, const unsigned &length);
}

#endif // QWIFFER_BASICTYPESREADER_H
