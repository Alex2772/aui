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

#include <AUI/Common/AVector.h>
#include <AUI/Common/ASignal.h>
#include "AModelIndex.h"
#include "IListModel.h"

template <typename StoredType>
class AListModel: public AVector<StoredType>, public AObject, public IListModel<StoredType> {
    using p = AVector<StoredType>;
public:

    inline AListModel() = default;


    inline AListModel(typename p::size_type _Count)
            : p(_Count)
    {
    }

    inline AListModel(typename p::size_type _Count, const StoredType& _Val)
            : p(_Count, _Val)
    {
    }

    inline AListModel(std::initializer_list<StoredType> _Ilist)
    : p(_Ilist)
    {
    }

    inline AListModel(const p& _Right)
            : p(_Right)
    {
    }
    inline AListModel(const AListModel<StoredType>& _Right)
            : p(_Right.begin(), _Right.end())
    {
    }

    inline AListModel(p&& _Right)
    : p(_Right)
            {
            }

    template <class Iterator>
    inline AListModel(Iterator first, Iterator end): p(first, end) {}
    
    void push_back(const StoredType& data) {
        p::push_back(data);
        emit this->dataInserted(AModelRange{AModelIndex(p::size()-1), AModelIndex(p::size()), this});
    }

    AListModel& operator<<(const StoredType& data) {
        push_back(data);
        return *this;
    }

    size_t listSize() override {
        return p::size();
    }

    StoredType listItemAt(const AModelIndex& index) override {
        return p::at(index.getRow());
    }

};