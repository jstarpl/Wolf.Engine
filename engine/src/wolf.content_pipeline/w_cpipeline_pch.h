﻿/*
	Project			 : Wolf Engine. Copyright(c) Pooya Eimandar (http://PooyaEimandar.com) . All rights reserved.
	Source			 : Please direct any bug to https://github.com/PooyaEimandar/Wolf.Engine/issues
	Website			 : http://WolfSource.io
	Name			 : w_cpipeline_pch.h
	Description		 : Pre-Compiled header of Wolf.ContentPipeline
	Comment          :
*/


#ifndef __W_CPIPELINE_PCH_H__
#define __W_CPIPELINE_PCH_H__

#include "w_cpipeline_dll.h"


// disable VC++ 2K5 warnings about deprecated standard C functions
#ifdef _MSC_VER
#if _MSC_VER >= 1400
#define _CRT_SECURE_NO_DEPRECATE
#endif
#endif

#ifdef _LINUX
#define __cdecl
#define _isnan(x) isnan(x)
#define _finite(x) finite(x)
#endif

#ifdef WIN32
//#include <Windows.h>
//TODO: just for amd-tootle, use glm later
#include <DirectXMath.h>
#endif

#include <vector>
#include <map>
#include <list>
#include <queue>
#include <set>
#include <rapidxml.hpp>
#include <fstream>
#include <sstream>

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <functional>
#include <string>
#include <assert.h>
#include <float.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm_extention.h>

#include <w_logger.h>
#include <w_Ireleasable.h>

#endif
