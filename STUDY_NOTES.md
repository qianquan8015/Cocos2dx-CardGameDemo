# 学习笔记

## 1. 对需求的理解

这个项目是一个简化版纸牌消除小游戏。当前阶段的重点不是做完整关卡，也不是做复杂发牌系统，而是先把最核心的交互跑通：

- 桌面牌点击后能判断是否匹配顶部牌。
- 备用牌点击后能替换顶部牌。
- 牌移动时有动画。
- 已经移动过的牌可以撤销。

因此第一版只需要固定牌局，不需要洗牌、随机发牌、遮挡翻牌和胜负判断。

## 2. 对 Cocos2d-x 工程的理解

Cocos2d-x 3.17.2 是 C++ 项目，不是 Cocos Creator。它需要完整的 Cocos2d-x 工程结构，例如：

- `Classes/`
- `Resources/`
- `proj.win32/`
- `CMakeLists.txt`
- Cocos2d-x 引擎目录或外部引擎依赖

老版本 Cocos2d-x 的命令行工具依赖 Python 2.7。当前项目创建和迁移时使用了 Python 2.7.18 conda 环境。Windows 下编译使用的是 Visual Studio Build Tools 2022 和 MSBuild。

## 3. 实现过程中遇到的问题

最开始只有 `Classes` 源码层文件，不是完整 Cocos2d-x 工程，因此不能直接编译运行。后面需要用 `cocos new` 创建完整 C++ 模板工程，再把源码迁移进去。

过程中遇到的主要问题：

- Python 3.12 不兼容 Cocos2d-x 3.17.2 的老脚本，需要 Python 2.7.18。
- Cocos2d-x 3.17.2 的老编译脚本可能无法正确识别 VS2022。
- VS2017 Build Tools 下载和配置不方便，最后改用 VS2022 Build Tools + MSBuild 直接编译 `HelloCpp.sln`。
- 迁移后需要把新增的 `.cpp` 文件加入 `.vcxproj`，否则 Visual Studio 不会编译这些文件。
- 中文界面文字需要给工程增加 `/utf-8` 编译选项，否则 MSVC 可能按本地代码页解析源码。

## 4. 对架构的理解

把 `CardData`、`CardView`、`GameController`、`MoveRecord` 分开，是为了避免所有逻辑都写在一个 Scene 里。

- `CardData` 只表示一张牌的数据。
- `CardView` 只管显示、点击和动画。
- `GameController` 负责点击后的业务逻辑。
- `MoveRecord` 保存一次移动，方便撤销。
- `GameState` 保存当前整体状态。

这样以后要换牌面图片时，只改 `CardView`；要换规则时，只改 `CardRule` 或 `GameController`；要换布局时，优先改场景初始化或关卡配置。

## 5. 对 Undo 功能的理解

Undo 的关键不是让牌移动回去，而是恢复状态。

一次有效移动会改变很多东西：

- 卡牌所在区域。
- 卡牌当前位置。
- 当前顶部牌。
- 桌面牌列表或备用牌列表。
- 历史记录。

如果撤销时只播放反向动画，但不恢复这些数据，画面看起来回去了，逻辑其实已经错了。所以下一步点击时可能会出现匹配对象不对、牌区列表不对等问题。

## 6. 后续可优化方向

- 接入 `Resources/res` 中的真实图片资源。
- 增加遮挡关系和自动翻牌。
- 增加完整牌堆和多张备用牌。
- 增加胜负判断。
- 增加更好的 UI 效果。
- 增加关卡配置文件，让固定牌局变成可配置牌局。
