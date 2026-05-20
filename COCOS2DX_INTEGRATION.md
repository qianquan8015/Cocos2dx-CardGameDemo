# Cocos2d-x 3.17 工程集成说明

当前目录只是源码层，不是完整 Cocos2d-x 3.17 工程。它不包含 `cocos2d/`、完整 `Resources/`、`proj.win32/*.sln`、`proj.win32/*.vcxproj` 等工程文件。

推荐做法：先用 Cocos2d-x 3.17 创建完整 C++ 工程，例如 `CardGameDemo`，再把当前源码迁移进去。

## 自动迁移脚本

已提供脚本：

```text
tools/integrate_to_cocos2dx_win.ps1
```

用法示例：

```powershell
.\tools\integrate_to_cocos2dx_win.ps1 "D:\Path\To\CardGameDemo"
```

脚本会检查目标目录是否存在：

```text
Classes/
proj.win32/
CMakeLists.txt
```

然后执行：

- 复制当前 `Classes/` 下的 Demo 源码到目标工程 `Classes/`。
- 覆盖目标工程原有 `Classes/AppDelegate.h` 和 `Classes/AppDelegate.cpp`。
- 自动修改目标工程 `CMakeLists.txt`，尽量加入新增 cpp。
- 自动修改 `proj.win32/*.vcxproj`，加入需要编译的 cpp。
- 如果存在 `proj.win32/*.vcxproj.filters`，自动加入新增 cpp，方便 Visual Studio 文件树显示。
- 输出应打开的 `.sln` 文件和第一次运行验收流程。

## 文件复制清单

假设完整模板工程根目录为 `CardGameDemo/`。

| 当前文件 | 目标工程路径 | 操作 |
| --- | --- | --- |
| `Classes/AppDelegate.h` | `CardGameDemo/Classes/AppDelegate.h` | 覆盖模板文件 |
| `Classes/AppDelegate.cpp` | `CardGameDemo/Classes/AppDelegate.cpp` | 覆盖模板文件 |
| `Classes/Config/GameConfig.h` | `CardGameDemo/Classes/Config/GameConfig.h` | 新增文件 |
| `Classes/Logic/CardRule.h` | `CardGameDemo/Classes/Logic/CardRule.h` | 新增文件 |
| `Classes/Logic/GameController.h` | `CardGameDemo/Classes/Logic/GameController.h` | 新增文件 |
| `Classes/Logic/GameController.cpp` | `CardGameDemo/Classes/Logic/GameController.cpp` | 新增文件 |
| `Classes/Models/CardData.h` | `CardGameDemo/Classes/Models/CardData.h` | 新增文件 |
| `Classes/Models/GameState.h` | `CardGameDemo/Classes/Models/GameState.h` | 新增文件 |
| `Classes/Models/MoveRecord.h` | `CardGameDemo/Classes/Models/MoveRecord.h` | 新增文件 |
| `Classes/Scenes/CardGameScene.h` | `CardGameDemo/Classes/Scenes/CardGameScene.h` | 新增文件 |
| `Classes/Scenes/CardGameScene.cpp` | `CardGameDemo/Classes/Scenes/CardGameScene.cpp` | 新增文件 |
| `Classes/Views/CardView.h` | `CardGameDemo/Classes/Views/CardView.h` | 新增文件 |
| `Classes/Views/CardView.cpp` | `CardGameDemo/Classes/Views/CardView.cpp` | 新增文件 |

`proj.win32/main.cpp` 通常保留 Cocos2d-x 3.17 模板默认写法即可。窗口创建在 `AppDelegate.cpp` 中完成，不要在 `main.cpp` 中重复创建 `GLView`。

## Visual Studio 配置

脚本会尝试在 `proj.win32/*.vcxproj` 中确保以下项存在：

```xml
<ClCompile Include="..\Classes\AppDelegate.cpp" />
<ClCompile Include="..\Classes\Logic\GameController.cpp" />
<ClCompile Include="..\Classes\Scenes\CardGameScene.cpp" />
<ClCompile Include="..\Classes\Views\CardView.cpp" />
```

如果目标工程中仍保留：

```xml
<ClCompile Include="..\Classes\HelloWorldScene.cpp" />
```

可以保留。`AppDelegate.cpp` 已经不再引用 `HelloWorldScene`。

请确认 Visual Studio 工程的 `Additional Include Directories` 包含：

```text
$(ProjectDir)..\Classes
```

Cocos2d-x 模板工程通常已经包含该路径。脚本会检查项目文件文本中是否能看到该路径；如果没有，会输出手动设置提示。

## CMakeLists.txt 配置

脚本会尝试把以下 cpp 加入 `CMakeLists.txt` 中已有的源文件列表：

```cmake
Classes/AppDelegate.cpp
Classes/Logic/GameController.cpp
Classes/Scenes/CardGameScene.cpp
Classes/Views/CardView.cpp
```

如果模板 CMake 写法较特殊，脚本会在文件末尾写入注释提示。此时请手动把上述 cpp 放入应用 target 的源文件列表。

同时确保 include 路径包含：

```cmake
target_include_directories(${APP_NAME}
    PRIVATE
        Classes
)
```

## AppDelegate 检查点

`Classes/AppDelegate.cpp` 应满足：

```cpp
#include "Scenes/CardGameScene.h"
```

窗口创建：

```cpp
glview = GLViewImpl::createWithRect(
    "CardGameDemo",
    Rect(0, 0, GameConfig::DESIGN_WIDTH, GameConfig::DESIGN_HEIGHT),
    0.5f);
```

设计分辨率：

```cpp
glview->setDesignResolutionSize(
    GameConfig::DESIGN_WIDTH,
    GameConfig::DESIGN_HEIGHT,
    ResolutionPolicy::FIXED_WIDTH);
```

启动场景：

```cpp
director->runWithScene(CardGameScene::createScene());
```

不应再引用 `HelloWorldScene`。

## 第一次运行验收

1. 打开脚本输出的 `proj.win32/*.sln`。
2. 使用 Visual Studio 编译并运行 Windows target。
3. 确认出现 `1080 x 2080` 竖屏窗口。
4. 确认上方主牌区、下方堆牌区显示正常。
5. 确认可以看到顶部牌 `♣4`、备用牌 `♥A`、桌面牌 `♦3`、`♠2`、`♣3`、`♣K`。
6. 点击 `♦3`，它移动到顶部牌位置，顶部牌变为 `♦3`。
7. 点击 `♥A`，它移动到顶部牌位置，顶部牌变为 `♥A`。
8. 点击 `♠2`，它移动到顶部牌位置，顶部牌变为 `♠2`。
9. 连续点击 `Undo` 三次，依次恢复 `♠2`、`♥A`、`♦3`。
10. 第四次点击 `Undo` 时无历史记录，不执行操作，也不崩溃。
