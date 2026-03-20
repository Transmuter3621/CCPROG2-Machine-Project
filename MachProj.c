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
	Precondition: 
	@param aRecipes[] - list of recipes
	@param recipeTitle - recipe name the user is trying to find
	@param numRecipes - number of recipes
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
	Function 1: Username and Password Changer
	This function changes the user's username and/or password
	Precondition: option must be a single character
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
			scanf("%[^\n]", old_username);
			if(strcmp(old_username, username) == 0)
			{
				printf("New username: ");
				scanf("%[^\n]", new_username);
				strcpy(username, new_username);
			}
			else
				printf("Invalid username. Please try again.\n");
		}
		else if(option == 'P')
		{
			printf("Old password: ");
			scanf("%[^\n]", old_password);
			if(strcmp(old_password, password) == 0)
			{
				printf("New password: ");
				scanf("%[^\n]", new_password);
				strcpy(password, new_password);
			}
			else
				printf("Invalid username. Please try again.\n");
		}
		else
			printf("Invalid input, please try again.\n");
		printf("What will you change? Press U for username, P for password, or X for exit. ");
		scanf("%c", &option);
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
void ViewCalorie(ingredientType ingredient[], int ingredient_count)
{
	int i = ingredient_count;
	char option;
	printf("		Food			Quantity	Unit	Calories");
	while(i < 10)
	{
		printf("%s\t\t%f\t\t%s\t\t%f\n", ingredient[i].food, ingredient[i].quantity, ingredient[i].unit, ingredient[i].calories);
		i++;
	}
	printf("View next 10 items? Press 'N' to proceed; press 'X' to exit.\n");
	scanf(" %c", &option);
	while(option != 'X')
	{
		while(i % 10 != 0)
		{
			printf("%s\t\t%f\t\t%s\t\t%f\n", ingredient[i].food, ingredient[i].quantity, ingredient[i].unit, ingredient[i].calories);
			i++;
		}
		printf("View next 10 items? Press 'N' to proceed; press 'X' to exit.\n");
		scanf(" %c", &option);
	}
}

