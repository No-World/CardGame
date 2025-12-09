# 纸牌消除游戏 (CardGame)

## 项目概述

本项目是一个基于 Cocos2d-x 3.17 引擎开发的纸牌消除类游戏。游戏的核心玩法是通过点击主牌区的卡牌，与底牌堆顶部的卡牌进行数值匹配（数值大1或小1）来消除卡牌。项目严格遵循 MVC（Model-View-Controller）架构设计，实现了逻辑与视图的分离，具有良好的可维护性和扩展性。

## 功能特性

*   **核心玩法**：
    *   **主牌区**：显示待消除的卡牌，支持层叠遮挡关系。
    *   **底牌堆**：接收匹配的卡牌。
    *   **备用牌堆**：当无牌可消时，可翻开备用牌作为新的底牌。
    *   **匹配规则**：点击主牌区未被遮挡的卡牌，若其点数与底牌点数相差 1（支持 A-K 循环，即 A与2、A与K均可匹配），则消除该卡牌并移动到底牌堆。
*   **回退功能 (Undo)**：
    *   支持无限步回退（直到初始状态）。
    *   回退操作包含平滑的卡牌移动动画。
    *   支持回退“消除操作”和“翻备用牌操作”。
*   **关卡系统**：
    *   支持通过 JSON 配置文件定义关卡布局（卡牌位置、花色、点数）。
    *   自动检测并加载下一关。
*   **多语言支持**：
    *   基于 JSON 的多语言配置系统，支持动态切换语言（目前默认中文）。
*   **游戏流程**：
    *   胜利判定：主牌区清空即视为胜利。
    *   胜利结算界面：提供“重玩”、“下一关”、“退出游戏”选项。

## 技术架构 (MVC)

本项目采用严格的 MVC 分层架构，各模块职责如下：

### 1. 目录结构

```
Classes/
├── configs/      # 静态配置层
│   ├── GameConfig.h          # 全局常量（设计分辨率、卡牌缩放等）
│   ├── LevelConfig.h/cpp     # 关卡数据结构及加载器
│   ├── CardResConfig.h/cpp   # 资源路径配置
│   └── LangConfig.h/cpp      # 多语言配置管理
├── models/       # 数据模型层 (Model)
│   ├── GameModel.h/cpp       # 游戏整体状态数据
│   ├── CardModel.h/cpp       # 单张卡牌数据（点数、花色、正反面、位置）
│   └── UndoModel.h/cpp       # 回退栈数据结构
├── views/        # 视图层 (View)
│   ├── GameView.h/cpp        # 游戏主场景 UI
│   ├── PlayFieldView.h/cpp   # 主牌区容器视图
│   ├── StackView.h/cpp       # 堆牌区容器视图
│   └── CardView.h/cpp        # 单张卡牌视图（处理点击事件转发）
├── controllers/  # 控制器层 (Controller)
│   └── GameController.h/cpp  # 核心业务逻辑控制器，协调 Model 与 View
├── managers/     # 管理器层
│   └── UndoManager.h/cpp     # 回退逻辑管理器，持有 UndoModel
├── services/     # 服务层
│   └── GameModelFromLevelGenerator.h/cpp # 关卡生成服务（将配置转换为运行时模型）
└── utils/        # 工具类
```

### 2. 交互流程

1.  **用户输入**：用户点击 `CardView`。
2.  **事件转发**：`CardView` 通过回调函数将点击事件传递给 `PlayFieldView`，最终传递给 `GameController`。
3.  **逻辑处理**：`GameController` 接收 `cardId`，调用 `GameModel` 获取卡牌数据，判断是否符合匹配规则。
4.  **数据更新**：
    *   若匹配成功，`UndoManager` 记录操作。
    *   `GameModel` 更新卡牌位置状态。
5.  **视图更新**：`GameController` 调用 `GameView` 播放动画并刷新界面。

## 环境依赖与构建

### 开发环境
*   **引擎**：Cocos2d-x 3.17
*   **IDE**：Visual Studio 2022 (Windows)
*   **语言**：C++ 11

### 编译运行
1.  确保已安装 Visual Studio 2022 及 C++ 桌面开发组件。
2.  打开 `proj.win32/CardGame.sln` 解决方案文件。
3.  将 `CardGame` 设为启动项目。
4.  点击“本地 Windows 调试器”进行编译和运行。

> **注意**：资源文件位于 `Resources/` 目录。在 Debug 模式下，`AppDelegate` 已配置搜索路径优先加载项目根目录的 `Resources`，无需手动拷贝资源。

## 扩展指南

### 1. 添加新关卡
1.  在 `Resources/levels/` 目录下创建新的 JSON 文件，例如 `level2.json`。
2.  文件格式参考 `level1.json`：
    ```json
    {
        "Playfield": [
            { "CardFace": 1, "CardSuit": 0, "Position": { "x": 500, "y": 1000 } }
        ],
        "Stack": [ ... ]
    }
    ```
3.  游戏胜利后会自动检测是否存在 `level{N+1}.json`，若存在则显示“下一关”按钮。

### 2. 添加新语言
1.  在 `Resources/lang/` 目录下创建新的语言文件，例如 `en.json`。
2.  定义必要的键值对（参考 `zh.json`）。
3.  在 `AppDelegate.cpp` 中修改 `LangConfig::getInstance()->loadLanguage("en");`。

### 3. 扩展新功能（例如：万能牌）
1.  **Model 层**：在 `CardModel` 或 `CardFaceType` 中添加新的类型定义。
2.  **Config 层**：在 `CardResConfig` 中添加新卡牌的图片路径。
3.  **Controller 层**：修改 `GameController::canMatch` 方法，增加对万能牌的匹配逻辑判断。
4.  **Service 层**：在 `GameModelFromLevelGenerator` 中处理新类型卡牌的生成逻辑。

## 编码规范
*   **类名**：大驼峰 (e.g., `GameController`)
*   **方法/变量**：小驼峰 (e.g., `startGame`, `_gameModel`)
*   **成员变量**：下划线开头 (e.g., `_playFieldView`)
*   **常量**：k开头或全大写 (e.g., `kCardScale`, `DESIGN_WIDTH`)
