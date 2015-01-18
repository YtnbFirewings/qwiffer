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

#include "SWFTags.h"
#include <cstring>

namespace Qwiffer
{
    SWFTag::SWFTag() : m_tagCode(0), m_length(0), m_data(nullptr)
    {

    }

    SWFTag::SWFTag(SWFTag const &tag) : m_tagCode(tag.m_tagCode), m_length(tag.m_length), m_data(nullptr)
    {
        if (m_length)
        {
            m_data = new char[m_length];
            memcpy(m_data, tag.m_data, m_length);
        }
    }

    SWFTag& SWFTag::operator=(SWFTag const &tag)
    {
        m_tagCode = tag.m_tagCode;
        m_length = tag.m_length;
        if (m_length)
        {
            m_data = new char[m_length];
            memcpy(m_data, tag.m_data, m_length);
        }
        else
            m_data = nullptr;
        return *this;
    }

    SWFTag::SWFTag(UI16 const &tagCode, UI32 const &length, unsigned char const * const &data) : m_tagCode(tagCode), m_length(length), m_data(nullptr)
    {
        if (m_length)
        {
            m_data = new char[m_length];
            memcpy(m_data, data, m_length);
        }
    }
}
