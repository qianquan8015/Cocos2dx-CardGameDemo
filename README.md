# 简化版纸牌消除 Demo

这是一个基于 Cocos2d-x 3.17.2 / C++ 实现的简化版纸牌消除小游戏 Demo。项目目标是完成需求一中的核心流程：桌面牌点击匹配、备用牌替换顶部牌、`MoveTo` 平移动画、连续撤销回退，并保持视图、逻辑、数据分离。

当前版本保持最小可运行显示方式：卡牌使用矩形 + Label 文本绘制。需求资源已经整理到 `CardGameDemo/Resources/res/`，后续如需升级真实牌面，只需要修改 `CardView` 显示层，不影响匹配、撤销和状态逻辑。

## 开发环境

- 系统：Windows
- 引擎：Cocos2d-x 3.17.2
- 语言：C++
- Python：Python 2.7.18 conda 环境，用于 Cocos2d-x 老版工具链
- 构建工具：Visual Studio Build Tools 2022
- 编译工具：MSBuild
- 构建目标：Win32 Debug
- 设计分辨率：1080 x 2080
- 窗口大小：1080 x 2080
- 主牌区：1080 x 1500
- 堆牌区：1080 x 580

## 项目结构

```text
CardGameDemo/
  Classes/
    AppDelegate.cpp
    Config/
    Logic/
    Models/
    Scenes/
    Views/
  Resources/
    res/
      card_general.png
      number/
      suits/
  proj.win32/
    HelloCpp.sln
    HelloCpp.vcxproj
  CMakeLists.txt

PROGRAM_DESIGN.md
STUDY_NOTES.md
RUN_WIN32_DEBUG.md
COCOS2DX_INTEGRATION.md
DELIVERY_CHECKLIST.md
submission/Classes.zip
```

说明：

- `CardGameDemo/Classes`：纸牌 Demo 的 C++ 源码。
- `CardGameDemo/Resources/res`：需求文档提供的图片资源，当前版本已整理但暂未接入牌面显示。
- `CardGameDemo/proj.win32`：Visual Studio Win32 工程。
- `PROGRAM_DESIGN.md`：程序设计说明。
- `STUDY_NOTES.md`：学习笔记。
- `RUN_WIN32_DEBUG.md`：运行说明。

## 编译方式

当前项目已经使用 VS2022 Build Tools / MSBuild 编译通过。

重新编译时，先初始化 VS2022 C++ 编译环境，再编译 `HelloCpp.sln`：

```powershell
cmd /c """<VS2022 BuildTools>\VC\Auxiliary\Build\vcvarsall.bat"" x86 && ""<VS2022 BuildTools>\MSBuild\Current\Bin\MSBuild.exe"" ""CardGameDemo\proj.win32\HelloCpp.sln"" /p:Configuration=Debug /p:Platform=Win32 /p:PlatformToolset=v143 /p:WindowsTargetPlatformVersion=10.0.26100.0 /m:1 /v:minimal"
```

也可以直接打开：

```text
CardGameDemo/proj.win32/HelloCpp.sln
```

选择 `Debug | Win32` 后编译运行。

注意：为了让 GitHub 仓库更轻量，建议不要提交 `CardGameDemo/cocos2d/` 引擎目录。重新编译时需要先准备 Cocos2d-x 3.17.2，并按 `COCOS2DX_INTEGRATION.md` 补齐工程依赖。如果希望别人克隆后直接编译，可以保留并提交 `CardGameDemo/cocos2d/`，但该目录体积较大。

## 运行方式

当前已生成的可执行文件：

```text
CardGameDemo/proj.win32/Debug.win32/HelloCpp.exe
```

运行方式：

- 双击 `HelloCpp.exe`
- 或在 PowerShell 中执行：

```powershell
& "CardGameDemo\proj.win32\Debug.win32\HelloCpp.exe"
```

## 手动验收流程

初始顶部牌应为 `♣4`。

| 步骤 | 操作 | 预期结果 |
| --- | --- | --- |
| 1 | 点击 `♦3` | `♦3` 与 `♣4` 点数差 1，移动到顶部牌位置，并成为新的顶部牌 |
| 2 | 点击 `♥A` | 备用牌不做匹配判断，移动到顶部牌位置，并成为新的顶部牌 |
| 3 | 点击 `♠2` | `♠2` 与 `♥A` 点数差 1，移动到顶部牌位置，并成为新的顶部牌 |
| 4 | 撤销第一次 | `♠2` 回到原桌面位置，顶部牌恢复为 `♥A` |
| 5 | 撤销第二次 | `♥A` 回到原备用牌位置，顶部牌恢复为 `♦3` |
| 6 | 撤销第三次 | `♦3` 回到原桌面位置，顶部牌恢复为 `♣4` |
| 7 | 撤销第四次 | 没有历史记录，不执行操作，也不崩溃 |

## 当前已实现功能

- 固定测试牌局。
- 桌面牌点数差 1 时可以匹配。
- 匹配规则不判断花色。
- 备用牌点击后直接替换顶部牌。
- 每次有效移动记录历史。
- 支持连续撤销回退。
- 有效移动使用 `MoveTo` 动画。
- 动画期间锁定输入，避免连续点击导致状态混乱。
- Cocos2d-x 3.17.2 Win32 工程可以编译运行。
- 运行日志覆盖匹配成功、备用牌点击、撤销成功、无历史撤销、匹配失败。

## 当前未实现功能

以下内容属于后续扩展，不属于当前需求一核心范围：

- 随机发牌。
- 完整关卡系统。
- 遮挡关系与自动翻牌。
- 胜负判断。
- 音效。
- 真实牌面图片接入。
