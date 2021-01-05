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

#include "AUrl.h"

#include <functional>

#include "AUI/Common/AMap.h"
#include "AUI/Util/BuiltinFiles.h"

AUrl::AUrl(const AString& full)
{
	auto posColon = full.find(':');
	if (posColon == AString::NPOS)
	{
		mPath = full;
		mProtocol = "file";
	} else
	{
		mProtocol = full.mid(0, posColon);
		if (mProtocol.empty())
		{
			mProtocol = "builtin";
			mPath = full.mid(posColon + 1);
		} else
		{
			auto posHost = posColon + 3;
			auto posSlash = full.find('/', posHost);
			if (posSlash == AString::NPOS)
				posSlash = 0;
			mHost = full.mid(posHost, posSlash - posHost);
			if (posSlash)
			{
				mPath = full.mid(posSlash + 1);
			}
		}
	}
}

AMap<AString, std::function<_<IInputStream>(const AUrl&)>> AUrl::ourResolvers = {
        {"builtin", [](const AUrl& u) {
            return BuiltinFiles::open(u.getPath());
        }}
};
_<IInputStream> AUrl::open() const {
	if (auto is = ourResolvers[mProtocol](*this))
	    return is;
	throw IOException("could not open url: " + getFull());
}

void AUrl::registerResolver(const AString& protocol, const std::function<_<IInputStream>(const AUrl&)>& factory) {
    ourResolvers[protocol] = factory;
}