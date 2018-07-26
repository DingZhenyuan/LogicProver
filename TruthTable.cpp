#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <stack>
#include <map>
using namespace std;
string epr, epr1, epr2;
string pdnf, pcnf; //pdnf��ȡ, pcnf��ȡ
map <char, bool> mp; //��ϣ��
stack <char> st;    //���ڵõ���׺���ʽ
stack <int> dst;    //���ڼ�����ʽ����ֵ
int val[26];
int res, num;

bool CanIn(char fir, char sec) //�ܷ���ջ
{
    int i, o;
    switch(fir)    //����ջ�ڣ�ջ��Ԫ�����ȼ�
    {  
        case '#': i = 0; break;  
        case '(': i = 1; break;  
        case '~': i = 3; break;  
        case '>': i = 5; break;  
        case '|': i = 7; break;  
        case '&': i = 9; break;  
        case '!': i = 11; break;  
        case ')': i = 12; break;  
    }  
    switch(sec)  
    {  
        case '#': o = 0; break;  
        case '(': o = 12; break;  
        case '~': o = 2; break;  
        case '>': o = 4; break;  
        case '|': o = 6; break;  
        case '&': o = 8; break;  
        case '!': o = 10; break;  
        case ')': o = 1; break;  
    }  
    if(i < o)  
        return true;  
    else  
        return false;  
}

void to_suffix()      //��׺���ʽת��׺���ʽ
{
    while(st.size())    //���ջ
        st.pop();
    string tmp = "";    //�м�������������׺���ʽ
    st.push('#');       //'#'Ϊջ�ױ��
    int len = epr.length();
    for(int i = 0; i < len; i++)
    {
        if(mp[epr[i]])          //�����ǰ����ĸ����ֱ�Ӽӵ���׺���ʽ��
        {
            tmp = tmp + epr[i];
            continue;
        }
        if(CanIn(st.top(), epr[i])) //�õ�ǰ���ַ���ջ��Ԫ����ȣ���ջ��Ԫ�����ȼ�С��ջ�����ȼ�������ջ
            st.push(epr[i]);
        else if(epr[i] == ')')  //��������Ƕ��
        {
            while(st.top() != '(')
            {
                tmp = tmp + st.top();
                st.pop();
            }
            st.pop();
        }
        else        //���ջ��Ԫ�����ȼ�����ջ��Ԫ�����ȼ�����Ԫ�س�ջ��ֱ��ջ��Ԫ�����ȼ�С��ջ�����ȼ�
        {
            do
            {
                tmp = tmp + st.top();
                st.pop();
            }while(!CanIn(st.top(), epr[i]));
            st.push(epr[i]);
        }
    }
    while(st.top() != '#')   //��ʣ��Ԫ�س�ջ
    {  
        tmp = tmp + st.top();     
        st.pop();  
    }  
    st.pop();               
    epr = tmp;     //��ʱtmpΪ�õ��ĺ�׺���ʽ����ֵ��epr
    //cout << "epr = " << epr << endl;
}

void Or(int a, int b)     //������
{
    res = a + b;
    res = res > 1 ? 1 : res;
    dst.push(res);
}

void And(int a, int b)     //������
{
    res = a * b;
    dst.push(res);
}

void Not()          //������
{
    int a = dst.top();
    dst.pop();
    res = a == 1 ? 0 : 1;
    dst.push(res);
}   

void If(int a, int b)    //��������
{
    res = (b == 1 && a == 0) ? 0 : 1;
    dst.push(res);
}

void Iif(int a, int b)  //˫��������
{
    res = (a == b) ? 1 : 0;
    dst.push(res);
}

void cal()      //������ֵ
{
    while(dst.size())   //���ջdst
        dst.pop();
    int len = epr.length();
    int a, b;
    for(int i = 0; i < len; i++)  
    {
        if(mp[epr[i]])
        {
            for(int j = 0; j < 26; j++)
            {
                if(epr[i] == (j + 'A'))
                {
                    dst.push(val[j]);
                    break;
                }
            }
            continue;
        }  
        if(epr[i] != '!')
        {
            a = dst.top();
            dst.pop();
            b = dst.top();
            dst.pop();
        } 
        switch(epr[i])  
        {  
            case '|': 
                Or(a, b); 
                break;  
            case '&': 
                And(a, b); 
                break;  
            case '!': 
                Not(); 
                break;  
            case '~': 
                Iif(a, b); 
                break;  
            case '>': 
                If(a, b); 
                break;  
        }   
    }  
}

void Input1()  //����һ�����ʽ
{
    epr = "";
    printf("������������ֵ���ʽ: (! ��), (| ��ȡ), (& ��ȡ), (> ����), (~ ˫����)\n");
    cin >> epr; 
}

