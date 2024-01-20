#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

struct inputType
{
    string type;
    string x;
    string y;
};

// ------------------------------------------------------------------------ Mau Chuc Nang --------------------------------------------------------------------------------
int modeFunction();
void singlePlayerFunction();
void multiPlayerFunction();
int difficultyLevelFunction();
int boardSizeFunction(int difficulty, int &noOfMines);
void helpGuideFunction(int boardSize, int numOfMines);
vector<vector<char> > myBoardFunction(int difficulty);
vector<vector<char> > realBoardFunction(int boardSize, int noOfMines, int &countDigs, vector<vector<char> > &myBoard);
vector<vector<char> > manualBoardFunction(int boardSize, int numOfMines, int &countDigs, vector<vector<char> > &myBoard, string &name1, string &name2);
void updateBoardFunction(vector<vector<char> > &myBoard, vector<vector<char> > &realBoard, int boardSize, int &countDigs, string type, int x, int y);
void printBoardFunction(vector<vector<char> > &board);
void IO_Function(vector<vector<char> > &myBoard, vector<vector<char> > &realBoard, int boardSize, int flag, int numOfMines, int &countDigs, string &name, string name2 = "");
inputType inputConstraintFunction(vector<vector<char> > &myBoard, int boardSize, int flag);
void lostBoardFunction(vector<vector<char> > &myBoard, vector<vector<char> > &realBoard, int boardSize, string name, string name2 = "");
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Chon che do
int modeFunction()
{
    cout << "\nCo Hai Che do :\n"
         << "Mot Nguoi Choi: Random bay min`.\n"
         << "Hai nguoi choi: Nguoi choi thu 2 se dat bay cho nguoi choi thu 1\n";
    cout << "\nChon che do :\n"
         << "Nhap 1 cho mot nguoi choi\n"
         << "Nhap 2 cho 2 nguoi choi\n"
         << ": ";

    string mode;
    getline(cin, mode);

    if (mode == "1")
    {
        return 1;
    }
    else if (mode == "2")
    {
        return 2;
    }
    else
    {
        cout << "Chon Sai. Vui Long Chon Lai\n";
        return modeFunction();
    }
}

// Voi che do 1 nguoi choi:
void singlePlayerFunction()
{
    cout << "\nTen cua ban : ";
    string name;
    getline(cin, name);

    // do kho ( Bang cung nhu so luong min )
    int difficulty = difficultyLevelFunction();

    int numOfMines;
    int boardSize = boardSizeFunction(difficulty, numOfMines);

    helpGuideFunction(boardSize, numOfMines);

    vector<vector<char> > myBoard = myBoardFunction(boardSize);
    printBoardFunction(myBoard);

    int countDigs = 0;

    // Nay` chua mo se k hien thi
    vector<vector<char> > realBoard = realBoardFunction(boardSize, numOfMines, countDigs, myBoard);
    IO_Function(myBoard, realBoard, boardSize, numOfMines, numOfMines, countDigs, name);
}

// 2 nguoi choi
void multiPlayerFunction()
{
    cout << "\nTen nguoi choi thu 1 : ";
    string name1;
    getline(cin, name1);
    cout << "Ten nguoi choi thu 2 : ";
    string name2;
    getline(cin, name2);

    // do kho
    int difficulty = 1;

    int numOfMines;
    int boardSize = boardSizeFunction(difficulty, numOfMines);

    helpGuideFunction(boardSize, numOfMines);

    vector<vector<char> > myBoard = myBoardFunction(boardSize);

    int countDigs = 0;

    vector<vector<char> > realBoard = manualBoardFunction(boardSize, numOfMines, countDigs, myBoard, name1, name2);
    IO_Function(myBoard, realBoard, boardSize, numOfMines, numOfMines, countDigs, name1, name2);
}

