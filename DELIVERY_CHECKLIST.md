# 交付清单

## 1. GitHub 仓库应包含

- `CardGameDemo/Classes`
- `CardGameDemo/Resources/res`
- `CardGameDemo/proj.win32`
- `CardGameDemo/CMakeLists.txt`
- `README.md`
- `PROGRAM_DESIGN.md`
- `STUDY_NOTES.md`
- `RUN_WIN32_DEBUG.md`
- `COCOS2DX_INTEGRATION.md`
- `DELIVERY_CHECKLIST.md`
- `.gitignore`

## 2. 单独提交文件

- 个人简历文件：用户自行提交，不放入 GitHub。
- `submission/Classes.zip`：由 `CardGameDemo/Classes` 压缩生成，用于单独提交源码。

## 3. 不建议提交

- `CardGameDemo/proj.win32/Debug.win32`
- `CardGameDemo/proj.win32/Release.win32`
- `.vs`
- `*.suo`
- `*.user`
- `*.VC.db`
- `.DS_Store`
- 本地路径缓存
- 个人简历
- 临时日志和缓存文件

## 4. 关于 Cocos2d-x 引擎目录

当前 `CardGameDemo/cocos2d` 目录体积较大。交付时有两种选择：

- 如果要保证别人克隆后直接编译，可以保留并提交 `CardGameDemo/cocos2d`。
- 如果要做轻量 GitHub 仓库，建议忽略 `CardGameDemo/cocos2d`，并在 README 中说明需要下载 Cocos2d-x 3.17.2 后补齐。

当前 `.gitignore` 默认采用轻量仓库方案，忽略 `CardGameDemo/cocos2d/`。

## 5. 最终验收

- Win32 Debug 已经可以编译。
- `HelloCpp.exe` 已经可以启动。
- 纸牌 Demo 核心流程可以手动验收。
- `Resources/res` 已整理真实资源，但当前版本不接入真实牌面。
