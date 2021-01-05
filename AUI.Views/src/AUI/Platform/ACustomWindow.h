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
#include "AWindow.h"

#if defined(_WIN32)

class API_AUI_VIEWS ACustomWindow: public AWindow
{
private:
    bool mDragging = false;

protected:
	LRESULT winProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	void doDrawWindow() override;
	
public:
	ACustomWindow(const AString& name, int width, int height);
	ACustomWindow();
	~ACustomWindow() override;
	void setSize(int width, int height) override;

	virtual bool isCaptionAt(const glm::ivec2& pos);

signals:
    emits<> dragBegin;
    emits<> dragEnd;
};

#else
class API_AUI_VIEWS ACustomWindow: public AWindow
{
    friend class AWindowManager;
private:
    bool mDragging = false;

    void handleXConfigureNotify();

public:
    ACustomWindow(const AString& name, int width, int height);
    ACustomWindow() = default;
    ~ACustomWindow() override = default;

    void onMousePressed(glm::ivec2 pos, AInput::Key button) override;
    void onMouseReleased(glm::ivec2 pos, AInput::Key button) override;

signals:
    emits<glm::ivec2> dragBegin;
    emits<> dragEnd;
};
#endif