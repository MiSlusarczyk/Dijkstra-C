/** @file  */

#include "Functions.h"


bool Management(const char* path1, const char* path2, const char* path3)
{
	//stworzenie glownych list
	struct System* pHeadS = NULL;
	struct Input* pHeadI =NULL;
	struct Node* pHeadCI = NULL;
	struct Node* pHeadO = NULL;
	struct Node* pHeadST = NULL;
	struct Solution* pHeadSOL = NULL;

	struct System** d_S = &pHeadS;
	struct Input** d_I = &pHeadI;
	struct Node** d_CI = &pHeadCI;
	struct Node** d_O = &pHeadO;
	struct Node** d_ST = &pHeadST;
	struct Solution** d_SOL = &pHeadSOL;

	struct Node* pHeadY = NULL;
	struct Node** d_Y = &pHeadY;

	bool flag = true;

	flag = Load1(path1, d_S, d_CI, d_O, d_ST);
	{
		if (flag == false)
		{
			printf("Error reading data from the first file!");
			return false;
		}
	}
	flag = Load2(path2, d_CI, d_I, d_ST);
	{
		if (flag == false)
		{
			printf("Error reading data from the second file!");
			return false;
		}
	}
	CompleteData(pHeadI, d_ST, d_SOL);
	MakeSolution(d_S, d_SOL);
	ShowAll(pHeadS, pHeadST, pHeadCI, pHeadI, pHeadO, pHeadSOL);
	Save(path3, pHeadI, pHeadO, pHeadSOL);

	return true;
}

bool Load1(const char* path1, struct System** d_S, struct Node** d_CI, struct Node** d_O, struct Node** d_ST)
{

	FILE* file = fopen(path1, "r");

	if (file == NULL)
	{
		perror("File error!");
		return false;
	}

	Type type_name = NA;

	char* temp = malloc(sizeof(char));
	int i = 0;

	if (feof(file))
	{
		perror("Empty file!");
		return false;
	}

	while (!feof(file))
	{

		fscanf(file, "%s", temp);


		if (strcmp(temp,"IN:")==0)
		{
			type_name = IN;
		}
		else if (strcmp(temp, "OUT:") == 0)
		{
			type_name = OUT;
		}
		else if (strcmp(temp, "NEG") == 0)
		{
			type_name = NEG;
		}
		else if (strcmp(temp, "AND") == 0)
		{
			type_name = AND;
		}
		else if (strcmp(temp, "NAND") == 0)
		{
			type_name = NAND;
		}
		else if (strcmp(temp, "OR") == 0)
		{
			type_name = OR;
		}
		else if (strcmp(temp, "NOR") == 0)
		{
			type_name = NOR;
		}
		else if (strcmp(temp, "XOR") == 0)
		{
			type_name = XOR;
		}
		else if (strcmp(temp, "XNOR") == 0)
		{
			type_name = XNOR;
		}
		

		if (type_name != IN && type_name != OUT)
		{
			i++;
		}

		Attribution(file, d_ST, d_O, d_S, d_CI, type_name, i);

	}

	fclose(file);

	return true;
}

bool Load2(const char* path2, struct Node** d_CI, struct Input** d_I, struct Node** d_ST)
{

	FILE* file = fopen(path2, "r");

	if (file == NULL)
	{
		perror("File error!");
		return false;
	}

	char t = '\0';
	int temp;

	struct Input** d_input = NULL;
	struct Node** d_n = NULL;

	if (feof(file))
	{
		perror("Empty file!");
		return false;
	}

	while (!feof(file))
	{
		struct Input* temp_input = CreateInput();

		while (t != '\n')
		{
			struct Node* n = CreateNode();

			t = '\n';

			fscanf(file, "%u%c", &temp, &t);

			if (t == ':')
			{
				n->id = temp;

				fscanf(file, "%c ", &n->val);

				d_n = &(temp_input->i);
				AddNodeEnd(n, d_n);
			}
			else
			{
				temp_input->tact = temp;
			}

			n = NULL;
		}

		if (CompareNode(*d_CI, temp_input->i)==true)
		{
			printf("Incompatible inputs in first and second file!");
			return false;
		}
		
		AddInputEnd(temp_input, d_I);

		t = '\0';
		d_n = NULL;
		d_input = NULL;
	}
	fclose(file);
	return true;

}

void Attribution(FILE* file, Node** d_ST, Node** d_O, System** d_S, Node** d_CI, Type type_name, int i)
{
	char t = '\0';

	struct System* temp_system = CreateSystem();

	struct Node** d_n = NULL;

	while ((!feof(file)) && (t != '\n'))
	{

		t = '\n';

		struct Node* n = CreateNode();

		fscanf(file, "%u%c", &n->id, &t);


		if (type_name == NA)
		{
			break;
		}
		else if (type_name == IN)
		{
			AddNodeEnd(n, d_CI);
		}
		else if (type_name == OUT)
		{
			AddNodeEnd(n, d_O);
		}
		else
		{
			if (FindNodeID(n->id, *d_ST)==false)
			{
				CopyNodeEnd(n, d_ST);
			}


			if (t != '\n')
			{
				d_n = &(temp_system->in);
				AddNodeEnd(n, d_n);
			}
			else if (t == '\n')
			{
				d_n = &(temp_system->out);
				AddNodeEnd(n, d_n);
			}
		}

		n = NULL;
		d_n = NULL;
	}


	if (type_name != IN && type_name != OUT)
	{
		temp_system->gid = i;
		temp_system->gate = type_name;

		AddSystemEnd(temp_system, d_S);
	}

}

