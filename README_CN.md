<h1 align="center">ctp-pybind</h1>

<p align="center">
✨ 一键实现自动编译 CTP API C++ 和 Python 接口的绑定 ✨
</p>



<p align="center">
  简体中文 |
  <a href="README.md">English</a>
</p>

# 项目说明

根据原生CTP C++ API 自动化包装为 Python API，便于 CTP Python 开发者维护最新的 CTP 接口，实现 CTP 版本的快速升级。

**注意**：本项目仅在CTP v6.7.11版本下测试通过，其他版本未做测试，请自行测试，项目 CTP 版本号配置位于`ctp/__init__.py`文件。

## 1. 编译环境

本项目使用以下环境编译，若自行使用其它版本，请做相应调整。

- **Windows 11 + MSVC**(由Visual Studio 2022提供)
- **Python 3.13.6**，由 UV 安装。
- **CTP v6.7.11**：[CTP官方下载地址](https://www.simnow.com.cn/static/apiDownload.action)
- **Meson + Ninja**: 现代化的C++扩展构建系统。
- **Pybind11**: 用于在 C++ 和 Python 之间创建无缝的绑定（binding），使得 Python 能够轻松调用高性能的 C++ 代码。
- **UV**: 现代化Python包管理器，提供更快的安装速度和更智能的依赖解析。

## 2. 项目结构

```reStructuredText
/
├── 📂 ctp/ 								# CTP 接口相关
│   ├── 📂 api/ 							# CTP API模块
│   │   ├── 📂 generator/ 					# C++ 与 Python绑定过程文件
│   │   ├── 📂 include/ 					# 存放原生 CTP API C++ 头文件
│   │   ├── 📂 libs/ 						# 存放原生 CTP API 静态库文件
│   │   ├── 📂 src/ 						# 存放 C++ 和 Python 绑定过程文件
│   │   ├── 📁 ctp_constant.py 				# CTP API 常量，demo 中引用
│   │   ├── 📁 ctpmd.cp313-win_amd64.pyd	# C++ 编译为 Python 的行情扩展模块
│   │   ├── 📁 ctpmd.pyi 					# 行情扩展模块对应的存根文件
│   │   ├── 📁 ctptd.cp313-win_amd64.pyd	# C++ 编译为 Python 的交易扩展模块
│   │   ├── 📁 ctptd.pyi 					# 交易扩展模块对应的存根文件
│   │   ├── 📁 custom_constant.py 			# 用户自定义常量类，demo 中引用
│   │   ├── 📁 thostmduserapi_se.dll		# Windows CTP 行情 API 动态链接库
│   │   ├── 📁 thostmduserapi_se.so			# Linuxs CTP 行情 API 动态链接库
│   │   ├── 📁 thosttraderapi_se.dll		# Windows CTP 交易 API 动态链接库
│   │   └── 📁 thosttraderapi_se.so			# Linuxs CTP 交易 API 动态链接库
│   ├── 📁 __init__.py						# CTP版本配置文件
│   └── 📁 ctp.h							# 任务处理及编码转换
├── 📂 demo/								# 使用示例
│   ├── 📁 md_demo.py 						# 行情扩展模块使用示例
│   ├── 📁 td_demo.py 						# 交易扩展模块使用示例
│   └── 📁 util.py							# demo 公共函数
├── 📂 docs/								# 项目文档
├── 📂 script/								# 绑定生成脚本
├── 📁 .gitignore							# git提交忽略文件，由uv自动生成
├── 📁 .python-version						# 项目Python版本文件，由uv自动生成
├── 📁 LICENSE								# 项目License文件
├── 📁 README.md							# 项目英文说明文件
├── 📁 README_CN.md							# 项目中文说明文件
├── 📁 build.py								# 扩展模块自动化编译脚本，组装了 meson 命令
├── 📁 meson.build							# meson构建配置文件
├── 📁 pyproject.toml						# Python项目管理配置文件，由uv自动生成
└── 📁 uv.lock								# uv锁定文件，由uv自动生成
```

## 3. 安装基础环境

### 3.1 安装UV

#### 3.1.1 On Windows

**方式一：全局安装(推荐方式)**

```bash
powershell -ExecutionPolicy ByPass -c "irm https://astral.sh/uv/install.ps1 | iex"
```

**方式二：单独在 Python 环境中安装**

```bash
pip install uv
```

#### 3.1.2 On Linux

```bash
curl -LsSf https://astral.sh/uv/install.sh | sh
```

### 3.2 安装 Python

方式一进行这一步，你可以安装自己需要的版本

```bash
uv python install 3.13
```

## 4. 使用

### 4.1 方式一，命令安装

```bash
uv add ctp-pybind
# 或
pip install ctp-pybind
```

### 4.2 方式二，源码安装

下载本项目 Release 源码或者 `git clone`

#### 4.2.1 安装依赖

```bash
# 根目录下执行，将项目的依赖项与环境同步(同步Python版本及第三方依赖)
uv sync
```

#### 4.2.2 生成 CTP API 组装文件

```bash
.venv\Scripts\activate
cd script
# 一键生成所有CTP API组装文件
python generate_all.py
```
#### 4.2.3 生成 CTP API Python 绑定文件

```bash
# 项目根目录执行，生成绑定文件
python build.py
```

## 5. Demo测试

### 5.1 **行情扩展模块**

在 demo/ 下 `md_demo.py` 中填入 CTP 环境及 simonow 账户信息后运行，结果如下：

```reStructuredText
Start connecting to CTP market server...
CtpMdApi：Trying to create an API with path D:\Project\PycharmProjects\homalos-ctp\con/md
CtpMdApi：createFtdcMdApi call succeeded.
CtpMdApi：Try initializing the API using the address:tcp://182.254.243.31:40011...
CtpMdApi：init call succeeded.
Connecting to tcp://182.254.243.31:40011...
Waiting for connection and login to complete...
ctp md api callback: onFrontConnected - The market data server is connected successfully
Start the login process
CtpMdApi：reqUserLogin call succeeded.
ctp md api callback: onRspUserLogin - The market server login is successful
Starting to subscribe to 2 contracts...
Subscription contract: SA601
Prepare subscription contract: SA601
Send subscription request SA601
Subscription request sent SA601
ctp md api callback: onRspSubMarketData - Subscription feedback, Contract=SA601, ErrorID=0
symbol: SA601
ctp md api callback: onRtnDepthMarketData
CTP Market data reception: SA601 @ 17:00:34 LastPrice=1276.0
Subscription contract: FG601
Prepare subscription contract: FG601
Send subscription request FG601
Subscription request sent FG601
ctp md api callback: onRtnDepthMarketData
CTP Market data reception: SA601 @ 17:00:35 LastPrice=1276.0
...
```

### 5.2 **交易扩展模块**

在 demo/ 下 `td_demo.py` 中填入 CTP 环境及 simonow 账户信息后运行，结果如下：

```reStructuredText
CtpTdApi: Attempting to create an API with path D:\Project\PycharmProjects\homalos-ctp\con/td
CtpTdApi: createFtdcTraderApi call succeeded.
CtpTdApi：尝试使用地址初始化 API：tcp://182.254.243.31:30001...
CtpTdApi：init 调用成功。
Waiting for connection and login to complete...
ctp td api callback: onFrontConnected - Trading server connection successful
开始认证，auth_status: False
发送认证请求，req_id: 1
Transaction server authorization verification successful
开始登录，login_status: False
发送登录请求，req_id: 2
ctp td api callback: onRspUserLogin - Login Response, ErrorID=0
Trading server login successful
Settlement information confirmed successfully

🚀 开始下单测试...
正在委托下单...
symbol: SA601
direction: BUY_OPEN
price: 1286
volume: 1
委托请求发送成功
委托下单成功，委托号：1_-394894342_1
下单完成，订单号: 1_-394894342_1

⏰ 等待5秒观察订单状态...
ctp td api callback: onRtnOrder
订单状态更新 - 订单 ID：1_-394894342_1，状态：未知 (a)
状态变化: 新订单 -> 未知
ctp td api callback: onRtnOrder
订单状态更新 - 订单 ID：1_-394894342_1，状态：未知 (a)
状态变化: a -> 未知
ctp td api callback: onRtnOrder
订单状态更新 - 订单 ID：1_-394894342_1，状态：全部成交 (0)
订单全部成交 - 订单号: 1_-394894342_1, 合约: SA601
状态变化: a -> 全部成交
ctp td api callback: onRtnTrade
onRtnTrade trade_id: 2025090800029227, order_id:        48977, price: 1286.0, volume: 1, trade_date: 20250905, trade_time: 21:41:12

==================================================
📋 订单状态汇总
==================================================
订单号: 1_-394894342_1 | 状态: 全部成交
==================================================
...
```

## 6. 脚本功能说明

本节内容只面向对生成绑定过程感兴趣的研究者，如果只需要生成绑定文件，则无需阅读这些内容，generator脚本位于`script/` 目录下。

### 6.1 `generator_function_const.py`

- **作用**：**生成基础函数常量文件**
- **功能**：读取 CTP API C++ 的头文件 `ThostFtdcMdApi.h`、`ThostFtdcTraderApi.h` 代码，解析其中的函数，生成 `ctp_function_const.py`（函数常量定义）。

### 6.2 `generate_data_type.py`

- **作用**：**生成数据类型定义文件**
- **功能**：读取 CTP API C++ 的头文件 `ThostFtdcUserApiDataType.h`，解析其中的 `#define` 常量定义和 `typedef` 类型定义，生成 `ctp_typedef.py` 和 `ctp_constant.py`(demo 中 import 使用)。

### 6.3 `generate_struct.py`

- **作用**：**生成结构体定义文件**
- **功能**：读取 CTP API C++ 的头文件 `ThostFtdcUserApiStruct.h`，并依赖 `ctp_typedef.py` 中的类型映射，解析C++结构体定义，生成 Python 字典格式的结构体定义文件 `ctp_struct.py`。

### 6.4 `generate_api_functions.py`

- **作用**：**生成API函数绑定代码**
- **功能**：读取 CTP 的 API 头文件（如 `ThostFtdcTraderApi.h`、`ThostFtdcMdApi.h`），并依赖 `ctp_struct.py` 中的结构体定义和 `generate_helper.py` 辅助脚本，生成大量的 C++ 源代码文件，用于 Python 绑定。

### 6.5 `generate_dll_entry.py`

- **作用**：**生成C++ DLL入口点代码文件**
- **功能**：
  - 生成 `dllmain.cpp`、`stdafx.cpp`、`stdafx.h` 三个文件，输出在 `ctp/api/src/ctpmd` 和 `ctp/api/src/ctptd` 中
  - **dllmain.cpp**: 包含标准的DLL入口点函数，处理进程和线程的加载/卸载
  - **stdafx.cpp**: 简单的预编译头包含文件
  - **stdafx.h**: 包含Windows API头文件和常用定义

### 6.6 `generate_cpp.py`

- **作用**：**生成cpp和h文件**
- **功能**：
  - 分别在 `ctp/api/src/ctpmd` 和 `ctp/api/src/ctptd` 目录下生成 `ctpmd.cpp`、`ctpmd.h` 和 `ctptd.cpp`、`ctptd.h` 四个文件
  - 头文件包含完整的类声明和函数原型
  - CPP文件包含所有实现和绑定

### 6.7 `generate_all.py`

- **作用**：**组装所有 md 和 td header、source 等文件生成 cpp 和 h 文件**
- **功能**：组装上述文件生成的文件及 header、source 等文件生成 `ctpmd.cpp`、`ctpmd.h` 和 `ctptd.cpp`、`ctptd.h` 四个文件，相相当于上述6个脚本按顺序一键执行。

### 6.8 `build.py`

- **作用**：**一键编译出 C++ 和 Python 之间的绑定文件**
- **功能**：编译出 C++ 和 Python 之间的绑定文件，文件位于`ctp/api/`包括：
  - `ctpmd.cp313-win_amd64.pyd`
  - `ctptd.cp313-win_amd64.pyd`
  - `ctpmd.pyi`
  - `ctptd.pyi`

文件依赖关系：

1. **`generator_function_const.py`** → 生成 `ctp_function_const.py`
2. **`generate_data_type.py`** → 生成 `ctp_typedef.py` 和 `ctp_constant.py`(demo 中 import 使用)
3. **`generate_struct.py`**(依赖`ctp_typedef.py`) → 生成 `ctp_struct.py`
4. **`generate_api_functions.py`**(依赖`ctp_struct.py`、`ctp_function_const.py`、`generate_helper.py`) → 生成md和td多个API header、source绑定文件
5. **`generate_dll_entry.py`** → 生成 `dllmain.cpp`、`stdafx.cpp`、`stdafx.h`
6. **`generate_cpp.py`**(依赖上述所有文件生成的文件及header、source文件) →  生成 `ctpmd.cpp`、`ctpmd.h`和`ctptd.cpp`、`ctptd.h`
7. **`generate_all.py`** → 组装出 `ctpmd.cpp`、`ctpmd.h`和`ctptd.cpp`、`ctptd.h` 文件(相当于上述6个脚本按顺序一键执行)
8. **`build.py`**(依赖`ctp/api/src/`下的 `ctpmd` 和 `ctptd` 模块) → 一键编译出 `ctpmd.cp313-win_amd64.pyd`、`ctptd.cp313-win_amd64.pyd`、`ctpmd.pyi`、`ctptd.pyi`


## 7. 脚本的作用

这些脚本最终生成的代码用于：
- 自动处理数据类型转换
- 生成回调函数的Python绑定
- 生成请求函数的Python绑定
- 生成**C++ 和 Python 之间创建无缝的绑定（binding）文件，使得 Python 能够轻松调用高性能的 C++ 代码**


## 8. 优势

- 使用 Pybind 将 C++ 与 Python 绑定，性能优于 Swig 转换方式。
- 自动同步: 当 CTP 官方更新头文件时，替换最新的原生 h、dll、so、lib 文件，执行生成脚本后，脚本会自动反映最新的虚函数
- 易于维护: 无需手动更新大量硬编码的函数声明
- 减少错误: 避免了手动维护可能导致的遗漏或错误
- 提高效率: 开发者只需关注业务逻辑，不用担心底层接口变化

## 9. 社区支持

- [![QQ Group](https://img.shields.io/badge/QQ%20Group%231-Join-blue)](https://qun.qq.com/universal-share/share?ac=1&authKey=dzGDk%2F%2Bpy%2FwpVyR%2BTrt9%2B5cxLZrEHL793cZlFWvOXuV5I8szMnOU4Wf3ylap7Ph0&busi_data=eyJncm91cENvZGUiOiI0NDYwNDI3NzciLCJ0b2tlbiI6IlFrM0ZhZmRLd0xIaFdsZE9FWjlPcHFwSWxBRFFLY2xZbFhaTUh4K2RldisvcXlBckZ4NVIrQzVTdDNKUFpCNi8iLCJ1aW4iOiI4MjEzMDAwNzkifQ%3D%3D&data=O1Bf7_yhnvrrLsJxc3g5-p-ga6TWx6EExnG0S1kDNJTyK4sV_Nd9m4p-bkG4rhj_5TdtS5lMjVZRBv4amHyvEA&svctype=4&tempid=h5_group_info)
- [pypi.org](https://pypi.org/project/ctp-pybind)

## 10. 免责声明

👈[免责声明内容](docs/免责声明.md)

## 11. 补充

**Meson**: 类似于Make、CMake，它的主要任务是配置编译环境、生成编译指令（比如给Ninja），并管理整个编译过程。它本身并不直接编译代码，而是驱动像Ninja这样的工具来完成。

**Pybind11**: 轻量级的 C++ 库，用于将 C++ 代码暴露（绑定）给 Python 解释器。它允许 Python 代码像调用普通 Python 模块一样，无缝地调用 C++ 编写的函数和类。其核心目标是提供一个极致简单、近乎零样板代码的接口，能轻松地将 C++ 的高性能计算能力与 Python 的易用性和庞大的生态系统结合起来。

**参考**: [vnpy_ctp](https://github.com/vnpy/vnpy_ctp)

---

*ctp-pybind*
*最后更新：2026-07-10*

