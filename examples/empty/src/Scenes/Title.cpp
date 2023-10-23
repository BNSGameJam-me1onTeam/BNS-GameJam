// Title.cpp
#include "Title.hpp"

Title::Title(const InitData& init) : IScene{ init }
{
    Print << U"Title::Title()";
}

Title::~Title()
{
    Print << U"UseController: " << getData().use_controller;
}

void Title::update()
{
    if (KeyEnter.down())
    {
        getData().use_controller = false;
        changeScene(State::SelectStage);
    }
    
    
    alpha += Scene::DeltaTime()*0.7;
    if (alpha >= 2.0){
        alpha -= 2.0;
    }

}

void Title::draw() const
{
    Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });
    
    FontAsset(U"TitleFont")(U"鍋パニック！逆襲の具材たち（適）").drawAt(Scene::Center()-Point{0, 100});
    
    if (alpha > 1.0){
        FontAsset(U"NormalFont")(U"Press Enter or A to Start").drawAt(Scene::Center()+Point{0, 100}, ColorF{0.0, 0.0, 0.0, 1.0-(alpha-1.0)});
    }else{
        FontAsset(U"NormalFont")(U"Press Enter or A to Start").drawAt(Scene::Center()+Point{0, 100}, ColorF{0.0, 0.0, 0.0, alpha});
    }
}

