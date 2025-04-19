#include "ResolutionHelper.h"

const cocos2d::Size ResolutionHelper::DESIGN_RESOLUTION = cocos2d::Size(1920, 1080);

ResolutionHelper& ResolutionHelper::getInstance() {
    static ResolutionHelper instance;
    return instance;
}

ResolutionHelper::ResolutionHelper() {
    _visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    _designResolution = ResolutionHelper::DESIGN_RESOLUTION;

    calculateScaleFactors();
    calculateAspectRatios();
}

void ResolutionHelper::calculateScaleFactors() {
    _scaleFactorWidth = _visibleSize.width / _designResolution.width;
    _scaleFactorHeight = _visibleSize.height / _designResolution.height;
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

void ResolutionHelper::scaleSprite(cocos2d::Sprite& sprite) {
    // Design resolution and aspect ratio
    ResolutionHelper& resolutionHelper = ResolutionHelper::getInstance();

    // Check if aspect ratios are different
    float uniformScaleFactor = (resolutionHelper.getCurrentAspectRatio() != resolutionHelper.getDesignAspectRatio()) ?
        std::min(resolutionHelper.getScaleFactorWidth(), resolutionHelper.getScaleFactorHeight()) :
        resolutionHelper.getScaleFactorWidth(); // Use width as a baseline for scaling if aspect ratios are the same because of horizontal parallax

    // Scale the sprite
    sprite.setScale(uniformScaleFactor);
}