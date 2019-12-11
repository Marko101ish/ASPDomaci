//#include<iostream>
//class Node
//{
//public:
//	Node(int x = 0, int y = 0) : x_(x), y_(y) {}
//
//	friend std::ostream& operator<<(std::ostream&os, Node&myNode)
//	{
//		os << "Cvor: " << "(" << myNode.x_ << ", " << myNode.y_ << ")";
//		return os;
//	}
//
//	int x_, y_;
//};
//
//struct lstNode
//{
//	Node *myNode;
//	lstNode *next;
//};
//
//class List
//{
//public:
//	List()
//	{
//		head = last = nullptr;
//	}
//	List(const List&) = delete;
//	List(List&&) = delete;
//	List& operator = (const List &) = delete;
//	List& operator = (List &&) = delete;
//	~List()
//	{
//		while (head)
//		{
//			lstNode *old = head;
//			head = head->next;
//			delete old;
//		}
//	}
//
//	bool isInList(lstNode* newNode)
//	{
//		lstNode* pom = head;
//		while (pom)
//		{
//			if (pom->myNode == newNode->myNode)
//				return true;
//			pom = pom->next;
//		}
//		return false;
//	}
//
//	bool Dodaj(lstNode* newNode)
//	{
//		if (!isInList(newNode))
//		{
//			if (newNode)
//			{
//				if (!head)
//					head = newNode;
//				else
//					last->next = newNode;
//				last = newNode;
//				return true;
//			}
//		}
//		return false;
//	}
//	bool Izbaci(Node* outNode)
//	{
//		lstNode *pom = head;
//		lstNode *tek = nullptr;
//		while (pom)
//		{
//			if (pom->myNode == outNode)
//			{
//				if (pom == head)
//				{
//					head = head->next;
//				}
//				else
//				{
//					if (pom == last)
//						last = tek;
//					tek->next = pom->next;
//				}
//				pom->next = nullptr;
//				return true;
//			}
//			tek = pom;
//			pom = pom->next;
//		}
//		return false;
//	}
//	lstNode* GetHead()
//	{
//		return head;
//	}
//
//	friend std::ostream& operator<<(std::ostream& os, List& myList)
//	{
//		lstNode *pom = myList.head;
//		while (pom)
//		{
//			os << *(pom->myNode) << " ---> ";
//			pom = pom->next;
//		}
//		return os;
//	}
//
//private:
//	lstNode *head, *last;
//};
//struct Graph
//{
//	List **niz;
//	int size;
//};
//
//bool Povezi(Graph &myGraph, int ind1, int ind2)
//{
//	if (ind1 >= 0 && ind1 < myGraph.size && ind2 >= 0 && ind2 < myGraph.size && ind1 != ind2)
//	{
//		lstNode *tmp = new lstNode();
//		tmp->myNode = myGraph.niz[ind1]->GetHead()->myNode;
//		myGraph.niz[ind2]->Dodaj(tmp);
//		tmp = new lstNode();
//		tmp->myNode = myGraph.niz[ind2]->GetHead()->myNode;
//		myGraph.niz[ind1]->Dodaj(tmp);
//		return true;
//	}
//	else
//		return false;
//}
//
//
//bool DodajGranu(Graph &myGraph)
//{
//	int i = -1, j = -1;
//	std::cout << "Unesite indekse izmedju kojih dodajete granu: ";
//	std::cin >> i >> j;
//	if (Povezi(myGraph, i, j))
//	{
//		return true;
//	}
//	else
//		return false;
//}
//
//
//
//bool UkloniGranu(Graph &myGraph)
//{
//	int i = -1, j = -1;
//	std::cout << "Unesite indekse izmedju kojih uklanjate granu: ";
//	std::cin >> i >> j;
//	if (i >= 0 && i < myGraph.size && j >= 0 && j < myGraph.size && i != j)
//	{
//		myGraph.niz[i]->Izbaci(myGraph.niz[j]->GetHead()->myNode);
//		myGraph.niz[j]->Izbaci(myGraph.niz[i]->GetHead()->myNode);
//		return true;
//	}
//	else
//		return false;
//}
//void Ispis(Graph &myGraph)
//{
//	if (myGraph.size == 0)
//		std::cout << "Nema cvorova!\n";
//	else
//	{
//		for (int i = 0; i < myGraph.size; i++)
//		{
//			std::cout << "Indeks: " << i << ": " << *myGraph.niz[i] << std::endl;
//		}
//	}
//}
//
//void DodajCvor(Graph &myGraph)
//{
//	int x, y;
//	std::cout << "Unesite parametre x i y novog cvora: ";
//	std::cin >> x >> y;
//	myGraph.niz = (List**)realloc(myGraph.niz, (myGraph.size + 1) * sizeof(List*));
//	myGraph.niz[myGraph.size++] = new List();
//	lstNode *tmp = new lstNode();
//	tmp->myNode = new Node(x, y);
//	myGraph.niz[myGraph.size - 1]->Dodaj(tmp);
//}
//
//void IzbaciCvor(Graph &myGraph)
//{
//	int ind;
//	std::cout << "Unesite indeks cvora koji zelite da uklonite: ";
//	std::cin >> ind;
//	if (ind >= 0 && ind < myGraph.size)
//	{
//		Node *old = myGraph.niz[ind]->GetHead()->myNode;
//		for (int i = 0; i < myGraph.size; i++)
//		{
//			myGraph.niz[i]->Izbaci(old);
//			if ((i >= ind) && (i != myGraph.size - 1))
//			{
//				myGraph.niz[i] = myGraph.niz[i + 1];
//			}
//		}
//		delete(old);
//		if (myGraph.size-- != 1)
//		{
//			myGraph.niz = (List**)realloc(myGraph.niz, myGraph.size * sizeof(List*));
//		}
//	}
//}
//
//void BrisiGraf(Graph &myGraph)
//{
//	for (int i = 0; i < myGraph.size; i++)
//	{
//		delete myGraph.niz[i];
//	}
//	myGraph.size = 0;
//}
//void Init(Graph &myGraph)
//{
//	BrisiGraf(myGraph);
//	int n;
//	std::cout << "Unesite broj cvorova grafa:\n";
//	std::cin >> n;
//	if (!(n > 0))
//	{
//		std::cin.clear();
//		std::cin.ignore();
//		n = 1;
//	}
//	myGraph.size = n;
//	myGraph.niz = (List**)realloc(myGraph.niz, n * (sizeof(List*)));
//
//	for (int i = 0; i < n; i++)
//	{
//		myGraph.niz[i] = new List();
//		lstNode *tmp = new lstNode();
//		tmp->myNode = new Node(i%n, i%n - 1);
//		myGraph.niz[i]->Dodaj(tmp);
//	}
//}
//
//
//
//lstNode* GetNode(Graph &myGraph, Node * pom)
//{
//	for (int i = 0; i < myGraph.size; i++)
//		if (myGraph.niz[i]->GetHead()->myNode == pom)
//			return myGraph.niz[i]->GetHead();
//	return nullptr;
//}
//
//
//
//int main()
//{
//	Graph OurGraph;
//	OurGraph.size = 0;
//	OurGraph.niz = (List**)calloc(1, sizeof(List*));
//	int opcija = 0;
//	do
//	{
//		std::cout << "\n-------------\nUnesite odgovarajuci broj za izbor opcija:\n";
//		std::cout << "1) Inicijalizacija grafa\n";
//		std::cout << "2) Dodavanje novog cvora\n";
//		if (OurGraph.size > 0)
//		{
//			std::cout << "3) Uklanjanje cvora\n";
//			if (OurGraph.size > 1)
//			{
//				std::cout << "4) Dodavanje grane izmedju dva cvora\n";
//				std::cout << "5) Uklanjanje grane izmedju dva cvora\n";
//			}
//			std::cout << "6) Ispis grafa\n";
//			std::cout << "7) Brisanje grafa\n";
//		}
//
//		std::cout << "8) Prekid rada\n";
//		std::cin >> opcija;
//		std::cout << "\n---------------\n";
//		switch (opcija)
//		{
//		case 1:
//			Init(OurGraph);
//			break;
//		case 2:
//			if (OurGraph.size <= 0)
//			{	
//				OurGraph.size = 0;
//			}
//			DodajCvor(OurGraph);
//			break;
//		case 3:
//			if (OurGraph.size > 0)
//			{
//				IzbaciCvor(OurGraph);
//			}
//			break;
//		case 4:
//			if (OurGraph.size > 1)
//				DodajGranu(OurGraph);
//			break;
//		case 5:
//			if (OurGraph.size > 1)
//				UkloniGranu(OurGraph);
//			break;
//		case 6:
//			if (OurGraph.size > 1)
//				Ispis(OurGraph);
//			break;
//		case 7:
//			if (OurGraph.size > 0)
//				BrisiGraf(OurGraph);
//			break;
//		case 8:
//			BrisiGraf(OurGraph);
//			exit(0);
//		}
//	}
//	while (1);
//
//	system("pause");
//	return 0;
//}