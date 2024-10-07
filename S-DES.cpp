#include <iostream>
#include <cstring>
using namespace std;

// ������S1��S2�����������㷨�е�S�в���
int S1[4][4][2] = { {{0,1}, {0, 0}, {1, 1}, {1, 0}},
                   {{1, 1}, {1, 0}, {0, 1}, {0, 0}},
                   {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
                   {{1, 1}, {0, 1}, {0, 0}, {1, 0}} };
int S2[4][4][2] = { {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
                   {{1, 0}, {0, 0}, {0, 1}, {1, 1}},
                   {{1, 1}, {1, 0}, {0, 1}, {0, 0}},
                   {{1, 0}, {0, 1}, {0, 0}, {1, 1}} };

// ������Կ����������һ������Ϊ11����Կk�������������Ϊ9����Կk1��k2
void createkey(int k[11], int k1[9], int k2[9]) {
    int temp[11];
    // ��k�����Ԫ���������в����Ƶ�temp����
    temp[1] = k[3];
    temp[2] = k[5];
    temp[3] = k[2];
    temp[4] = k[7];
    temp[5] = k[4];
    temp[6] = k[10];
    temp[7] = k[1];
    temp[8] = k[9];
    temp[9] = k[8];
    temp[10] = k[6];
    // ��temp���鸴�Ƶ�k1��k2������
    for (int i = 1; i <= 5; i++) {
        k1[i] = temp[i];
        k2[i] = temp[i + 5];
    }
}

// ִ�������㷨����������һ������Ϊ9����������R��һ������Ϊ9����Կ����K������޸ĺ����������R
void f(int R[], int K[]) {
    int temp[9];
    // ��R�����Ԫ����K�����Ԫ�ؽ���������㲢���Ƶ�temp����
    temp[1] = R[4];
    temp[2] = R[1];
    temp[3] = R[2];
    temp[4] = R[3];
    temp[5] = R[2];
    temp[6] = R[3];
    temp[7] = R[4];
    temp[8] = R[1];
    for (int i = 1; i <= 8; i++) {
        temp[i] = temp[i] ^ K[i];
    }
    // ʹ��S�в�����temp�����Ԫ�ؽ���ת��
    int s1[5], s2[5];
    for (int i = 1; i <= 4; i++) {
        s1[i] = temp[i];
        s2[i] = temp[i + 4];
    }
    int x1, x2, x3, x4;
    x1 = S1[s1[1] * 2 + s1[4] % 4][s1[2] * 2 + s1[3] % 4][0];
    x2 = S1[s1[1] * 2 + s1[4] % 4][s1[2] * 2 + s1[3] % 4][1];
    x3 = S2[s2[1] * 2 + s2[4] % 4][s2[2] * 2 + s2[3] % 4][0];
    x4 = S2[s2[1] * 2 + s2[4] % 4][s2[2] * 2 + s2[3] % 4][1];
    R[1] = x2;
    R[2] = x4;
    R[3] = x3;
    R[4] = x1;
}

// ���ܺ���������һ������Ϊ9����������R����������Ϊ9����Կ����k1��k2��������ܺ����������R
void encode(int x, int k1[], int k2[]) {
    int ming[9];
    // ��������ַ�ת��Ϊ��Ӧ�Ķ���������ming
    for (int i = 8; i >= 1; i--) {
        ming[i] = x % 2;
        x /= 2;
    }
    int temp[9];
    // ��ming�����Ԫ�ؽ����������в����Ƶ�temp����
    temp[1] = ming[2];
    temp[2] = ming[6];
    temp[3] = ming[3];
    temp[4] = ming[1];
    temp[5] = ming[4];
    temp[6] = ming[8];
    temp[7] = ming[5];
    temp[8] = ming[7];
    // ��temp���鸴�Ƶ�L0��R0�����У�Ȼ��ִ�������㷨
    int L0[5], R0[5], L1[5], R1[5], L2[5], R2[5];
    for (int i = 1; i <= 4; i++) {
        L0[i] = temp[i];
        R0[i] = temp[i + 4];
    }
    memcpy(L1, R0, sizeof(L1));
    f(R0, k1);
    for (int i = 1; i <= 4; i++) {
        R1[i] = L0[i] ^ R0[i];
    }
    memcpy(R2, R1, sizeof(R2));
    f(R1, k2);
    for (int i = 1; i <= 4; i++) {
        L2[i] = L1[i] ^ R1[i];
    }
    temp[1] = L2[4];
    temp[2] = L2[1];
    temp[3] = L2[3];
    temp[4] = R2[1];
    temp[5] = R2[3];
    temp[6] = L2[2];
    temp[7] = R2[4];
    temp[8] = R2[2];
    // ������ܺ�Ķ����ƺͶ�Ӧ���ַ�
    cout << "���ܺ������Ϊ:";
    int ans = 0;
    for (int i = 1; i <= 8; i++) {
        ans += temp[i] * (1 << (8 - i));
        cout << temp[i];
    }
    cout << "\n";
    cout << "���ܺ��Ӧ��ĸΪ:" << (char)ans << "\n";
}

// ���ܺ���������һ������Ϊ9����������R����������Ϊ9����Կ����k1��k2��������ܺ����������R
void decode(int x, int k1[], int k2[]) {
    int ming[9];
    // ��������ַ�ת��Ϊ��Ӧ�Ķ���������ming
    for (int i = 8; i >= 1; i--) {
        ming[i] = x % 2;
        x /= 2;
    }
    int temp[9];
    // ��ming�����Ԫ�ؽ����������в����Ƶ�temp����
    temp[1] = ming[2];
    temp[2] = ming[6];
    temp[3] = ming[3];
    temp[4] = ming[1];
    temp[5] = ming[4];
    temp[6] = ming[8];
    temp[7] = ming[5];
    temp[8] = ming[7];
    // ��temp���鸴�Ƶ�L2��R2�����У�Ȼ��ִ�н����㷨
    int L2[5], R2[5], L1[5], R1[5], L0[5], R0[5];
    for (int i = 1; i <= 4; i++) {
        L2[i] = temp[i];
        R2[i] = temp[i + 4];
    }
    memcpy(R1, R2, sizeof(R1));
    f(R2, k2);
    for (int i = 1; i <= 4; i++) {
        L1[i] = L2[i] ^ R2[i];
    }
    memcpy(R0, L1, sizeof(R0));
    f(L1, k1);
    for (int i = 1; i <= 4; i++) {
        L0[i] = R1[i] ^ L1[i];
    }
    temp[1] = L0[4];
    temp[2] = L0[1];
    temp[3] = L0[3];
    temp[4] = R0[1];
    temp[5] = R0[3];
    temp[6] = L0[2];
    temp[7] = R0[4];
    temp[8] = R0[2];
    // ������ܺ�Ķ����ƺͶ�Ӧ���ַ�
    cout << "���ܺ������Ϊ:";
    int ans = 0;
    for (int i = 1; i <= 8; i++) {
        ans += temp[i] * (1 << (8 - i));
        cout << temp[i];
    }
    cout << "\n";
    cout << "���ܺ��Ӧ��ĸΪ:" << (char)ans << "\n";
}
//�����ƽ�
void bruteForce() {
    int k[11];
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int k = 0; k < 256; k++) {
                k[1] = i;
                k[2] = j;
                k[3] = k;
                k[4] = k;
                k[5] = k;
                k[6] = k;
                k[7] = k;
                k[8] = k;
                k[9] = k;
                k[10] = k;
                createkey(k, k1, k2);
                // ����������һ�������ַ��� "hello" �ͼ��ܺ���ַ��� "encrypted"
                char decrypted[10];
                decode("encrypted", k1, k2);
                if (strcmp(decrypted, "hello") == 0) {
                    cout << "�ҵ���ȷ����Կ: " << k[1] << ", " << k[2] << ", " << k[3] << ", " << k[4] << ", " << k[5] << ", " << k[6] << ", " << k[7] << ", " << k[8] << ", " << k[9] << ", " << k[10] << endl;
                    return;
                }
            }
        }
    }
    cout << "û���ҵ���ȷ����Կ" << endl;
}
// ������������������Կ�Ͳ��Լ��ܡ����ܹ���
int main() {
    int k[11], k1[9], k2[9];
    // ��������Կk
    int choice;
    cout << "��ѡ�����:" << endl;
    cout << "0. ������8-bit���ּӽ���" << endl;
    cout << "1. �����ƽ�" << endl;

    cout << "������ѡ��: ";
    cin >> choice;
    switch (choice)
    {
    case 0:
        cout << "����������ԿK(��Կ��ÿһλ�ÿո����):";
        for (int i = 1; i <= 10; i++) {
            cin >> k[i];
        }
        // ����createkey��������k1��k2��Կ
        createkey(k, k1, k2);
        // ���������ַ�������
        char ming[2];
        cout << "����������:";
        cin >> ming;
        encode(ming[0], k1, k2);
        // ���������ַ�������
        cout << "����������:";
        char mi[2];
        cin >> mi;
        decode(mi[0], k1, k2);
    case 1:
        bruteForce();
        break;

    default:
        cout << "��Ч��ѡ��" << endl;

    }

    return 0;
}
