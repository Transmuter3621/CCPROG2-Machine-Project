#include "MachProj.c"

int main()
{
	char main_option, displaynext;
	char garbage;
	int access_check, recipe_option, box_option;
	int a, i = 0, calorie_info_count = 0;
	int numRecipes = 0;		// to be updated whenever the user adds recipes
	int recipe_index, ingredient_index;
	recipeType aRecipes[MAX], savedRecipes[MAX];
	string food, recipeTitle, ingredient, filename;
	ingredientType calorie_input, calorie_info[MAX], calorie_add[MAX];
	float calorie_goal;
	string_step step;
	string username, password, current_username, current_password;
	strcpy(current_username, "admin");
	strcpy(current_password, "ad1234");
	
	aRecipes[MAX_INGREDIENTS].numIngredients = 0;
	aRecipes[MAX_STEPS].numSteps = 0;

	printf("******************** Main Menu ********************\n");
	printf("[U] Update recipe box\n");
	printf("[A] Access recipe box\n");
	printf("[E] Exit\n");
	printf("Choose a menu option: ");
	scanf("%c", &main_option);
	scanf("%c", &garbage);
	while(main_option != 'E')
	{
		if(main_option == 'U')
		{
			printf("Username: ");
			scanf("%[^\n]", username);
			scanf("%c", &garbage);
			printf("Password: ");
			scanf("%[^\n]", password);
			scanf("%c", &garbage);
			access_check = PassCheck(username, current_username, password, current_password);
			if(access_check == 3)
			{
				do
				{
					printf("\n************** Update Recipe Box **************\n");
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
					scanf(" %d", &box_option);
					scanf("%c", &garbage);
					printf("\n");
					
					if(box_option == 1)
					{
						printf("******* Add Food-Calorie Info *******\n");
						calorie_info[calorie_info_count] = AddFoodCalorie(calorie_input);
						calorie_info_count++;
					}

					else if(box_option == 2)
					{
						printf("******** Food-Calorie Chart ********\n");
						if(calorie_info_count == 0)
							printf("No data to view.\n");
						else
							ViewCalorie(calorie_info, calorie_info_count);
					}

					else if(box_option == 3)
					{
						printf("******* Save Food-Calorie Info *******\n");
						printf("Save data to what file? ");
						scanf("%[^\n]", filename);
						SaveCalorie(calorie_info, calorie_info_count, filename);
					}

					else if(box_option == 4)
					{
						printf("******* Load Food-Calorie Info *******\n");
						printf("Load data from what file? ");
						scanf("%[^\n]", filename);
						if(calorie_info_count == 0)
							printf("File has no content.\n");
						else
							LoadCalorie(calorie_add[i], filename, calorie_info, calorie_info_count);
					}

					else if(box_option == 5)
					{
						printf("******* Add Recipe *******\n");
						aRecipes[numRecipes] = AddRecipe(aRecipes[numRecipes], calorie_info, calorie_info_count);
						numRecipes++;
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
							recipe_index = SearchName(aRecipes, recipeTitle, numRecipes);
							printf("Choose what to modify from 0-4: ");
							scanf(" %d", &recipe_option);
							if(recipe_option == 1)
							{
								printf("********** Add Ingredient **********\n");
								ingredient_index = aRecipes[recipe_index].numIngredients;
								aRecipes[recipe_index].items[ingredient_index] = AddIngredient(aRecipes[recipe_index].items[ingredient_index], calorie_info, calorie_info_count);
								aRecipes[recipe_index].numIngredients++;
							}
							else if(recipe_option == 2)
							{
								printf("********* Delete Ingredient ********\n");
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
								printf("************ Delete Step ***********\n");
								printf("Enter step: ");
								scanf("%[^\n]", step);
								DeleteStep(aRecipes[recipe_index], step);
							}
						}while(recipe_option != 0);
					}

					else if(box_option == 7)
					{
						printf("*********** Delete Recipe ***********\n");
						DeleteRecipe(aRecipes, recipeTitle, numRecipes);
					}

					else if(box_option == 8)
					{
						printf("********* List of Recipes *********\n");
						DisplayRecipeTitles(aRecipes, numRecipes);
					}

					else if(box_option == 9)
					{
						AlphabeticalSort(aRecipes, numRecipes);
						a = 0;
						printf("*********** Scan Recipes ***********\n");
						do
						{
							DisplayRecipe(aRecipes[a]);
							a++;
							printf("Display next recipe? Press N for next or X for exit. ");
							scanf("%c", &displaynext);
							while(displaynext != 'N')
							{
								printf("Invalid input, please try again. ");
								scanf("%c", &displaynext);
							}
						}while(displaynext != 'X');
					}

					else if(box_option == 10)
					{
						printf("********** Recipe Search **********\n");
						DisplayRecipeTitles(aRecipes, numRecipes);
						printf("Choose recipe: ");
						scanf("%[^\n]", recipeTitle);
						recipe_index = SearchName(aRecipes, recipeTitle, numRecipes);
						DisplayRecipe(aRecipes[recipe_index]);
					}

					else if(box_option == 11)
					{
						printf("********** Export Recipes **********\n");
						printf("Save data to what file? ");
						scanf("%[^\n]", filename);
						ExportRecipes(aRecipes, numRecipes, filename);
					}

					else if(box_option == 12)
					{
						printf("********** Import Recipes **********\n");
						printf("Load data from what file? ");
						scanf("%[^\n]", filename);
						ImportRecipes(aRecipes, filename);
					}

					else if(box_option == 13)
					{
						printf("********** Change Username or Password **********\n");
						AccessModifier(username, password);
					}
				} while(box_option != 0);
			}
			else if(access_check == 2)
				printf("Invalid username. Please try again.\n");
			else if(access_check == 1)
				printf("Invalid password. Please try again.\n");
			else
				printf("Invalid username and password. Please try again.\n");
		}
		else if(main_option == 'A')
		{
			do
			{
				printf("\n************** Access Recipe Box **************\n");
				printf("[0] Return to main menu\n");
				printf("[1] Import recipes\n");
				printf("[2] List recipe titles\n");
				printf("[3] Display recipes\n");
				printf("[4] Scan recipes by ingredient\n");
				printf("[5] Generate shopping list\n");
				printf("[6] Recommend menu\n");
				printf("Choose an access option from 0-6: ");
				scanf(" %d", &box_option);
				printf("\n");
				
				if(box_option == 1)
				{
					printf("********** Import Recipes **********\n");
					printf("Load data to what file? ");
					scanf("%[^\n]", filename);
					ImportRecipes(aRecipes, filename);
				}

				else if(box_option == 2)
				{
					printf("********* List of Recipes *********\n");
					DisplayRecipeTitles(aRecipes, numRecipes);
				}

				else if(box_option == 3)
				{
					AlphabeticalSort(aRecipes, numRecipes);
					a = 0;
					printf("*********** Scan Recipes ***********\n");
					do
					{
						DisplayRecipe(aRecipes[a]);
						a++;
						printf("Display next recipe? Press N for next or X for exit. ");
						scanf(" %c", &displaynext);
						while(displaynext != 'N')
						{
							printf("Invalid input, please try again. ");
							scanf(" %c", &displaynext);
						}
					}while(displaynext != 'X');
				}

				else if(box_option == 4)
				{
					printf("******** Scan Recipes By Ingredient ********\n");
					AlphabeticalSort(aRecipes, numRecipes);
					a = 0;
					printf("Enter ingredient: ");
					fgets(ingredient, sizeof(ingredient), stdin);
					do
					{
						ScanByIngredient(aRecipes, numRecipes, ingredient, savedRecipes);
						a++;
						printf("Display next recipe? Press N for next or X for exit. ");
						scanf(" %c", &displaynext);
						while(displaynext != 'N')
						{
							printf("Invalid input, please try again. ");
							scanf(" %c", &displaynext);
						}
					}while(displaynext != 'X');
				}

				else if(box_option == 5)
				{
					printf("********* Generate Shopping List *********\n");
					ShoppingList(aRecipes, numRecipes);
				}
				
				else if(box_option == 6)
				{
					printf("******* Menu Recommendation *******\n");
					printf("Enter calorie goal: ");
					scanf("%f", &calorie_goal);
					RecommendMenu(aRecipes, numRecipes, calorie_goal);
				}
			}while(box_option != 0);
		}
		else if(main_option != 'U' && main_option != 'A' && main_option != 'E')
			printf("Invalid option.\n");
		
		printf("\n******************** Main Menu ********************\n");
		printf("[U] Update recipe box\n");
		printf("[A] Access recipe box\n");
		printf("[E] Exit\n");
		printf("\nChoose a menu option: ");
		scanf(" %c", &main_option);
	}
	return 0;
}