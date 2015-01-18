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

#ifndef QWIFFER_SWFREADER_H
#define QWIFFER_SWFREADER_H

#include "SWFStruct.h"
#include <memory>

namespace Qwiffer
{
    class SWFReader
    {
    public:
        static bool Read(unsigned char const * const &pos, const unsigned &len, SWF &out);

    private:
        static SWFReader swfRdr;

        SWFReader();
        ~SWFReader();

        bool ReadSWFHeader(unsigned char const **pos, const unsigned &maxLength, SWF::SWFHeader &out);
        bool ReadTag(unsigned char const **pos, const unsigned &maxLength, SWFTag &out);
    };
}

#endif // QWIFFER_SWFREADER_H
