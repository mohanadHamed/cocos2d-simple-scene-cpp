
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	bool isJumping;

	void addJumpButtonUI(cocos2d::Vec2& visibleOrigin, cocos2d::Sprite* characterSprite);

	void jumpButtonClick(cocos2d::Sprite* characterSprite);

	cocos2d::Sprite* createAndAddCharacterSprite(cocos2d::ParallaxNode *parallaxNode, cocos2d::Vec2 visibleOrigin, cocos2d::Size visibleSize, float placePosY);
};

#endif // __GAME_SCENE_H__

