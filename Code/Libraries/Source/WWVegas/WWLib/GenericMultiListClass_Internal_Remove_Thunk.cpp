// cl: /DNDEBUG /MD /EHs-c-
// Lift the GenericMultiListClass::Internal_Remove __emit thunk to clean C++.
//
// Verbatim Zero Hour multilist.cpp: walk the object's chain of list nodes to
// find the one belonging to this list, unlink it from both the object list and
// the node chain, then free it. The assert in ZH's else branch compiles away.
//
// Retail pins the layout: an object keeps its first list node at +0x04, and a
// node holds Prev at +0x00, Next at +0x04, NextList at +0x08 and its owning
// List at +0x10.
//
// The node is pool-allocated, so `delete` is not the CRT one: it becomes a
// two-instruction call into the object pool at 0x0134ECD4. Modelling that as a
// class-specific operator delete reproduces it exactly, and MSVC then duplicates
// the free-and-return-true tail into both arms of the unlink, which is why the
// same three instructions appear twice at the end of the retail body.

class GenericMultiListClass;

class ObjectPool
{
public:
	void Free_Object_Memory(void *block);					///< retail body at 0x009DBEB0
};

extern ObjectPool TheMultiListNodePool;						///< retail object at 0x0134ECD4

class MultiListNodeClass
{
public:
	void operator delete(void *block) { TheMultiListNodePool.Free_Object_Memory(block); }

	MultiListNodeClass *Prev;								///< retail this+0x00
	MultiListNodeClass *Next;								///< retail this+0x04
	MultiListNodeClass *NextList;							///< retail this+0x08
	unsigned char m_unreconstructed_0C[4];
	GenericMultiListClass *List;							///< retail this+0x10
};

class MultiListObjectClass
{
public:
	MultiListNodeClass *Get_List_Node(void) const { return ListNode; }
	void Set_List_Node(MultiListNodeClass *node) { ListNode = node; }

private:
	unsigned char m_unreconstructed_00[4];
	MultiListNodeClass *ListNode;							///< retail this+0x04
};

class GenericMultiListClass
{
protected:
	bool Internal_Remove(MultiListObjectClass *obj);
};

// ?Internal_Remove@GenericMultiListClass@@IAE_NPAVMultiListObjectClass@@@Z
bool GenericMultiListClass::Internal_Remove(MultiListObjectClass *obj)
{
	// find the list node in this object that belongs to this list
	MultiListNodeClass *lnode = obj->Get_List_Node();
	MultiListNodeClass *prevlnode = 0;

	while ((lnode) && (lnode->List != this))
	{
		prevlnode = lnode;
		lnode = lnode->NextList;
	}

	if (lnode == 0)
	{
		return false;
	}

	// now we've found the node which corresponds to this list,
	// unlink from the list of objects
	lnode->Prev->Next = lnode->Next;
	lnode->Next->Prev = lnode->Prev;

	// unlink from the list of list nodes
	if (prevlnode)
	{
		prevlnode->NextList = lnode->NextList;
	}
	else
	{
		obj->Set_List_Node(lnode->NextList);
	}

	// delete the link
	delete lnode;

	return true;
}
