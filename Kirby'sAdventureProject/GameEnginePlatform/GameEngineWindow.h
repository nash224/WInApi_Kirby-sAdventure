#pragma once
#include "GameEngineWindowTexture.h"

#include <Windows.h>
#include <string>

class GameEngineWindow
{
public:
	static GameEngineWindow MainWindow;

	// constructor desstructor
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	void Open(const std::string& _Title, HINSTANCE hInstance);
	void ClearBackBuffer();
	void DoubleBuffering();
	static void MessageLoop(HINSTANCE hInstance, void (*_Start)(HINSTANCE), void (*_Update)(), void (*_End)());
	void SetPosAndScale(const float4& _Pos, const float4& _Scale); 


	HDC GetHDC()
	{
		return Hdc;
	}

	float4 GetScale() const
	{
		return Scale;
	}

	GameEngineWindowTexture* GetWindowBuffer()
	{
		return WindowBuffer;
	}

	GameEngineWindowTexture* GetBackBuffer()
	{
		return BackBuffer;
	}

	static void WIndowOff()
	{
		IsWindowUpdate = false;
	}

	static bool IsFocus()
	{
		return IsFocusValue;
	}

protected:

private:
	static bool IsWindowUpdate;
	static bool IsFocusValue;

	static HINSTANCE Instance;
	std::string Title = " ";
	HWND hWnd = nullptr;
	HDC Hdc = nullptr;

	float4 Scale = {0};

	GameEngineWindowTexture* WindowBuffer = nullptr;
	GameEngineWindowTexture* BackBuffer = nullptr;

	void MyRegisterClass();
	void InitInstance();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};