// Do kho cho 1 ng choi
int difficultyLevelFunction()
{
    cout << "\nChon Do Kho :\n"
         << "Nhap 1 cho Co ban (9x9 & 10 min)\n"
         << "Nhap 2 cho Trung Binh (16x16 & 40 min)\n"
         << "Nhap 3 cho Nang Cao (24x24 & 99 min)\n"
         << ": ";

    string difficulty;
    getline(cin, difficulty);

    if (difficulty == "1")
    {
        return 1;
    }
    else if (difficulty == "2")
    {
        return 2;
    }
    else if (difficulty == "3")
    {
        return 3;
    }
    else
    {
        cout << "Nhap sai! Vui long thu lai.\n";
        return difficultyLevelFunction();
    }
}
int boardSizeFunction(int difficulty, int &numOfMines)
{
    int size;
    switch (difficulty)
    {
    case 1:
        size = 9;
        numOfMines = 10;
        break;
    case 2:
        size = 16;
        numOfMines = 40;
        break;
    case 3:
        size = 24;
        numOfMines = 99;
        break;
    default:
        break;
    }
    return size;
}

// Tro giup
void helpGuideFunction(int boardSize, int numOfMines)
{
    cout << "\nTro Giup :\n"
         << "Ban se duoc mot khu mine " << boardSize << "x" << boardSize << ", bao gom" << numOfMines << " qua min.\n"
         << "Ban se co " << numOfMines << " ( flag ), ban co the danh dau o min.\n"
         << "So hang va so cot se duoc de cap lan luot o ben trai va phai tren de giup ban.\n"
         << "Huong dan choi : \n"
         << "D x y - Dao o vi tri (x, y), Mien la o do chua hien thi va gan co.\n"
         << "F x y - Dat co tai o (x, y), Mien la o do chua hien thi.\n"
         << "U x y - Bo co khoi o (x, y), Mien la o do da duoc dat co.\n";
}

vector<vector<char> > myBoardFunction(int boardSize)
{
    vector<vector<char> > myBoard(boardSize, vector<char>(boardSize, '-'));
    return myBoard;
}

vector<vector<char> > realBoardFunction(int boardSize, int numOfMines, int &countDigs, vector<vector<char> > &myBoard)
{
    cout << "Nhap toa do (D x y) : ";
    inputType input;
    cin >> input.type >> input.x >> input.y;

    //Checking whether the command is correct or not and the provided input is inside board or not
    while (input.type != "D" || stoi(input.x) < 0 || stoi(input.x) >= boardSize || stoi(input.y) < 0 || stoi(input.y) >= boardSize)
    {
        if (input.type != "D")
        {
            cout << "\"" << input.type << "\" Khong hop le. Vui long thu lai.\n\n";
        }
        else if (stoi(input.x) < 0 || stoi(input.x) >= boardSize || stoi(input.y) < 0 || stoi(input.y) >= boardSize)
        {
            cout << "(" << stoi(input.x) << ", " << stoi(input.y) << ") Nam ngoai pham vi. Vui long thu lai.\n\n";
        }
        cout << "Nhap toa do (D x y) : ";
        cin >> input.type >> input.x >> input.y;
    }

    vector<vector<char> > realBoard(boardSize, vector<char>(boardSize, '-'));
    realBoard[stoi(input.x)][stoi(input.y)] = '?';

    // Random min
    while (numOfMines)
    {
        int xMine = rand() % boardSize;
        int yMine = rand() % boardSize;
        if (abs(xMine - stoi(input.x)) > 1 && abs(yMine - stoi(input.y)) > 1 && realBoard[xMine][yMine] == '-')
        {
            realBoard[xMine][yMine] = '*';
            numOfMines--;
        }
    }

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (realBoard[i][j] != '*')
            {
                int count = 0;
                if (i != 0 && j != 0 && realBoard[i - 1][j - 1] == '*')
                {
                    count++;
                }
                if (i != 0 && j != boardSize - 1 && realBoard[i - 1][j + 1] == '*')
                {
                    count++;
                }
                if (i != boardSize - 1 && j != 0 && realBoard[i + 1][j - 1] == '*')
                {
                    count++;
                }
                if (i != boardSize - 1 && j != boardSize - 1 && realBoard[i + 1][j + 1] == '*')
                {
                    count++;
                }
                if (i != 0 && realBoard[i - 1][j] == '*')
                {
                    count++;
                }
                if (i != boardSize - 1 && realBoard[i + 1][j] == '*')
                {
                    count++;
                }
                if (j != 0 && realBoard[i][j - 1] == '*')
                {
                    count++;
                }
                if (j != boardSize - 1 && realBoard[i][j + 1] == '*')
                {
                    count++;
                }
                realBoard[i][j] = '0' + count;
            }
        }
    }

    updateBoardFunction(myBoard, realBoard, boardSize, countDigs, input.type, stoi(input.x), stoi(input.y));
    return realBoard;
}

