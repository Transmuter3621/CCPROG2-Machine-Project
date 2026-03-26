/***************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the
concepts learned. I have constructed the functions and their respective algorithms and corresponding code by
myself. The program was run, tested, and debugged by my own efforts. I further certify that I have not copied in
part or whole or otherwise plagiarized the work of other students and/or persons.
Eryn Claire Go Sy, DLSU ID# 12506621
***************************************************************************/

/*
	Description: This program is a meal repository with access and modification features on the recipes,
	as well as having a shopping list generator and a menu recommendation function.
	Programmed by: Sy, Eryn Claire Go, S21B
	Last modified: March 30, 2026
	Version: 
	[Acknowledgements: <stdio.h>, <stdlib.h>, <string.h>, <time.h>]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50		// recipes and food items
#define MAX_INGREDIENTS 20
#define MAX_STEPS 15
/* For RecommendMenu
   Maximum combinations of 1, 2, or 3 recipe classes in 50 recipes
   Spilt 50 evenly: 17, 17, 16
   1 recipe: 50
   2 recipes: (17 * 17) + (17 * 16) + (17 * 16) = 833
   3 recipes: 17 * 17 * 16 = 4624
   Total: 5507
*/
#define MAX_RECIPESETS 5507

typedef char string[21];
typedef char string_unit[16];
typedef char string_step[71];

struct ingredientTag
{
	string food;
	float quantity;
	string_unit unit;
	float calories;
};
typedef struct ingredientTag ingredientType;

struct recipeTag
{
	string name;
	string class;
	int servings;
	float calorie_total;
	ingredientType items[MAX_INGREDIENTS];
	int numIngredients;
	string_step steps[MAX_STEPS];
	int numSteps;
};
typedef struct recipeTag recipeType;

