/** @file  */

#include"Lists.h"

//Tworzenie domyslnych struktur
Node* CreateNode()
{
	Node* n = malloc(sizeof(Node));
	n->id = 0;
	n->val = 'x';
	n->pNext = NULL;
	return n;
}

Input* CreateInput()
{
	Input* n = malloc(sizeof(Input));
	n->pNext = NULL;
	n->i = NULL;

	return n;
}

System* CreateSystem()
{
	System* n = malloc(sizeof(System));
	n->pNext = NULL;
	n->out = NULL;
	n->in = NULL;

	n->gate = NA;
	n->gid = 0;

	return n;
}

LInt* CreateLInt()
{
	LInt* n = malloc(sizeof(LInt));
	n->pNext = NULL;
	n->val = 0;

	return n;
}

Solution* CreateSolution()
{
	Solution* n = malloc(sizeof(Solution));
	n->pNext = NULL;
	n->tempST = NULL;
	n->lgate = NULL;
	n->ST = NULL;
	n->tact = 0;

	return n;
}


//Funkcje pomocnicze do operowania na Node'ach

 void AddNodeEnd (Node* n, Node** pHeadN)
{
	 if (pHeadN != NULL)
	 {
		 if ((*pHeadN) != NULL)
		 {
			 Node* temp = (*pHeadN);
			 while ((temp)->pNext != NULL)
			 {
				 (temp) = (temp)->pNext;
			 }
			 temp->pNext = n;

		 }
		 else
		 {
			 (*pHeadN) = n;
		 }
	 }
}

 void CopyNodeEnd(Node* n, Node** pHeadN)
 {
	 if (pHeadN != NULL)
	 {
		 if ((*pHeadN) != NULL)
		 {
			 Node* temp = (*pHeadN);
			 while ((temp)->pNext != NULL)
			 {
				 (temp) = (temp)->pNext;
			 }
			 (temp)->pNext = malloc(sizeof(Node));
			 memcpy(temp->pNext, n, sizeof(Node));

		 }
		 else
		 {
		 (*pHeadN) = malloc(sizeof(Node));
		 memcpy((*pHeadN), n, sizeof(Node));
		 }
	 }
 }

 void CopyNodeList(Node* pHeadN1, Node** pHeadN2)
 {
		 while (pHeadN1 != NULL)
		 {
			 if ((*pHeadN2) == NULL)
			 {
				 *pHeadN2 = malloc(sizeof(Node));
				 memcpy((*pHeadN2), pHeadN1, sizeof(Node));
				 (*pHeadN2)->pNext = NULL;
				 pHeadN1 = pHeadN1->pNext;
			 }
			 else
			 {
				 Node* temp = (*pHeadN2);
				 while ((temp)->pNext != NULL)
				 {
					 (temp) = (temp)->pNext;
				 }
				 temp->pNext = malloc(sizeof(Node));
				 memcpy(temp->pNext, pHeadN1, sizeof(Node));
				 temp->pNext->pNext = NULL;
				 pHeadN1 = pHeadN1->pNext;
			 }
		 }
 }

 char FindNodeVAL(unsigned int tempid, Node* pHeadN)
 {
	 while (pHeadN != NULL)
	 {
		 if (pHeadN->id == tempid)
		 {
			 return pHeadN->val;
		 }
		 pHeadN = pHeadN->pNext;
	 }
	 return NULL;
 }


 void ShowNode(Node* pHeadN)
 {
	 while (pHeadN != NULL)
	 {
		 printf("%u:%c ", pHeadN->id, pHeadN->val);

		 pHeadN = pHeadN->pNext;
	 }
 }

bool FindNodeID(unsigned int id, Node* pHeadState)
{
		if (pHeadState == NULL)
		{
			return false;
		}
		else
		{
			Node *temp = pHeadState;

			while (temp != NULL)
			{
				if (id == temp->id)
				{
					temp = NULL;
					return true;
				}

				temp = temp->pNext;
			}

			return false;
		}
}

void PrintNode(Node* n, Node* pHeadN)
{
	while (n != NULL)
	{
		Node* temp = pHeadN;
		while (temp != NULL)
		{
			if (n->id == temp->id)
			{
				printf("%d:%c ", temp->id, temp->val);
			}

			temp = temp->pNext;
		}

		n = n->pNext;
	}
}


Node* FindNodeN(Node* n, Node** pHeadState)
{
	if (pHeadState != NULL)
	{
		if ((*pHeadState) == NULL)
		{
			return NULL;
		}
		else
		{
			Node *temp = *pHeadState;

			while (temp != NULL)
			{
				if (n->id == temp->id)
				{
					return temp;
				}
			}

			temp = temp->pNext;
		}

		return NULL;
	}
	else
	{
		return NULL;
	}
}

