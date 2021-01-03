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
Node NIL = new RBTreeNode;				//哨兵结点
int main()
{
	NIL->color = BLACK;
	NIL->left = NULL;
	NIL->right = NULL;
	NIL->parent = NULL;
	cout << "1.插入结点" << endl;
	cout << "2.删除结点" << endl;
	cout << "3.查看红黑树" << endl;
	cout << "0.退出程序" << endl;
	int choice = 1;
	while (1)
	{
		cout << "输入选择：";
		cin >> choice;
		if (choice == 0)
		{
			break;
		}
		switch (choice)
		{
			case 1:
				DataType value;
				cout << "输入值：";
				cin >> value;
				insert(root, value);
				break;
			case 2:
				DataType del_value;
				cout << "输入值：";
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
			//调整红黑树
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
			//调整红黑树
			insert_case1(tmp);
		}
	}
}

//插入的是根节点，直接调整为黑色
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
//父节点是黑色，不用调整
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

//父亲结点和叔父结点红色，此时需要考虑两种，一种是祖父结点就在根节点，无需要考虑其他，还有一种就是不是在根节点，祖父节点有兄弟的时候，就需要先把根节点调红色，再回去调整
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

//父亲结点和子节点位置不一致，将这种情况调至情况5情况一致来处理
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
//情况5即是父节点和子节点所在的位置一致
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
//node为旋转的结点
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

//获取该节点的兄弟
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

//层序遍历
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
				cout << "红色  ";
			}
			else
			{
				cout << "黑色  ";
			}
			cout << node->value << "  " << endl;
			list.push(node->left);
			list.push(node->right);
		}
	}
}

//中序遍历
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

//删除孩子结点
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
		//检查右子树是否为空
		if (node->right == NIL)
		{
			//空的时候就当成删除一个结点的情况
			delete_one_child(node);
			return true;
		}
		//不为空的时候，则要去右子树取后继，无论是只有一个结点还是两个结点，都可以这样操作，直接用后继去替换根的值
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
	//取可能不为NIL的另一边
	Node child = node->left == NIL ? node->right : node->left;
	if (node->parent == NULL && node->left == NIL && node->right == NIL)
	{
		//删除的是根节点，并且左右子树都为空的情况
		node = NULL;
		root = node;
		return;
	}
	//删除根节点，左右子树有一个不为空
	if (node->parent == NULL)
	{
		delete node;
		child->parent = NULL;
		root = child;
		root->color = BLACK;
		return;
	}
	//删除的不是根节点
	if (node->parent->left == node)
	{
		node->parent->left = child;
	}
	else
	{
		node->parent->right = child;
	}
	//四种情况，第一种，删除的结点左右子树都是空的，直接删除
	//第二种，删除的跟结点黑色，子结点红色，将子节点改为黑色，再删除
	//第三种，删除的根结点是红色，子节点黑色，直接删除
	//第四种，删除的根节点和子结点都是黑色，分为另一种情况讨论
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

//情况1：删除了该结点，就还剩下根节点
void delete_case1(Node node)
{
	if (node->parent == NULL)
	{
		node->color = BLACK;
		return;
	}
	delete_case2(node);
}

//情况3，兄弟结点红色，两个孩子结点肯定为黑色，不然之前插入就已经不满足了，如果调整，还需要再去结点2判断一下
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

//情况2：结点2的父亲、兄弟，侄子结点都是黑色的时候
void delete_case3(Node node)
{
	Node sib = sibling(node);
	//此时的修正，让祖父结点两边的子树少了一个黑色，如果是根节点，没有问题，但是如果不是根节点的话，就比其他结点少了一个黑色了，所以需要重新重1开始进行调整
	if ((node->parent->color == BLACK) && (sib->color == BLACK) && (sib->left->color == BLACK) && (sib->right->color == BLACK))
	{
		sib->color = RED;
		delete_case1(node->parent);
	}
	else
		delete_case4(node);
}

//结点的父亲是红色，兄弟结点和侄子结点都是黑色
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

//变换为情况6，即兄弟结点下的红色子节点和兄弟结点所处的位置不一样，需要调成一致
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

//情况6，兄弟结点和红色结点的所处位置一致，然后就是为了让左边子树结点数增加，去补充删除的黑色子节点个数
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

//找删除结点的后继，即是右子树中的最小值
Node getSmallestChild(Node node)
{
	if (node->left == NIL)
	{
		return node;
	}
	return getSmallestChild(node->left);
}