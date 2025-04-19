#ifndef RESULUTIONHELPER_H
#define RESULUTIONHELPER_H

#include "cocos2d.h"

class ResolutionHelper {
public:
    static const cocos2d::Size DESIGN_RESOLUTION;

    static ResolutionHelper& getInstance();

    void calculateScaleFactors();
    void calculateAspectRatios();

    float getScaleFactorWidth() const;
    float getScaleFactorHeight() const;
    float getDesignAspectRatio() const;
    float getCurrentAspectRatio() const;
    cocos2d::Vec2 getVerticallyScaledPosition(cocos2d::Vec2) const;
	void scaleSprite(cocos2d::Sprite& sprite);

private:
    ResolutionHelper();
    ~ResolutionHelper() = default;

    ResolutionHelper(const ResolutionHelper&) = delete;
    ResolutionHelper(ResolutionHelper&&) = delete;

    ResolutionHelper& operator=(const ResolutionHelper&) = delete;
    ResolutionHelper& operator=(ResolutionHelper&&) = delete;

    cocos2d::Size _designResolution;
    cocos2d::Size _visibleSize;
    float _scaleFactorWidth;
    float _scaleFactorHeight;
    float _designAspectRatio;
    float _currentAspectRatio;
};


#endif // RESULUTIONHELPER_H