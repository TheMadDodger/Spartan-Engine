#pragma once
#include "EditorWindow.h"

namespace Spartan::Editor
{
	class ContentBrowser : public EditorWindowTemplate<ContentBrowser>
	{
	public:
		ContentBrowser();
		virtual ~ContentBrowser();

	private:
		virtual void OnGUI() override;

	private:
		void ProcessDirectory(filesystem::path path);
		void ProcessFile(filesystem::path path);

		void DirectoryBrowser();
		void FileBrowser();

	private:
		int m_I;
		std::hash<std::string> m_Hasher;
		filesystem::path m_SelectedPath;
		filesystem::path m_RootAssetPath;
	};
}