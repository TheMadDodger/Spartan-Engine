#pragma once
#include "Singleton.h"

struct LayerData
{
public:
	LayerData() : LayerFlag(0), LayerID(0), LayerName(""), IsUILayer(false) {}

private:
	LayerData(size_t id, size_t flag, const std::string& layerName, bool isUILayer);

public:
	size_t LayerFlag;
	size_t LayerID;
	std::string LayerName;
	bool IsUILayer;

private:
	friend class LayerManager;
};

class DefaultLayerNames
{
public:
	static const std::string Default;
	static const std::string Background;
	static const std::string MiddleLayer;
	static const std::string ForeGround;
	static const std::string UIBackground;
	static const std::string UIMiddle;
	static const std::string UIForeground;

private:
	DefaultLayerNames() {}
	~DefaultLayerNames() {}
};

class LayerManager : public Singleton<LayerManager>
{
public:
	LayerManager();
	~LayerManager();

	const LayerData& CreateLayer(const std::string& layerName, bool isUILayer = false);
	const LayerData& operator[](const std::string &layer);
	const LayerData& operator[](size_t layerID);

	size_t Size();

private:
	std::map <std::string, LayerData> m_LayerData;
	std::vector <std::string> m_LayerIDToName;

private:
	void CreateDefaultLayers();
};
