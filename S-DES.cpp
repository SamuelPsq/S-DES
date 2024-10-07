#include <iostream>
#include <cstring>
using namespace std;

// 定义阵S1和S2，用于密码算法中的S盒操作
int S1[4][4][2] = { {{0,1}, {0, 0}, {1, 1}, {1, 0}},
                   {{1, 1}, {1, 0}, {0, 1}, {0, 0}},
                   {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
                   {{1, 1}, {0, 1}, {0, 0}, {1, 0}} };
int S2[4][4][2] = { {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
                   {{1, 0}, {0, 0}, {0, 1}, {1, 1}},
                   {{1, 1}, {1, 0}, {0, 1}, {0, 0}},
                   {{1, 0}, {0, 1}, {0, 0}, {1, 1}} };

// 生成密钥函数，输入一个长度为11的密钥k，输出两个长度为9的密钥k1和k2
void createkey(int k[11], int k1[9], int k2[9]) {
    int temp[11];
    // 将k数组的元素重新排列并复制到temp数组
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
    // 将temp数组复制到k1和k2数组中
    for (int i = 1; i <= 5; i++) {
        k1[i] = temp[i];
        k2[i] = temp[i + 5];
    }
}

// 执行密码算法函数，输入一个长度为9的明文数组R和一个长度为9的密钥数组K，输出修改后的明文数组R
void f(int R[], int K[]) {
    int temp[9];
    // 将R数组的元素与K数组的元素进行异或运算并复制到temp数组
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
    // 使用S盒操作对temp数组的元素进行转换
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

// 加密函数，输入一个长度为9的明文数组R和两个长度为9的密钥数组k1和k2，输出加密后的明文数组R
void encode(int x, int k1[], int k2[]) {
    int ming[9];
    // 将输入的字符转换为对应的二进制数组ming
    for (int i = 8; i >= 1; i--) {
        ming[i] = x % 2;
        x /= 2;
    }
    int temp[9];
    // 将ming数组的元素进行重新排列并复制到temp数组
    temp[1] = ming[2];
    temp[2] = ming[6];
    temp[3] = ming[3];
    temp[4] = ming[1];
    temp[5] = ming[4];
    temp[6] = ming[8];
    temp[7] = ming[5];
    temp[8] = ming[7];
    // 将temp数组复制到L0和R0数组中，然后执行密码算法
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
    // 输出加密后的二进制和对应的字符
    cout << "加密后二进制为:";
    int ans = 0;
    for (int i = 1; i <= 8; i++) {
        ans += temp[i] * (1 << (8 - i));
        cout << temp[i];
    }
    cout << "\n";
    cout << "加密后对应字母为:" << (char)ans << "\n";
}

// 解密函数，输入一个长度为9的密文数组R和两个长度为9的密钥数组k1和k2，输出解密后的明文数组R
void decode(int x, int k1[], int k2[]) {
    int ming[9];
    // 将输入的字符转换为对应的二进制数组ming
    for (int i = 8; i >= 1; i--) {
        ming[i] = x % 2;
        x /= 2;
    }
    int temp[9];
    // 将ming数组的元素进行重新排列并复制到temp数组
    temp[1] = ming[2];
    temp[2] = ming[6];
    temp[3] = ming[3];
    temp[4] = ming[1];
    temp[5] = ming[4];
    temp[6] = ming[8];
    temp[7] = ming[5];
    temp[8] = ming[7];
    // 将temp数组复制到L2和R2数组中，然后执行解密算法
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
    // 输出解密后的二进制和对应的字符
    cout << "解密后二进制为:";
    int ans = 0;
    for (int i = 1; i <= 8; i++) {
        ans += temp[i] * (1 << (8 - i));
        cout << temp[i];
    }
    cout << "\n";
    cout << "解密后对应字母为:" << (char)ans << "\n";
}
//暴力破解
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
                // 假设我们有一个明文字符串 "hello" 和加密后的字符串 "encrypted"
                char decrypted[10];
                decode("encrypted", k1, k2);
                if (strcmp(decrypted, "hello") == 0) {
                    cout << "找到正确的密钥: " << k[1] << ", " << k[2] << ", " << k[3] << ", " << k[4] << ", " << k[5] << ", " << k[6] << ", " << k[7] << ", " << k[8] << ", " << k[9] << ", " << k[10] << endl;
                    return;
                }
            }
        }
    }
    cout << "没有找到正确的密钥" << endl;
}
// 主函数，用于输入密钥和测试加密、解密功能
int main() {
    int k[11], k1[9], k2[9];
    // 输入主密钥k
    int choice;
    cout << "请选择操作:" << endl;
    cout << "0. 基础的8-bit数字加解密" << endl;
    cout << "1. 暴力破解" << endl;

    cout << "请输入选择: ";
    cin >> choice;
    switch (choice)
    {
    case 0:
        cout << "请输入主密钥K(密钥的每一位用空格隔开):";
        for (int i = 1; i <= 10; i++) {
            cin >> k[i];
        }
        // 调用createkey函数生成k1和k2密钥
        createkey(k, k1, k2);
        // 输入明文字符并加密
        char ming[2];
        cout << "请输入明文:";
        cin >> ming;
        encode(ming[0], k1, k2);
        // 输入密文字符并解密
        cout << "请输入密文:";
        char mi[2];
        cin >> mi;
        decode(mi[0], k1, k2);
    case 1:
        bruteForce();
        break;

    default:
        cout << "无效的选择" << endl;

    }

    return 0;
}
