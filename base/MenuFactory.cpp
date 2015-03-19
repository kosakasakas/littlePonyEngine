//
//  MenuFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/18.
//
//

#include "MenuFactory.h"
#include "extensions/cocos-ext.h"
#include "LPMenuItemSprite.h"
#include "LPScrollableMenu.h"
#include "LittlePonyController.h"
#include "MenuItemFactory.h"

USING_NS_CC_EXT;

MenuFactory::MenuFactory()
{
}

MenuFactory::~MenuFactory()
{
}

Node* MenuFactory::createObject(const ValueMap& defBody, const ValueMap& uiData) {
    
    // from defBody
    std::string normalImage = defBody.at("normalImage").asString();
    std::string selectedImage = defBody.at("selectedImage").asString();
    std::string name = defBody.at("name").asString();
    bool scrollable = (defBody.find("scrollable") != defBody.end())
                        ? defBody.at("scrollable").asBool()
                        : false;
    
    // from uiData
    bool useMenuList = (uiData.find("use_list") != uiData.end()) ? uiData.at("use_list").asBool() : false;
    
    MenuItemFactory* mif = MenuItemFactory::create();
    Menu* m;
    
    if (!useMenuList) {
        // ボタンが一つの場合
        MenuItem* mi = (MenuItem*)mif->createObject(defBody, uiData);
        m = Menu::create(mi,NULL);
        
        m->retain();
        setProperty(m, uiData);
        
    } else {
        
        // ボタンリストの生成
        Vector<MenuItem*> mvec;
        mif->createMenuItemVector(mvec, defBody, uiData);
        
        // LPScrollableLayerにのせる場合はLPScrollableMenuで作成すること
        if(scrollable) {
            m = LPScrollableMenu::createWithArray(mvec);
        } else {
            m = Menu::createWithArray(mvec);
        }
        
        // from uiData
        int list_rowNum = (uiData.find("list_row_num") != uiData.end()) ? uiData.at("list_row_num").asInt() : 1;
        int list_columnNum = (uiData.find("list_column_num") != uiData.end()) ? uiData.at("list_column_num").asInt() : 1;
        int list_w_padding = (uiData.find("list_w_padding") != uiData.end()) ? uiData.at("list_w_padding").asInt() : 0;
        int list_h_padding = (uiData.find("list_h_padding") != uiData.end()) ? uiData.at("list_h_padding").asInt() : 0;
        int size_width = uiData.at("size_width").asInt();
        int size_height = uiData.at("size_height").asInt();
        
        // スクロールに必要なサイズを計算して入れる
        Size s;
        s.width = size_width * list_rowNum + list_h_padding * (list_rowNum - 1);
        s.height = size_height * list_columnNum + list_h_padding * (list_columnNum - 1);
        m->setContentSize(s);
    
        m->alignItemsHorizontallyWithPadding(list_w_padding);
        m->alignItemsVerticallyWithPadding(list_h_padding);
        
        /*
        // 必要ならこんな感じでマトリクス状に表示させる
        // マトリクスの場合はpaddingが効かないので、別途サイズ調整する必要あり。
        ValueVector rows;
        for (int j = 0; j < list_columnNum; ++j) {
            Value v(list_rowNum);
            rows.push_back(v);
        }
        m->alignItemsInColumnsWithArray(rows);
         */
        
        m->retain();
        setProperty(m, uiData);
        
        // containerサイズに合わせてmのpositionを変えないと表示が狂うので最後に調整する。
        Point p = m->getPosition();
        m->setPosition(Vec2(p.x,p.y+0.5*s.height));
    }
    
    
    return m;
}

void MenuFactory::onButtonCalled(Ref* sender) {
    // buttonの場合、常に二階層上が基準nodeになる想定
    Node* node = ((Node*)sender)->getParent()->getParent();
    LittlePonyController::getInstatnce()->notifyUINotificationCenter(node);
}