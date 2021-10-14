#include "Graphics.h"

#pragma comment(lib, "d3d11.lib")

Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC swapChainDescription = {};
	swapChainDescription.BufferDesc.Width = 0;
	swapChainDescription.BufferDesc.Height = 0;
	swapChainDescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDescription.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDescription.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDescription.SampleDesc.Count = 1;
	swapChainDescription.SampleDesc.Quality = 0;
	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.BufferCount = 1;
	swapChainDescription.OutputWindow = hWnd;
	swapChainDescription.Windowed = TRUE;
	swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDescription.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDescription,
		&m_pSwapChain,
		&m_pDevice,
		nullptr,
		&m_pContext
	);

	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	m_pDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&m_pTarget
	);
}

void Graphics::EndFrame()
{
	m_pSwapChain->Present(1u, 0u);
}

void Graphics::ClearBuffer(float r, float g, float b)
{
	const float color[] = { r, g, b, 1.0f };
	m_pContext->ClearRenderTargetView(m_pTarget.Get(), color);
}

ID3D11Device* Graphics::GetDevice()
{
	return m_pDevice.Get();
}

ID3D11DeviceContext* Graphics::GetContext()
{
	return m_pContext.Get();
}
