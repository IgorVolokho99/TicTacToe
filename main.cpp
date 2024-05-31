#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>


void print_vector(std::vector<int>& v_m)
{
    for (auto x: v_m)
        std::cout << x << " ";
    std::cout << std::endl;
}

bool check_win(std::vector<char>& board)
{
    for (int i = 0; i < 3; ++i) if (board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2] && board[i * 3 + 2] != '-') return true;

    for (int i = 0; i < 3; ++i) if (board[0 + i] == board[3 + i] && board[3 + i] == board[6 + i] && board[6 + i] != '-') return true;

    if (board[0] == board[4] && board[4] == board[8] && board[8] != '-') return true;

    if (board[2] == board[4] && board[4] == board[6] && board[6] != '-') return true;

    return false;
}

void show_board(std::vector<char>& board)
{

    std::cout << board[0] << " " << board[1] << " " << board[2] << std::endl;
    std::cout << board[3] << " " << board[4] << " " << board[5] << std::endl;
    std::cout << board[6] << " " << board[7] << " " << board[8] << std::endl;
    std::cout << "-----" << std::endl;

}

char find_the_best_move(std::vector<char> board, std::vector<int> valid_moves, char last_move)
{
    if (check_win(board)) return last_move;
    else if (valid_moves.size() == 0) return 'D';
    else {
        if (last_move == 'x') {
            std::vector<char> results;
            for (int i = 0; i < valid_moves.size(); ++i)
            {
                std::vector<char> b(board);
                std::vector<int> v(valid_moves);
                b[valid_moves[i]] = 'o';
                v.erase(std::remove(v.begin(), v.end(), valid_moves[i]), v.end());
                results.push_back(find_the_best_move(b, v, 'o'));
            }
            if (std::find(results.begin(), results.end(), 'o') != results.end()) return 'o';
            else if (std::find(results.begin(), results.end(), 'D') != results.end()) return 'D';
            else return 'x';
        } else {
            std::vector<char> results;
            for (int i = 0; i < valid_moves.size(); ++i)
            {
                std::vector<char> b = board;
                std::vector<int> v = valid_moves;
                b[valid_moves[i]] = 'x';
                v.erase(std::remove(v.begin(), v.end(), valid_moves[i]), v.end());
                results.push_back(find_the_best_move(b, v, 'x'));
            }

            if (std::count(results.begin(), results.end(), 'x') >= 1) return 'x';
            else if (std::count(results.begin(), results.end(), 'D') >= 1) return 'D';
            else return 'o';
        }
    }
}

int f(std::vector<char>& board, std::vector<int>& valid_moves)
{
    for (int i = 0; i < valid_moves.size(); ++i)
    {
        std::vector<char> b = board;
        std::vector<int> v = valid_moves;
        b[valid_moves[i]] = 'o';
        int bot_move = valid_moves[i];
        v.erase(std::remove(v.begin(), v.end(), valid_moves[i]), v.end());
        if (find_the_best_move(b, v, 'o') == 'D' || find_the_best_move(b, v, 'o') == 'o')
         {
            return valid_moves[i];
        }
    }



}


int main()
{
    srand(time(0));

    std::vector<char> board = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
    std::vector<int> valid_moves = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    show_board(board);
    while (not check_win(board) && valid_moves.size() != 0)
    {
        std::cout << "Enter your move: ";
        int player_move;
        std::cin >> player_move;
        board[player_move - 1] = 'x';
        valid_moves.erase(std::remove(valid_moves.begin(), valid_moves.end(), player_move - 1), valid_moves.end());
        show_board(board);
        if (check_win(board)) {
            std::cout << "You won this game!" << std::endl;
            break;
        } else if (valid_moves.size() == 0) {
            std::cout << "It's a draw!" << std::endl;
            break;
        }

        int bot_move = f(board, valid_moves);
        board[bot_move] = 'o';
        valid_moves.erase(std::remove(valid_moves.begin(), valid_moves.end(), bot_move), valid_moves.end());
        show_board(board);
        if (check_win(board)) {
            std::cout << "You lost this game!" << std::endl;
            break;
        }
    }



    return 0;
}
