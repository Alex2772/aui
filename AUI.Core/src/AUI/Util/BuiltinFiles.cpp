/**
 * =====================================================================================================================
 * Copyright (c) 2020 Alex2772
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 * Original code located at https://github.com/Alex2772/aui
 * =====================================================================================================================
 */

#include "BuiltinFiles.h"

#include "LZ.h"
#include "AUI/Common/AString.h"
#include "AUI/IO/ByteBufferInputStream.h"

void BuiltinFiles::loadBuffer(AByteBuffer& data)
{
	AByteBuffer unpacked;
	LZ::decompress(data, unpacked);

	while (unpacked.getAvailable())
	{
		std::string file;
		unpacked >> file;

		uint32_t s;
		unpacked >> s;

		auto b = _new<AByteBuffer>();
		b->reserve(s);
		b->setSize(s);

		unpacked.get(b->data(), s);
        inst().mBuffers[AString(file)] = b;
	}
}

_<IInputStream> BuiltinFiles::open(const AString& file)
{
	if (auto c = inst().mBuffers.contains(file))
	{
	    c->second->setCurrentPos(0);
		return _new<ByteBufferInputStream>(c->second);
	}
	return nullptr;
}

BuiltinFiles& BuiltinFiles::inst() {
    static BuiltinFiles f;
    return f;
}

void BuiltinFiles::load(const unsigned char* data, size_t size) {
    AByteBuffer b(data, size);
    inst().loadBuffer(b);
}