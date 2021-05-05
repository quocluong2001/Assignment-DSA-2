#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif


//your code should be after that directive

void print2DUtil(KnightTree* root, int space)
{
	// Base case 
	if (root == NULL)
		return;

	// Increase distance between levels 
	space += 10;

	// Process right child first 
	print2DUtil(root->pRightChild, space);

	// Print current node after space 
	// count 
	cout << endl;
	for (int i = 10; i < space; i++)
		cout << " ";
	cout << root->key << "_" << root->level << "\n";

	// Process left child 
	print2DUtil(root->pLeftChild, space);
}

void print2D(KnightTree* root)
{
	// Pass initial space count as 0 
	print2DUtil(root, 0);
}

void printList(ringsignList* pList)
{
	cout << "Saruman's ringsign list: ";
	if (pList == NULL) cout << "NULL";
	while (pList != NULL)
	{
		cout << pList->nRingsign;
		if (pList->pNext == NULL) cout << "";
		else cout << " -> ";
		pList = pList->pNext;
	}
	cout << "\n";
}

//Use for converting from bst to array
struct KnightInfo
{
	int key;
	int level;
};

int CountRingsign(ringsignList* pSarumanList)
{
	if (pSarumanList == NULL) return 0;

	int result = 0;
	while (pSarumanList != NULL)
	{
		++result;
		pSarumanList = pSarumanList->pNext;
	}
	
	return result;
}

void SortRingsignList(ringsignList*& pSarumanList)
{
	if (pSarumanList == NULL) return;

	int size = CountRingsign(pSarumanList);
	ringsignList* current = pSarumanList;
	for (int i = 0; i < size; ++i)
	{
		ringsignList* nextRingsign = current->pNext;
		if (nextRingsign == NULL) break;
		for (int j = i + 1; j < size; ++j)
		{
			if (current->nRingsign > nextRingsign->nRingsign) 
				swap(current->nRingsign, nextRingsign->nRingsign);
			nextRingsign = nextRingsign->pNext;
		}
		current = current->pNext;
	}
}

//////////////////////////////////////// TREE FUNCTIONS ////////////////////////////////

int getHeight(KnightTree* root)
{
	if (root == NULL)
		return 0;
	return 1 + max(getHeight(root->pLeftChild), getHeight(root->pRightChild));
}

int getBalance(KnightTree* root)
{
	if (root == NULL)
		return 0;
	return (getHeight(root->pLeftChild) - getHeight(root->pRightChild));
}

KnightTree* rotateLeft(KnightTree*& root)
{
	KnightTree* tmp = root->pRightChild;
	KnightTree* T = tmp->pLeftChild;

	root->pRightChild = T;
	tmp->pLeftChild = root;

	root->balance = getBalance(root);
	tmp->balance = getBalance(tmp);

	root = tmp;
	return root;
}

KnightTree* rotateRight(KnightTree*& root)
{
	KnightTree* tmp = root->pLeftChild;
	KnightTree* T = tmp->pRightChild;

	root->pLeftChild = T;
	tmp->pRightChild = root;

	root->balance = getBalance(root);
	tmp->balance = getBalance(tmp);

	root = tmp;
	return root;
}

KnightTree* CreateNode(int key, int level)
{
	KnightTree* Node = new KnightTree;
	Node->key = key;
	Node->level = level;
	Node->balance = 0;
	Node->pLeftChild = NULL;
	Node->pRightChild = NULL;
	return Node;
}

KnightTree* InsertBST(KnightTree*& root, int key, int level)
{
	if (root == NULL)
		return CreateNode(key, level);

	if (key < root->key)
		root->pLeftChild = InsertBST(root->pLeftChild, key, level);
	else if (key > root->key)
		root->pRightChild = InsertBST(root->pRightChild, key, level);

	return root;
}

