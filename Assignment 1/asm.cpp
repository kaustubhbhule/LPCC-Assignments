#include <bits/stdc++.h>
using namespace std;

class Tables
{
public:
    int LC = 0, LT[2] = {0};
    vector<vector<string>> MOT{
        {"AREG", "RG", "01"},
        {"BREG", "RG", "02"},
        {"CREG", "RG", "03"},
        {"DREG", "RG", "04"},
        {"EQ", "CC", "01"},
        {"LT", "CC", "02"},
        {"GT", "CC", "03"},
        {"LE", "CC", "04"},
        {"GE", "CC", "05"},
        {"ANY", "CC", "06"},
        {"STOP", "IS", "00"},
        {"ADD", "IS", "01"},
        {"SUB", "IS", "02"},
        {"MULT", "IS", "03"},
        {"MOVER", "IS", "04"},
        {"MOVEM", "IS", "05"},
        {"COMP", "IS", "06"},
        {"BC", "IS", "07"},
        {"DIV", "IS", "08"},
        {"READ", "IS", "09"},
        {"PRINT", "IS", "10"},
        {"LOAD", "IS", "11"},
        {"START", "AD", "01"},
        {"END", "AD", "02"},
        {"ORIGIN", "AD", "03"},
        {"EQU", "AD", "04"},
        {"LTORG", "AD", "05"},
        {"DS", "DL", "01"},
        {"DC", "DL", "02"}};

    vector<vector<string>> CODE, INTCODE, SYMTAB, LITTAB, POOLTAB;

    int getIndex(string str, vector<vector<string>> table)
    {
        for (int i = 0; i < table.size(); i++)
            if (str == table[i][0])
                return i;
        return -1;
    }

    string getClass(string mnemonic)
    {
        int i = getIndex(mnemonic, MOT);
        if (i != -1)
            return MOT[i][1];
        return "NULL";
    }

    string getOpCODE(string mnemonic)
    {
        int i = getIndex(mnemonic, MOT);
        if (i != -1)
            return MOT[i][2];
        return "NULL";
    }

    bool isMnemonic(string str)
    {
        if (getIndex(str, MOT) > -1)
            return true;
        return false;
    }

    bool isConstant(string str)
    {
        try
        {
            if (stoi(str) >= 0)
                return true;
        }
        catch (exception &e)
        {
            return false;
        }
        return false;
    }

    bool isOperator(string str)
    {
        if (str.length() == 1)
            if (int(str[0]) > 41 && int(str[0]) < 48)
                return true;
        return false;
    }

    bool isLiteral(string str)
    {
        if (str[0] == '=')
            return true;
        return false;
    }

    bool isSymbol(string str)
    {
        if (!isMnemonic(str) && !isConstant(str) && !isOperator(str) && !isLiteral(str))
            return true;
        return false;
    }

    void genTAB()
    {
        for (int i = 0; i < CODE.size(); i++)
        {
            for (int j = 0; j < CODE[i].size(); j++)
            {
                if (isSymbol(CODE[i][j]) && getIndex(CODE[i][j], SYMTAB) == -1 && j != 0)
                    SYMTAB.push_back({CODE[i][j]});
                else if (isLiteral(CODE[i][j]))
                    LITTAB.push_back({CODE[i][j]});
            }
        }
    }

