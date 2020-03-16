#include "stdafx.h"
#include "UICanvas.h"

UICanvas::UICanvas() : GameObject("Canvas"), m_pRenderTexture(nullptr)
{
}

UICanvas::~UICanvas()
{
}

void UICanvas::Initialize(const GameContext& gameContext)
{
	
}

void UICanvas::Update(const GameContext& gameContext)
{
}

void UICanvas::Draw(const GameContext& gameContext)
{
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
}

void UICanvas::PostDraw(const GameContext& gameContext)
{
}
