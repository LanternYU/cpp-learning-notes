# 一.char和string 的学习笔记
## 1.输入输出
### 1.1 char[]的cin
cin 通过空白（空格 制表符和换行符）来确定字符串的结束位置 
比如：对 char[20] name  
当 cin>>name 当输入为ALEX WANG时
name中存储的值为 ALEX 并把WANG存储在输入队列中
### 1.2 cin.get()与cin.getline()
getline()读取一行 通过换行符来确定行尾 但不保存换行符
get()也读取一行 同样通过换行符来确定行尾 但并不读取并丢弃换行符
```cpp
cin.get(name,Arsize)
cin.get(dessert,Arsize)//这样第二行get并不会发挥作用

cin.get(name,Arsize)
cin.get()
cin.get(dessert,Arsize)//这样第二行get会发挥作用
```