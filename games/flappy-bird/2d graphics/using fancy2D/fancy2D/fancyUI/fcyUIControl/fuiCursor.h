////////////////////////////////////////////////////////////////////////////////
/// @file  fuiCursor.h
/// @brief fancyUI 按钮
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyUIBase/fuiControl.h"

#define FUICURSOR_LAYERPRIORITY 1000.f

////////////////////////////////////////////////////////////////////////////////
/// @brief UI 按钮
////////////////////////////////////////////////////////////////////////////////
class fuiCursor :
	public fuiControl
{
protected: // 属性
	std::wstring m_CursorSprite;
	fcyColor m_BlendColor;
	
	fuiPropertyAccessor<std::wstring> m_CursorSprite_Accessor;
	fuiPropertyAccessor<fcyColor> m_BlendColor_Accessor;
protected: // 绘图资源
	fcyRefPointer<fuiSprite> m_pCursorSprite;
	
	void OnStyleChanged(fuiControl* pThis, fuiEventArgs* pArgs);

	void OnGlobalMouseMove(fuiControl* pThis, fuiEventArgs* pArgs);
public: // 实现接口
	void Update(fDouble ElapsedTime);
	void Render(fuiGraphics* pGraph);
public:
	fuiCursor(fuiPage* pRootPage, const std::wstring& Name);
	~fuiCursor();
};
