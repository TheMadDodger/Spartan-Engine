#pragma once
#include "EditorWindow.h"

namespace Spartan::Editor
{
    class SceneWindow : public EditorWindowTemplate<SceneWindow>
    {
    public:
        SceneWindow();
        virtual ~SceneWindow();

    private:
        virtual void OnGUI() override;
    };
}