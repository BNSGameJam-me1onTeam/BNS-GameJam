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
    double alpha = 0.0;
    
    const Audio select{ U"example/sound/select_equipment.mp3" };
    const Audio start{ U"example/sound/togame.mp3" };
    const Texture bg{U"example/background/SelectEquipment.png"};
};