    void showTAB(vector<vector<string>> table, string name)
    {
        cout << "\n---------------------------------" << endl;
        cout << " " << name << endl;
        cout << "---------------------------------\n"
             << endl;
        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j < table[i].size(); j++)
                cout << " " << table[i][j] << "\t";
            if (table[i].size() != 0)
                cout << endl;
        }
        cout << endl;
    }

    void genINTCODE()
    {
        for (int i = 0; i < CODE.size(); i++)
        {
            vector<string> temp;
            for (int j = 0; j < CODE[i].size(); j++)
            {
                string result = "";
                if (isMnemonic(CODE[i][j]) && getClass(CODE[i][j]) != "CC")
                {
                    if (getClass(CODE[i][j]) == "RG")
                        result = "(" + to_string(stoi(getOpCODE(CODE[i][j]))) + ")";
                    else
                        result = "(" + getClass(CODE[i][j]) + ", " + getOpCODE(CODE[i][j]) + ")";

                    if (CODE[i][j] == "ORIGIN")
                    {
                        temp.push_back(result);
                        break;
                    }
                }
                else if (isConstant(CODE[i][j]))
                {
                    if (stoi(CODE[i][j]) < 10)
                        result = "(C, 0" + to_string(stoi(CODE[i][j])) + ")";
                    else
                        result = "(C, " + CODE[i][j] + ")";
                }
                else if (isLiteral(CODE[i][j]))
                {
                    if (getIndex(CODE[i][j], LITTAB) == -1)
                        LITTAB.push_back({CODE[i][j]});

                    if (j != 0)
                        if (getIndex(CODE[i][j], LITTAB) + 1 < 10)
                            result = "(L, 0" + to_string(getIndex(CODE[i][j], LITTAB) + 1) + ")";
                        else
                            result = "(L, " + to_string(getIndex(CODE[i][j], LITTAB) + 1) + ")";
                }
                else if (isSymbol(CODE[i][j]))
                {
                    if (getIndex(CODE[i][j], SYMTAB) == -1)
                        SYMTAB.push_back({CODE[i][j]});

                    if (j != 0)
                        if (getIndex(CODE[i][j], SYMTAB) + 1 < 10)
                            result = "(S, 0" + to_string(getIndex(CODE[i][j], SYMTAB) + 1) + ")";
                        else
                            result = "(S, " + to_string(getIndex(CODE[i][j], SYMTAB) + 1) + ")";
                }

                if (result != "")
                    temp.push_back(result);
            }
            if (temp.size() == 2)
            {
                string tmp = temp[1];
                temp.erase(temp.begin() + 1);
                temp.push_back(" ");
                temp.push_back(tmp);
            }
            INTCODE.push_back(temp);
        }
    }
    void genAddrTAB()
    {
        LC = stoi(CODE[0][1]) - 1;
        for (int i = 0; i < CODE.size(); i++)
        {
            if (CODE[i].size() > 0)
            {
                int k = 0;

                for (int j = 0; j < CODE[i].size(); j++)

                    if (isLiteral(CODE[i][j]))
                        LT[1]++;

                if (isSymbol(CODE[i][0]))
                    k = 1;

                if (CODE[i][k] == "EQU")
                {
                    LC++;
                    SYMTAB[getIndex(CODE[i][0], SYMTAB)].push_back(to_string(LC));
                }
                else if (getClass(CODE[i][k]) != "AD")
                {
                    LC++;
                    if (isSymbol(CODE[i][0]))
                    {
                        SYMTAB[getIndex(CODE[i][0], SYMTAB)].push_back(to_string(LC));
                    }
                }
                else if (CODE[i][k] == "LTORG" || CODE[i][k] == "END")
                {
                    bool pflag = false;
                    vector<string> temp;
                    for (int m = LT[0]; m < LT[1]; m++)
                    {
                        LC++;
                        LITTAB[m].push_back(to_string(LC));
                        if (!pflag)
                        {
                            temp.push_back(to_string(LT[0] + 1));
                            POOLTAB.push_back(temp);
                            pflag = true;
                        }
                    }
                    LT[0] = LT[1];
                }
                else
                {
                    if (CODE[i][k] == "ORIGIN")
                    {
                        if (CODE[i].size() == 2)
                        {
                            if (isSymbol(CODE[i][k + 1]))
                                LC = stoi(SYMTAB[getIndex(CODE[i][k + 1], SYMTAB)][1]) - 1;
                            else
                                LC++;
                        }
                        else
                        {
                            switch (CODE[i][k + 2][0])
                            {
                            case '+':
                                LC = (stoi(SYMTAB[getIndex(CODE[i][k + 1], SYMTAB)][1]) + stoi(CODE[i][k + 3])) - 1;
                                break;
                            case '-':
                                LC = (stoi(SYMTAB[getIndex(CODE[i][k + 1], SYMTAB)][1]) - stoi(CODE[i][k + 3])) - 1;
                                break;
                            case '*':
                                LC = (stoi(SYMTAB[getIndex(CODE[i][k + 1], SYMTAB)][1]) * stoi(CODE[i][k + 3])) - 1;
                                break;
                            case '/':
                                LC = (stoi(SYMTAB[getIndex(CODE[i][k + 1], SYMTAB)][1]) / stoi(CODE[i][k + 3])) - 1;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }
                CODE[i].push_back(to_string(LC));
            }
        }
    }
};

class Assembler : public Tables
{
public:
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
                else if (data[i] == '+')
                    line += " + ";
                else if (data[i] == '-')
                    line += " - ";
                else if (data[i] == '*')
                    line += " * ";
                else if (data[i] == '/')
                    line += " / ";
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
};

int main(int argc, char **argv)
{

    Assembler assm;
    assm.toVector("input.asm");
    assm.genTAB();
    assm.genINTCODE();
    assm.genAddrTAB();
    assm.showTAB(assm.INTCODE, "Intermediate Code (IC)");
    assm.showTAB(assm.SYMTAB, "Symbol Table (ST)");
    assm.showTAB(assm.LITTAB, "Literal Table (LT)");
    assm.showTAB(assm.POOLTAB, "Pool Table (PT)");
    return 0;
}