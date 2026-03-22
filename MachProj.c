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
	string steps[MAX_STEPS];
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
void AlphabeticalSort(recipeType aRecipes[], int numRecipes)
{
	int i, j, min;
	recipeType temp;
	for(i = 0; i < numRecipes; i++)
	{
		min = i;
		for(j = i; j < numRecipes; j++)
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
int SearchName(recipeType aRecipes[], string recipeTitle, int numRecipes)
{
	int i, index = -1;
	for(i = 0; i < numRecipes; i++)
	{
		if(strcmp(aRecipes[i].name, recipeTitle) == 0)
			index = i;
	}
	return index;
}

/*
	Helper Function 3: Display Recipe
	This function displays one recipe's details
	Precondition: 
	@param aRecipe - recipe struct
*/
void DisplayRecipe(recipeType aRecipe)
{
	int i, j;
	printf("%s		%d		%f\n", aRecipe.name, aRecipe.servings, aRecipe.calorie_total);
	printf("Ingredients:\n");
	for(i = 0; i < aRecipe.numIngredients; i++)
		printf("%f %s %s		%f\n", aRecipe.items[i].quantity, aRecipe.items[i].unit, aRecipe.items[i].food, aRecipe.items[i].calories);
	printf("Procedure:\n");
	for(j = 0; j < aRecipe.numSteps; j++)
		printf("%s\n", aRecipe.steps[j]);
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
	char option;
	printf("What will you change? Press U for username, P for password, or X for exit. ");
	scanf("%c", &option);
	while(option != 'X')
	{
		if(option == 'U')
		{
			printf("Old username: ");
			fgets(old_username, sizeof(old_username), stdin);
			if(strcmp(old_username, username) == 0)
			{
				printf("New username: ");
				fgets(new_username, sizeof(new_username), stdin);
				strcpy(username, new_username);
			}
			else
				printf("Invalid username. Please try again.\n");
		}
		else if(option == 'P')
		{
			printf("Old password: ");
			fgets(old_password, sizeof(old_password), stdin);
			if(strcmp(old_password, password) == 0)
			{
				printf("New password: ");
				fgets(new_password, sizeof(new_password), stdin);
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
	Precondition: 
	@param food_info - struct that holds a food item's name, quantity in certain units, and calorie count
	@return food_info
*/
ingredientType AddFoodCalorie(ingredientType food_info)
{
	char garbage;	// to get rid of leftover \n

	printf("Food item: ");
	scanf("%[^\n]", food_info.food);
	scanf("%c", &garbage);

	printf("Quantity: ");
	scanf(" %f", &food_info.quantity);
	scanf("%c", &garbage);

	printf("Unit: ");
	scanf("%[^\n]", food_info.unit);
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
void ViewCalorie(ingredientType food_info[], int food_count)
{
	int i = 0;
	char option;
	printf("		Food			Quantity	Unit	Calories\n");
	while(i < food_count && i < 10)
	{
		printf("%s	%.2f	%s	%.2f\n", food_info[i].food, food_info[i].quantity, food_info[i].unit, food_info[i].calories);
		i++;
	}
	if(food_count > 10)
	{
		printf("View next 10 items? Press 'N' to proceed; press 'X' to exit.\n");
		scanf(" %c", &option);
		while(option != 'X')
		{
			do
			{
				printf("%s		%.2f		%s		%.2f\n", food_info[i].food, food_info[i].quantity, food_info[i].unit, food_info[i].calories);
				i++;
			} while(i % 10 != 0);
			printf("View next 10 items? Press 'N' to proceed or 'X' to exit.\n");
			scanf(" %c", &option);
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
void SaveCalorie(ingredientType food_info[], int food_count, string filename)
{
	FILE *CalText;
	int a;
	if((CalText = fopen(filename, "w")) != NULL)
	{
		for(a = 0; a < food_count; a++)
		{
			fprintf(CalText, "%s\n", food_info[a].food);
			fprintf(CalText, "%f ", food_info[a].quantity);
			fprintf(CalText, "%s ", food_info[a].unit);
			fprintf(CalText, "%f\n\n", food_info[a].calories);
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
	@param food_info - struct that holds a food item's name, quantity in certain units, and calorie count
	@param filename - name of file that contains food-calorie info
	@param calorie_info - struct that saves the food items
	@param calorie_info_count - number of food items in the file
*/
void LoadCalorie(ingredientType food_info, string filename, ingredientType calorie_info[], int calorie_info_count)
{
	int c, f1, f2, f3, f4, unique_check = 0;
	FILE *CalText;
	if((CalText = fopen(filename, "r")) != NULL)
	{
		do
		{
			f1 = fscanf(CalText, "%[^\n]", food_info.food);
			f2 = fscanf(CalText, " %f", &food_info.quantity);
			f3 = fscanf(CalText, "%s", food_info.unit);
			f4 = fscanf(CalText, " %f", &food_info.calories);
			if(f1 && f2 && f3 && f4)
			{
				unique_check = 0;
				for(c = 0; c < calorie_info_count; c++)
				{
					if(strcmp(food_info.food, calorie_info[c].food) == 0)
						unique_check++;
				}
				if(unique_check == 0)
				{
					calorie_info[calorie_info_count] = food_info;
					calorie_info_count++;
				}
			}
		} while(f1 && f2 && f3 && f4);
		fclose(CalText);
	}
	else
		printf("Error loading file. Please try again.\n");
}

/*
	Function 7: Add ingredient
	This function gets the input of an ingredient and its quantity
	Precondition: 
	@param ingredient - struct that holds an ingredient's name and quantity in certain units
	@param food_info - struct that holds a food item's name, quantity in certain units, and calorie count
	@param food_count - number of existing food items
	@return ingredient which has the ingredient name,  quantity, and unit
*/
ingredientType AddIngredient(ingredientType ingredient, ingredientType food_info[], int food_count)
{
	char garbage;
	int i;

	printf("Food item: ");
	scanf("%[^\n]", ingredient.food);
	scanf("%c", &garbage);

	printf("Quantity: ");
	scanf(" %f", &ingredient.quantity);
	scanf("%c", &garbage);

	printf("Unit: ");
	scanf("%[^\n]", ingredient.unit);
	scanf("%c", &garbage);

	ingredient.calories = 0;
	for(i = 0; i < food_count; i++)
	{
		if(strcmp(ingredient.food, food_info[i].food) == 0)
			ingredient.calories = food_info[i].calories / food_info[i].quantity * ingredient.quantity;
	}

	return ingredient;
}

/*
	Function 8: Add Recipe
	This function adds an ingredient to a recipe
	Precondition: dish, class, and step only contain letters in the alphabet
				  class can only be starter, main, or dessert
				  servings must be a positive integer
	@param aRecipe - recipe struct
	@param food_info - struct that holds a food item's name, quantity in certain units, and calorie count
	@param food_count - number of existing food items
	@return aRecipe
*/
recipeType AddRecipe(recipeType aRecipe, ingredientType food_info[], int food_count)
{
	char garbage;
	int i = 0, j = 0;

	printf("Recipe: ");
	scanf("%[^\n]", aRecipe.name);
	scanf("%c", &garbage);

	printf("Class: ");
	scanf("%[^\n]", aRecipe.class);
	fgets(aRecipe.class, sizeof(aRecipe.class), stdin);
	scanf("%c", &garbage);

	printf("Servings: ");
	scanf(" %d", &aRecipe.servings);
	scanf("%c", &garbage);

	printf("Ingredients:\n");
	do
	{
		aRecipe.items[i] = AddIngredient(aRecipe.items[i], food_info, food_count);
	} while(strcmp(aRecipe.items[i++].food, "888"));
	aRecipe.numIngredients = i;

	do
	{
		scanf("%[^\n]", aRecipe.steps[j]);
		scanf("%c", &garbage);
	} while(strcmp(aRecipe.steps[j++], "888"));
	aRecipe.numSteps = j;

	return aRecipe;
}

/*
	Function 9: Delete Ingredient
	This function deletes an ingredient from a recipe
	Precondition: the name of the ingredient only contains letters in the alphabet
	@param aRecipe - recipe struct
	@param ingredient - ingredient to be deleted
*/
void DeleteIngredient(recipeType aRecipe, string ingredient)
{
	int a = 0, i;
	string delete;
	if(aRecipe.numIngredients <= 1)
		printf("Cannot delete any more ingredients.\n");
	else
	{
		for(i = 0; i < aRecipe.numIngredients; i++)
		{
			if(strcmp(aRecipe.items[i].food, ingredient) == 0)
				strcpy(delete, aRecipe.items[i].food);
		}
		while(a < aRecipe.numIngredients)
		{
			if(strcmp(aRecipe.items[a].food, delete) == 0)
			{
				if(a < aRecipe.numIngredients - 1)
				{
					for(i = a; i < aRecipe.numIngredients - 1; i++)
						aRecipe.items[i] = aRecipe.items[i + 1];
				}
				(aRecipe.numIngredients)--;
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
	@param step - step to be added
*/
void AddStep(recipeType aRecipe, string_step step)
{
	strcpy(aRecipe.steps[aRecipe.numSteps], step);
	aRecipe.numSteps++;
}

/*
	Function 11: Delete Step
	This function deletes a step to a recipe
	Precondition: step contains at most 70 characters
	@param aRecipe - recipe struct
	@param step - step to be deleted
*/
void DeleteStep(recipeType aRecipe, string_step step)
{
	int a = 0, i;
	string_step delete;
	if(aRecipe.numSteps <= 1)
		printf("Cannot delete any more steps.\n");
	else
	{
		for(i = 0; i < aRecipe.numSteps; i++)
		{
			if(strcmp(aRecipe.steps[i], step) == 0)
				strcpy(delete, aRecipe.steps[i]);
		}
		while(a < aRecipe.numSteps)
		{
			if(strcmp(aRecipe.steps[a], delete) == 0)
			{
				if(a < aRecipe.numSteps - 1)
				{
					for(i = a; i < aRecipe.numSteps - 1; i++)
						strcpy(aRecipe.steps[i], aRecipe.steps[i + 1]);
				}
				(aRecipe.numSteps)--;
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
void DeleteRecipe(recipeType aRecipes[], string recipeTitle, int numRecipes)
{
	int a = 0, i;
	int delete = SearchName(aRecipes, recipeTitle, numRecipes);
	if(delete == -1)
		printf("Recipe not found. ");
	else
	{
		while(a < numRecipes)
		{
			if(strcmp(aRecipes[a].name, aRecipes[delete].name) == 0)
			{
				if(a < numRecipes - 1)
				{
					for(i = a; i < numRecipes - 1; i++)
						aRecipes[i] = aRecipes[i + 1];
				}
				numRecipes--;
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
void DisplayRecipeTitles(recipeType aRecipes[], int numRecipes)
{
	int i;
	AlphabeticalSort(aRecipes, numRecipes);
	for(i = 0; i < numRecipes; i++)
		printf("%s\n", aRecipes[i].name);
}

/*
	Function 14: Search Recipe by Title
	This function searches a recipe by its title
	Precondition: recipeTitle contains 20 characters at most
	@param aRecipes[] - list of recipes
	@param recipeTitle - recipe the user is trying to find
	@param n - number of recipes
*/
void SearchByTitle(recipeType aRecipes[], string recipeTitle, int numRecipes)
{
	DisplayRecipeTitles(aRecipes, numRecipes);
	int index = SearchName(aRecipes, recipeTitle, numRecipes);
	if(index > -1)
		DisplayRecipe(aRecipes[index]);
	else if(index == -1)
		printf("Recipe not found.\n");
}

/*
	Function 15: Export Recipes
	This function saves the current list of recipes in the user's text file of choice (if it's found)
	Precondition: recipeTitle contains 20 characters at most
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes
	@param filename - name of file that will contain all recipes made at the time
*/
void ExportRecipes(recipeType aRecipes[], int numRecipes, string filename)
{
	FILE *RecipeList;
	int a, i, j;
	if((RecipeList = fopen(filename, "w")) != NULL)
	{
		for(a = 0; a < numRecipes; a++)
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
	Function 16: Import Recipes
	This function loads a list of recipes from the user's inputted text file (if it's found)
	Precondition: recipeTitle contains 20 characters at most
	@param aRecipes[] - list of recipes
	@param filename - name of file user will load recipes from
*/
void ImportRecipes(recipeType aRecipes[], string filename)
{
	FILE *RecipeList;
	int a = 0, i, j;
	char garbage, word[12];		// to scan leftover \n, "Ingredients", and "Steps"
	if((RecipeList = fopen(filename, "r")) != NULL)
	{
		do
		{
			fscanf(RecipeList, "%[^\n]", aRecipes[a].name);
			fscanf(RecipeList, "%c", &garbage);
			fscanf(RecipeList, "%d %s", &aRecipes[a].servings, aRecipes[a].class);
			fscanf(RecipeList, "%c", &garbage);
			fscanf(RecipeList, "%s %d", word, &aRecipes[a].numIngredients);
			fscanf(RecipeList, "%c", &garbage);
			for(i = 0; i < aRecipes[a].numIngredients; i++)
			{
				fscanf(RecipeList, "%f %s %[^\n]", &aRecipes[a].items[i].quantity, aRecipes[a].items[i].unit, aRecipes[a].items[i].food);
				fscanf(RecipeList, "%c", &garbage);
			}
			fscanf(RecipeList, "%s", word);
			for(j = 0; j < aRecipes[a].numSteps; j++)
			{
				fscanf(RecipeList, "%[^\n]", aRecipes[a].steps[j]);
				fscanf(RecipeList, "%c", &garbage);
			}
			a++;
		} while(a != 0);
		fclose(RecipeList);
	}
	else
		printf("Error loading file. Please try again.\n");
}

/*
	Function 17: Search Recipe by Ingredient
	This function searches a recipe according to its ingredient
	Precondition: 
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes
	@param fooditem - user-inputted ingredient
	@param savedRecipes[] - list of recipes that have searched ingredient
*/
void ScanByIngredient(recipeType aRecipes[], int numRecipes, string fooditem, recipeType savedRecipes[])
{
	int a, i, found, save = 0;
	for(a = 0; a < numRecipes; a++)
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
	@param numRecipes - number of recipes
*/
void ShoppingList(recipeType aRecipes[], int numRecipes)
{
	int i, index, num;
	string recipe;
	DisplayRecipeTitles(aRecipes, numRecipes);
	printf("Choose recipe: ");
	scanf("%[^\n]", recipe);
	index = SearchName(aRecipes, recipe, numRecipes);
	printf("Enter number of people: ");	
	scanf(" %d", &num);
	printf("List of ingredients for %s:\n", aRecipes[index].name);
	for(i = 0; i < aRecipes[index].numIngredients; i++)
		printf("%f %s %s\n", aRecipes[index].items[i].quantity * num, aRecipes[index].items[i].unit, aRecipes[index].items[i].food);
}

/*
	Function 19: Recommend Menu
	This function searches a recipe according to its ingredient
	Precondition: 
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes
	@param calorie_goal - amount of calories the user aims to gain
*/
void RecommendMenu(recipeType aRecipes[], int numRecipes, float calorie_goal)
{
	int a, b, c, closest = 0, counter = 0, i, saved_menu = 0;
	recipeType recommend[3];
	for(a = 0; a < numRecipes; a++)
	{
		if(strcmp(aRecipes[a].class, "main") == 0)
		{
			if(aRecipes[a].calorie_total > aRecipes[closest].calorie_total && aRecipes[a].calorie_total <= calorie_goal)
			{
				closest = a;
				recommend[saved_menu] = aRecipes[closest];
				saved_menu++;
			}
			if(aRecipes[closest].calorie_total == calorie_goal)
				counter++;
			calorie_goal -= aRecipes[closest].calorie_total;
		}
	}
	closest = 0;
	if(counter == 0)
	{
		for(b = 0; b < numRecipes; b++)
		{
			if(strcmp(aRecipes[b].class, "starter") == 0)
			{
				if(aRecipes[b].calorie_total > aRecipes[closest].calorie_total && aRecipes[b].calorie_total <= calorie_goal)
				{
					closest = b;
					recommend[saved_menu] = aRecipes[closest];
					saved_menu++;
				}
				if(aRecipes[closest].calorie_total == calorie_goal)
					counter++;
				calorie_goal -= aRecipes[closest].calorie_total;
			}
		}
	}
	closest = 0;
	if(counter == 0)
	{
		for(c = 0; c < numRecipes; c++)
		{
			if(strcmp(aRecipes[c].class, "dessert") == 0)
			{
				if(aRecipes[c].calorie_total > aRecipes[closest].calorie_total && aRecipes[c].calorie_total <= calorie_goal)
				{
					closest = c;
					recommend[saved_menu] = aRecipes[closest];
					saved_menu++;
				}
			}
		}
	}
	for(i = 0; i < saved_menu; i++)
		DisplayRecipe(recommend[i]);
}