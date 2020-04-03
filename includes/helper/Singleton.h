#pragma once

/*!
 * @brief	adds Instance Getter
 *			removes constructor acsess
 */
#define GE_DECLARE_SINGLETON(CLASS)			\
public:										\
	static CLASS* GetInstancePtr(void)		\
	{										\
		if (!mpInstance)					\
			mpInstance = new CLASS();		\
		return mpInstance;					\
	}										\
	static CLASS& GetInstance(void)			\
	{										\
		if (!mpInstance)					\
			mpInstance = new CLASS();		\
		return *mpInstance;					\
	}										\
protected:									\
	CLASS() { }								\
	CLASS(const CLASS&);					\
	CLASS& operator=(const CLASS&) { }		\
	static CLASS* mpInstance;

/*!
 * @brief	initialices static members
 */
#define GE_DEFINE_SINGLETON(CLASS)			\
CLASS* CLASS::mpInstance = nullptr;