#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "Helpers/ResolutionHelper.h"
#include "Helpers/ParallaxHelper.h"
#include "Helpers/ResourceConstants.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	isJumping = false;
	// Create Parallax Node
	auto parallaxNode = ParallaxNode::create();

	this->addChild(parallaxNode);

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();
	auto placePosX = visibleOrigin.x + visibleSize.width / 2;
	auto placePosY = visibleOrigin.y;
	auto placePos = Vec2(placePosX, placePosY);

	// Background layer
	ParallaxHelper::getInstance().addSprite(parallaxNode,
		ResourceConstants::BACKGROUND_SPRITE,
		cocos2d::Vec2(0.5f, 1 - ResolutionHelper::getInstance().getScaleFactorHeight()),
		ParallaxLayer::BACKGROUND,
		Vec2(0.05f, 0.0f),
		placePos);

	// Foreground layer
	ParallaxHelper::getInstance().addSprite(parallaxNode,
		ResourceConstants::FOREGROUND_SPRITE,
		cocos2d::Vec2(0.5f, 1 - ResolutionHelper::getInstance().getScaleFactorHeight()),
		ParallaxLayer::FOREGROUND,
		Vec2(0.8f, 0.0f),
		placePos);

	// Character sprite
	auto characterSprite = createAndAddCharacterSprite(parallaxNode, visibleOrigin, visibleSize, placePosY);

	// Touch to scroll
	auto listener = ParallaxHelper::getInstance().buildTouchEventsListener(parallaxNode, _eventDispatcher);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// Jump Button
	addJumpButtonUI(visibleOrigin, characterSprite);

	return true;
}

void GameScene::addJumpButtonUI(cocos2d::Vec2& visibleOrigin, cocos2d::Sprite* characterSprite)
{
	int buttonPositionMargin = 50;
	auto jumpButton = cocos2d::ui::Button::create(ResourceConstants::JUMP_BUTTON_SPRITE); // Use the correct namespace for Button
	jumpButton->setScale(ResolutionHelper::getInstance().getScaleFactorHeight());
	auto jumpButtonPosX = visibleOrigin.x + jumpButton->getContentSize().width / 2 + buttonPositionMargin; // center of the screen
	auto jumpButtonPosY = visibleOrigin.y + jumpButton->getContentSize().height / 2 + buttonPositionMargin; // position the button at the center of the screen
	jumpButton->setPosition(Vec2(jumpButtonPosX, jumpButtonPosY));
	jumpButton->setAnchorPoint(Vec2(0.5f, 0.5f));
	jumpButton->addClickEventListener([=](Ref* sender) mutable
		{
			jumpButtonClick(characterSprite);
		});

	this->addChild(jumpButton, ParallaxLayer::UI);
}

void GameScene::jumpButtonClick(cocos2d::Sprite* characterSprite)
{
	if (isJumping) return;

	isJumping = true;

	auto jumpRatio = 0.3f;
	float jumpHeight = cocos2d::Director::getInstance()->getVisibleSize().height * jumpRatio;

	// Set jumping sprite
	characterSprite->setTexture(ResourceConstants::PLAYER_JUMP_SPRITE);

	// Jump action
	auto jumpAction = cocos2d::JumpBy::create(1.0f, cocos2d::Vec2(0, 0), jumpHeight, 1);

	// After jump: revert sprite & unlock jump flag
	auto revertSprite = cocos2d::CallFunc::create([=]() mutable {
		characterSprite->setTexture(ResourceConstants::PLAYER_IDLE_SPRITE);
		isJumping = false;
		});

	// Run jump sequence
	auto sequence = cocos2d::Sequence::create(jumpAction, revertSprite, nullptr);
	characterSprite->runAction(sequence);
}

Sprite* GameScene::createAndAddCharacterSprite(ParallaxNode *parallaxNode, Vec2 visibleOrigin, Size visibleSize, float placePosY)
{
	float playerPositionYShift = 340;

	auto characterSprite = Sprite::create(ResourceConstants::PLAYER_IDLE_SPRITE);
	auto playerPosX = visibleOrigin.x + visibleSize.width / 2;
	auto playerPosY = ResolutionHelper::getInstance().getEffectiveHeightScaleFactor() * (playerPositionYShift + placePosY + characterSprite->getContentSize().height / 2);
	ParallaxHelper::getInstance().addSprite(parallaxNode,
		characterSprite,
		cocos2d::Vec2(0.5f, 0.5f),
		ParallaxLayer::CHARACTER,
		Vec2(0.8f, 0.0f),
		Vec2(playerPosX, playerPosY));

	return characterSprite;
}
