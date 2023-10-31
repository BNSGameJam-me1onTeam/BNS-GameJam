// Title.cpp
#include "Title.hpp"
#include "Controller.hpp"

Title::Title(const InitData& init) : IScene{ init }
{
    getData().use_controller = false;
    getData().p1_data = {-1, -1, -1};
    getData().p2_data = {-1, -1, -1};
    getData().p1_input = {KeyA, KeyD, KeyW, KeyS, KeyQ};
    getData().p2_input = {KeyLeft, KeyRight, KeyUp, KeyDown, KeySlash};
    getData().stage_id = 0;
    bgm.play();
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
    
    // P1コントローラ設定
    Array<int8> inputdata = getWherePush();
    if(inputdata[0] != -1 and inputdata[1] != -1)
    {
        getData().p1_data.conindex = inputdata[0];
        getData().p1_input.Up = Gamepad(inputdata[0]).povUp;
        getData().p1_input.Down = Gamepad(inputdata[0]).povDown;
        getData().p1_input.Left = Gamepad(inputdata[0]).povLeft;
        getData().p1_input.Right = Gamepad(inputdata[0]).povRight;
        getData().p1_input.Confirm = Gamepad(inputdata[0]).buttons[inputdata[1]];
        getData().use_controller = true;
        changeScene(State::SelectStage);
    }
}

void Title::draw() const
{
    Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });
    
    titleAnimation.advance();
    titleAnimation.drawAt(Scene::Center());
}

