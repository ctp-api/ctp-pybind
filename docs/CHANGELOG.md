## v6.7.11.6

## [v6.7.11.6] - 2026-07-10

### 更新

- **功能**：将项目引用从homalos-ctp重命名为ctp-pybind。
- **功能**：增加身份验证状态追踪。
- **功能**：更新文件描述和文档内容。
- **功能**：更新免责声明文档，使用新的项目名称和日期。
- **功能**：刷新所有文档文件的最后更新时间戳。
- **功能**：修复pyproject.toml中构建工具作为运行时依赖的问题。
- **功能**：修复版本号不一致问题（meson.build、__version__.py、CHANGELOG.md）。
- **功能**：修复pyproject.toml中引用不存在的demo.py文件。
- **功能**：移除demo/md_demo.py中硬编码的密码。
- **功能**：修复docs/Disclaimer.md中的日期错误（2027->2026）。
- **功能**：修复ctp.h中的缓冲区溢出风险、数据竞争问题，移除using namespace pybind11污染。
- **功能**：修复hatch_build.py中使用os.getcwd()而非self.root的路径问题。
- **功能**：修复script/generate_dll_entry.py和generate_data_type.py中的文件名注释错误。
- **功能**：修复ctp/__init__.py中的文件名注释错误。
- **功能**：移除旧式类继承（object）。
- **功能**：修复demo/td_demo.py中的损坏注释。
- **功能**：移除重复的ctp/ctp.h文件。
- **功能**：修复.gitignore中排除hatch_build.py和__version__.py的问题。
- **功能**：重构script/generate_api_functions.py中的重复代码。
- **功能**：修复build.py自动安装依赖的问题。
- **功能**：修复generate_struct.py和generate_api_functions.py中模块导入路径问题。
- **功能**：支持Python 3.10-3.13多版本打包发布。
- **功能**：新增多版本批量构建脚本build_all.py，使用hatch build打包。

------

### Update

- **Feature:** Renamed project references from homalos-ctp to ctp-pybind.
- **Feature:** Add authentication status tracking.
- **Feature:** Updated file descriptions and documentation content.
- **Feature:** Updated disclaimer document with new project name and dates.
- **Feature:** Refreshed last updated timestamps across all documentation files.
- **Feature:** Fixed build tools being listed as runtime dependencies in pyproject.toml.
- **Feature:** Fixed version inconsistency across meson.build, __version__.py, and CHANGELOG.md.
- **Feature:** Fixed non-existent demo.py file reference in pyproject.toml.
- **Feature:** Removed hardcoded password from demo/md_demo.py.
- **Feature:** Fixed date typo in docs/Disclaimer.md (2027->2026).
- **Feature:** Fixed buffer overflow, data race issues in ctp.h, removed using namespace pybind11 pollution.
- **Feature:** Fixed path resolution in hatch_build.py using self.root instead of os.getcwd().
- **Feature:** Fixed incorrect filename in docstrings for generate_dll_entry.py and generate_data_type.py.
- **Feature:** Fixed incorrect filename in ctp/__init__.py docstring.
- **Feature:** Removed old-style class inheritance (object).
- **Feature:** Fixed broken comment in demo/td_demo.py.
- **Feature:** Removed duplicate ctp/ctp.h file.
- **Feature:** Fixed .gitignore excluding hatch_build.py and __version__.py.
- **Feature:** Refactored duplicated code in script/generate_api_functions.py.
- **Feature:** Fixed build.py auto-installing dependencies via uv add.
- **Feature:** Fixed module import path issues in generate_struct.py and generate_api_functions.py.
- **Feature:** Added support for Python 3.10-3.13 multi-version packaging.
- **Feature:** Added multi-version build script build_all.py using hatch build.

## v6.7.11.5

## [v6.7.11.5] - 2026-05-08

### 更新

- **功能**：优化目录结构，将demo放入[demo](https://github.com/ctp-api/ctp-pybind/tree/main/demo)目录，过程脚本放入[script](https://github.com/ctp-api/ctp-pybind/tree/main/script)目录。
- **功能**：优化部分脚本的代码。
- **功能**：优化README文档。
- **功能**：修改部分脚本的命名。

------

### Update

- **Feature:** Optimized the directory structure, moving demos into the [demo](https://github.com/ctp-api/ctp-pybind/tree/main/demo) directory and process scripts into the [script](https://github.com/ctp-api/ctp-pybind/tree/main/script) directory.
- **Feature:** Optimized the code for select scripts.
- **Feature:** Improved the README documentation.
- **Feature:** Renamed several scripts.

## v6.7.11.4

## [v6.7.11.4] - 2025-09-05

### 新增功能

- **功能**：修改部分代码中的命名。
- **功能**：ctp_constant.py存放在ctp/api/下。
- **功能**：新增util.py工具。
- **功能**：新增行情扩展模块测试示例td_demo.py。

------

## [v6.7.11.4] - 2025-09-05

### New Features

- **Function**: Modified naming in some code.
- **Function**: ctp_constant.py is now stored in ctp/api/.
- **Function**: Added the util.py tool.
- **Function**: Added the market expansion module test example td_demo.py.

## v6.7.11.2

## [v6.7.11.2] - 2025-09-04

### 新增功能

- **功能**：优化Demo代码注释。
- **功能**：优化README.md、README_EN.md文件。

------

## [v6.7.11.2] - 2025-09-04

### New Features

- **Function**: Optimized demo code comments.
- **Function**: Optimized README.md and README_EN.md files.
