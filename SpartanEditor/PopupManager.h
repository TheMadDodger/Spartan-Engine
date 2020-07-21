#pragma once

namespace Spartan::Editor
{
	class PopupManager
	{
	private:
		struct Popup
		{
			Popup(const std::string& name, const std::string& description, const std::vector<std::string>& buttons, const std::vector<std::function<void()>>& buttonFuncs);

			const std::string m_PopupName;
			const std::string m_PopupDescription;
			const std::vector<std::string> m_Buttons;
			const std::vector<std::function<void()>> m_ButtonFuncs;
		};

	public:
		static void OpenPopup(const std::string& name, const std::string& description, const std::vector<std::string>& buttons, const std::vector<std::function<void()>>& buttonFuncs);
		static void CloseCurrentPopup();

	private:
		friend class EditorApp;
		static void OnGUI();

		static vector<Popup> m_Popups;
		static vector<std::string> m_OpeningPopupNames;

	private:
		PopupManager();
		virtual ~PopupManager();
	};
}