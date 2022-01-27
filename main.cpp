#include <iostream>
#include <string>

using namespace std;

#define N 1000

void extended_euclid (long a, long b, long *d, long *x, long *y)
{
    int s;

    if (b == 0){
        *d = a; *x = 1; *y = 0;
        return;
    }

    extended_euclid(b,a % b,d,x,y);

    s = *y;

    *y = *x - (a / b) * (*y);

    *x = s;

}
void calculate_C(long a, long b, long *C)
{
    *C = (a+b)/2;
}
void calculate_r(long a, long b, long P, int C, long *U, long *V, long *r)
{
    for(int i = 1; i < N;i++){
        U[i] = U[i-1];
        V[i] = V[i-1];
        if(r[i-1] <= C) {
            r[i] = r[i-1] * b % P;
            V[i]++;
        }
        else {
            r[i] = r[i-1] * a % P;
            U[i]++;
        }
    }
}
int calculate_X(long *U, long *V, long P_1, int i, int j, long *x, long *y, long *d)
{
    int X, a, b;

    a = (U[j] - U[i]) % P_1;
    b = (V[i] - V[j]) % P_1;
    if(b < 0)
        b+=P_1;
    extended_euclid(b, P_1, d, x, y);
    if(*d != 1){
        cout << "Обратного элемента не существует" << endl;
        return 0;
    }
    if(*x < 0)
        *x+=P_1;
    X = (a * (*x)) % P_1;
    return X;
}
void findIndex(long *r, int *i, int *j)
{
    for(*i = 0; *i < N; (*i)++){
        for(*j = *i + 1; *j < N; (*j)++){
            if(r[*i] == r[*j]) {
                return;
            }
        }
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");

    long d, x, X, y, a, b, P, P_1, C; int i = 0, j = 0;
    long U[N], V[N], r[N];
    bool flag, onlyDigit;
    string strA, strB, strP, strAll;
    char in;

    while(true){
        cout << "1 - Вычислить дискретный логарифм" << endl;
        cout << "2 - Выйти\nВвод: ";

        cin >> in;

        switch (in) {
            case '1':
                flag = true;
                while (flag){
                    onlyDigit = true;
                    cout << "Введите значения согласно примеру(a^x = b (mod P)), P - простое число: " << endl;
                    cout << "a = ";
                    cin >> strA;
                    cout << "b = ";
                    cin >> strB;
                    cout << "P = ";
                    cin >> strP;
                    strAll = strA + strB + strP;
                    for(int k = 0; k < strAll.length(); k++){
                        if(!isdigit(strAll[k])){
                            cout << "Ошибка. Вы ввели букву" << endl;
                            onlyDigit = false;
                            break;
                        }
                    }
                    if(onlyDigit){
                        flag = false;
                        a = stol(strA);
                        b = stol(strB);
                        P = stol(strP);
                    }
                }


                P_1 = P - 1;
                r[0] = b; U[0] = 0; V[0] = 1;

                calculate_C(a, b, &C);

                calculate_r(a, b, P, C, U, V, r);

                findIndex(r, &i, &j);

                X = calculate_X(U, V, P_1, i, j, &x, &y, &d);

                if(X)
                    cout << "x = " << X << endl << endl;
                else
                    cout << "Ошибка. Проверьте правильность введенных данных и повторите попытку." << endl << endl;
                break;
            case '2':
                return 0;
            default:
                cout << "Выберите 1 или 2:" << endl;
                break;


        }

    }

}
