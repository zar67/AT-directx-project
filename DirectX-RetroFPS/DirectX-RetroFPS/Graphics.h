#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <string>

#include "Camera.h"

class Graphics
{
public:
	Graphics(HWND window, int width, int height);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;

	void RenderFrame();
	void ClearBuffer(float r, float g, float b);

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	Camera* GetCamera();

	std::wstring GetShaderFolder();

private:
	void CreateDeviceAndSwapChain(HWND window);
	void CreateRenderTargetView();
	void CreateDepthStencilBuffer(int width, int height);
	void CreateDepthStencilState();
	void CreateViewport(int width, int height);

	Camera m_camera;

	Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDeviceContext = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView = nullptr;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_pDepthStencilState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer = nullptr;
};