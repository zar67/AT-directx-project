/* ------------------------------------------------- */
/* Filename: Graphics.h                              */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the Graphics class.        */
/* The Graphics class initalises DirectX and handles */
/* DirectX functionality like the render pipeline    */
/* and the swap-chain.                               */
/* ------------------------------------------------- */

#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "VertexShader.h"

class Graphics
{
public:
	Graphics(HWND window);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;

	void EndFrame();
	void ClearBuffer(float r, float g, float b);

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

private:
	void InitialiseDirectX(HWND window);
	void InitialiseShaders();

	std::wstring GetShaderFolder();

	Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDeviceContext = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView = nullptr;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout = nullptr;

	VertexShader m_vertexShader;
};