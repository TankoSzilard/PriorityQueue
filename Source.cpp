#include<iostream>
#include<queue>
class Node
{
public:
	int value;
	Node* parent, * left, * right;
	Node()
	{
		value = 0;
		parent = left = right = nullptr;
	}
	int kids()
	{
		if (this->left == nullptr && this->right == nullptr)
			return 0;
		if (this->left != nullptr && this->right == nullptr)
			return 1;
		if (this->left == nullptr && this->right != nullptr)
			return 2;
		if (this->left != nullptr && this->right != nullptr)
			return 3;
	}
};
class BinaryTree
{
private:
	Node* H;
	int size;
	void RSD(Node* node)//Parcurgere radacina-stanga-dreapta
	{
		if (node == nullptr)
			return;
		std::cout << node->value << ' ';
		RSD(node->left);
		RSD(node->right);
	}
	void SRD(Node* node)//Parcurgere stanga-dreapta-radacina
	{
		if (node == nullptr)
			return;
		SRD(node->left);
		std::cout << node->value << ' ';
		SRD(node->right);
	}
	void SDR(Node* node)//Parcurgere stanga-radacina-dreapta
	{
		if (node == nullptr)
			return;
		SDR(node->left);
		SDR(node->right);
		std::cout << node->value << ' ';
	}
	void readNodes(Node* parent, int position)
	{
		Node* node = new Node;
		int copii;
		std::cout << "Introduceti valoarea fiului ";
		if (position == 1)
			std::cout << "stang al nodului cu valoarea " << parent->value << '\n';
		else
			std::cout << "drept al nodului cu valoarea " << parent->value << '\n';
		std::cin >> node->value;
		node->parent = parent;
		if (position == 1)
			parent->left = node;
		else
			parent->right = node;
		std::cout << "Introduceti 0 daca acest nod nu are fii,1 daca are numai  un fiu stang, 2 daca are numai un fiu drept, sau 3 daca are 2 fii.\n";
		std::cin >> copii;
		switch (copii)
		{
		case 1:
			readNodes(node, 1);
			node->right = nullptr;
			break;
		case 2:
			node->left = nullptr;
			readNodes(node, 2);
			break;
		case 3:
			readNodes(node, 1);
			readNodes(node, 2);
			break;
		default:
			node->left = node->right = nullptr;
			break;
		}

	}
public:
	BinaryTree()
	{
		H = nullptr;
		size = 0;
	}
	void read()
	{
		H = new Node;
		int copii;
		std::cout << "Introduceti valoarea radacinii: ";
		std::cin >> H->value;
		std::cout << "Introduceti 0 daca acest nod nu are fii,1 daca are numai  un fiu stang, 2 daca are numai un fiu drept, sau 3 daca are 2 fii.\n";
		std::cin >> copii;
		switch (copii)
		{
		case 1:
			readNodes(H, 1);
			H->right = nullptr;
			break;
		case 2:
			H->left = nullptr;
			readNodes(H, 2);
			break;
		case 3:
			readNodes(H, 1);
			readNodes(H, 2);
			break;
		default:
			H->left = H->right = nullptr;
			break;
		}

	}
	Node* head()
	{
		return H;
	}
	int height(Node* nod)
	{
		if (nod == nullptr)
			return -1;
		return 1 + std::max(height(nod->left), height(nod->right));
	}
	void preordine()
	{
		std::cout << "parcurgerea in preordine: ";
		RSD(H);
		std::cout << '\n';
	}
	void inordine()
	{
		std::cout << "parcurgerea in inordine: ";
		SRD(H);
		std::cout << '\n';
	}
	void postordine()
	{
		std::cout << "parcurgerea in postordine: ";
		SDR(H);
		std::cout << '\n';
	}


	void niveluri()
	{
		std::cout << "parcurgerea pe niveluri: ";
		int currentLevel = 0;
		std::queue<Node*> coada1, coada2;
		coada1.push(H);
		do
		{
			std::cout << "\nNivelul " << currentLevel << ": ";
			do
			{
				std::cout << coada1.front()->value << ' ';
				if (coada1.front()->left)
					coada2.push(coada1.front()->left);
				if (coada1.front()->right)
					coada2.push(coada1.front()->right);
				coada1.pop();
			} while (!coada1.empty());
			while (!coada2.empty())
			{
				coada1.push(coada2.front());
				coada2.pop();
			}
			++currentLevel;
		} while (!coada1.empty());
		std::cout << '\n';
	}

	void printFrunze()
	{
		std::cout << "frunzele: ";
		std::queue<Node*>q;
		q.push(H);
		while (!q.empty())
		{
			bool l = 0, r = 0;
			if (q.front()->left != nullptr)
			{
				q.push(q.front()->left);
				l = 1;
			}
			if (q.front()->right != nullptr)
			{
				q.push(q.front()->right);
				r = 1;
			}
			if (l == 0 && r == 0)
				std::cout << q.front()->value << ' ';
			q.pop();
		};
		std::cout << '\n';
	}

	bool compare(BinaryTree h1, BinaryTree h2)
	{
		std::queue<Node*>q1, q2;
		q1.push(h1.H);
		q2.push(h2.H);
		do
		{
			if (q1.front()->value != q2.front()->value)
				return 0;
			int k1 = q1.front()->kids();
			int k2 = q2.front()->kids();
			if (k1 != k2)
				return 0;
			if (k1 == 1)
			{
				q1.push(q1.front()->left);
				q2.push(q2.front()->left);
			}
			if (k1 == 2)
			{
				q1.push(q1.front()->right);
				q2.push(q2.front()->right);
			}
			if (k1 == 3)
			{
				q1.push(q1.front()->left);
				q2.push(q2.front()->left);
				q1.push(q1.front()->right);
				q2.push(q2.front()->right);

			}

			q1.pop();
			q2.pop();
		} while (!q1.empty() && !q2.empty());
		return q1.empty() == q1.empty();
	}
	bool isCompleteTree()
	{
		std::queue<Node*>q;
		q.push(H);
		do
		{
			bool l = 1, r = 1;
			if (q.front()->left != nullptr)
			{
				q.push(q.front()->left);
				l = 0;
			}
			if (q.front()->right != nullptr)
			{
				q.push(q.front()->right);
				r = 0;
			}
			if (l != r)
				return false;
		} while (!q.empty());
		return true;
	}
	int depth(Node* nod)
	{
		if (nod == H)
			return 0;
		return 1 + depth(nod->parent);
	}
};



int main()
{
	BinaryTree test;
	test.read();
	test.preordine();
	test.inordine();
	test.postordine();
	test.niveluri();
	test.printFrunze();
	std::cout << "\nInaltimea arborebui : " << test.height(test.head());
	return 0;
}