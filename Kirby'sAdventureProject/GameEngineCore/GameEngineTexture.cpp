#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineTexture.h"
#include <Windows.h>
#include <string>

GameEngineTexture::GameEngineTexture() 
{
}

GameEngineTexture::~GameEngineTexture() 
{
}


void GameEngineTexture::LoadResource(const std::string& _FilePath)
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

void GameEngineTexture::ScaleCheck()
{
	// GetObject()�� ��ü�� ũ��, ���, ��Ʈ ����, ���� ���� �����´�.
	// Info�� ����ü�� ������ �޸� �ּҸ� �����Ѵ�.
	GetObject(BitMap, sizeof(BITMAP), &Info);
	
	BITMAP OldInfo = {0};
	GetObject(BitMap, sizeof(BITMAP), &OldInfo);
}
