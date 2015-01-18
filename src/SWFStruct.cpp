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

#include "SWFStruct.h"

namespace Qwiffer
{
    SWF::SWF()
    : m_header{{0}, 0, 0, RECT{0,0,0,0,0}, 0, 0}, m_tags(std::vector<SWFTag>())
    {

    }

    SWF::SWF(SWF const &swf)
    : m_header(swf.m_header), m_tags(swf.m_tags)
    {

    }

    SWF& SWF::operator=(SWF const &swf)
    {
        m_header = swf.m_header;
        m_tags = swf.m_tags;
        return *this;
    }

    SWF::~SWF()
    {
        // Swapping m_tags with empty vector frees its memory
        std::vector<SWFTag>().swap(m_tags);
    }

    std::string SWF::Signature() const { return std::string((char*)m_header.signature, 3); }
    UI8 SWF::Version() const { return m_header.version; }
    UI32 SWF::FileLength() const { return m_header.fileLength; }
    unsigned SWF::Width() const { return (m_header.frameSize.Xmax - m_header.frameSize.Xmin)/20; }
    unsigned SWF::Height() const { return (m_header.frameSize.Ymax - m_header.frameSize.Ymin)/20; }
    float SWF::FrameRate() const { return (float)m_header.frameRate; }
    UI16 SWF::FrameCount() const { return m_header.frameCount; }
    size_t SWF::TagCount() const { return m_tags.size(); }
    SWFTag const & SWF::TagAt(const unsigned& index) const { return m_tags.at(index); }
}
