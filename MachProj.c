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

typedef char string[100];

struct meal
{
	string food;
	float quantity;
	string unit;
	float calories;
};

void swap(candidateType *aCandidate, candidateType *bCandidate)
{
	candidateType temp;
	temp = *aCandidate;
	*aCandidate = *bCandidate;
	*bCandidate = temp;
}

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
			temp = *aCandidate;
			*aCandidate = *bCandidate;
			*bCandidate = temp;
		}
	}
}

/*
	Helper Function 2: Search
	This function organizes the recipe list in increasing alphabetical order
	Precondition: 
	@param option is the user's input into the menu items
*/
void Search()
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
	Function 1: Password Changer???
	This function changes the user's username and password
	Precondition: 
	@param option is the user's input into the menu items
	@returns 0, 1, 2, or 3 depending on what menu option matches the user's
*/
int MenuCheck(char option)
{
	
}

/*
	Function 2: Password Checker
	This function checks for user's password
	Precondition: option must be a single character
	@param option is the user's input into the menu items
	@returns 0 or 1 depending on whether or not the password matches
*/
int PassCheck(string password)
{
	
}

/*
	Function 3: Add Food Calorie Info
	This function 
	Precondition: 
	@param option is the user's input into the menu items
*/
void AddCalorie(string food, float quantity, string unit, float calories)
{
	
}

/*
	Function 4: View Calorie Info
	This function displays the food, its quantity, unit, and calorie count
	Precondition: option must be a single character
	@param food
	@param quantity
	@param unit
	@param calories
	@param option is either N for next display or X for exit
*/
void ViewCalorie(string food, float quantity, string unit, float calories, char option)
{
	while(option != 'X')
	{
		do
		{
			
		}while();
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
*/
void SaveCalorie(string food, float quantity, string unit, float calories)
{
	
}

/*
	Function 6: Load Calorie Info
	This function checks for user's password
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void LoadCalorie(string password)
{
	
}

/*
	Function 7: Add Recipe
	This function checks for user's menu input
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void AddRecipe(string dish, string class, int servings, )
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
	This function checks for user's password
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void DeleteRecipe(string dish)
{
	if(
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
	char option, key, garbage;
	int i, n = 0;
	candidateType candidate[20];
	printf("******************Main Menu******************\n");
	printf("U - Update recipe box\n");
	printf("A - Access recipe box\n");
	printf("E - Exit\n");
	printf("\nChoose a menu option from A-E: ");
	scanf("%c", &option);
	while(option != 'E')
	{
		if(option == 'U')
		{
			
		}
		else if(option == 'A')
		{
			
		}
		else if(option != 'U' && option != 'A' && option != 'E')
			printf("Invalid option.");
		printf("\nChoose a menu option: ");
		scanf(" %c", &option);
	}
	return 0;
}