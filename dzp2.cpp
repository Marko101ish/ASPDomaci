#include <iostream>
#include<string>


#pragma region Heder

enum Kategorija { POLJE, ULAZ, IZLAZ };

class Node
{
public:
	Node(int x = 0, int y = 0) : x_(x), y_(y) {}

	friend std::ostream& operator<<(std::ostream&os, Node&myNode)
	{
		os << "Cvor: " << "(" << myNode.x_ << ", " << myNode.y_ << ")";
		return os;
	}

	//Lavirint
	void SetKategorija(Kategorija newKat)
	{
		vrstaPolja_ = newKat;
	}
	Kategorija GetKategorija() const
	{
		return vrstaPolja_;
	}

	int x_, y_;
	bool posecen = false;
private:
	//Lavirint
	Kategorija vrstaPolja_ = POLJE;
};

struct lstNode
{
	Node *myNode;
	lstNode *next;
};

class List
{
public:
	List()
	{
		head = last = nullptr;
	}
	List(const List&) = delete;
	List(List&&) = delete;
	List& operator = (const List &) = delete;
	List& operator = (List &&) = delete;
	~List()
	{
		while (head)
		{
			lstNode *old = head;
			head = head->next;
			delete old;
		}
	}

	bool isInList(lstNode* newNode)
	{
		lstNode* pom = head;
		while (pom)
		{
			if (pom->myNode == newNode->myNode)
				return true;
			pom = pom->next;
		}
		return false;
	}




	//Lavirint
	bool isInList(int x, int y)
	{
		lstNode* pom = head;
		while (pom)
		{
			Node *tmp = pom->myNode;
			if (tmp->x_ == x && tmp->y_ == y)
				return true;
			pom = pom->next;
		}
		return false;
	}
	bool HasRight()
	{
		if (isInList(head->myNode->x_, head->myNode->y_ + 1))
			return true;
		return false;
	}
	bool HasDown()
	{
		if (isInList(head->myNode->x_ + 1, head->myNode->y_))
			return true;
		return false;
	}

	bool Dodaj(lstNode* newNode)
	{
		if (!isInList(newNode))
		{
			if (newNode)
			{
				if (!head)
					head = newNode;
				else
					last->next = newNode;
				last = newNode;
				return true;
			}
		}
		return false;
	}
	bool Izbaci(Node* outNode)
	{
		lstNode *pom = head;
		lstNode *tek = nullptr;
		while (pom)
		{
			if (pom->myNode == outNode)
			{
				if (pom == head)
				{
					head = head->next;
				}
				else
				{
					if (pom == last)
						last = tek;
					tek->next = pom->next;
				}
				pom->next = nullptr;
				return true;
			}
			tek = pom;
			pom = pom->next;
		}
		return false;
	}
	lstNode* GetHead()
	{
		return head;
	}

	friend std::ostream& operator<<(std::ostream& os, List& myList)
	{
		lstNode *pom = myList.head;
		while (pom)
		{
			os << *(pom->myNode) << " ---> ";
			pom = pom->next;
		}
		return os;
	}

	lstNode* Pop()
	{
		lstNode *pom = head;
		if (head != last)
		{
			lstNode *tek = head;
			while (pom != last)
			{
				tek = pom;
				pom = pom->next;
			}
			tek->next = nullptr;
			pom = last;
			last = tek;
		}
		else
		{
			pom = head;
			head = last = nullptr;
		}
		return pom;
	}

private:
	lstNode *head, *last;
};
struct Graph
{
	List **niz;
	int size, height, width, ulaz;
};

bool Povezi(Graph &myGraph, int ind1, int ind2)
{
	if (ind1 >= 0 && ind1 < myGraph.size && ind2 >= 0 && ind2 < myGraph.size && ind1 != ind2)
	{
		lstNode *tmp = new lstNode();
		tmp->myNode = myGraph.niz[ind1]->GetHead()->myNode;
		myGraph.niz[ind2]->Dodaj(tmp);
		tmp = new lstNode();
		tmp->myNode = myGraph.niz[ind2]->GetHead()->myNode;
		myGraph.niz[ind1]->Dodaj(tmp);
		return true;
	}
	else
		return false;
}

//Lavirint
bool DodajGranu(Graph &myGraph)
{
	int x1 = -1, y1 = -1;
	int x2 = -1, y2 = -1;
	int lstSize = myGraph.width * myGraph.height;
	int ind1, ind2;
	std::cout << "Unesite poziciju prvog cvora: ";
	std::cin >> x1 >> y1;
	std::cout << "Unesite poziciju drugog cvora: ";
	std::cin >> x2 >> y2;
	if (abs(x1 - x2) == 1 && abs(y1 - y2) == 0 || abs(x1 - x2) == 0 && abs(y1 - y2) == 1)
	{
		ind1 = x1 * myGraph.width + y1;
		ind2 = x2 * myGraph.width + y2;
		if (Povezi(myGraph, ind1, ind2))
		{
			return true;
		}
	}
	return false;

}


