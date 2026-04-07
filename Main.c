/****************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the
concepts learned. I have constructed the functions and their respective algorithms and corresponding code by
myself. The program was run, tested, and debugged by my own efforts. I further certify that I have not copied in
part or whole or otherwise plagiarized the work of other students and/or persons, nor did I employ the use of AI 
in any part of the deliverable.
Eryn Claire Go Sy, DLSU ID# 12506621
****************************************************************************************************/

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

	printf("********************** Main Menu **********************\n");
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
					printf("\n**************** Update Recipe Box ****************\n");
					printf("[0] Return to Main Menu\n");
					printf("[1] Add Food-Calorie Info\n");
					printf("[2] Delete Food-Calorie Info\n");
					printf("[3] View Food-Calorie Chart\n");
					printf("[4] Save Calorie Info\n");
					printf("[5] Load Calorie Info\n");
					printf("[6] Add Recipe\n");
					printf("[7] Modify Recipe\n");
					printf("[8] Delete Recipe\n");
					printf("[9] List Recipe Titles\n");
					printf("[10] Scan Recipes\n");
					printf("[11] Search Recipe by Title\n");
					printf("[12] Scan Recipes by Ingredient\n");
					printf("[13] Export Recipes\n");
					printf("[14] Import Recipes\n");
					printf("[15] Change Username and/or Password\n");
					printf("Choose an update option from 0-15: ");
					scanf(" %d", &box_option);
					scanf("%c", &garbage);
					printf("\n");
					
					while(box_option < 0 || box_option > 15)
					{
						printf("Invalid option. Please try again: ");
						scanf(" %d", &box_option);
						scanf("%c", &garbage);
						printf("\n");
					}

					if(box_option == 1)
					{
						printf("********* Add Food-Calorie Info ********\n");
						if(calorie_info_count == 50)
							printf("Food item count is at limit, cannot add more.\n");
						else
							AddFoodCalorie(calorie_input, calorie_info, &calorie_info_count);
					}
					
					else if(box_option == 2)
					{
						printf("******* Delete Food-Calorie Info *******\n");
						if(calorie_info_count != 0)
						{
							printf("Enter food item to delete: ");
							scanf("%[^\n]", food);
							scanf("%c", &garbage);
						}
						DeleteFoodCalorie(calorie_info, &calorie_info_count, food);
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
						if(numRecipes == 50)
							printf("Recipe count is at limit, cannot add more.\n");
						else
							AddRecipe(aRecipes, &numRecipes);
					}

					else if(box_option == 7)
					{
						printf("*************** Modify Recipe ***************\n");
						if(numRecipes == 0)
							printf("No recipes to modify.\n");
						else
						{
							DisplayRecipeTitles(aRecipes, &numRecipes);
							printf("Choose recipe: ");
							scanf("%[^\n]", recipeTitle);
							scanf("%c", &garbage);
							recipe_index = SearchName(aRecipes, &numRecipes, recipeTitle);
							if(recipe_index != -1)
							{
								do
								{
									printf("Editing %s...\n", aRecipes[recipe_index].name);
									printf("[0] Return to Update Menu\n");
									printf("[1] Change Recipe Title\n");
									printf("[2] Change Class\n");
									printf("[3] Change Servings\n");
									printf("[4] Add Ingredient\n");
									printf("[5] Delete Ingredient\n");
									printf("[6] Add Step\n");
									printf("[7] Delete Step\n");
									printf("[8] Display Recipe\n");
									printf("Choose what to modify from 0-8: ");
									scanf(" %d", &recipe_option);
									scanf("%c", &garbage);
									printf("\n");
									while(recipe_option < 0 || recipe_option > 8)
									{
										printf("Invalid option. Choose from 0-8 only: ");
										scanf(" %d", &recipe_option);
										scanf("%c", &garbage);
									}
									if(recipe_option != 0)
									{
										if(recipe_option == 1)
										{
											printf("********** Change Recipe Title *********\n");
											printf("New recipe title: ");
											scanf("%[^\n]", aRecipes[recipe_index].name);
											scanf("%c", &garbage);
										}
										else if(recipe_option == 2)
										{
											printf("************* Change Class *************\n");
											printf("New class: main, starter, or dessert? ");
											scanf("%s", aRecipes[recipe_index].class);
											scanf("%c", &garbage);
										}
										else if(recipe_option == 3)
										{
											printf("************ Change Servings ***********\n");
											printf("New servings: ");
											scanf("%d", &aRecipes[recipe_index].servings);
											scanf("%c", &garbage);
										}
										else if(recipe_option == 4)
										{
											printf("************ Add Ingredient ************\n");
											if(aRecipes[recipe_index].numIngredients <= MAX_INGREDIENTS)
											{
												ingredient_index = aRecipes[recipe_index].numIngredients;
												aRecipes[recipe_index].items[ingredient_index] = AddIngredient(aRecipes[recipe_index].items[ingredient_index]);
												aRecipes[recipe_index].numIngredients++;
											}
											else
												printf("Cannot add any more ingredients.\n");
										}
										else if(recipe_option == 5)
										{
											printf("*********** Delete Ingredient **********\n");
											if(aRecipes[recipe_index].numIngredients <= 1)
												printf("Cannot delete any more ingredients.\n");
											else
											{
												printf("Ingredient: ");
												scanf("%[^\n]", ingredient);
												scanf("%c", &garbage);
												DeleteIngredient(&aRecipes[recipe_index], food);
											}
										}
										else if(recipe_option == 6)
										{
											printf("*************** Add Step ***************\n");
											if(aRecipes[recipe_index].numSteps > MAX_STEPS)
												printf("Step count has exceeded limit.\n");
											else
											{
												printf("Enter step number to insert: ");
												scanf("%d", &step_insert);
												scanf("%c", &garbage);
												while(step_insert - 1 > aRecipes[recipe_index].numSteps)
												{
													printf("Invalid placement. Please try again: ");
													scanf("%d", &step_insert);
													scanf("%c", &garbage);
												}
												printf("Enter step: ");
												scanf("%[^\n]", step);
												scanf("%c", &garbage);
												AddStep(&aRecipes[recipe_index], step_insert, step);
											}
										}
										else if(recipe_option == 7)
										{
											printf("************** Delete Step *************\n");
											if(aRecipes[recipe_index].numSteps == 1)
												printf("Cannot delete any more steps.\n");
											else
											{
												printf("Enter step number to delete: ");
												scanf("%d", &step_remove);
												scanf("%c", &garbage);
												while(step_remove - 1 > aRecipes[recipe_index].numSteps || step_remove < 1)
												{
													printf("Invalid step number. Please try again: \n");
													scanf("%d", &step_remove);
													scanf("%c", &garbage);
												}
												DeleteStep(&aRecipes[recipe_index], step_remove);
											}
										}
										else if(recipe_option == 8)
											DisplayRecipe(aRecipes[recipe_index]);
									}
								} while(recipe_option != 0);
							}
							else
								printf("Recipe not found.\n");
						}
					}

					else if(box_option == 8)
					{
						printf("************* Delete Recipe ************\n");
						DisplayRecipeTitles(aRecipes, &numRecipes);
						printf("Enter recipe to delete: ");
						scanf("%[^\n]", recipeTitle);
						scanf("%c", &garbage);
						DeleteRecipe(aRecipes, &numRecipes, recipeTitle);
					}

					else if(box_option == 9)
					{
						printf("************ List of Recipes ***********\n");
						if(numRecipes == 0)
							printf("No recipes to view.\n");
						else
							DisplayRecipeTitles(aRecipes, &numRecipes);
					}

					else if(box_option == 10)
					{
						AlphabeticalSort(aRecipes, &numRecipes);
						a = 0;
						printf("************* Scan Recipes *************\n");
						if(numRecipes == 0)
							printf("No recipes to view.\n");
						else
						{
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
								printf("\n");
							}while(a < numRecipes && displaynext != 'X');
						}
					}

					else if(box_option == 11)
					{
						printf("******** Search Recipe by Title ********\n");
						if(numRecipes == 0)
							printf("No recipes to search.\n");
						else
						{
							DisplayRecipeTitles(aRecipes, &numRecipes);
							printf("Enter recipe title: ");
							scanf("%[^\n]", recipeTitle);
							recipe_index = SearchName(aRecipes, &numRecipes, recipeTitle);
							if(recipe_index == -1)
								printf("Recipe not found.\n");
							else
								DisplayRecipe(aRecipes[recipe_index]);
						}
					}
				
					else if(box_option == 12)
					{
						printf("****** Scan Recipes By Ingredient ******\n");
						if(numRecipes == 0)
							printf("No recipes to search.\n");
						else
							ScanByIngredient(aRecipes, &numRecipes, savedRecipes);
					}

					else if(box_option == 13)
					{
						printf("************ Export Recipes ************\n");
						printf("Save data to what file? ");
						scanf("%[^\n]", filename);
						ExportRecipes(aRecipes, &numRecipes, filename);
					}

					else if(box_option == 14)
					{
						printf("************ Import Recipes ************\n");
						printf("Load data from what file? ");
						scanf("%[^\n]", filename);
						ImportRecipes(aRecipes, &numRecipes, filename);
					}

					else if(box_option == 15)
					{
						printf("******** Change Username or Password ********\n");
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
				DeleteFoodCalorie(calorie_info, &calorie_info_count, calorie_info[b].food);
			calorie_info[0] = (ingredientType){0};
			for(c = 0; c < numRecipes; c++)
				DeleteRecipe(aRecipes, &numRecipes, aRecipes[c].name);
			aRecipes[0] = (recipeType){0};
		}
		else if(main_option == 'A')
		{
			do
			{
				printf("\n**************** Access Recipe Box ****************\n");
				printf("[0] Return to Main Menu\n");
				printf("[1] Load Calorie Info\n");
				printf("[2] View Food-Calorie Chart\n");
				printf("[3] Import Recipes\n");
				printf("[4] List Recipe Titles\n");
				printf("[5] Scan Recipes\n");
				printf("[6] Search Recipe by Title\n");
				printf("[7] Scan Recipes by Ingredient\n");
				printf("[8] Generate Shopping List\n");
				printf("[9] Recommend Menu\n");
				printf("Choose an access option from 0-9: ");
				scanf(" %d", &box_option);
				scanf("%c", &garbage);
				printf("\n");
				
				while(box_option < 0 || box_option > 9)
				{
					printf("Invalid option. Please try again: ");
					scanf(" %d", &box_option);
					scanf("%c", &garbage);
					printf("\n");
				}
				
				if(box_option == 1)
				{
					printf("******** Load Food-Calorie Info ********\n");
					printf("Load data from what file? ");
					scanf("%[^\n]", filename);
					LoadCalorie(filename, calorie_info, &calorie_info_count);
				}

				else if(box_option == 2)
				{
					printf("********** Food-Calorie Chart **********\n");
					if(calorie_info_count == 0)
						printf("No data to view.\n");
					else
						ViewCalorie(calorie_info, &calorie_info_count);
				}

				else if(box_option == 3)
				{
					printf("************ Import Recipes ************\n");
					printf("Load data from what file? ");
					scanf("%[^\n]", filename);
					ImportRecipes(aRecipes, &numRecipes, filename);
				}

				else if(box_option == 4)
				{
					printf("************ List of Recipes ***********\n");
					if(numRecipes == 0)
						printf("No recipes to view.\n");
					else
						DisplayRecipeTitles(aRecipes, &numRecipes);
				}

				else if(box_option == 5)
				{
					AlphabeticalSort(aRecipes, &numRecipes);
					a = 0;
					printf("************* Scan Recipes *************\n");
					if(numRecipes == 0)
						printf("No recipes to view.\n");
					else
					{
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
						} while(a < numRecipes && displaynext != 'X');
					}
				}

				else if(box_option == 6)
				{
					printf("******** Search Recipe by Title ********\n");
					if(numRecipes == 0)
						printf("No recipes to search.\n");
					else
					{
						DisplayRecipeTitles(aRecipes, &numRecipes);
						printf("Enter recipe title: ");
						scanf("%[^\n]", recipeTitle);
						recipe_index = SearchName(aRecipes, &numRecipes, recipeTitle);
						if(recipe_index == -1)
							printf("Recipe not found.\n");
						else
							DisplayRecipe(aRecipes[recipe_index]);
					}
				}
				
				else if(box_option == 7)
				{
					printf("****** Scan Recipes By Ingredient ******\n");
					if(numRecipes == 0)
						printf("No recipes to search.\n");
					else
						ScanByIngredient(aRecipes, &numRecipes, savedRecipes);
				}

				else if(box_option == 8)
				{
					printf("******** Generate Shopping List ********\n");
					ShoppingList(aRecipes, &numRecipes);
				}
				
				else if(box_option == 9)
				{
					printf("********** Menu Recommendation *********\n");
					printf("Enter calorie goal: ");
					scanf("%f", &calorie_goal);
					scanf("%c", &garbage);
					RecommendMenu(aRecipes, &numRecipes, calorie_goal);
				}

				CalorieMatcher(aRecipes, &numRecipes, calorie_info, &calorie_info_count);
			}while(box_option != 0);

			for(b = 0; b < calorie_info_count; b++)
				DeleteFoodCalorie(calorie_info, &calorie_info_count, calorie_info[b].food);
			calorie_info[0] = (ingredientType){0};
			for(c = 0; c < numRecipes; c++)
				DeleteRecipe(aRecipes, &numRecipes, aRecipes[c].name);
			aRecipes[0] = (recipeType){0};
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