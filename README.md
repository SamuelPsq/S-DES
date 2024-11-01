S-DES的实现
==== 

  - [编程和测试要求](#编程和测试要求)
 - [开发手册](#开发手册)
   - [算法说明](#算法说明)
   - [接口说明](#接口说明)
  - [用户指南](#用户指南)

编程和测试要求
-------
### 重庆大学信息安全导论课程第二次作业，S-AES算法的实现
### 第1关：基本测试  
> 根据S-AES算法编写和调试程序，提供GUI解密支持用户交互。输入可以是16bit的数据和16bit的密钥，输出是16bit的密文。
### 第2关：交叉测试  
>考虑到是"算法标准"，所有人在编写程序的时候需要使用相同算法流程和转换单元(替换盒、列混淆矩阵等)，以保证算法和程序在异构的系统或平台上都可以正常运行。设有A和B两组位同学(选择相同的密钥K)；则A、B组同学编写的程序对明文P进行加密得到相同的密文C；或者B组同学接收到A组程序加密的密文C，使用B组程序进行解密可得到与A相同的P。
  ### 第3关：扩展功能  
 > 考虑到向实用性扩展，加密算法的数据输入可以是ASII编码字符串(分组为2 Bytes)，对应地输出也可以是ACII字符串(很可能是乱码)。
  ### 第4关：多重加密
  #### 双重加密
>  将S-AES算法通过双重加密进行扩展，分组长度仍然是16 bits，但密钥长度为32 bits。3.4.2 中间相遇攻击假设你找到了使用相同密钥的明、密文对(一个或多个)，请尝试使用中间相遇攻击的方法找到正确的密钥Key(K1+K2)。
   #### 三重加密
将S-AES算法通过三重加密进行扩展，下面两种模式选择一种完成：(1)按照32 bits密钥Key(K1+K2)的模式进行三重加密解密，(2)使用48bits(K1+K2+K3)的模式进行三重加解密。
### 第5关：工作模式
> 基于S-AES算法，使用密码分组链(CBC)模式对较长的明文消息进行加密。注意初始向量(16 bits) 的生成，并需要加解密双方共享。在CBC模式下进行加密，并尝试对密文分组进行替换或修改，然后进行解密，请对比篡改密文前后的解密结果。
开发手册
-------
### 算法说明
#### 实现了一个基于S盒替换和异或运算的密码算法，包括加密和解密功能。算法的主要步骤如下：
>1.  定义S盒操作：定义两个S盒（S1和S2），用于进行S盒替换操作。S盒替换是密码算法中的一个核心操作，用于将明文或密文转换为另一个明文或密文。
>2.  生成密钥：定义一个名为createkey的函数，输入一个长度为11的密钥数组k，输出两个长度为9的密钥数组k1和k2。这个函数的主要目的是将原始密钥k进行处理，得到两个新的密钥k1和k2，用于后续的加密和解密操作。
>3.  执行密码算法：定义一个名为f的函数，输入一个长度为9的明文数组R和一个长度为9的密钥数组K，输出修改后的明文数组R。这个函数的主要目的是使用S盒操作和异或运算对明文数组R进行处理，得到修改后的明文数组R。
>4.  加密函数：定义一个名为encode的函数，输入一个长度为9的明文数组R和两个长度为9的密钥数组k1和k2，输出加密后的明文数组R。这个函数的主要目的是使用生成密钥函数createkey生成的密钥k1和k2，以及执行密码算法函数f，对输入的明文数组R进行加密操作。
>5.  解密函数：定义一个名为decode的函数，输入一个长度为9的密文数组R和两个长度为9的密钥数组k1和k2，输出解密后的明文数组R。这个函数的主要目的是使用生成密钥函数createkey生成的密钥k1和k2，以及执行密码算法函数>f，对输入的密文数组R进行解密操作。
>6.  主函数：定义一个名为main的主函数，用于输入密钥和测试加密、解密功能。这个函数的主要目的是让用户输入主密钥k，调用createkey函数生成k1和k2密钥，然后分别对输入的明文和密文进行加密和解密操作，并输出结果。整个算法的核心是S盒替换和异或运算，通过这两个操作，可以将明文或密文转换为另一个明文或密文。在实际应用中，可以根据需要调整S盒的值以增加密码的安全性。
### 接口说明
#### 加密接口：encode
#### 功能：将明文转换为密文，并使用特定的加密算法进行加密。
>输入参数：
x：一个字符，表示明文字符。
k1：一个长度为9的整数数组，表示加密密钥k1。
k2：一个长度为9的整数数组，表示加密密钥k2。
输出：
加密后的字符和对应的二进制表示。


#### 解密接口：decode
#### 功能：将密文转换为明文，并使用特定的解密算法进行解密。
> 输入参数：
x：一个字符，表示密文字符。
k1：一个长度为9的整数数组，表示解密密钥k1。
k2：一个长度为9的整数数组，表示解密密钥k2。
输出：
解密后的字符和对应的二进制表示。
#### 密钥生成接口：createkey
#### 功能：生成用于加密和解密的两个密钥数组k1和k2。
>输入参数：
k：一个长度为11的整数数组，表示原始密钥。
输出：
两个长度为9的整数数组k1和k2。

#### 主函数接口：main
#### 功能：接收用户输入的明文或密文，并调用加密或解密接口进行处理。
>输入参数：

用户输入的明文或密文字符。
输出：
加密或解密后的结果，包括对应的二进制表示和字符。

用户指南
-------
### 用户指南：密码算法加密与解密工具
#### 一、概述
本工具提供了一种基于特定算法的加密和解密功能，用于处理字符信息。通过输入明文或密文，用户可以使用本工具进行加密或解密操作，实现信息的保护和安全传输。

#### 二、功能特性
加密功能：将明文转换为密文，使用特定的加密算法进行数据保护。
解密功能：将密文转换回明文，实现数据的还原和访问。
密钥生成：生成用于加密和解密的密钥，确保数据处理的安全性。
#### 三、使用步骤
>启动工具：运行程序或脚本，确保环境支持所需的编程语言和库。
#### 在主页面需要选择进行的操作，输入0进行基础的8-bit数字加解密，输入1则是进行暴力破解，需要在进行完case0之后才能有效
#### 基础的8-bit数字加解密的过程如下
##### 1.输入密钥：
>在程序运行时，根据提示输入一个长度为11的密钥数组k。密钥是加密和解密过程中不可或缺的部分，其安全性直接关系到数据的安全性。
##### 2.生成密钥：
>调用createkey函数，将输入的密钥数组k作为参数传递。此函数将生成两个用于后续加密和解密操作的密钥数组k1和k2。
##### 3.加密或解密：
>输入明文或密文字符，使用encode或decode函数进行操作。确保根据需要选择正确的函数。通过encode函数加密明文，通过decode函数解密密文。
##### 4.查看结果：
>程序将输出加密或解密后的二进制表示和对应的字符，便于用户确认数据处理的结果。
#### 暴力破解是自动的，直接在case选择时输入1即可
