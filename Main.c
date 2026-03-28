#include "MachProj.c"

int main()
{
	char main_option, displaynext;
	char garbage;
	int access_check, recipe_option, box_option;
	int calorie_info_count = 0;		// to be updated whenever the user adds food items
	int numRecipes = 0;		// to be updated whenever the user adds recipes
	int a, b, c, recipe_index, ingredient_index, step_insert, step_remove;
	recipeType aRecipes[MAX], savedRecipes[MAX];
	string food, recipeTitle, ingredient, filename;
	ingredientType calorie_input, calorie_info[MAX];
	float calorie_goal;
	string_step step;
	string username, password, current_username, current_password;
	strcpy(current_username, "admin");
	strcpy(current_password, "ad1234");
	
	aRecipes[MAX_INGREDIENTS].numIngredients = 0;
	aRecipes[MAX_STEPS].numSteps = 0;
	srand(time(NULL));

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
					printf("[2] Add food-calorie info\n");
					printf("[3] View food-calorie chart\n");
					printf("[4] Save calorie info\n");
					printf("[5] Load calorie info\n");
					printf("[6] Add recipe\n");
					printf("[7] Modify recipe\n");
					printf("[8] Delete recipe\n");
					printf("[9] List recipe titles\n");
					printf("[10] Scan recipes\n");
					printf("[11] Search recipe by title\n");
					printf("[12] Export recipes\n");
					printf("[13] Import recipes\n");
					printf("[14] Change username and/or password\n");
					printf("Choose an update option from 0-13: ");
					scanf(" %d", &box_option);
					scanf("%c", &garbage);
					printf("\n");
					
					if(box_option == 1)
					{
						printf("********* Add Food-Calorie Info ********\n");
						calorie_info[calorie_info_count] = AddFoodCalorie(calorie_input);
						calorie_info_count++;
					}
					
					else if(box_option == 2)
					{
						printf("******* Delete Food-Calorie Info *******\n");
						printf("Enter food item to delete: ");
						scanf("%[^\n]", food);
						scanf("%c", &garbage);
					}

					else if(box_option == 3)
					{
						printf("********** Food-Calorie Chart **********\n");
						if(calorie_info_count == 0)
							printf("No data to view.\n");
						else
							ViewCalorie(calorie_info, &calorie_info_count);
					}

					else if(box_option == 4)
					{
						printf("******** Save Food-Calorie Info ********\n");
						printf("Save data to what file? ");
						scanf("%[^\n]", filename);
						SaveCalorie(filename, calorie_info, &calorie_info_count);
					}

					else if(box_option == 5)
					{
						printf("******** Load Food-Calorie Info ********\n");
						printf("Load data from what file? ");
						scanf("%[^\n]", filename);
						LoadCalorie(filename, calorie_info, &calorie_info_count);
					}

					else if(box_option == 6)
					{
						printf("************** Add Recipe **************\n");
						AddRecipe(aRecipes, &numRecipes);
					}

					else if(box_option == 7)
					{
						printf("************** Modify Recipe **************\n");
						DisplayRecipeTitles(aRecipes, &numRecipes);
						printf("Choose recipe: ");
						scanf("%[^\n]", recipeTitle);
						scanf("%c", &garbage);
						recipe_index = SearchName(aRecipes, &numRecipes, recipeTitle);
						do
						{
							printf("[0] Return to update menu\n");
							printf("[1] Add ingredient\n");
							printf("[2] Delete ingredient\n");
							printf("[3] Add step\n");
							printf("[4] Delete step\n");
							printf("Choose what to modify from 0-4: ");
							scanf(" %d", &recipe_option);
							scanf("%c", &garbage);
							while(recipe_option < 0 || recipe_option > 4)
							{
								printf("Invalid option. Choose from 0-4 only: ");
								scanf(" %d", &recipe_option);
								scanf("%c", &garbage);
							}
							if(recipe_option != 0)
							{
								if(recipe_option == 1)
								{
									printf("********** Add Ingredient **********\n");
									ingredient_index = aRecipes[recipe_index].numIngredients;
									aRecipes[recipe_index].items[ingredient_index] = AddIngredient(aRecipes[recipe_index].items[ingredient_index]);
									aRecipes[recipe_index].numIngredients++;
								}
								else if(recipe_option == 2)
								{
									printf("********* Delete Ingredient ********\n");
									printf("Ingredient: ");
									scanf("%[^\n]", ingredient);
									scanf("%c", &garbage);
									DeleteIngredient(&aRecipes[recipe_index], food);
								}
								else if(recipe_option == 3)
								{
									printf("************* Add Step *************\n");
									printf("Enter step number to insert: ");
									scanf("%d", &step_insert);
									scanf("%c", &garbage);
									printf("Enter step: ");
									scanf("%[^\n]", step);
									scanf("%c", &garbage);
									AddStep(&aRecipes[recipe_index], step_insert, step);
								}
								else if(recipe_option == 4)
								{
									printf("************ Delete Step ***********\n");
									printf("Enter step number to delete: ");
									scanf("%d", &step_remove);
									scanf("%c", &garbage);
									DeleteStep(&aRecipes[recipe_index], step_remove);
								}
							}
							printf("\n");
						} while(recipe_option != 0);
					}

					else if(box_option == 8)
					{
						printf("*********** Delete Recipe ***********\n");
						DisplayRecipeTitles(aRecipes, &numRecipes);
						printf("Enter recipe to delete: ");
						scanf("%[^\n]", recipeTitle);
						scanf("%c", &garbage);
						DeleteRecipe(aRecipes, &numRecipes, recipeTitle);
					}

					else if(box_option == 9)
					{
						printf("********* List of Recipes *********\n");
						DisplayRecipeTitles(aRecipes, &numRecipes);
					}

					else if(box_option == 10)
					{
						AlphabeticalSort(aRecipes, &numRecipes);
						a = 0;
						printf("*********** Scan Recipes ***********\n");
						do
						{
							DisplayRecipe(aRecipes[a]);
							a++;
							if(a < numRecipes)
							{
								printf("Display next recipe? Press N for next or X for exit. ");
								scanf(" %c", &displaynext);
								scanf("%c", &garbage);
								while(displaynext != 'N' && displaynext != 'X')
								{
									printf("Invalid input, please try again. ");
									scanf(" %c", &displaynext);
									scanf("%c", &garbage);
								}
							}
						}while(a < numRecipes && displaynext != 'X');
					}

					else if(box_option == 11)
					{
						printf("********** Recipe Search **********\n");
						DisplayRecipeTitles(aRecipes, &numRecipes);
						printf("Choose recipe: ");
						scanf("%[^\n]", recipeTitle);
						recipe_index = SearchName(aRecipes, &numRecipes, recipeTitle);
						DisplayRecipe(aRecipes[recipe_index]);
					}

					else if(box_option == 12)
					{
						printf("********** Export Recipes **********\n");
						printf("Save data to what file? ");
						scanf("%[^\n]", filename);
						ExportRecipes(aRecipes, &numRecipes, filename);
					}

					else if(box_option == 13)
					{
						printf("********** Import Recipes **********\n");
						printf("Load data from what file? ");
						scanf("%[^\n]", filename);
						ImportRecipes(aRecipes, &numRecipes, filename);
					}

					else if(box_option == 14)
					{
						printf("********** Change Username or Password **********\n");
						AccessModifier(current_username, current_password);
					}

					CalorieMatcher(aRecipes, &numRecipes, calorie_info, &calorie_info_count);
				} while(box_option != 0);
			}
			else if(access_check == 2)
				printf("Invalid username. Please try again.\n");
			else if(access_check == 1)
				printf("Invalid password. Please try again.\n");
			else
				printf("Invalid username and password. Please try again.\n");

			for(b = 0; b < calorie_info_count; b++)
				DeleteFoodCalorie(calorie_info, &calorie_info_count, &calorie_info[b]);
			for(c = 0; c < numRecipes; c++)
				DeleteRecipe(aRecipes, numRecipes, aRecipes[c].name);
		}
		else if(main_option == 'A')
		{
			do
			{
				printf("\n************** Access Recipe Box **************\n");
				printf("[0] Return to main menu\n");
				printf("[1] Load calorie info\n");
				printf("[2] Import recipes\n");
				printf("[3] List recipe titles\n");
				printf("[4] Display recipes\n");
				printf("[5] Scan recipes by ingredient\n");
				printf("[6] Generate shopping list\n");
				printf("[7] Recommend menu\n");
				printf("Choose an access option from 0-7: ");
				scanf(" %d", &box_option);
				scanf("%c", &garbage);
				printf("\n");
				
				if(box_option == 1)
				{
					printf("******* Load Food-Calorie Info *******\n");
					printf("Load data from what file? ");
					scanf("%[^\n]", filename);
					LoadCalorie(filename, calorie_info, &calorie_info_count);
				}

				else if(box_option == 2)
				{
					printf("********** Import Recipes **********\n");
					printf("Load data from what file? ");
					scanf("%[^\n]", filename);
					ImportRecipes(aRecipes, &numRecipes, filename);
				}

				else if(box_option == 3)
				{
					printf("********* List of Recipes *********\n");
					DisplayRecipeTitles(aRecipes, &numRecipes);
				}

				else if(box_option == 4)
				{
					AlphabeticalSort(aRecipes, &numRecipes);
					a = 0;
					printf("*********** Scan Recipes ***********\n");
					do
					{
						DisplayRecipe(aRecipes[a]);
						a++;
						if(a < numRecipes)
						{
							printf("Display next recipe? Press N for next or X for exit. ");
							scanf(" %c", &displaynext);
							scanf("%c", &garbage);
							while(displaynext != 'N' && displaynext != 'X')
							{
								printf("Invalid input, please try again. ");
								scanf(" %c", &displaynext);
								scanf("%c", &garbage);
							}
						}
					}while(a < numRecipes && displaynext != 'X');
				}

				else if(box_option == 5)
				{
					printf("******** Scan Recipes By Ingredient ********\n");
					printf("Enter ingredient: ");
					scanf("%[^\n]", ingredient);
					scanf("%c", &garbage);
					ScanByIngredient(aRecipes, &numRecipes, ingredient, savedRecipes);
				}

				else if(box_option == 6)
				{
					printf("********* Generate Shopping List *********\n");
					ShoppingList(aRecipes, &numRecipes);
				}
				
				else if(box_option == 7)
				{
					printf("******* Menu Recommendation *******\n");
					printf("Enter calorie goal: ");
					scanf("%f", &calorie_goal);
					scanf("%c", &garbage);
					RecommendMenu(aRecipes, &numRecipes, calorie_goal);
				}

				CalorieMatcher(aRecipes, &numRecipes, calorie_info, &calorie_info_count);
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
		scanf("%c", &garbage);
	}
	return 0;
}