KnightTree* InsertAVL(KnightTree*& root, int key, int level)
{
	if (root == NULL)
		return CreateNode(key, level);

	if (key < root->key)
		root->pLeftChild = InsertAVL(root->pLeftChild, key, level);
	else if (key > root->key)
		root->pRightChild = InsertAVL(root->pRightChild, key, level);
	else
		return root;

	root->balance = getBalance(root);

	if (root->balance > 1 && key < root->pLeftChild->key)
		return rotateRight(root);

	if (root->balance < -1 && key > root->pRightChild->key)
		return rotateLeft(root);

	if (root->balance > 1 && key > root->pLeftChild->key)
	{
		root->pLeftChild = rotateLeft(root->pLeftChild);
		return rotateRight(root);
	}

	if (root->balance < -1 && key < root->pRightChild->key)
	{
		root->pRightChild = rotateRight(root->pRightChild);
		return rotateLeft(root);
	}

	return root;
}

//Find inorder successor
KnightTree* MinvalueNode(KnightTree* root)
{
	if (root == NULL)
		return root;
	KnightTree* current = root;
	while (current->pLeftChild != NULL)
		current = current->pLeftChild;
	return current;
}

//Find inorder predecessor
KnightTree* MaxvalueNode(KnightTree* root)
{
	if (root == NULL)
		return root;
	KnightTree* current = root;
	while (current->pRightChild != NULL)
		current = current->pRightChild;
	return current;
}

KnightTree* DeleteBST(KnightTree*& root, int key)
{
	if (root == NULL)
		return root;

	if (key < root->key)
		root->pLeftChild = DeleteBST(root->pLeftChild, key);
	else if (key > root->key)
		root->pRightChild = DeleteBST(root->pRightChild, key);
	else
	{
		KnightTree* tmp;
		if ((root->pLeftChild == NULL) || (root->pRightChild) == NULL)
		{
			if (root->pLeftChild != NULL) tmp = root->pLeftChild;
			else tmp = root->pRightChild;
			if (tmp == NULL)
			{
				tmp = root;
				root = NULL;
			}
			else *root = *tmp;
			delete tmp;
		}
		else
		{
			tmp = MinvalueNode(root->pRightChild);
			root->key = tmp->key;
			root->level = tmp->level;

			root->pRightChild = DeleteBST(root->pRightChild, tmp->key);
		}
	}
	return root;
}

KnightTree* DeleteAVL(KnightTree*& root, int key)
{
	if (root == NULL)
		return root;

	if (key < root->key)
		root->pLeftChild = DeleteBST(root->pLeftChild, key);
	else if (key > root->key)
		root->pRightChild = DeleteBST(root->pRightChild, key);
	else
	{
		KnightTree* tmp;
		if ((root->pLeftChild == NULL) || (root->pRightChild) == NULL)
		{
			if (root->pLeftChild != NULL) tmp = root->pLeftChild;
			else tmp = root->pRightChild;
			if (tmp == NULL)
			{
				tmp = root;
				root = NULL;
			}
			else *root = *tmp;
			delete tmp;
		}
		else
		{
			tmp = MinvalueNode(root->pRightChild);
			root->key = tmp->key;
			root->level = tmp->level;

			root->pRightChild = DeleteBST(root->pRightChild, tmp->key);
		}
	}

	if (root == NULL)
		return root;

	if (root->balance > 1 && key < root->pLeftChild->key)
		return rotateRight(root);

	if (root->balance < -1 && key > root->pRightChild->key)
		return rotateLeft(root);

	if (root->balance > 1 && key > root->pLeftChild->key)
	{
		root->pLeftChild = rotateLeft(root->pLeftChild);
		return rotateRight(root);
	}

	if (root->balance < -1 && key < root->pRightChild->key)
	{
		root->pRightChild = rotateRight(root->pRightChild);
		return rotateLeft(root);
	}

	return root;
}

bool IsEmpty(KnightTree* root)
{
	if (root == NULL) return true;
	return false;
}

bool Contain(KnightTree* root, int key)
{
	KnightTree* current = root;
	while (current != NULL)
	{
		if (key < current->key) current = current->pLeftChild;
		else if (key > current->key) current = current->pRightChild;
		else return true;
	}
	return false;
}

//Delete all nodes
void DeleteAll(KnightTree*& root)
{
	if (root == NULL) return;
	DeleteAll(root->pLeftChild);
	DeleteAll(root->pRightChild);
	delete root;
}

//Delete all nodes and set root = NULL
KnightTree* DeleteTree(KnightTree*& pTree)
{
	DeleteAll(pTree);
	pTree = NULL;
	return pTree;
}

