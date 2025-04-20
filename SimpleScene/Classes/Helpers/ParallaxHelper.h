#ifndef PARALLAXHELPER_H
#define PARALLAXHELPER_H

#include "cocos2d.h"

class ParallaxLayer {
public:
	static const int BACKGROUND = 0;
	static const int FOREGROUND = 1;
	static const int CHARACTER = 2;
	static const int UI = 3;
};

class ParallaxHelper {
public:
    static ParallaxHelper& getInstance();

    void addSprite(cocos2d::ParallaxNode* parallaxNode, 
                    std::string spriteName,
                    cocos2d::Vec2 anchorPoint,
                    int zOrder,
                    cocos2d::Vec2 parallaxRatio,
                    const cocos2d::Vec2& placePos);
    void addSprite(cocos2d::ParallaxNode* parallaxNode,
                    cocos2d::Sprite* sprite,
                    cocos2d::Vec2 anchorPoint,
                    int zOrder,
                    cocos2d::Vec2 parallaxRatio,
                    const cocos2d::Vec2& placePos);

    cocos2d::EventListenerTouchOneByOne* buildTouchEventsListener(cocos2d::ParallaxNode* parallaxNode, cocos2d::EventDispatcher *eventDispacther);

private:
    ParallaxHelper();
    ~ParallaxHelper() = default;

    ParallaxHelper(const ParallaxHelper&) = delete;
    ParallaxHelper(ParallaxHelper&&) = delete;

    ParallaxHelper& operator=(const ParallaxHelper&) = delete;
    ParallaxHelper& operator=(ParallaxHelper&&) = delete;
};


#endif // PARALLAXHELPER_H