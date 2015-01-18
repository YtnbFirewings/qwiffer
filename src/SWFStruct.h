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

#ifndef QWIFFER_SWFSTRUCT_H
#define QWIFFER_SWFSTRUCT_H

#include <string>
#include <vector>
#include "SWFTags.h"

namespace Qwiffer
{
    class SWF
    {
    public:
        SWF();
        SWF(SWF const &);
        SWF& operator=(SWF const &);
        ~SWF();

        std::string Signature() const;
        UI8 Version() const;
        UI32 FileLength() const;
        unsigned Width() const;
        unsigned Height() const;
        float FrameRate() const;
        UI16 FrameCount() const;
        size_t TagCount() const;
        SWFTag const & TagAt(const unsigned& index) const;

    private:
        friend class SWFReader;
        struct SWFHeader
        {
            UI8 signature[3];
            UI8 version;
            UI32 fileLength;
            RECT frameSize;
            UI16 frameRate;
            UI16 frameCount;
        } m_header;
        std::vector<SWFTag> m_tags;
    };
}

#endif // QWIFFER_SWFSTRUCT_H
