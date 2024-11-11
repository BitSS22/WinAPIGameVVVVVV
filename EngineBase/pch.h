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

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;
using std::placeholders::_5;
using std::placeholders::_6;
using std::placeholders::_7;
using std::placeholders::_8;
using std::placeholders::_9;
using std::placeholders::_10;

#define GET_DELTA UEngineTimer::GetInst()->GetDeltaTime()