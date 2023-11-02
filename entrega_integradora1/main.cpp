#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Función para leer el contenido de un archivo en una cadena
string readFile(const string &filename)
{
    ifstream file(filename);
    string content, line;
    while (getline(file, line))
    {
        content += line;
    }
    file.close();
    return content;
}

// Función para determinar si una cadena contiene a otra
int contains(const string &str, const string &substr)
{
    int strLen = str.length();
    int substrLen = substr.length();
    for (int i = 0; i <= strLen - substrLen; i++)
    {
        bool found = true;
        for (int j = 0; j < substrLen; j++)
        {
            if (str[i + j] != substr[j])
            {
                found = false;
                break;
            }
        }
        if (found)
            return i + 1;
    }
    return -1;
}

// Función de algoritmo de manacher, que devuelve la posicion y el tamaño del palindromo mas largo
// Y recibe como parametro la cadena a analizar
pair<int, int> manacher(string s)
{
    string T;
    int n = s.size();
    for (int i = 0; i <= 2 * n; i++)
    {
        if (i % 2 == 0)
            T += "#";
        else
            T += s[i / 2];
    }
    vector<int> L(2 * n + 1, 0);
    L[1] = 1;
    int maxLong = 0;
    int maxCenter = 0;
    int C = 1;
    int Ri = 0;
    int Li = 0;
    for (Ri = 2; Ri < 2 * n; Ri++)
    {
        Li = C - (Ri - C);
        bool expand = false;
        if (Ri < C + L[C])
        {
            if (L[Li] < (C + L[C] - Ri))
            {
                L[Ri] = L[Li];
            }
            else if ((L[Li] == (C + L[C] - Ri)) && (C + L[C]) == 2 * n)
            {
                L[Ri] = L[Li];
            }
            else if ((L[Li] == (C + L[C] - Ri)) && (C + L[C]) < 2 * n)
            {
                L[Ri] = L[Li];
                expand = true;
            }
            else if ((L[Li] > (C + L[C] - Ri)) && (C + L[C]) < 2 * n)
            {
                L[Ri] = C + L[C] - Ri;
                expand = true;
            }
            else
            {
                L[Ri] = 0;
                expand = true;
            }
        }
        else
        {
            L[Ri] = 0;
            expand = true;
        }
        if (expand)
        {
            while (Ri + L[Ri] < 2 * n + 1 && Ri - L[Ri] > 0 && T[Ri - L[Ri] - 1] == T[Ri + L[Ri] + 1])
                L[Ri]++;
        }
        if (Ri + L[Ri] > C + L[C])
        {
            C = Ri;
        }
        if (L[Ri] > maxLong)
        {
            maxLong = L[Ri];
            maxCenter = Ri;
        }
    }
    int start = (maxCenter - maxLong) / 2;
    int m = maxLong;
    return make_pair(start, m);
}

int main()
{
    string transmission1 = readFile("transmission1.txt");
    string transmission2 = readFile("transmission2.txt");
    string mcode1 = readFile("mcode1.txt");
    string mcode2 = readFile("mcode2.txt");
    string mcode3 = readFile("mcode3.txt");

    cout << endl;
    int result1 = contains(transmission1, mcode1);
    cout << "mcode1.txt en transmission1.txt:" << endl;
    cout << (result1 != -1 ? "true" : "false") << " en pos. " << result1 << endl;

    cout << endl;
    int result2 = contains(transmission1, mcode2);
    cout << "mcode2.txt en transmission1.txt:" << endl;
    cout << (result2 != -1 ? "true" : "false") << " en pos. " << result2 << endl;

    cout << endl;
    int result3 = contains(transmission1, mcode3);
    cout << "mcode3.txt en transmission1.txt:" << endl;
    cout << (result3 != -1 ? "true" : "false") << " en pos. " << result3 << endl;

    cout << endl;
    int result4 = contains(transmission2, mcode1);
    cout << "mcode1.txt en transmission2.txt:" << endl;
    cout << (result4 != -1 ? "true" : "false") << " en pos. " << result4 << endl;

    cout << endl;
    int result5 = contains(transmission2, mcode2);
    cout << "mcode2.txt en transmission2.txt:" << endl;
    cout << (result5 != -1 ? "true" : "false") << " en pos. " << result5 << endl;

    cout << endl;
    int result6 = contains(transmission2, mcode3);
    cout << "mcode3.txt en transmission2.txt:" << endl;
    cout << (result6 != -1 ? "true" : "false") << " en pos. " << result6 << endl;

    cout << endl;
    pair<int, int> p = manacher(transmission1);
    int start = p.first;
    int m = p.second;
    cout << "El palindromo mas largo en transmission1 empieza en: " << start << " y tiene longitud: " << m << endl;
    cout << endl;
    pair<int, int> p2 = manacher(transmission2);
    int start2 = p2.first;
    int m2 = p2.second;
    cout << "El palindromo mas largo en transmission2 empieza en: " << start2 << " y tiene longitud: " << m2 << endl;

    return 0;
}
