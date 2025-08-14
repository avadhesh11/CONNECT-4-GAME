#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
    #define clr "cls" 
#else
    #define clr "clear" 
#endif

void history()
{
  FILE *file = fopen("results.txt", "r");
  if (file == NULL)
  {
    printf("No game history found.\n");
    return;
  }
  char line[256];
  printf("Game History:\n");
  while (fgets(line, sizeof(line), file))
  {
    printf("%s", line);
  }
  fclose(file);
}

void saveresult(char *player1, char *player2, char *result)
{
  FILE *file = fopen("results.txt", "a");
  if (file == NULL)
  {
    printf("Error! Unable to open file for saving results.\n");
    return;
  }
  time_t now = time(NULL);
  struct tm *local = localtime(&now);
  fprintf(file, "Date: %02d-%02d-%04d Time: %02d:%02d:%02d\n",
          local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
          local->tm_hour, local->tm_min, local->tm_sec);
  fprintf(file, "Player 1: %s, Player 2: %s, Result: %s \n", player1, player2, result);
  fclose(file);
  printf("Game result saved successfully!\n");
  return;
}

void iboard(char a[7][7])
{
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      a[i][j] = '.';
    }
  }
}
void pboard(char a[7][7])
{
  printf("\n1    2    3    4    5    6    7\n");
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {

      printf("%c    ", a[i][j]);
    }
    printf("    ");
    printf("\n");
  }
  printf("\n");
}
void gboard(char a[7][7], int *m, int n, char b)
{
  printf("\n1    2    3    4    5    6    7\n");
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      if (i == *m && j == n)
      {
        a[i][j] = b;
      }

      printf("%c    ", a[i][j]);
    }
    printf("    ");
    printf("\n");
  }
  printf("\n");
}

bool win1(char a[7][7], int x, int y, char s)
{
  if (y + 3 < 7 && a[x][y] == s && a[x][y + 1] == s && a[x][y + 2] == s && a[x][y + 3] == s)
  {
    return true;
  }
  if (y - 3 >= 0 && a[x][y] == s && a[x][y - 1] == s && a[x][y - 2] == s && a[x][y - 3] == s)
  {
    return true;
  }
  if (x + 3 < 7 && a[x][y] == s && a[x + 1][y] == s && a[x + 2][y] == s && a[x + 3][y] == s)
  {
    return true;
  }
  if (x - 3 > 0 && a[x][y] == s && a[x - 1][y] == s && a[x - 2][y] == s && a[x - 3][y] == s)
  {
    return true;
  }
  if (x + 3 < 7 && y + 3 < 7 && a[x][y] == s && a[x + 1][y + 1] == s && a[x + 2][y + 2] == s && a[x + 3][y + 3] == s)
  {
    return true;
  }
  if (x - 3 >= 0 && y - 3 >= 0 && a[x][y] == s && a[x - 1][y - 1] == s && a[x - 2][y - 2] == s && a[x - 3][y - 3] == s)
  {
    return true;
  }
  if (x - 3 >= 0 && y + 3 < 7 && a[x][y] == s && a[x - 1][y + 1] == s && a[x - 2][y + 2] == s && a[x - 3][y + 3] == s)
  {
    return true;
  }
  if (x + 3 < 7 && y - 3 >= 0 && a[x][y] == s && a[x + 1][y - 1] == s && a[x + 2][y - 2] == s && a[x + 3][y - 3] == s)
  {
    return true;
  }
  return false;
}

typedef struct playrinfo
{
  char name[50];
  char symbol;
} p;

