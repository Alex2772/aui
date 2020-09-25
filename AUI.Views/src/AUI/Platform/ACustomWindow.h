﻿#pragma once
#include "AWindow.h"

#if defined(_WIN32)

class API_AUI_VIEWS ACustomWindow: public AWindow
{
protected:
	LRESULT winProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	void doDrawWindow() override;
	
public:
	ACustomWindow(const AString& name, int width, int height);
	ACustomWindow();
	~ACustomWindow() override;

	void setSize(int width, int height) override;
};

#else
class API_AUI_VIEWS CustomWindow: public AWindow
{
public:
    CustomWindow(const AString& name, int width, int height);
    CustomWindow() = default;
    ~CustomWindow() override = default;
};
#endif