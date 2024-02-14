#include <Siv3D.hpp>
#include <random>
#include "Mob.hpp"

Mob::Mob(const InitData& init, int guzai_id) : IScene{ init } {
	// 乱数生成
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist_direction(0, 1);
	std::uniform_int_distribution<int> dist_speed(360, 450);
	std::uniform_int_distribution<int> dist_pos(350, 930);

	// 共有データを取得
	auto data = getData();

	// GIFのパスを作成
	String gifPath_mob = U"";
	if (!data.stage_id)
	{
		gifPath_mob = U"nabePanic/images/nabe_gif/nige_soubi_";
	}
	else
	{
		gifPath_mob = U"nabePanic/images/pafe_gif/nige_soubi_";
	}
	gifPath_mob += Format(guzai_id + 1);
	gifPath_mob += U".gif";

	// 生成したパスを元にGIFオブジェクトを作成
	AnimatedGIFReader gif_mob{ Resource(gifPath_mob) };

	// 各フレームの画像と、次のフレームへのディレイ（ミリ秒）をロード
	gif_mob.read(images_mob, delays_mob);

	// 各フレームの Image から Texure を作成
	for (const auto& image : images_mob)
	{
		mob_textures << Texture{ image };
	}
	images_mob.clear();

	// 移動速度
	speed_mob = dist_speed(mt);

	// 画像の向き（0：左、1：右）
	direction_mob = dist_direction(mt);

	switch (guzai_id) {
		case 0:
			// GIFの大きさ
			size_mob = 0.25;

			// 移動制限
			Xborder_left_mob = 290;
			Xborder_right_mob = 985;

			// 画像の初期位置
			m_position_mob = Vec2(dist_pos(mt), Scene::Height() - 250);
			break;
		case 1:
			// GIFの大きさ
			size_mob = 0.32;

			// 移動制限
			Xborder_left_mob = 295;
			Xborder_right_mob = 985;

			// 画像の初期位置
			m_position_mob = Vec2(dist_pos(mt), Scene::Height() - 250);
			break;
		case 2:
			// GIFの大きさ
			size_mob = 0.30;

			// 移動制限
			Xborder_left_mob = 325;
			Xborder_right_mob = 965;

			// 画像の初期位置
			m_position_mob = Vec2(dist_pos(mt), Scene::Height() - 270);
			break;
		default:
			break;
	}
}

Mob::~Mob() {}

void Mob::update() {
	if (m_position_mob.x < Xborder_left_mob)
	{
		direction_mob = 1;
	}

	if (m_position_mob.x > Xborder_right_mob)
	{
		direction_mob = 0;
	}

	if (direction_mob == 0)
	{
		m_position_mob.x -= (Scene::DeltaTime() * speed_mob);
	}
	else
	{
		m_position_mob.x += (Scene::DeltaTime() * speed_mob);
	}
}

void Mob::draw() const {
	// アニメーションの経過時間
	const double t1 = Scene::Time();

	// 経過時間と各フレームのディレイに基づいて、何番目のフレームを描けばよいかを計算
	const size_t frameIndex_mob = AnimatedGIFReader::GetFrameIndex(t1, delays_mob);

	// 具材の描画
	if (direction_mob == 0)
	{
		mob_textures[frameIndex_mob].scaled(size_mob).drawAt(m_position_mob);
	}
	else
	{
		mob_textures[frameIndex_mob].mirrored().scaled(size_mob).drawAt(m_position_mob);
	}
}
