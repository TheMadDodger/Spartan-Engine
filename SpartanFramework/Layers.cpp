#include "stdafx.h"
#include "Layers.h"

namespace SpartanEngine
{
	const std::string DefaultLayerNames::Default = "Default";
	const std::string DefaultLayerNames::Background = "Background";
	const std::string DefaultLayerNames::MiddleLayer = "MiddleLayer";
	const std::string DefaultLayerNames::ForeGround = "ForeGround";
	const std::string DefaultLayerNames::UIBackground = "UIBackground";
	const std::string DefaultLayerNames::UIMiddle = "UIMiddle";
	const std::string DefaultLayerNames::UIForeground = "UIForeground";

	LayerManager::LayerManager()
	{
		CreateDefaultLayers();
	}

	LayerManager::~LayerManager() {}

	const LayerData& LayerManager::CreateLayer(const std::string& layerName, bool isUILayer)
	{
		size_t flag = 1 << m_LayerData.size();
		LayerData layerData = LayerData(m_LayerData.size(), flag, layerName, isUILayer);
		m_LayerData.try_emplace(layerName, layerData);
		m_LayerIDToName.push_back(layerName);
		return m_LayerData[layerName];
	}

	const LayerData& LayerManager::operator[](const std::string& layer)
	{
		if (m_LayerData.count(layer) <= 0)
			throw new exception("The specified layer doesn't exist!");
		return m_LayerData[layer];
	}

	const LayerData& LayerManager::operator[](size_t layerID)
	{
		if (layerID >= m_LayerIDToName.size())
			throw new exception();

		const std::string& layerName = m_LayerIDToName[layerID];
		return operator[](layerName);
	}

	size_t LayerManager::Size()
	{
		return m_LayerIDToName.size();
	}

	void LayerManager::CreateDefaultLayers()
	{
		CreateLayer(DefaultLayerNames::Default);
		CreateLayer(DefaultLayerNames::Background);
		CreateLayer(DefaultLayerNames::MiddleLayer);
		CreateLayer(DefaultLayerNames::ForeGround);
		CreateLayer(DefaultLayerNames::UIBackground, true);
		CreateLayer(DefaultLayerNames::UIMiddle, true);
		CreateLayer(DefaultLayerNames::UIForeground, true);
	}

	LayerData::LayerData(size_t id, size_t flag, const std::string& layerName, bool isUILayer)
		: LayerID(id), LayerName(layerName), LayerFlag(flag), IsUILayer(isUILayer)
	{}
}