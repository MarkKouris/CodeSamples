/*
 * file: Animation.h
 * author: Mark Kouris
 * brief: the interface of the Animation class.
 *      This class will be in charge of handling the animation
 *      and switching of frames for each sprite that has an animation.
 *
 */
#pragma once    
#include <string> // path and repeated name stored as strings
#include <vector> // for storing all animation frames (vector of textures)
#include "Texture.h"
#include "Shader.h"

class Animation 
{
public:

    bool swapToRun = false; // helper for seeing when animations have finished

    Animation();
    Animation(const char* folderPath, const char* repeatedName,
        int frameCount, float frameDuration, float frameDelay,
        Shader& shader);

    void animationUpdate(float dt); //advances the frames.
    void animationPlay();
    void advanceFrame();

    //gettors
    unsigned int getFrameCount() const;
    float getFrameDelay() const;
    float getFrameDuration() const;
    bool getIsRunning();
    bool getIsLooping();
    bool getIsDone();
    int getCurrentFrame();
    std::string getAnimationPath() const;
    const std::vector<Texture>& getAnimationFrames() const;
    std::string getRepeatingName() const;
    int getHoldFrame() const { return holdFrame_; }

    //settors
    void setFrameCount(unsigned int frameCount);
    void setFrameDelay(float frameDelay);
    void setFrameDuration(float frameDuration);
    void setIsRunning(bool isRunning);
    void setIsLooping(bool isLooping);
    void setIsDone(bool isDone);
    void setFrameHold(int frame);
    void setRepeatedName(std::string name);
    void setCurrentFrame(int i) { loops_ = i; }

private:
    unsigned int frameCount_;               // the size of the vector
    float frameDelay_;                      // how long before changing frames in seconds
    float frameDuration_;                   // how long each frame is displayed in seconds
    bool isRunning_;                        // whether the animation frame advances
    bool isLooping_;                        // whether or not the animation will continue
    bool isDone_;                           // whether or not the animation is at the end of the vector.
    std::string animationPath_;             // path to folder containing the animation images
    std::vector<Texture> animationFrames_;  // a vector of textures to display to show animation.
    std::string repeatedName_;              // the repeating name for animations
    int loops_ = 0;                         // helper for seeing when animations 
    int holdFrame_ = 0;                     // whether to hold a frame in animation

};