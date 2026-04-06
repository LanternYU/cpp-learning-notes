# 🛠️ Modern C++ Exploration & Engineering Repository

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-11%2F14%2F17%2F20-blue.svg)](https://en.cppreference.com/)
[![Build System](https://img.shields.io/badge/Build-CMake-green.svg)](https://cmake.org/)
[![Status](https://img.shields.io/badge/Status-Actively%20Updating-orange.svg)](https://github.com/)


> **"Talk is cheap, I'm showing you codes and notes"**
> 
> 本仓库是我在本科/研究生阶段深度进阶 **现代 C++ (Modern C++)** 的工程实践笔记的整理，包括语法记录和代码用例，由于学习时间跨度较大，记录笔记/测试代码所用的软件前后不统一，部分内容有缺失，正在寻找/重写。

---

## 🏗️ 核心模块 

仓库采用模块化架构，每个专题均包含 **底层模拟实现** 与 **单元测试**。

### 1. 面向对象程序设计 (OOP)
* **构造与析构深度**： 处理虚析构函数以防止内存泄漏，探索构造函数中的异常安全保障。
* **深拷贝与移动**： 严格遵循 Rule of Five，实现具备深拷贝逻辑与移动语义的类。
* **接口与抽象**： 利用纯虚函数实现接口类，探索 C++ 中的多继承问题及 虚继承 解决菱形继承的机制。
  
### 2. 内存管理与资源安全 
* **RAII 深度实践：** 模拟实现 `Shared_ptr` 与 `Unique_ptr`，理解引用计数原理与异常安全性。
* **对象池 ：** 针对高性能场景实现轻量级对象池，减少 `new/delete` 带来的内存碎片。

### 3. STL 核心解构
* **容器模拟：** 深度剖析并复刻 `std::vector` 的动态扩容、迭代器失效处理及强异常安全保证。
* **空间配置器 ：** 研究 STL 如何通过一级/二级配置器管理细小内存块以提升效率。
* **类型擦除：** 剖析 `std::function` 与 Lambda 闭包的底层实现机制。

### 4. 并发编程
* **线程池 ：** 基于 `std::condition_variable` 实现的高效任务调度池。
* **同步原语：** 对比 `mutex`、`lock_guard` 与 `atomic` 在多线程环境下的性能表现。
* **异步模型：** 实践 `std::future` / `std::promise` 异步任务交互。

---

## 📈 学习与更新日志 (Lab Logs)

---
