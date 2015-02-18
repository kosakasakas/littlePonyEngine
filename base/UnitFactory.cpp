//
//  UnitFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "UnitFactory.h"
#include "Unit.h"
#include "cocos2d.h"
#include "UnitDataFactory.h"
#include "BattleController.h"

USING_NS_CC;

UnitFactory::UnitFactory()
{
}

UnitFactory::~UnitFactory()
{
}

Unit* UnitFactory::createObject(int objectID) {
    UnitData* uData;
    if (BattleController::getInstance()->getField() != NULL) {
        uData = BattleController::getInstance()->getField()->getSharedUnitData(objectID);
        uData->retain();
        Unit* unit = new Unit(uData);
        return unit;
    } else {
        UnitDataFactory* udFactory = new UnitDataFactory("unitData.plist");
        uData = (UnitData*)udFactory->create(objectID);
        BattleController* bc = BattleController::getInstance();
        bc->getField()->setSharedUnitData(uData); // これたぶん落ちるから、ここを通るようなら再考する。
        Field* field = bc->getField();
        field->registUnitFamiryFieldObserver(uData);
        field->registUnitMagicFieldObserver(uData);
        CCLOG("create and set unitData.");
        return NULL;
    }
}