int CountLeafNodes(KnightTree* pTree)
{
	if (pTree == NULL) return 0;
	if (pTree->pLeftChild == NULL && pTree->pRightChild == NULL) return 1;
	else return (CountLeafNodes(pTree->pLeftChild) + CountLeafNodes(pTree->pRightChild));
}

int GetDepthofNodeUntil(KnightTree* pTree, int key, int level)
{
	if (pTree == NULL) return 0;

	if (pTree->key == key) return level;

	int downlevel = GetDepthofNodeUntil(pTree->pLeftChild, key, level + 1);
	if (downlevel != 0) return downlevel;
	downlevel = GetDepthofNodeUntil(pTree->pRightChild, key, level + 1);
	return downlevel;
}

//Get level of node
int GetDepthofNode(KnightTree* pTree, int key)
{
	return GetDepthofNodeUntil(pTree, key, 1);
}

//Count full nodes
int CountfullNodes(KnightTree* pTree)
{
	if (pTree == NULL) return 0;
	return 1 + CountfullNodes(pTree->pLeftChild) + CountfullNodes(pTree->pRightChild);
}

bool CheckCompleteTree(KnightTree* pTree)
{
	int n = CountfullNodes(pTree);
	int h = getHeight(pTree);
	if (n == (pow(2, h) - 1)) return true;
	return false;
}

///////////////////////////////////////// EVENT IMPLEMENTATION ///////////////////////////////////

//////////////////////////////////////// Utility functions ///////////////////////////////////////

//Use for selecting which type of tree to work on
string formation(bool BST, bool AVL)
{
	if (BST) return "BST";
	return "AVL";
}

//Change to BST formation
void changetoBST(bool& BST, bool& AVL)
{
	BST = true;
	AVL = false;
}

//Change to AVL formation
void changetoAVL(bool& BST, bool& AVL)
{
	BST = false;
	AVL = true;
}

int countNumberofDigits(int eventCode)
{
	int result = 0;
	while (eventCode != 0)
	{
		eventCode /= 10;
		++result;
	}
	return result;
}

KnightTree* FindClosestKnight(KnightTree* pTree, int key)
{
	KnightTree* current = pTree;
	KnightTree* result = current;
	int minDiff = abs(current->key - key);
	while (current != NULL)
	{
		int currentDiff = abs(current->key - key);
		if (currentDiff < minDiff ||
			(currentDiff == minDiff && current->key < result->key))
		{
			minDiff = currentDiff;
			result = current;
		}
		if (key > current->key) current = current->pRightChild;
		else if (key < current->key) current = current->pLeftChild;
		else
		{
			if (current->key < result->key)
				result = current;
			return result;
		}
	}
	return result;
}

//Change current tree to array
int BSTtoArray(KnightTree* pTree, KnightInfo knights[], int i)
{
	if (pTree == NULL) return i;

	i = BSTtoArray(pTree->pLeftChild, knights, i);
	knights[i].key = pTree->key;
	knights[i].level = pTree->level;
	++i;
	i = BSTtoArray(pTree->pRightChild, knights, i);

	return i;
}

void InsertPreorder(KnightTree* pTree, KnightTree*& newTree)
{
	if (pTree == NULL) return;
	newTree = InsertBST(newTree, pTree->key, pTree->level);
	InsertPreorder(pTree->pLeftChild, newTree);
	InsertPreorder(pTree->pRightChild, newTree);
}

void InsertInorder(KnightTree* pTree, KnightTree*& newTree)
{
	if (pTree == NULL) return;
	InsertInorder(pTree->pRightChild, newTree);
	newTree = InsertAVL(newTree, pTree->key, pTree->level);
	InsertInorder(pTree->pLeftChild, newTree);
}

int GetKnightKey(int eventCode)
{
	eventCode /= 10;
	if (countNumberofDigits(eventCode) == 4) return eventCode -= 1000;
	else if (countNumberofDigits(eventCode) == 3) return eventCode -= 100;
	else if (countNumberofDigits(eventCode) == 2) return eventCode -= 10;
	return 0;
}

int GetKnightLevel(int eventCode)
{
	return eventCode % 10;
}

