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

struct ingredientTag
{
	string food;
	float quantity;
	string unit;
	float calories;
};
typedef struct ingredientTag ingredientType;

struct recipeTag
{
	string name;
	string class;
	int servings;
	float calorie_total;
	ingredientType items[MAX];
	int numIngredients;
	string steps[MAX];
	int numSteps;
};
typedef struct recipeTag recipeType;

/*
	Helper Function 1: Alphabetical Organizer
	This function organizes the recipe list in increasing alphabetical order
	Precondition: 
	@param aRecipes[] - list of recipes
*/
void AlphabeticalSort(recipeType aRecipes[])
{
	int i, j, min;
	recipeType temp;
	for(i = 0; i < n; i++)
	{
		min = i;
		for(j = i; j < n; j++)
		{
			if(strcmp(aRecipes[min].name, aRecipes[j].name) > 0)
				min = j;
		}
		if(i != min)
		{
			temp = aRecipes[i];
			aRecipes[i] = aRecipes[min];
			aRecipes[min] = temp;
		}
	}
}

/*
	Helper Function 2: Search
	This function organizes the recipe list in increasing alphabetical order
	Precondition: 
	@param aRecipes[] - list of recipes
	@param recipeTitle - recipe the user is trying to find
	@param n - number of recipes
*/
int Search(string list[], string key, int n)
{
	int i, index = -1;
	for(i = 0; i < n; i++)
	{
		if(strcmp(list[i], key) == 0)
			index = i;
	}
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
			scanf("%[^\n]", old_password)
			printf("New username: ")
			scanf("%[^\n]", new_username)
		}
		else if(option == 'P')
		{
			printf("Old password: ")
			scanf("%[^\n]", old_password)
			printf("New password: ")
			scanf("%[^\n]", new_password)
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
	Function 3: Add food-calorie info / ingredient
	This function adds the info of a food item to struct meal
	Precondition: 
	@param food - food item input
	@param quantity - quantity input
	@param unit - unit input
	@param calories - calorie input
	@returns contents of temporary struct
*/
ingredientType AddIngredient(string food, float quantity, string unit, float calories)
{
	ingredientType ingredient;
	strcpy(ingredient.food, food);
	ingredient.quantity = quantity;
	strcpy(ingredient.unit, unit);
	ingredient.calories = calories;
	return ingredient;
};

/*
	Function 4: View food-calorie chart
	This function displays the food, its quantity, unit, and calorie count
	Precondition: option must be a single character
	@param ingredient - struct that holds a food item's name, quantity in certain units, and calorie count
*/
void ViewCalorie(ingredientType ingredient[])
{
	int a = 0;
	char option;
	printf("		Food			Quantity	Unit	Calories");
	while(a < 10)
	{
		printf("%s\t\t%f\t\t%s\t\t%f\n", ingredient[a].food, ingredient[a].quantity, ingredient[a].unit, ingredient[a].calories);
		a++;
	}
	printf("View next 10 items? Press 'N' to proceed; press 'X' to exit.\n")
	scanf(" %c", &option);
	while(option != 'X')
	{
		while(a % 10 != 0)
		{
			printf("%s\t\t%f\t\t%s\t\t%f\n", ingredient[a].food, ingredient[a].quantity, ingredient[a].unit, ingredient[a].calories);
			a++;
		}
		printf("View next 10 items? Press 'N' to proceed; press 'X' to exit.\n")
		scanf(" %c", &option);
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
	@param ingredient - struct that holds a food item's name, quantity in certain units, and calorie count
*/
void SaveCalorie(ingredientType ingredient[], int *numRecipes)
{
	FILE *CalText;
	int a;
	printf("******* Save Food-Calorie Info *******\n");
	printf("Save data to what file? ");
	scanf("%[^\n]", CalText);
	if(fopen(CalText, "w") != NULL)
	{
		for(a = 0; a < *numRecipes; a++)
		{
			fprintf(CalText, "%s\n", ingredient[a].food);
			fprintf(CalText, "%f ", ingredient[a]->quantity);
			fprintf(CalText, "%s ", ingredient[a].unit);
			fprintf(CalText, "%f\n\n", ingredient[a]->calories);
		}
		fclose(CalText);
	}
	else
		printf("Error loading file. Please try again.\n");
}

/*
	Function 6: Load Calorie Info
	This function loads a food item's calorie info
	Precondition: 
	@param ingredient - struct that holds a meal's name, quantity in certain units, and calorie count
*/
void LoadCalorie(ingredientType ingredient)
{
	FILE *CalText;
	printf("******* Load Food-Calorie Info *******\n");
	printf("Load data from what file? ");
	scanf("%[^\n]", CalText);
	if(fopen(CalText, "r") != NULL)
	{
		fprintf(CalText, "%s\n", ingredient.food);
		fprintf(CalText, "%f ", ingredient.quantity);
		fprintf(CalText, "%s ", ingredient.unit);
		fprintf(CalText, "%f\n\n", ingredient.calories);
		fclose(CalText);
	}
	else
		printf("Error loading file. Please try again.\n");
}

/*
	Function 7: Add Recipe
	This function checks for user's menu input
	Precondition: option must be a single character
	@param dish
	@param class
	@param servings
	@param ingredient
	@param step
*/
recipeType AddRecipe(string dish, string class, int servings, ingredientType ingredient, string step)
{
	recipeType aRecipe;
	strcpy(aRecipe.dish, dish);
	strcpy(aRecipe.class, class);
	aRecipe.servings = servings;
	aRecipe.items = ingredient;
	strcpy(aRecipe.step, step);
	return aRecipe;
}

/*
	Function 8: Delete Ingredient
	This function checks for user's menu input
	Precondition: option must be a single character
	@param food - food item input
	@param quantity - quantity input
	@param unit - unit input
	@param calories - calorie input
	@returns contents of temporary struct
*/
ingredientType DeleteIngredient(recipeType aRecipe, ingredientType ingredient, int *numItems)
{
	int a = 0, i;
	string delete = items[Search(aRecipe.items.food, ingredient.food, *numItems)];
	while(a < *numItems)
	{
		if(strcmp(delete, ) == 0)
		{
			if(a < *numItems - 1)
			{
				for(i = a; i < *pElem - 1; i++)
					A[i] = A[i + 1];
			}
			(*numItems)--;
		}
		else
			a++;
	}
}

/*
	Function 9: Add Step
	This function adds a step to a recipe
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void AddStep(recipeType aRecipe, string aStep)
{
	strcpy(aRecipe.steps[aRecipe.numSteps], aStep);
}

/*
	Function 10: Delete Step
	This function deletes a step to a recipe
	Precondition: 
	@param option is the user's input into the menu items
*/
void DeleteStep(recipeType aRecipe, string aStep, int *numSteps)
{
	int a = 0, i;
	int delete = aRecipe.steps[Search(aRecipe.steps, aStep, *numSteps)];
	while(a < *numSteps)
	{
		if(aRecipe.steps[a] == delete)
		{
			if(a < *numSteps - 1)
			{
				for(i = a; i < *numSteps - 1; i++)
					aRecipe.steps[i] = aRecipe.steps[i + 1];
			}
			(*numSteps)--;
		}
		else
			a++;
	}
}

/*
	Function 11: Delete Recipe
	This function deletes a recipe from the repository
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void DeleteRecipe(recipeType aRecipes[], string recipeTitle, int *numRecipes)
{
	int a = 0, i;
	int delete = A[Search(key, A, *pElem)];
	while(a < *pElem)
	{
		if(strcmp(aRecipes[a], recipeTitle) == 0)
		{
			if(a < *pElem - 1)
			{
				for(i = a; i < *pElem - 1; i++)
					A[i] = A[i + 1];
			}
			(*numRecipes)--;
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
void DisplayRecipeTitles(recipeType aRecipes[], int *numRecipes)
{
	int i;
	printf("********* List of Recipes *********\n");
	for(i = 0; i < *numRecipes; i++)
		printf("%s\n", aRecipes[i].name);
}

/*
	Function 13: Scan Recipes
	This function checks for user's password
	Precondition: option must be a single character
	@param aRecipe - recipe struct
*/
void DisplayRecipe(recipeType aRecipe)
{
	int i, j;
	printf("%s		%d		%f\n", aRecipe.name, aRecipe.servings, aRecipe.calorie_total);
	printf("Ingredients:\n");
	for(i = 0; i < aRecipe.numIngredients; i++)
		printf("%f %s %s		%f\n", aRecipe.items[i].quantity, aRecipe.items[i].unit, aRecipe.items[i].food, aRecipe.items[i].calorie);
	printf("Procedure:\n");
	for(j = 0; j < aRecipe.numSteps; j++)
		printf("%d. %s\n", j + 1, steps[j]);
}

/*
	Function 14: Search Recipe by Title
	This function searches a recipe by its title
	Precondition: 
	@param aRecipes[] - list of recipes
	@param recipeTitle - recipe the user is trying to find
	@param n - number of recipes
*/
void SearchByTitle(recipeType aRecipes[], string recipeTitle, int *numRecipes)
{
	printf("********** Recipe Search **********\n");
	DisplayRecipeTitles(aRecipes, *numRecipes);
	int index = Search(aRecipes, recipeTitle, *numRecipes);
	if(index > -1)
		DisplayRecipe(aRecipes[index]);
	else if(index == -1)
		printf("Recipe not found.\n");
}

/*
	Function 15: Export Recipes
	This function checks for user's password
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void ExportRecipes(recipeType aRecipes[], int *numRecipes)
{
	FILE *RecipeList;
	int a, i, j;
	printf("Save data to what file? ");
	scanf("%[^\n]", RecipeList);
	for(a = 0; a < *numRecipes; a++)
	{
		RecipeList = fopen(" ", "w");
		fprintf(RecipeList, "%s\n", aRecipes[a].name);
		fprintf(RecipeList, "%f ", aRecipes[a]->quantity);
		fprintf(RecipeList, "%s ", aRecipes[a].unit);
		fprintf(RecipeList, "%f\n\n", aRecipes[a]->calories);
		fprintf("Ingredients:\n");
		for(i = 0; i < aRecipes[a].numIngredients; i++)
			fprintf("%f %s %s\t\t%f\n", aRecipes[a].items[i].quantity, aRecipes[a].items[i].unit, aRecipes[a].items[i].food, aRecipes[a].items[i].calorie);
		fprintf("Steps:\n");
		for(j = 0; j < aRecipes[a].numSteps; j++)
			fprintf("%d. %s\n", j + 1, aRecipes[a].steps[j]);
	}
	fclose(RecipeList);
}

/*
	Function 16: Import Recipes
	This function checks for user's password
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void ImportRecipes(recipeType aRecipes[], int *numRecipes)
{
	FILE *RecipeList;
	int a;
	printf("Load data from what file? ");
	scanf("%[^\n]", RecipeList);
	for(a = 0; a < *numRecipes; a++)
	{
		RecipeList = fopen(" ", "r");
		fprintf(RecipeList, "%s\n", aRecipes[a].name);
		fprintf(RecipeList, "%f ", aRecipes[a].quantity);
		fprintf(RecipeList, "%s ", aRecipes[a].unit);
		fprintf(RecipeList, "%f\n\n", aRecipes[a]->calories);
		fprintf("Ingredients:\n");
		for(i = 0; i < aRecipes[a].numIngredients; i++)
			fprintf("%f %s %s\t\t%f\n", aRecipes[a].items[i].quantity, aRecipes[a].items[i].unit, aRecipes[a].items[i].food, aRecipes[a].items[i].calorie);
		fprintf("Steps:\n");
		for(j = 0; j < aRecipes[a].numSteps; j++)
			fprintf("%d. %s\n", j + 1, aRecipes[a].steps[j]);
	}
	fclose(RecipeList);
}

/*
	Function 17: Search Recipe by Ingredient
	This function searches a recipe according to its ingredient
	Precondition: option must be a single character
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes
	@param fooditem - user-inputted ingredient
	@param savedRecipes[] - list of recipes that have searched ingredient
*/
void SearchByIngredient(recipeType aRecipes[], int *numRecipes, string fooditem, recipeType savedRecipes[])
{
	int a, i, found, save = 0;
	for(a = 0; a < *numRecipes; a++)
	{
		found = 0;
		for(i = 0; i < aRecipes[a].numIngredients; i++)
		{
			if(strcmp(aRecipes[a].items[i].food, fooditem) == 0)
				found++;
		}
		if(found > 0)
		{
			savedRecipes[save] = aRecipes[a];
			save++;
		}
	}
}

/*
	Function 18: Generate Shopping List
	This function randomizes a shopping list for the user
	Precondition: option must be a single character
	@param aRecipes[] - list of recipes
	@param 
*/
void ShoppingList(recipeType aRecipes[], int *numRecipes)
{
	int num, index;
	string recipe;
	printf("********* Generate Shopping List *********\n");
	DisplayRecipeTitles(aRecipes);
	printf("Choose recipe: ")
	scanf("%[^\n]", title);
	index = Search(aRecipes->name, recipe, &numRecipes);
	printf("Enter number of people: ");	
	scanf(" %d", num);
	printf("List of ingredients for %s:\n", aRecipes[index].name);
	printf(" ");
}

/*
	Function 19: Recommend Menu
	This function searches a recipe according to its ingredient
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void RecommendMenu(recipeType aRecipes[], int *numRecipes, float calorie_goal)
{
	int index = Search(aRecipes, "Lunch", *numRecipes);
	if(calorie_goal == aRecipes[index].calorie_total)
	{
		
	}
	else
	{
		
	}
}

int main()
{
	char main_option;
	int box_option, recipe_option;
	int a = 0;	// calorie_info
	int i, n = 0;
	string username, password;
	string sUsername, sPassword;
	strcpy(sUsername, "admin");
	strcpy(sPassword, "ad1234");
	string food, unit;
	float quantity, calories;
	mealType calorie_info;
	string dish, class, ingredients[MAX], procedure[];
	int servings;
	srand(time(NULL));
	
	printf("******************** Main Menu ********************\n");
	printf("[U] Update recipe box\n");
	printf("[A] Access recipe box\n");
	printf("[E] Exit\n");
	printf("\nChoose a menu option from A-E: ");
	scanf(" %c", &option);
	while(main_option != 'E')
	{
		if(main_option == 'U')
		{
			printf("Username: ")
			scanf("%[^\n]", username);
			printf("Password: ")
			scanf("%[^\n]", password);
			while(box_option != 0)
			{
				printf("************** Update Recipe Box **************\n");
				printf("[0] Return to main menu\n");
				printf("[1] Add food-calorie info\n");
				printf("[2] View food-calorie chart\n");
				printf("[3] Save calorie info\n");
				printf("[4] Load calorie info\n");
				printf("[5] Add recipe\n");
				printf("[6] Modify recipe\n");
				printf("[7] Delete recipe\n");
				printf("[8] List recipe titles\n");
				printf("[9] Scan recipes\n");
				printf("[10] Search recipe by title\n");
				printf("[11] Export recipes\n");
				printf("[12] Import recipes\n");
				printf("[13] Change username and/or password\n");
				printf("Choose an update option from 0-13: ");
				scanf(" %d", box_option);
				
				if(box_option == 1)
				{
					printf("******* Add Food-Calorie Info *******\n");
					printf("Food item: ");
					scanf("%[^\n]", food);
					printf("Quantity: ");
					scanf(" %f", &quantity);
					printf("Unit: ");
					scanf("%[^\n]", unit);
					printf("Calorie amount: ");
					scanf(" %f", &calories);
					calorie_info[a] = AddCalorie(food, quantity, unit, calories);
					a++;
				}
				else if(box_option == 2)
				{
					printf("******** Food-Calorie Chart ********\n");
					if(a == 0)
						printf("No data to view.\n");
					else
						ViewCalorie(calorie_info[a]);
				}
				else if(box_option == 3)
					
				else if(box_option == 4)
					
				else if(box_option == 5)
					
				else if(box_option == 6)
				{
					do
					{
						printf("************** Modify Recipe **************\n");
						printf("[0] Return to update menu\n");
						printf("[1] Add ingredient\n");
						printf("[2] Delete ingredient\n");
						printf("[3] Add step\n");
						printf("[4] Delete step\n");
						printf("Choose what to modify from 0-4: ");
						scanf(" %d", recipe_option);
						if(recipe_option == 1)
							
						else if(recipe_option == 2)
							
						else if(recipe_option == 3)
							
						else if(recipe_option == 4)
							
					}while(recipe_option != 0);
				}
				else if(box_option == 7)
					
				else if(box_option == 8)
					
				else if(box_option == 9)
				{
					printf("*********** Scan Recipes ***********\n");
					do
					{
						
					}while();
				}
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
				printf("[0] Return to main menu\n");
				printf("[1] Import recipes\n");
				printf("[2] List recipe titles\n");
				printf("[3] Display recipes\n");
				printf("[4] Scan recipes by ingredient\n");
				printf("[5] Generate shopping list\n");
				printf("[6] Recommend menu\n");
				printf("Choose an access option from 0-6: ");
				scanf(" %d", box_option);
				
				if(box_option == 1)
					
				else if(box_option == 2)
					
				else if(box_option == 3)
					
				else if(box_option == 4)
					
				else if(box_option == 5)
					
				else if(box_option == 6)
				{
					printf("******* Menu Recommendation *******\n");
					
				}
			}while(box_option != 0);
		}
		else if(main_option != 'U' && main_option != 'A' && main_option != 'E')
			printf("Invalid option.");
		printf("\nChoose a menu option: ");
		scanf(" %c", &main_option);
	}
	return 0;
}

