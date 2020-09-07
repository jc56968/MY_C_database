#pragma once
#include<iostream>
#include<list>
#include<map>
#include<deque>
#include<math.h>
#include<stack>
#include<vector>


using namespace std;



template <class data, class value>
class BNode
{
	friend  class table<data, value>;
	friend   class SloT<data, value>;
	friend  class Bplusetree<data, value>;
public:
	bool merge_bro_bpluse(BNode<data, value>* p, bool left);
	bool merge_fa_bpluse();
	bool merge_bro(BNode<data, value>* p, bool left);
	bool merge_fa();
	BNode(int Node_size = 5, bool is = 0);
	BNode(BNode& A);
	BNode& operator=(BNode& A);
	int get_insert_index(value v);
	bool add_node(data d, value v);
	bool add_slot_node(value v, BNode* p, BNode* q);
	~BNode();
	BNode* divide();
private:
	data** D;
	value* V;
	BNode** Slot;
	int index;
	int Node_size;
	BNode* father;
	bool isBpluse;
	BNode* fro;
	BNode* beh;
};

template <class data, class value>
class Bplusetree
{

	friend class table<data,value>;

	friend  class SloT<data,value>;

	friend  class BNode<data,value>;
	// friend   table:: add_clust_slot(int );
public:
	Bplusetree(int Node_size);
	~Bplusetree();
	Bplusetree(Bplusetree& T);
	data* get_data(BNode<data, value>* p, int ind);
	data* get_data(value v);
	pair<BNode<data, value>*, int> find(value v);
	bool add(data d, value v);
	vector<data*>  visit();
	void pprint();
	bool alter(data d, value v);
	bool del(value v);
private:
	int Node_size;
	BNode<data, value>* root;
	BNode<data, value>* fro;

	BNode<data, value>* beh;



};



template <class data, class value>
bool BNode<data, value>::merge_bro(BNode<data, value>* p, bool left)
{
	if (left)
	{

		p->index--;

		D[index] = p->D[p->index];
		V[index] = p->V[p->index];

		p->D[p->index] = 0;
		p->V[p->index] = 0;
		for (int i = 0; i < index; i++)
		{
			swap(D[i], D[i + 1]);
			swap(V[i], V[i + 1]);
		}
		for (int i = 0; i <= p->father->index; i++)
			if (p->father->Slot[i] == p)
			{
				p->father->V[i] = V[0];
				break;
			}

		index++;



	}
	else
	{
		p->index--;
		D[index] = p->D[0];
		V[index] = p->V[0];

		p->D[0] = 0;
		p->V[0] = 0;
		for (int i = 0; i < p->index; i++)
		{
			swap(p->D[i], p->D[i + 1]);
			swap(p->V[i], p->V[i + 1]);
		}
		for (int i = 0; i < p->father->index; i++)
			if (p->father && p->father->Slot[i] == this)
			{
				p->father->V[i] = p->V[0];
			}
		index++;
	}
	return 1;
}

