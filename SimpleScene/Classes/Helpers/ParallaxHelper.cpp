#include "ParallaxHelper.h"
#include "ResolutionHelper.h"
#include "cocos2d.h"

USING_NS_CC;

ParallaxHelper& ParallaxHelper::getInstance()
{
	static ParallaxHelper instance;
	return instance;
}

ParallaxHelper::ParallaxHelper()
{

}

void ParallaxHelper::addSprite(cocos2d::ParallaxNode* parallaxNode,
								std::string spriteName,
								cocos2d::Vec2 anchorPoint,
								int zOrder,
								cocos2d::Vec2 parallaxRatio,
								const cocos2d::Vec2& placePos)
{
	auto sprite = cocos2d::Sprite::create(spriteName);
	addSprite(parallaxNode, sprite, anchorPoint, zOrder, parallaxRatio, placePos);
}

void ParallaxHelper::addSprite(cocos2d::ParallaxNode* parallaxNode,
								cocos2d::Sprite* sprite,
								cocos2d::Vec2 anchorPoint,
								int zOrder,
								cocos2d::Vec2 parallaxRatio,
								const cocos2d::Vec2& placePos)
{
	ResolutionHelper::getInstance().scaleSprite(sprite);
	sprite->setAnchorPoint(anchorPoint);
	parallaxNode->addChild(sprite, zOrder, parallaxRatio, ResolutionHelper::getInstance().getVerticallyScaledPosition(placePos));
}

EventListenerTouchOneByOne* ParallaxHelper::buildTouchEventsListener(cocos2d::ParallaxNode* parallaxNode, cocos2d::EventDispatcher* eventDispatcher)
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event) { return true; };
	listener->onTouchMoved = [parallaxNode](Touch* touch, Event* event) {
		auto delta = touch->getDelta();
		float dragMax = ResolutionHelper::getInstance().getEffectiveHeightScaleFactor() * cocos2d::Director::getInstance()->getVisibleSize().width / 2;
		auto newPos = parallaxNode->getPosition() + delta;
		newPos.x = std::max(newPos.x, -dragMax);
		newPos.x = std::min(newPos.x, dragMax);

		parallaxNode->setPosition(newPos);
		};

	return listener;
}