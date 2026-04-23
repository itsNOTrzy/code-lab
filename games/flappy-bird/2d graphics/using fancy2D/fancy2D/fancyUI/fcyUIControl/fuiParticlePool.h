////////////////////////////////////////////////////////////////////////////////
/// @file  fuiParticlePool.h
/// @brief fancyUI 粒子池
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyUIBase/fuiControl.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief UI 粒子池
////////////////////////////////////////////////////////////////////////////////
class fuiParticlePool :
	public fuiControl
{
protected:
	fcyRefPointer<f2dParticlePool> m_pParticlePool;
protected: // 属性
	fuiPropertyAccessor<void*> m_ParticlePool_Accessor;
public: // 实现接口
	void Update(fDouble ElapsedTime);
	void Render(fuiGraphics* pGraph);
public:
	fuiParticlePool(fuiPage* pRootPage, const std::wstring& Name);
	~fuiParticlePool();
};
