#pragma once

#define OBJECT_TYPE(object) virtual const std::type_info& GetType() override { return typeid(object); }
#define OBJECT_BASETYPE(object) virtual const std::type_info& GetBaseType() override { return typeid(object); }
#define OBJECT_CREATE(object) virtual SEObject* Create() override { return (SEObject*)(new object()); }

#define BASIC_OBJECT(object, base) OBJECT_TYPE(object) \
OBJECT_BASETYPE(base) \
OBJECT_CREATE(object)

#define REGISTER_CLASS(c) Spartan::SEObject::RegisterObjectClass<c>()

namespace Spartan
{
	class SEObject
	{
	public:
		SEObject() {}
		virtual ~SEObject() {}

		virtual const std::type_info& GetBaseType() = 0;
		virtual const std::type_info& GetType() = 0;
		virtual SEObject* Create() = 0;

		static void DestroyClassTemplates();

		template<class T>
		static void RegisterObjectClass()
		{
			const std::type_info& type = typeid(T);
			size_t hashCode = GetClassHash(type);
			auto it = m_RegisteredClasses.find(hashCode);
			if (it != m_RegisteredClasses.end()) return; // Class already registered!

			SEObject* pObject = new T();
			m_RegisteredClasses[hashCode] = pObject;
			m_AllRegisteredClasses.push_back(pObject);

			const std::type_info& baseType = pObject->GetBaseType();
			size_t baseHashCode = GetClassHash(baseType);

			auto it2 = m_RegisteredClassesPerBaseType.find(baseHashCode);
			if (it2 == m_RegisteredClassesPerBaseType.end())
				m_RegisteredClassesPerBaseType[baseHashCode] = std::vector<SEObject*>();

			m_RegisteredClassesPerBaseType[baseHashCode].push_back(pObject);
		}
		template<class T>
		static SEObject* CreateObject()
		{
			return CreateObject(typeid(T));
		}

		static SEObject* CreateObject(const std::type_info& type);
		static SEObject* CreateObject(size_t hashCode);

		template<class T>
		static size_t GetClassHash()
		{
			const std::type_info& type = typeid(T);
			return GetAssetHash(type);
		}

		static size_t GetClassHash(const std::type_info& type);

		template<class T>
		static bool GetRegisteredClassCount(size_t& count)
		{
			return GetRegisteredClassCount(typeid(T), count);
		}

		static bool GetRegisteredClassCount(const std::type_info& baseType, size_t& count);
		static bool GetRegisteredClassCount(size_t baseHashCode, size_t& count);
		static size_t GetRegisteredClassCount();

		template<class T>
		static T* GetRegisteredClassAtIndex(size_t index)
		{
			return (T*)GetRegisteredClassAtIndex(typeid(T), index);
		}

		static SEObject* GetRegisteredClassAtIndex(const std::type_info& baseType, size_t index);
		static SEObject* GetRegisteredClassAtIndex(size_t baseHashCode, size_t index);
		static SEObject* GetRegisteredClassAtIndex(size_t index);

	private:
		static std::map<size_t, SEObject*> m_RegisteredClasses;
		static std::vector<SEObject*> m_AllRegisteredClasses;
		static std::map<size_t, std::vector<SEObject*>> m_RegisteredClassesPerBaseType;
		static std::hash<std::string> m_ClassHasher;
	};

	template<class T, class BaseT>
	class SEObjectTemplate : public SEObject
	{
	public:
		BASIC_OBJECT(T, BaseT);
	};
}