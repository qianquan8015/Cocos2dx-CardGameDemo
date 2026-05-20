# Win32 Debug 运行说明

## 1. exe 路径

当前 Win32 Debug 可执行文件：

```text
CardGameDemo/proj.win32/Debug.win32/HelloCpp.exe
```

## 2. 如何运行

方式一：双击运行：

```text
CardGameDemo/proj.win32/Debug.win32/HelloCpp.exe
```

方式二：在 PowerShell 中执行：

```powershell
& "CardGameDemo\proj.win32\Debug.win32\HelloCpp.exe"
```

## 3. 运行画面说明

- 上方为桌面牌区。
- 下方为堆牌区。
- 堆牌区包含备用牌、顶部牌和撤销按钮。
- 当前版本使用矩形 + Label 显示卡牌。
- `CardGameDemo/Resources/res` 中已经整理了真实图片资源，但当前 exe 暂未接入真实牌面图片。

## 4. 验收流程

初始顶部牌应为 `♣4`。

1. 点击 `♦3`，应移动到顶部牌位置，并成为新的顶部牌。
2. 点击 `♥A`，应移动到顶部牌位置，并成为新的顶部牌。
3. 点击 `♠2`，应移动到顶部牌位置，并成为新的顶部牌。
4. 点击撤销第一次，`♠2` 回到原桌面位置，顶部牌恢复为 `♥A`。
5. 点击撤销第二次，`♥A` 回到原备用牌位置，顶部牌恢复为 `♦3`。
6. 点击撤销第三次，`♦3` 回到原桌面位置，顶部牌恢复为 `♣4`。
7. 点击撤销第四次，没有历史记录，不执行操作，也不崩溃。

## 5. 注意事项

- 当前版本是最小可运行 Demo，没有随机发牌、遮挡翻牌、胜负判断。
- 当前版本暂未接入真实图片牌面。
- 如需重新编译，需要 VS Build Tools 和 MSBuild。
- 如果仓库不包含 `CardGameDemo/cocos2d`，需要先准备 Cocos2d-x 3.17.2 引擎依赖。
