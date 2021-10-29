#include "Graphics.h"
#include "ErrorLogger.h"

Graphics::Graphics(HWND window, int width, int height) :
	m_camera(6.0f, 3.0f, DirectX::XMFLOAT2(50, 50))
{ 
	CreateDeviceAndSwapChain(window);
	CreateRenderTargetView();
	CreateDepthStencilBuffer(width, height);
	CreateDepthStencilState();
	CreateViewport(width, height);

	m_camera.SetProjectionValues(90, static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
}

void Graphics::RenderFrame()
{
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), 0);
	m_pSwapChain->Present(1u, 0u);
}

void Graphics::ClearBuffer(float r, float g, float b)
{
	const float color[] = { r, g, b, 1.0f };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), color);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

ID3D11Device* Graphics::GetDevice()
{
	return m_pDevice.Get();
}

ID3D11DeviceContext* Graphics::GetDeviceContext()
{
	return m_pDeviceContext.Get();
}

Camera* Graphics::GetCamera()
{
	return &m_camera;
}

std::wstring Graphics::GetShaderFolder()
{
	std::wstring shaderFolder = L"";

	if (IsDebuggerPresent() == TRUE)
	{
#ifdef _DEBUG
		shaderFolder = L"..\\x64\\Debug\\";
#else
		shaderFolder = L"..\\x64\\Release\\";
#endif
	}

	return shaderFolder;
}

void Graphics::CreateDeviceAndSwapChain(HWND window)
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
	swapChainDescription.OutputWindow = window;
	swapChainDescription.Windowed = TRUE;
	swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDescription.Flags = 0;

	HRESULT hResult = D3D11CreateDeviceAndSwapChain(
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
		&m_pDeviceContext
	);

	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to Create Device and Swap Chain");
		return;
	}
}

void Graphics::CreateRenderTargetView()
{
	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
	HRESULT hResult = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);

	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "GetBuffer Failed");
		return;
	}

	hResult = m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_pRenderTargetView);

	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to Create Render Target View");
		return;
	}
}

void Graphics::CreateDepthStencilBuffer(int width, int height)
{
	D3D11_TEXTURE2D_DESC depthBufferDescription;
	depthBufferDescription.Width = width;
	depthBufferDescription.Height = height;
	depthBufferDescription.MipLevels = 1;
	depthBufferDescription.ArraySize = 1;
	depthBufferDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDescription.SampleDesc.Count = 1;
	depthBufferDescription.SampleDesc.Quality = 0;
	depthBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDescription.CPUAccessFlags = 0;
	depthBufferDescription.MiscFlags = 0;

	HRESULT hResult = m_pDevice->CreateTexture2D(&depthBufferDescription, NULL, m_pDepthStencilBuffer.GetAddressOf());
	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to Create Depth Stencil Buffer");
		return;
	}

	hResult = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer.Get(), NULL, m_pDepthStencilView.GetAddressOf());
	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to Create Depth Stencil View");
		return;
	}

	m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());
}

void Graphics::CreateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDescription;
	ZeroMemory(&depthStencilDescription, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthStencilDescription.DepthEnable = true;
	depthStencilDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDescription.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	HRESULT hResult = m_pDevice->CreateDepthStencilState(&depthStencilDescription, m_pDepthStencilState.GetAddressOf());
	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to Create Depth Stencil View");
		return;
	}
}

void Graphics::CreateViewport(int width, int height)
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_pDeviceContext->RSSetViewports(1, &viewport);
}