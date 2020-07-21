#pragma once
#include "EditorWindow.h"
#include <RenderTexture.h>

namespace Spartan::Editor
{
    class SceneWindow : public EditorWindowTemplate<SceneWindow>
    {
    public:
        SceneWindow();
        virtual ~SceneWindow();

    private:
        virtual void OnPaint() override;
        virtual void OnGUI() override;

    private:
        RenderTexture* m_pRenderTexture;
    };
}