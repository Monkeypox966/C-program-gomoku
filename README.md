# C 语言五子棋与井字棋

两个独立的 C 语言小游戏：带图形界面的五子棋（双人 / 人机），以及控制台井字棋。
下面按 **Windows + MinGW-w64** 的方式编译运行，五子棋所需 Raylib 库和音效已随仓库提供。

<br>

## 第一步：准备编译工具

安装包含 GCC 的 [MinGW-w64 工具链](https://www.mingw-w64.org/downloads/)，将工具链的 `bin` 目录加入 PATH。
重新打开 PowerShell，确认下面的命令能显示 GCC 版本：

```powershell
gcc --version
```

五子棋无需另装 Raylib。井字棋可以直接用 GCC 编译；下方另提供 CMake 方式。

<br>

## 第二步：下载项目

已安装 Git 时执行：

```powershell
git clone https://github.com/Monkeypox966/C-program-gomoku.git
cd C-program-gomoku
```

没有 Git 时，可以 [下载 ZIP](https://github.com/Monkeypox966/C-program-gomoku/archive/refs/heads/main.zip)。
解压后，在包含 `gomoku`、`raylib` 和 `resources` 的项目根目录打开 PowerShell。
保留这几个文件夹的相对位置，音效会从 `resources/` 读取。

<br>

## 第三步：编译并启动五子棋

从项目根目录进入 `gomoku`，执行：

```powershell
cd gomoku
gcc main.c game.c aimove.c judge.c score.c -o gomoku.exe -O2 -I..\raylib\include -L..\raylib\lib -lraylib -lgdi32 -lwinmm
```

确认编译结束且没有报错后，启动游戏：

```powershell
.\gomoku.exe
```

也可以在 `gomoku/` 中执行 `.\build.bat`，它会编译并自动启动。
该脚本未检查 GCC 的退出码，不能只凭 “Compilation successful” 判断编译成功。

<br>

## 第四步：选择模式并开始下棋

| 操作 | 方法 |
| --- | --- |
| 双人对战 | 主菜单点击 **PVP**，两人轮流落子 |
| 人机对战 | 主菜单点击 **PVE**，再按 **1 / 2 / 3** 选择简单 / 中等 / 困难 |
| 落子 | 鼠标左键点击棋盘交叉点 |
| 悔棋 | 点击右侧 **Regret** |
| 重新开始 | 点击右侧 **Restart** |
| 退出 | 关闭游戏窗口 |

棋盘为 15×15，横向、纵向或斜向连续至少五子即可获胜。
PVE 悔棋会撤销玩家与 AI 最近一回合的落子。
当前图形对局未显示棋盘下满时的平局结果。

<br>

## 也可以运行井字棋

**从项目根目录**执行以下命令；如果终端还在 `gomoku/`，先执行 `cd ..`：

```powershell
cd jing_zi_qi
gcc main.c print_board.c judge.c print_the_result.c ai_move.c -o jing_zi_qi.exe -mconsole
```

编译没有报错后执行：

```powershell
.\jing_zi_qi.exe
```

按提示输入用空格分隔的坐标 `x y`，每个坐标取值为 **0、1、2**，例如 `1 1` 表示中心格。
只选择空格；当前程序没有完整校验越界输入和重复落子。玩家为 O，AI 为 X。

如果已安装 CMake 和 MinGW Make，并确认 `cmake`、`gcc`、`mingw32-make` 都在 PATH 中，
也可以在 `jing_zi_qi/` 中使用：

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
.\build\jing_zi_qi.exe
```

<br>

## 常见问题

**找不到 `gcc`？** 检查是否安装了 MinGW-w64、其 `bin` 是否加入 PATH，并重新打开终端。

**提示找不到 Raylib 头文件或库？** 在 `gomoku/` 中编译，并保留同级的 `../raylib/include` 和 `../raylib/lib`。
使用与附带库匹配的 Windows MinGW 工具链；本仓库未验证 Linux / macOS 图形版构建。

**启动时提示缺少 `raylib.dll`？** 可将仓库内 `raylib/lib/raylib.dll` 复制到 `gomoku.exe` 同目录。

**游戏没有音效？** 从 `gomoku/` 目录启动，确保 `../resources/knock.wav` 和 `../resources/cheers.wav` 存在。

**困难模式思考较慢？** AI 搜索深度随难度增加，可先选择 1 或 2 熟悉操作。

<br>

## 源码导览（可选）

| 目录 | 内容 |
| --- | --- |
| `gomoku/` | Raylib 图形版五子棋 |
| `jing_zi_qi/` | 控制台井字棋 |
| `raylib/` | 图形库头文件、Windows 库与独立许可证 |
| `resources/` | 落子和胜利音效 |

两个程序均使用 Minimax + Alpha-Beta 剪枝。需要阅读实现时，可展开下方说明。

<details>
<summary>五子棋文件与关键函数</summary>

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

`int check_win()` `[game.c]`

- 功能：图形对局循环使用的连珠胜负检查。
- 返回：0（没有五子连珠）、1（白方获胜）、2（黑方获胜）；该函数不返回平局状态。

`int judge(void)` `[judge.c]`

- 功能：独立的规则判定函数，额外检查棋盘是否下满。
- 返回：0（进行中）、1（AI / 白方获胜）、2（玩家 / 黑方获胜）、-1（平局）。

井字棋的 `judge()` 返回值与五子棋不同：2 表示进行中，-1 表示玩家获胜，1 表示 AI 获胜，0 表示平局。

</details>

<br>

## 许可证

项目使用 [BSD 3-Clause License](LICENSE)。附带 Raylib 的许可见 [raylib/LICENSE](raylib/LICENSE)。
