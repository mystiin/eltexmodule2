#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define MAX_ITEM 14
#define MAX_MOBS 10

typedef struct
{
    int ID;
    char name[20];
    int value;
    int needstamina;
} Item;
typedef struct
{
    int killmob;
    int cheast;
    int steps;
    int allcash;
} FinalScore;

typedef struct
{
    Item weapon;
    Item armor;
    Item healpotion;
    Item damagepotion;
    Item staminapotion;
    Item items[MAX_ITEM];
} Inventory;

typedef struct
{
    char name[13];
    int damage;
    int hpmon;
    int staminamob;
    int emer; //gold
    int xp;
}Monsters;

void stats(int*, int*, int*);
void statslvlup(int*, int*, int*, int*);
void gameclass(int*, int*, int*, Inventory* inventory, Item* [MAX_ITEM], int*);
void statscheck(int*, int*, int*, int*, int*, int*);
void invcheak(Inventory* inventory, int*);
void shop(Inventory* inventory, int*, Item* item);
void battle(Inventory* inventory, Item* item, Monsters* mob, int*, int*, int*, int*, int*, int*, int*, FinalScore* score);
void chest(Inventory* inventory, Item* item, FinalScore* score);
void lvlup(int*, int*, int*, int*, int*, int*);

int main()
{
    srand(time(NULL));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Размеры
    SMALL_RECT windowSize = { 0, 0, 70, 20 };          // Окна
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize); // Консоли
    puts("                                                                       ");
    puts(" @@@@@@@                             @@@@@                             ");
    puts(" @       @      @@@@@ @@@@@@ @    @ @     @ @@@@@    @@   @@@@@@ @@@@@ ");
    puts(" @       @        @   @       @  @  @       @    @  @  @  @        @   ");
    puts(" @@@@@   @        @   @@@@@    @@   @       @    @ @    @ @@@@@    @   ");
    puts(" @       @        @   @        @@   @       @@@@@  @@@@@@ @        @   ");
    puts(" @       @        @   @       @  @  @     @ @   @  @    @ @        @   ");
    puts(" @@@@@@@ @@@@@@   @   @@@@@@ @    @  @@@@@  @    @ @    @ @        @   ");
    puts("                                                                       ");
    puts("                   PRESS ANY BUTTON TO START NEW GAME                  ");
    char key;
    key = _getch();
    if (key)
    {
        system("cls");
    }
    Item item[MAX_ITEM] =
    { {0, "Wooden Sword", 5, 3},
        {1, "Iron Sword", 7, 4},
        {2, "Diamond Sword",10, 5},
        {3, "Wooden Bow", 6, 4},
        {4, "Iron Bow", 8, 5},
        {5, "Diamond Bow", 12, 7},
        {6, "Wooden trident", 3, 2},
        {7, "Iron trident", 5, 3},
        {8, "Diamond trident", 7, 3},
        {9, "Wooden Armor set", 7, 0},
        {10, "Iron Armor set", 15, 0},
        {11, "Diamond Armor set", 20, 0}
    };
    Monsters mob[MAX_MOBS] =
    {
        {"Zombie", 4, 14, 6, 8, 20},
        {"Skeleton", 5, 15, 5, 10, 22},
        {"Spider", 6, 16, 6, 12, 24},
        {"Piglin", 7, 20, 8, 16, 26},
        {"Gust", 12, 24, 4, 20, 28},
        {"Ifrit", 10, 26, 10, 24, 30},
        {"Enderman", 12, 28, 12, 28, 32},
        {"Enderslime", 13, 32, 20, 30, 34},
        {"Enderwoman", 14, 37, 15, 32, 36},
        {"Ender Dragon", 20, 100, 40, 300, 100}
    };
    Inventory inventory;
    inventory.armor.name[0] = '\0';
    inventory.armor.value = 0;
    inventory.damagepotion.value = 0;
    inventory.healpotion.value = 0;
    inventory.staminapotion.value = 0;
    FinalScore score;
    score.allcash = 0;
    score.cheast = 0;
    score.killmob = 0;
    score.steps = 0;
    int emeralds = 10;
    int HP_player = 20;
    int lvl = 0;
    int xp = 0;
    int strength = 0, stamina = 6, mana = 0;
    gameclass(&strength, &stamina, &mana, &inventory, &item, &HP_player);
    stats(&strength, &stamina, &mana);
    while (1)
    {
        int event = rand() % 100;
        int action;
        printf("1. Check stats\n2. Check inventory\n3. Check lvlup\n4. Next step\nInput: ");
        scanf_s("%d", &action);
        switch (action)
        {
        case 1:
            system("cls");
            statscheck(strength, stamina, mana, HP_player, lvl, xp);
            continue;
        case 2:
            system("cls");
            invcheak(&inventory, emeralds);
            continue;
        case 3:
            system("cls");
            lvlup(&lvl, &xp, &strength, &stamina, &mana, &HP_player);
            continue;
        case 4:
            system("cls");
            if (event > 0 && event < 21) //chance shop
            {
                shop(&inventory, &emeralds, &item);
                continue;
            }
            else if (event > 20 && event < 31) //chance chest
            {
                chest(&inventory, &item, &score);
                continue;
            }
            else //battle
            {
                battle(&inventory, &item, &mob, &HP_player, &emeralds, &stamina, &lvl, &xp, &strength, &mana, &score);
                continue;
            }
            score.steps += 1;
        }
    }
}

