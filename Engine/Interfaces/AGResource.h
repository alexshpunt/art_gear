#ifndef AG_RESOURCE_H
#define AG_RESOURCE_H

#include <string>

class AGResourceManager; 
class AGResPtr; 

///////////////////////////////////////////////////////////////////////////
///Ётот класс позвол€ет не беспокоитьс€ об освобождении ресурсов
///как только не будет существовать объектов, которые используют данный
///ресурс, то сразу же будет освобождена пам€ть. 
///////////////////////////////////////////////////////////////////////////
class AGResource 
{
	friend class AGResourceManager; 
	friend class AGResPtr; 
	public:
		virtual unsigned getType() const = 0; 
		const std::wstring& getName() const; 
		bool isValid() const; 

	protected:
		//ƒл€ AGResourceManager	
		AGResource();
		virtual ~AGResource(); 

		bool m_isValid; 
	private:
		//ƒл€ AGResPtr
		void incRef();
		void decRef(); 

		void setName( const std::wstring& name );

		AGResource& operator=( const AGResource& res ); 

		std::wstring m_name; 
		unsigned int m_refsCount; 
};

class AGResPtr 
{
	public:
		AGResPtr(); 
		AGResPtr( AGResource& res );
		AGResPtr( AGResource* res );
		~AGResPtr(); 

		AGResPtr& operator=( AGResource& res );
		AGResPtr& operator=( AGResource* res );

		AGResource* getData() const; 

		bool isNull() const; 

	private:
		AGResource* m_res; 
};



#endif 