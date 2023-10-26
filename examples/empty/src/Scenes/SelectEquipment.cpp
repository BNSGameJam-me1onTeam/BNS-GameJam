// SelectEquipment.cpp
#include "SelectEquipment.hpp"
#include "Controller.hpp"

SelectEquipment::SelectEquipment(const InitData& init) : IScene{ init }
{
    for (auto i : step(3)){
        seme_soubi << Texture{U"example/texture/{}/seme_soubi_{}.png"_fmt(!(getData().stage_id) ? U"nabe" : U"pafe", i+1)};
        nige_soubi << Texture{U"example/texture/{}/nige_soubi_{}.png"_fmt(!(getData().stage_id) ? U"nabe" : U"pafe", i+1)};
    }
}

SelectEquipment::~SelectEquipment()
{
    Print << U"Player1 Role: {}, EquipmentID: {}"_fmt(getData().p1_data.role, getData().p1_data.eqid);
    Print << U"Player2 Role: {}, EquipmentID: {}"_fmt(getData().p2_data.role, getData().p2_data.eqid);
}

void SelectEquipment::update()
{
    // ゲームスタート
    int32 p1 = getData().p1_data.role;
    int32 p2 = getData().p2_data.role;
    if (KeySpace.down() and p1 != -1 and p2 != -1 and p1 == !p2)
    {
        changeScene(State::Game);
    }
    
    //Player1のカーソル処理
    if (getData().p1_input.Up.down()){
        p1_cursor.y = Clamp(--(p1_cursor.y), 0, 1);
    }
    if (getData().p1_input.Down.down()){
        p1_cursor.y = Clamp(++(p1_cursor.y), 0, 1);
    }
    if (getData().p1_input.Left.down()){
        p1_cursor.x = Clamp(--(p1_cursor.x), 0, 2);
    }
    if (getData().p1_input.Right.down()){
        p1_cursor.x = Clamp(++(p1_cursor.x), 0, 2);
    }
    if (getData().p1_input.Confirm.down()){
        getData().p1_data.role = p1_cursor.y;
        getData().p1_data.eqid = p1_cursor.x;
    }
    
    //Player2のカーソル処理
    if(!getData().use_controller or getData().p2_data.conindex != -1)
    {
        if (getData().p2_input.Up.down()){
            p2_cursor.y = Clamp(--(p2_cursor.y), 0, 1);
        }
        if (getData().p2_input.Down.down()){
            p2_cursor.y = Clamp(++(p2_cursor.y), 0, 1);
        }
        if (getData().p2_input.Left.down()){
            p2_cursor.x = Clamp(--(p2_cursor.x), 0, 2);
        }
        if (getData().p2_input.Right.down()){
            p2_cursor.x = Clamp(++(p2_cursor.x), 0, 2);
        }
        if (getData().p2_input.Confirm.down()){
            getData().p2_data.role = p2_cursor.y;
            getData().p2_data.eqid = p2_cursor.x;
        }
    }
    else{
        // P2コントローラ設定
        Array<int32> inputdata = getWherePush();
        if(inputdata[0] != -1 and inputdata[1] != -1 and inputdata[0] != getData().p1_data.conindex)
        {
            getData().p2_data.conindex = inputdata[0];
            getData().p2_input.Up = Gamepad(inputdata[0]).povUp;
            getData().p2_input.Down = Gamepad(inputdata[0]).povDown;
            getData().p2_input.Left = Gamepad(inputdata[0]).povLeft;
            getData().p2_input.Right = Gamepad(inputdata[0]).povRight;
            getData().p2_input.Confirm = Gamepad(inputdata[0]).buttons[inputdata[1]];
        }
    }
}

void SelectEquipment::draw() const
{
    Scene::SetBackground(ColorF{ 1.0, 1.0, 1.0 });
    FontAsset(U"NormalFont")(U"Press Space to Start Game").drawAt(Scene::Center()+Point{0, 200}, ColorF{0.0, 0.0, 0.0});
    
    //カーソルの出力
    Rect{Arg::center(Scene::Center()+Point{(p1_cursor.x-1)*230, (p1_cursor.y-1)*230}), 210}.draw(ColorF{Palette::Blue, 0.5});
    Rect{Arg::center(Scene::Center()+Point{(p2_cursor.x-1)*230, (p2_cursor.y-1)*230}), 210}.draw(ColorF{Palette::Red, 0.5});
    
    // サムネ一覧の出力
    for (auto i : step(3)){
        seme_soubi[i].resized(192).drawAt(Scene::Center()+Point((i-1)*230, -230));
        nige_soubi[i].resized(192).drawAt(Scene::Center()+Point((i-1)*230, 0));
    }
    
    // 選択中の装備表示
    if(getData().p1_data.role == 0){
        seme_soubi[getData().p1_data.eqid].resized(192).drawAt(Scene::Center()+Point(-500, 220));
    }else if(getData().p1_data.role == 1){
        nige_soubi[getData().p1_data.eqid].resized(192).drawAt(Scene::Center()+Point(-500, 220));
    }
    if(getData().p2_data.role == 0){
        seme_soubi[getData().p2_data.eqid].resized(192).drawAt(Scene::Center()+Point(500, 220));
    }else if(getData().p2_data.role == 1){
        nige_soubi[getData().p2_data.eqid].resized(192).drawAt(Scene::Center()+Point(500, 220));
    }
    
}