bool UkloniGranu(Graph &myGraph)
{
	int i = -1, j = -1;
	std::cout << "Unesite indekse izmedju kojih uklanjate granu: ";
	std::cin >> i >> j;
	if (i >= 0 && i < myGraph.size && j >= 0 && j < myGraph.size && i != j)
	{
		myGraph.niz[i]->Izbaci(myGraph.niz[j]->GetHead()->myNode);
		myGraph.niz[j]->Izbaci(myGraph.niz[i]->GetHead()->myNode);
		return true;
	}
	else
		return false;
}


void DodajCvor(Graph &myGraph)
{
	int x, y;
	std::cout << "Unesite parametre x i y novog cvora: ";
	std::cin >> x >> y;
	myGraph.niz = (List**)realloc(myGraph.niz, (myGraph.size + 1) * sizeof(List*));
	myGraph.niz[myGraph.size++] = new List();
	lstNode *tmp = new lstNode();
	tmp->myNode = new Node(x, y);
	myGraph.niz[myGraph.size - 1]->Dodaj(tmp);
}

void IzbaciCvor(Graph &myGraph)
{
	int ind;
	std::cout << "Unesite indeks cvora koji zelite da uklonite: ";
	std::cin >> ind;
	if (ind >= 0 && ind < myGraph.size)
	{
		Node *old = myGraph.niz[ind]->GetHead()->myNode;
		for (int i = 0; i < myGraph.size; i++)
		{
			myGraph.niz[i]->Izbaci(old);
			if ((i >= ind) && (i != myGraph.size - 1))
			{
				myGraph.niz[i] = myGraph.niz[i + 1];
			}
		}
		delete(old);
		if (myGraph.size-- != 1)
		{
			myGraph.niz = (List**)realloc(myGraph.niz, myGraph.size * sizeof(List*));
		}
	}
}

void BrisiGraf(Graph &myGraph)
{
	for (int i = 0; i < myGraph.size; i++)
	{
		delete myGraph.niz[i];
	}
	myGraph.size = 0;
}
void Init(Graph &myGraph)
{
	BrisiGraf(myGraph);
	int n;
	std::cout << "Unesite broj cvorova grafa:\n";
	std::cin >> n;
	if (!(n > 0))
	{
		std::cin.clear();
		std::cin.ignore();
		n = 1;
	}
	myGraph.size = n;
	myGraph.niz = (List**)realloc(myGraph.niz, n * (sizeof(List*)));

	for (int i = 0; i < n; i++)
	{
		myGraph.niz[i] = new List();
		lstNode *tmp = new lstNode();
		tmp->myNode = new Node(i%n, i%n - 1);
		myGraph.niz[i]->Dodaj(tmp);
	}
}



lstNode* GetNode(Graph &myGraph, Node * pom)
{
	for (int i = 0; i < myGraph.size; i++)
		if (myGraph.niz[i]->GetHead()->myNode == pom)
			return myGraph.niz[i]->GetHead();
	return nullptr;
}
bool CheckPosition(int x, int y, int width, int height)
{
	if ((x >= 0 && x < height) && (y >= 0 && y < width))
	{
		if (x == 0 || x == (height - 1) || y == 0 || y == (width - 1))
			return true;
	}
	return false;
}


void Init(Graph &myGraph, bool tekst = false)
{
	int ulazx, ulazy, izlazx, izlazy;
	do
	{
		std::cout << "Unesite dimenzije lavirinta: ";
		std::cin >> myGraph.width >> myGraph.height;
		std::cin.clear();
		std::cin.ignore();
	} while ((myGraph.width <= 0 || myGraph.height <= 0) || (myGraph.width > 80 || myGraph.height > 50) && tekst);

	do
	{
		std::cout << "Unesite poziciju ulaza: ";
		std::cin >> ulazx >> ulazy;
		std::cin.clear();
		std::cin.ignore();
	} while (!CheckPosition(ulazx, ulazy, myGraph.width, myGraph.height));
	myGraph.ulaz = ulazx * myGraph.width + ulazy;
	do
	{
		std::cout << "Unesite poziciju izlaza: ";
		std::cin >> izlazx >> izlazy;
		std::cin.clear();
		std::cin.ignore();
	} while ((!CheckPosition(izlazx, izlazy, myGraph.width, myGraph.height)) || (ulazx == izlazx && ulazy == izlazy));
	myGraph.size = myGraph.width * myGraph.height;
	myGraph.niz = (List**)realloc(myGraph.niz, (myGraph.size)* (sizeof(List*)));
	int ind = 0;
	for (int i = 0; i < myGraph.height; i++)
	{
		for (int j = 0; j < myGraph.width; j++)
		{
			myGraph.niz[ind] = new List();
			lstNode *tmp = new lstNode();
			tmp->myNode = new Node(i, j);
			if (i == ulazx && j == ulazy)
				tmp->myNode->SetKategorija(ULAZ);
			if (i == izlazx && j == izlazy)
				tmp->myNode->SetKategorija(IZLAZ);
			myGraph.niz[ind++]->Dodaj(tmp);
		}
	}
}


