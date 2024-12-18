#pragma once

#include <EngineBase/pch.h>

#include "EngineInput.h"

#define KEY_DOWN(key) UEngineInput::GetInst().IsDown(key)
#define KEY_UP(key) UEngineInput::GetInst().IsUp(key)
#define KEY_PRESS(key) UEngineInput::GetInst().IsPress(key)
#define KEY_FREE(key) UEngineInput::GetInst().IsFree(key)
#define KEY_TIME(key) UEngineInput::GetInst().GetPressTime(key)
