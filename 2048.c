#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define BACKGROUND 100
#define TEXT 101
#define COLOR_2 102
#define COLOR_4 103
#define COLOR_8 104
#define COLOR_16 105
#define COLOR_32 106
#define COLOR_64 107
#define COLOR_128 108
#define COLOR_256 109
#define COLOR_512 110
#define COLOR_1024 111
#define COLOR_2048 112
#define BACKGROUND 100
#define TEXT 101
#define COLOR_2 102
#define COLOR_4 103
#define COLOR_8 104
#define COLOR_16 105
#define COLOR_32 106
#define COLOR_64 107
#define COLOR_128 108
#define COLOR_256 109
#define COLOR_512 110
#define COLOR_1024 111
#define COLOR_2048 112

int grid[4][4] = {0}, score = 0, grid2[4][4] = {0}, score2 = 0;

// functie pentru initializarea culorilor
void initialize_colors()
{
    init_color(BACKGROUND, 900, 900, 800);
    init_color(TEXT, 300, 150, 50);

    init_pair(1, TEXT, BACKGROUND);

    init_color(COLOR_2, 800, 800, 0);
    init_color(COLOR_4, 800, 680, 0);
    init_color(COLOR_8, 800, 560, 0);
    init_color(COLOR_16, 800, 440, 0);
    init_color(COLOR_32, 800, 320, 0);
    init_color(COLOR_64, 680, 200, 0);
    init_color(COLOR_128, 560, 80, 0);
    init_color(COLOR_256, 440, 0, 0);
    init_color(COLOR_512, 320, 0, 0);
    init_color(COLOR_1024, 200, 0, 0);
    init_color(COLOR_2048, 80, 0, 0);

    init_pair(2, TEXT, COLOR_2);
    init_pair(3, TEXT, COLOR_4);
    init_pair(4, TEXT, COLOR_8);
    init_pair(5, TEXT, COLOR_16);
    init_pair(6, TEXT, COLOR_32);
    init_pair(7, TEXT, COLOR_64);
    init_pair(8, TEXT, COLOR_128);
    init_pair(9, BACKGROUND, COLOR_256);
    init_pair(10, BACKGROUND, COLOR_512);
    init_pair(11, BACKGROUND, COLOR_1024);
    init_pair(12, BACKGROUND, COLOR_2048);
}
// afisarea meniului de joc
void menu(char *menu[], int nr, int aleg)
{

    clear();
    start_color();
    initialize_colors();
    bkgd(COLOR_PAIR(1));
    // calcularea dimensiunilor ecranului
    int lin, col;
    getmaxyx(stdscr, lin, col);

    int starty = (lin - nr) / 2;
    int startx = (col - 20) / 2;
    int i;
    // afisarea optiunilor si evidentierea alegerii curente
    for (i = 0; i < nr; ++i)
    {
        if (aleg == i + 1)
        {
            attron(A_REVERSE);
            mvprintw(starty + i + 1, startx + 2, "[%s]", menu[i]);
            attroff(A_REVERSE);
        }
        else
        {
            mvprintw(starty + i + 1, startx + 2, " %s ", menu[i]);
        }
    }

    refresh();
}
// adaugarea celulelor aleatoare cu valori 2 sau 4
void populate_grid(int grid[4][4], int nr)
{

    int k;
    for (k = 0; k < nr; k++)
    {
        int i, j;
        do
        {
            i = rand() % 4;
            j = rand() % 4;
        } while (grid[i][j] != 0);

        grid[i][j] = (rand() % 2 + 1) * 2;
    }
}
// golirea tablei de joc si resetarea scorului
void reset_game(int grid[4][4], int score)
{
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            grid[i][j] = 0;
    score = 0;
    populate_grid(grid, 2);
}
// mutarea in sus a celulelor
int move_up(int grid[4][4])
{
    int mut = 0;
    int score = 0;
    int i, j;
    int prev_grid[4][4];
    // memorarea tablei de joc inainte de mutare
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            prev_grid[i][j] = grid[i][j];
        }
    }
    // mutarea celulelor in sus
    for (j = 0; j < 4; j++)
    {
        int sch = 0;
        for (i = 1; i < 4; i++)
        {
            if (grid[i][j] != 0)
            {
                int prev = i - 1;
                // mut celulele nenule cat de sus pot
                while (prev >= 0 && grid[prev][j] == 0)
                {
                    grid[prev][j] = grid[prev + 1][j];
                    grid[prev + 1][j] = 0;
                    prev--;
                }
                // daca celula de deasupra este egala cu cea de sub ea, le adun
                if (prev >= 0 && grid[prev][j] == grid[prev + 1][j] && sch == 0)
                {

                    grid[prev][j] *= 2;
                    score += grid[prev][j];
                    grid[prev + 1][j] = 0;
                    sch = 1;
                }
            }
        }
    }
    // verific daca s-a mutat ceva
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (grid[i][j] != prev_grid[i][j])
            {
                mut = 1;
                break;
            }
        }
        if (mut == 1)
        {
            break;
        }
    }
    return mut ? score : 0;
}
// mutarea in jos a celulelor
// urmeaza acelasi algoritm ca la mutarea in sus
int move_down(int grid[4][4])
{
    int mut = 0;
    int score = 0;
    int i, j;
    int prev_grid[4][4];

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            prev_grid[i][j] = grid[i][j];
        }
    }
    // mutarea celulelor in jos
    for (j = 0; j < 4; j++)
    {
        int sch = 0;
        for (i = 2; i >= 0; i--)
        {
            if (grid[i][j] != 0)
            {
                int urm = i + 1;
                // mut celulele nenule cat de jos pot
                while (urm < 4 && grid[urm][j] == 0)
                {

                    grid[urm][j] = grid[urm - 1][j];
                    grid[urm - 1][j] = 0;
                    urm++;
                }
                // daca celula de sub este egala cu cea de deasupra, le adun
                if (urm < 4 && grid[urm][j] == grid[urm - 1][j] && sch == 0)
                {

                    grid[urm][j] *= 2;
                    score += grid[urm][j];
                    grid[urm - 1][j] = 0;

                    sch = 1;
                }
            }
        }
    }
    // verific daca s-a mutat ceva
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (grid[i][j] != prev_grid[i][j])
            {
                mut = 1;
                break;
            }
        }
        if (mut == 1)
        {
            break;
        }
    }
    return mut ? score : 0;
}
// mutarea la stanga a celulelor
int move_left(int grid[4][4])
{
    int mut = 0;
    int score = 0;
    int i, j;
    int prev_grid[4][4];
    // memorarea tablei de joc inainte de mutare
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            prev_grid[i][j] = grid[i][j];
        }
    }
    // mutarea celulelor la stanga
    for (i = 0; i < 4; i++)
    {
        int sch = 0;
        for (j = 1; j < 4; j++)
        {
            if (grid[i][j] != 0)
            {
                int prev = j - 1;
                // mut celulele nenule cat de la stanga pot
                while (prev >= 0 && grid[i][prev] == 0)
                {
                    grid[i][prev] = grid[i][prev + 1];
                    grid[i][prev + 1] = 0;
                    prev--;
                }
                // daca celula din stanga este egala cu cea din dreapta, le adun
                if (prev >= 0 && grid[i][prev] == grid[i][prev + 1] && sch == 0)
                {
                    grid[i][prev] *= 2;
                    score += grid[i][prev];
                    grid[i][prev + 1] = 0;

                    sch = 1;
                }
            }
        }
    }
    // verific daca s-a mutat ceva
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (grid[i][j] != prev_grid[i][j])
            {
                mut = 1;
                break;
            }
        }
        if (mut == 1)
        {
            break;
        }
    }

    return mut ? score : 0;
}
// mutarea la dreapta a celulelor
int move_right(int grid[4][4])
{
    int mut = 0;
    int score = 0;
    int i, j;
    int prev_grid[4][4];
    // memorarea tablei de joc inainte de mutare
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            prev_grid[i][j] = grid[i][j];
        }
    }
    // mutarea celulelor la dreapta
    for (i = 0; i < 4; i++)
    {
        int sch = 0;
        for (j = 2; j >= 0; j--)
        {
            if (grid[i][j] != 0)
            {
                int urm = j + 1;
                // mut celulele nenule cat de la dreapta pot
                while (urm < 4 && grid[i][urm] == 0)
                {
                    grid[i][urm] = grid[i][urm - 1];
                    grid[i][urm - 1] = 0;
                    urm++;
                }
                // daca celula din dreapta este egala cu cea din stanga, le adun
                if (urm < 4 && grid[i][urm] == grid[i][urm - 1] && sch == 0)
                {
                    grid[i][urm] *= 2;
                    score += grid[i][urm];
                    grid[i][urm - 1] = 0;

                    sch = 1;
                }
            }
        }
    }
    // verific daca s-a mutat ceva
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (grid[i][j] != prev_grid[i][j])
            {
                mut = 1;
                break;
            }
        }
        if (mut == 1)
        {
            break;
        }
    }
    return mut ? score : 0;
}
// afisarea tablei de joc
void draw_grid(int grid[4][4], WINDOW *leftBox, int starty, int y, int lat, int inalt, int x)
{
    start_color();
    initialize_colors();
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            // creez o noua fereastra pentru fiecare celula
            // asociez o culoare fiecarei celule in functie de valoarea ei
            WINDOW *cell = newwin(inalt, lat, starty + y + i * inalt, x + j * lat);

            if (grid[i][j] == 2)
            {
                wbkgd(cell, COLOR_PAIR(2));
            }
            else if (grid[i][j] == 4)
            {
                wbkgd(cell, COLOR_PAIR(3));
            }
            else if (grid[i][j] == 8)
            {
                wbkgd(cell, COLOR_PAIR(4));
            }
            else if (grid[i][j] == 16)
            {
                wbkgd(cell, COLOR_PAIR(5));
            }
            else if (grid[i][j] == 32)
            {
                wbkgd(cell, COLOR_PAIR(6));
            }
            else if (grid[i][j] == 64)
            {
                wbkgd(cell, COLOR_PAIR(7));
            }
            else if (grid[i][j] == 128)
            {
                wbkgd(cell, COLOR_PAIR(8));
            }
            else if (grid[i][j] == 256)
            {
                wbkgd(cell, COLOR_PAIR(9));
            }
            else if (grid[i][j] == 512)
            {
                wbkgd(cell, COLOR_PAIR(10));
            }
            else if (grid[i][j] == 1024)
            {
                wbkgd(cell, COLOR_PAIR(11));
            }
            else if (grid[i][j] == 2048)
            {
                wbkgd(cell, COLOR_PAIR(12));
            }
            else
            {
                wbkgd(cell, COLOR_PAIR(1));
            }
            // afisez numarul din celula daca este nenula
            if (grid[i][j] == 0)
            {
                box(cell, 0, 0);
            }
            else
            {
                char num[5];
                sprintf(num, "%d", grid[i][j]);
                int num_y = inalt / 2;
                int num_x = (lat - strlen(num)) / 2;
                wattron(cell, A_BOLD);
                mvwprintw(cell, num_y, num_x, "%s", num);
                wattroff(cell, A_BOLD);
            }
            wrefresh(cell);
            delwin(cell);
        }
    }
}
// afisarea scorului
void print_score(WINDOW *rightBox, int starty, int score)
{
    int score_y = starty + 2;
    int latC = getmaxx(rightBox);
    int score_len = snprintf(NULL, 0, "Score: %d", score);
    int score_x = (latC - score_len) / 2;
    mvwprintw(rightBox, score_y, score_x, "Score: %d", score);
    wrefresh(rightBox);
}
// verificarea daca s-a ajuns la 2048
int check_win(int grid[4][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (grid[i][j] == 2048)
            {
                return 1;
            }
        }
    }
    return 0;
}
// verificarea daca s-a ajuns la finalul jocului
int check_game_over(int grid[4][4])
{
    int i, j;
    int count = 0;
    int ok = 0;
    // verific daca oricare doua celule adiacente sunt egale
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (grid[i][j] == 0)
            {
                ok = 1;
            }
            if (i > 0 && grid[i][j] == grid[i - 1][j])
            {
                ok = 1;
            }
            if (i < 3 && grid[i][j] == grid[i + 1][j])
            {
                ok = 1;
            }
            if (j > 0 && grid[i][j] == grid[i][j - 1])
            {
                ok = 1;
            }
            if (j < 3 && grid[i][j] == grid[i][j + 1])
            {
                ok = 1;
            }
            if (grid[i][j] != 0)
            {
                count++;
            }
        }
    }
    // daca nu exista celule adiacente egale si tabla e plina
    // jocul s-a terminat
    if (ok == 0 && count == 16)
    {
        return 1;
    }

    return 0;
}
// numararea celulelor goale
int count_empty_cells(int grid[4][4])
{
    int count = 0;
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (grid[i][j] == 0)
            {
                count++;
            }
        }
    }
    return count;
}
// determinarea celei mai bune mutari
int best_direction(int grid[4][4])
{
    int dir[4] = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
    int max1 = -1;
    int best = -1;
    int i;
    for (i = 0; i < 4; i++)
    {

        int grid0[4][4];
        memcpy(grid0, grid, sizeof(grid0));

        if (dir[i] == KEY_UP)
        {
            move_up(grid0);
        }
        else if (dir[i] == KEY_DOWN)
        {
            move_down(grid0);
        }
        else if (dir[i] == KEY_LEFT)
        {
            move_left(grid0);
        }
        else if (dir[i] == KEY_RIGHT)
        {
            move_right(grid0);
        }
        // stabilesc care e cea mai buna mutare
        // in functie de numarul de celule goale in fiecare caz
        int empty = count_empty_cells(grid0);
        if (empty > max1)
        {
            max1 = empty;
            best = dir[i];
        }
    }

    return best;
}
// afisarea informatiilor din dreapta ecranului
void right_print(WINDOW *rightBox, int score)
{
    time_t t;
    time(&t);
    struct tm *tm_info = localtime(&t);
    char buffer[26];
    strftime(buffer, 26, "%H:%M:%S %d-%m", tm_info);
    int len = strlen(buffer);
    int inaltC = getmaxy(rightBox);
    int latC = getmaxx(rightBox);
    int startx = (latC - len) / 2;
    int starty = (inaltC - 3) / 2;
    print_score(rightBox, starty, score);
    mvwprintw(rightBox, starty, startx, "%s", buffer);
    wrefresh(rightBox);
    int prev_grid[4][4];
    int i;
    for (i = 0; i < 4; i++)
    {
        memcpy(prev_grid[i], grid[i], sizeof(int) * 4);
    }

    char *text[] = {
        "Use the arrow keys to:",
        "Up: Move tiles upwards",
        "Down: Move tiles downwards",
        "Left: Move tiles to the left",
        "Right: Move tiles to the right",
        "Press 'Q' or 'q' to quit the game",
        "Press 'Z' or 'z' to undo the last move"};

    int text_y = starty + 4;

    for (i = 0; i < sizeof(text) / sizeof(char *); i++)
    {
        int text_x = (latC - strlen(text[i])) / 2;
        mvwprintw(rightBox, text_y + i, text_x, "%s", text[i]);
    }

    wrefresh(rightBox);
}
// functia principala de joc
void start(int grid[4][4], int score, int state)
{
    time_t last_move;
    initscr();
    start_color();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    initialize_colors();
    clear();
    refresh();
    bkgd(COLOR_PAIR(1));
    // calculez dimensiuni si creez ferestrele
    int lin, col;
    getmaxyx(stdscr, lin, col);
    lin = lin - 5;
    int size;
    int i, j;
    if (lin < col)
    {
        size = lin - 6;
    }
    else
    {
        size = col / 2 - 6;
    }
    int start = (lin - size) / 2;
    int jum = col / 2;

    WINDOW *leftBox = newwin(lin + 2, jum, start + 5, jum);
    wbkgd(leftBox, COLOR_PAIR(1));

    int inalt = size / 4;
    int lat = jum / 4;

    int grid_y = (size - inalt * 4) / 2;
    int grid_x = (jum - lat * 4) / 2;

    draw_grid(grid, leftBox, start, grid_y, lat, inalt, grid_x);
    wrefresh(leftBox);

    WINDOW *rightBox = newwin(lin, 0, start - 3.75, jum);
    wbkgd(rightBox, COLOR_PAIR(1));
    nodelay(stdscr, TRUE);
    right_print(rightBox, score);
    wrefresh(rightBox);
    int ch;
    // fac o copie a tablei actuale de joc
    int prev_grid[4][4];
    for (i = 0; i < 4; i++)
    {
        memcpy(prev_grid[i], grid[i], sizeof(int) * 4);
    }
    last_move = time(NULL);
    // bucla principala pt logica jocului
    while (1)
    {
        right_print(rightBox, score);
        wrefresh(rightBox);
        int prev_score = score;
        // citesc mutarea user-ului
        ch = getch();
        int mut = 0;
        if (ch == 'Q' || ch == 'q')
        {
            endwin();
            last_move = time(NULL);
            break;
        }
        else if (ch == 'z' || ch == 'Z')
        {
            // pentru functia de undo, ma intorc la momentul anterior
            // salvat la inceput
            for (int i = 0; i < 4; i++)
            {
                memcpy(grid[i], prev_grid[i], sizeof(int) * 4);
            }
            score = prev_score;
            draw_grid(grid, leftBox, start, grid_y, lat, inalt, grid_x);
            right_print(rightBox, score);
            last_move = time(NULL);
            continue;
        }
        else
        {
            // memorez tabla de joc inainte de mutare
            int prev_grid[4][4];
            for (i = 0; i < 4; i++)
            {
                memcpy(prev_grid[i], grid[i], sizeof(int) * 4);
            }
            // mut celulele in functie de mutarea user-ului
            // actualizez last_move pentru a calcula corect timpul de la ultima mutare
            if (ch == KEY_UP)
            {
                mut = move_up(grid);
                last_move = time(NULL);
            }
            else if (ch == KEY_DOWN)
            {
                mut = move_down(grid);
                last_move = time(NULL);
            }
            else if (ch == KEY_LEFT)
            {
                mut = move_left(grid);
                last_move = time(NULL);
            }
            else if (ch == KEY_RIGHT)
            {
                mut = move_right(grid);
                last_move = time(NULL);
            }
            // verific daca s-a modificat tabla de joc
            int ct = 0;
            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    if (grid[i][j] == prev_grid[i][j])
                    {
                        ct++;
                    }
                }
            }
            // in caz afirmativ, adaug o noua celula aleatorie si actualizez scorul
            if (ct != 16)
            {
                populate_grid(grid, 1);
                score += mut;
            }
            // daca au trecut 10 secunde de la ultima mutare
            // calculez cea mai buna mutare si o execut
            if (difftime(time(NULL), last_move) >= 10)
            {

                for (i = 0; i < 4; i++)
                {
                    memcpy(prev_grid[i], grid[i], sizeof(int) * 4);
                }
                ch = best_direction(grid);
                if (ch == KEY_UP)
                {
                    mut = move_up(grid);
                    last_move = time(NULL);
                }
                else if (ch == KEY_DOWN)
                {
                    mut = move_down(grid);
                    last_move = time(NULL);
                }
                else if (ch == KEY_LEFT)
                {
                    mut = move_left(grid);
                    last_move = time(NULL);
                }
                else if (ch == KEY_RIGHT)
                {
                    mut = move_right(grid);
                    last_move = time(NULL);
                }

                int ct = 0;
                for (i = 0; i < 4; i++)
                {
                    for (j = 0; j < 4; j++)
                    {
                        if (grid[i][j] == prev_grid[i][j])
                        {
                            ct++;
                        }
                    }
                }

                if (ct != 16)
                {
                    populate_grid(grid, 1);
                    score += mut;
                }
                last_move = time(NULL);
                wrefresh(rightBox);
            }
            else
            {
                ch = getch();
            }

            draw_grid(grid, leftBox, start, grid_y, lat, inalt, grid_x);
            wrefresh(leftBox);
            // verific daca s-a ajuns la 2048
            if (check_win(grid))
            {

                wrefresh(leftBox);

                right_print(rightBox, score);
                int x = (getmaxx(rightBox) - strlen("You win!") - 2) / 2;
                wattron(rightBox, A_BOLD);
                mvwprintw(rightBox, 5, x, "You win!");
                wattroff(rightBox, A_BOLD);
                wrefresh(rightBox);

                sleep(10);

                break;
            }
            draw_grid(grid, leftBox, start, grid_y, lat, inalt, grid_x);
            wrefresh(leftBox);
            // verific daca tabla de joc este plina si nu mai exista mutari
            if (check_game_over(grid))
            {

                wrefresh(leftBox);

                int x = (getmaxx(rightBox) - strlen("Game over!") - 2) / 2;
                wattron(rightBox, A_BOLD);
                mvwprintw(rightBox, 5, x, "Game over!");
                wattroff(rightBox, A_BOLD);
                wrefresh(rightBox);

                sleep(10);

                break;
            }
        }
        // salvez tabla de joc si scorul
        // pentru functia de resume
        int i;
        score2 = score;
        for (i = 0; i < 4; i++)
        {
            memcpy(grid2[i], grid[i], sizeof(int) * 4);
        }

        draw_grid(grid, leftBox, start, grid_y, lat, inalt, grid_x);
        wrefresh(leftBox);

        right_print(rightBox, score);
    }
    delwin(leftBox);
    delwin(rightBox);
    endwin();
}

