#pragma once
class EditorWindow
{
public:
	EditorWindow(const std::string &windowName, float windowWidth, float windowHeight) {}
	~EditorWindow() {}

	template<typename T>
	static EditorWindow *GetWindow()
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

	virtual const std::type_info &GetType() = 0;

protected:
	virtual void OnGUI() = 0;

private:
	void RenderGUI();

private:
	friend class GameTool;
	const std::string m_WindowName;
	ImVec2 m_WindowDimensions;
	static std::vector<EditorWindow*> m_pActiveEditorWindows;
};

template<typename T>
class EditorWindowTemplate : public EditorWindow
{
public:
	EditorWindowTemplate(const std::string &windowName, float windowWidth, float windowHeight) : EditorWindow(windowName, windowWidth, windowHeight) {}
	virtual ~EditorWindowTemplate() {}

private:
	virtual const std::type_info &GetType() override
	{
		return typeid(T);
	}
};

