#pragma once
#include <cassert>

#define SUCCEED(__ARG__) (__ARG__ == DXFResult::DXF_SUCCEED) ?  true :  false
#define ASSERT(__ARG__) assert(__ARG__)

enum class DXFResult
{
	FAILED_UNKNOWN = -1,

	DXF_SUCCEED = 0,
	FAILED_WINDOW = 1,
	DXFRESULT_NUM
};