void AddLegolas(KnightInfo knights[], int n, KnightInfo Legolas)
{
	if (Legolas.key > knights[n - 2].key) knights[n - 1] = Legolas;
	else
	{
		for (int i = n - 2; i >= 0; --i)
		{
			if (i == 0) knights[i] = Legolas;
			else if (Legolas.key < knights[i].key && Legolas.key < knights[i - 1].key)
			{
				knights[i + 1] = knights[i];
				knights[i] = knights[i - 1];
			}
			else if (Legolas.key < knights[i].key && Legolas.key > knights[i - 1].key)
			{
				knights[i + 1] = knights[i];
				knights[i] = Legolas;
				break;
			}
		}
	}
}

int GetMonsterKey(int eventCode)
{
	return abs(eventCode /= 10);
}

int GetMonsterLevel(int eventCode)
{
	return abs(eventCode % 10);
}

string DefineMonster(int eventCode)
{
	if (GetMonsterKey(eventCode) == 777) return "Lurtz";
	else if (GetMonsterKey(eventCode) == 888) return "Saruman";
	return "Normal";
}

KnightTree* LoseMonster(KnightTree*& pTree, int key, bool& BST, bool& AVL)
{
	if (formation(BST, AVL) == "BST") return DeleteBST(pTree, key);
	else if (formation(BST, AVL) == "AVL" && key == 999)
	{
		changetoBST(BST, AVL);
		return DeleteBST(pTree, key);
	}
	return DeleteAVL(pTree, key);
}

void LurtzAbility(KnightTree*& pTree, KnightTree* current, int monsterLevel)
{
	if (current == NULL) return;
	LurtzAbility(pTree, current->pLeftChild, monsterLevel);
	LurtzAbility(pTree, current->pRightChild, monsterLevel);
	if (GetDepthofNode(pTree, current->key) >= monsterLevel) pTree = DeleteBST(pTree, current->key);
}

int GetOrb_GaladrielKey(int eventCode)
{
	return eventCode % 1000;
}

bool AragornLead(KnightTree* pTree)
{
	if (pTree->key == 777) return true;
	return false;
}

void SortKnightArray(KnightInfo knights[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (knights[i].level > knights[j].level)
				swap(knights[i].level, knights[j].level);
		}
	}
}

void SetKnightLeveltoZero(KnightTree*& pTree)
{
	if (pTree == NULL) return;
	SetKnightLeveltoZero(pTree->pLeftChild);
	SetKnightLeveltoZero(pTree->pRightChild);
	pTree->level = 0;
}

void InsertLegoLas(KnightTree*& pTree, KnightInfo knights[], int left, int right)
{
	if (right >= left)
	{
		int mid = left + (right - left + 1) / 2;

		pTree = InsertBST(pTree, knights[mid].key, knights[mid].level);

		InsertLegoLas(pTree, knights, left, mid - 1);
		InsertLegoLas(pTree, knights, mid + 1, right);
	}
}

bool Escape(KnightTree* pTree, ringsignList* pSarumanList)
{
	if (CountfullNodes(pTree) != CountRingsign(pSarumanList)) return false;

	/*printList(pSarumanList);*/

	int size = CountfullNodes(pTree);
	KnightInfo* knights = new KnightInfo[size];

	BSTtoArray(pTree, knights, 0);
	SortKnightArray(knights, size);
	SortRingsignList(pSarumanList);

	for (int i = 0; i < size; ++i)
	{
		if (knights[i].level != pSarumanList->nRingsign) return false;
		pSarumanList = pSarumanList->pNext;
	}

	delete[] knights;
	return true;
}

/////////////////////////////////////// New knight arrived //////////////////////////////////

//New knight arrived except special case
KnightTree* NewKnight(KnightTree*& pTree, int eventCode, bool BST, bool AVL)
{
	int key = GetKnightKey(eventCode);
	int level = GetKnightLevel(eventCode);
	while (Contain(pTree, key))
	{
		if (key == 776 || key == 887) 
			key += 2;
		else
			++key;
		if (key > 998) 
			return pTree;
	}
	if (formation(BST, AVL) == "BST") return InsertBST(pTree, key, level);
	return InsertAVL(pTree, key, level);
}

