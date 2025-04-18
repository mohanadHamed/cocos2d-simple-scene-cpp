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

 #include "HelloWorldScene.h"
 #include "ui/CocosGUI.h"

 USING_NS_CC;
 
 Scene* HelloWorld::createScene()
 {
     return HelloWorld::create();
 }
 
 // Print useful error message instead of segfaulting when files are not there.
 static void problemLoading(const char* filename)
 {
     printf("Error while loading: %s\n", filename);
     printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
 }
 
 // on "init" you need to initialize your instance
 bool HelloWorld::init()
 {
     //////////////////////////////
     // 1. super init first
     if ( !Scene::init() )
     {
         return false;
     }
 
     // Create Parallax Node
     auto parallaxNode = ParallaxNode::create();
     this->addChild(parallaxNode);
 
     // Background layer
     auto bg = Sprite::create("background.png");
     bg->setAnchorPoint(Vec2::ZERO);
     parallaxNode->addChild(bg, 0, Vec2(0.05f, 0.0f), Vec2::ZERO);
 
     // Foreground layer
     auto fg = Sprite::create("foreground.png");
     fg->setAnchorPoint(Vec2::ZERO);
     parallaxNode->addChild(fg, 9, Vec2(0.8f, 0.0f), Vec2::ZERO);
 
     // Character sprite
     auto character = Sprite::create("player_idle.png");
     auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();                          // get visible size so we can have a viewpoint
     auto visibleOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();                             // same for origin point
     float centerX = visibleOrigin.x + visibleSize.width / 2;                                                     // X for the center of the screen
     float centerY = visibleOrigin.y + visibleSize.height / 2;
     character->setPosition(Vec2(centerX, centerY));                                                            // set the position of the character
 
     parallaxNode->addChild(character, 10, Vec2(0.8f, 0.0f), character->getPosition());
 
     // Touch to scroll
     auto listener = EventListenerTouchOneByOne::create();
     listener->onTouchBegan = [](Touch* touch, Event* event) { return true; };
     listener->onTouchMoved = [parallaxNode](Touch* touch, Event* event) {
         Vec2 delta = touch->getDelta();
         parallaxNode->setPosition(parallaxNode->getPosition() + delta);
     };
     _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
 
     // Jump Button
     auto jumpButton = cocos2d::ui::Button::create("jump_button.png"); // Use the correct namespace for Button
     jumpButton->setPosition(Vec2(256, 256));
     jumpButton->addClickEventListener([=](Ref* sender){
         if (!character->getActionByTag(1)) {
             auto jump = Sequence::create(
                 MoveBy::create(0.3f, Vec2(0, 200)),
                 MoveBy::create(0.4f, Vec2(0, -200)),
                 nullptr
             );
             jump->setTag(1);
             character->runAction(jump);
         }
     });
     this->addChild(jumpButton, 100);
 
     return true;
 
     /*
     auto visibleSize = Director::getInstance()->getVisibleSize();
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
 
     /////////////////////////////
     // 2. add a menu item with "X" image, which is clicked to quit the program
     //    you may modify it.
 
     // add a "close" icon to exit the progress. it's an autorelease object
     auto closeItem = MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
 
     if (closeItem == nullptr ||
         closeItem->getContentSize().width <= 0 ||
         closeItem->getContentSize().height <= 0)
     {
         problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
     }
     else
     {
         float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
         float y = origin.y + closeItem->getContentSize().height/2;
         closeItem->setPosition(Vec2(x,y));
     }
 
     // create menu, it's an autorelease object
     auto menu = Menu::create(closeItem, NULL);
     menu->setPosition(Vec2::ZERO);
     this->addChild(menu, 1);
 
     /////////////////////////////
     // 3. add your codes below...
 
     // add a label shows "Hello World"
     // create and initialize a label
 
     auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
     if (label == nullptr)
     {
         problemLoading("'fonts/Marker Felt.ttf'");
     }
     else
     {
         // position the label on the center of the screen
         label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height - label->getContentSize().height));
 
         // add the label as a child to this layer
         this->addChild(label, 1);
     }
 
     // add "HelloWorld" splash screen"
     auto sprite = Sprite::create("HelloWorld.png");
     if (sprite == nullptr)
     {
         problemLoading("'HelloWorld.png'");
     }
     else
     {
         // position the sprite on the center of the screen
         sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
 
         // add the sprite as a child to this layer
         this->addChild(sprite, 0);
     }
     return true;
     */
 }
 
 
 // void HelloWorld::menuCloseCallback(Ref* pSender)
 // {
 //     //Close the cocos2d-x game scene and quit the application
 //     Director::getInstance()->end();
 
 //     /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
 
 //     //EventCustom customEndEvent("game_scene_close_event");
 //     //_eventDispatcher->dispatchEvent(&customEndEvent);
 
 
 // }
 