/***************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the
concepts learned. I have constructed the functions and their respective algorithms and corresponding code by
myself. The program was run, tested, and debugged by my own efforts. I further certify that I have not copied in
part or whole or otherwise plagiarized the work of other students and/or persons.
Eryn Claire Go Sy, DLSU ID# 12506621
***************************************************************************/

/*
	Description: This program .
	Programmed by: Sy, Eryn Claire Go, S21B
	Last modified: March 30, 2025
	Version: 
	[Acknowledgements: <stdio.h>, <stdlib.h>, <string.h>, <time.h>]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50

typedef char string[100];

struct meal
{
	string food;
	float quantity;
	string unit;
	float calories;
};
typedef struct meal mealType;

struct recipe
{
	string name;
	string class;
	int servings
	float calories;
};
typedef struct recipe recipeType;

/*
	Helper Function 1: Alphabetical Organizer
	This function organizes the recipe list in increasing alphabetical order
	Precondition: 
	@param option is the user's input into the menu items
*/
void AlphabeticalSort()
{
	int i, j, min;
	candidateType temp;
	for(i = 0; i < n; i++)
	{
		min = i;
		for(j = i; j < n; j++)
		{
			if(strcmp(aCandidate[min].lastname, aCandidate[j].lastname) > 0)
				min = j;
		}
		if(i != min)
		{
			temp = ;
			 = ;
			 = temp;
		}
	}
}

