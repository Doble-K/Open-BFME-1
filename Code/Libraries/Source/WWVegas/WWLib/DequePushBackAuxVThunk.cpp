class MapObject
{
};

class PartitionCell
{
};

class SightingInfo
{
};

namespace _STL
{
	template<class Type>
	class allocator
	{
	};

	template<class Type, class Allocator>
	class deque
	{
	protected:
		void _M_push_back_aux_v(Type const &);
	};

	template<class Type, class Allocator>
	__declspec(naked) void deque<Type, Allocator>::_M_push_back_aux_v(Type const &)
	{
		__asm {
			_emit 0E9h
			_emit 089h
			_emit 02Ah
			_emit 033h
			_emit 000h
		}
	}

	template __declspec(naked) void deque<MapObject *, allocator<MapObject *> >::_M_push_back_aux_v(MapObject * const &);
	template __declspec(naked) void deque<PartitionCell *, allocator<PartitionCell *> >::_M_push_back_aux_v(PartitionCell * const &);
	template __declspec(naked) void deque<SightingInfo *, allocator<SightingInfo *> >::_M_push_back_aux_v(SightingInfo * const &);
}
