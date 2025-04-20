# cocos2d-simple-scene-cpp  
A simple parallax scene built using Cocos2d-x (C++)

## Overview  
This project demonstrates a horizontally scrollable parallax scene using Cocos2d-x with C++.  

## Features  
- Three distinct layers: background, foreground, and a central character  
- Mouse and touch support for horizontal dragging  
- A jump button that triggers a smooth jump animation for the character  

## Demo  
🎥 [Watch Video](https://github.com/user-attachments/assets/19bf51a6-9f66-495d-911d-912b49bc4142)

## Compatibility  
- Tested on Windows 11 and Android 14  
- `CMakeLists.txt` updated to reflect project structure  

## Key Classes & Logic  
- **GameScene**: Main scene logic, including layer setup, UI, and user input handling  
- **ResolutionHelper**: Utility class for resolution scaling and aspect ratio calculations  
- **ParallaxHelper**: Utility class for sprite setup and drag event logic  

## Challenges Faced  
The biggest hurdle was building and configuring the Android version, especially updating `CMakeLists.txt`, Gradle files, and project layout to work with the latest tools.

## Future Improvements & Notes  
Although the current setup works well across two platforms and multiple resolutions, additional testing across a wider range of devices may reveal layout inconsistencies. Tweaks to resolution scaling logic may be needed to ensure consistent behavior on all screen sizes.
