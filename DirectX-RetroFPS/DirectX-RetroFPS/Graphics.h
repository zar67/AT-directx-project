/* ------------------------------------------------- */
/* Filename: Graphics.h                              */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the Graphics class.        */
/* The Graphics class initalises DirectX and handles */
/* DirectX functionality like the render pipeline    */
/* and the swap-chain.                               */
/* ------------------------------------------------- */

#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "d3d11.lib")

#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>
#include "ErrorLogger.h"

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

	std::wstring GetShaderFolder();

private:
	void InitialiseDirectX(HWND window, int width, int height);

	Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDeviceContext = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView = nullptr;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_pDepthStencilState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer = nullptr;

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState = nullptr;
};