bool CompareNode(Node* pHeadI, Node* pHeadCI)
{
	while (pHeadI != NULL && pHeadCI != NULL)
	{
		if(pHeadI->id==pHeadCI->id)
		{
			pHeadI = pHeadI->pNext;
			pHeadCI = pHeadCI->pNext;
		}

	}

	if (pHeadI == NULL && pHeadCI == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//Funkcje pomocnicze do operowania na Systemach
void AddSystemEnd(System* s, System** pHeadS)
{
	if (pHeadS != NULL)
	{
		if ((*pHeadS) != NULL)
		{
			System* temp = (*pHeadS);
			while ((temp)->pNext != NULL)
			{
				(temp) = (temp)->pNext;
			}
			temp->pNext = s;

		}
		else
		{
			(*pHeadS) = s;
		}
	}
}

void ShowSystem(System* pHeadS)
{
	printf("Lista bramek:\n\n");

	while (pHeadS != NULL)
	{

		printf("Numer bramki: %d\n", pHeadS->gid);

		switch (pHeadS->gate) 
		{
		case NEG:
			printf("Bramka NEG\n");
			break;
		case AND:
			printf("Bramka AND\n");
			break;
		case NAND:
			printf("Bramka NAND\n");
			break;
		case OR:
			printf("Bramka NAND\n");
			break;
		case NOR:
			printf("Bramka NAND\n");
			break;
		case XOR:
			printf("Bramka XNOR\n");
			break;
		case NA:
			printf("Brak bramki!\n");
			break;
		default:
			printf("Blad bramki!\n");
			break;
		}

		printf("Lista wejsc bramki: ");
		ShowNode(pHeadS->in);

		printf("\nWyjscie bramki: ");
		ShowNode(pHeadS->out);
		printf("\n\n");

		pHeadS = pHeadS->pNext;
	}
}

//Funkcje pomocnicze do operowania na strukturze wejscia
void AddInputEnd(Input* i, Input** pHeadI)
{
	if (pHeadI != NULL)
	{
		if ((*pHeadI) != NULL)
		{
			Input* temp = (*pHeadI);
			while ((temp)->pNext != NULL)
			{
				(temp) = (temp)->pNext;
			}
			temp->pNext = i;

		}
		else
		{
			(*pHeadI) = i;

		}
	}
}

void ShowInput(Input* pHeadI)
{
	printf("\n\nLista wejsc ukladu z drugiego pliku:\n");
	while (pHeadI != NULL)
	{
		ShowNode(pHeadI->i);
		printf("Liczba taktow: %d\n", pHeadI->tact);
		
		pHeadI = pHeadI->pNext;
	}
	printf("\n");
}

//Funkcje pomocnicze do operowania na liscie intow
void CopyLIntEnd(unsigned int n, LInt** pHeadLInt)
{
	if (pHeadLInt != NULL)
	{

		LInt* tempLI = CreateLInt();
		tempLI->val = n;

		if ((*pHeadLInt) != NULL)
		{
			LInt* temp = (*pHeadLInt);
			while ((temp)->pNext != NULL)
			{
				(temp) = (temp)->pNext;
			}
			(temp)->pNext = malloc(sizeof(Node));
			memcpy(temp->pNext, tempLI, sizeof(Node));

		}
		else
		{
			(*pHeadLInt) = malloc(sizeof(Node));
			memcpy((*pHeadLInt), tempLI, sizeof(Node));
		}
	}
}

bool FindLGate(unsigned int gid, LInt* pHeadLInt)
{
	if (pHeadLInt == NULL)
	{
		return false;
	}
	else
	{
		LInt* temp = pHeadLInt;

		while (temp != NULL)
		{
			if (gid == temp->val)
			{
				temp = NULL;
				return true;
			}

			temp = temp->pNext;
		}

		return false;
	}
}

//Funkcje pomocnicze do operowania na strukturze rozwiazania
void AddSolutionEnd(Solution* sol, Solution** pHeadSOL)
{
	if (pHeadSOL != NULL)
	{
		if ((*pHeadSOL) != NULL)
		{
			Solution* temp = (*pHeadSOL);
			while ((temp)->pNext != NULL)
			{
				(temp) = (temp)->pNext;
			}
			temp->pNext = sol;

		}
		else
		{
			(*pHeadSOL) = sol;
		}
	}
}

void ShowSolution(Input* pHeadI, Node*  pHeadO, Solution* pHeadSOL)
{
	printf("Rozwiazanie:\n");

	while (pHeadSOL!=NULL)
	{
		printf("IN: ");
		PrintNode(pHeadI->i, pHeadSOL->ST);
		
		printf("T:%d ",pHeadSOL->tact);

		printf("OUT: ");
		PrintNode(pHeadO, pHeadSOL->ST);
		printf("\n");

		pHeadI = pHeadI->pNext;
		pHeadSOL = pHeadSOL->pNext;
	}
}