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
    
    alpha += Scene::DeltaTime()*0.5;
    if (alpha >= 2.0){
        alpha -= 2.0;
    }
    
    // P1コントローラ設定
    Array<int32> inputdata = getWherePush();
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
    
    FontAsset(U"TitleFont")(U"鍋パニック！逆襲の具材たち（適）").drawAt(Scene::Center()-Point{0, 250});
    
    if (alpha > 1.0){
        FontAsset(U"LargeFont")(U"コントローラの任意のボタン，またはEnterを押してください").drawAt(Scene::Center()+Point{0, 200}, ColorF{0.0, 0.0, 0.0, 1.0-(alpha-1.0)});
        FontAsset(U"NormalFont")(U"コントローラの場合，押したボタンが確定ボタンに設定されます").drawAt(Scene::Center()+Point{0, 250}, ColorF{0.0, 0.0, 0.0, 1.0-(alpha-1.0)});
    }else{
        FontAsset(U"LargeFont")(U"コントローラの任意のボタン，またはEnterを押してください").drawAt(Scene::Center()+Point{0, 200}, ColorF{0.0, 0.0, 0.0, alpha});
        FontAsset(U"NormalFont")(U"コントローラの場合，押したボタンが確定ボタンに設定されます").drawAt(Scene::Center()+Point{0, 250}, ColorF{0.0, 0.0, 0.0, alpha});
    }
}