vector<vector<char> > manualBoardFunction(int boardSize, int numOfMines, int &countDigs, vector<vector<char> > &myBoard, string &name1, string &name2)
{
    int numOfMinesCopy = numOfMines;
    numOfMinesCopy++;

    vector<pair<int, int> > manualInput;
    string manualInputX, manualInputY;
    cout << "\n"
         << name2 << ", Ban phai cung cap " << numOfMinesCopy << " cap toa do dat min (Them 1 de tranh bi thua dau game " << name1 << ").\n";

    while (numOfMinesCopy)
    {
        cout << "Nhap toa do (x y) : ";
        cin >> manualInputX >> manualInputY;

        if (stoi(manualInputX) < 0 || stoi(manualInputX) >= boardSize || stoi(manualInputY) < 0 || stoi(manualInputY) >= boardSize)
        {
            cout << "(" << stoi(manualInputX) << ", " << stoi(manualInputY) << ") Nam ngoai pham vi. Vui long thu lai.\n";
        }
        else if (1)
        {
            bool check = true;
            for (int i = 0; i < manualInput.size(); i++)
            {
                if (manualInput[i].first == stoi(manualInputX) && manualInput[i].second == stoi(manualInputY))
                {
                    check = false;
                    cout << "Ban da nhap o nay roi (" << stoi(manualInputX) << ", " << stoi(manualInputY) << "). Vui long thu lai.\n";
                    break;
                }
            }
            if (check)
            {
                manualInput.push_back(make_pair(stoi(manualInputX), stoi(manualInputY)));
                numOfMinesCopy--;
            }
        }
    }

    for (int i = 0; i < 1000; i++)
    {
        cout << "Chuan bi mine...\n";
    }

    cout << "\n"
         << name1 << ", Luot cua ban!\n";
    printBoardFunction(myBoard);

    cout << "Nhap toa do (D x y) : ";
    inputType input;
    cin >> input.type >> input.x >> input.y;

    while (input.type != "D" || stoi(input.x) < 0 || stoi(input.x) >= boardSize || stoi(input.y) < 0 || stoi(input.y) >= boardSize)
    {
        if (input.type != "D")
        {
            cout << "\"" << input.type << "\" Khong hop le. Vui long thu lai.\n\n";
        }
        else if (stoi(input.x) < 0 || stoi(input.x) >= boardSize || stoi(input.y) < 0 || stoi(input.y) >= boardSize)
        {
            cout << "(" << stoi(input.x) << ", " << stoi(input.y) << ") Nam ngoai pham vi. Vui long thu lai.\n\n";
        }
        cout << "Nhap toa do (D x y) : ";
        cin >> input.type >> input.x >> input.y;
    }

    vector<vector<char> > realBoard(boardSize, vector<char>(boardSize, '-'));
    realBoard[stoi(input.x)][stoi(input.y)] = '?';

    for (int i = 0; i < manualInput.size(); i++)
    {
        if (realBoard[manualInput[i].first][manualInput[i].second] == '-')
        {
            realBoard[manualInput[i].first][manualInput[i].second] = '*';
            numOfMines--;
        }
        if (numOfMines == 0)
        {
            break;
        }
    }

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (realBoard[i][j] != '*')
            {
                int count = 0;
                if (i != 0 && j != 0 && realBoard[i - 1][j - 1] == '*')
                {
                    count++;
                }
                if (i != 0 && j != boardSize - 1 && realBoard[i - 1][j + 1] == '*')
                {
                    count++;
                }
                if (i != boardSize - 1 && j != 0 && realBoard[i + 1][j - 1] == '*')
                {
                    count++;
                }
                if (i != boardSize - 1 && j != boardSize - 1 && realBoard[i + 1][j + 1] == '*')
                {
                    count++;
                }
                if (i != 0 && realBoard[i - 1][j] == '*')
                {
                    count++;
                }
                if (i != boardSize - 1 && realBoard[i + 1][j] == '*')
                {
                    count++;
                }
                if (j != 0 && realBoard[i][j - 1] == '*')
                {
                    count++;
                }
                if (j != boardSize - 1 && realBoard[i][j + 1] == '*')
                {
                    count++;
                }
                realBoard[i][j] = '0' + count;
            }
        }
    }

    updateBoardFunction(myBoard, realBoard, boardSize, countDigs, input.type, stoi(input.x), stoi(input.y));
    return realBoard;
}

