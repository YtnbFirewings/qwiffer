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

#ifndef QWIFFER_SWFTAGS_H
#define QWIFFER_SWFTAGS_H

#include "BasicTypes.h"

namespace Qwiffer
{
    struct SWFTag
    {
        SWFTag(SWFTag const &);
        SWFTag& operator=(SWFTag const &);
        SWFTag(UI16 const &tagCode, UI32 const &length, unsigned char const * const &data);
        unsigned TagCode() const { return m_tagCode; }
        unsigned Length() const { return m_length; }
    private:
        friend class SWFReader;
        UI16 m_tagCode;
        UI32 m_length;
        char *m_data;

        SWFTag();
    };
}

#endif // QWIFFER_SWFTAGS_H
