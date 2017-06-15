#include <fstream>
#include <iostream>

template <class T> struct Node
{
	T _key;
	Node<T>* _left;
	Node<T>* _right;
};
template <class T> class BST
{
private:
	Node<T>*_root;
	int _count;
public:
	BST();
	~BST();
	void delete_tree(Node<T>*);
	void insert_node(const T&);
	int get_count() const;
	void print() const;
	Node<T>* find_node(const T&, Node<T>*)const;
	Node<T>*root_()const;
	void display(Node<T>*, unsigned int)const;
	void out()const;
	void reading(const std::string&);
	void output(std::ostream&, Node<T>*)const;
	void writing(const std::string&)const;
	bool delete_value(Node<T>*, Node<T>*, const T&);
	bool delete_val(const T&);
};

template<class T>
BST<T>::BST()
{
	_root = nullptr;
	_count = 0;
}

template<class T>
BST<T>::~BST()
{
	delete_tree(_root);
	_count = 0;
}

template<class T>
void BST<T>::delete_tree(Node<T>* temp)
{
	if (!temp)
		return;
	if (temp->_left)
	{
		delete_tree(temp->_left);
		temp->_left = nullptr;
	}

	if (temp->_right)
	{
		delete_tree(temp->_right);
		temp->_right = nullptr;
	}
	delete temp;
}

template<class T>
Node<T>*BST<T>::root_()const
{
	return _root;
}

template<class T>
int BST<T>::get_count()const
{
	return _count;
}

template<class T>
void BST<T>::insert_node(const T&val)
{
	if (find_node(val, _root) != nullptr) return;
	Node<T>* dn = new Node<T>;
	dn->_key = val;
	dn->_left = dn->_right = 0;
	Node<T>* pn = _root;
	Node<T>* temp = _root;
	while (temp)
	{
		pn = temp;
		if (val < temp->_key)
			temp = temp->_left;
		else
			temp = temp->_right;
	}
	if (!pn)
		_root = dn;
	else
	{
		if (val < pn->_key)
			pn->_left = dn;
		else
			pn->_right = dn;
	}
	_count++;
}
template<class T>
Node<T>* BST<T>::find_node(const T& val, Node<T>* temp) const
{
	if (temp == nullptr || val == temp->_key)
		return temp;
	if (val > temp->_key)
		return find_node(val, temp->_right);
	else
		return find_node(val, temp->_left);
}

template<typename T>
void BST<T>::reading(const std::string& filename)
{
	std::ifstream fin(filename);
	try
	{
		if (!fin.is_open()) throw 404;
		int k;
		fin >> k;
		T temp;
		if (_root != nullptr)
		{
			delete_tree(_root);
			_root = nullptr;
			_count = 0;
		}
		for (int i = 0; i < k; ++i)
		{
			fin >> temp;
			insert_node(temp);
		}
		fin.close();
	}
	catch (int i)
	{
		std::cout << "The file wasn't found" << std::endl;
	}
}
template<typename T>
void BST<T>::print() const
{
	output(std::cout, this->_root);
}
template<typename T>
void BST<T>::output(std::ostream& out, Node<T>* temp)const
{
	if (!temp) return;
	out << temp->_key << " ";
	output(out, temp->_left);
	output(out, temp->_right);
}

template<typename T>
void BST<T>::writing(const std::string& filename)const
{
	std::ofstream fout(filename);
	try
	{
		if (!fout.is_open())
			throw 99;
		fout << _count << " ";
		output(fout, _root);
		fout.close();
	}
	catch (int i)
	{
		std::cout << "The file wasn't found" << std::endl;
	}
}

template<typename T>
void BST<T>::display(Node<T>* temp, unsigned int level)const
{
	if (temp)
	{
		display(temp->_left, level + 1);
		for (unsigned int i = 0; i < level; i++)
			std::cout << "-";
		std::cout << temp->_key << std::endl;
		display(temp->_right, level + 1);
	}
}
template<typename T>
void BST<T>::out()const
{
	display(_root, 0);
}

template<class T>
bool BST<T>::delete_value(Node<T>* parent, Node<T>* current,const T& val)
{
	if (!current) return false;
	if (current->_key == val)
	{
		if (current->_left == NULL || current->_right == NULL) {
			Node<T>* temp = current->_left;
			if (current->_right) temp = current->_right;
			if (parent) {
				if (parent->_left == current) {
					parent->_left = temp;
				}
				else {
					parent->_right = temp;
				}
			}
			else {
				this->_root = temp;
			}
		}
		else {
			Node<T>* validSubs = current->_right;
			while (validSubs->_left) {
				validSubs = validSubs->_left;
			}
			T temp = current->_key;
			current->_key = validSubs->_key;
			validSubs->_key = temp;
			return delete_value(current, current->_right, temp);
		}
		delete current;
		count--;
		return true;
	}
	if (current->_key > val)
		return delete_value(current, current->_left, val);
	else 
		return delete_value(current, current->_right, val);
}
template<class T>
bool BST<T>::delete_val(const T& value)
{
	return this->delete_value(NULL,_root, value);
}
