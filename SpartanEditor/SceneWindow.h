#pragma once
#include "EditorWindow.h"
#include "SceneViewCamera.h"
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
        SceneViewCamera* m_pSceneCamera;
        RenderTexture* m_pSceneRenderTexture;
    };
}