#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

/****************************************************
DECLARACIÓN DE FUNCIONES
****************************************************/

int Insert_Value(int value);
int Remove_Value(int id);
int Remove_Largest();
void Print_Collection();
void Release_Memory();


/****************************************************
ESTRUCTURAS
****************************************************/
/*Se usa para construir la lista, se le agrega 
el id y value de cada valor de Collection*/ 
struct node
{
	int id;
	int value;
	struct node* nextdir;
};

/****************************************************
VARIABLES GLOBALES
****************************************************/
struct node* first;
struct node* next;//Nuevo elemento de lista
struct node* aux;
struct node* auxremove;//Auxiliar utilizado para borrar por ID. Esta un nodo atrás del nodo que tiene el id buscado.
int idCount = 0; //Variable que contendrá los Ids asignados automáticamente.

/***************************************************
FUNCIONES
***************************************************/

int main()
{
	first=NULL;
	
	int newid;
	int newvalue;
	int option = 0;
	
	cout << "\nWelcome to your new Integers Collection\n" << endl;
	
	while (option != 9) //La aplicación no se cerrará hasta que sea elegida la opción Exit.
	{
		cout << "Choose an option:\n" << endl;
		cout << "Add a new value (1)" << endl;
		cout << "Remove a value giving id (2)" << endl;
		cout << "Remove Largest (3)" << endl;
		cout << "Print collection (4)" <<endl;
		cout << "Exit (9)\n"<<endl;
		cin >> option;
	
		switch (option)
		{
			case 1: 
			int newValue;
			int newID;
			cout << "Type the new value: ";
			cin>>newValue;
			newID = Insert_Value(newValue);
			cout << "New ID of Value added: " << newID << "\n" << endl;
			break;
			
			case 2:
			int idToRemove;
			int valueRemoved;
			cout <<"Type the id to remove: ";
			cin>>idToRemove;
			valueRemoved = Remove_Value(idToRemove);
			if(valueRemoved == 0)
			{
				cout<< "ERROR: No value with the ID entered, try again"<<endl;
			}
			else
			{
				cout<< "Value removed was: " << valueRemoved << "\n" <<endl;
			}
			break;
			
			case 3:
			int ValueLargestRemoved;
			ValueLargestRemoved = Remove_Largest();
			if(ValueLargestRemoved == 0)
			{
				cout << "ERROR: No elements in Collection yet.\n"<<endl;
			}
			else
			{
				cout << "Largest value removed= " << ValueLargestRemoved<< "\n" <<endl;
			}
			break;
			
			case 4:
			Print_Collection();
			break;
			
			case 9:
			break;
			
		}
	}
	Release_Memory();
}

/*!
 *\brief Insert_Value().- Utilizada para agregar nodos a la lista. Se le asigna un ID automático (idCount) y se toma el valor 	agregado por el usuario.
 *\param [in] int value.- Valor elegido por el usuario para añadir a Collection.
 *\return Regresa el ID del valor añadido.
*/
int Insert_Value(int value)
{
	idCount++;
	aux=first;
	next=(struct node*)malloc(sizeof(struct node));
	next->value=value;
	next->id=idCount;
	next->nextdir=NULL;
	if(first==NULL)
	{
		first=next;
		return idCount;
	}
	while(aux->nextdir != NULL)
	{
		aux = aux->nextdir;
	}
	aux->nextdir = next;

	return idCount;
}

/*!
 *\brief Remove_Value().- Elimina el dato de la lista según el ID que el usuario haya elegido.
 *\param [in] int id.- Id elegido por el usuario para que sea borrado de Collection.
 *\return Regresa el valor del dato borrado.
*/
int Remove_Value(int id)
{
	int i=0;
	int valueRemoved;
	aux=first;
	auxremove=aux;
	while(aux != NULL)
	{
		if(aux->id == id)
		{
			valueRemoved = aux->value;
			if(i==0)
			{
				first=aux->nextdir;
				free(aux);
			}
			else
			{
				auxremove->nextdir = aux->nextdir;
				free(aux);
			}
			return valueRemoved;
		}
		else
		{
			auxremove = aux;
			aux = aux->nextdir;
			i++;
		}
	}
	return 0;
}

/*!
 *\brief Remove_Largest().- Elimina el dato con el valor mas alto de Collection.
 *\return Regresa el valor del dato borrado.
*/
int Remove_Largest()
{
	int idLargestRemoved;
	int AuxLargest=0;
	aux = first;
	if (first== NULL)
	{
		return 0;
	}
	else
	{
		while (aux != NULL)
		{
			if(aux->value > AuxLargest)
			{
				AuxLargest = aux->value;
				idLargestRemoved = aux->id;
			}
			aux = aux->nextdir;
		}
	}
	return Remove_Value(idLargestRemoved);
}

/*!
 *\brief Print_Collection().- Imprime todos los ids y valores que contiene Collection.
*/
void Print_Collection()
{
	aux = first;
	cout<<"COLLECTION VALUES"<<endl;
	cout<<"ID"<<setw(13)<<"VALUE"<<endl;
	while (aux != NULL)
	{
		cout<<" "<<aux->id<<setw(13)<<aux->value<<endl;
		aux = aux->nextdir;
	}
	cout<<"\n";
}

/*!
 *\brief Release_Memory().- Al ser cerrado el programa se libera la memoria de todos los nodos que contiene Collection.
*/
void Release_Memory()
{
	if (first == NULL)
	{
		cout << "Application closed"<<endl;
	}
	else
	{
		aux = first;
		while (first != NULL)
		{
			first = first->nextdir;
			free(aux);
			aux = first;
		}
		cout<<"Memory released and application closed"<<endl;
	}
}