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

#ifndef QWIFFER_BASICTYPES_H
#define QWIFFER_BASICTYPES_H

#include <climits>
#include <cstdint>

namespace Qwiffer
{
    // 1/20th of a logical pixel
    // 1 pixel = 20 twips
    typedef int twip;

    typedef int8_t SI8;
    typedef uint8_t UI8;

    typedef int16_t SI16;
    typedef uint16_t UI16;

    typedef int32_t SI32;
    typedef uint32_t UI32;

    typedef uint64_t UI64;

    union fx32
    {
        struct fx
        {
            int16_t characteristic;
            uint16_t mantissa;
        };
        uint32_t value;
    };
    // >= SWF 8
    union fx16
    {
        struct fx
        {
            int8_t characteristic;
            uint8_t mantissa;
        };
        uint16_t value;
    };

    typedef float FLOAT;
    typedef double DOUBLE;
    union FLOAT16
    {
        struct float16
        {
            uint8_t sign : 1;
            uint8_t exponent : 5;
            uint16_t mantissa : 10;
        };
        uint16_t value;
    };

    typedef UI8 LanguageCode;
    enum { Latin = 1, Japanese, Korean, Simplified_Chinese, Traditional_Chinese };

    struct RGB { UI8 Red; UI8 Green; UI8 Blue; };
    struct RGBA { UI8 Red; UI8 Green; UI8 Blue; UI8 Alpha; };
    struct ARGB { UI8 Alpha; UI8 Red; UI8 Green; UI8 Blue; };

    struct RECT
    {
        uint8_t Nbits : 5;
        int32_t Xmin;
        int32_t Xmax;
        int32_t Ymin;
        int32_t Ymax;
    };

    struct MATRIX
    {
        bool HasScale : 1;
        uint8_t NScaleBits : 5;
        union ScaleX
        {
            float fx;
            int32_t value;
        };
        union ScaleY
        {
            float fx;
            int32_t value;
        };
        bool HasRotate : 1;
        uint8_t NRotateBits : 5;
        union RotateSkew0
        {
            float fx;
            int32_t value;
        };
        union RotateSkew1
        {
            float fx;
            int32_t value;
        };
        uint8_t NTranslateBits : 5;
        int32_t TranslateX;
        int32_t TranslateY;
    };

    struct CXFORM
    {
        bool HasAddTerms : 1;
        bool HasMultTerms : 1;
        uint8_t Nbits : 4;
        int16_t RedMultTerm;
        int16_t GreenMultTerm;
        int16_t BlueMultTerm;
        int16_t RedAddTerm;
        int16_t GreenAddTerm;
        int16_t BlueAddTerm;
    };

    struct CXFORMWITHALPHA
    {
        bool HasAddTerms : 1;
        bool HasMultTerms : 1;
        uint8_t Nbits : 4;
        int16_t RedMultTerm;
        int16_t GreenMultTerm;
        int16_t BlueMultTerm;
        int16_t AlphaMultTerm;
        int16_t RedAddTerm;
        int16_t GreenAddTerm;
        int16_t BlueAddTerm;
        int16_t AlphaAddTerm;
    };
}

#endif // QWIFFER_BASICTYPES_H