void preprea() //������ʽ
{
    num = 0;
    mp.clear();  //���map
    int len = epr.length();
    for(int i = 0; i < len; i++)
    {
        if(epr[i] >= 'A' && epr[i] <= 'Z')  
        {
            if(mp[epr[i]] == false)
            {
                mp[epr[i]] = true;  //��¼��Щ��ĸ�ڱ��ʽ��
                num ++;     //num��ʾ���ʽ���м�����ĸ
            }
        }
    }
}

void Input2()   //�����������ʽ
{
    epr = "";
    epr1 = "";
    epr2 = "";
    printf("������������ֵ���ʽ: (! ��), (| ��ȡ), (& ��ȡ), (> ����), (~ ˫����)\n");
    printf("�������һ��\n");
    cin >> epr1;
    printf("������ڶ���\n");
    cin >> epr2;
}

//idx����ĸ�ı�ţ�cnt��ʾ�Ѿ��������ĸ�ĸ�����p����Ƿ������ֵ��
void DFS(int idx, int cnt, int p)   //������������õ���ֵ�������ʽ
{
    if(cnt == num)
    {
        cal();
        if(res == 1)
        {
            pdnf += "(";
            int c = 0;
            for(int i = 0; i < 26; i++)
            {
                char t[1];
                t[0] = i + 'A';
                string ch(t);
                if(mp[ch[0]])
                {
                    c ++;
                    if(val[i] == 1)
                        pdnf += ch;
                    else
                        pdnf += "!" + ch; 
                    if(c != num)
                        pdnf += "&";
                }
            }
            pdnf += ")";
            pdnf += "|";
        }
        else
        {
            pcnf += "(";
            int c = 0; //��¼��ĸ����
            for(int i = 0; i < 26; i++)
            {
                char t[1];
                t[0] = i + 'A';
                string ch(t);
                if(mp[ch[0]]) //�ж���ĸ�Ƿ����
                {
                    c ++;
                    if(val[i] == 0)
                        pcnf += ch;
                    else
                        pcnf += "!" + ch; 
                    if(c != num)
                        pcnf += "|";
                }
            }
            pcnf += ")";
            pcnf += "&";
        }
        if(!p)
        {
            for(int i = 0; i < 26; i++)
                if(mp[i + 'A'])
                    printf("%d\t", val[i]);
            printf("%d\n", res);
        }
        return;
    }
    int idxx = 0;
    for(int i = idx; i < 26; i++)
    {
        if(mp[i + 'A'])
        {
            idxx = i;
            break;
        }
    }
    val[idxx] = 1;
    DFS(idxx + 1, cnt + 1, p);
    val[idxx] = 0;
    DFS(idxx + 1, cnt + 1, p);
    return;
}

void Print(bool p)  //�����ֵ�������ʽ, ��p==0���������ֵ��
{
    if(!p)
    {
        for(int i = 0; i < 26; i++)
            if(mp[i + 'A'])
                printf("%c\t", i + 'A');
        printf("res\n");
    }
    int idx = 0;  //idx������¼0 - 26�ֱ���A - Z��Ӧ
    for(int i = 0; i < 26; i++)
    {
        if(mp[i + 'A'])
        {
            idx = i;
            break;
        }
    }
    val[idx] = 1;
    DFS(idx + 1, 1, p);
    val[idx] = 0;
    DFS(idx + 1, 1, p);
}

void output_table()    //�����ֵ��ӿں���
{
    Input1();
    preprea();
    to_suffix();
    printf("��ֵ��Ϊ:\n");
    Print(0);
}

void output_pcnf()    //�������ȡ��ʽ�ӿں���  
{
    Input1();
    preprea();
    to_suffix();
    pcnf = ""; //��ʼ��
    Print(1);  
    int len = pcnf.length();
    if(len == 0)
        printf("����ʽ\n");
    else
    {
        pcnf.erase(pcnf.length() - 1);  
        cout << "����ȡ��ʽ��" << pcnf << endl << endl;  
    }
}

void output_pdnf()  //�������ȡ��ʽ�ӿں���  
{
    Input1();
    preprea();
    to_suffix();
    pdnf = "";
    Print(1);
    int len = pdnf.length();
    if(len == 0)
        printf("����ʽ\n");
    else
    {
        pdnf.erase(pdnf.length() - 1);  
        cout << "����ȡ��ʽ��" << pdnf << endl << endl;  
    }
}

