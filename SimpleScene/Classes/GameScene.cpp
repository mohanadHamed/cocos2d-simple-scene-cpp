/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

 #include "GameScene.h"
 #include "ui/CocosGUI.h"
 #include "Helpers/ResolutionHelper.h"

 #include <fstream>
 #include <string>

 USING_NS_CC;
 
 Scene* GameScene::createScene()
 {
     return GameScene::create();
 }
 
 // Print useful error message instead of segfaulting when files are not there.
 static void problemLoading(const char* filename)
 {
     printf("Error while loading: %s\n", filename);
     printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
 }
 
 // on "init" you need to initialize your instance
 bool GameScene::init()
 {
     //////////////////////////////
     // 1. super init first
     if ( !Scene::init() )
     {
         return false;
     }
 
	 isJumping = false;
     // Create Parallax Node
     auto parallaxNode = ParallaxNode::create();
     
     this->addChild(parallaxNode);
 
     auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();                          // get visible size so we can have a viewpoint
     auto visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();                             // same for origin point
     auto placePosX = visibleOrigin.x + visibleSize.width / 2;
	 auto placePosY = visibleOrigin.y;
	 auto placePos = Vec2(placePosX, placePosY);
     // Background layer
     auto bg = Sprite::create("background.png");
     ResolutionHelper::getInstance().scaleSprite(*bg);
     bg->setAnchorPoint(cocos2d::Vec2(0.5f, 1 - ResolutionHelper::getInstance().getScaleFactorHeight()));
     parallaxNode->addChild(bg, 0, Vec2(0.05f, 0.0f), ResolutionHelper::getInstance().getVerticallyScaledPosition(placePos));
 
     // Foreground layer
     auto fg = Sprite::create("foreground.png");
     ResolutionHelper::getInstance().scaleSprite(*fg);
     fg->setAnchorPoint(cocos2d::Vec2(0.5f, 1 - ResolutionHelper::getInstance().getScaleFactorHeight()));
     parallaxNode->addChild(fg, 1, Vec2(0.8f, 0.0f), ResolutionHelper::getInstance().getVerticallyScaledPosition(placePos));
 
     // Character sprite
     auto character = Sprite::create("player_idle.png");
     ResolutionHelper::getInstance().scaleSprite(*character);

     auto centerX = visibleOrigin.x + visibleSize.width / 2;  
	 auto centerY = visibleOrigin.y + visibleSize.height / 2; // center of the screen
     auto playerPosX = visibleOrigin.x + visibleSize.width / 2;
	 auto playerPosY = ResolutionHelper::getInstance().getEffectiveHeightScaleFactor() * (340 + placePosY + character->getContentSize().height / 2);
	 character->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
     //character->setPosition(Vec2(playerPosX, playerPosY)));                                                            // set the position of the character
 
     std::ofstream outFile("visible.txt"); // File will be created in working directory
     if (outFile.is_open()) {
         outFile << "origin x: " << visibleOrigin.x << "\n";
         outFile << "origin y: " << visibleOrigin.y << "\n";
         outFile << "Width: " << visibleSize.width << "\n";
         outFile << "Height: " << visibleSize.height << "\n";
         outFile.close();
     }
     else {
         CCLOG("Failed to open framesize.txt for writing");
     }

     parallaxNode->addChild(character, 2, Vec2(0.8f, 0.0f), ResolutionHelper::getInstance().getVerticallyScaledPosition(Vec2(playerPosX, playerPosY)));
 
     // Touch to scroll
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
     _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
 
     // Jump Button
     auto jumpButton = cocos2d::ui::Button::create("jump_button.png"); // Use the correct namespace for Button
	 jumpButton->setScale(ResolutionHelper::getInstance().getScaleFactorHeight());
	 auto jumpButtonPosX = visibleOrigin.x + jumpButton->getContentSize().width / 2 + 50; // center of the screen
     auto jumpButtonPosY = visibleOrigin.y + jumpButton->getContentSize().height / 2 + 50; // position the button at the center of the screen
     jumpButton->setPosition(Vec2(jumpButtonPosX, jumpButtonPosY));
	 jumpButton->setAnchorPoint(Vec2(0.5f, 0.5f));
     jumpButton->addClickEventListener([=](Ref* sender) mutable {
         if (isJumping) return;

         isJumping = true;

         auto jumpRatio = 0.3f;
         float jumpHeight = cocos2d::Director::getInstance()->getVisibleSize().height * jumpRatio;

         // Set jumping sprite
         character->setTexture("player_jump.png");

         // Jump action
         auto jumpAction = cocos2d::JumpBy::create(1.0f, cocos2d::Vec2(0, 0), jumpHeight, 1);
         
         // After jump: revert sprite & unlock jump flag
         auto revertSprite = cocos2d::CallFunc::create([=]() mutable {
             character->setTexture("player_idle.png");
             isJumping = false;
             });

         // Run jump sequence
         auto sequence = cocos2d::Sequence::create(jumpAction, revertSprite, nullptr);
         character->runAction(sequence);
         });

     this->addChild(jumpButton, 3);
 
     return true;
 }
 