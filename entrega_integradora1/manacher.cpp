#include <iostream>
#include <vector>
using namespace std;

int main()
{
    string s = "abjksadhaaaaabbbbbaaaaaasdfghjkl";
    string T;
    int n = s.size();
    for (int i = 0; i <= 2 * n; i++)
    {
        if (i % 2 == 0)
            T += "#";
        else
            T += s[i/2];
    }
    cout << T << endl;
    vector<int> L(2*n + 1, 0);
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
            while (Ri + L[Ri] < 2*n + 1 && Ri - L[Ri] > 0 && T[Ri - L[Ri] - 1] == T[Ri + L[Ri] + 1])
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
    cout << "Palindromo mas largo: " << start << ", longitud: " << m << endl;
    return 0;
}