//�ж��������ʽ�Ĺ�ϵ
//ԭ��: ����A������B���ȼ���(A<->B)����,������ʽ������ȡ��ʽ
//     ����A������B�������̺���ϵ(��A�̺�B)��(A->B)����,������ʽ������ȡ��ʽ
void judge_two()    
{
    bool flag1 = false, flag2 = false;
    Input2();
    epr = "(" + epr1 + ")" + "~" + "(" + epr2 + ")";
    preprea();
    to_suffix();
    pcnf = "";
    Print(1);
    int len = pcnf.length();
    if(len == 0)
    {
        flag1 = true;
        printf("\n�����⹫ʽ�ȼ�\n");
    }
    if(!flag1)
    {
        epr = "(" + epr1 + ")" + ">" + "(" + epr2 + ")";
        preprea();
        to_suffix();
        pcnf = "";
        Print(1);
        len = pcnf.length();
        if(len == 0)
        {
            flag2 = true;
            cout << endl << epr1 << endl;
            printf("�̺�\n");
            cout << epr2 << endl;
        }

        epr = "(" + epr2 + ")" + ">" + "(" + epr1 + ")";
        preprea();
        to_suffix();
        pcnf = "";
        Print(1);
        len = pcnf.length();
        if(len == 0)
        {
            flag2 = true;
            cout << endl << epr2 << endl;
            printf("�̺�\n");
            cout << epr1 << endl;
        }
    }
    if(!flag1 && !flag2)
        printf("�����⹫ʽ�Ȳ��ȼ��ֲ������̺���ϵ\n");
}

void solve() //����߼�����
{
    printf("��������:\n");
    printf("һ�Է��޴������ǵ�һ��������·������һ������.\n");
    printf("�����ʺ���:\"�����к�����Ů��?\"����û���庢�ӵĻش�.\n");
    printf("���Ӹ�ĸ��ĳһ��˵,�Һ��ӻش����\"�����к�\",��һ������˵:\"�⺢������,����Ů��.\"\n");
    printf("����������ԴӲ�˵��,��Ů�Դ���������˵�����滰,Ҳ������˵����ٻ�.\n");
    printf("������С���Ա�,�Լ�˭���丸��,˭����ĸ�ף�\n\n");
    printf("�������, ��:\n\n");
    printf("P��ʾ����:��һ��˵�����Ǹ���\n");
    printf("Q��ʾ����:��һ����˵�Ļ�Ϊ��\n");
    printf("R��ʾ����:�ڶ�����˵�ĵ�һ��Ϊ��\n");
    printf("S��ʾ����:�ڶ�����˵�ĵڶ���Ϊ��\n");
    printf("������֪ì����Ϣ,���ǿ��Եõ����¼���ì�����\n");
    printf("1. P&!Q        (����һ��˵�����Ǹ���,����˵��)\n");
    printf("2. P&Q         (����һ��˵�����Ǹ���,����û˵��,��ʱ��ĸ�����仰����򶼼�\n");
    printf("                ������֪ì��,��һ��һ��,����븸����˵��ì��)\n");
    printf("3. !P&(!(R&S)) (���ڶ���˵�����Ǹ���,�������мٻ�)\n");
    printf("4. !P&Q        (����һ��˵������ĸ��,��ĸ��˵�������,����Ϊ���ײ�˵�ٻ�)\n");
    printf("                ,��˸��׵Ļ�Ϊ����ĸ�׵Ļ�ì��\n");
    printf("�õ�ì�ܵ��������,�����ǻ���һ��õ����ʽ:\n");
    printf("(P&!Q)|(P&Q)|(!P&(!(R&S)))|(!P&Q)\n");
    printf("���ñ��ʽ����ֵ��:\n");
    epr = "(P&!Q)|(P&Q)|(!P&(!(R&S)))|(!P&Q)";
    preprea();
    to_suffix();
    Print(0);
    printf("\n����ֵ����Կ���ֻ��0 0 1 1��ʱ��û��ì��\n");
    printf("��ĸ����˵��˵��,���׺�˵û˵��,���ǿɵõ���:\n\n");
    printf("��һ��˵������ĸ��\n");
    printf("�ڶ���˵�����Ǹ���\n");
    printf("������Ů��\n");
}

void Menu() //�˵�
{
    printf("\n����ʹ��\n");
    printf("��ѡ�����:\n");
    printf("1 - �����ֵ��\n");
    printf("2 - �������ȡ��ʽ\n");
    printf("3 - �������ȡ��ʽ\n");
    printf("4 - �Ƚ������⹫ʽ�Ƿ�ȼۻ��̺�\n");
    printf("5 - �����Ŀ�е��߼�����\n");
    printf("6 - �˳�\n");
}

int main()
{
    Menu();
    while(true)
    {
        char tp[2]; //ѡ�����
        scanf("%s", tp);
        if(tp[0] > '6' || tp[0] < '1')
        {
            printf("��������\n");
            continue;
        }
        if(tp[0] == '1')
            output_table();
        else if(tp[0] == '2')
            output_pcnf();
        else if(tp[0] == '3')
            output_pdnf();
        else if(tp[0] == '4')
            judge_two();
        else if(tp[0] == '5')
            solve();
        else if(tp[0] == '6')
        {
            printf("ллʹ��\n");
            break;
        }   
        Menu();
    }
}
