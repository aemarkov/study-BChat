#ifndef __SMARTPOINTERDELETERS_H__
#define __SMARTPOINTERDELETERS_H__

/*!
 * \brief Ѕазовый класс deleter дл€ освобождение ресурсов при использовании
 * умных указателей
 *
 * ≈сли ресурс требуетс€ осовободить как-то по особому, реализуйте 
 * deletor и передайте в конструктор shared_ptr
 *
 * ƒл€ unique_ptr как-то по-особому
 */
template <class T>
class SmartPointerDeleter
{
public:
	virtual void operator()(T* pointer) = 0;
};

#endif
