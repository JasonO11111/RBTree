#include<iostream>
#include<queue>
using namespace std;
typedef struct RBTreeNode* Node;
typedef Node Root;
typedef int DataType;
typedef char Color;
#define RED 0
#define BLACK 1
struct RBTreeNode{
	Color color;
	DataType value;
	Node left;
	Node right;
	Node parent;
};
Node grandparent(Node node);
Node uncle(Node node);
Node sibling(Node node);
void insert(Node node, DataType data);
void insert_case1(Node node);
void insert_case2(Node node);
void insert_case3(Node node);
void insert_case4(Node node);
void insert_case5(Node node);
void rorate_left(Node node);
void rorate_right(Node node);
void traverse();
void inorder(Node node);
bool delete_child(Node node, DataType value);
Node getSmallestChild(Node node);
void delete_one_child(Node node);
void delete_case1(Node node);
void delete_case2(Node node);
void delete_case3(Node node);
void delete_case4(Node node);
void delete_case5(Node node);
void delete_case6(Node node);
Root root = NULL;
Node NIL = new RBTreeNode;				//�ڱ����
int main()
{
	NIL->color = BLACK;
	NIL->left = NULL;
	NIL->right = NULL;
	NIL->parent = NULL;
	cout << "1.������" << endl;
	cout << "2.ɾ�����" << endl;
	cout << "3.�鿴�����" << endl;
	cout << "0.�˳�����" << endl;
	int choice = 1;
	while (1)
	{
		cout << "����ѡ��";
		cin >> choice;
		if (choice == 0)
		{
			break;
		}
		switch (choice)
		{
			case 1:
				DataType value;
				cout << "����ֵ��";
				cin >> value;
				insert(root, value);
				break;
			case 2:
				DataType del_value;
				cout << "����ֵ��";
				cin >> del_value;
				delete_child(root, del_value);
				break;
			case 3:
				traverse();
				break;
			default:
				break;
		}
	}
	return 0;
}

void insert(Node node, DataType data)
{
	if (root == NULL)
	{
		root = new RBTreeNode;
		root->value = data;
		root->color = RED;
		root->parent = NULL;
		root->left = NIL;
		root->right = NIL;
		insert_case1(root);
		return;
	}
	if (node->value >= data)
	{
		if (node->left != NIL)
			insert(node->left,data);
		else
		{
			Node tmp = new RBTreeNode;
			tmp->value = data;
			tmp->color = RED;
			tmp->left = tmp->right = NIL;
			tmp->parent = node;
			node->left = tmp;
			//���������
			insert_case1(tmp);
		}
	}
	else
	{
		if (node->right != NIL)
			insert(node->right, data);
		else
		{
			Node tmp = new RBTreeNode;
			tmp->value = data;
			tmp->color = RED;
			tmp->left = tmp->right = NIL;
			tmp->parent = node;
			node->right = tmp;
			//���������
			insert_case1(tmp);
		}
	}
}

//������Ǹ��ڵ㣬ֱ�ӵ���Ϊ��ɫ
void insert_case1(Node node)
{
	if (node->parent == NULL)
	{
		node->color = BLACK;
	}
	else
	{
		insert_case2(node);
	}
}
//���ڵ��Ǻ�ɫ�����õ���
void insert_case2(Node node)
{
	if (node->parent->color == BLACK)
	{
		return;
	}
	else
	{
		insert_case3(node);
	}
}

//���׽����常����ɫ����ʱ��Ҫ�������֣�һ�����游�����ڸ��ڵ㣬����Ҫ��������������һ�־��ǲ����ڸ��ڵ㣬�游�ڵ����ֵܵ�ʱ�򣬾���Ҫ�ȰѸ��ڵ����ɫ���ٻ�ȥ����
void insert_case3(Node node)
{
	if (grandparent(node) != NULL && uncle(node)->color == RED)
	{
		node->parent->color = BLACK;
		grandparent(node)->color = RED;
		uncle(node)->color = BLACK;
		insert_case1(grandparent(node));
	}
	else
	{
		insert_case4(node);
	}
}

