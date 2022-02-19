#pragma once

#include <vector>

#include "Bindable.h"

class Bindable;

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graphics& graphics, const std::vector<unsigned short>& indices);
	virtual ~IndexBuffer() = default;

	virtual void Bind(Graphics& graphics) override;

	UINT GetCount();

protected:
	UINT m_count = 0;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer = nullptr;
};