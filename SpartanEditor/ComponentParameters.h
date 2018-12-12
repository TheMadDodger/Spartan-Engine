#pragma once
#include <Components.h>

template<typename T>
struct Range
{
	Range() {};
	Range(T min, T max) : Min(min), Max(max) {};

	T Min;
	T Max;
};

class ComponentParamBase
{
public:
	explicit ComponentParamBase(const std::string &name) : m_Name(name) {}
	virtual ~ComponentParamBase() {}

	const std::string &GetName() { return m_Name; }

	virtual void Apply() = 0;

	virtual void MakeImGui() = 0;

private:
	std::string m_Name;
};

class ComponentStringParam : public ComponentParamBase
{
public:
	ComponentStringParam(const std::string &name, const char *data, char *value) : Data(data), Value(value), ComponentParamBase(name) {}
	const char *Data;
	char *Value;

	//Range<float> Range;
	//T Step;

private:
	virtual void Apply()
	{
		//ZeroMemory(Value, 100);
		//memcpy(Value, Data, strlen(Data));
	}

	virtual void MakeImGui()
	{
		ImGui::InputText(GetName().data(), Value, 100);
	}
};

template<typename T>
class ComponentParam : public ComponentParamBase
{
public:
	ComponentParam(const std::string &name, T data, T& value) : Data(data), Value(value), ComponentParamBase(name) {}
	T Data;
	T &Value;

	Range<T> Range;
	T Step;

private:
	virtual void Apply()
	{
		Value = Data;
	}

	virtual void MakeImGui()
	{
		if (typeid(T) == typeid(float))
		{
			ImGui::InputFloat(GetName().data(), (float*)&Data);
		}
		else if(typeid(T) == typeid(int))
		{
			ImGui::InputInt(GetName().data(), (int*)&Data);
		}
		else if (typeid(T) == typeid(Vector2))
		{
			ImGui::InputFloat2(GetName().data(), (float*)&Data);
		}
		else if (typeid(T) == typeid(Vector3))
		{
			ImGui::InputFloat3(GetName().data(), (float*)&Data);
		}
		else if (typeid(T) == typeid(Color))
		{
			if (ImGui::ColorEdit4(GetName().data(), (float*)&Data))
			{
				ImGui::ColorPicker4(GetName().data(), (float*)&Data);
			}
		}
		else
		{
			// Unsuported type!
		}
	}
};

class BaseComponentParameters
{
public:
	explicit BaseComponentParameters() {};
	virtual ~BaseComponentParameters()
	{
		for (auto pParam : m_pParams)
		{
			delete pParam;
		}
		m_pParams.clear();
	};

	virtual BaseComponentParameters *Create(BaseComponent *pComponent) = 0;
	virtual void LoadParams() = 0;
	virtual const std::type_info &GetType() { return typeid(this); };
	void AddParam(ComponentParamBase *pParam) { m_pParams.push_back(pParam); }

protected:
	std::vector<ComponentParamBase*> m_pParams;
};

template <typename T>
class ComponentParameters : public BaseComponentParameters
{
public:
	ComponentParameters(T *pComponent) : m_pComponent(pComponent)
	{
		/*if (!pComponent)
		{
			m_IsTemplate = true;
			m_pComponent = new T();
		}*/
	}
	ComponentParameters(std::function<void(ComponentParameters<T>*)> func) : m_pComponent(nullptr), m_BuildParamsFunc(func) {}

	virtual ~ComponentParameters()
	{
		/*if (m_IsTemplate)
		{
			delete m_pComponent;
			m_pComponent = nullptr;
		}*/
	}

	BaseComponentParameters *Create(BaseComponent *pComponent) override
	{
		auto pObj = new ComponentParameters<T>(dynamic_cast<T*>(pComponent));
		m_BuildParamsFunc(pObj);
		return pObj;
	}
	
	virtual void LoadParams()
	{
		std::for_each(m_pParams.begin(), m_pParams.end(), [&](ComponentParamBase *pParam)
		{
			pParam->MakeImGui();
			pParam->Apply();
		});
	}

	virtual const std::type_info &GetType()
	{
		return typeid(T*);
	}

	T *m_pComponent;

protected:
	bool m_IsTemplate = false;

	std::function<void(ComponentParameters<T>*)> m_BuildParamsFunc;
};

struct ComponentConnection
{
	ComponentConnection(BaseComponent *pComp, BaseComponentParameters *pParam) : pComponent(pComp), pParams(pParam) {}

	BaseComponent *pComponent;
	BaseComponentParameters *pParams;
};

class ComponentParameterManager
{
public:
	static ComponentParameterManager *GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new ComponentParameterManager();
		return m_pInstance;
	}

	static void Destroy()
	{
		if (m_pInstance)
			delete m_pInstance;

		m_pInstance = nullptr;
	}

	void Register(BaseComponentParameters *pTemplate)
	{
		if(pTemplate)
			m_pRegisteredTemplates.push_back(pTemplate);
	}

	BaseComponentParameters *Find(BaseComponent *pComponent)
	{
		auto it = std::find_if(m_ConnectedComponents.begin(), m_ConnectedComponents.end(), [&](const ComponentConnection &pComp)
		{
			if (pComp.pComponent == pComponent)
				return true;
			return false;
		});
		if (it == m_ConnectedComponents.end())
			return nullptr;

		auto conn = *it;
		return conn.pParams;
	}

	BaseComponentParameters *Create(BaseComponent *pComponent)
	{
		auto pParam = Find(pComponent);
		if (pParam)
		{
			return pParam;
		}

		auto it = std::find_if(m_pRegisteredTemplates.begin(), m_pRegisteredTemplates.end(), [&](BaseComponentParameters *pParams)
		{
			const std::type_info &info1 = pParams->GetType();
			const std::type_info &info2 = pComponent->GetType();
			if (pParams->GetType() == pComponent->GetType())
				return true;
			return false;
		});

		if (it == m_pRegisteredTemplates.end())
			return nullptr;

		auto pParams = *it;
		auto pNewParam = pParams->Create(pComponent);
		m_pComponetParams.push_back(pNewParam);
		m_ConnectedComponents.push_back(ComponentConnection(pComponent, pNewParam));
		return pNewParam;
	}

	void Clear()
	{
		for (auto pParam : m_pComponetParams)
		{
			delete pParam;
		}
		m_pComponetParams.clear();
		m_ConnectedComponents.clear();
	}

private:
	ComponentParameterManager() {}
	~ComponentParameterManager()
	{
		Clear();
		for (auto pParam : m_pRegisteredTemplates)
		{
			delete pParam;
		}
		m_pRegisteredTemplates.clear();
	}

private:
	static ComponentParameterManager *m_pInstance;

private:
	std::vector<BaseComponentParameters*> m_pRegisteredTemplates;
	std::vector<BaseComponentParameters*> m_pComponetParams;
	std::vector<ComponentConnection> m_ConnectedComponents;
};

class TransformParams : public ComponentParameters<TransformComponent>
{
public:
	TransformParams(TransformComponent *pComp) : ComponentParameters<TransformComponent>(pComp) {}
	virtual ~TransformParams() {}

public:
	//virtual void BuildParams() final;
};