//���׽����ӽڵ�λ�ò�һ�£�����������������5���һ��������
void insert_case4(Node node)
{
	if (grandparent(node)->left == node->parent && node == node->parent->right)
	{
		rorate_left(node);
		node = node->left;
	}
	else if (grandparent(node)->right == node->parent && node == node->parent->left)
	{
		rorate_right(node);
		node = node->right;
	}
	insert_case5(node);
}
//���5���Ǹ��ڵ���ӽڵ����ڵ�λ��һ��
void insert_case5(Node node)
{
	node->parent->color = BLACK;
	grandparent(node)->color = RED;
	if (node == node->parent->left && node->parent == grandparent(node)->left)
	{
		rorate_right(node->parent);
	}
	else
	{
		rorate_left(node->parent);
	}
}
//nodeΪ��ת�Ľ��
void rorate_left(Node node)
{
	if (node->parent == NULL)
	{
		root = node;
		return;
	}
	Node gp = grandparent(node);
	Node fa = node->parent;
	Node y = node->left;
	fa->right = y;
	if (y != NIL)
		y->parent = fa;
	fa->parent = node;
	node->left = fa;
	if (root == fa)
		root = node;
	node->parent = gp;
	if (gp != NULL)
	{
		if (gp->left == fa)
			gp->left = node;
		else
			gp->right = node;
	}
}

void rorate_right(Node node)
{
	Node gp = grandparent(node);
	Node fa = node->parent;
	Node y = node->right;
	fa->left = y;
	if (y != NIL)
		y->parent = fa;
	fa->parent = node;
	node->right = fa;
	if (root == fa)
		root = node;
	node->parent = gp;
	if (gp != NULL)
	{
		if (gp->left == fa)
			gp->left = node;
		else
			gp->right = node;
	}
}

Node grandparent(Node node)
{
	if (node->parent == NULL)
		return NULL;
	return node->parent->parent;
}

Node uncle(Node node)
{
	if (grandparent(node) == NULL){
		return NULL;
	}
	if (node->parent == grandparent(node)->left)
		return grandparent(node)->right;
	else
		return grandparent(node)->left;
}

//��ȡ�ýڵ���ֵ�
Node sibling(Node node)
{
	if (node->parent->left == node)
	{
		return node->parent->right;
	}
	else
	{
		return node->parent->left;
	}
}

//�������
void traverse()
{
	queue<Node> list;
	Node node = NULL;
	if (root == NULL)
		return;
	list.push(root);
	while (!list.empty())
	{
		node = list.front();
		list.pop();
		if (node == NIL)
			continue;
		else
		{
			if (node->color == RED)
			{
				cout << "��ɫ  ";
			}
			else
			{
				cout << "��ɫ  ";
			}
			cout << node->value << "  " << endl;
			list.push(node->left);
			list.push(node->right);
		}
	}
}

//�������
void inorder(Node node)
{
	if (node == NIL)
		return;
	if (node->left != NIL)
		inorder(node->left);
	cout << node->value << " ";
	if (node->right != NIL)
		inorder(node->right);
}

//ɾ�����ӽ��
bool delete_child(Node node, DataType value)
{
	if (node->value > value)
	{
		if (node->left == NIL)
			return false;
		return delete_child(node->left, value);
	}
	else if (node->value < value)
	{
		if (node->right == NIL)
			return false;
		return delete_child(node->right, value);
	}
	else if (node->value == value)
	{
		//����������Ƿ�Ϊ��
		if (node->right == NIL)
		{
			//�յ�ʱ��͵���ɾ��һ���������
			delete_one_child(node);
			return true;
		}
		//��Ϊ�յ�ʱ����Ҫȥ������ȡ��̣�������ֻ��һ����㻹��������㣬����������������ֱ���ú��ȥ�滻����ֵ
		Node smallNode = getSmallestChild(node->right);
		swap(node->value, smallNode->value);
		delete_one_child(smallNode);
		return true;
	}
	else
	{
		return false;
	}
}