void updateBoardFunction(vector<vector<char> > &myBoard, vector<vector<char> > &realBoard, int boardSize, int &countDigs, string type, int x, int y)
{
    if (type == "F")
    {
        myBoard[x][y] = 'F';
    }
    else if (type == "U")
    {
        myBoard[x][y] = '-';
    }
    else
    {
        myBoard[x][y] = realBoard[x][y];
        countDigs++;

        if (realBoard[x][y] == '0')
        {
            if (x != 0 && y != 0 && myBoard[x - 1][y - 1] == '-')
            {
                updateBoardFunction(myBoard, realBoard, boardSize, countDigs, type, x - 1, y - 1);
            }
            if (x != 0 && y != boardSize - 1 && myBoard[x - 1][y + 1] == '-')
            {
                updateBoardFunction(myBoard, realBoard, boardSize, countDigs, type, x - 1, y + 1);
            }
            if (x != boardSize - 1 && y != 0 && myBoard[x + 1][y - 1] == '-')
            {
                updateBoardFunction(myBoard, realBoard, boardSize, countDigs, type, x + 1, y - 1);
            }
            if (x != boardSize - 1 && y != boardSize - 1 && myBoard[x + 1][y + 1] == '-')
            {
                updateBoardFunction(myBoard, realBoard, boardSize, countDigs, type, x + 1, y + 1);
            }
            if (x != 0 && myBoard[x - 1][y] == '-')
            {
                updateBoardFunction(myBoard, realBoard, boardSize, countDigs, type, x - 1, y);
            }
            if (x != boardSize - 1 && myBoard[x + 1][y] == '-')
            {
                updateBoardFunction(myBoard, realBoard, boardSize, countDigs, type, x + 1, y);
            }
            if (y != 0 && myBoard[x][y - 1] == '-')
            {
                updateBoardFunction(myBoard, realBoard, boardSize, countDigs, type, x, y - 1);
            }
            if (y != boardSize - 1 && myBoard[x][y + 1] == '-')
            {
                updateBoardFunction(myBoard, realBoard, boardSize, countDigs, type, x, y + 1);
            }
        }
    }
}
void printBoardFunction(vector<vector<char> > &board)
{
    cout << "\nBang hien tai cua ban :\n"
         << "     ";

    for (int i = 0; i < board.size(); i++)
    {
        cout << setw(2) << i << " ";
    }
    cout << "\n\n\n";
    for (int i = 0; i < board.size(); i++)
    {
        cout << setw(2) << i << "    ";

        for (int j = 0; j < board[i].size(); j++)
        {
            cout << board[i][j] << "  ";
        }
        cout << "\n\n";
    }
}

void IO_Function(vector<vector<char> > &myBoard, vector<vector<char> > &realBoard, int boardSize, int flag, int numOfMines, int &countDigs, string &name, string name2)
{
    printBoardFunction(myBoard);

    inputType input = inputConstraintFunction(myBoard, boardSize, flag);

    if (input.type == "D" && realBoard[stoi(input.x)][stoi(input.y)] == '*')
    {
        lostBoardFunction(myBoard, realBoard, boardSize, name, name2);
        return;
    }
    else if (input.type == "F")
    {
        flag--;
    }
    else if (input.type == "U")
    {
        flag++;
    }

    updateBoardFunction(myBoard, realBoard, boardSize, countDigs, input.type, stoi(input.x), stoi(input.y));

    if (countDigs == (boardSize * boardSize - numOfMines))
    {
        printBoardFunction(myBoard);
        cout << "Ban da chien thang, " << name << "!\n";
        if (name2 != "")
        {
            cout << "Ban da thua, " << name2 << "!\n";
        }
        return;
    }

    IO_Function(myBoard, realBoard, boardSize, flag, numOfMines, countDigs, name, name2);
}

