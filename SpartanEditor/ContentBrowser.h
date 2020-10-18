#pragma once
#include "EditorWindow.h"
#include "Event.h"

namespace Spartan::Editor
{
	class ContentBrowser : public EditorWindowTemplate<ContentBrowser>
	{
	public:
		ContentBrowser();
		virtual ~ContentBrowser();

		static Event<const std::filesystem::path&> OnFileDoubleClick;

	private:
		virtual void OnGUI() override;

	private:
		void ProcessDirectory(filesystem::path path);
		void ProcessFile(filesystem::path path);

		void DirectoryBrowser();
		void FileBrowser();
		void NonMetaFile(std::filesystem::path& path);

	private:
		int m_I;
		static int m_IconSize;
		std::hash<std::string> m_Hasher;
		filesystem::path m_SelectedPath;
		filesystem::path m_RootAssetPath;
	};
}