int main()
{
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(0, NULL);
    srand(time(NULL));
    start_color();
    bkgd(COLOR_PAIR(1));
    char *opt[] = {"New Game", "Resume", "Quit"};
    int nr = 3;
    int aleg = 1;
    int user_choice;
    // primesc input-ul user-ului
    while (1)
    {
        clear();
        // afisez meniul
        menu(opt, nr, aleg);

        user_choice = getch();
        // la fiecare mutare in sus sau in jos, schimb optiunea selectata
        if (user_choice == KEY_UP)
        {
            if (aleg == 1)
            {
                aleg = nr;
            }
            else
            {
                aleg--;
            }
        }
        else if (user_choice == KEY_DOWN)
        {
            if (aleg == nr)
            {
                aleg = 1;
            }
            else
            {
                aleg++;
            }
        }
        // cand se apasa enter, se executa optiunea selectata
        else if (user_choice == 10)
        {
            if (aleg == 1)
            {
                reset_game(grid, score);
                start(grid, score, 0);
            }
            else if (aleg == 2)
            {
                int i;
                for (i = 0; i < 4; i++)
                {
                    memcpy(grid[i], grid2[i], 4 * sizeof(int));
                }
                score = score2;
                start(grid, score, 1);
            }
            else if (aleg == 3)
            {
                curs_set(1);
                endwin();
                return 0;
            }
        }
    }
    curs_set(1);
    endwin();
    return 0;
}
