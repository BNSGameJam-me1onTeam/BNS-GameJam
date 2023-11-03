// Story.cpp
#include "Story.hpp"

Story::Story(const InitData& init) : IScene{ init }{}

Story::~Story(){}

void Story::update()
{
    if (storyAnimation.posSec() >= storyAnimation.lengthSec())
    {
        changeScene(State::SelectEquipment);
    }
}

void Story::draw() const
{
    storyAnimation.advance();
    storyAnimation.scaled(0.68).drawAt(Scene::Center());
}

