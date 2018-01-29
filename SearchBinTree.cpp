template<class K, class V>
struct BSTNode//树的结点  
{
	BSTNode<K, V> *_pLeft;
	BSTNode<K, V>  *_pRight;
	K _data;
	V _value;
	BSTNode(const K &data, const V &value)
		:_data(data)
		, _value(value)
		, _pLeft(NULL)
		, _pRight(NULL)
	{}
};
template<class K, class V>
class BSTree
{
	typedef BSTNode<K, V> Node;
	typedef Node* _PNode;
private:
	_PNode _pRoot;
public:
	BSTree()
		:_pRoot(NULL){}
	bool Insert(const K& data, const V& value)
	{
		if (_pRoot == NULL)
		{
			_pRoot = new Node(data, value);//根节点  
			return true;
		}
		_PNode cur = _pRoot;
		_PNode pParent = NULL;
		while (cur)
		{
			if (cur->_data == data)
				return false;
			else if (cur->_data > data)
			{
				pParent = cur;
				cur = cur->_pLeft;
			}
			else
			{
				pParent = cur;
				cur = cur->_pRight;
			}
		}
		_PNode pNewNode = new Node(data, value);
		if (data<pParent->_data)
			pParent->_pLeft = pNewNode;
		else
			pParent->_pRight = pNewNode;
		return true;
	}
	K Mindata()
	{
		_PNode cur = _pRoot;
		while (cur->_pLeft)
			cur = cur->_pLeft;
		return cur->_data;
	}
	K Maxdata()
	{
		_PNode cur = _pRoot;
		while (cur->_pRight)
			cur = cur->_pRight;
		return cur->_data;
	}
	bool Delete(const K& data)
	{
		if (_pRoot == NULL)
			return false;
		_PNode cur = _pRoot;
		_PNode pParent = NULL;
		//首先找到删除的那个结点的位置  
		while (cur)
		{
			if (cur->_data == data)
				break;
			else if (cur->_data > data)
			{
				pParent = cur;
				cur = cur->_pLeft;
			}
			else
			{
				pParent = cur;
				cur = cur->_pRight;
			}
		}
		if (cur)
		{
			//找到这个结点以后开始判断下面三种情况  
			//1.只有右子树没有左子树  
			if (cur->_pLeft == NULL)
			{
				//如果当前结点是根结点的话  
				if (cur == _pRoot)
					_pRoot = _pRoot->_pRight;
				//当前结点是父结点的左子树还是右子树  
				else
				{
					if (cur == pParent->_pLeft)
						pParent->_pLeft = cur->_pRight;
					else
						pParent->_pRight = cur->_pRight;
				}
			}
			else if (cur->_pRight == NULL)//只有左子树没有右子树  
			{
				if (cur == _pRoot)
				{
					_pRoot = _pRoot->_pLeft;
				}
				else
				{
					if (pParent->_pLeft == cur)
						pParent->_pLeft = cur->_pLeft;
					else
						pParent->_pRight = cur->_pLeft;
				}
			}
			else//左右子树都有的情况下  
			{
				//首先找到右子树中最小的  
				_PNode Min = cur->_pRight;
				_PNode _pParent = cur;
				while (Min->_pLeft)
				{
					_pParent = Min;
					Min = Min->_pLeft;
				}//找到了最小的然后和要删除的值交换  
				cur->_data = Min->_data;
				cur->_value = Min->_value;
				if (_pParent->_pLeft == Min)
				{
					_pParent->_pLeft = Min->_pRight;
				}
				else
				{
					_pParent->_pRight = Min->_pRight;
				}
				delete[] Min;
				return true;
			}
		}
		delete[] cur;
		return true;
	}
	void InOrder()
	{
		_InOrder(_pRoot);
	}
	void _InOrder(_PNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}
};
void test()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree< int, int> bst;
	for (int i = 0; i < sizeof(a) / sizeof(*a); ++i)
	{
		bst.Insert(a[i], i);
	}
	cout << bst.Maxdata() << endl;
	cout << bst.Mindata() << endl;
	bst.Delete(9);
	bst.InOrder();
}