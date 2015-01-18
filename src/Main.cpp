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

#include <iostream>
#include <fstream>
#include <string>
#include "SWFReader.h"

using std::string;
using std::ifstream;
using std::cout;
using std::cerr;
using std::endl;

bool ReadTextFile(const string&, string&);
bool ReadBinaryFile(const string&, char *&, unsigned&);

int main(int argc, char *argv[])
{
    string swfFilePath = "";
    if (argc == 1)
        return 0;

    for (int i = 1; i < argc; ++i)
    {
    swfFilePath = argv[i];
    cout << "Parsing " << swfFilePath << endl;

    char *swfBytes = nullptr;
    unsigned swfSize = 0;

    if (!ReadBinaryFile(swfFilePath, swfBytes, swfSize))
    {
        cerr << "File not found: " << swfFilePath << endl;
        return 0;
    }

    Qwiffer::SWF s;
    Qwiffer::SWFReader::Read((unsigned char *&)swfBytes, swfSize, s);
    for (size_t i = 0; i < s.TagCount(); ++i)
        cout << s.TagAt(i).TagCode() << " Length: " << s.TagAt(i).Length() << endl;
    delete [] swfBytes;
    }
    return 0;
}

bool ReadTextFile(const string &path, string &out)
{
    ifstream in(path.c_str(), ifstream::in);
    if (!in.is_open())
        return false;

    out = string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    in.close();
    return true;
}

bool ReadBinaryFile(const string &path, char *&out, unsigned &outSize)
{
    ifstream in(path.c_str(), ifstream::in | ifstream::binary | ifstream::ate);
    if (!in.is_open())
        return false;

    outSize = in.tellg();
    in.seekg(in.beg);
    out = new char[outSize];
    in.read(out, outSize);

    in.close();
    return true;
}
