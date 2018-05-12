#pragma once
#include "BaseComponent.h"
#include "../Helpers/MathHelpers.h"

class SpriteSheetData;

using namespace Math;

enum AnimationPlayerStatus
{
	SReverse,
	SIdle,
	SPlay,
};

class SpriteSheetComponent : public BaseComponent
{
public:
	SpriteSheetComponent(const std::string &file, const Math::Origin &origin = Math::Origin::Center);
	SpriteSheetComponent(const std::string &file, const Vector2 &origin);
	~SpriteSheetComponent();

protected:
	void Initialize(const GameContext &gameContext) override;
	void Update(const GameContext &gameContext) override;
	void Draw(const GameContext &gameContext) override;

public: // Animation Calls
	void Play(const std::string &clipName, bool loop = false);
	void SetSpeed(int speed);
	void Reverse();
	void Pause();

private:
	void CalculateOrigin(const Math::Origin &origin, const FrameData &frame);

private:
	SpriteSheetData *m_pSpriteSheet;
	Vector2 m_Origin;
	Math::Origin m_OriginType;
	bool m_CalculateOrigin = false;
	const std::string m_File;

private: // Animation Player Parameters
	int m_FramesPerSecond;
	AnimationClip m_CurrentAnimationClip;
	int m_CurrentFrame;
	bool m_Loop;
	AnimationPlayerStatus m_Status;

	float m_Timer = 0.0f;
};