int main()
{
  char board[7][7];
  printf("\n");
  printf("       \033[90mWELCOME TO CONNECT 4!           \n");
  printf("\n");
  printf("*           RULES AND GUIDE       *\n");
  printf("FIRST ENTER H IF YOU WANT TO SEE HISTORY OR ELSE ANY CHARACTER TO PLAY THE GAME \n");

  printf("HOW TO PLAY:\n");
  printf("1. ENTER ANY NUMBER BETWEEN 1 TO 7, AND THE SELECTED SYMBOL( EXCEPT '.' AND SYMBOL'S CAN'T BE SAME) BY THAT PARTICULAR PLAYER WILL BE MARKED AT THAT POSITION.\n");
  printf("2. THE PROCESS GOES SAME FOR PLAYER 2 AND CONTINUES UNTIL ONE PLAYER GETS DECLARED AS A WINNER!\n");
  printf("WHILE ENTERING NUMBERS PLAYERS CAN TYPE 0 FOR NEW GAME AND 10 TO EXIT AND 11TO START FROM PLAYER'S NAME i.e. FROM VER BEGINNING\n\n");
  printf("* HOW TO WIN? *\n");
  printf("IF THERE IS A CONTINUOUS PATTERN OF FOUR SYMBOLS IN A ROW OF ANY PLAYER:\n");
  printf(" - HORIZONTALLY,\n");
  printf(" - VERTICALLY, OR\n");
  printf(" - DIAGONALLY,\n");
  printf("HE/SHE WILL BE DECLARED AS A WINNER AND THE GAME ENDS!\n\n");
  printf("\n");
  printf("*      ENJOY THE GAME AND WIN!    *\033[0m \n");
  printf("\n");

  printf("->ENTER H TO SHOW HISTORY OR ELSE ENTER ANY CHARACTER TO START A NEW GAME: ");

  char s;
  scanf("%c", &s);
  getchar();
  if (s != 'H')
  {
    p p1;
    p p2;
  restart:
    fflush(stdin);
    printf("Please enter name of player 1: ");
    fgets(p1.name, 50, stdin);
    p1.name[strcspn(p1.name, "\n")] = '\0';
    printf("Please enter symbol for player 1(single character only) - %s: ", p1.name);

    scanf("%c", &p1.symbol);
    getchar();
    while (p1.symbol == '.')
    {
      printf("INVALID INPUT KINDLY REFER TO RULES(OF HOW TO PLAY POINT 1) AND THEN TRY AGAIN!\n");
      printf("Please enter symbol for player 1(single character only) - %s: ", p1.name);
      scanf("%c", &p1.symbol);
      getchar();
    }
    printf("Please enter name of player 2: ");
    fgets(p2.name, 50, stdin);
    p2.name[strcspn(p2.name, "\n")] = '\0';
    while (strcmp(p2.name, p1.name) == 0)
    {
      printf("Both players name can't be same, TRY AGAIN!\n");
      printf("Please enter name of player 2:");
      fgets(p2.name, 50, stdin);
      p2.name[strcspn(p2.name, "\n")] = '\0';
    }
    printf("Please enter symbol for player 2(single character only) - %s: ", p2.name);
    scanf("%c", &p2.symbol);
    getchar();
    while (p2.symbol == p1.symbol || p2.symbol == '.')
    {
      printf("INVALID INPUT KINDLY REFER TO RULES(OF HOW TO PLAY POINT 1) AND THEN TRY AGAIN!\n");
      printf("Please enter symbol for player 2(single character only) - %s: ", p2.name);
      scanf("%c", &p2.symbol);
      getchar();
    }
    bool win = false;
    int m = 7;

    system(clr);

    new : iboard(board);
    printf("NOTE: TYPE 0 FOR NEW GAME AND 10 TO EXIT AND 11 TO START FROM PLAYER'S NAME i.e. FROM VERY BEGINNING\n");
    pboard(board);

    int w;
    int pre = 0;

    while (!win)
    {

      int a;
      int x = 6;

      if (pre != 0)
      {
        printf("Last move by player 2 was: %d\n", pre);
      }
      printf("PLAYER 1: %s enter any number between 1 to 7:", p1.name);

      if (scanf("%d", &a) != 1)
      {

        printf("Invalid input! Please enter a number between 1 to 7.\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        continue;
      }
      if (a == 10)
      {
        exit(0);
      }
      if (a == 11)
      {
        system(clr);
        printf("RESTARTING THE GAME FROM BEGINNING\n");
        goto restart;
      }
      if (a == 0)
      {
        system(clr);
        printf("NEW GAME STARTS\n");
        iboard(board);
        pre = 0;
        printf("NOTE: TYPE 0 FOR NEW GAME AND 10 TO EXIT AND 11 TO START FROM PLAYER'S NAME i.e. FROM VERY BEGINNING\n");
        pboard(board);
        m = 7;
        continue;
      }

      if (a < 0 || a > 7)
      {
        printf("Invalid input try again\n");
        continue;
      }
      while (board[x][a - 1] != '.')
      {
        x--;
      }
      if (x < 0)
      {
        printf("Invalid input try again\n");
        m--;
        continue;
      }
      if (m == 0)
      {
        printf("GAME DRAW!\n");
        printf("NEW GAME STARTS\n");
        iboard(board);
        pre = 0;
        printf("NOTE: TYPE 0 FOR NEW GAME AND 10 TO EXIT AND 11 TO START FROM PLAYER'S NAME i.e. FROM VERY BEGINNING\n");
        pboard(board);
        m = 7;
        continue;
      }
      gboard(board, &x, a - 1, p1.symbol);

      if (win1(board, x, a - 1, p1.symbol))
      {
        win = true;
        w = 1;
        break;
      }
      system(clr);

      printf("NOTE: TYPE 0 FOR NEW GAME AND 10 TO EXIT AND 11 TO START FROM PLAYER'S NAME i.e. FROM VERY BEGINNING\n");
      pboard(board);
      printf("Last move by player 1 was: %d\n", a);

      int b;
    here:

      printf("PLAYER 2: %s enter any number between 1 to 7:", p2.name);
      if (scanf("%d", &b) != 1)
      {

        printf("Invalid input! Please enter a number between 1 to 7.\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        goto here;
      }
      if (b == 10)
      {
        exit(0);
      }
      if (b == 11)
      {
        system(clr);
        printf("RESTARTING THE GAME FROM BEGINNING\n");
        goto restart;
      }
      if (b <= 0 || b > 7)
      {
        printf("Invalid input try again\n");
        goto here;
      }

      if (b == 0)
      {
        system(clr);
        printf("NEW GAME STARTS\n");
        iboard(board);
        pre = 0;
        printf("NOTE: TYPE 0 FOR NEW GAME AND 10 TO EXIT AND 11 TO START FROM PLAYER'S NAME i.e. FROM VERY BEGINNING\n");
        pboard(board);
        m = 7;
        continue;
      }
      int y = 6;

      while (board[y][b - 1] != '.')
      {
        y--;
      }
      if (y < 0)
      {
        printf("Invalid input try again\n");
        m--;
        goto here;
      }
      gboard(board, &y, b - 1, p2.symbol);
      if (win1(board, y, b - 1, p2.symbol))
      {
        win = true;
        w = 2;
        break;
      }
      if (m == 0)
      {
        printf("GAME DRAW!\n");
        printf("NEW GAME STARTS\n");
        pre = 0;
        iboard(board);
        printf("NOTE: TYPE 0 FOR NEW GAME AND 10 TO EXIT AND 11 TO START FROM PLAYER'S NAME i.e. FROM VERY BEGINNING\n");
        pboard(board);
        m = 7;
        continue;
      }
      pre = b;
      system("clear");
      printf("NOTE: TYPE 0 FOR NEW GAME AND 10 TO EXIT AND 11 TO START FROM PLAYER'S NAME i.e. FROM VERY BEGINNING\n");
      pboard(board);
    }
    char result[60];
    switch (w) {
  case 1:
    snprintf(result, sizeof(result), "%s wins", p1.name);
    printf("\n\033[93m       *****************************************\n");
    printf("      *                                         *\n");
    printf("     *                                            *\n");
    printf("    *                                              *\n");
    printf("                \033[91mPLAYER 1 - %s WINS!\033[93m                  \n", p1.name);
    printf("    *                                              *\n");
    printf("     *                                            *\n");
    printf("      *                                          *\n");
    printf("        *****************************************\033[0m \n");
    break;

  case 2:
    snprintf(result, sizeof(result), "%s wins", p2.name);
    printf("\n\033[93m       *****************************************\n");
    printf("      *                                         *\n");
    printf("     *                                            *\n");
    printf("    *                                              *\n");
    printf("                \033[91mPLAYER 2 - %s WINS!\033[93m                  \n", p2.name);
    printf("    *                                              *\n");
    printf("     *                                            *\n");
    printf("      *                                          *\n");
    printf("        *****************************************\033[0m \n");
    break;

  default:
    printf("Invalid result.\n");
    break;
}

    printf("Do you wish to save the results? Press Y to save results.\n");
    char saveresults;
    while (getchar() != '\n')
      ;
    scanf("%c", &saveresults);
    if (saveresults == 'Y')
    {
      saveresult(p1.name, p2.name, result);
    }
    printf("ENTER 0 TO START A NEW GAME OR ENTER 10 TO EXIT OR ENTER 11 TO RESTART GAME FROM BEGINNING:");
    int k;

    while (scanf("%d", &k) != 1)
    {
      printf("Invalid input! Please enter a valid number (0, 10, or 11): ");
      while (getchar() != '\n')
        ; // Clear the buffer
    }

    while (getchar() != '\n')
      ;
    if (k == 10)
    {
      exit(0);
    }
    if (k == 0)
    {
      system(clr);
      printf("NEW GAME STARTS...\n");
      win = false;
      goto new;
    }
    if (k == 11)
    {
      system(clr);
      printf("RESTARTING THE GAME FROM BEGINNING\n");
      goto restart;
    }
  }
  else
  {
    history();
    printf("NEW GAME STARTS\n");
    goto restart;
  }
  return 0;
}