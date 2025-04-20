#include "ResolutionHelper.h"

ResolutionHelper& ResolutionHelper::getInstance() 
{
    static ResolutionHelper instance;
    return instance;
}

ResolutionHelper::ResolutionHelper() 
{
    _visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    _designResolution = cocos2d::Vec2(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT);
	_frameSize = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();

    calculateScaleFactors();
    calculateAspectRatios();
}

void ResolutionHelper::calculateScaleFactors() 
{
    _scaleFactorWidth = _visibleSize.width / _designResolution.width;
    _scaleFactorHeight = _visibleSize.height / _designResolution.height;
	_scaleFactorFrameHeight = _frameSize.height / _designResolution.height;
}

void ResolutionHelper::calculateAspectRatios()
{
    _designAspectRatio = _designResolution.width / _designResolution.height;
    _currentAspectRatio = _visibleSize.width / _visibleSize.height;
}

float ResolutionHelper::getScaleFactorWidth() const 
{
    return _scaleFactorWidth;
}

float ResolutionHelper::getScaleFactorHeight() const 
{
    return _scaleFactorHeight;
}

float ResolutionHelper::getEffectiveHeightScaleFactor() const
{
    return _scaleFactorHeight == 1 ? _scaleFactorHeight : _scaleFactorFrameHeight;
}

float ResolutionHelper::getDesignAspectRatio() const
{
    return _designAspectRatio;
}

float ResolutionHelper::getCurrentAspectRatio() const
{
    return _currentAspectRatio;
}

cocos2d::Vec2 ResolutionHelper::getVerticallyScaledPosition(cocos2d::Vec2 originalPosition) const
{
	float scaledX = originalPosition.x;
	float scaledY = originalPosition.y * _scaleFactorHeight;
	return cocos2d::Vec2(scaledX, scaledY);
}

void ResolutionHelper::scaleSprite(cocos2d::Sprite *sprite) const 
{
    // Scale the sprite
    sprite->setScale(getEffectiveHeightScaleFactor());
}