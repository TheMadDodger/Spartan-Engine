#include "stdafx.h"
#include "../../stdafx.h"
#include "SpriteSheetComponent.h"
#include "../Scenes/GameObject.h"
#include "TransformComponent.h"

SpriteSheetComponent::SpriteSheetComponent(const std::string &file, const Origin &origin) : m_File(file),
	m_pSpriteSheet(nullptr), m_CalculateOrigin(true), m_OriginType(origin),
	m_CurrentFrame(0), m_Status(SIdle) {}

SpriteSheetComponent::SpriteSheetComponent(const std::string &file, const Vector2 &origin) : m_Origin(origin),
	m_File(file), m_pSpriteSheet(nullptr), m_CurrentFrame(0), m_Status(SIdle) {}

SpriteSheetComponent::~SpriteSheetComponent() {}

void SpriteSheetComponent::Initialize(const GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	m_pSpriteSheet = ContentManager::GetInstance()->Load<SpriteSheetData>(m_File);

	if (m_pSpriteSheet == nullptr)
		return;

	m_CurrentAnimationClip = m_pSpriteSheet->m_AnimationClips[0];
}

void SpriteSheetComponent::Update(const GameContext &gameContext)
{
	if (m_FramesPerSecond != 0)
	{
		switch (m_Status)
		{
		case SIdle:
			// Do Nothing
			break;

		case SPlay:
			m_Timer += *gameContext.pTime->GetDeltaTime() / 1000.0f;
			if (m_Timer >= 1.0f / m_FramesPerSecond)
			{
				++m_CurrentFrame;
				if (m_CurrentFrame >= m_CurrentAnimationClip.NumberOfFrames)
				{
					m_CurrentFrame = 0;
					if (!m_Loop)
						m_Status = SIdle;
				}

				m_Timer -= 1.0f / m_FramesPerSecond;
			}
			break;

		case SReverse:
			m_Timer += *gameContext.pTime->GetDeltaTime();
			if (m_Timer >= 1.0f / m_FramesPerSecond)
			{
				--m_CurrentFrame;
				if (m_CurrentFrame <= 0)
				{
					if (!m_Loop)
					{
						m_Status = SIdle;
						m_CurrentFrame = m_CurrentAnimationClip.NumberOfFrames - 1;
					}
				}

				m_Timer -= 1.0f / m_FramesPerSecond;
			}
			break;

		default:
			break;
		}
	}
}

void SpriteSheetComponent::Draw(const GameContext &gameContext)
{
	auto frame = m_CurrentAnimationClip.Frames[m_CurrentFrame];
	if (m_CalculateOrigin)
		CalculateOrigin(m_OriginType, frame);

	glPushMatrix();
	GetGameObject()->GetTransform()->ApplyTransform();
	gameContext.pRenderer->RenderSprite(m_pSpriteSheet->m_pImageData, frame.FrameRect, m_Origin);
	glPopMatrix();
}

void SpriteSheetComponent::Play(const std::string &clipName, bool loop)
{
	if (m_CurrentAnimationClip.Name == clipName && m_Status == SPlay) // Animation already playing
	{
		// Just keep playing the animation
		return;
	}

	auto it = find_if(m_pSpriteSheet->m_AnimationClips.begin(), m_pSpriteSheet->m_AnimationClips.end(), [clipName](const AnimationClip &clip)
	{
		if (clip.Name == clipName)
		{
			return true;
		}
		else
		{
			return false;
		}
	});

	if (it == m_pSpriteSheet->m_AnimationClips.end()) // Clip not found!
	{
		Utilities::Debug::LogWarning("SpriteSheetComponent::Play > Could not find the clip with name: " + string(clipName));
		Pause();
		return;
	}
	
	m_CurrentAnimationClip = *it;
	m_FramesPerSecond = m_CurrentAnimationClip.FramesPerSecond;
	m_CurrentFrame = 0;
	m_Status = SPlay;
	m_Loop = loop;
}

void SpriteSheetComponent::SetSpeed(int speed)
{
	m_FramesPerSecond = speed;
}

void SpriteSheetComponent::Reverse()
{
	if (m_Status == SPlay)
	{
		m_Status = SReverse;
	}
	else
	{
		m_Status = SPlay;
	}
}

void SpriteSheetComponent::Pause()
{
	m_Status = SIdle;
}

void SpriteSheetComponent::CalculateOrigin(const Origin &origin, const FrameData &frame)
{
	switch (origin)
	{
	case TopLeft:
		m_Origin = Vector2::Zero();
		break;

	case TopMiddle:
		m_Origin = Vector2::Zero();
		m_Origin.x = (float)frame.FrameRect.w / 2.0f;
		break;

	case TopRight:
		m_Origin = Vector2::Zero();
		m_Origin.x = (float)frame.FrameRect.w;
		break;

	case LeftCenter:
		m_Origin = Vector2::Zero();
		m_Origin.x = 0;
		m_Origin.y = (float)frame.FrameRect.h / 2.0f;
		break;

	case Center:
		m_Origin = Vector2::Zero();
		m_Origin.x = (float)frame.FrameRect.w / 2.0f;
		m_Origin.y = (float)frame.FrameRect.h / 2.0f;
		break;

	case RightCenter:
		m_Origin = Vector2::Zero();
		m_Origin.x = (float)frame.FrameRect.w;
		m_Origin.y = (float)frame.FrameRect.h / 2.0f;
		break;

	case BottomLeft:
		m_Origin = Vector2::Zero();
		m_Origin.x = 0;
		m_Origin.y = (float)frame.FrameRect.h;
		break;

	case BottomMiddle:
		m_Origin = Vector2::Zero();
		m_Origin.x = (float)frame.FrameRect.w / 2.0f;
		m_Origin.y = (float)frame.FrameRect.h;
		break;

	case BottomRight:
		m_Origin = Vector2::Zero();
		m_Origin.x = (float)frame.FrameRect.w;
		m_Origin.y = (float)frame.FrameRect.h;
		break;

	default:
		break;
	}
}