/*
	Helper Function 2: Search
	This function organizes the recipe list in increasing alphabetical order
	Precondition: 
	@param option is the user's input into the menu items
*/
void Search(recipeType aRecipe)
{
	int low = 0, high = n - 1, mid;
	int found = 0, index;
	while(!found && low <= high)
	{
		mid = low + (high - low) / 2;
		if( == A[mid])
			found = 1;
		else if( < A[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	if(found)
		index = mid;
	else
		index = -1;
	return index;
}

/*
	Function 1: Username and Password Changer
	This function changes the user's username and/or password
	Precondition: option must be a single character
	@param access is either the user's username or password
	@param option is the user's input of what they want to change (e.g. 'U' for username, 'P' for password)
*/
void AccessModifier(char option)
{
	string old_username, new_username, old_password, new_password;
	do
	{
		if(option == 'U')
		{
			printf("Old username: ")
			scanf("%s", old_password)
			printf("New username: ")
			scanf("%s", new_username)
		}
		else if(option == 'P')
		{
			printf("Old password: ")
			scanf("%s", old_password)
			printf("New password: ")
			scanf("%s", new_password)
		}
		else
			printf("Invalid input, please try again.\n")
	}while(option != 'X');
}

/*
	Function 2: Password Checker
	This function checks for user's password
	Precondition: option must be a single character
	@param username - username input
	@param sUsername - saved username
	@param password - password input
	@param sPassword - saved password
	@returns 0 or 1 depending on whether or not both username and password match
*/
int PassCheck(string username, string sUsername, string password, string sPassword)
{
	int check = 0;
	if((strcmp(username, sUsername) == 0) && (strcmp(password, sPassword) == 0))
		check = 1;
	return check;
}

/*
	Function 3: Add food-calorie info
	This function adds the info of a food item to struct meal
	Precondition: 
	@param food - food item input
	@param quantity - quantity input
	@param unit - unit input
	@param calories - calorie input
	@returns contents of temporary struct
*/
mealType AddCalorie(string food, float quantity, string unit, float calories)
{
	mealType aMeal;
	strcpy(aMeal.food, food);
	aMeal.quantity = quantity;
	strcpy(aMeal.unit, unit);
	aMeal.calories = calories;
	return aMeal;
};

/*
	Function 4: View food-calorie chart
	This function displays the food, its quantity, unit, and calorie count
	Precondition: option must be a single character
	@param aMeal - struct that holds a meal's name, quantity in certain units, and calorie count
	@param option is either N for next display or X for exit
*/
void ViewCalorie(mealType aMeal)
{
	int a = 0;
	printf("		Food			Quantity	Unit	Calories");
	while(a < 10)
	{
		printf("%s		%f		%s		%f\n", aMeal[a].food, aMeal[a].quantity, aMeal[a].unit, aMeal[a].calories);
		a++;
	}
	printf("View next 10 items? Press 'N' to proceed; press 'X' to exit.\n")
	while(option != 'X')
	{
		while(a % 10 != 0)
		{
			printf("%s		%f		%s		%f\n", aMeal[a].food, aMeal[a].quantity, aMeal[a].unit, aMeal[a].calories);
			a++;
		}
		printf("View next 10 items? Press 'N' to proceed; press 'X' to exit.\n")
		scanf(" %c", option);
	}
}

/*
	Function 5: Save Calorie Info
	This function checks for user's password
	Precondition: 
	@param food
	@param quantity
	@param unit
	@param calories
	@param aMeal - struct that holds a meal's name, quantity in certain units, and calorie count
*/
void SaveCalorie(mealType aMeal)
{
	FILE *fp;
	fp = fopen("Food-calorie information.txt", "a");
	fprintf(fp, "%s\n", aMeal.food);
	fprintf(fp, "%f ", aMeal->quantity);
	fprintf(fp, "%s ", aMeal.unit);
	fprintf(fp, "%f\n\n", aMeal->calories);
	fclose(fp);
}

/*
	Function 6: Load Calorie Info
	This function checks for user's password
	Precondition: option must be a single character
	@param aMeal - struct that holds a meal's name, quantity in certain units, and calorie count
*/
void LoadCalorie(mealType aMeal)
{
	FILE *fp;
	fp = fopen("Food-calorie information.txt", "r");
	fprintf(fp, "%s\n", aMeal.food);
	fprintf(fp, "%f ", aMeal->quantity);
	fprintf(fp, "%s ", aMeal.unit);
	fprintf(fp, "%f\n\n", aMeal->calories);
	fclose(fp);
}

/*
	Function 7: Add Recipe
	This function checks for user's menu input
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void AddRecipe(string dish, string class, int servings, string steps[])
{
	
}

/*
	Function 8: Add Ingredient
	This function checks for user's menu input
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void ModifyIngredient(string ingredientList[])
{
	
}

/*
	Function 9: Add Step
	This function checks for user's menu input
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void ModifyStep(string instructions[])
{
	
}

/*
	Function 10: Modify Recipe
	This function checks for user's password
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void ModifyRecipe(char option)
{
	while(option != 'X')
	{
		
	}
}

/*
	Function 11: Delete Recipe
	This function deletes a recipe from the repository
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void DeleteRecipe(recipeType aRecipe)
{
	int a = 0, i;
	int delete = A[Search(key, A, *pElem)];
	while(a < *pElem)
	{
		if(A[a] == delete)
		{
			if(a < *pElem - 1)
			{
				for(i = a; i < *pElem - 1; i++)
					A[i] = A[i + 1];
			}
			(*pElem)--;
		}
		else
			a++;
	}
}

/*
	Function 12: Display Recipe Titles
	This function checks for user's password
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void DisplayRecipeTitles(string )
{
	
}

/*
	Function 13: Display Full Recipes
	This function checks for user's password
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void DisplayRecipes(string )
{
	
}

/*
	Function 14: Search Recipe by Title
	This function searches a recipe according to its name
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void SearchByTitle(string )
{
	
}

/*
	Function 15: Export Recipes
	This function checks for user's password
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void ExportRecipes(string )
{
	
}

/*
	Function 16: Import Recipes
	This function checks for user's password
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void ImportRecipes(string )
{
	
}

/*
	Function 17: Scan Recipes
	This function checks for user's password
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void ScanRecipe(string )
{
	
}

/*
	Function 18: Search Recipe by Ingredient
	This function searches a recipe according to its ingredient
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void ShoppingList(string )
{
	
}

/*
	Function 19: Generate Shopping List
	This function randomizes a shopping list for the user
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void RecommendMenu(string )
{
	
}

/*
	Function 20: Recommend Menu
	This function searches a recipe according to its ingredient
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void SearchByIngredient(string )
{
	
}

int main()
{
	char main_option;
	int box_option;
	int i, n = 0;
	string username, password;
	string sUsername, sPassword;
	strcpy(sUsername, "admin");
	strcpy(sPassword, "ad1234");
	printf("******************Main Menu******************\n");
	printf("[U] Update recipe box\n");
	printf("[A] Access recipe box\n");
	printf("[E] Exit\n");
	printf("\nChoose a menu option from A-E: ");
	scanf("%c", &option);
	while(main_option != 'E')
	{
		if(main_option == 'U')
		{
			printf("Username: ")
			scanf("%s", username);
			printf("Password: ")
			scanf("%s", password);
			while(box_option != 0)
			{
				printf("[1] Add food-calorie info\n");
				printf("[2] View food-calorie chart\n");
				printf("[3] Save calorie info\n");
				printf("[4] Load calorie info\n");
				printf("[5] Add recipe\n");
				printf("[6] Modify recipe\n");
				printf("[7] Delete recipe\n");
				printf("[8] List recipe titles\n");
				printf("[9] Display recipes\n");
				printf("[10] Search recipe by title\n");
				printf("[11] Export recipes\n");
				printf("[12] Import recipes\n");
				printf("[13] Change username and/or password\n");
				printf("[0] Return to main menu\n");
				
				if(box_option == 1)
				{
					printf("Food item: ");
					scanf("%s", aMeal[a]->food);
					printf("Quantity: ");
					scanf("%f", &aMeal[a]->quantity);
					printf("Unit: ");
					scanf("%s", aMeal[a]->unit);
					printf("Calorie amount: ");
					scanf("%f", &aMeal[a]->calories);

				}
				else if(box_option == 2)
					
				else if(box_option == 3)
					
				else if(box_option == 4)
					
				else if(box_option == 5)
					
				else if(box_option == 6)
					
				else if(box_option == 7)
					
				else if(box_option == 8)
					
				else if(box_option == 9)
					
				else if(box_option == 10)
					
				else if(box_option == 11)
					
				else if(box_option == 12)
					
				else if(box_option == 13)
					
			}
		}
		else if(main_option == 'A')
		{
			do
			{
				printf("[1] Import recipes\n");
				printf("[2] List recipe titles\n");
				printf("[3] Display recipes\n");
				printf("[4] Scan recipes by ingredient\n");
				printf("[5] Generate shopping list\n");
				printf("[6] Recommend menu\n");
				printf("[0] Return to main menu\n");
				
				if(box_option == 1)
					
				else if(box_option == 2)
					
				else if(box_option == 3)
					
				else if(box_option == 4)
					
				else if(box_option == 5)
					
				else if(box_option == 6)
					
			}while(box_option != 0);
		}
		else if(main_option != 'U' && main_option != 'A' && main_option != 'E')
			printf("Invalid option.");
		printf("\nChoose a menu option: ");
		scanf(" %c", &main_option);
	}
	return 0;
}