template <class data, class value>
bool BNode<data, value>::merge_bro_bpluse(BNode<data, value> * p, bool left)
{
	if (left)
	{
		for (int i = 0; i <= father->index; i++)
			if (father->Slot[i] == p)
			{
				V[index] = father->V[i];
				Slot[index + 1] = p->Slot[p->index];
				int i;
				for (i = index; i > 0; i--)
				{
					swap(Slot[i + 1], Slot[i]);
					swap(V[i], V[i - 1]);
				}
				swap(Slot[i], Slot[i + 1]);
				index++;


				father->V[i] = p->V[p->index - 1];
				p->V[p->index - 1] = 0;
				p->Slot[p->index] = 0;
				p->index--;
				break;
			}

	}
	else
	{
		for (int j = 0; j <= father->index; j++)
			if (father->Slot[j] == this)
			{
				V[index] = father->V[j];
				Slot[index + 1] = p->Slot[0];

				father->V[j] = p->V[0];
				p->V[0] = 0;
				p->Slot[0] = 0;
				int i;
				p->index--;
				for (i = 0; i < p->index; i++)
				{
					swap(p->Slot[i], p->Slot[i + 1]);
					swap(p->V[i], p->V[i + 1]);
				}
				swap(p->Slot[i], p->Slot[i + 1]);
				index++;




			}
	}
	return 0;
}
template <class data, class value>
bool BNode<data, value>::merge_fa_bpluse()
{
	if (fro && fro->father == father)
	{
		for (int i = 0; i <= father->index; i++)
			if (father->Slot[i] == fro)
			{
				fro->V[fro->index] = father->V[i];
				father->V[i] = 0;

				father->Slot[i + 1] = 0;
				int j;
				for (j = i; j < father->index; j++)
				{
					swap(V[j], V[j + 1]);
					swap(Slot[j + 1], Slot[j + 2]);
				}
				father->index--;
				fro->index++;
				int ind = fro->index;
				int x;
				for (x = ind; x < x - ind + this->index; x++)
				{
					fro->V[x] = V[x - ind];
					fro->Slot[x] = Slot[x - ind];
					fro->index++;

				}
				fro->Slot[x] = Slot[x - ind];

				if (father->father == 0 && father->index == 0)
				{

					delete father;
					father = fro;
					fro->father = 0;
				}
				else if (father)
				{
					BNode<data, value>* p = father;
					if (father->index < ceil(Node_size + 1) / 2 - 1)
					{

						if (p->fro != 0 && p->father == p->fro->father && p->fro->index > ceil(Node_size + 1) / 2 - 1)
							father->merge_bro_bpluse(p->fro, 1);
						else if (p->beh != 0 && p->father == p->beh->father && p->beh->index > ceil(Node_size + 1) / 2 - 1)
							father->merge_bro_bpluse(p->beh, 0);
						else
							father->merge_fa_bpluse();
					}
				}
				fro->beh = beh;
				if (beh)
					beh->fro = fro;
				delete this;
			}
	}
	else if (beh && beh->father == father)
	{


		for (int i = 0; i <= father->index; i++)
			if (father->Slot[i] == this)
			{
				V[index] = father->V[i];
				father->V[i] = 0;

				father->Slot[i + 1] = 0;

				int j;
				for (j = i; j < father->index; j++)
				{
					swap(father->V[j], father->V[j + 1]);
					swap(father->Slot[j + 1], father->Slot[j + 2]);
				}
				father->index--;
				index++;
				int ind = index;
				int x;
				for (x = ind; x < ind + beh->index; x++)
				{
					V[x] = beh->V[x - ind];
					Slot[x] = beh->Slot[x - ind];
					index++;

				}
				Slot[x] = beh->Slot[x - ind];


				if (father != 0)
				{
					BNode<data, value>* p = father;
					if (father->index < ceil(Node_size + 1) / 2 - 1)
					{
						if (father->father == 0 && father->index == 0)
						{




							if (this->beh)
								this->beh->fro = this;
							if (this->fro)
								this->fro->beh = this;
							this->fro = father->fro;
							this->beh = father->beh;

							father->BNode::BNode(*this);
							father->father = 0;
							delete this;
							return 0;


						}
						else if (p->fro != 0 && p->father == p->fro->father && p->fro->index > ceil(Node_size + 1) / 2 - 1)
							father->merge_bro_bpluse(p->fro, 1);
						else if (p->beh != 0 && p->father == p->beh->father && p->beh->index > ceil(Node_size + 1) / 2 - 1)
							father->merge_bro_bpluse(p->beh, 0);
						else
							father->merge_fa_bpluse();
					}
				}

				if (beh->beh)
				{
					beh->beh->fro = this;
					beh = beh->beh;
				}
				else
					beh = beh->beh;
				delete beh;
			}



	}
	return 0;
}

