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
	// LoadImageA() ù��° ���ڴ� �̹����� �ε��ϴ� ����� �ν��Ͻ� �ڵ鰪�� ��Ÿ���µ�,
	// �� �ڵ��� null�Ͻ�, ���� �������� ���μ������� �ε�ȴ�.
	// ��ȯ���� �̹��� �ڵ�
	HANDLE ImageHandle = LoadImageA(nullptr, _FilePath.c_str(), IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert(_FilePath + "�� �̹��� �ε忡 �����߽��ϴ�.");
		return;
	}

	// �̹��� �ڵ�
	BitMap = static_cast<HBITMAP>(ImageHandle);

	// CreateCompatibleDC()�� HDC�� ȣȯ ������ �޸�DC�� ������
	// �޸�DC�� ����ϸ� Device Context�� ����ϴ� �ͺ��� �����ӵ��� �׷����� ����� �� �ִ�. 
	// �̹��� ���� ����
	ImageDC = CreateCompatibleDC(nullptr);

	// ��Ʈ�� ��ü�� �����Ͽ� ����ϴ±���
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	// ��Ʈ�� �̹����� ũ�⸦ Ȯ���Ѵ�.
	ScaleCheck();
}

void GameEngineWindowTexture::ResCreate(const float4& _Scale)
{

	HANDLE ImageHandle = CreateCompatibleBitmap(GameEngineWindow::MainWindow.GetHDC(), _Scale.iX(), _Scale.iY());

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("�̹��� ������ �����߽��ϴ�.");
		return;
	}

	BitMap = static_cast<HBITMAP>(ImageHandle);

	ImageDC = CreateCompatibleDC(nullptr);

	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ScaleCheck();
}


void GameEngineWindowTexture::ScaleCheck()
{
	// GetObject()�� ��ü�� ũ��, ���, ��Ʈ ����, ���� ���� �����´�.
	// Info�� ����ü�� ������ �޸� �ּҸ� �����Ѵ�.
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

	// hdcDest ��� ����� �ڵ� (�������� HDC)
	// hdcSrc ����� ��Ʈ���� ����� �ڵ�(���ҽ��� HDC)
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

	TransparentBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		CopyImageDC,
		_OtherPos.iX(), // �����Ϸ��� �̹����� �»��X
		_OtherPos.iY(), // �����Ϸ��� �̹����� �»��Y
		_OtherScale.iX(), // _OtherPos�� �ʺ� 
		_OtherScale.iY(), // _OtherPos�� ����
		_TransColor);
}