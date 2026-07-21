本仓库包含两个独立的 C 语言博弈程序，均采用 Minimax + Alpha-Beta 剪枝：

| 程序 | 目录 | 平台 | 说明 |
| --- | --- | --- | --- |
| 五子棋人机对战 | `gomoku/` | 图形界面（Raylib） | 15×15 棋盘，PVP/PVE 双模式，UI、音效、悔棋、难度选择 |
| 井字棋 AI | `jing_zi_qi/` | 控制台（CMake） | 3×3 井字棋，演示剪枝算法的最小实现 |

```
C-program-gomoku/
├── gomoku/          # Raylib 五子棋
│   ├── main.c       # 入口：主菜单 + 模式分发
│   ├── game.c       # PVP/PVE 主循环、绘制、交互
│   ├── aimove.c     # Minimax + Alpha-Beta 剪枝
│   ├── score.c      # 棋型哈希表估值
│   ├── judge.c      # 胜负/平局判定
│   ├── gomoku.h     # 公共头文件
│   └── build.bat    # 一键编译
├── jing_zi_qi/      # 控制台井字棋
│   ├── main.c  ai_move.c  judge.c
│   ├── print_board.c  print_the_result.c
│   ├── jing_zi_qi.h  CMakeLists.txt
├── raylib/          # 共享图形库（include / lib）
├── resources/       # 共享音效（knock.wav / cheers.wav）
├── README.md  LICENSE
```

---

# 一、五子棋人机对战系统（gomoku/）

《基于 Raylib 的五子棋人机对战系统》设计报告

**1. 系统功能说明**

本系统是一款基于 C 语言和 Raylib 图形库开发的五子棋游戏，旨在提供流畅的交互体验和具有挑战性的人机对战功能。系统主要包含以下功能：

双模式对战：

- PVP（人人对战）：支持两名玩家在同一台设备上轮流落子，系统自动判定胜负。
- PVE（人机对战）：玩家与内置 AI 进行对弈。AI 具备不同难度分级，能够进行智能攻防。

图形化交互界面 (GUI)：

- 提供可视化的主菜单，支持模式选择。
- 游戏界面包含标准 15x15 棋盘（含天元、星位标记）。
- 实时显示当前落子方、步数统计以及游戏结果（胜利/失败提示）。
- 美观的 UI 控件，包括圆角按钮、鼠标悬停变色效果、落子音效等。

辅助功能：

- 悔棋功能：支持撤销上一步（PVE 模式下自动撤销一回合，即玩家和 AI 各撤一步）。
- 重开局：无需重启程序即可快速开始新的一局。
- 难度选择：在 PVE 模式下，玩家可以通过键盘快捷键选择 AI 的思考深度（简单/普通/困难）。

**2. 编译与使用**

依赖：MinGW-w64 的 `gcc`、Raylib（仓库内 `raylib/` 已附 include 与 lib）。

```bat
cd gomoku
build.bat        # 编译并启动 gomoku.exe
```

或手动编译：

```bat
gcc main.c game.c aimove.c judge.c score.c -o gomoku.exe -O2 -I..\raylib\include -L..\raylib\lib -lraylib -lgdi32 -lwinmm
```

> 音效通过相对路径 `../resources/*.wav` 加载，因此可执行文件需从 `gomoku/` 目录运行。

模式选择：

- 点击界面上的 "PVP" 按钮进入双人对战模式。
- 点击 "PVE" 按钮进入难度选择界面，按下键盘数字键 1（简单）、2（中等）或 3（困难）即可开始人机对战。

游戏操作：

- 悔棋：点右侧控制面板的 "Regret" 按钮可撤销最近一步。
- 重开：点击 "Restart" 按钮清空棋盘重新开始。

胜负判定：当任意一方在横、竖、斜方向连成 5 子时，游戏结束，屏幕显示获胜方，并伴随胜利音效。

**3. 程序结构**

本系统采用模块化设计，将图形界面、游戏逻辑、AI 算法分文件管理，降低了耦合度。

3.1 **核心文件结构**

- `main.c`: 程序入口，负责主窗口初始化、资源加载、主菜单逻辑及模式分发。
- `game.c`: 负责游戏核心流程控制（PVP/PVE 循环）、图形绘制（棋盘、棋子、UI）、交互响应（鼠标点击）。
- `aimove.c`: AI 核心算法。包含 Minimax 算法与 Alpha-Beta 剪枝的实现。
- `score.c`: 局面估值。利用哈希表对当前棋型进行评分，为 AI 提供决策依据。
- `judge.c`: 规则判定。负责检查是否有五子连珠以及是否平局。
- `gomoku.h`: 全局头文件。统一定义常量、数据结构、全局变量及函数声明。

3.2 **关键函数及参数说明**

`int main()` `[main.c]`

- 功能：初始化 Raylib 窗口和音频设备，处理主菜单事件，根据用户选择调用 `PVP()` 或 `choose_dif()`。

`int PVP() / int PVE()` `[game.c]`

- 功能：游戏主循环。处理每一帧的输入、逻辑更新和画面绘制。

`struct move ai_move(int a, int b, int turn, int deep)` `[aimove.c]`

- 功能：基于 Alpha-Beta 剪枝的 Minimax 递归搜索函数。
- 参数：
  - `a`: Alpha 值（下界）。
  - `b`: Beta 值（上界）。
  - `turn`: 当前回合（1为AI，0为人）。
  - `deep`: 剩余搜索深度（对应难度）。
- 返回：最佳落子位置 `struct move`。

`int score(void)` `[score.c]`

- 功能：遍历棋盘，计算当前局面的总分。
- 实现：使用 `build_table` 预构建哈希表，通过方向向量 dx, dy 扫描棋型。

`int check_win() / int judge()` `[game.c / judge.c]`

- 功能：判断游戏状态。
- 返回：0（进行中）、1/2（某方获胜）、-1（平局）。

---

# 二、井字棋 AI（jing_zi_qi/）

控制台版井字棋，作为 Minimax + Alpha-Beta 剪枝的最小演示。人下记为 `-1`（O），AI 下记为 `1`（X），空位为 `0`。

编译（CMake）：

```bat
cd jing_zi_qi
cmake -B build && cmake --build build --config Release
```

或直接用 gcc：

```bat
gcc main.c print_board.c judge.c print_the_result.c ai_move.c -o jing_zi_qi.exe -mconsole
```

运行后按提示输入 `x y` 落子坐标即可。