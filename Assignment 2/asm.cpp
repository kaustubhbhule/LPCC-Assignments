#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> CODE, INTCODE, MNT, MDT, FVPPL, AVPPL;

void toVector(string filename)
{
    string data, word;
    ifstream file(filename);
    while (getline(file, data))
    {
        string line = " ";
        for (int i = 0; i < data.length(); i++)
        {
            if (data[i] == ';')
                break;
            else if (data[i] == ',')
                line += ' ';
            else
                line += data[i];
        }
        istringstream iss(line);
        vector<string> temp;
        for (string word; iss >> word;)
        {
            temp.push_back(word);
        }
        CODE.push_back(temp);
    }
    file.close();
}

void showTable(vector<vector<string>> table, string name, bool isIC = false)
{
    cout << "\n---------------------------------" << endl;
    cout << " " << name << endl;
    cout << "---------------------------------\n"
         << endl;
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
        {
            if (isIC)
            {
                if (j == 0 || j == table[i].size() - 1)
                    cout << table[i][j] << " ";
                else
                    cout << table[i][j] << ", ";
            }
            else
                cout << table[i][j] << "\t";
        }

        cout << endl;
    }
    cout << endl;
}

int getRowIndex(string str, vector<vector<string>> table)
{
    for (int i = 0; i < table.size(); i++)
        if (str == table[i][0])
            return i;
    return -1;
}

int getColIndex(int row_id, string str, vector<vector<string>> table)
{
    for (int i = 0; i < table[row_id].size(); i++)
        if (str == table[row_id][i])
            return i;
    return -1;
}

void genTAB()
{
    int mnt_index = 1;
    for (int i = 0; i < CODE.size(); i++)
    {
        vector<string> temp;
        string macro;
        if (CODE[i][0] == "MACRO")
        {
            macro = CODE[i][1];
            temp.push_back(CODE[i][1]);
            temp.push_back(to_string(CODE[i].size() - 2));
            temp.push_back(to_string(mnt_index));
            MNT.push_back(temp);

            temp.clear();
            temp = CODE[i];
            temp.erase(temp.begin());
            FVPPL.push_back(temp);
            temp.clear();

            while (CODE[i][0] != "MEND")
            {
                i++;
                temp.clear();
                for (int j = 0; j < CODE[i].size(); j++)
                {
                    int arg_id = getColIndex(getRowIndex(macro, FVPPL), CODE[i][j], FVPPL);
                    if (arg_id >= 0)
                        temp.push_back("#" + to_string(arg_id));
                    else
                        temp.push_back(CODE[i][j]);
                }
                if (getRowIndex(CODE[i][0], FVPPL) > -1)
                {
                    temp.clear();
                    temp = CODE[i];
                    AVPPL.push_back(temp);
                }
                MDT.push_back(temp);
                mnt_index++;
            }
        }
        else
        {
            INTCODE.push_back(CODE[i]);
        }
    }
}

int main()
{
    toVector("input.asm");
    genTAB();
    showTable(INTCODE, "Intermediate Code (IC)", true);
    showTable(MNT, "Macro Names Table (MNT)");
    showTable(MDT, "Macro Definition Table (MDT)");
    return 0;
}