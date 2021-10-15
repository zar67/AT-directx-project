/* ------------------------------------------------- */
/* Filename: Graphics.cpp                            */
/* Author: Zoe Rowbotham                             */
/* Description: Includes function declarations for   */
/* the Graphics class.                               */
/* ------------------------------------------------- */

#include "Graphics.h"
#include "ErrorLogger.h"

#pragma comment(lib, "d3d11.lib")

Graphics::Graphics(HWND window, int width, int height)
{
	InitialiseDirectX(window, width, height);
	InitialiseShaders();
	InitialiseScene();
}

void Graphics::RenderFrame()
{
	m_pDeviceContext->IASetInputLayout(m_vertexShader.GetInputLayout());
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pDeviceContext->VSSetShader(m_vertexShader.GetShader(), NULL, 0);
	m_pDeviceContext->PSSetShader(m_pixelShader.GetShader(), NULL, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);

	m_pDeviceContext->Draw(3, 0);

	m_pSwapChain->Present(1u, 0u);
}

void Graphics::ClearBuffer(float r, float g, float b)
{
	const float color[] = { r, g, b, 1.0f };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), color);
}

ID3D11Device* Graphics::GetDevice()
{
	return m_pDevice.Get();
}

ID3D11DeviceContext* Graphics::GetDeviceContext()
{
	return m_pDeviceContext.Get();
}

void Graphics::InitialiseDirectX(HWND window, int width, int height)
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

	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
	hResult = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);

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

	m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), NULL);

	// Create the Viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;

	//Set the Viewport
	m_pDeviceContext->RSSetViewports(1, &viewport);
}

void Graphics::InitialiseShaders()
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOUR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	int numElements = ARRAYSIZE(layout);

	if (!m_vertexShader.Initialise(m_pDevice, GetShaderFolder() + L"VertexShader.cso", layout, numElements))
	{
		return;
	}

	if (!m_pixelShader.Initialise(m_pDevice, GetShaderFolder() + L"PixelShader.cso"))
	{
		return;
	}
}

void Graphics::InitialiseScene()
{
	Vertex verticies[]
	{
		Vertex(-0.5f, -0.5f, 1.0f, 0.0f, 0.0f),
		Vertex(0.0f, 0.5f, 0.0f, 1.0f, 0.0f),
		Vertex(0.5f, -0.5f, 0.0f, 0.0f, 1.0f),
	};

	D3D11_BUFFER_DESC vertexBufferDescription;
	ZeroMemory(&vertexBufferDescription, sizeof(vertexBufferDescription));

	vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDescription.ByteWidth = sizeof(Vertex) * ARRAYSIZE(verticies);
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = 0;
	vertexBufferDescription.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));

	vertexBufferData.pSysMem = verticies;

	HRESULT hResult = m_pDevice->CreateBuffer(
		&vertexBufferDescription, &vertexBufferData, 
		m_vertexBuffer.GetAddressOf()
	);

	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to Create Vertex Buffer");
		return;
	}
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