template <class data, class value>
bool BNode<data, value>::merge_fa()
{
	if (fro->father == father)
	{
		int i = 0;
		while (i != index)
		{
			swap(fro->V[fro->index], V[i]);
			swap(fro->D[fro->index], D[i]);
			i++;
		}
		for (int i = 0; i < father->index; i++)
		{
			if (father->Slot[i] == fro)
			{
				father->V[i] = 0;
				father->Slot[i + 1] = 0;
				while (i + 1 != father->index)
				{
					swap(father->V[i], father->V[i + 1]);
					swap(father->Slot[i + 1], father->Slot[i + 2]);
					i++;
				}
			}
		}
		fro->beh = beh;
		if (beh)
			beh->fro = fro;
		fro->index++;
		father->index--;


	}
	else
	{
		if (beh->father != father)
			cout << "cerr";
		else
		{
			for (int i = 0; i < beh->index; i++)
			{
				swap(beh->V[i], beh->V[i + index]);
				swap(beh->D[i], beh->D[i + index]);

			}
			for (int i = 0; i < index; i++)
			{
				swap(V[i], beh->V[i]);
				swap(D[i], beh->D[i]);
			}

			for (int i = 0; i < father->index; i++)
			{
				if (father->Slot[i] == this)
				{
					father->V[i] = 0;
					father->Slot[i] = 0;
					while (i + 1 != father->index)
					{
						swap(father->V[i], father->V[i + 1]);
						swap(father->Slot[i], father->Slot[i + 1]);
						i++;
					}
				}
			}
			fro->beh = beh;
			beh->fro = fro;
			father->index--;
			beh->index++;



		}
	}

	BNode<data, value>* p = father;
	if (father->index < ceil(Node_size + 1) / 2 - 1)
	{

		if (p->fro != 0 && p->father == p->fro->father && p->fro->index > ceil(Node_size + 1) / 2 - 1)
			father->merge_bro_bpluse(p->fro, 1);
		else if (p->beh != 0 && p->father == p->beh->father && p->beh->index > ceil(Node_size + 1) / 2 - 1)
			father->merge_bro_bpluse(p->beh, 0);
		else
			father->merge_fa_bpluse();
	}
	if (this->fro)
		this->fro->beh = beh;
	if (this->beh)
		this->beh->fro = fro;

	delete this;
	return 1;
}
template <typename data, typename value>
BNode<data, value>::BNode(int Node_size, bool is) :Node_size(Node_size), isBpluse(is)
{
	if (isBpluse)
	{
		Slot = new BNode * [Node_size + 1];
		D = 0;
	}
	else {
		Slot = 0;
		D = new data * [Node_size];
	}
	V = new value[Node_size];
	father = 0;
	fro = 0;
	beh = 0;
	index = 0;
}

template <class data, class value>
BNode<data, value>::BNode(BNode & A)
{
	BNode* p = new BNode(A.Node_size, A.isBpluse);
	father = A.father;
	fro = A.fro;
	beh = A.beh;
	index = A.index;
	if (isBpluse)
	{
		int i;
		for (i = 0; i < A.index; i++)
			Slot[i] = A.Slot[i];
		Slot[i] = A.Slot[i];
	}
	else
	{
		for (int i = 0; i < A.index; i++)
			D[i] = A.D[i];
	}
	for (int i = 0; i < A.index; i++)
		V[i] = A.V[i];


}
template <class data, class value>
BNode<data, value>& BNode<data, value>::operator=(BNode & A)
{
	cout << "no copy operator" << endl;
}
template <class data, class value>
int BNode<data, value>::get_insert_index(value v)
{
	int i = 0;
	for (i = 0; i < index; i++)
	{
		if (v < V[i])
		{
			for (int j = index; j > i; j--)
			{
				if (isBpluse)
					swap(Slot[j], Slot[j + 1]);
				else
					swap(D[j], D[j - 1]);
				swap(V[j], V[j - 1]);
			}
			return i;
		}
	}
	return i;
}
template <class data, class value>
bool BNode<data, value>::add_node(data d, value v)
{
	if (index < Node_size)
	{
		D[index] = new data;
		int n = get_insert_index(v);

		*D[n] = d;
		V[n] = v;
		++index;
		if (index == Node_size)
			divide();
		return 1;
	}
	else
		return 0;

}

