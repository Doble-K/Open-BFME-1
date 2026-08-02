// cl: /DNDEBUG /MD /EHsc

class DefinitionClass;
class Render2DClass;
class TextureClass;

template <class T>
class VectorClass
{
public:
	virtual ~VectorClass();

private:
	T *m_vector;
	int m_vectorMax;
	bool m_isValid;
	bool m_isAllocated;
	bool m_padding[2];
};

template <class T>
VectorClass<T>::~VectorClass()
{
	if (m_vector != 0 && m_isAllocated)
	{
		delete[] m_vector;
		m_vector = 0;
	}

	m_isAllocated = false;
	m_vectorMax = 0;
}

template class VectorClass<int>;
template class VectorClass<float>;
template class VectorClass<unsigned char>;
template class VectorClass<DefinitionClass *>;
template class VectorClass<Render2DClass *>;
template class VectorClass<TextureClass *>;
