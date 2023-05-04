#include <iostream>
#include <GameEngineCore/GameEngineCore.h>
#include <GameContents/ContentsCore.h>


//
// WIndows Api�� ����Ͽ� â �������̽��� �����ϴ� �ڵ忡���� ��Ŀ ���� �ý����� â���� �����ؾ� �Ѵ�.

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngineCore::EngineStart<ContentsCore>("Kirby's Adventure", hInstance);


    return 0;
}