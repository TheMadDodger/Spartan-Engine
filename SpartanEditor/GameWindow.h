#pragma once
#include "EditorWindow.h"
namespace Spartan::Editor
{
    class GameWindow : public EditorWindowTemplate<GameWindow>
    {
    public:
        GameWindow();
        virtual ~GameWindow();

    private:
        virtual void OnPaint() override;
        virtual void OnGUI() override;
    };
}