//
//  LayerFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/03.
//
//

#include "LayerFactory.h"
#include "LittlePonyController.h"
#include "LPScrollableLayer.h"
#include "LPScrollableMenu.h"
#include "NodeFactory.h"

LayerFactory::LayerFactory()
{
}

LayerFactory::~LayerFactory()
{
}

Node* LayerFactory::createObject(const ValueMap& defBody, const ValueMap& uiData) {
    // from uiData
    int width = uiData.at("size_width").asInt();
    int height = uiData.at("size_height").asInt();
    std::string colorDef = (uiData.find("colorDef") != uiData.end())
                            ? uiData.at("colorDef").asString()
                            : "";
    bool scrollable = (uiData.find("scrollable") != uiData.end())
                            ? uiData.at("scrollable").asBool()
                            : false;
    
    Layer* layer;
    if (scrollable) {
        // from uiData.
        std::string scrollDirection = (uiData.find("scroll_direction") != uiData.end())
        ? uiData.at("scroll_direction").asString()
        : "";
        
        // scroll layer作成
        Size requiredSize(width,height);
        LPScrollableLayer* slayer = LPScrollableLayer::create(requiredSize);
        
        // setLPContainerより先にsetPropertyしないと、vewRectの位置がずれてしまう。
        slayer->retain();
        setProperty(slayer, uiData);
        
        // containerタグ以下でscrollableMenuのリストNodeを作る。
        NodeFactory* nf = NodeFactory::create();
        Node* container = nf->getContainerNode(uiData);
        
        // containerのサイズにlayerを合わせる
        Size s = container->getContentSize();
        slayer->setContentSize(container->getContentSize());
        slayer->setContentOffset(Vec2(0, (requiredSize.height - s.height)), false);
        slayer->setViewSize(requiredSize);
        
        // ScrollView上でタッチを透過するMaskAreaを設定する
        Rect maskArea;
        ValueVector maskVec;
        if (uiData.find("maskArea") != uiData.end()){
            maskVec = uiData.at("maskArea").asValueVector();
            ValueMap rectMap = maskVec[0].asValueMap();
            maskArea.origin = Vec2(rectMap.at("x").asInt(), rectMap.at("y").asInt());
            maskArea.size =  Size(rectMap.at("width").asInt(), rectMap.at("height").asInt());
        }
        slayer->setMaskArea(maskArea);
        
        // LP改造containerに格納
        slayer->setLPContainer((Menu*)container);
        
        // スクロール方向を格納
        if (scrollDirection == "vertical") {
            slayer->setDirection(LPScrollView::Direction::VERTICAL);
        } else if (scrollDirection == "horizontal") {
            slayer->setDirection(LPScrollView::Direction::HORIZONTAL);
        }
        
        
        layer = slayer;
        
    } else if (!colorDef.empty()) {
        // color layerの場合
        Color3B color = LittlePonyController::getInstatnce()->getUIDefMap()->getColor(colorDef);
        layer = LayerColor::create(Color4B(color.r, color.g, color.b,255), width, height);
        
        layer->retain();
        setProperty(layer, uiData);
    }
    
    return layer;
}
