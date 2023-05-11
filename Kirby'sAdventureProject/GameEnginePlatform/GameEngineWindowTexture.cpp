#include "GameEngineWindowTexture.h"
#include "GameEngineWindow.h"

#include <GameEngineBase/GameEngineDebug.h>

#include <Windows.h>
#include <string>

#pragma comment(lib, "msimg32.lib")

GameEngineWindowTexture::GameEngineWindowTexture() 
{
}

GameEngineWindowTexture::~GameEngineWindowTexture() 
{
}


void GameEngineWindowTexture::ResLoad(const std::string& _FilePath)
{
	// MSLearn : Loads an icon, cursor, animated cursor, or bitmap.
	// LoadImageA() 첫번째 인자는 이미지를 로드하는 모듈의 인스턴스 핸들값을 나타내는데,
	// 이 핸들이 null일시, 현재 실행중인 프로세스에서 로드된다.
	// 반환값은 이미지 핸들
	HANDLE ImageHandle = LoadImageA(nullptr, _FilePath.c_str(), IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert(_FilePath + "의 이미지 로드에 실패했습니다.");
		return;
	}

	// 이미지 핸들
	BitMap = static_cast<HBITMAP>(ImageHandle);

	// CreateCompatibleDC()는 HDC와 호환 가능한 메모리DC를 생성함
	// 메모리DC를 사용하면 Device Context를 사용하는 것보다 빠른속도로 그래픽을 출력할 수 있다. 
	// 이미지 수행 권한
	ImageDC = CreateCompatibleDC(nullptr);

	// 비트맵 객체를 선택하여 사용하는권한
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	// 비트맵 이미지의 크기를 확인한다.
	ScaleCheck();
}

void GameEngineWindowTexture::ResCreate(const float4& _Scale)
{

	HANDLE ImageHandle = CreateCompatibleBitmap(GameEngineWindow::MainWindow.GetHDC(), _Scale.iX(), _Scale.iY());

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다.");
		return;
	}

	BitMap = static_cast<HBITMAP>(ImageHandle);

	ImageDC = CreateCompatibleDC(nullptr);

	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ScaleCheck();
}


void GameEngineWindowTexture::ScaleCheck()
{
	// GetObject()는 개체의 크기, 모양, 비트 단위, 색상 들을 가져온다.
	// Info에 구조체를 저장할 메모리 주소를 전달한다.
	GetObject(BitMap, sizeof(BITMAP), &Info);
	
	BITMAP OldInfo;
	GetObject(OldBitMap, sizeof(BITMAP), &OldInfo);
}


void GameEngineWindowTexture::BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos)
{
	BitCopy(_CopyTexture, _Pos, _CopyTexture->GetScale());
}

void GameEngineWindowTexture::BitCopy(
	GameEngineWindowTexture* _CopyTexture, 
	const float4& _Pos, 
	const float4& _Scale)
{
	HDC CopyImageDC = _CopyTexture->GetImageDC();

	// hdcDest 출력 대상의 핸들 (윈도우의 HDC)
	// hdcSrc 출력할 비트맵이 저장된 핸들(리소스의 HDC)
	BitBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		CopyImageDC,
		0,
		0,
		SRCCOPY);
}


void GameEngineWindowTexture::TransCopy(
	GameEngineWindowTexture* _CopyTexture,
	const float4& _Pos,
	const float4& _Scale,
	const float4& _OtherPos, 
	const float4& _OtherScale,
	int _TransColor)
{
	HDC CopyImageDC = _CopyTexture->GetImageDC();

	int PosX = _Pos.iX() - _Scale.ihX(); // 출력위치 시작점
	int PosY = _Pos.iY() - _Scale.ihY();
	int ScaleX = _Scale.iX();
	int ScaleY = _Scale.iY();
	

	TransparentBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(), // 출력위치 시작점X
		_Pos.iY() - _Scale.ihY(), // 출력위치 시작점Y
		_Scale.iX(), // 출력 범위X
		_Scale.iY(), // 출력 범위Y
		CopyImageDC,
		_OtherPos.iX(), // 소스 이미지의 시작점X
		_OtherPos.iY(), // 소스 이미지의 시작점Y
		_OtherScale.iX(), // 소스 이미지의 끝점X
		_OtherScale.iY(), // 소스 이미지의 끝점Y
		_TransColor);
}