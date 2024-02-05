#include <iostream>
#include <ctime>

void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char computer);
void smartComputerMove(char *spaces, char computer, char round);
bool checkWinner(char *spaces, char player, char computer);
bool checkTie(char *spaces);

int main()
{
    char spaces[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char player = 'X';
    char computer = 'O';
    bool running = true;

    drawBoard(spaces);

    while (running)
    {
        playerMove(spaces, player);
        drawBoard(spaces);
        if (checkWinner(spaces, player, computer))
        {
            running = false;
            break;
        }
        else if (checkTie(spaces))
        {
            running = false;
            break;
        }
        smartComputerMove(spaces, computer, player);
        drawBoard(spaces);
        if (checkWinner(spaces, player, computer))
        {
            running = false;
            break;
        }
        else if (checkTie(spaces))
        {
            running = false;
            break;
        }
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}

void drawBoard(char *spaces)
{
    std::cout << "\n";
    std::cout << "     |     |     "
              << "\n";
    std::cout << "  " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << "  "
              << "\n";
    std::cout << "_____|_____|_____"
              << "\n";
    std::cout << "     |     |     "
              << "\n";
    std::cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << "  "
              << "\n";
    std::cout << "_____|_____|_____"
              << "\n";
    std::cout << "     |     |     "
              << "\n";
    std::cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << "  "
              << "\n";
    std::cout << "     |     |     "
              << "\n";
    std::cout << "\n";
}
void playerMove(char *spaces, char player)
{
    int number;
    do
    {
        std::cout << "Enter a spot to place a marker (1-9): ";
        std::cin >> number;
        number--;
        if (spaces[number] == ' ')
        {

            spaces[number] = player;
            break;
        }

    } while (!number > 0 || !number < 8);
}
/*void computerMove(char *spaces, char computer)
{
    int number;
    srand(time(0));

    while (true)
    {
        number = rand() % 9;
        if (spaces[number] == ' ')
        {
            spaces[number] = computer;
            break;
        }
    }
}*/
/*bool smartCheckWin(char *spaces)
{
    unsigned wins[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    int i;
    for (i = 0; i < 8; ++i)
    {
        if (spaces[wins[i][0]] != 0 &&
            spaces[wins[i][0]] == spaces[wins[i][1]] && spaces[wins[i][1]] == spaces[wins[i][2]])
            return spaces[wins[i][2]];
    }
    return 0;
}*/
int smartCheckWin(char *spaces, char player)
{

    int victory = 0;
    bool filled = false;
    if (spaces[0] != ' ' && spaces[1] != ' ' && spaces[2] != ' ' && spaces[3] != ' ' && spaces[4] != ' ' && spaces[5] != ' ' && spaces[6] != ' ' && spaces[7] != ' ' && spaces[8] != ' ')
    {
        filled = true;
    }
    // CHECK ROWS:
    if ((spaces[0] != ' ') && (spaces[0] == spaces[1] and spaces[1] == spaces[2]))
    {
        spaces[0] == player ? victory = -1 : victory = 1;
    }
    else if ((spaces[3] != ' ') && (spaces[3] == spaces[4] and spaces[4] == spaces[5]))
    {
        spaces[3] == player ? victory = -1 : victory = 1;
    }
    else if ((spaces[6] != ' ') && (spaces[6] == spaces[7] and spaces[7] == spaces[8]))
    {
        spaces[6] == player ? victory = -1 : victory = 1;
    }

    // CHECK COLUMNS:
    else if ((spaces[0] != ' ') && (spaces[0] == spaces[3] and spaces[3] == spaces[6]))
    {
        spaces[0] == player ? victory = -1 : victory = 1;
    }
    else if ((spaces[1] != ' ') && (spaces[1] == spaces[4] and spaces[4] == spaces[7]))
    {
        spaces[1] == player ? victory = -1 : victory = 1;
    }
    else if ((spaces[2] != ' ') && (spaces[2] == spaces[5] and spaces[5] == spaces[8]))
    {
        spaces[2] == player ? victory = -1 : victory = 1;
    }

    // CHECK DIAGONALS:
    else if ((spaces[0] != ' ') && (spaces[0] == spaces[4] and spaces[4] == spaces[8]))
    {
        spaces[0] == player ? victory = -1 : victory = 1;
    }
    else if ((spaces[2] != ' ') && (spaces[2] == spaces[4] and spaces[4] == spaces[6]))
    {
        spaces[2] == player ? victory = -1 : victory = 1;
    }

    if (filled == true)
    {
        return -1;
    }
    // Tie
    else
    {
        return 0;
    }

    return victory;
}
int minimax(char *spaces, char player, char computer, char round)
{
    int winner = smartCheckWin(spaces, player);
    if (winner != 0)
    {
        return 1;
    }
    int pos = -1;
    int score = -10;
    int test = 0;
    int rvalue = 0;

    for (int i = 0; i < 9; i++)
    {
        if (spaces[i] == ' ')
        {
            int thisScore;
            if (round == -1)
            {
                spaces[i] = player;
                int thisScore = minimax(spaces, player, computer, 1);
            }
            else
            {
                spaces[i] = computer;
                int thisScore = minimax(spaces, player, computer, -1);
            }
            if (thisScore > score)
            {
                score = thisScore;
                rvalue = score;
                pos = i;
            }
            test = i;
        }
    }
    spaces[test] = ' ';
    if (pos == -1)
        return 0;

    return rvalue;
}

void smartComputerMove(char *spaces, char computer, char player)
{
    int number;
    srand(time(0));
    int score = -10;
    bool stop = true;

    while (stop)
    {
        for (int i = 0; i < 9; i++)
        {
            if (spaces[i] == ' ')
            {
                spaces[i] = computer;
                int temp_score = minimax(spaces, player, computer, -1);
                spaces[i] = ' ';
                if (temp_score > score)
                {
                    score = temp_score;
                    spaces[i] = computer;
                    stop = false;
                    break;
                }
            }
        }
    }
}
bool checkWinner(char *spaces, char player, char computer)
{

    // CHECK ROWS:
    if ((spaces[0] != ' ') && (spaces[0] == spaces[1] and spaces[1] == spaces[2]))
    {
        spaces[0] == player ? std::cout << "You win!\n" : std::cout << "You lose\n";
    }
    else if ((spaces[3] != ' ') && (spaces[3] == spaces[4] and spaces[4] == spaces[5]))
    {
        spaces[3] == player ? std::cout << "You win!\n" : std::cout << "You lose\n";
    }
    else if ((spaces[6] != ' ') && (spaces[6] == spaces[7] and spaces[7] == spaces[8]))
    {
        spaces[6] == player ? std::cout << "You win!\n" : std::cout << "You lose\n";
    }

    // CHECK COLUMNS:
    else if ((spaces[0] != ' ') && (spaces[0] == spaces[3] and spaces[3] == spaces[6]))
    {
        spaces[0] == player ? std::cout << "You win!\n" : std::cout << "You lose\n";
    }
    else if ((spaces[1] != ' ') && (spaces[1] == spaces[4] and spaces[4] == spaces[7]))
    {
        spaces[1] == player ? std::cout << "You win!\n" : std::cout << "You lose\n";
    }
    else if ((spaces[2] != ' ') && (spaces[2] == spaces[5] and spaces[5] == spaces[8]))
    {
        spaces[2] == player ? std::cout << "You win!\n" : std::cout << "You lose\n";
    }

    // CHECK DIAGONALS:
    else if ((spaces[0] != ' ') && (spaces[0] == spaces[4] and spaces[4] == spaces[8]))
    {
        spaces[0] == player ? std::cout << "You win!\n" : std::cout << "You lose\n";
    }
    else if ((spaces[2] != ' ') && (spaces[2] == spaces[4] and spaces[4] == spaces[6]))
    {
        spaces[2] == player ? std::cout << "You win!\n" : std::cout << "You lose\n";
    }

    // Tie
    else
    {
        return false;
    }

    return true;
}
bool checkTie(char *spaces)
{

    for (int i = 0; i < 9; i++)
    {
        if (spaces[i] == ' ')
        {
            return false;
        }
    }
    std::cout << "Its a tie!\n";
    return true;
}
