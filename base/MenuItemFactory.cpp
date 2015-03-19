//
//  MenuItemFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/18.
//
//

#include "MenuItemFactory.h"
#include "extensions/cocos-ext.h"
#include "LPMenuItemSprite.h"
#include "LPScrollableMenu.h"
#include "LittlePonyController.h"
#include "NodeFactory.h"

USING_NS_CC_EXT;

MenuItemFactory::MenuItemFactory()
{
}

MenuItemFactory::~MenuItemFactory()
{
}

Node* MenuItemFactory::createObject(const ValueMap& defBody, const ValueMap& uiData) {
    
    // from defBody
    std::string normalImage = defBody.at("normalImage").asString();
    std::string selectedImage = defBody.at("selectedImage").asString();
    std::string name = defBody.at("name").asString();
    bool use9Sprite_width = (defBody.find("use9sprite_width") != defBody.end())
                            ? defBody.at("use9sprite_width").asBool()
                            : false;
    bool use9Sprite_height = (defBody.find("use9sprite_height") != defBody.end())
                            ? defBody.at("use9sprite_height").asBool()
                            : false;
    bool scrollable = (defBody.find("scrollable") != defBody.end())
                            ? defBody.at("scrollable").asBool()
                            : false;
    
    // from uiData
    int tag = uiData.at("tag").asInt();
    int size_width = uiData.at("size_width").asInt();
    int size_height = uiData.at("size_height").asInt();
    std::string text = (uiData.find("text") != uiData.end())
                        ? uiData.at("text").asString()
                        : "";
    
    MenuItem* mi = NULL;
    ccMenuCallback callback = CC_CALLBACK_1(MenuItemFactory::onButtonCalled, this);
    
    if (use9Sprite_width || use9Sprite_height) {
        float not_def = 0.3333f;
        float cap_scale_width = (defBody.find("cap_scale_width") != defBody.end())
        ? defBody.at("cap_scale_width").asFloat()
        : not_def;
        float cap_scale_height = (defBody.find("cap_scale_height") != defBody.end())
        ? defBody.at("cap_scale_height").asFloat()
        : not_def;
        
        Scale9Sprite* normalSprite;
        Scale9Sprite* selectedSprite;
        if (cap_scale_width == not_def && cap_scale_height == not_def) {
            
            // cap幅が未定義なので、デフォルト9分割を適用
            normalSprite = Scale9Sprite::create(normalImage);
            selectedSprite = Scale9Sprite::create(selectedImage);
            
        } else {
            
            // 画像サイズと全体スケールの取得のためSpriteを使う
            Sprite* sp = Sprite::create(normalImage);
            Size s = sp->getContentSize();
            Rect origin(0,0,s.width,s.height);
            
            float cap_x = s.width * cap_scale_width;
            float cap_y = s.height * cap_scale_height;
            float cap_width = s.width - cap_x * 2;
            float cap_height = s.height - cap_y * 2;
            Rect cap(cap_x, cap_y, cap_width, cap_height);
            
            normalSprite = Scale9Sprite::create(normalImage, origin, cap);
            selectedSprite = Scale9Sprite::create(selectedImage, origin, cap);
            
        }
        
        Size originSize = normalSprite->getContentSize();
        Size contentSize = Size((use9Sprite_width) ? size_width : originSize.width,
                                (use9Sprite_height) ? size_height : originSize.height);
        normalSprite->setContentSize(contentSize);
        selectedSprite->setContentSize(contentSize);
        
        mi = LPMenuItemSprite::create(normalSprite, selectedSprite, callback);
        
        // 9Scaleしない場合は線形でスケールをかける
        if (!use9Sprite_width) mi->setScaleX((float)size_width/(float)contentSize.width);
        if (!use9Sprite_height) mi->setScaleY((float)size_height/(float)contentSize.height);
        
        // ラベルなど、MenuItemと連動して動くようなnodeをmiにaddchildする。
        NodeFactory* nf = NodeFactory::create();
        nf->manageColumnNode("container", mi, uiData);
        
    } else {
        mi = MenuItemImage::create(normalImage, selectedImage, callback);
        Size contentSize = mi->getContentSize();
        mi->setScaleX((float)size_width/(float)contentSize.width);
        mi->setScaleY((float)size_height/(float)contentSize.height);
    }
    
    // MenuItemはMenuにaddされる事を期待しているので、Tag以外のプロパティはsetPropertyしないでそのまま返す。
    mi->setTag(tag);
    mi->retain();
    
    return mi;
}

MenuItem* MenuItemFactory::createMenuItem(const ValueMap& defBody, const ValueMap& uiData) {
    return (MenuItem*)createObject(defBody, uiData);
}

void MenuItemFactory::createMenuItemVector(Vector<MenuItem*>& destVec, const ValueMap& defBody, const ValueMap& uiData) {
    destVec.clear();
    
    // from uiData.
    int tag = uiData.at("tag").asInt();
    int list_rowNum = (uiData.find("list_row_num") != uiData.end()) ? uiData.at("list_row_num").asInt() : 1;
    int list_columnNum = (uiData.find("list_column_num") != uiData.end()) ? uiData.at("list_column_num").asInt() : 1;
    
    for (int i = 0; i < list_rowNum; ++i) {
        for (int j = 0; j < list_columnNum; ++j) {
            MenuItem* mi = createMenuItem(defBody, uiData);

            // タグは連番で貼り直す。
            mi->setTag(tag);
            ++tag;
            
            destVec.pushBack(mi);
        }
    }
    
}

void MenuItemFactory::onButtonCalled(Ref* sender) {
    LittlePonyController::getInstatnce()->notifyUINotificationCenter(sender);
}
