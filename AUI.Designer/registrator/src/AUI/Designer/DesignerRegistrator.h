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

#pragma once

#include <AUI/Common/AString.h>
#include <AUI/Common/SharedPtr.h>
#include <AUI/Common/AVector.h>
#include <AUI/Reflect/AClass.h>
#include <AUI/View/AView.h>

namespace aui::detail {
    struct API_AUI_DESIGNER_REGISTRATOR DesignerRegistrationBase {
    public:
        DesignerRegistrationBase() noexcept;
        virtual ~DesignerRegistrationBase() noexcept;
        virtual _<AView> instanciate() = 0;
        virtual AString name() = 0;

        static const AVector<DesignerRegistrationBase*>& getRegistrations();
    };

    template <typename V>
    struct DesignerRegistration: aui::detail::DesignerRegistrationBase {
    private:
    public:
        AString name() override {
            return AClass<V>::name();
        }
    };
}

#define PP_CAT(a, b) PP_CAT_I(a, b)
#define PP_CAT_I(a, b) PP_CAT_II(~, a ## b)
#define PP_CAT_II(p, res) res

#define DESIGNER_REGISTRATION(clazz, code) struct PP_CAT(clazz, Registrator): aui::detail::DesignerRegistration<clazz> code PP_CAT(clazz, RegistratorInst);