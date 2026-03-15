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
			printf("Old username: ");
			scanf("%[^\n]", old_password);
			printf("New username: ");
			scanf("%[^\n]", new_username);
		}
		else if(option == 'P')
		{
			printf("Old password: ");
			scanf("%[^\n]", old_password);
			printf("New password: ");
			scanf("%[^\n]", new_password);
		}
		else
			printf("Invalid input, please try again.\n");
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
	printf("View next 10 items? Press 'N' to proceed; press 'X' to exit.\n");
	scanf(" %c", &option);
	while(option != 'X')
	{
		while(a % 10 != 0)
		{
			printf("%s\t\t%f\t\t%s\t\t%f\n", ingredient[a].food, ingredient[a].quantity, ingredient[a].unit, ingredient[a].calories);
			a++;
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
void SaveCalorie(ingredientType ingredient[], int *numItems)
{
	FILE *CalText;
	int a;
	printf("******* Save Food-Calorie Info *******\n");
	printf("Save data to what file? ");
	scanf("%[^\n]", CalText);
	if(fopen(CalText, "w") != NULL)
	{
		for(a = 0; a < *numItems; a++)
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
recipeType AddRecipe(string dish, string class, int servings, ingredientType ingredient[], string step)
{
	int a;
	recipeType aRecipe;
	strcpy(aRecipe.name, dish);
	strcpy(aRecipe.class, class);
	aRecipe.servings = servings;
	aRecipe.items[a] = ingredient[a];
	strcpy(aRecipe.steps[a], step);
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
void DeleteIngredient(recipeType aRecipe, string ingredient)
{
	int a = 0, i;
	int delete = Search(aRecipe.items, ingredient, aRecipe.numIngredients);
	while(a < aRecipe.numIngredients)
	{
		if(strcmp(aRecipe.items[delete].food, ingredient) == 0)
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
					strcpy(aRecipe.steps[i], aRecipe.steps[i + 1]);
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
void DeleteRecipe(recipeType aRecipe[], string recipeTitle, int *numRecipes)
{
	int a = 0, i;
	int delete = Search(recipeTitle, aRecipe, *numRecipes);
	while(a < *numRecipes)
	{
		if(strcmp(aRecipe[a].name, recipeTitle) == 0)
		{
			if(a < *numRecipes - 1)
			{
				for(i = a; i < *numRecipes - 1; i++)
					aRecipe[i] = aRecipe[i + 1];
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
	AlphabeticalSort(aRecipes, *numRecipes);
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
void ExportRecipes(recipeType aRecipes[], int *numRecipes, string filename)
{
	FILE *RecipeList;
	int a, i, j;
	printf("Save data to what file? ");
	scanf("%[^\n]", RecipeList);
	if(RecipeList = fopen(" ", "w"))
	{
		for(a = 0; a < *numRecipes; a++)
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
		fclose(filename);
	}
}

/*
	Function 16: Import Recipes
	This function checks for user's password
	Precondition: option must be a single character
	@param option is the user's input into the menu items
*/
void ImportRecipes(recipeType aRecipes[], int *numRecipes, string filename)
{
	FILE *RecipeList;
	int a, i, j;
	if(RecipeList = fopen(filename, "r"))
	{
		for(a = 0; a < *numRecipes; a++)
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
		fclose(filename);
	}
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
void ScanByIngredient(recipeType aRecipes[], int *numRecipes, string fooditem, recipeType savedRecipes[])
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
	DisplayRecipeTitles(aRecipes, &numRecipes);
	printf("Choose recipe: ");
	scanf("%[^\n]", recipe);
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
		int index = Search(aRecipes, "Starter", *numRecipes);
		aRecipes[index].calorie_total += aRecipes[index].calorie_total;		// update calorie total
		if(calorie_goal == aRecipes[index].calorie_total)
		{
			
		}
	}
}

int main()
{
	char main_option, recipe_option, user_pass;
	int box_option;
	int c = 0;	// for calorie_info
	int a = 0, b = 0;
	int i = 0, j = 0, n = 0;
	int *numRecipes = 0;	// to be updated whenever the user adds recipes
	int recipe_index;
	recipeType aRecipes[MAX], savedRecipes[MAX];
	string food, unit, recipeTitle, ingredient, step;
	float quantity, calories;
	ingredientType calorie_info[MAX], ingredients[MAX];
	string dish, class, procedure[MAX], filename;
	int servings;
	string username, password, displaynext;
	string sUsername, sPassword;
	strcpy(sUsername, "admin");
	strcpy(sPassword, "ad1234");
	srand(time(NULL));
	
	aRecipes[MAX].numIngredients = 0;
	aRecipes[MAX].numSteps = 0;

	printf("******************** Main Menu ********************\n");
	printf("[U] Update recipe box\n");
	printf("[A] Access recipe box\n");
	printf("[E] Exit\n");
	printf("\nChoose a menu option from A-E: ");
	scanf(" %c", &main_option);
	while(main_option != 'E')
	{
		if(main_option == 'U')
		{
			printf("Username: ");
			scanf("%[^\n]", username);
			printf("Password: ");
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
					calorie_info[c] = AddIngredient(food, quantity, unit, calories);
					c++;
				}
				else if(box_option == 2)
				{
					printf("******** Food-Calorie Chart ********\n");
					if(c == 0)
						printf("No data to view.\n");
					else
						ViewCalorie(&calorie_info[c]);
				}
				else if(box_option == 3)
					SaveCalorie(calorie_info, &c);
				else if(box_option == 4)
					LoadCalorie(calorie_info[c]);
				else if(box_option == 5)
				{
					printf("******* Add Recipe *******\n");
					printf("Recipe: ");
					scanf("%[^\n]", dish);
					printf("Class: ");
					scanf("%[^\n]", class);
					printf("Servings: ");
					scanf(" %d", &servings);
					printf("Ingredients: ");
					do
					{
						ingredients[i] = AddIngredient(food, quantity, unit, calories);
					} while(strcmp(ingredients[i++].food, "888"));
					do
					{
						scanf("%[^\n]", procedure[j]);
					} while (strcmp(procedure[j++], "888"));
					aRecipes[*numRecipes] = AddRecipe(dish, class, servings, ingredients, procedure);
					(*numRecipes)++;
				}
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
						printf("Choose recipe: ");
						scanf("%[^\n]", recipeTitle);
						recipe_index = Search(aRecipes, recipeTitle, &numRecipes);
						printf("Choose what to modify from 0-4: ");
						scanf(" %d", &recipe_option);
						if(recipe_option == 1)
						{
							printf("********** Add Ingredient **********\n");
							printf("Food item: ");
							scanf("%[^\n]", food);
							printf("Quantity: ");
							scanf(" %f", &quantity);
							printf("Unit: ");
							scanf("%[^\n]", unit);
							printf("Calorie amount: ");
							scanf(" %f", &calories);
							aRecipes[recipe_index].items[aRecipes[recipe_index].numIngredients] = AddIngredient(food, quantity, unit, calories);
							aRecipes[recipe_index].numIngredients++;
						}
						else if(recipe_option == 2)
						{
							printf("********** Delete Recipe **********\n");
							printf("Ingredient: ");
							scanf("%[^\n]", food);
							DeleteIngredient(aRecipes[recipe_index], food);
						}
						else if(recipe_option == 3)
						{
							printf("************* Add Step *************\n");
							printf("Enter step: ");
							scanf("%[^\n]", step);
							AddStep(aRecipes[recipe_index], step);
						}
						else if(recipe_option == 4)
						{
							printf("*********** Delete Step ***********\n");
							printf("Enter step: ");
							scanf("%[^\n]", step);
							DeleteStep(aRecipes[recipe_index], step, &aRecipes[recipe_index].numSteps);
						}
					}while(recipe_option != 0);
				}
				else if(box_option == 7)
				{
					printf("*********** Delete Recipe ***********\n");
					DeleteRecipe(aRecipes, recipeTitle, &numRecipes);
				}
				else if(box_option == 8)
					DisplayRecipeTitles(aRecipes, &numRecipes);
				else if(box_option == 9)
				{
					AlphabeticalSort(aRecipes, &numRecipes);
					a = 0;
					printf("*********** Scan Recipes ***********\n");
					do
					{
						DisplayRecipe(aRecipes[a]);
						a++;
						printf("Display next recipe? Press N for next or X for exit. ");
						scanf("%s", displaynext);
						while(displaynext != 'N')
						{
							printf("Invalid input, please try again. ");
							scanf("%s", displaynext);
						}
					}while(displaynext != 'X');
				}
				else if(box_option == 10)
				{
					printf("******* Search recipe by title *******\n");
					DisplayRecipeTitles(aRecipes, &numRecipes);
					printf("Choose recipe: ");
					scanf("%[^\n]", recipeTitle);
					recipe_index = Search(aRecipes, recipeTitle, &numRecipes);
					DisplayRecipe(aRecipes[recipe_index]);
				}
				else if(box_option == 11)
				{
					printf("********** Export Recipes **********\n");
					printf("Save data to what file? ");
					scanf("%[^\n]", filename);
					ExportRecipes(aRecipes, &numRecipes, filename);
				}
				else if(box_option == 12)
				{
					printf("********** Import Recipes **********\n");
					printf("Load data to what file? ");
					scanf("%[^\n]", filename);
					ImportRecipes(aRecipes, &numRecipes, filename);
				}
				else if(box_option == 13)
				{
					printf("********** Change Username or Password **********\n");
					printf("What will you change? Press U for username or P for password. ");
					scanf("%c", &user_pass);
					AccessModifier(user_pass);
				}
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
				{
					printf("********** Import Recipes **********\n");
					printf("Load data to what file? ");
					scanf("%[^\n]", filename);
					ImportRecipes(aRecipes, &numRecipes, filename);
				}
				else if(box_option == 2)
					DisplayRecipeTitles(aRecipes, &numRecipes);
				else if(box_option == 3)
				{
					AlphabeticalSort(aRecipes, &numRecipes);
					a = 0;
					printf("*********** Scan Recipes ***********\n");
					do
					{
						DisplayRecipe(aRecipes[a]);
						a++;
						printf("Display next recipe? Press N for next or X for exit. ");
						scanf("%s", displaynext);
						while(displaynext != 'N')
						{
							printf("Invalid input, please try again. ");
							scanf("%s", displaynext);
						}
					}while(displaynext != 'X');
				}
				else if(box_option == 4)
				{
					AlphabeticalSort(aRecipes, &numRecipes);
					a = 0;
					printf("Enter ingredient: ");
					scanf("%[^\n]", ingredient);
					printf("******** Scan Recipes By Ingredient ********\n");
					do
					{
						ScanByIngredient(aRecipes, &numRecipes, ingredient, savedRecipes);
						a++;
						printf("Display next recipe? Press N for next or X for exit. ");
						scanf("%s", displaynext);
						while(displaynext != 'N')
						{
							printf("Invalid input, please try again. ");
							scanf("%s", displaynext);
						}
					}while(displaynext != 'X');
				}
				else if(box_option == 5)
					ShoppingList(aRecipes, &numRecipes);
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