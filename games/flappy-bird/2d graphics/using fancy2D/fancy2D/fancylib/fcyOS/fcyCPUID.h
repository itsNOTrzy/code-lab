////////////////////////////////////////////////////////////////////////////////
/// @file  fcyCPUID.h
/// @brief fancy CPU信息读取
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyType.h"

#include <string>

/// @addtogroup fancy库底层支持
/// @{

namespace fcyCPUID
{
	/// @brief 获得CPU厂家
	std::string GetCPUString();
	/// @breif 获得CPU品牌
	std::string GetCPUBrand();
};

/// @}
