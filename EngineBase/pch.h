#pragma once

#include <Windows.h>

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <functional>

#include "EngineDebug.h"
#include "EngineMath.h"
#include "EngineRandom.h"
#include "EngineTimer.h"
#include "Object.h"

#define INNER_CLASS 

using std::vector;
using std::list;
using std::map;
using std::make_pair;
using std::string;
using std::string_view;
using std::function;

using std::bind;

#define GET_DELTA UEngineTimer::GetInst()->GetDeltaTime()