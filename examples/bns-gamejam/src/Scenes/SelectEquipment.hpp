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
    
    const Audio bgm{ Resource(U"bns-gamejam/sounds/selecteq.mp3"), Loop::Yes};
    const Audio select{ Resource(U"bns-gamejam/sounds/select_equipment.mp3")};
    const Audio start{ Resource(U"bns-gamejam/sounds/togame.mp3")};
    const Audio cursor{ Resource(U"bns-gamejam/sounds/cursor.mp3")};
    const Audio confirm{ Resource(U"bns-gamejam/sounds/confirm.mp3")};
    const Texture bg{ Resource(U"bns-gamejam/backgrounds/SelectEquipment.png")};
    
    const AnimatedGIFReader animation{ Resource(U"bns-gamejam/backgrounds/selectstage.gif")};
    Array<Texture> textures;
    Array<int32> delays;
    const Texture loading{ Resource(U"bns-gamejam/backgrounds/loading.png")};
    
    double flag = 2.0;
};
