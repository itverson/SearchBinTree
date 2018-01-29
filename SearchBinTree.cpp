template<class K, class V>
struct BSTNode//���Ľ��  
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
			_pRoot = new Node(data, value);//���ڵ�  
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
		//�����ҵ�ɾ�����Ǹ�����λ��  
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
			//�ҵ��������Ժ�ʼ�ж������������  
			//1.ֻ��������û��������  
			if (cur->_pLeft == NULL)
			{
				//�����ǰ����Ǹ����Ļ�  
				if (cur == _pRoot)
					_pRoot = _pRoot->_pRight;
				//��ǰ����Ǹ���������������������  
				else
				{
					if (cur == pParent->_pLeft)
						pParent->_pLeft = cur->_pRight;
					else
						pParent->_pRight = cur->_pRight;
				}
			}
			else if (cur->_pRight == NULL)//ֻ��������û��������  
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
			else//�����������е������  
			{
				//�����ҵ�����������С��  
				_PNode Min = cur->_pRight;
				_PNode _pParent = cur;
				while (Min->_pLeft)
				{
					_pParent = Min;
					Min = Min->_pLeft;
				}//�ҵ�����С��Ȼ���Ҫɾ����ֵ����  
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