bool CompleteData(Input* d_I, Node** d_ST, Solution** d_SOL)
{

	if (d_I == NULL || d_ST == NULL)
	{
		return false;
	}
	else
	{
		if (d_I == NULL || d_I->i == NULL)
		{
			return false;
		}
		else
		{
			Input* t_I = d_I;
			Solution* t_SOL = NULL;

			while (t_I != NULL)
			{
				Node* t_N = t_I->i;
				Node* t_ST = NULL;
				CopyNodeList(*d_ST, &t_ST);
				t_SOL = CreateSolution();

				while (t_N != NULL)
				{

					Node* tempn = t_ST;

					while (tempn != NULL && (tempn->id != t_N->id))
					{
						tempn = tempn->pNext;
					}
					if (tempn != NULL)
					{
						if (tempn->id == t_N->id)
						{
							tempn->val = t_N->val;
						}
					}

					t_N = t_N->pNext;
				}

				CopyNodeList(t_ST, &(t_SOL->ST));

				t_SOL->tact = t_I->tact;

				t_I = t_I->pNext;

				AddSolutionEnd(t_SOL, d_SOL);
			}

			return true;
		}
	}
}

void MakeSolution(System** d_S, Solution** d_SOL)
{

	Solution* tempSOL = *d_SOL;
	while (tempSOL != NULL)
	{
		int idx = 1;
		System* tempS = *d_S;

		while (idx <= tempSOL->tact)
		{
			if (idx == 3)
			{
				printf("");
			}
			SolveStep(tempS, &tempSOL);

			idx++;
		}

		tempSOL = tempSOL->pNext;
	}
}

void SolveStep(System* tempS, Solution** d_tempLST)
{
	while (tempS != NULL)
	{

		if (FindLGate(tempS->gid, (*d_tempLST)->lgate) == false)
		{
			unsigned long int l = 0;
			unsigned long int h = 0;
			unsigned long int x = 0;
			Node* tIN = tempS->in;

			while (tIN != NULL)
			{
				char tval = FindNodeVAL(tIN->id, (*d_tempLST)->ST);
				if (tval == '0')
				{
					l++;
				}
				else if (tval == '1')
				{
					h++;
				}
				else if (tval == 'x')
				{
					x++;
				}

				tIN = tIN->pNext;
			}

			if (tempS->gate == NEG)
			{

				if (x == 0 && (l == 0 || h == 0))
				{
					Node* tS = tempS->out;
					while (tS != NULL)
					{
						Node* n = CreateNode();
						n->id = tS->id;

						if (h != 0)
						{
							n->val = '0';
						}
						else
						{
							n->val = '1';
						}

						if (FindNodeID(n->id, (*d_tempLST)->tempST) == false)
						{
							CopyNodeEnd(n, &((*d_tempLST)->tempST));
						}
						tS = tS->pNext;
					}

					CopyLIntEnd(tempS->gid, &((*d_tempLST)->lgate));
				}
			}
			else if (tempS->gate == AND)
			{
				if (x == 0 || l != 0)
				{
					Node* tS = tempS->out;
					while (tS != NULL)
					{
						Node* n = CreateNode();
						n->id = tS->id;

						if ((h != 0 && l != 0) || h == 0)
						{
							n->val = '0';
						}
						else if (l == 0 && x == 0)
						{
							n->val = '1';
						}

						if (FindNodeID(n->id, (*d_tempLST)->tempST) == false)
						{
							CopyNodeEnd(n, &((*d_tempLST)->tempST));
						}
						tS = tS->pNext;
					}

					CopyLIntEnd(tempS->gid, &((*d_tempLST)->lgate));
				}
			}
			else if (tempS->gate == NAND)
			{
				Node* tS = tempS->out;
				if (x == 0 || l != 0)
				{
					while (tS != NULL)
					{
						Node* n = CreateNode();
						n->id = tS->id;

						if ((h != 0 && l != 0) || h == 0)
						{
							n->val = '1';
						}
						else if (l == 0 && x == 0)
						{
							n->val = '0';
						}

						if (FindNodeID(n->id, (*d_tempLST)->tempST) == false)
						{
							CopyNodeEnd(n, &((*d_tempLST)->tempST));
						}
						tS = tS->pNext;
					}

					CopyLIntEnd(tempS->gid, &((*d_tempLST)->lgate));
				}
			}
			else if (tempS->gate == OR)
			{
				Node* tS = tempS->out;
				if (x == 0 || (h != 0))
				{
					while (tS != NULL)
					{
						Node* n = CreateNode();
						n->id = tS->id;

						if (h != 0)
						{
							n->val = '1';
						}
						else if (h == 0 && x == 0)
						{
							n->val = '0';
						}

						if (FindNodeID(n->id, (*d_tempLST)->tempST) == false)
						{
							CopyNodeEnd(n, &((*d_tempLST)->tempST));
						}
						tS = tS->pNext;
					}

					CopyLIntEnd(tempS->gid, &((*d_tempLST)->lgate));
				}
			}
			else if (tempS->gate == NOR)
			{
				Node* tS = tempS->out;
				if (x == 0 || (h != 0))
				{
					while (tS != NULL)
					{
						Node* n = CreateNode();
						n->id = tS->id;

						if (h != 0)
						{
							n->val = '0';
						}
						else if (h == 0 && x == 0)
						{
							n->val = '1';
						}

						if (FindNodeID(n->id, (*d_tempLST)->tempST) == false)
						{
							CopyNodeEnd(n, &((*d_tempLST)->tempST));
						}
						tS = tS->pNext;
					}

					CopyLIntEnd(tempS->gid, &((*d_tempLST)->lgate));
				}
			}
			else if (tempS->gate == XOR)
			{
				Node* tS = tempS->out;
				if (x == 0 || (h != 0 && l != 0))
				{
					while (tS != NULL)
					{
						Node* n = CreateNode();
						n->id = tS->id;

						if (h != 0 && l != 0)
						{
							n->val = '1';
						}
						else if ((l == 0 || h == 0) && x == 0)
						{
							n->val = '0';
						}

						if (FindNodeID(n->id, (*d_tempLST)->tempST) == false)
						{
							CopyNodeEnd(n, &((*d_tempLST)->tempST));
						}
						tS = tS->pNext;
					}

					CopyLIntEnd(tempS->gid, &((*d_tempLST)->lgate));
				}
			}
			else if (tempS->gate == XNOR)
			{
				Node* tS = tempS->out;
				if (x == 0 || (h != 0 && l != 0))
				{
					while (tS != NULL)
					{
						Node* n = CreateNode();
						n->id = tS->id;

						if (h != 0 && l != 0)
						{
							n->val = '0';
						}
						else if ((l == 0 || h == 0) && x == 0)
						{
							n->val = '1';
						}

						if (FindNodeID(n->id, (*d_tempLST)->tempST) == false)
						{
							CopyNodeEnd(n, &((*d_tempLST)->tempST));
						}
						tS = tS->pNext;
					}

					CopyLIntEnd(tempS->gid, &((*d_tempLST)->lgate));
				}
			}
		}

		tempS = tempS->pNext;
	}

	CompleteStep((*d_tempLST)->tempST, &(*d_tempLST)->ST);
}


