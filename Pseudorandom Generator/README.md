# Pseudorandom Generator

## 线性同余算法

- 迭代式：Xi+1 = aXi + c mod m
- 特征：一次产生一个伪随机数；不具备可证明安全性
- 思路：设定基础种子后，通过lcg_rand()更新迭代后的值

```c
#include <stdio.h>
//设定种子
void lcg_srand(unsigned int seed) {
    _seed=seed;
}
//线性同余算法
unsigned int lcg_rand(){
    _seed=(_a * _seed + _c) % _m;
    return _seed;
}
```

## BBS伪随机数生成器

- 参数选择：p和q为素数，且p mod 4 = q mod 4 = 3
- 迭代式：Xi+1 = Xi^2^ mod N
- 特征：一次产生一个伪随机比特；安全性可规约到大数难分解困难问题
- 思路：迭代后通过flag选择最重要比特位
- 最低位思路：与1求AND，获取最后一位比特值

```c
//迭代32轮，选择重要比特位后保存在bit_stream中
for(int i=0;i<32;++i){
    _bbs_seed = (_bbs_seed * _bbs_seed) % _n;
    switch(flag){
        case 0:bit_stream += last_bit(_bbs_seed);break;
        case 1:bit_stream += last_bit(_bbs_seed >> 16);break;
        case 2:bit_stream += last_bit(_bbs_seed >> 8);break;
    }
}
//最后将二进制流转换成十进制数

// 与0x0001进行并运算获得最后一位的比特值
int last_bit(unsigned int x) {
return x & 0x0001;
}
//思路：通过统计数字二进制的“1”的个数返回相应值
int parity_even(unsigned int x) {
int count = 0;
while (x) { // 判断是否为“1”并计数
if (x & 0x1) { ++count;}
x >>= 1; // 移位进行下一位判断
}
return count % 2 == 0 ? 0 : 1; // 奇数则返回1
}
// 奇校验为偶校验的相反值
int parity_odd(unsigned int x) {
return 1 – parity_even(x);
}
```
