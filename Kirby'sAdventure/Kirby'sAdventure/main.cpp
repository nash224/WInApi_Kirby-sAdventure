#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineString.h>


// WIndows Api�� ����Ͽ� â �������̽��� �����ϴ� �ڵ忡���� ��Ŀ ���� �ý����� â���� �����ؾ� �Ѵ�.

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    std::string TemporaryName = GameEngineString::ToUpperReturn("isChangeToLargeWord");
    GameEngineCore::EngineStart("Kirby's Adventure", hInstance);


    return 0;
}