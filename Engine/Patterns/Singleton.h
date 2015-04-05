//#pragma once 
#define DECLARE_SINGLETON(a)	public: \
					static a& getInstance(){ \
						static a instance; \
						return instance; \
					}\
				private: \
					a(){} \
					a(const a& copy){} \
					~a(){} \
					a& operator= (const a& copy){}

#define DECLARE_SINGLETON_INIT(a) public: \
					static a& getInstance(){ \
						static a instance; \
						return instance; \
					}\
				  private: \
					a(){ init(); } \
					a(const a& copy){} \
					~a(){} \
					a& operator= (const a& copy){}