void gameclass(int* strength, int* stamina, int* mana, Inventory* inventory, Item* item, int* HP_player) //функция выбора "класса"
{
    int class;
    do {
        printf("Choose your class:\n 1. Swordsman: higher strenth, wooden sword\n 2. Archer: higher stamina, wooden bow\n 3. Wizard: higher mana, wooden trident\n Your choice: ");
        scanf_s("%d", &class);
        system("cls");
        switch (class)
        {
        case 1: //stamina
            *strength += 4;
            inventory->weapon = item[0];
            printf("%s", "Your choice Swordsman, +2 to the strenth\n");
            break;

        case 2: // intell
            *stamina += 4;
            inventory->weapon = item[3];
            printf("%s", "Your choice Archer, +2 to the stamina\n");
            break;
        case 3: //strenght
            *mana += 4;
            inventory->weapon = item[6];
            printf("%s", "Your choice Wizard, +2 to the mana\n");
            break;
        default:
            printf("%s", "Try again(1-3)\n");
            break;
        }
    } while (class < 1 || class > 3);
    //statscheck(*strength, *stamina, *mana, *HP_player, *lvl);
}
void stats(int* strength, int* stamina, int* mana) //функция добавления очков
{
    printf("%s\n", "You have 10 points for your stats");
    while (1) {
        int pointsSTA;
        int pointsSTR;
        int pointsINT;
        printf("Input points for strength: ");
        scanf_s("%d", &pointsSTR);
        *strength += pointsSTR;
        printf("Input points for stamina: ");
        scanf_s("%d", &pointsSTA);
        *stamina += pointsSTA;
        printf("Input points for mana: ");
        scanf_s("%d", &pointsINT);
        *mana += pointsINT;

        if ((pointsSTA + pointsSTR + pointsINT) == 10) {
            system("cls");
            break;
        }
        else {
            *strength -= pointsSTR;
            *stamina -= pointsSTA;
            *mana -= pointsINT;
            printf("%s", "Your summary points: ");
            printf("%d\n", (pointsSTA + pointsSTR + pointsINT));
            printf("Summary points must be 10. Please, input again.\n");
        }
    }
}
void statslvlup(int* strength, int* stamina, int* mana, int* HP_player) //функция добавления очков
{
    HP_player += 5;
    printf("%s\n", "You have 3 points for your stats");
    while (1) {
        int pointsSTA;
        int pointsSTR;
        int pointsINT;
        printf("Input points for strength: ");
        scanf_s("%d", &pointsSTR);
        *strength += pointsSTR;
        printf("Input points for stamina: ");
        scanf_s("%d", &pointsSTA);
        *stamina += pointsSTA;
        printf("Input points for intelligence: ");
        scanf_s("%d", &pointsINT);
        *mana += pointsINT;

        if (pointsSTA + pointsSTR + pointsINT == 3) {
            break;
        }
        else {
            *strength -= pointsSTR;
            *stamina -= pointsSTA;
            *mana -= pointsINT;
            printf("%s", "Your summary points: ");
            printf("%d\n", (pointsSTA + pointsSTR + pointsINT));
            printf("Summary points must be 3. Please, input again.\n");
        }
    }
}
void statscheck(int* strength, int* stamina, int* mana, int* HP_player, int* lvl, int* xp) //функция проверки своих очков навыков
{
    printf("%s", "Now you have this stats: \n");
    printf("Level: %d\n", lvl);
    printf("Xp: %d\n", xp);
    printf("Healts: %d\n", HP_player);
    printf("Stamina: %d\n", stamina);
    printf("Strenght: %d\n", strength);
    printf("Mana: %d\n", mana);
}
void invcheak(Inventory* inventory, int* emeralds)
{
    printf("Inventory: \n");
    printf("Weapon: %s | Damage: %d\n", inventory->weapon.name, inventory->weapon.value);
    printf("Armor: %s | Defence: %d\n", inventory->armor.name, inventory->armor.value);
    printf("Healt Potion(s) value: %d\n", inventory->healpotion.value);
    printf("Damage Potion(s) value: %d\n", inventory->damagepotion.value);
    printf("Emeralds: %d\n", emeralds);
}
void shop(Inventory* inventory, int* emeralds, Item* item)
{
    printf("%s", "Welcome in shop!\n");
    printf("You have %d emeralds, but can buy only 1 item!\n", *emeralds);
    printf("1. Healt Potion 5 emeralds\n");
    printf("2. Damage Potion 5 emeralds\n");
    printf("3. Stamina Potion 5 emeralds\n");
    printf("4. Wooden armor 10 emeralds\n");
    printf("5. Iron Armor 20 emeralds\n");
    printf("6. Diamond Armor 50 emeralds\n");
    printf("7. Iron Sword 20 emeralds\n");
    printf("8. Diamond Sword 50 emeralds\n");
    printf("9. Iron Bow 20 emeralds\n");
    printf("10. Diamond Bow 50 emeralds\n");
    printf("11. Iron Trident 20 emeralds\n");
    printf("12. Diamond Trident 50 emeralds\n");
    printf("13. Skip shop\n");
    int buyitem;
    do {
        printf("Input:");
        scanf_s("%d", &buyitem);
        system("cls");
        switch (buyitem)
        {
        case 1:
            if (*emeralds >= 5)
            {
                *emeralds -= 5;
                inventory->healpotion.value += 1;
                printf("You bought the Health Potion! Good luck!\n");
            }
            else
            {
                printf("You dont have emeralds, poshel von!\n");
            }
            break;
        case 2:
            if (*emeralds >= 5)
            {
                *emeralds -= 5;
                inventory->damagepotion.value += 1;
                printf("You bought the Damage Potion! Good luck!\n");
            }
            else
            {
                printf("You dont have emeralds, poshel von!\n");
            }
            break;
        case 3:
            if (*emeralds >= 5)
            {
                *emeralds -= 5;
                inventory->staminapotion.value += 1;
                printf("You bought the Stamina Potion! Good luck!\n");
            }
            else
            {
                printf("You dont have emeralds, poshel von!\n");
            }
            break;
        case 4:
            if (*emeralds >= 10)
            {
                *emeralds -= 10;
                inventory->armor = item[9];
                printf("You bought the Wooden Armor! Good luck!\n");
            }
            else
            {
                printf("You dont have emeralds, poshel von!\n");
            }
            break;
        case 5:
            if (*emeralds >= 20)
            {
                *emeralds -= 20;
                inventory->armor = item[10];
                printf("You bought the Iron Armor! Good luck!\n");
            }
            else
            {
                printf("You dont have emeralds, poshel von!\n");
            }
            break;
        case 6:
            if (*emeralds >= 50)
            {
                *emeralds -= 50;
                inventory->armor = item[11];
                printf("You bought the Diamond Armor! Good luck!\n");
            }
            else
            {
                printf("You dont have emeralds, poshel von!\n");
            }
            break;
        case 7:
            if (*emeralds >= 20)
            {
                *emeralds -= 20;
                inventory->weapon = item[1];
                printf("You bought the Iron Sword! Good luck!\n");
            }
            else
            {
                printf("You dont have emeralds, poshel von!\n");
            }
            break;
        case 8:
            if (*emeralds >= 50)
            {
                *emeralds -= 50;
                inventory->weapon = item[2];
                printf("You bought the Diamond Sword! Good luck!\n");
            }
            else
            {
                printf("You dont have emeralds, poshel von!\n");
            }
            break;
        case 9:
            if (*emeralds >= 20)
            {
                *emeralds -= 20;
                inventory->weapon = item[4];
                printf("You bought the Iron Bow! Good luck!\n");
            }
            else
            {
                printf("You dont have emeralds, poshel von!\n");
            }
            break;
        case 10:
            if (*emeralds >= 50)
            {
                *emeralds -= 50;
                inventory->weapon = item[5];
                printf("You bought the Diamond Bow! Good luck!\n");
            }
            else
            {
                printf("You dont have emeralds, poshel von!\n");
            }
            break;
        case 11:
            if (*emeralds >= 20)
            {
                *emeralds -= 20;
                inventory->weapon = item[7];
                printf("You bought the Iron Trident! Good luck!\n");
            }
            else
            {
                printf("You dont have emeralds, poshel von!\n");
            }
            break;
        case 12:
            if (*emeralds >= 50)
            {
                *emeralds -= 50;
                inventory->weapon = item[8];
                printf("You bought the Diamond Trident! Good luck!\n");
            }
            else
            {
                printf("You dont have emeralds, poshel von!\n");
            }
            break;
        case 13:
            break;
        default:
            printf("%s", "Try again(1-12)\n");
            break;
        }
    } while (buyitem < 1 || buyitem > 13);
}
void battle(Inventory* inventory, Item* item, Monsters* mob, int* HP_player, int* emeralds, int* stamina, int* lvl, int* xp, int* strenght, int* mana, FinalScore* score)
{
    srand(time(NULL));
    int HPbattle = *HP_player + inventory->armor.value;
    printf("HP player: %d \n", HPbattle, inventory->armor.value);
    int mobid;
    if (*lvl >= 0 && *lvl < 3)
    {
        mobid = rand() % 3;
    }
    else if (*lvl > 3 && *lvl < 7)
    {
        mobid = 3 + rand() % 3;
    }
    else if (*lvl > 7 && *lvl < 10)
    {
        mobid = 6 + rand() % 3;
    }
    else
    {
        mobid = 9;
    }
    Monsters* agrmob = (mob);
    int mobhp = (agrmob + mobid)->hpmon;
    int mobstamina = (agrmob + mobid)->staminamob;
    int stamin = *stamina;
    int damagepl = inventory->weapon.value + (*strenght / 3); //player's damage
    int staminus = 3;
    printf("Battle begin! Your enemie %s: Hp: %d\n", (agrmob + mobid)->name, (agrmob + mobid)->hpmon);
    printf(" 1.Attack(-3 stamina)\n 2.Use Health Potion\n 3.Use Damage Potion\n 4.Use Stamina Potion\n 5.Skip/End battle\n");
    int flag = 1;
    while (flag)
    {
        int choice;
        if (mobid < 9)
        {
            if (mobhp > 0 && HPbattle > 0)
            {
                int mobdamage = rand() % 100;
                printf("Input: ");
                scanf_s("%d", &choice);
                switch (choice)
                {
                case 1:
                {
                    if (mobhp > 0 && (stamin - staminus) > 0)
                    {
                        mobhp -= damagepl;
                        printf("Mob %s got hit! Your damage: %d, Mob Hp: %d\n", (agrmob + mobid)->name, damagepl, mobhp);
                        stamin -= staminus;
                        printf("You have %d stamina\n", stamin);
                        if (mobdamage > 0 && mobdamage < 21) //chance miss
                        {
                            printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                        }
                        else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                        {
                            HPbattle -= (agrmob + mobid)->damage - 3;
                            mobstamina -= 4;
                            printf("Critical hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        else //chance default damage
                        {
                            HPbattle -= (agrmob + mobid)->damage;
                            mobstamina -= 2;
                            printf("Hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                case 2:
                {
                    if (inventory->healpotion.value > 0)
                    {

                        if (HPbattle != HP_player)
                        {
                            HPbattle += 10;
                            inventory->healpotion.value -= 1;
                            printf("Healt Potion was drinked, now your HP: %d\n", HPbattle);
                            if (mobdamage > 0 && mobdamage < 21) //chance miss
                            {
                                printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                            }
                            else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                            {
                                HPbattle -= (agrmob + mobid)->damage + 3;
                                mobstamina -= 4;
                                printf("Critical hit from %s\n", (agrmob + mobid)->name);
                                printf("Your HP: %d\n", HPbattle);
                            }
                            else //chance default damage
                            {
                                HPbattle -= (agrmob + mobid)->damage;
                                mobstamina -= 2;
                                printf("Hit from %s\n", (agrmob + mobid)->name);
                                printf("Your HP: %d\n", HPbattle);
                            }
                            continue;

                        }
                        else
                        {
                            printf("HP if full!\n");
                            if (mobdamage > 0 && mobdamage < 21) //chance miss
                            {
                                printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                            }
                            else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                            {
                                HPbattle -= (agrmob + mobid)->damage + 3;
                                mobstamina -= 4;
                                printf("Critical hit from %s\n", (agrmob + mobid)->name);
                                printf("Your HP: %d\n", HPbattle);
                            }
                            else //chance default damage
                            {
                                HPbattle -= (agrmob + mobid)->damage;
                                mobstamina -= 2;
                                printf("Hit from %s\n", (agrmob + mobid)->name);
                                printf("Your HP: %d\n", HPbattle);
                            }
                            continue;
                        }

                    }
                    else
                    {
                        printf("You dont have Healt Potion!\n");
                        if (mobdamage > 0 && mobdamage < 21) //chance miss
                        {
                            printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                        }
                        else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                        {
                            HPbattle -= (agrmob + mobid)->damage + 3;
                            mobstamina -= 4;
                            printf("Critical hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        else //chance default damage
                        {
                            HPbattle -= (agrmob + mobid)->damage;
                            mobstamina -= 2;
                            printf("Hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        continue;
                    }
                }
                case 3:
                {
                    if (inventory->damagepotion.value > 0)
                    {
                        damagepl += 7;
                        inventory->damagepotion.value -= 1;
                        printf("Damage Potion was drinked, now your damage: %d\n", damagepl);
                        if (mobdamage > 0 && mobdamage < 21) //chance miss
                        {
                            printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                        }
                        else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                        {
                            HPbattle -= (agrmob + mobid)->damage + 3;
                            mobstamina -= 4;
                            printf("Critical hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        else //chance default damage
                        {
                            HPbattle -= (agrmob + mobid)->damage;
                            mobstamina -= 2;
                            printf("Hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        continue;
                    }
                    else
                    {
                        printf("You dont have Damage potion!\n");
                        if (mobdamage > 0 && mobdamage < 21) //chance miss
                        {
                            printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                        }
                        else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                        {
                            HPbattle -= (agrmob + mobid)->damage + 3;
                            mobstamina -= 4;
                            printf("Critical hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        else //chance default damage
                        {
                            HPbattle -= (agrmob + mobid)->damage;
                            mobstamina -= 2;
                            printf("Hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        continue;
                    }
                }
                case 4:
                {
                    if (inventory->staminapotion.value > 0)
                    {
                        stamin += 7;
                        inventory->staminapotion.value -= 1;
                        printf("Stamina Potion was drinked, now your stamina: %d\n", stamin);
                        if (mobdamage > 0 && mobdamage < 21) //chance miss
                        {
                            printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                        }
                        else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                        {
                            HPbattle -= (agrmob + mobid)->damage + 3;
                            mobstamina -= 4;
                            printf("Critical hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        else //chance default damage
                        {
                            HPbattle -= (agrmob + mobid)->damage;
                            mobstamina -= 2;
                            printf("Hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        continue;
                    }
                    else
                    {
                        printf("You dont have Stamina Potion!\n");
                        if (mobdamage > 0 && mobdamage < 21) //chance miss
                        {
                            printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                        }
                        else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                        {
                            HPbattle -= (agrmob + mobid)->damage + 3;
                            mobstamina -= 4;
                            printf("Critical hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        else //chance default damage
                        {
                            HPbattle -= (agrmob + mobid)->damage;
                            mobstamina -= 2;
                            printf("Hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        continue;
                    }
                }
                case 5:
                {

                    printf("You skip battle, pussy!\n");
                    break;
                }
                default:
                    printf("Choice 1-5!");
                }
            }
            else if (mobhp > 0 && HPbattle <= 0)
            {
                printf("||||||DEFEAT||||||\nYou kill %d mobs\nOpen %d cheats\nMove on %d steps\nEarn %d emeralds", score->killmob, score->cheast, score->steps, score->allcash);
                break;
            }
            else
            {
                printf("%s is dead, you got %d emeralds and %d exp!\n", (agrmob + mobid)->name, (agrmob + mobid)->emer, (agrmob + mobid)->xp);
                *emeralds += (agrmob + mobid)->emer;
                *xp += (agrmob + mobid)->xp;
                score->killmob += 1;
                score->allcash += (agrmob + mobid)->emer;
                flag = 0;
                printf("Battle End!\n");
                break;
            }
        }
        else
        {
            if (mobhp > 0 && HPbattle > 0)
            {
                int mobdamage = rand() % 100;
                printf("Input: ");
                scanf_s("%d", &choice);
                switch (choice)
                {
                case 1:
                {
                    if (mobhp > 0 && (stamin - staminus) > 0)
                    {
                        mobhp -= damagepl;
                        printf("Mob %s got hit! Your damage: %d, Mob Hp: %d\n", (agrmob + mobid)->name, damagepl, mobhp);
                        stamin -= staminus;
                        printf("You have %d stamina\n", stamin);
                        if (mobdamage > 0 && mobdamage < 21) //chance miss
                        {
                            printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                        }
                        else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                        {
                            HPbattle -= (agrmob + mobid)->damage - 3;
                            mobstamina -= 4;
                            printf("Critical hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        else //chance default damage
                        {
                            HPbattle -= (agrmob + mobid)->damage;
                            mobstamina -= 2;
                            printf("Hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                case 2:
                {
                    if (inventory->healpotion.value > 0)
                    {

                        if (HPbattle != HP_player)
                        {
                            HPbattle += 10;
                            inventory->healpotion.value -= 1;
                            printf("Healt Potion was drinked, now your HP: %d\n", HPbattle);
                            if (mobdamage > 0 && mobdamage < 21) //chance miss
                            {
                                printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                            }
                            else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                            {
                                HPbattle -= (agrmob + mobid)->damage + 3;
                                mobstamina -= 4;
                                printf("Critical hit from %s\n", (agrmob + mobid)->name);
                                printf("Your HP: %d\n", HPbattle);
                            }
                            else //chance default damage
                            {
                                HPbattle -= (agrmob + mobid)->damage;
                                mobstamina -= 2;
                                printf("Hit from %s\n", (agrmob + mobid)->name);
                                printf("Your HP: %d\n", HPbattle);
                            }
                            continue;

                        }
                        else
                        {
                            printf("HP if full!\n");
                            if (mobdamage > 0 && mobdamage < 21) //chance miss
                            {
                                printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                            }
                            else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                            {
                                HPbattle -= (agrmob + mobid)->damage + 3;
                                mobstamina -= 4;
                                printf("Critical hit from %s\n", (agrmob + mobid)->name);
                                printf("Your HP: %d\n", HPbattle);
                            }
                            else //chance default damage
                            {
                                HPbattle -= (agrmob + mobid)->damage;
                                mobstamina -= 2;
                                printf("Hit from %s\n", (agrmob + mobid)->name);
                                printf("Your HP: %d\n", HPbattle);
                            }
                            continue;
                        }

                    }
                    else
                    {
                        printf("You dont have Healt Potion!\n");
                        if (mobdamage > 0 && mobdamage < 21) //chance miss
                        {
                            printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                        }
                        else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                        {
                            HPbattle -= (agrmob + mobid)->damage + 3;
                            mobstamina -= 4;
                            printf("Critical hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        else //chance default damage
                        {
                            HPbattle -= (agrmob + mobid)->damage;
                            mobstamina -= 2;
                            printf("Hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        continue;
                    }
                }
                case 3:
                {
                    if (inventory->damagepotion.value > 0)
                    {
                        damagepl += 7;
                        inventory->damagepotion.value -= 1;
                        printf("Damage Potion was drinked, now your damage: %d\n", damagepl);
                        if (mobdamage > 0 && mobdamage < 21) //chance miss
                        {
                            printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                        }
                        else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                        {
                            HPbattle -= (agrmob + mobid)->damage + 3;
                            mobstamina -= 4;
                            printf("Critical hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        else //chance default damage
                        {
                            HPbattle -= (agrmob + mobid)->damage;
                            mobstamina -= 2;
                            printf("Hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        continue;
                    }
                    else
                    {
                        printf("You dont have Damage potion!\n");
                        if (mobdamage > 0 && mobdamage < 21) //chance miss
                        {
                            printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                        }
                        else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                        {
                            HPbattle -= (agrmob + mobid)->damage + 3;
                            mobstamina -= 4;
                            printf("Critical hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        else //chance default damage
                        {
                            HPbattle -= (agrmob + mobid)->damage;
                            mobstamina -= 2;
                            printf("Hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        continue;
                    }
                }
                case 4:
                {
                    if (inventory->staminapotion.value > 0)
                    {
                        stamin += 7;
                        inventory->staminapotion.value -= 1;
                        printf("Stamina Potion was drinked, now your stamina: %d\n", stamin);
                        if (mobdamage > 0 && mobdamage < 21) //chance miss
                        {
                            printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                        }
                        else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                        {
                            HPbattle -= (agrmob + mobid)->damage + 3;
                            mobstamina -= 4;
                            printf("Critical hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        else //chance default damage
                        {
                            HPbattle -= (agrmob + mobid)->damage;
                            mobstamina -= 2;
                            printf("Hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        continue;
                    }
                    else
                    {
                        printf("You dont have Stamina Potion!\n");
                        if (mobdamage > 0 && mobdamage < 21) //chance miss
                        {
                            printf("%s is miss, you so lucky!\n", (agrmob + mobid)->name);
                        }
                        else if (mobdamage > 20 && mobdamage < 41) //chance critical hit
                        {
                            HPbattle -= (agrmob + mobid)->damage + 3;
                            mobstamina -= 4;
                            printf("Critical hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        else //chance default damage
                        {
                            HPbattle -= (agrmob + mobid)->damage;
                            mobstamina -= 2;
                            printf("Hit from %s\n", (agrmob + mobid)->name);
                            printf("Your HP: %d\n", HPbattle);
                        }
                        continue;
                    }
                }
                case 5:
                {

                    printf("Good choice! Ender Dragon kill the World!\n");
                    printf("||||||DEFEAT||||||\nYou kill %d mobs\nOpen %d cheats\nMove on %d steps\nEarn %d emeralds", score->killmob, score->cheast, score->steps, score->allcash);
                    break;

                }
                default:
                    printf("Choice 1-5!");
                }
            }
            else if (mobhp > 0 && HPbattle <= 0)
            {
                printf("||||||DEFEAT||||||\nYou kill %d mobs\nOpen %d cheats\nMove on %d steps\nEarn %d emeralds", score->killmob, score->cheast, score->steps, score->allcash);
                break;
            }
            else
            {
                printf("%s is dead, you got %d emeralds and %d exp!\n", (agrmob + mobid)->name, (agrmob + mobid)->emer, (agrmob + mobid)->xp);
                *emeralds += (agrmob + mobid)->emer;
                *xp += (agrmob + mobid)->xp;
                flag = 0;
                printf("Battle End!\n");
                printf("||||||VICTORY||||||\nYou kill %d mobs\nOpen %d cheats\nMove on %d steps\nEarn %d emeralds", score->killmob, score->cheast, score->steps, score->allcash);
                break;
            }
        }

    }
}
void lvlup(int* lvl, int* xp, int* strength, int* stamina, int* mana, int* HP_player)
{
    if (*xp > 50)
    {
        *lvl += 1;
        *xp -= 50;
        *HP_player += 5;
        statslvlup(&strength, &stamina, &mana, &HP_player);
    }
    else
    {
        printf("You dont have xp to level up :(\n");
    }
}
void chest(Inventory* inventory, Item* item, FinalScore* score)
{
    srand(time(NULL));
    int randitem = rand() % 100;
    if (randitem > 0 && randitem < 34) // Health
    {
        printf("You find Health Potion!\n");
        inventory->healpotion.value += 1;
    }
    else if (randitem > 33 && randitem < 67) // Damage
    {
        printf("You find Damage Potion!\n");
        inventory->damagepotion.value += 1;
    }
    else // Stamina
    {
        printf("You find Stamina Potion!\n");
        inventory->staminapotion.value += 1;
    }
    score->allcash += 1;
}