/*
	Function 5: Save Calorie Info
	This function checks for user's password
	Precondition: 
	@param ingredient - struct that holds a food item's name, quantity in certain units, and calorie count
	@param numItems - number of ingredients
*/
void SaveCalorie(ingredientType ingredient[], int numItems, string filename)
{
	FILE *CalText;
	int a;
	if((CalText = fopen(filename, "w")) != NULL)
	{
		for(a = 0; a < numItems; a++)
		{
			fprintf(CalText, "%s\n", ingredient[a].food);
			fprintf(CalText, "%f ", ingredient[a].quantity);
			fprintf(CalText, "%s ", ingredient[a].unit);
			fprintf(CalText, "%f\n\n", ingredient[a].calories);
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
	@param ingredient - struct that holds a food item's name, quantity in certain units, and calorie count
	@param filename - name of file that contains food-calorie info
	@param calorie_info - struct that saves the food items
	@param calorie_info_count - number of food items in the file
*/
void LoadCalorie(ingredientType ingredient, string filename, ingredientType calorie_info[], int calorie_info_count)
{
	int c, f1, f2, f3, f4, scan_check;
	FILE *CalText;
	if((CalText = fopen(filename, "r")) != NULL)
	{
		for(c = 0; c < calorie_info_count; c++)
		{
			scan_check = 0;
			f1 = fscanf(CalText, "%[^\n]", ingredient.food);
			f2 = fscanf(CalText, " %f", &ingredient.quantity);
			f3 = fscanf(CalText, "%[^\n]", ingredient.unit);
			f4 = fscanf(CalText, " %f", &ingredient.calories);
			if(f1 == 1 && f2 == 1 && f3 == 1 && f4 == 1)
				scan_check++;
			if(scan_check == 1)
				calorie_info[c] = ingredient;
		}
		fclose(CalText);
	}
	else
		printf("Error loading file. Please try again.\n");
}

/*
	Function 7: Add Recipe
	This function checks for user's menu input
	Precondition: dish, class, and step only contain letters in the alphabet
				  class can only be main, starter, or dessert
				  servings must be a positive integer
	@param dish - name of recipe user inputs
	@param class - type of recipe ()
	@param servings - 
	@param ingredient - 
	@param step - 
*/
recipeType AddRecipe(string dish, string class, int servings, ingredientType ingredient[], string procedure[])
{
	int i = 0, j = 0;
	recipeType aRecipe;
	strcpy(aRecipe.name, dish);
	strcpy(aRecipe.class, class);
	aRecipe.servings = servings;
	do
	{
		aRecipe.items[i] = ingredient[i];
		i++;
	} while(strcmp(aRecipe.items[i].food, "888"));
	aRecipe.numIngredients = i;
	do
	{
		strcpy(aRecipe.steps[j], procedure[j]);
		j++;
	} while(strcmp(aRecipe.steps[j], "888"));
	aRecipe.numSteps = j;
	return aRecipe;
}

/*
	Function 8: Delete Ingredient
	This function checks for user's menu input
	Precondition: 
	@param aRecipe - recipe struct
*/
void DeleteIngredient(recipeType aRecipe, string ingredient)
{
	int a = 0, i;
	string delete;
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

/*
	Function 9: Add Step
	This function adds a step to a recipe
	Precondition: option must be a single character
	@param aRecipe - recipe struct
*/
void AddStep(recipeType aRecipe, string aStep)
{
	strcpy(aRecipe.steps[aRecipe.numSteps], aStep);
	aRecipe.numSteps++;
}

/*
	Function 10: Delete Step
	This function deletes a step to a recipe
	Precondition: 
	@param aRecipe - recipe struct
*/
void DeleteStep(recipeType aRecipe, string aStep)
{
	int a = 0, i;
	string delete;
	for(i = 0; i < aRecipe.numSteps; i++)
	{
		if(strcmp(aRecipe.steps[i], aStep) == 0)
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

/*
	Function 11: Delete Recipe
	This function deletes a recipe from the repository
	Precondition: option must be a single character
	@param aRecipe - recipe struct
*/
void DeleteRecipe(recipeType aRecipes[], string recipeTitle, int numRecipes)
{
	int a = 0, i;
	int delete = SearchName(aRecipes, recipeTitle, numRecipes);
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

/*
	Function 12: Display Recipe Titles
	This function checks for user's password
	Precondition: option must be a single character
	@param aRecipe - recipe struct
*/
void DisplayRecipeTitles(recipeType aRecipes[], int numRecipes)
{
	int i;
	AlphabeticalSort(aRecipes, numRecipes);
	printf("********* List of Recipes *********\n");
	for(i = 0; i < numRecipes; i++)
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
		printf("%f %s %s		%f\n", aRecipe.items[i].quantity, aRecipe.items[i].unit, aRecipe.items[i].food, aRecipe.items[i].calories);
	printf("Procedure:\n");
	for(j = 0; j < aRecipe.numSteps; j++)
		printf("%d. %s\n", j + 1, aRecipe.steps[j]);
}

/*
	Function 14: Search Recipe by Title
	This function searches a recipe by its title
	Precondition: 
	@param aRecipes[] - list of recipes
	@param recipeTitle - recipe the user is trying to find
	@param n - number of recipes
*/
void SearchByTitle(recipeType aRecipes[], string recipeTitle, int numRecipes)
{
	printf("********** Recipe Search **********\n");
	DisplayRecipeTitles(aRecipes, numRecipes);
	int index = SearchName(aRecipes, recipeTitle, numRecipes);
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
void ExportRecipes(recipeType aRecipes[], int numRecipes, string filename)
{
	FILE *RecipeList;
	int a, i, j;
	if((RecipeList = fopen(filename, "w")) != NULL)
	{
		for(a = 0; a < numRecipes; a++)
		{
			fprintf(RecipeList, "%s\n", aRecipes[a].name);
			fprintf(RecipeList, "%d servings %s\n", aRecipes[a].servings, aRecipes[a].class);
			fprintf(RecipeList, "Ingredients %d\n", aRecipes[a].numIngredients);
			for(i = 0; i < aRecipes[a].numIngredients; i++)
				fprintf(RecipeList, "%f %s %s\t\t%f\n", aRecipes[a].items[i].quantity, aRecipes[a].items[i].unit, aRecipes[a].items[i].food, aRecipes[a].items[i].calories);
			fprintf(RecipeList, "Steps:\n");
			for(j = 0; j < aRecipes[a].numSteps; j++)
				fprintf(RecipeList, "%d. %s\n", j + 1, aRecipes[a].steps[j]);
		}
		fclose(RecipeList);
	}
	else
		printf("Error loading file. Please try again.\n");
}

/*
	Function 16: Import Recipes
	This function checks for user's password
	Precondition: option must be a single character
	@param aRecipes[] - list of recipes
	@param numRecipes - number of recipes
	@param filename - name of file user will load recipes from
*/
void ImportRecipes(recipeType aRecipes[], int numRecipes, string filename)
{
	FILE *RecipeList;
	int a, i, j;
	if((RecipeList = fopen(filename, "r")) != NULL)
	{
		for(a = 0; a < numRecipes; a++)
		{
			fprintf(RecipeList, "%s\n", aRecipes[a].name);
			fprintf(RecipeList, "%d servings %s\n", aRecipes[a].servings, aRecipes[a].class);
			fprintf(RecipeList, "Ingredients %d\n", aRecipes[a].numIngredients);
			for(i = 0; i < aRecipes[a].numIngredients; i++)
				fprintf(RecipeList, "%f %s %s\t\t%f\n", aRecipes[a].items[i].quantity, aRecipes[a].items[i].unit, aRecipes[a].items[i].food, aRecipes[a].items[i].calories);
			fprintf(RecipeList, "Steps:\n");
			for(j = 0; j < aRecipes[a].numSteps; j++)
				fprintf(RecipeList, "%d. %s\n", j + 1, aRecipes[a].steps[j]);
		}
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
	@param 
*/
void ShoppingList(recipeType aRecipes[], int numRecipes)
{
	int i, index, num;
	string recipe;
	printf("********* Generate Shopping List *********\n");
	DisplayRecipeTitles(aRecipes, numRecipes);
	printf("Choose recipe: ");
	scanf("%[^\n]", recipe);
	index = SearchName(aRecipes, recipe, numRecipes);
	printf("Enter number of people: ");	
	scanf(" %d", &num);
	printf("List of ingredients for %s:\n", aRecipes[index].name);
	for(i = 0; i < aRecipes[index].numIngredients; i++)
		printf("%f %s\n", aRecipes[index].items[i].quantity * num, aRecipes[index].items[i].food);
}

/*
	Function 19: Recommend Menu
	This function searches a recipe according to its ingredient
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void RecommendMenu(recipeType aRecipes[], int numRecipes, float calorie_goal)
{
	int a, b, c, closest = 0, counter = 0, i;
	recipeType recommend[3];
	for(a = 0; a < numRecipes; a++)
	{
		if(strcmp(aRecipes[a].class, "main") == 0)
		{
			if(aRecipes[a].calorie_total > aRecipes[closest].calorie_total && aRecipes[a].calorie_total <= calorie_goal)
				closest = a;
			recommend[0] = aRecipes[closest];
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
					closest = b;
				recommend[1] = aRecipes[closest];
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
					closest = c;
				recommend[2] = aRecipes[closest];
			}
		}
	}
	for(i = 0; i < 3; i++)
		DisplayRecipe(recommend[i]);
}