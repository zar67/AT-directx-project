#pragma once
#include <d3d11.h>
#include <wrl.h>

class Graphics
{
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;

	void EndFrame();
	void ClearBuffer(float r, float g, float b);

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pTarget = nullptr;
};

