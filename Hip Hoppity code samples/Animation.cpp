/*
 * file: Animation.cpp
 * author: Mark Kouris
 * brief: the implementation of the animation class,
 *        this handles which animation frame to display.
 */

#include "Animation.h"
#include <iostream>

/* Use Notes:

FolderPath: the path to the folder containing the animation frames
    ie: "./Data/Assets/Running"
repeatedName: the name for the animation frames that repeates.
    ie: "Run_"

The file extension must be a RGBA png file,
each file must have the same width and height, or animation will look off.

*/

//default ctor, only here as backup if something messes up.
Animation::Animation() : repeatedName_("none"),animationFrames_(0), animationPath_("No Path Specified"), isDone_(false),
isLooping_(false), isRunning_(false), frameDuration_(0.f), frameDelay_(0.f), frameCount_(0)
{
    animationFrames_.push_back(Texture());
}

Animation::Animation(const char* folderPath, const char* repeatedName,
                     int frameCount, float frameDuration, float frameDelay, Shader& shader) :
    repeatedName_(repeatedName), animationFrames_(), animationPath_(folderPath), isRunning_(false),
    isLooping_(false), isDone_(false), frameDuration_(frameDuration),
    frameDelay_(frameDelay), frameCount_(frameCount)

{
    char filename[256];
    /* general method for setting up animation:  */
    for (int i = 0; i < frameCount; ++i)
    {
        sprintf_s(filename,"%s%i", repeatedName, i);
        animationFrames_.push_back(Texture(filename, shader));
    }

    //here the vector should be filled with the textures.
}

//advances the frames.
void Animation::animationUpdate(float dt)
{
    if (isRunning_)
    {
        frameDelay_ -= dt;
        if (frameDelay_ <= 0)
        {
            if (holdFrame_ == 0 || loops_ != holdFrame_)
            {
                advanceFrame();
                loops_ += 1;
            }

            if (loops_ == frameCount_ &&
                strcmp(repeatedName_.c_str(), "Run_") != 0) 
                //run animation has special properties
            {
                swapToRun = true;
                loops_ = 0;
            }

            if (loops_ > (int)frameCount_)
            {
                loops_ = 0;
            }
        }
    }
}

//Sets the proper flags to signal the start of our animation
void Animation::animationPlay()
{
  isRunning_ = true;
  isDone_ = false;

}

//in charge of advancing in the vector if enough time has elapsed
void Animation::advanceFrame()
{
    //this function is only called when enough time has elapsed. 
    std::string textureName = repeatedName_ + std::to_string(loops_);
    animationFrames_[0].setName(textureName);
    frameDelay_ = frameDuration_;

}

//gettors

unsigned int Animation::getFrameCount() const
{
    return frameCount_;
}

float Animation::getFrameDelay() const
{
    return frameDelay_;
}

float Animation::getFrameDuration() const
{
    return frameDuration_;
}

bool Animation::getIsRunning()
{
    return isRunning_;
}

bool Animation::getIsLooping()
{
    return isLooping_;
}

bool Animation::getIsDone()
{
    return isDone_;
}

int Animation::getCurrentFrame()
{
    return loops_;
}

std::string Animation::getAnimationPath() const
{
    return animationPath_;
}

const std::vector<Texture>& Animation::getAnimationFrames() const
{
    return animationFrames_;
}

std::string Animation::getRepeatingName() const
{
    return repeatedName_;
}


//settors

void Animation::setFrameCount(unsigned int frameCount)
{
    frameCount_ = frameCount;
}

void Animation::setFrameDelay(float frameDelay)
{
    frameDelay_ = frameDelay;
}

void Animation::setFrameDuration(float frameDuration)
{
    frameDuration_ = frameDuration;
}

void Animation::setIsRunning(bool isRunning)
{
    isRunning_ = isRunning;
}

void Animation::setIsLooping(bool isLooping)
{
    isLooping_ = isLooping;
}

void Animation::setIsDone(bool isDone)
{
    isDone_ = isDone;
}

void Animation::setFrameHold(int frame)
{
    holdFrame_ = frame;
}

void Animation::setRepeatedName(std::string name)
{
    repeatedName_ = name;
}