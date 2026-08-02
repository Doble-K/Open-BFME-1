// cl: /DNDEBUG /MD /EHsc

class TextureClass;
class VertexMaterialClass;

class Vector2
{
private:
	float m_x;
	float m_y;
};

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

// unsigned char / DefinitionClass* / Render2DClass* / tThreadInfoType* / ShaderClass
// were instantiated here too, but retail proves each has its OWN vtable
// (0x113ac74, 0x113a0fc x3, 0x113c5e4) while this folded body loads 0x11bc44c —
// so their destructors cannot be this body. See the DIR32 consistency gate.
template class VectorClass<int>;
template class VectorClass<float>;
template class VectorClass<TextureClass *>;
template class VectorClass<VertexMaterialClass *>;
template class VectorClass<Vector2>;
