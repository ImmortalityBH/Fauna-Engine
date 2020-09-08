#pragma once

#include <d3d11.h>
#include "Graphics/Shader/Shader.h"
#include "Graphics/Bindable.h"

class Graphics;

class GeometryShader : public Shader, public Bindable
{
public:
	bool Init(ID3D11Device* pDevice, std::wstring& filePath);
	GeometryShader() = default;
	~GeometryShader() = default;

	void Bind(Graphics& gfx) override;
	void SetShaderResources(Graphics& gfx, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* pViews) override;
	void SetSamplers(Graphics& gfx, UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* pSamplers) override;

	ID3D11GeometryShader* getGeometryShader() const { return pGeometryShader.Get(); }
private:
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> pGeometryShader = nullptr;
};

