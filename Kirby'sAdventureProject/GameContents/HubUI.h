#pragma once

// Ό³Έν :
class HubUI
{
public:
	// constrcuter destructer
	HubUI();
	~HubUI();

	// delete Function
	HubUI(const HubUI& _Other) = delete;
	HubUI(HubUI&& _Other) noexcept = delete;
	HubUI& operator=(const HubUI& _Other) = delete;
	HubUI& operator=(HubUI&& _Other) noexcept = delete;

protected:

private:

};