///////////////////////////////////// Found Orb ///////////////////////////////////////////

//Found philosopher's orb
void RescueOrb(KnightTree*& pTree, int eventCode)
{
	if (pTree == NULL) return;

	int OrbValue = GetOrb_GaladrielKey(eventCode);
	KnightTree* result = FindClosestKnight(pTree, OrbValue);
	if (result->level < 9) ++result->level;
}

///////////////////////////////////// Meet Aragon //////////////////////////////////////////

//Encounter Aragorn
KnightTree* MeetAragorn(KnightTree*& pTree, int eventCode)
{
	int key = GetKnightKey(eventCode);
	int level = GetKnightLevel(eventCode);

	if (IsEmpty(pTree)) return InsertBST(pTree, key, level);

	KnightTree* newTree = NULL;

	newTree = InsertBST(newTree, key, level);
	InsertPreorder(pTree, newTree);
	pTree = DeleteTree(pTree);
	return newTree;
}

/////////////////////////////////// Meet Gandalf ///////////////////////////////////////////

//Encounter Gandalf
KnightTree* MeetGandalf(KnightTree*& pTree, int eventCode)
{
	int key = GetKnightKey(eventCode);
	int level = GetKnightLevel(eventCode);

	if (IsEmpty(pTree)) return InsertBST(pTree, key, level);

	KnightTree* newTree = NULL;

	newTree = InsertAVL(newTree, key, level);
	InsertInorder(pTree, newTree);
	pTree = DeleteTree(pTree);
	return newTree;
}

/////////////////////////////////// Meet Legolas /////////////////////////////////////

//Encounter Legolas
KnightTree* MeetLegolas(KnightTree*& pTree, int eventCode)
{
	KnightInfo Legolas;
	Legolas.key = GetKnightKey(eventCode);
	Legolas.level = GetKnightLevel(eventCode);

	if (IsEmpty(pTree)) return InsertBST(pTree, Legolas.key, Legolas.level);

	int n = CountfullNodes(pTree) + 1;
	KnightInfo* knights = new KnightInfo[n];

	BSTtoArray(pTree, knights, 0);
	AddLegolas(knights, n, Legolas);

	pTree = DeleteTree(pTree);

	int left = 0;
	int right = n - 1;
	InsertLegoLas(pTree, knights, left, right);

	delete[] knights;
	return pTree;
}

//////////////////////////////////// Meet Gimli /////////////////////////////

//Encounter Gimli
KnightTree* MeetGimli(KnightTree*& pTree, int eventCode, int BST, int AVL)
{
	if (CheckCompleteTree(pTree) == false)
	{
		int key = GetKnightKey(eventCode);
		int level = GetKnightLevel(eventCode);
		if (formation(BST, AVL) == "BST") return InsertBST(pTree, key, level);
		return InsertAVL(pTree, key, level);
	}
	return pTree;
}

/////////////////////////////////// Fight Monster ////////////////////////////////

//Fight monster
KnightTree* MeetMonster(KnightTree*& pTree, int eventCode, bool& BST, bool& AVL)
{
	if (pTree == NULL) return pTree;

	int monsterKey = GetMonsterKey(eventCode);
	int monsterLevel = GetMonsterLevel(eventCode);

	/*cout << "Types of monster: " << DefineMonster(eventCode) << " | " << "Lv: " << monsterLevel << endl;*/

	if (AragornLead(pTree) && monsterLevel == pTree->level) return pTree;

	if (DefineMonster(eventCode) == "Normal" ||
		(DefineMonster(eventCode) == "Lurtz" && CountLeafNodes(pTree) != monsterLevel))
	{
		KnightTree* knight = FindClosestKnight(pTree, monsterKey);

		/*cout << "Knight chosen: " << knight->key  << " | " << "Lv: " << knight->level << endl;*/

		if (knight->level < monsterLevel) return LoseMonster(pTree, knight->key, BST, AVL);
	}
	else if (DefineMonster(eventCode) == "Lurtz" && CountLeafNodes(pTree) == monsterLevel)
	{
		KnightTree* current = pTree;
		LurtzAbility(pTree, current, monsterLevel);
	}
	else if (DefineMonster(eventCode) == "Saruman")
	{
		while (pTree != NULL)
		{
			KnightTree* knight = FindClosestKnight(pTree, monsterKey);

			/*cout << "Knight chosen: " << knight->key << " | " << "Lv: " << knight->level << endl;*/

			if (knight->level < monsterLevel) pTree = LoseMonster(pTree, knight->key, BST, AVL);
			else break;
		}
	}
	return pTree;
}