void CompleteStep(Node* tempST, Node** pHeadST)
{
	if (tempST != NULL && pHeadST != NULL)
	{
		while (tempST != NULL)
		{
			Node* m_ST = *pHeadST;

			while (m_ST != NULL)
			{
				if (tempST->id == m_ST->id)
				{
					m_ST->val = tempST->val;
				}

				m_ST = m_ST->pNext;
			}

			tempST = tempST->pNext;
		}
	}
}

void ShowAll(struct System* pHeadS, struct Node* pHeadST, struct Node* pHeadCI, struct Input* pHeadI, struct Node* pHeadO, struct Solution* pHeadSOL)
{
	ShowSystem(pHeadS);

	printf("\n\nLista wyjsc ukladu:\n");
	ShowNode(pHeadO);

	printf("\n\nLista wejsc ukladu z pierwszego pliku:\n");
	ShowNode(pHeadCI);

	ShowInput(pHeadI);

	ShowSolution(pHeadI, pHeadO, pHeadSOL);
}

bool Save(const char* path3, struct Input* pHeadI, struct Node* pHeadO, struct Solution* pHeadSOL)
{
	FILE* file = fopen(path3, "w");

	while (pHeadI != NULL && pHeadSOL != NULL)
	{
		fprintf(file, "IN: ");

		while ((pHeadI->i) != NULL)
		{
			fprintf(file, "%d:%c ", pHeadI->i->id, pHeadI->i->val);

			pHeadI->i = (pHeadI->i)->pNext;
		}

		fprintf(file, "T:%d ", pHeadI->tact);

		Node* temp = pHeadO;

		fprintf(file, "OUT: ");

		while (temp != NULL)
		{
			Node* tempST = pHeadSOL->ST;

			while (tempST != NULL)
			{
				if (temp->id == tempST->id)
				{
					fprintf(file, "%d:%c", tempST->id, tempST->val);

					if (temp->pNext != NULL)
					{
						fprintf(file, " ");
					}
				}

				tempST = tempST->pNext;
			}

			temp = temp->pNext;
		}

		if (pHeadSOL->pNext != NULL)
		{
			fprintf(file, "\n");
		}

		pHeadI = pHeadI->pNext;
		pHeadSOL = pHeadSOL->pNext;
	}

	fclose(file);
	return true;
}