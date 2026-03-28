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
	Function 1: Password Checker
	This function checks if the user's inputted username and password are correct
	Precondition: username and password can only be 20 characters at most
	@param username - username input
	@param current_username - saved username
	@param password - password input
	@param current_password - saved password
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
	Function 2: Add food-calorie info
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
	Function 3: Delete food-calorie info
	This function deletes the info of a certain food item
	Precondition: quantity can only be a non-negative float
				  quantity and unit are to be inputted with a space between
	@param food_info - struct that holds a food item's name, quantity in certain units, and calorie count
	@param food_count - number of existing food items
	@param food - name of food item to delete
*/
void DeleteFoodCalorie(ingredientType food_info[], int *food_count, string food)
{
	int a = 0, i, delete = -1;
	for(i = 0; i < *food_count; i++)
	{
		if(strcmp(food_info[i].food, food) == 0)
			delete = i;
	}
	if(delete == -1)
		printf("Food item not found.\n");
	else
	{
		while(a < *food_count)
		{
			if(a == delete)
			{
				if(a < *food_count - 1)
				{
					for(i = a; i < *food_count - 1; i++)
						food_info[i] = food_info[i + 1];
				}
				(*food_count)--;
			}
			else
				a++;
		}
	}
}

/*
	Function 4: View food-calorie chart
	This function displays the food, its quantity, unit, and calorie count in a chart
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
	This function exports the current food-calorie info to the user's choice of file
	Precondition: the number of food items must not exceed 50
	@param filename - name of file that will store food-calorie info
	@param food_info - struct that holds a food item's name, quantity in certain units, and calorie count
	@param food_count - number of food items
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
		printf("Food-calorie info saved successfully!\n");
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
		else
			printf("File loaded successfully!\n");
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
	Precondition: recipe name and steps only contain letters in the alphabet
				  class can only be starter, main, or dessert
				  servings must be a positive integer
				  user will input steps in order (no insertion of steps in the middle)
	@param aRecipe - recipe struct
	@param numRecipes - number of recipes
*/
void AddRecipe(recipeType aRecipes[], int *numRecipes)
{
	char garbage, option;
	int i = 0, j = 0;
	string recipe;

	printf("Recipe: ");
	scanf("%[^\n]", recipe);
	scanf("%c", &garbage);

	if(SearchName(aRecipes, numRecipes, recipe) > -1)
	{
		strcpy(aRecipes[*numRecipes].name, recipe);
		aRecipes[*numRecipes].calorie_total = 0;

		printf("Class: ");
		scanf("%[^\n]", aRecipes[*numRecipes].class);
		scanf("%c", &garbage);

		printf("Servings: ");
		scanf(" %d", &aRecipes[*numRecipes].servings);
		scanf("%c", &garbage);

		printf("Ingredients:\n");
		do
		{
			aRecipes[*numRecipes].items[i] = AddIngredient(aRecipes[*numRecipes].items[i]);
			i++;
			printf("Continue adding ingredients? Y/N ");
			scanf(" %c", &option);
			scanf("%c", &garbage);
		} while(option == 'Y' || option == 'y');
		aRecipes[*numRecipes].numIngredients = i;

		printf("Steps:\n");
		do
		{
			printf("%d. ", j);
			scanf("%[^\n]", aRecipes[*numRecipes].steps[j]);
			scanf("%c", &garbage);
			j++;
			printf("Continue adding steps? Y/N ");
			scanf(" %c", &option);
		} while(option == 'Y' || option == 'y');
		aRecipes[*numRecipes].numSteps = j;
		(*numRecipes)++;
	}
	else
		printf("Recipe name already exists.\n");
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
	int a = 0, i, delete;
	for(i = 0; i < aRecipe->numIngredients; i++)
	{
		if(strcmp(aRecipe->items[i].food, ingredient) == 0)
			delete = i;
	}
	while(a < aRecipe->numIngredients)
	{
		if(a == delete)
		{
			if(a < aRecipe->numIngredients - 1)
			{
				for(i = delete; i < aRecipe->numIngredients - 1; i++)
					aRecipe->items[i] = aRecipe->items[i + 1];
			}
			(aRecipe->numIngredients)--;
		}
		else
			a++;
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
	aRecipe->numSteps++;
	for(a = step_insert; a < aRecipe->numSteps; a++)		// step_insert is the index of the step after the one that will be inserted
		strcpy(aRecipe->steps[a], aRecipe->steps[a + 1]);
	step_insert--;	// step array starts at 0 but step list starts at 1 so decrement to go to actual index
	strcpy(aRecipe->steps[step_insert], step);
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
	step_remove--;
	while(a < aRecipe->numSteps)
	{
		if(a == step_remove)
		{
			if(a < aRecipe->numIngredients - 1)
			{
				for(i = step_remove; i < aRecipe->numSteps - 1; i++)
					strcpy(aRecipe->steps[i], aRecipe->steps[i + 1]);
			}
			(aRecipe->numSteps)--;
		}
		else
			a++;
	}
}

/*
	Function 12: Delete Recipe
	This function deletes a recipe from the list
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
		printf("Recipe not found.\n");
	else
	{
		while(a < *numRecipes)
		{
			if(a == delete)
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
	This function displays each recipe title in alphabetical order
	Precondition: number of recipes must not exceed 50
	@param aRecipe - recipe struct
	@param numRecipes - number of recipes
*/
void DisplayRecipeTitles(recipeType aRecipes[], int *numRecipes)
{
	int i;
	if(*numRecipes == 0)
		printf("No recipes to show.\n");
	else
	{
		AlphabeticalSort(aRecipes, numRecipes);
		for(i = 0; i < *numRecipes; i++)
			printf("%s\n", aRecipes[i].name);
	}
}

/*
	Function 14: Display Recipe
	This function displays one recipe's details
	Precondition: aRecipe has all valid contents
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
				fprintf(RecipeList, "%.3f %s %s\n", aRecipes[a].items[i].quantity, aRecipes[a].items[i].unit, aRecipes[a].items[i].food);
			fprintf(RecipeList, "Steps %d\n", aRecipes[a].numSteps);
			for(j = 0; j < aRecipes[a].numSteps; j++)
				fprintf(RecipeList, "%s\n", aRecipes[a].steps[j]);
			fprintf(RecipeList, "\n");
		}
		fclose(RecipeList);
		printf("Recipes saved successfully!\n");
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
			if(fscanf(RecipeList, " %20[^\n] %d %7s %12s %d", recipe.name, &recipe.servings, recipe.class, word, &recipe.numIngredients) == 5)
			{
				scan_check++;
				ingredient_scan = 0;
				for(i = 0; i < recipe.numIngredients; i++)
				{
					if(fscanf(RecipeList, " %f %15s %20[^\n]", &recipe.items[i].quantity, recipe.items[i].unit, recipe.items[i].food) == 3)
						ingredient_scan++;
				}
				if(ingredient_scan == recipe.numIngredients)
					scan_check++;
				if(fscanf(RecipeList, " %6s %d", word, &recipe.numSteps) == 2)
					scan_check++;
				step_scan = 0;
				for(j = 0; j < recipe.numSteps; j++)
				{
					if(fscanf(RecipeList, " %70[^\n]", recipe.steps[j]) == 1)
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
		else
			printf("File loaded successfully!\n");
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
	Precondition: number of recipes must not exceed 50
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

/*
	Function 20: Recommend Menu
	This function searches a recipe according to its ingredient
	Precondition: number of recipes must not exceed 50
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes
	@param calorie_goal - amount of calories the user aims to gain
*/
void RecommendMenu(recipeType aRecipes[], int *numRecipes, float calorie_goal)
{
	int a, b, c, d, e = 0, f, g = 0, h, i = 0, j, k, l;
	int main_count = 0, starter_count = 0, dessert_count = 0;
	int closest_main = -1, closest_starter = -1, closest_dessert = -1;	// -1 to signal no recipe was found to be below calorie goal
	int random, saved = 0, closest = 0;
	int main_index[*numRecipes], starter_index[*numRecipes], dessert_index[*numRecipes];
	int main_match = 1, starter_match = 1, dessert_match = 1;
	recipeType aMain[*numRecipes], aStarter[*numRecipes], aDessert[*numRecipes], recommend[*numRecipes];
	float calorie_diff[*numRecipes], actual_calories = 0;
	char option, garbage;

	for(a = 0; a < *numRecipes; a++)
	{
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
			dessert_count++;
		}
	}

	do
	{
		if(aMain[e].calorie_total <= calorie_goal)
			closest_main = e;
		e++;
	} while(closest_main == -1 && e < main_count);
	if(closest_main != -1)
	{
		for(e = 0; e < main_count; e++)
		{
			calorie_diff[e] = calorie_goal - aMain[e].calorie_total;
			if(calorie_diff[e] >= 0 && aMain[e].calorie_total > aMain[closest_main].calorie_total)
				closest_main = e;
		}
		main_index[0] = closest_main;
		for(f = 0; f < main_count; f++)
		{
			if(aMain[f].calorie_total == aMain[closest_main].calorie_total && f != closest_main)
			{
				main_index[main_match] = f;
				main_match++;	// number of main recipes that have the same closest calorie total
			}
		}
		random = rand() % main_match;
		recommend[saved] = aMain[main_index[random]];
		calorie_goal -= recommend[saved].calorie_total;
		saved++;
	}

	do
	{
		if(aStarter[g].calorie_total <= calorie_goal)
			closest_starter = g;
		g++;
	} while(closest_starter == -1 && g < starter_count);
	if(closest_starter != -1)
	{
		for(g = 0; g < starter_count; g++)
		{
			calorie_diff[g] = calorie_goal - aStarter[g].calorie_total;
			if(calorie_diff[g] >= 0 && aStarter[g].calorie_total > aStarter[closest_starter].calorie_total)
				closest_starter = g;
		}
		starter_index[0] = closest_starter;
		for(h = 0; h < starter_count; h++)
		{
			if(aStarter[h].calorie_total == aStarter[closest_main].calorie_total && h != closest_starter)
			{
				starter_index[starter_match] = h;
				starter_match++;	// number of starter recipes that have the same closest calorie total
			}
		}
		random = rand() % starter_match;
		recommend[saved] = aStarter[starter_index[random]];
		calorie_goal -= recommend[saved].calorie_total;
		saved++;
	}

	do
	{
		if(aDessert[i].calorie_total <= calorie_goal)
			closest_dessert = i;
		i++;
	} while(closest_dessert == -1 && i < dessert_count);
	if(closest_dessert != -1)
	{
		for(i = 0; i < dessert_count; i++)
		{
			calorie_diff[i] = calorie_goal - aDessert[i].calorie_total;
			if(calorie_diff[i] >= 0 && aDessert[i].calorie_total > aDessert[closest_dessert].calorie_total)
				closest_dessert = i;
		}
		dessert_index[0] = closest_dessert;
		for(j = 0; j < starter_count; j++)
		{
			if(aDessert[j].calorie_total == aDessert[closest_main].calorie_total && j != closest_dessert)
			{
				dessert_index[dessert_match] = j;
				dessert_match++;	// number of dessert recipes that have the same closest calorie total
			}
		}
		random = rand() % dessert_match;
		recommend[saved] = aDessert[dessert_index[random]];
		saved++;
	}
	
	// if all recipes are above calorie goal, find the one with the lowest calories since that would be closest to goal
	if(saved == 0)
	{
		printf("No recipe is below calorie goal. Show recipe closest to calorie goal? Press Y to show. ");
		scanf(" %c", &option);
		scanf("%c", &garbage);
		if(option == 'Y' || option == 'y')
		{
			for(k = 0; k < *numRecipes; k++)
			{
				if(aRecipes[k].calorie_total < aRecipes[closest].calorie_total)
					closest = k;
			}
			DisplayRecipe(aRecipes[closest]);
		}
	}
	else
	{
		for(l = 0; l < saved; l++)
		{
			DisplayRecipe(recommend[l]);
			actual_calories += recommend[l].calorie_total;
		}
		printf("Calorie total: %.2f\n", actual_calories);
	}
}

/*
	Function 21: Username and Password Changer
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