////////////////////////////////// Meet Galadriel ////////////////////////////////

void MeetGaladriel(KnightTree*& pTree, int eventCode)
{
	if (pTree == NULL) return;

	int GaladrielKey = GetOrb_GaladrielKey(eventCode);
	KnightTree* knight = FindClosestKnight(pTree, GaladrielKey);
	knight->level = 9;
}

/////////////////////////////////////////////////////////////////////////////////////

void SarumanEscape(KnightTree*& pTree, ringsignList* pSarumanList)
{
	if (Escape(pTree, pSarumanList) == true)
		SetKnightLeveltoZero(pTree);
}

string defineEvent(int eventCode, bool& BST, bool& AVL)
{
	if (eventCode == 5) return "SarumanEscape";

	else if (eventCode < 0) return "MeetMonster";

	else if ((eventCode >= 100 && eventCode <= 199) ||
		(eventCode >= 1000 && eventCode <= 1999) ||
		(eventCode >= 10000 && eventCode <= 19999))
	{
		if (GetKnightKey(eventCode) == 777)
		{
			changetoBST(BST, AVL);
			return "Aragorn";
		}
		else if (GetKnightKey(eventCode) == 999)
		{
			changetoAVL(BST, AVL);
			return "Gandalf";
		}
		else if (GetKnightKey(eventCode) == 888)
		{
			changetoBST(BST, AVL);
			return "Legolas";
		}
		else if (eventCode >= 10000 && eventCode <= 10009) return "Gimli";
		return "NewKnight";
	}

	else if ((eventCode >= 200 && eventCode <= 299) ||
		(eventCode >= 2000 && eventCode <= 2999))
		return "RescueOrb";

	else if ((eventCode >= 300 && eventCode <= 399) ||
		(eventCode >= 3000 && eventCode <= 3999))
		return "MeetGaladriel";
	return "";
}

KnightTree*  siege(eventList* pEvent, ringsignList* pSarumanList)
{
	KnightTree* pTree = NULL; 
	//let's save the lady
	bool BST = true;
	bool AVL = false;

	while (defineEvent(pEvent->nEventCode, BST, AVL) == "RescueOrb" ||
		defineEvent(pEvent->nEventCode, BST, AVL) == "MeetGaladriel")
		pEvent = pEvent->pNext;

	while (pEvent != NULL)
	{
		string event = defineEvent(pEvent->nEventCode, BST, AVL);

		/*cout << "EventCode: " << pEvent->nEventCode << " | " << "Event: " << event << endl;*/

		if (event == "SarumanEscape")
		{
			SarumanEscape(pTree, pSarumanList);
			/*print2D(pTree);*/
			break;
		}

		else if (event == "MeetMonster") pTree = MeetMonster(pTree, pEvent->nEventCode, BST, AVL);

		else if (event == "Aragorn") pTree = MeetAragorn(pTree, pEvent->nEventCode);

		else if (event == "Gandalf") pTree = MeetGandalf(pTree, pEvent->nEventCode);

		else if (event == "Legolas") pTree = MeetLegolas(pTree, pEvent->nEventCode);

		else if (event == "Gimli") pTree = MeetGimli(pTree, pEvent->nEventCode, BST, AVL);

		else if (event == "NewKnight") pTree = NewKnight(pTree, pEvent->nEventCode, BST, AVL);

		else if (event == "RescueOrb") RescueOrb(pTree, pEvent->nEventCode);

		else if (event == "MeetGaladriel") MeetGaladriel(pTree, pEvent->nEventCode);

		/*if (IsEmpty(pTree)) cout << "NULL";
		else print2D(pTree);

		cout << "\n";

		cout << "-----------------------------------------------------" << endl;*/

		if (IsEmpty(pTree)) break;
		pEvent = pEvent->pNext;
	}
  
	return pTree;
}

//your code should be before that directive