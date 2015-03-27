//
//  littlePony.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/02/17.
//

#ifndef __LITTLE_PONY_ENGINE_H__
#define __LITTLE_PONY_ENGINE_H__

// 0x00 HI ME LO
// 00   03 03 00
#define LITTLE_PONY_VERSION 0x00010000

//
// all littlePonyEngine include files
//

// utility
#include "utility/AppManager.h"
#include "utility/AppMacros.h"
#include "utility/LittlePonyController.h"
#include "utility/FSM.h"

// base
#include "base/BaseObject.h"
#include "base/NodeFactory.h"

// test
#include "Test.h"

const char* littlePonyVersion();

#endif // __LITTLE_PONY_ENGINE_H__