void delete_one_child(Node node)
{
	//ȡ���ܲ�ΪNIL����һ��
	Node child = node->left == NIL ? node->right : node->left;
	if (node->parent == NULL && node->left == NIL && node->right == NIL)
	{
		//ɾ�����Ǹ��ڵ㣬��������������Ϊ�յ����
		node = NULL;
		root = node;
		return;
	}
	//ɾ�����ڵ㣬����������һ����Ϊ��
	if (node->parent == NULL)
	{
		delete node;
		child->parent = NULL;
		root = child;
		root->color = BLACK;
		return;
	}
	//ɾ���Ĳ��Ǹ��ڵ�
	if (node->parent->left == node)
	{
		node->parent->left = child;
	}
	else
	{
		node->parent->right = child;
	}
	//�����������һ�֣�ɾ���Ľ�������������ǿյģ�ֱ��ɾ��
	//�ڶ��֣�ɾ���ĸ�����ɫ���ӽ���ɫ�����ӽڵ��Ϊ��ɫ����ɾ��
	//�����֣�ɾ���ĸ�����Ǻ�ɫ���ӽڵ��ɫ��ֱ��ɾ��
	//�����֣�ɾ���ĸ��ڵ���ӽ�㶼�Ǻ�ɫ����Ϊ��һ���������
	if (node->left != NIL || node->right != NIL)
	{
		child->parent = node->parent;
		if (node->color == BLACK)
		{
			if (child->color == RED)
			{
				child->color = BLACK;
			}
			else
			{
				delete_case1(child);
			}
		}
	}
	delete node;
}

//���1��ɾ���˸ý�㣬�ͻ�ʣ�¸��ڵ�
void delete_case1(Node node)
{
	if (node->parent == NULL)
	{
		node->color = BLACK;
		return;
	}
	delete_case2(node);
}

//���3���ֵܽ���ɫ���������ӽ��϶�Ϊ��ɫ����Ȼ֮ǰ������Ѿ��������ˣ��������������Ҫ��ȥ���2�ж�һ��
void delete_case2(Node node)
{
	Node sib = sibling(node);
	if (sib->color == RED)
	{
		node->parent->color = RED;
		sib->color = BLACK;
		if (node->parent->left == sib)
			rorate_right(node->parent);
		else
			rorate_left(node->parent);
	}
	delete_case3(node);
}

//���2�����2�ĸ��ס��ֵܣ�ֶ�ӽ�㶼�Ǻ�ɫ��ʱ��
void delete_case3(Node node)
{
	Node sib = sibling(node);
	//��ʱ�����������游������ߵ���������һ����ɫ������Ǹ��ڵ㣬û�����⣬����������Ǹ��ڵ�Ļ����ͱ������������һ����ɫ�ˣ�������Ҫ������1��ʼ���е���
	if ((node->parent->color == BLACK) && (sib->color == BLACK) && (sib->left->color == BLACK) && (sib->right->color == BLACK))
	{
		sib->color = RED;
		delete_case1(node->parent);
	}
	else
		delete_case4(node);
}

//���ĸ����Ǻ�ɫ���ֵܽ���ֶ�ӽ�㶼�Ǻ�ɫ
void delete_case4(Node node)
{
	Node sib = sibling(node);
	if ((node->parent->color == RED) && (sib->color == BLACK) && (sib->left->color == BLACK) && (sib->right->color == BLACK))
	{
		sib->color = RED;
		node->parent->color = BLACK;
	}
	else
	{
		delete_case5(node);
	}
}

//�任Ϊ���6�����ֵܽ���µĺ�ɫ�ӽڵ���ֵܽ��������λ�ò�һ������Ҫ����һ��
void delete_case5(Node node)
{
	Node sib = sibling(node);
	if (sib->color == BLACK)
	{
		if ((node == node->parent->left) && (sib->right->color == BLACK) && (sib->left->color == RED))
		{
			sib->color = RED;
			sib->left->color = BLACK;
			rorate_right(sib);
		}
		else if ((node == node->parent->right) && (sib->left->color == BLACK) && (sib->right->color == RED))
		{
			sib->color = RED;
			sib->right->color = BLACK;
			rorate_left(sib);
		}
	}
	delete_case6(node);
}

//���6���ֵܽ��ͺ�ɫ��������λ��һ�£�Ȼ�����Ϊ�������������������ӣ�ȥ����ɾ���ĺ�ɫ�ӽڵ����
void delete_case6(Node node)
{
	Node sib = sibling(node);
	sib->color = node->parent->color;
	node->parent->color = BLACK;
	if (node == node->parent->left)
	{
		sib->right->color = BLACK;
		rorate_left(node->parent);
	}
	else
	{
		sib->left->color = BLACK;
		rorate_right(node->parent);
	}
}

//��ɾ�����ĺ�̣������������е���Сֵ
Node getSmallestChild(Node node)
{
	if (node->left == NIL)
	{
		return node;
	}
	return getSmallestChild(node->left);
}