/*
	Helper Function 1: Alphabetical Organizer
	This function organizes the recipe list in increasing alphabetical order
	Precondition: all recipe info is valid
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes
*/
void AlphabeticalSort(recipeType aRecipes[], int *numRecipes)
{
	int i, j, min;
	recipeType temp;
	for(i = 0; i < *numRecipes; i++)
	{
		min = i;
		for(j = i; j < *numRecipes; j++)
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
	Helper Function 2: Search recipe title
	This function searches for a recipe title in an array of recipes
	Precondition: all recipe info is valid
	@param aRecipes[] - list of recipes
	@param recipeTitle - recipe name the user is trying to find
	@param numRecipes - number of recipes
	@return index of recipe array where recipe was found or -1 if not found
*/
int SearchName(recipeType aRecipes[], int *numRecipes, string recipeTitle)
{
	int i, index = -1;
	for(i = 0; i < *numRecipes; i++)
	{
		if(strcmp(aRecipes[i].name, recipeTitle) == 0)
			index = i;
	}
	return index;
}

/*
	Helper Function 3: Calorie matcher
	This function matches the amount of calories of the ingredients in a recipe
	Precondition: all entries in aRecipes and food_info are complete
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes
	@param food_info - struct that holds a food item's name, quantity in certain units, and calorie count
	@param food_count - number of existing food items
*/
void CalorieMatcher(recipeType aRecipes[], int *numRecipes, ingredientType food_info[], int *food_count)
{
	int a, i, f;
	for(a = 0; a < *numRecipes; a++)
	{
		aRecipes[a].calorie_total = 0;
		for(i = 0; i < aRecipes[a].numIngredients; i++)
		{
			aRecipes[a].items[i].calories = 0;
			for(f = 0; f < *food_count; f++)
			{
				if(strcmp(aRecipes[a].items[i].food, food_info[f].food) == 0)
				{
					aRecipes[a].items[i].calories = food_info[f].calories / food_info[f].quantity * aRecipes[a].items[i].quantity;
					aRecipes[a].calorie_total += aRecipes[a].items[i].calories;
				}
			}
		}
	}
}

/*
	Function 1: Username and Password Changer
	This function changes the user's username and/or password
	Precondition: username and password can only be 20 characters max
	@param username - current username
	@param password - current password
*/
void AccessModifier(string username, string password)
{
	string old_username, new_username, old_password, new_password;
	char option, garbage;
	printf("What will you change? Press U for username, P for password, or X for exit. ");
	scanf("%c", &option);
	scanf("%c", &garbage);
	while(option != 'X')
	{
		if(option == 'U')
		{
			printf("Old username: ");
			scanf("%[^\n]", old_username);
			scanf("%c", &garbage);
			if(strcmp(old_username, username) == 0)
			{
				printf("New username: ");
				scanf("%[^\n]", new_username);
				scanf("%c", &garbage);
				strcpy(username, new_username);
			}
			else
				printf("Invalid username. Please try again.\n");
		}
		else if(option == 'P')
		{
			printf("Old password: ");
			scanf("%[^\n]", old_password);
			scanf("%c", &garbage);
			if(strcmp(old_password, password) == 0)
			{
				printf("New password: ");
				scanf("%[^\n]", new_password);
				scanf("%c", &garbage);
				strcpy(password, new_password);
			}
			else
				printf("Invalid password. Please try again.\n");
		}
		else
			printf("Invalid input, please try again.\n");
		printf("What will you change? Press U for username, P for password, or X for exit. ");
		scanf(" %c", &option);
	}
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
int PassCheck(string username, string current_username, string password, string current_password)
{
	int check = 0;		// nothing is correct
	if((strcmp(username, current_username) == 0) && (strcmp(password, current_password) != 0))			// correct username
		check = 1;
	else if((strcmp(username, current_username) != 0) && (strcmp(password, current_password) == 0))		// correct password
		check = 2;
	else if((strcmp(username, current_username) == 0) && (strcmp(password, current_password) == 0))		// correct username and password
		check = 3;
	return check;
}

/*
	Function 3: Add food-calorie info
	This function adds the info of a certain food item
	Precondition: quantity can only be a non-negative float
				  quantity and unit are to be inputted with a space between
	@param food_info - struct that holds a food item's name, quantity in certain units, and calorie count
	@return food_info
*/
ingredientType AddFoodCalorie(ingredientType food_info)
{
	char garbage;	// to get rid of leftover \n

	printf("Food item: ");
	scanf("%[^\n]", food_info.food);
	scanf("%c", &garbage);

	printf("Quantity and Unit: ");
	scanf(" %f %s", &food_info.quantity, food_info.unit);
	scanf("%c", &garbage);

	printf("Calorie amount: ");
	scanf(" %f", &food_info.calories);
	scanf("%c", &garbage);

	return food_info;
}

/*
	Function 4: View food-calorie chart
	This function displays the food, its quantity, unit, and calorie count
	Precondition: the number of food items must not exceed 50
	@param food_info - struct that holds a food item's name, quantity in certain units, and calorie count
	@param food_count - number of existing food items
*/
void ViewCalorie(ingredientType food_info[], int *food_count)
{
	int a, b, i = 0, min;
	ingredientType temp;
	char option;
	// Alphabetical sort for food items
	for(a = 0; a < *food_count; a++)
	{
		min = a;
		for(b = a; b < *food_count; b++)
		{
			if(strcmp(food_info[min].food, food_info[b].food) > 0)
				min = b;
		}
		if(a != min)
		{
			temp = food_info[a];
			food_info[a] = food_info[min];
			food_info[min] = temp;
		}
	}
	printf("+--------------------+------------+----------------+------------+\n");
	printf("|        Food        |  Quantity  |      Unit      |  Calories  |\n");
	while(i < *food_count && i < 10)
	{
		printf("|%-20s|%-12.2f|%-16s|%-12.2f|\n", food_info[i].food, food_info[i].quantity, food_info[i].unit, food_info[i].calories);
		i++;
	}
	printf("+--------------------+------------+----------------+------------+\n");
	if(i < *food_count && *food_count > 10)
	{
		printf("View next 10 items? Press 'N' to proceed; press 'X' to exit. ");
		scanf(" %c", &option);
		while(i < *food_count && option != 'X')
		{
			printf("+--------------------+------------+----------------+------------+\n");
			printf("|        Food        |  Quantity  |      Unit      |  Calories  |\n");
			do
			{
				printf("|%-20s|%-12.2f|%-16s|%-12.2f|\n", food_info[i].food, food_info[i].quantity, food_info[i].unit, food_info[i].calories);
				i++;
			} while(i < *food_count && i % 10 != 0);
			printf("+--------------------+------------+----------------+------------+\n");
			if(i < *food_count)
			{
				printf("View next 10 items? Press 'N' to proceed or 'X' to exit. ");
				scanf(" %c", &option);
			}
		}
	}
}

/*
	Function 5: Save Calorie Info
	This function checks for user's password
	Precondition: 
	@param food_info - struct that holds a food item's name, quantity in certain units, and calorie count
	@param numItems - number of ingredients
	@param filename - name of file that will store food-calorie info
*/
void SaveCalorie(string filename, ingredientType food_info[], int *food_count)
{
	FILE *CalText;
	int a;
	if((CalText = fopen(filename, "w")) != NULL)
	{
		for(a = 0; a < *food_count; a++)
		{
			fprintf(CalText, "%s\n", food_info[a].food);
			fprintf(CalText, "%.3f %s ", food_info[a].quantity, food_info[a].unit);
			fprintf(CalText, "%.3f\n\n", food_info[a].calories);
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
	@param filename - name of file that contains food-calorie info
	@param calorie_info - struct that saves the food items
	@param calorie_info_count - number of food items stored in the program (starting point of adding file calorie-info)
*/
void LoadCalorie(string filename, ingredientType calorie_info[], int *calorie_info_count)
{
	int c, unique = -8, start_count = *calorie_info_count;
	ingredientType food_info;
	FILE *CalText;
	char garbage, overwrite;
	if((CalText = fopen(filename, "r")) != NULL)
	{
		while((fscanf(CalText, " %[^\n] %f %s %f ", food_info.food, &food_info.quantity, food_info.unit, &food_info.calories) == 4))
		{
			unique = -1;
			for(c = 0; c < *calorie_info_count; c++)
			{
				if(strcmp(food_info.food, calorie_info[c].food) == 0)
					unique = c;
			}
			if(unique == -1)
			{
				calorie_info[*calorie_info_count] = food_info;
				(*calorie_info_count)++;
			}
			else
			{
				printf("This recipe already exists. Overwrite saved recipe? Y/N ");
				scanf(" %c", &overwrite);
				scanf("%c", &garbage);
				while(overwrite != 'Y' && overwrite != 'y' && overwrite != 'N' && overwrite != 'n')
				{
					printf("Invalid input. Please try again.\n");
					scanf(" %c", &overwrite);
					scanf("%c", &garbage);
				}
				if(overwrite == 'Y' || overwrite == 'y')
					calorie_info[unique] = food_info;
				else if(overwrite == 'N' || overwrite == 'n')
					printf("%s skipped.\n", food_info.food);
			}
		}
		fclose(CalText);
		if(*calorie_info_count == start_count && unique == -8)	// unique == -8 means the function never found appropriate content
			printf("File lacks content.\n");
	}
	else
		printf("Error loading file. Please try again.\n");
}

/*
	Function 7: Add ingredient
	This function gets the input of an ingredient and its quantity
	Precondition: quantity can only be a non-negative float
				  quantity and unit are to be inputted with a space between
	@param ingredient - struct that holds an ingredient's name and quantity in certain units
	@return ingredient which has the ingredient name,  quantity, and unit
*/
ingredientType AddIngredient(ingredientType ingredient)
{
	char garbage;

	printf("Food item: ");
	scanf("%[^\n]", ingredient.food);
	scanf("%c", &garbage);

	printf("Quantity with unit: ");
	scanf("%f %s", &ingredient.quantity, ingredient.unit);
	scanf("%c", &garbage);

	return ingredient;
}

/*
	Function 8: Add Recipe
	This function adds an ingredient to a recipe
	Precondition: dish, class, and step only contain letters in the alphabet
				  class can only be starter, main, or dessert
				  servings must be a positive integer
	@param aRecipe - recipe struct
	@return aRecipe
*/
recipeType AddRecipe(recipeType *aRecipe)
{
	char garbage, option;
	int i = 0, j = 0;
	aRecipe->calorie_total = 0;

	printf("Recipe: ");
	scanf("%[^\n]", aRecipe->name);
	scanf("%c", &garbage);

	printf("Class: ");
	scanf("%[^\n]", aRecipe->class);
	scanf("%c", &garbage);

	printf("Servings: ");
	scanf(" %d", &aRecipe->servings);
	scanf("%c", &garbage);

	printf("Ingredients:\n");
	do
	{
		aRecipe->items[i] = AddIngredient(aRecipe->items[i]);
		i++;
		printf("Continue adding ingredients? Y/N ");
		scanf(" %c", &option);
		scanf("%c", &garbage);
	} while(option == 'Y' || option == 'y');
	aRecipe->numIngredients = i;

	printf("Steps:\n");
	do
	{
		scanf("%[^\n]", aRecipe->steps[j]);
		scanf("%c", &garbage);
		j++;
		printf("Continue adding steps? Y/N ");
		scanf(" %c", &option);
	} while(option == 'Y' || option == 'y');
	aRecipe->numSteps = j;

	return (*aRecipe);
}

/*
	Function 9: Delete Ingredient
	This function deletes an ingredient from a recipe
	Precondition: the name of the ingredient only contains letters in the alphabet
	@param aRecipe - recipe struct
	@param ingredient - ingredient to be deleted
*/
void DeleteIngredient(recipeType *aRecipe, string ingredient)
{
	int a = 0, i;
	string delete;
	if(aRecipe->numIngredients <= 1)
		printf("Cannot delete any more ingredients.\n");
	else
	{
		for(i = 0; i < aRecipe->numIngredients; i++)
		{
			if(strcmp(aRecipe->items[i].food, ingredient) == 0)
			{
				strcpy(delete, aRecipe->items[i].food);
				aRecipe->calorie_total -= aRecipe->items[i].calories;
			}
		}
		while(a < aRecipe->numIngredients)
		{
			if(strcmp(aRecipe->items[a].food, delete) == 0)
			{
				if(a < aRecipe->numIngredients - 1)
				{
					for(i = a; i < aRecipe->numIngredients - 1; i++)
						aRecipe->items[i] = aRecipe->items[i + 1];
				}
				(aRecipe->numIngredients)--;
			}
			else
				a++;
		}
	}
}

/*
	Function 10: Add Step
	This function adds a step to a recipe
	Precondition: step contains at most 70 characters
	@param aRecipe - recipe struct
	@param step_insert - step number (not index) where new step will be inserted
	@param step - step to be added
*/
void AddStep(recipeType *aRecipe, int step_insert, string_step step)
{
	int a;
	if(step_insert > MAX_STEPS)
		printf("Step count has exceeded limit.\n");
	else
	{
		while(step_insert > aRecipe->numSteps)
			printf("Invalid placement. Please try again: ");
		aRecipe->numSteps++;
		for(a = step_insert; a < aRecipe->numSteps; a++)		// step_insert is the index of the step after the one that will be inserted
			strcpy(aRecipe->steps[a], aRecipe->steps[a + 1]);
		step_insert--;	// step array starts at 0 but step list starts at 1 so decrement to go to actual index
		strcpy(aRecipe->steps[step_insert], step);
	}
}

/*
	Function 11: Delete Step
	This function deletes a step to a recipe
	Precondition: step contains at most 70 characters
	@param aRecipe - recipe struct
	@param step_remove - step number (not index) to be deleted
*/
void DeleteStep(recipeType *aRecipe, int step_remove)
{
	int a = 0, i;
	if(aRecipe->numSteps == 1)
		printf("Cannot delete any more steps.\n");
	else
	{
		while(step_remove > aRecipe->numSteps || step_remove < 1)
			printf("Invalid step number.\n");
		step_remove--;
		while(a < aRecipe->numSteps)
		{
			if(a == step_remove)
			{
				if(a < aRecipe->numSteps - 1)
				{
					for(i = a; i < aRecipe->numSteps - 1; i++)
						strcpy(aRecipe->steps[i], aRecipe->steps[i + 1]);
				}
				(aRecipe->numSteps)--;
			}
			else
				a++;
		}
	}
}

/*
	Function 12: Delete Recipe
	This function deletes a recipe from the repository
	Precondition: recipeTitle contains 20 characters at most
	@param aRecipe - recipe struct
	@param recipeTitle - name of recipe to be deleted
	@param numRecipes - number of recipes
*/
void DeleteRecipe(recipeType aRecipes[], int *numRecipes, string recipeTitle)
{
	int a = 0, i;
	int delete = SearchName(aRecipes, numRecipes, recipeTitle);
	if(delete == -1)
		printf("Recipe not found. ");
	else
	{
		while(a < *numRecipes)
		{
			if(strcmp(aRecipes[a].name, aRecipes[delete].name) == 0)
			{
				if(a < *numRecipes - 1)
				{
					for(i = a; i < *numRecipes - 1; i++)
						aRecipes[i] = aRecipes[i + 1];
				}
				(*numRecipes)--;
			}
			else
				a++;
		}
	}
}

/*
	Function 13: Display Recipe Titles
	This function checks for user's password
	Precondition: 
	@param aRecipe - recipe struct
	@param numRecipes - number of recipes
*/
void DisplayRecipeTitles(recipeType aRecipes[], int *numRecipes)
{
	int i;
	AlphabeticalSort(aRecipes, numRecipes);
	for(i = 0; i < *numRecipes; i++)
		printf("%s\n", aRecipes[i].name);
}

/*
	Function 14: Display Recipe
	This function displays one recipe's details
	Precondition: 
	@param aRecipe - recipe struct
*/
void DisplayRecipe(recipeType aRecipe)
{
	int i, j;
	printf("%-20s\t\t%-8d\t\t%.2f\n", aRecipe.name, aRecipe.servings, aRecipe.calorie_total);
	printf("Ingredients:\n");
	for(i = 0; i < aRecipe.numIngredients; i++)
		printf("%-12.2f %-15s %-20s %.2f\n", aRecipe.items[i].quantity, aRecipe.items[i].unit, aRecipe.items[i].food, aRecipe.items[i].calories);
	printf("\nProcedure:\n");
	for(j = 0; j < aRecipe.numSteps; j++)
		printf("%d. %s\n", j + 1, aRecipe.steps[j]);
	printf("\n");
}

/*
	Function 15: Search Recipe by Title
	This function searches a recipe by its title
	Precondition: recipeTitle contains 20 characters at most
	@param aRecipes[] - list of recipes
	@param recipeTitle - recipe the user is trying to find
	@param numRecipes - number of recipes
*/
void SearchByTitle(recipeType aRecipes[], int *numRecipes, string recipeTitle)
{
	DisplayRecipeTitles(aRecipes, numRecipes);
	int index = SearchName(aRecipes, numRecipes, recipeTitle);
	if(index > -1)
		DisplayRecipe(aRecipes[index]);
	else if(index == -1)
		printf("Recipe not found.\n");
}

/*
	Function 16: Export Recipes
	This function saves the current list of recipes in the user's text file of choice (if it's found)
	Precondition: recipeTitle contains 20 characters at most
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes
	@param filename - name of file that will contain all recipes made at the time
*/
void ExportRecipes(recipeType aRecipes[], int *numRecipes, string filename)
{
	FILE *RecipeList;
	int a, i, j;
	if((RecipeList = fopen(filename, "w")) != NULL)
	{
		for(a = 0; a < *numRecipes; a++)
		{
			fprintf(RecipeList, "%s\n", aRecipes[a].name);
			fprintf(RecipeList, "%d %s\n", aRecipes[a].servings, aRecipes[a].class);
			fprintf(RecipeList, "Ingredients %d\n", aRecipes[a].numIngredients);
			for(i = 0; i < aRecipes[a].numIngredients; i++)
				fprintf(RecipeList, "%f %s %s\n", aRecipes[a].items[i].quantity, aRecipes[a].items[i].unit, aRecipes[a].items[i].food);
			fprintf(RecipeList, "Steps:\n");
			for(j = 0; j < aRecipes[a].numSteps; j++)
				fprintf(RecipeList, "%s\n", aRecipes[a].steps[j]);
			fprintf(RecipeList, "\n");
		}
		fclose(RecipeList);
	}
	else
		printf("Error loading file. Please try again.\n");
}

/*
	Function 17: Import Recipes
	This function loads a list of recipes from the user's inputted text file (if it's found)
	Precondition: recipeTitle contains 20 characters at most
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes (starting point of recipe adding)
	@param filename - name of file user will load recipes from
*/
void ImportRecipes(recipeType aRecipes[], int *numRecipes, string filename)
{
	FILE *RecipeList;
	int a, scan_check, i, j, ingredient_scan, step_scan, unique = -8, start_recipes = *numRecipes;
	recipeType recipe;
	char garbage, word[12];		// to scan leftover \n, "Ingredients", and "Steps"
	char overwrite;
	if((RecipeList = fopen(filename, "r")) != NULL)
	{
		do
		{
			scan_check = 0;
			if(fscanf(RecipeList, " %[^\n] %d %s %s %d", recipe.name, &recipe.servings, recipe.class, word, &recipe.numIngredients) == 5)
			{
				scan_check++;
				ingredient_scan = 0;
				for(i = 0; i < recipe.numIngredients; i++)
				{
					if(fscanf(RecipeList, " %f %s %[^\n]", &recipe.items[i].quantity, recipe.items[i].unit, recipe.items[i].food) == 3)
						ingredient_scan++;
				}
				if(ingredient_scan == recipe.numIngredients)
					scan_check++;
				if(fscanf(RecipeList, " %s %d", word, &recipe.numSteps) == 2)
					scan_check++;
				step_scan = 0;
				for(j = 0; j < recipe.numSteps; j++)
				{
					if(fscanf(RecipeList, " %[^\n]", recipe.steps[j]) == 1)
						step_scan++;
				}
				if(step_scan == recipe.numSteps)
					scan_check++;
			}
			if(scan_check == 4)
			{
				unique = -1;
				for(a = 0; a < *numRecipes; a++)
				{
					if(strcmp(recipe.name, aRecipes[a].name) == 0)
						unique = a;		// duplicate recipe index is saved to unique
				}
				if(unique == -1)
				{
					aRecipes[*numRecipes] = recipe;
					(*numRecipes)++;
				}
				else	// a recipe is found to have the same name
				{
					printf("This recipe already exists. Overwrite saved recipe? Y/N ");
					scanf(" %c", &overwrite);
					scanf("%c", &garbage);
					while(overwrite != 'Y' && overwrite != 'y' && overwrite != 'N' && overwrite != 'n')
					{
						printf("Invalid input. Please try again.\n");
						scanf(" %c", &overwrite);
						scanf("%c", &garbage);
					}
					if(overwrite == 'Y' || overwrite == 'y')
						aRecipes[unique] = recipe;
					else if(overwrite == 'N' || overwrite == 'n')
						printf("Recipe %s skipped.\n", recipe.name);
				}
			}
			fscanf(RecipeList, "%c", &garbage);		// to get rid of \n between recipes
		} while(scan_check != 0);
		fclose(RecipeList);
		if(*numRecipes == start_recipes && unique == -8)		// unique == -8 means the function never found appropriate content
			printf("File lacks content.\n");
	}
	else
		printf("Error loading file. Please try again.\n");
}

/*
	Function 18: Search Recipe by Ingredient
	This function searches a recipe according to its ingredient
	Precondition: 
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes
	@param fooditem - user-inputted ingredient
	@param savedRecipes[] - list of recipes that have searched ingredient
*/
void ScanByIngredient(recipeType aRecipes[], int *numRecipes, string fooditem, recipeType savedRecipes[])
{
	int a, i, found, save = 0, s;
	char displaynext;
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
	if(found > 0)
	{
		AlphabeticalSort(savedRecipes, &save);
		s = 0;
		do
		{
			DisplayRecipe(savedRecipes[s]);
			s++;
			if(s < save)
			{
				printf("Display next recipe? Press N for next or X for exit. ");
				scanf(" %c", &displaynext);
				while(displaynext != 'N' && displaynext != 'X')
				{
					printf("Invalid input, please try again. ");
					scanf(" %c", &displaynext);
				}
			}
		} while(s < save && displaynext != 'X');
	}
	else
		printf("No recipes matching ingredient.\n");
	
}

/*
	Function 19: Generate Shopping List
	This function randomizes a shopping list for the user
	Precondition: option must be a single character
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes
*/
void ShoppingList(recipeType aRecipes[], int *numRecipes)
{
	int i, index, num;
	string recipe;
	DisplayRecipeTitles(aRecipes, numRecipes);
	printf("Choose recipe: ");
	scanf("%[^\n]", recipe);
	index = SearchName(aRecipes, numRecipes, recipe);
	printf("Enter number of people: ");	
	scanf(" %d", &num);
	printf("List of ingredients for %s:\n", aRecipes[index].name);
	for(i = 0; i < aRecipes[index].numIngredients; i++)
		printf("%.2f %s %s\n", aRecipes[index].items[i].quantity / aRecipes[index].servings * num, aRecipes[index].items[i].unit, aRecipes[index].items[i].food);
}

struct threeRecipes
{
	recipeType main_recipe,
			   starter_recipe,
			   dessert_recipe;
	int main, starter, dessert;		// signal that there's a main, starter, or dessert
	float calorieTotal;
};
typedef struct threeRecipes recipe3;

/*
	Function 20: Recommend Menu
	This function searches a recipe according to its ingredient
	Precondition: numRecipes is at most 50
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes
	@param calorie_goal - amount of calories the user aims to gain
*/
void RecommendMenu(recipeType aRecipes[], int *numRecipes, float calorie_goal)
{
	int a, b, c, d, e, f, g, h, i, j, k, l;
	int num = 0;	// number of total recipeSets
	int main_count = 0, starter_count = 0, dessert_count = 0;
	int saved_menu = 0, closest, random;
	recipeType aMain[*numRecipes], aStarter[*numRecipes], aDessert[*numRecipes];
	recipe3 recipeSet[MAX_RECIPESETS];
	recipe3 recommend[MAX_RECIPESETS];
	float calorie_diff[MAX_RECIPESETS];
	char option, garbage;

	for(a = 0; a < *numRecipes; a++)
	{
		recipeSet[num].main = 0;
		recipeSet[num].starter = 0;
		recipeSet[num].dessert = 0;
		if(strcmp(aRecipes[a].class, "main") == 0)
		{
			aMain[main_count] = aRecipes[a];
			aMain[main_count].servings = 1;
			for(b = 0; b < aRecipes[a].numIngredients; b++)
			{
				aMain[main_count].items[b].quantity = aRecipes[a].items[b].quantity / aRecipes[a].servings;
				aMain[main_count].items[b].calories = aRecipes[a].items[b].calories / aRecipes[a].servings;
			}
			aMain[main_count].calorie_total = aRecipes[a].calorie_total / aRecipes[a].servings;
			recipeSet[num].main_recipe = aMain[main_count];
			recipeSet[num].main = 1;
			main_count++;
		}
		else if(strcmp(aRecipes[a].class, "starter") == 0)
		{
			aStarter[starter_count] = aRecipes[a];
			aStarter[starter_count].servings = 1;
			for(c = 0; c < aRecipes[a].numIngredients; c++)
			{
				aStarter[starter_count].items[c].quantity = aRecipes[a].items[c].quantity / aRecipes[a].servings;
				aStarter[starter_count].items[c].calories = aRecipes[a].items[c].calories / aRecipes[a].servings;
			}
			aStarter[starter_count].calorie_total = aRecipes[a].calorie_total / aRecipes[a].servings;
			recipeSet[num].starter_recipe = aStarter[starter_count];
			recipeSet[num].starter = 1;
			starter_count++;
		}
		else if(strcmp(aRecipes[a].class, "dessert") == 0)
		{
			aDessert[dessert_count] = aRecipes[a];
			aDessert[dessert_count].servings = 1;
			for(d = 0; d < aRecipes[a].numIngredients; d++)
			{
				aDessert[dessert_count].items[d].quantity = aRecipes[a].items[d].quantity / aRecipes[a].servings;
				aDessert[dessert_count].items[d].calories = aRecipes[a].items[d].calories / aRecipes[a].servings;
			}
			aDessert[dessert_count].calorie_total = aRecipes[a].calorie_total / aRecipes[a].servings;
			recipeSet[num].dessert_recipe = aDessert[dessert_count];
			recipeSet[num].dessert = 1;
			dessert_count++;
		}
		recipeSet[num].calorieTotal = aRecipes[a].calorie_total / aRecipes[a].servings;
		num++;
	}

	for(e = 0; e < main_count; e++)
	{
		for(f = 0; f < starter_count; f++)
		{
			recipeSet[num].main_recipe = aMain[e];
			recipeSet[num].starter_recipe = aStarter[f];
			recipeSet[num].calorieTotal = recipeSet[num].main_recipe.calorie_total + recipeSet[num].starter_recipe.calorie_total;
			recipeSet[num].main = 1;
			recipeSet[num].starter = 1;
			recipeSet[num].dessert = 0;
			num++;
		}
		for(g = 0; g < dessert_count; g++)
		{
			recipeSet[num].main_recipe = aMain[e];
			recipeSet[num].dessert_recipe = aDessert[g];
			recipeSet[num].calorieTotal = recipeSet[num].main_recipe.calorie_total + recipeSet[num].dessert_recipe.calorie_total;
			recipeSet[num].main = 1;
			recipeSet[num].starter = 0;
			recipeSet[num].dessert = 1;
			num++;
		}
	}

	for(f = 0; f < starter_count; f++)
	{
		for(g = 0; g < dessert_count; g++)
		{
			recipeSet[num].starter_recipe = aStarter[f];
			recipeSet[num].dessert_recipe = aDessert[g];
			recipeSet[num].calorieTotal = recipeSet[num].starter_recipe.calorie_total + recipeSet[num].dessert_recipe.calorie_total;
			recipeSet[num].main = 0;
			recipeSet[num].starter = 1;
			recipeSet[num].dessert = 1;
			num++;
		}
	}

	for(h = 0; h < main_count; h++)
	{
		for(i = 0; i < starter_count; i++)
		{
			for(j = 0; j < dessert_count; j++)
			{
				recipeSet[num].main_recipe = aMain[h];
				recipeSet[num].starter_recipe = aStarter[i];
				recipeSet[num].dessert_recipe = aDessert[j];
				recipeSet[num].calorieTotal = recipeSet[num].main_recipe.calorie_total + recipeSet[num].starter_recipe.calorie_total + recipeSet[num].dessert_recipe.calorie_total;
				recipeSet[num].main = 1;
				recipeSet[num].starter = 1;
				recipeSet[num].dessert = 1;
				num++;
			}
		}
	}

	for(k = 0; k < num; k++)
	{
		calorie_diff[k] = calorie_goal - recipeSet[k].calorieTotal;
		if(calorie_diff[k] >= 0)
			closest = k;
	}

	for(k = 0; k < num; k++)
	{
		if(calorie_diff[k] < calorie_diff[closest] && calorie_diff[k] >= 0)
			closest = k;
	}

	// to find recipe combinations of the same desired calorie total
	for(k = 0; k < num; k++)
	{
		if(calorie_diff[k] == calorie_diff[closest])
		{
			recommend[saved_menu] = recipeSet[k];
			saved_menu++;
		}
	}

	// if all recipes are above calorie goal, find the one with the lowest calories since that would be closest to goal
	if(saved_menu == 0)
	{
		printf("No recipe is below calorie goal. Show recipe closest to calorie goal? Press Y to show. ");
		scanf(" %c", &option);
		scanf("%c", &garbage);
		if(option == 'Y' || option == 'y')
		{
			closest = 0;
			for(l = 0; l < *numRecipes; l++)
			{
				if(aRecipes[l].calorie_total < aRecipes[closest].calorie_total)
					closest = l;
			}
			DisplayRecipe(aRecipes[closest]);
		}
	}
	else
	{
		random = rand() % saved_menu;
		if(recommend[random].main)
			DisplayRecipe(recommend[random].main_recipe);
		if(recommend[random].starter)
			DisplayRecipe(recommend[random].starter_recipe);
		if(recommend[random].dessert)
			DisplayRecipe(recommend[random].dessert_recipe);
	}
}