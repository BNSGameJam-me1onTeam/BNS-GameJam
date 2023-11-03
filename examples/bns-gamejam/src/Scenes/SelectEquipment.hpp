// SelectEquipment.hpp
#pragma once
#include "Common.hpp"

class SelectEquipment : public App::Scene
{
public:
    SelectEquipment(const InitData& init);
    ~SelectEquipment();

    void update() override;
    void draw() const override;

private:
    Array<Texture> seme_soubi;
    Array<Texture> nige_soubi;
    Point p1_cursor{0, 0};
    Point p2_cursor{0, 0};
    
    const Audio bgm{ U"bns-gamejam/sounds/selecteq.mp3", Loop::Yes};
    const Audio select{ U"bns-gamejam/sounds/select_equipment.mp3" };
    const Audio start{ U"bns-gamejam/sounds/togame.mp3" };
    const Audio cursor{U"bns-gamejam/sounds/cursor.mp3"};
    const Audio confirm{U"bns-gamejam/sounds/confirm.mp3"};
    const Texture bg{U"bns-gamejam/backgrounds/SelectEquipment.png"};
    
};
