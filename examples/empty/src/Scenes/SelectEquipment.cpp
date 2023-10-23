// SelectEquipment.cpp
#include "SelectEquipment.hpp"

SelectEquipment::SelectEquipment(const InitData& init) : IScene{ init }
{
    for (auto i : step(4)){
//        seme_soubi << Texture{U"example/texture/{}/seme_soubi_{}.png"_fmt(!(getData().stage_id) ? U"nabe" : U"pafe", i+1)};
//        nige_soubi << Texture{U"example/texture/{}/nige_soubi_{}.png"_fmt(!(getData().stage_id) ? U"nabe" : U"pafe", i+1)};

        seme_soubi << Texture{U"example/texture/{}/seme_soubi_1.png"_fmt(!(getData().stage_id) ? U"nabe" : U"pafe")};
        nige_soubi << Texture{U"example/texture/{}/nige_soubi_1.png"_fmt(!(getData().stage_id) ? U"nabe" : U"pafe")};
    }
}

SelectEquipment::~SelectEquipment()
{
    Print << U"Role(0: otama, 1: guzai): p1→{}, p2→{}"_fmt(getData().p1_data.role, getData().p2_data.role);
    Print << U"EqipmentID: p1→{}, p2→{}"_fmt(getData().p1_data.eqid, getData().p2_data.eqid);
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
    
    //Player1の処理
    if (KeyW.down()){
        p1_cursor.y = Clamp(--(p1_cursor.y), 0, 1);
    }
    if (KeyS.down()){
        p1_cursor.y = Clamp(++(p1_cursor.y), 0, 1);
    }
    if (KeyA.down()){
        p1_cursor.x = Clamp(--(p1_cursor.x), 0, 3);
    }
    if (KeyD.down()){
        p1_cursor.x = Clamp(++(p1_cursor.x), 0, 3);
    }
    if (KeyQ.down()){
        getData().p1_data.role = p1_cursor.y;
        getData().p1_data.eqid = p1_cursor.x;
    }
    
    //Player2の処理
    if (KeyUp.down()){
        p2_cursor.y = Clamp(--(p2_cursor.y), 0, 1);
    }
    if (KeyDown.down()){
        p2_cursor.y = Clamp(++(p2_cursor.y), 0, 1);
    }
    if (KeyLeft.down()){
        p2_cursor.x = Clamp(--(p2_cursor.x), 0, 3);
    }
    if (KeyRight.down()){
        p2_cursor.x = Clamp(++(p2_cursor.x), 0, 3);
    }
    if (KeySlash.down()){
        getData().p2_data.role = p2_cursor.y;
        getData().p2_data.eqid = p2_cursor.x;
    }
}

void SelectEquipment::draw() const
{
    Scene::SetBackground(ColorF{ 1.0, 1.0, 1.0 });
    FontAsset(U"NormalFont")(U"Press Space to Start Game").drawAt(Scene::Center()+Point{0, 200}, ColorF{0.0, 0.0, 0.0});
    
    //カーソルの出力
    Rect{Arg::center(Scene::Center()+Point{p1_cursor.x*200-300, p1_cursor.y*200-250}), 150}.draw(ColorF{Palette::Blue, 0.5});
    Rect{Arg::center(Scene::Center()+Point{p2_cursor.x*200-300, p2_cursor.y*200-250}), 150}.draw(ColorF{Palette::Red, 0.5});
    
    // サムネ一覧の出力
    for (auto i : step(4)){
        seme_soubi[i].resized(128).drawAt(Scene::Center()+Point(i*200-300, -250));
        nige_soubi[i].resized(128).drawAt(Scene::Center()+Point(i*200-300, -50));
    }
    
    // 選択中の装備表示
    if(getData().p1_data.role == 0){
        seme_soubi[getData().p1_data.eqid].resized(256).drawAt(Scene::Center()+Point(-480, 200));
    }else if(getData().p1_data.role == 1){
        nige_soubi[getData().p1_data.eqid].resized(256).drawAt(Scene::Center()+Point(-480, 200));
    }
    if(getData().p2_data.role == 0){
        seme_soubi[getData().p2_data.eqid].resized(256).drawAt(Scene::Center()+Point(480, 200));
    }else if(getData().p2_data.role == 1){
        nige_soubi[getData().p2_data.eqid].resized(256).drawAt(Scene::Center()+Point(480, 200));
    }
    
}