inputType inputConstraintFunction(vector<vector<char> > &myBoard, int boardSize, int flag)
{
    cout << flag << ((flag == 1) ? " flag con lai.\n" : " flags con lai.\n") << "Nhap toa do (D/F/U x y) : ";

    inputType input;
    cin >> input.type >> input.x >> input.y;

    if (input.type != "D" && input.type != "F" && input.type != "U")
    {
        cout << "\"" << input.type << "\" Khong hop le. Vui long thu lai.\n\n";
        return inputConstraintFunction(myBoard, boardSize, flag);
    }
    else if (stoi(input.x) < 0 || stoi(input.x) >= boardSize || stoi(input.y) < 0 || stoi(input.y) >= boardSize)
    {
        cout << "(" << stoi(input.x) << ", " << stoi(input.y) << ") Nam ngoai pham vi. Vui long thu lai.\n\n";
        return inputConstraintFunction(myBoard, boardSize, flag);
    }
    else if (input.type == "D" && myBoard[stoi(input.x)][stoi(input.y)] == 'F')
    {
        cout << "Ban da dat co (flag) o day. Vui long thu lai.\n\n";
        return inputConstraintFunction(myBoard, boardSize, flag);
    }
    else if (input.type == "D" && myBoard[stoi(input.x)][stoi(input.y)] != '-')
    {
        cout << "O nay da duoc dao (mine). Vui long thu lai.\n\n";
        return inputConstraintFunction(myBoard, boardSize, flag);
    }
    else if (input.type == "F" && flag <= 0)
    {
        cout << "Ban khong con cai co (flag) nao. Vui long thu lai.\n\n";
        return inputConstraintFunction(myBoard, boardSize, flag);
    }
    else if (input.type == "F" && myBoard[stoi(input.x)][stoi(input.y)] == 'F')
    {
        cout << "Ban da dat co o day. Vui long thu lai.\n\n";
        return inputConstraintFunction(myBoard, boardSize, flag);
    }
    else if (input.type == "F" && myBoard[stoi(input.x)][stoi(input.y)] != '-')
    {
        cout << "O nay da duoc dao (mine). Vui long thu lai.\n\n";
        return inputConstraintFunction(myBoard, boardSize, flag);
    }
    else if (input.type == "U" && myBoard[stoi(input.x)][stoi(input.y)] != 'F')
    {
        cout << "Ban khong con cai co (flag) nao. Vui long thu lai.\n\n";
        return inputConstraintFunction(myBoard, boardSize, flag);
    }
    else
    {
        return input;
    }
}

void lostBoardFunction(vector<vector<char> > &myBoard, vector<vector<char> > &realBoard, int boardSize, string name, string name2)
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (realBoard[i][j] == '*' && myBoard[i][j] != 'F')
            {
                myBoard[i][j] = '*';
            }

            if (myBoard[i][j] == 'F' && realBoard[i][j] != '*')
            {
                myBoard[i][j] = 'X';
            }
        }
    }

    printBoardFunction(myBoard);
    cout << "Ban da thua, " << name << "!\n";
    if (name2 != "")
    {
        cout << "Ban da chien thang, " << name2 << "!\n";
    }
}

// Bat dau game
void masterFunction()
{
    srand(time(NULL));
    cout << "\n\nChao mung toi Minesweeper co ban!\n";

    int mode = modeFunction();
    if (mode == 1)
    {
        singlePlayerFunction();
    }
    else
    {
        multiPlayerFunction();
    }
}
int main()
{
    masterFunction();
    return 0;
}