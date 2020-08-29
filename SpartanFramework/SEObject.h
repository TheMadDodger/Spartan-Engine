#pragma once

#define OBJECT_TYPE(object) virtual const std::type_info& GetType() override { return typeid(object); }
#define OBJECT_BASETYPE(object) virtual const std::type_info& GetBaseType() override { return typeid(object); }
#define OBJECT_CREATE(object) virtual SEObject* Create() override { return new object(); }

#define BASIC_OBJECT(object, base) OBJECT_TYPE(object) \
OBJECT_BASETYPE(base) \
OBJECT_CREATE(object)

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

		template<class T>
		static void RegisterObjectClass()
		{
			const std::type_info& type = typeid(T);
			size_t hashCode = type.hash_code();
			auto it = m_RegisteredClasses.find(hashCode);
			if (it != m_RegisteredClasses.end()) return;

			SEObject* pObject = new T();
			m_RegisteredClasses[hashCode] = pObject;
		}
		template<class T>
		static SEObject* CreateObject(const std::type_info& type)
		{
			return CreateObject(typeid(T));
		}

		static SEObject* CreateObject(const std::type_info& type);
		static SEObject* CreateObject(size_t hashCode);

	private:
		static std::map<size_t, SEObject*> m_RegisteredClasses;
	};

	template<class T, class BaseT>
	class SEObjectTemplate : public SEObject
	{
	public:
		BASIC_OBJECT(T, BaseT);
	};
}