void DrawMaze(Graph &myGraph)
{
	if (myGraph.width != 0 && myGraph.height != 0)
	{
		Node *tmpNode;
		List *tmpList;
		std::string outWalls, outIL;
		int ind;
		for (int i = 0; i < myGraph.height; i++)
		{
			if (i == 0 || i == myGraph.height - 1)
			{
				outWalls += '#';
				outIL += '|';
			}
			else
			{
				ind = i * myGraph.width;
				tmpList = myGraph.niz[ind];
				tmpNode = tmpList->GetHead()->myNode;
				if (tmpNode->GetKategorija() != POLJE)
					outIL += ' ';
				else
					outIL += '|';
			}

			for (int j = 0; j < myGraph.width; j++)
			{
				tmpList = myGraph.niz[i*myGraph.width + j];
				tmpNode = tmpList->GetHead()->myNode;
				if (i == 0 || i == myGraph.height - 1)
				{
					if (tmpList->HasDown() || tmpNode->GetKategorija() != POLJE && i == myGraph.height - 1)
						outIL += ' ';
					else
						outIL += '_';

					if (tmpNode->GetKategorija() != POLJE)
					{
						outWalls += " #";
					}
					else
					{
						outWalls += "##";
					}
					if (tmpList->HasRight())
						outIL += ' ';
					else
						outIL += '|';
				}
				else
				{
					if (tmpList->HasDown())
						outIL += ' ';
					else
						outIL += '_';

					if (tmpList->HasRight() || (tmpNode->GetKategorija() != POLJE && j > 0))
						outIL += ' ';
					else
						outIL += '|';
				}

			}
			if (i == 0)
			{
				std::cout << outWalls << std::endl;
				std::cout << outIL << std::endl;
				outWalls = "";
			}
			else if (i == myGraph.height - 1)
			{
				std::cout << outIL << std::endl;
				std::cout << outWalls << std::endl;
				outWalls = "";
			}
			else
			{
				std::cout << outIL << std::endl;
			}
			outIL = "";
		}
	}
	else
		std::cout << "Ne postoji lavirint!\n";
}

bool Obidji(Graph &myGraph)
{
	if (myGraph.size > 0)
	{
		List Red;
		if (myGraph.ulaz >= 0 && myGraph.ulaz < myGraph.size)
		{
			for (int i = 0; i < myGraph.size; i++)
			{
				myGraph.niz[i]->GetHead()->myNode->posecen = false;
			}
			std::cout << "Ulaz: " << *(myGraph.niz[myGraph.ulaz]->GetHead()->myNode) << std::endl;
			myGraph.niz[myGraph.ulaz]->GetHead()->myNode->posecen = true;
			Red.Dodaj(myGraph.niz[myGraph.ulaz]->GetHead());
			while (Red.GetHead() != nullptr)
			{
				lstNode *pom = Red.Pop();
				lstNode *tmp = GetNode(myGraph, pom->myNode);
				while (tmp)
				{
					if (!tmp->myNode->posecen)
					{
						std::cout << *(tmp->myNode) << std::endl;
						if (tmp->myNode->GetKategorija() == IZLAZ)
							return true;
						tmp->myNode->posecen = true;
						Red.Dodaj(tmp);
					}
					tmp = tmp->next;
				}
			}
		}
	}
	return false;
}

#pragma endregion

int main()
{
	bool tekst = true;
	Graph Maze;
	int width, height, opcija, size, ulaz;
	Maze.niz = (List**)calloc(1, sizeof(List*));
	Init(Maze, tekst);
	do
	{
		std::cout << "\n-------------\nUnesite odgovarajuci broj za izbor opcija:\n";
		std::cout << "1) Inicijalizacija lavirinta\n";
		if (Maze.size != 0)
		{
			std::cout << "2) Dodavanje puta\n";
			std::cout << "3) Resavanje lavirinta\n";
			std::cout << "4) Brisanje lavirinta\n";
			std::cout << "5) Ispis lavirinta\n";
		}
		std::cout << "6) Prekid rada\n";
		std::cin >> opcija;
		std::cout << "\n---------------\n";
		switch (opcija)
		{
		case 1:
			Init(Maze, tekst);
			break;
		if (size != 0)
		{
			case 2:
				while (DodajGranu(Maze))
				{
					DrawMaze(Maze);
				}
				break;
			case 3:
				Obidji(Maze);
				break;
			case 4:
				BrisiGraf(Maze);
				break;
			case 5:
				DrawMaze(Maze);
				break;
		}
		case 6:
			BrisiGraf(Maze);
			exit(0);
		}
	}
	while (1);
	system("pause");
	return 0;
}