template <class data, class value>
bool BNode<data, value>::add_slot_node(value v, BNode * p, BNode * q)
{

	if (index < Node_size)
	{

		int n = get_insert_index(v);

		Slot[n] = p;
		Slot[n + 1] = q;
		V[n] = v;
		++index;
		if (index == Node_size)
			divide();
		return 1;
	}
	else
	{
		return 0;
	}
}
template <class data, class value>
BNode<data, value>::~BNode()
{
	if (!isBpluse)
	{
		for (int i = 0; i < index; i++)
		{
			delete D[i];
			D[i] = 0;
		}
	}
	if (int(D) != 0xdddddddd)
		delete[]D;
	if (int(D) != 0xdddddddd)
		delete[]V;
	if (int(D) != 0xdddddddd)
		delete[]Slot;
	D = 0;
	V = 0;
	Slot = 0;
	father = 0;
	fro = 0;
	beh = 0;

}
template <class data, class value>
BNode<data, value> * BNode<data, value>::divide()
{
	if (father == 0)
	{
		BNode* p1;
		BNode* p2;
		int mid = Node_size / 2;
		if (isBpluse == 1)
		{
			p1 = new BNode(Node_size, 1);
			p2 = new BNode(Node_size, 1);


			int i;

			for (i = 0; i < mid; i++)
			{
				p1->add_slot_node(V[i], Slot[i], Slot[i + 1]);
				Slot[i]->father = p1;

			}
			Slot[i]->father = p1;
			for (i = mid + 1; i < index; i++)
			{
				p2->add_slot_node(V[i], Slot[i], Slot[i + 1]);
				Slot[i]->father = p2;
			}
			Slot[i]->father = p2;
			if (this->fro)
				this->fro->beh = p1;
			p1->fro = this->fro;
			p1->beh = p2;
			p2->fro = p1;
			p2->beh = this->beh;
			if (this->beh)
				this->beh->fro = p2;

		}
		else
		{
			p1 = new BNode(Node_size);
			p2 = new BNode(Node_size);
			int mid = Node_size / 2;
			for (int i = 0; i < mid; i++)
			{
				p1->add_node(*D[i], V[i]);
			}
			for (int i = mid; i < index; i++)
			{
				p2->add_node(*D[i], V[i]);
			}
			if (this->fro)
				this->fro->beh = p1;
			p1->fro = this->fro;
			p1->beh = p2;
			p2->fro = p1;
			p2->beh = this->beh;
			if (this->beh)
				this->beh->fro = p2;
		}
		int aim = V[mid];
		p1->father = this;
		p2->father = this;
		this->BNode::BNode(Node_size, 1);
		this->add_slot_node(aim, p1, p2);




		return this;

	}
	else
	{
		BNode* p1;
		BNode* p2;
		BNode* p3 = father;
		int mid = Node_size / 2;
		if (isBpluse == 1)
		{
			p1 = new BNode(Node_size, 1);
			p2 = new BNode(Node_size, 1);
			int i;
			for (i = 0; i < mid; i++)
			{
				p1->add_slot_node(V[i], Slot[i], Slot[i + 1]);
				Slot[i]->father = p1;

			}
			Slot[i]->father = p1;
			for (i = mid + 1; i < index; i++)
			{
				p2->add_slot_node(V[i], Slot[i], Slot[i + 1]);
				Slot[i]->father = p2;
			}
			Slot[i]->father = p2;
			if (this->fro)
				this->fro->beh = p1;
			p1->fro = this->fro;
			p1->beh = p2;
			p2->fro = p1;
			p2->beh = this->beh;
			if (this->beh)
				this->beh->fro = p2;

		}
		else
		{
			p1 = new BNode(Node_size);
			p2 = new BNode(Node_size);
			int mid = Node_size / 2;
			for (int i = 0; i < mid; i++)
			{
				p1->add_node(*D[i], V[i]);
			}
			for (int i = mid; i < index; i++)
			{
				p2->add_node(*D[i], V[i]);
			}
			if (this->fro)
				this->fro->beh = p1;
			p1->fro = this->fro;
			p1->beh = p2;
			p2->fro = p1;
			p2->beh = this->beh;
			if (this->beh)
				this->beh->fro = p2;
		}
		p1->father = p3;
		p2->father = p3;

		p3->add_slot_node(V[mid], p1, p2);

		delete this;




		return this;
	}

}




