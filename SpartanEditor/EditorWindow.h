#pragma once

namespace Spartan::Editor
{
	class EditorWindow
	{
	public:
		EditorWindow(const std::string& windowName, float windowWidth, float windowHeight) : m_WindowName(windowName), m_WindowDimensions(windowWidth, windowHeight), m_IsOpen(true) {}
		~EditorWindow() {}

		template<typename T>
		static EditorWindow* GetWindow()
		{
			for (size_t i = 0; i < m_pActiveEditorWindows.size(); ++i)
			{
				if (m_pActiveEditorWindows[i]->GetType() == typeid(T))
					return m_pActiveEditorWindows[i];
			}

			auto pWindow = new T();
			m_pActiveEditorWindows.push_back(pWindow);
			return pWindow;
		}

		virtual const std::type_info& GetType() = 0;

		void Close();

	protected:
		virtual void OnPaint() = 0;
		virtual void OnGUI() = 0;

	private:
		void RenderGUI();

		static void RenderWindows();

	protected:
		friend class EditorApp;
		const std::string m_WindowName;
		ImVec2 m_WindowDimensions;
		static std::vector<EditorWindow*> m_pActiveEditorWindows;
		static std::vector<EditorWindow*> m_pClosingEditorWindows;
		bool m_IsOpen;
	};

	template<typename T>
	class EditorWindowTemplate : public EditorWindow
	{
	public:
		EditorWindowTemplate(const std::string& windowName, float windowWidth, float windowHeight) : EditorWindow(windowName, windowWidth, windowHeight) {}
		virtual ~EditorWindowTemplate() {}

	private:
		virtual const std::type_info& GetType() override
		{
			return typeid(T);
		}
	};
}