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
    Texture m_texture;
};