template <class data, class value>
Bplusetree<data, value>::Bplusetree(int Node_size) :Node_size(Node_size)
{
	root = new BNode<data, value>(Node_size);

	fro = new BNode<data, value>(Node_size);
	beh = new BNode<data, value>(Node_size);

}
template <class data, class value>
Bplusetree<data, value>::~Bplusetree()
{
	stack<BNode<data, value>*> kill;
	deque<BNode<data, value>*> r;
	deque<BNode<data, value>*> r2;
	BNode<data, value>* p;
	p = root;
	r.push_back(p);
	while (!r.empty())
	{

		while (!r.empty())
		{

			p = r.front();
			if (p == NULL)
			{
				int SS;
			}
			r.pop_front();
			if (p)
			{
				kill.push(p);

			}
			else
			{

				exit(-5);
			}


			if (p->isBpluse == 1)
			{
				for (int i = 0; i <= p->index; i++)
					r2.push_back(p->Slot[i]);
			}
		}
		swap(r, r2);

		cout << endl;
	}
	while (!kill.empty())
	{
		delete kill.top();
		kill.top() = 0;
		kill.pop();
	}



	delete fro;
	delete beh;


	root = 0;
	fro = 0;
	beh = 0;
}
template <class data, class value>
Bplusetree<data, value>::Bplusetree(Bplusetree & T)
{
	cout << "no constrcu please use smart pointer";

}
template <class data, class value>
data* Bplusetree<data, value>::get_data(BNode<data, value> * p, int ind)
{
	return p->D[ind];
}
template <class data, class value>
data* Bplusetree<data, value>::get_data(value v)
{
	auto t = find(v);
	if (t.first)
		return get_data(t.first, t.second);
	else
		return 0;
}
template <class data, class value>
pair<BNode<data, value>*, int>  Bplusetree<data, value>::find(value v)
{
	BNode<data, value>* p;
	p = root;
	int i;
	while (1)
	{
		for (i = 0; i < p->index; i++)
		{
			if (v < p->V[i])
			{
				if (p->isBpluse && p->Slot[i] != 0)
				{
					p = p->Slot[i];
					i = -1;

				}
				else
				{
					for (int j = 0; j < p->index; j++)
						if (p->V[j] == v)
							return  pair<BNode<data, value>*, int>(p, j);
					return  pair<BNode<data, value>*, int>(0, 0);

				}
			}
		}

		if (i == p->index)
		{
			if (p->isBpluse && p->Slot[i] != 0)
			{
				p = p->Slot[i];
				i = -1;

			}
			else
			{

				for (int j = 0; j < p->index; j++)
					if (p->V[j] == v)
						return  pair<BNode<data, value>*, int>(p, j);
				return  pair<BNode<data, value>*, int>(0, 0);
			}
		}
	}
	return pair<BNode<data, value>*, int>(0, 0);
}
template <class data, class value>
bool  Bplusetree<data, value>::add(data d, value v)
{
	BNode<data, value>* p;
	p = root;
	int i;
	while (1)
	{
		for (i = 0; i < p->index; i++)
		{
			if (v < p->V[i])
			{
				if (p->isBpluse && p->Slot[i] != 0)
				{
					p = p->Slot[i];
					i = -1;

				}
				else
				{
					p->add_node(d, v);
					return 1;
				}
			}
		}

		if (i == p->index)
		{
			if (p->isBpluse && p->Slot[i] != 0)
			{
				p = p->Slot[i];
				i = -1;

			}
			else
			{

				p->add_node(d, v);
				return 1;
			}
		}
	}
	return 0;
}
template <class data, class value>
vector<data*> Bplusetree<data, value>::visit()
{
	vector<data*> out;
	BNode<data, value>* p = root;
	while (p)
	{
		if (p->isBpluse)
		{
			p = p->Slot[0];
		}
		else
		{
			while (p != 0)
			{
				for (int i = 0; i < p->index; i++)
				{
					cout << p->V[i] << " ";
					out.push_back(p->D[i]);
				}					p = p->beh;
			}

		}
	}
	cout << endl;
	return out;
}

template <class data, class value>
void  Bplusetree<data, value>::pprint()
{
	deque<BNode<data, value>*> r;
	deque<BNode<data, value>*> r2;
	BNode<data, value>* p;
	p = root;
	r.push_back(p);
	while (!r.empty())
	{

		while (!r.empty())
		{

			p = r.front();
			if (p == NULL)
			{
				int SS;
			}
			r.pop_front();
			if (p)
			{
				for (int i = 0; i < p->index; i++)
				{

					cout << p->V[i] << " ";

				}
				cout << " ";
			}
			else
			{
				cout << "line 757 p=nullptr";
				exit(-1);
			}


			if (p->isBpluse == 1)
			{
				for (int i = 0; i <= p->index; i++)
					r2.push_back(p->Slot[i]);
			}
		}
		swap(r, r2);

		cout << endl;
	}
}

template <class data, class value>
bool  Bplusetree<data, value>::alter(data d, value v)
{
	data* c = get_data(v);
	if (c != 0)
	{
		*c = d;
		return 1;
	}
	else

		return 0;

}
template <class data, class value>
bool  Bplusetree<data, value>::del(value v)
{
	pair<BNode<data, value>*, int> t = find(v);
	BNode<data, value>* p = t.first;

	value ind = t.second;
	if (p)
	{

		p->V[ind] = 0;

		delete(p->D[ind]);
		p->D[ind] = 0;
		for (int j = ind + 1; j < p->index; j++)
		{
			swap(p->D[j - 1], p->D[j]);
			swap(p->V[j - 1], p->V[j]);
		}
		p->index--;
		if (p->index < ceil(Node_size + 1) / 2 - 1)
		{
			if (p->father != 0)
			{
				if ((p->fro != 0 && p->father == p->fro->father && p->fro->index > ceil(Node_size + 1) / 2 - 1))

					p->merge_bro(p->fro, 1);
				else if (((p->beh != 0 && p->father == p->beh->father && p->beh->index > ceil(Node_size + 1) / 2 - 1)))
					p->merge_bro(p->beh, 0);
				else
					p->merge_fa();
			}

		}


		return 1;
	}
	else
		return 0;
}

