from __future__ import annotations

import os
import re
from dataclasses import dataclass
from typing import Iterable

from reportlab.lib import colors
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.pdfgen import canvas


ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
OUTPUT_DIR = os.path.join(ROOT, "output", "pdf")

PAGE_WIDTH = 960
PAGE_HEIGHT = 540

FONT_REGULAR = "NotoSansSC"
FONT_BOLD = "NotoSansSCBold"
FONT_MONO = "MicrosoftYaHeiMono"

NAV_BG = colors.HexColor("#f6f7fb")
INK = colors.HexColor("#202124")
MUTED = colors.HexColor("#5f6368")
ACCENT = colors.HexColor("#315fbd")
ACCENT_LIGHT = colors.HexColor("#e8f0fe")
LINE = colors.HexColor("#d7dce8")
SOFT_GREEN = colors.HexColor("#e9f7ef")
SOFT_YELLOW = colors.HexColor("#fff7df")
SOFT_RED = colors.HexColor("#fdeceb")
CODE_BG = colors.HexColor("#f5f5f5")


def register_fonts() -> None:
    font_candidates = [
        ("NotoSansSC", "C:/Windows/Fonts/msyh.ttc"),
        ("NotoSansSCBold", "C:/Windows/Fonts/msyhbd.ttc"),
        ("MicrosoftYaHeiMono", "C:/Windows/Fonts/MSYHMONO.ttf"),
    ]
    for name, path in font_candidates:
        if os.path.exists(path):
            pdfmetrics.registerFont(TTFont(name, path))


def text_width(text: str, font_name: str, font_size: int) -> float:
    return pdfmetrics.stringWidth(text, font_name, font_size)


def wrap_text(text: str, font_name: str, font_size: int, max_width: float) -> list[str]:
    if not text:
        return [""]

    parts = re.findall(r"[A-Za-z0-9_./+\-<>=()[\]{}|:]+|\s+|.", text)
    lines: list[str] = []
    current = ""

    for part in parts:
        candidate = current + part
        if text_width(candidate, font_name, font_size) <= max_width or not current:
            current = candidate
            continue

        lines.append(current.rstrip())
        current = part.lstrip()

    if current:
        lines.append(current.rstrip())
    return lines


def draw_round_rect(
    c: canvas.Canvas,
    x: float,
    y: float,
    w: float,
    h: float,
    fill_color: colors.Color,
    stroke_color: colors.Color | None = None,
    radius: float = 8,
) -> None:
    c.setFillColor(fill_color)
    c.setStrokeColor(stroke_color or fill_color)
    c.roundRect(x, y, w, h, radius, stroke=1 if stroke_color else 0, fill=1)


@dataclass
class Slide:
    section: str
    title: str
    kind: str
    body: object
    note: str = ""


class DeckRenderer:
    def __init__(self, path: str, title: str, subtitle: str, sections: list[str], slides: list[Slide]) -> None:
        self.path = path
        self.title = title
        self.subtitle = subtitle
        self.sections = sections
        self.slides = slides
        self.canvas = canvas.Canvas(path, pagesize=(PAGE_WIDTH, PAGE_HEIGHT))

    def render(self) -> None:
        total = len(self.slides)
        for index, slide in enumerate(self.slides, start=1):
            self.draw_background()
            self.draw_header(slide.section)
            self.draw_footer(index, total)
            if slide.kind == "title":
                self.draw_title_slide(slide)
            elif slide.kind == "section":
                self.draw_section_slide(slide)
            elif slide.kind == "bullets":
                self.draw_bullets(slide)
            elif slide.kind == "compare":
                self.draw_compare(slide)
            elif slide.kind == "table":
                self.draw_table(slide)
            elif slide.kind == "pseudo":
                self.draw_pseudo(slide)
            elif slide.kind == "flow":
                self.draw_flow(slide)
            else:
                self.draw_bullets(slide)
            self.canvas.showPage()
        self.canvas.save()

    def draw_background(self) -> None:
        c = self.canvas
        c.setFillColor(colors.white)
        c.rect(0, 0, PAGE_WIDTH, PAGE_HEIGHT, stroke=0, fill=1)
        c.setFillColor(NAV_BG)
        c.rect(0, PAGE_HEIGHT - 54, PAGE_WIDTH, 54, stroke=0, fill=1)
        c.setStrokeColor(LINE)
        c.line(0, PAGE_HEIGHT - 54, PAGE_WIDTH, PAGE_HEIGHT - 54)

    def draw_header(self, current_section: str) -> None:
        c = self.canvas
        x = 30
        y = PAGE_HEIGHT - 34
        for section in self.sections:
            active = section == current_section
            c.setFont(FONT_BOLD if active else FONT_REGULAR, 11)
            c.setFillColor(ACCENT if active else MUTED)
            c.drawString(x, y, section)
            x += text_width(section, FONT_BOLD if active else FONT_REGULAR, 11) + 24

    def draw_footer(self, index: int, total: int) -> None:
        c = self.canvas
        c.setStrokeColor(LINE)
        c.line(30, 34, PAGE_WIDTH - 30, 34)
        c.setFont(FONT_REGULAR, 10)
        c.setFillColor(MUTED)
        c.drawString(30, 18, self.subtitle)
        page_text = f"{index} / {total}"
        c.drawRightString(PAGE_WIDTH - 30, 18, page_text)

    def draw_slide_title(self, title: str) -> float:
        c = self.canvas
        c.setFont(FONT_BOLD, 26)
        c.setFillColor(INK)
        c.drawString(54, PAGE_HEIGHT - 98, title)
        c.setFillColor(ACCENT)
        c.rect(54, PAGE_HEIGHT - 112, 54, 4, stroke=0, fill=1)
        return PAGE_HEIGHT - 142

    def draw_title_slide(self, slide: Slide) -> None:
        c = self.canvas
        draw_round_rect(c, 70, 112, PAGE_WIDTH - 140, 284, colors.HexColor("#f8fbff"), LINE, 10)
        c.setFont(FONT_BOLD, 42)
        c.setFillColor(INK)
        for line_index, line in enumerate(wrap_text(slide.title, FONT_BOLD, 42, PAGE_WIDTH - 230)):
            c.drawCentredString(PAGE_WIDTH / 2, 326 - line_index * 54, line)
        c.setFont(FONT_REGULAR, 20)
        c.setFillColor(MUTED)
        c.drawCentredString(PAGE_WIDTH / 2, 218, str(slide.body))
        if slide.note:
            c.setFont(FONT_REGULAR, 14)
            c.setFillColor(ACCENT)
            c.drawCentredString(PAGE_WIDTH / 2, 170, slide.note)

    def draw_section_slide(self, slide: Slide) -> None:
        c = self.canvas
        c.setFont(FONT_BOLD, 20)
        c.setFillColor(ACCENT)
        c.drawString(76, 340, slide.section)
        c.setFont(FONT_BOLD, 40)
        c.setFillColor(INK)
        c.drawString(76, 284, slide.title)
        c.setFont(FONT_REGULAR, 20)
        c.setFillColor(MUTED)
        y = 232
        for line in wrap_text(str(slide.body), FONT_REGULAR, 20, PAGE_WIDTH - 160):
            c.drawString(76, y, line)
            y -= 34

    def draw_bullets(self, slide: Slide) -> None:
        c = self.canvas
        y = self.draw_slide_title(slide.title)
        bullets = list(slide.body)
        for item in bullets:
            if isinstance(item, tuple):
                text, color_name = item
                box_color = {"green": SOFT_GREEN, "yellow": SOFT_YELLOW, "red": SOFT_RED, "blue": ACCENT_LIGHT}.get(
                    color_name, ACCENT_LIGHT
                )
                draw_round_rect(c, 72, y - 18, PAGE_WIDTH - 144, 44, box_color, None, 8)
                c.setFillColor(INK)
                c.setFont(FONT_BOLD, 16)
                c.drawString(92, y - 2, text)
                y -= 62
                continue

            c.setFillColor(ACCENT)
            c.circle(76, y + 3, 4, stroke=0, fill=1)
            c.setFillColor(INK)
            c.setFont(FONT_REGULAR, 18)
            lines = wrap_text(str(item), FONT_REGULAR, 18, PAGE_WIDTH - 132)
            for line in lines:
                c.drawString(94, y, line)
                y -= 29
            y -= 12
        self.draw_note(slide.note)

    def draw_compare(self, slide: Slide) -> None:
        c = self.canvas
        self.draw_slide_title(slide.title)
        left_title, left_items, right_title, right_items = slide.body
        col_w = (PAGE_WIDTH - 150) / 2
        self.draw_panel(54, 140, col_w, 250, left_title, left_items, SOFT_RED)
        self.draw_panel(96 + col_w, 140, col_w, 250, right_title, right_items, SOFT_GREEN)
        self.draw_note(slide.note)

    def draw_panel(self, x: float, y: float, w: float, h: float, title: str, items: Iterable[str], color: colors.Color) -> None:
        c = self.canvas
        draw_round_rect(c, x, y, w, h, color, None, 8)
        c.setFont(FONT_BOLD, 20)
        c.setFillColor(INK)
        c.drawString(x + 22, y + h - 42, title)
        yy = y + h - 82
        c.setFont(FONT_REGULAR, 16)
        for item in items:
            c.setFillColor(ACCENT)
            c.circle(x + 30, yy + 5, 3, stroke=0, fill=1)
            c.setFillColor(INK)
            for line in wrap_text(item, FONT_REGULAR, 16, w - 62):
                c.drawString(x + 42, yy, line)
                yy -= 25
            yy -= 8

    def draw_table(self, slide: Slide) -> None:
        c = self.canvas
        y = self.draw_slide_title(slide.title)
        headers, rows = slide.body
        x = 58
        table_w = PAGE_WIDTH - 116
        col_w = table_w / len(headers)
        row_h = 42
        c.setFont(FONT_BOLD, 15)
        for i, header in enumerate(headers):
            draw_round_rect(c, x + i * col_w, y - 12, col_w - 4, row_h, ACCENT_LIGHT, None, 5)
            c.setFillColor(ACCENT)
            c.drawCentredString(x + i * col_w + col_w / 2 - 2, y + 3, header)
        y -= row_h
        c.setFont(FONT_REGULAR, 14)
        for row in rows:
            max_lines = max(len(wrap_text(str(cell), FONT_REGULAR, 14, col_w - 16)) for cell in row)
            height = max(row_h, 20 * max_lines + 18)
            for i, cell in enumerate(row):
                c.setStrokeColor(LINE)
                c.setFillColor(colors.white)
                c.rect(x + i * col_w, y - height + 26, col_w - 4, height, stroke=1, fill=1)
                c.setFillColor(INK)
                yy = y + 8
                for line in wrap_text(str(cell), FONT_REGULAR, 14, col_w - 16):
                    c.drawString(x + i * col_w + 8, yy, line)
                    yy -= 20
            y -= height
        self.draw_note(slide.note)

    def draw_pseudo(self, slide: Slide) -> None:
        c = self.canvas
        self.draw_slide_title(slide.title)
        lines = str(slide.body).splitlines()
        draw_round_rect(c, 70, 112, PAGE_WIDTH - 140, 290, CODE_BG, LINE, 8)
        c.setFont(FONT_MONO, 16)
        c.setFillColor(colors.HexColor("#263238"))
        y = 366
        for line in lines:
            c.drawString(94, y, line)
            y -= 25
        self.draw_note(slide.note)

    def draw_flow(self, slide: Slide) -> None:
        c = self.canvas
        self.draw_slide_title(slide.title)
        items = list(slide.body)
        start_x = 72
        y = 282
        gap = 20
        box_w = (PAGE_WIDTH - 144 - gap * (len(items) - 1)) / len(items)
        for i, item in enumerate(items):
            x = start_x + i * (box_w + gap)
            draw_round_rect(c, x, y, box_w, 88, ACCENT_LIGHT, LINE, 8)
            c.setFillColor(ACCENT)
            c.setFont(FONT_BOLD, 24)
            c.drawCentredString(x + box_w / 2, y + 52, str(i + 1))
            c.setFillColor(INK)
            c.setFont(FONT_BOLD, 16)
            for line_index, line in enumerate(wrap_text(item, FONT_BOLD, 16, box_w - 28)):
                c.drawCentredString(x + box_w / 2, y + 24 - line_index * 20, line)
            if i + 1 < len(items):
                c.setStrokeColor(ACCENT)
                c.setLineWidth(2)
                c.line(x + box_w + 4, y + 44, x + box_w + gap - 4, y + 44)
        self.draw_note(slide.note)

    def draw_note(self, note: str) -> None:
        if not note:
            return
        c = self.canvas
        draw_round_rect(c, 70, 60, PAGE_WIDTH - 140, 36, SOFT_YELLOW, None, 8)
        c.setFont(FONT_REGULAR, 14)
        c.setFillColor(colors.HexColor("#6b4f00"))
        c.drawString(90, 73, note)


def dp_slides() -> tuple[list[str], list[Slide]]:
    sections = ["引入", "状态设计", "基础模型", "背包", "总结"]
    slides = [
        Slide("引入", "动态规划入门补充讲义", "title", "把暴力搜索树压缩成状态表", "对 Day4 课件的二周目台阶补充"),
        Slide("引入", "这节课先不背公式", "bullets", [
            "DP 的第一目标不是写出 f[i] = ...，而是说清楚 f[i] 是什么问题。",
            "如果状态含义没定，转移式就是空中楼阁。别急，先把地基打好。",
            ("核心主线：暴力搜索会重复，DP 把重复的小问题只算一次。", "blue"),
        ]),
        Slide("引入", "DP 常出现在哪里", "bullets", [
            "题目在求方案数、最大值、最小值、可行性。",
            "暴力枚举方案可行但会反复进入同一个剩余问题。",
            "答案能按最后一步、最后一个元素、选或不选来分类。",
            "数据范围暗示不能指数枚举，通常需要 O(n^2)、O(nm)、O(n log n) 等级。",
        ]),
        Slide("引入", "搜索树到状态图", "flow", [
            "暴力枚举所有选择",
            "发现相同小问题重复出现",
            "给小问题命名为状态",
            "按依赖顺序只算一次",
        ], "DP 不是神秘递推，而是把重复计算压扁。"),
        Slide("状态设计", "写 DP 前的五件事", "bullets", [
            "状态含义：f[i][j] 用一句中文解释。",
            "有效起点：哪些状态一开始就知道。",
            "转移来源：当前状态按什么分类。",
            "循环顺序：算当前状态时，依赖项是否已经算完。",
            "答案位置：输出一个状态，还是所有状态取最值。",
        ]),
        Slide("状态设计", "记忆化搜索 vs 递推", "compare", (
            "记忆化搜索",
            ["从原问题往下递归", "第一次算出状态后存起来", "适合依赖关系不容易手排时"],
            "递推填表",
            ["按依赖顺序从小到大填", "每个状态显式循环计算", "适合顺序清楚的基础模型"],
        ), "两者本质相同：都在状态图上求值。"),
        Slide("基础模型", "模型一：斐波那契", "bullets", [
            "暴力递归里 fib(n - 2) 会被 fib(n) 和 fib(n - 1) 同时需要。",
            "每个 fib(i) 其实只需要算一次。",
            "状态：f[i] 表示第 i 项的值。",
            "转移：f[i] = f[i - 1] + f[i - 2]。",
        ]),
        Slide("基础模型", "斐波那契伪代码", "pseudo", """f[0] = 0
f[1] = 1

for i from 2 to n:
    f[i] = f[i - 1] + f[i - 2]

answer = f[n]""", "真正重要的是：算 f[i] 前，f[i - 1] 和 f[i - 2] 已经存在。"),
        Slide("基础模型", "模型二：网格路径数", "bullets", [
            "状态：f[i][j] 表示从起点走到 (i, j) 的方案数。",
            "最后一步只有两种来源：从左边来，或从下边来。",
            "两类路径不重叠、不遗漏，所以方案数相加。",
            "起点 f[1][1] = 1。",
        ]),
        Slide("基础模型", "最后一步分类", "pseudo", """f[1][1] = 1

for i from 1 to n:
    for j from 1 to m:
        if i == 1 and j == 1:
            continue
        f[i][j] = 0
        if i > 1: f[i][j] += f[i - 1][j]
        if j > 1: f[i][j] += f[i][j - 1]"""),
        Slide("基础模型", "方案数、最优值、可行性", "table", (
            ["目标", "分类后怎么合并", "例子"],
            [
                ["方案数", "把每一类数量相加", "网格路径数"],
                ["最大/最小值", "每类取最优，再取总最优", "最大金币路径"],
                ["是否可行", "只要有一类可行即可", "能否凑出容量"],
            ],
        )),
        Slide("基础模型", "模型三：最大金币路径", "bullets", [
            "状态仍然是 f[i][j]，但含义变成走到 (i, j) 的最大金币数。",
            "最后一步还是左边或下边。",
            "这次不能相加，因为我们只要最好的那条路。",
            "转移：value[i][j] + max(两个来源)。",
        ]),
        Slide("基础模型", "模型四：LIS 为什么要以 i 结尾", "compare", (
            "不够用的状态",
            ["f[i] 表示前 i 个数的 LIS", "只知道长度，不知道末尾", "无法判断能不能接上 a[i]"],
            "补信息后的状态",
            ["f[i] 表示以 a[i] 结尾的 LIS", "末尾固定，合法性可判断", "答案是 max(f[i])"],
        )),
        Slide("基础模型", "LIS 转移", "pseudo", """for i from 1 to n:
    f[i] = 1
    for j from 1 to i - 1:
        if a[j] < a[i]:
            f[i] = max(f[i], f[j] + 1)

answer = max(f[1..n])""", "状态要记录足够信息，让下一步判断是否合法。"),
        Slide("背包", "背包：不要记录选了哪些", "bullets", [
            "暴力状态如果记录完整选择集合，就是 2^n。",
            "DP 只记录：处理到第几个物品、还剩多少容量。",
            "状态：f[i][j] 表示只考虑前 i 个物品，容量不超过 j 的最大价值。",
            "当前物品只有两类：选，或不选。",
        ]),
        Slide("背包", "01 背包二维转移", "pseudo", """f[i][j] = f[i - 1][j]

if j >= volume[i]:
    f[i][j] = max(
        f[i][j],
        f[i - 1][j - volume[i]] + value[i]
    )""", "第 i 个物品最多选一次，所以来源必须是 i - 1。"),
        Slide("背包", "一维优化的方向", "compare", (
            "01 背包：倒序",
            ["物品只能用一次", "不能让本轮更新后的状态再拿同一物品", "j 从 m 到 volume[i]"],
            "完全背包：正序",
            ["物品可以用多次", "允许本轮新状态继续转移", "j 从 volume[i] 到 m"],
        ), "不要死背方向，问：同一物品能不能在本轮继续使用？"),
        Slide("背包", "01 背包一维伪代码", "pseudo", """for each item i:
    for j from m down to volume[i]:
        f[j] = max(
            f[j],
            f[j - volume[i]] + value[i]
        )"""),
        Slide("背包", "完全背包一维伪代码", "pseudo", """for each item i:
    for j from volume[i] to m:
        f[j] = max(
            f[j],
            f[j - volume[i]] + value[i]
        )"""),
        Slide("总结", "常见翻车点", "bullets", [
            "只写 f[i][j]，没有中文状态含义。",
            "初始化随手写 0，导致不可达状态被当成合法状态。",
            "忘记答案位置：LIS 不是天然输出 f[n]。",
            "一维背包循环方向写反。",
            "状态漏信息，导致转移时还要追问历史细节。",
        ]),
        Slide("总结", "比赛识别信号", "bullets", [
            "前 i 个、两个前缀、以 i 结尾、走到某个格子。",
            "路径方向受限，或选择过程天然有顺序。",
            "每个物品选或不选，容量或资源有限。",
            "求方案数、最大值、最小值、是否可行。",
            ("先写四行：数据范围、暴力复杂度、状态含义、转移分类。", "green"),
        ]),
        Slide("总结", "最后的话", "bullets", [
            "DP 的难点不是数组，而是把问题压缩成状态。",
            "先从暴力搜索出发，再找重复子问题。",
            "每个状态都要像一个封装好的问题：含义清楚，答案可复用。",
            "公式只是最后的记录。前面的分析才是你比赛时能迁移的东西。",
        ]),
    ]
    return sections, slides


def ds_slides() -> tuple[list[str], list[Slide]]:
    sections = ["引入", "线性结构", "树基础", "堆与BST", "并查集", "区间结构", "总结"]
    slides = [
        Slide("引入", "数据结构入门补充讲义", "title", "从操作矛盾出发选择结构", "对 Day6 与补充材料的二周目台阶补充"),
        Slide("引入", "这份补充的定位", "bullets", [
            "栈、队列只快速复习，因为它们是你已有的地基。",
            "二叉树、堆、二叉搜索树、并查集、区间结构都按重点讲。",
            "目标不是把所有代码塞给你，而是让你知道每个结构为什么存在。",
            ("核心主线：先理解维护了什么信息，再谈怎么实现。", "blue"),
        ]),
        Slide("引入", "不要一上来猜模板", "bullets", [
            "数据结构不是 STL 容器列表，而是一套维护信息的办法。",
            "先看查询、修改和操作次数，再选择结构。",
            "再问信息性质：能不能相减？能不能重复覆盖？能不能由左右合并？",
            "工具最后才出现。哼，顺序错了就会把线段树写成大型玄学仪式。",
        ]),
        Slide("引入", "做题先问五件事", "bullets", [
            "数据是什么：数组、集合、树、图，还是动态元素？",
            "查询什么：单点、前缀、区间、极值、连通性？",
            "修改什么：无修改、单点修改、区间修改、合并集合？",
            "操作次数多大：暴力会不会炸？",
            "信息性质如何：可减、幂等、只可合并？",
        ]),
        Slide("引入", "每个结构里存什么", "flow", [
            "存储信息",
            "维护不变式",
            "修改时更新受影响部分",
            "查询时拼出答案",
        ]),
        Slide("线性结构", "线性结构快速复习", "section", "栈和队列不是重点难点，但它们提供了最基本的“处理顺序”模型。"),
        Slide("线性结构", "栈：最近的未处理对象", "bullets", [
            "规则：后进先出。",
            "状态含义：还没有被匹配或消除的对象。",
            "括号匹配中，栈里存的是未匹配的左括号。",
            "遇到右括号，只能和最近的未匹配左括号尝试匹配。",
        ]),
        Slide("线性结构", "栈的识别信号", "bullets", [
            "最近出现的东西要最先处理。",
            "括号、表达式、嵌套结构。",
            "相邻消除，或者回退到上一个状态。",
            ("问自己：我是不是需要找最近的未处理元素？", "green"),
        ]),
        Slide("线性结构", "队列：按时间顺序扩展", "bullets", [
            "规则：先进先出。",
            "状态含义：已经发现，但还没有扩展的点。",
            "BFS 中，先入队的点距离更短，所以先扩展。",
            "第一次访问某个点时，通常就得到最短步数。",
        ]),
        Slide("线性结构", "从线性结构走向树", "bullets", [
            "栈和队列像一条线：每个元素主要看前后顺序。",
            "更复杂的数据结构开始出现分叉：一个节点下面可以有多个后续位置。",
            "树就是这种分叉关系的基础语言。",
            "堆、二叉搜索树、线段树都借用了二叉树的骨架。",
        ]),
        Slide("树基础", "树：层级关系", "section", "树不是一条线，而是“父亲 - 儿子 - 子树”的层级结构。"),
        Slide("树基础", "有根树的基本词", "bullets", [
            "根：整棵树的起点，没有父亲。",
            "父亲和儿子：一条边连接的上下级关系。",
            "叶子：没有儿子的节点。",
            "深度：从根走到该节点经过的边数。",
            "子树：以某个节点为根，连同下面所有后代形成的一整块。",
        ]),
        Slide("树基础", "树最重要的性质", "bullets", [
            "除根以外，每个节点有且只有一个父亲。",
            "从任意节点不断往父亲走，最终一定到根。",
            "一个节点到根的路径唯一。",
            "很多树上算法都在利用这个唯一父亲关系沉淀状态。",
        ]),
        Slide("树基础", "二叉树：最多两个儿子", "bullets", [
            "二叉树每个节点最多有左儿子和右儿子。",
            "左、右有区别，所以它比普通“最多两个孩子”的树更有结构。",
            "二叉树天然适合递归：处理根，再处理左子树和右子树。",
            "线段树、堆、BST 都可以从二叉树理解。",
        ]),
        Slide("树基础", "三种遍历", "table", (
            ["遍历", "访问顺序", "常见用途"],
            [
                ["前序", "根 -> 左 -> 右", "先处理当前节点，再下发任务"],
                ["中序", "左 -> 根 -> 右", "BST 中会得到递增序列"],
                ["后序", "左 -> 右 -> 根", "先算儿子，再合并到父亲"],
            ],
        )),
        Slide("树基础", "遍历的小例子", "pseudo", """      A
     / \\
    B   C
   / \\
  D   E

前序：A B D E C
中序：D B E A C
后序：D E B C A"""),
        Slide("树基础", "完全二叉树：可以放进数组", "bullets", [
            "除最后一层外都填满，最后一层从左到右连续填。",
            "形状规整，所以不一定需要指针。",
            "使用 1 号下标时：左儿子是 2x，右儿子是 2x + 1。",
            "父亲是 x / 2 向下取整。",
        ]),
        Slide("树基础", "为什么这很重要", "bullets", [
            "堆依赖完全二叉树的数组存储。",
            "向上调整就是不断找父亲 x / 2。",
            "向下调整就是比较 2x 和 2x + 1 两个儿子。",
            "先懂这个骨架，堆才不会像黑盒。",
        ]),
        Slide("堆与BST", "堆：动态维护极值", "section", "堆解决的是“数据会变，但我每次要当前最大或最小”。"),
        Slide("堆与BST", "堆的不变式", "bullets", [
            "小根堆：每个父亲都不大于它的儿子。",
            "因此根节点一定是整棵树最小值。",
            "堆不保证整体有序，只保证堆顶是极值。",
            "这就是它比完整排序更轻的原因。",
        ]),
        Slide("堆与BST", "堆的插入", "flow", [
            "新元素放到末尾",
            "保持完全二叉树形状",
            "和父亲比较",
            "不满足就向上交换",
        ], "一次最多走树高 O(log n)。"),
        Slide("堆与BST", "堆的删除堆顶", "flow", [
            "删除根节点",
            "末尾元素补到根",
            "和两个儿子比较",
            "向下交换直到合法",
        ]),
        Slide("堆与BST", "排序一次 vs 堆维护", "compare", (
            "排序一次",
            ["数据不会再产生新元素", "从头扫到尾即可", "适合静态选择"],
            "堆维护",
            ["操作后会产生新元素", "每次都要重新知道极值", "适合动态极值"],
        )),
        Slide("堆与BST", "合并果子为什么用堆", "bullets", [
            "每次取当前最小的两堆。",
            "合并后产生一堆新的果子。",
            "新堆还要参与之后的最小值选择。",
            "静态排序一次不够，必须动态维护最小值。",
        ]),
        Slide("堆与BST", "二叉搜索树：有序的二叉树", "section", "BST 把“小于往左、大于往右”变成一条查找路径。"),
        Slide("堆与BST", "BST 的规则", "bullets", [
            "左子树所有值都小于当前节点。",
            "右子树所有值都大于当前节点。",
            "每棵子树也必须满足同样规则。",
            "中序遍历会得到递增序列。",
        ]),
        Slide("堆与BST", "BST 查找", "flow", [
            "从根开始",
            "目标更小就往左",
            "目标更大就往右",
            "相等则找到",
        ], "如果树平衡，每一步大约丢掉一半候选。"),
        Slide("堆与BST", "BST 插入", "bullets", [
            "插入过程和查找几乎一样。",
            "从根开始比较，小往左，大往右。",
            "走到空位置时放入新节点。",
            "插入后仍然保持中序递增。",
        ]),
        Slide("堆与BST", "BST 删除为什么麻烦", "table", (
            ["情况", "处理方式", "原因"],
            [
                ["叶子", "直接删除", "没有子树需要接回去"],
                ["一个儿子", "让儿子顶上来", "有序关系仍可保持"],
                ["两个儿子", "用前驱或后继替换", "要保住左右大小关系"],
            ],
        )),
        Slide("堆与BST", "普通 BST 会退化", "compare", (
            "理想情况",
            ["树比较平衡", "高度约 log n", "查找、插入都快"],
            "退化情况",
            ["按 1,2,3,4,5 插入", "树歪成一条链", "查找退化成 O(n)"],
        )),
        Slide("堆与BST", "竞赛里常用 set/map", "bullets", [
            "平衡树通过旋转保持高度 O(log n)。",
            "std::set 维护无重复有序集合。",
            "std::multiset 允许重复元素。",
            "std::map 维护键到值的有序映射。",
        ]),
        Slide("堆与BST", "BST 的识别信号", "bullets", [
            "动态插入、删除、查找。",
            "需要有序遍历。",
            "需要找前驱、后继。",
            "需要维护键值映射。",
        ]),
        Slide("并查集", "并查集：集合归属", "section", "并查集不维护边的细节，只维护每个元素属于哪个集合。"),
        Slide("并查集", "并查集管理什么", "bullets", [
            "它管理的是：谁和谁属于同一个集合。",
            "每个集合选一个代表，也叫根。",
            "判断同组：看两个元素的根是否相同。",
            "合并集合：让一个根挂到另一个根下面。",
        ]),
        Slide("并查集", "为什么不直接搬集合", "compare", (
            "朴素做法",
            ["每次合并时搬动很多元素", "一次合并可能 O(n)", "多次操作容易炸"],
            "代表元做法",
            ["每个集合只认一个根", "合并时只接两个根", "查询时比较根"],
        )),
        Slide("并查集", "find：找根", "pseudo", """find(x):
    if parent[x] == x:
        return x
    return find(parent[x])""", "根的父亲是自己，这是并查集的停止条件。"),
        Slide("并查集", "merge：合并集合", "pseudo", """merge(x, y):
    root_x = find(x)
    root_y = find(y)

    if root_x != root_y:
        parent[root_x] = root_y"""),
        Slide("并查集", "并查集小模拟", "table", (
            ["操作", "结构含义", "结果"],
            [
                ["初始", "每个点父亲都是自己", "所有人各自一组"],
                ["合并 1,2", "1 的根接到 2 的根", "1 和 2 同组"],
                ["合并 3,4", "3 的根接到 4 的根", "3 和 4 同组"],
                ["合并 2,3", "两棵树接起来", "1,2,3,4 同组"],
            ],
        )),
        Slide("并查集", "路径压缩不是魔法", "bullets", [
            "如果 1 -> 2 -> 3 -> 4，查 1 的根要爬很久。",
            "既然已经知道根是 4，就把路上的父亲都改成 4。",
            "这不会改变集合关系，只是把树压扁。",
            "下次查询同一批点时会更快。",
        ]),
        Slide("并查集", "路径压缩版 find", "pseudo", """find(x):
    if parent[x] != x:
        parent[x] = find(parent[x])
    return parent[x]""", "这行 parent[x] = find(parent[x]) 就是在把路径压平。"),
        Slide("并查集", "按大小合并", "bullets", [
            "如果总把大树挂到小树下面，树可能变高。",
            "可以维护 size[root]，让小集合挂到大集合上。",
            "路径压缩加按大小合并后，单次操作几乎可以看成 O(1)。",
            "严格复杂度里有反阿克曼函数，入门阶段知道它极慢增长即可。",
        ]),
        Slide("并查集", "并查集擅长与不擅长", "compare", (
            "擅长",
            ["合并两个集合", "判断是否同组", "Kruskal 判断加边是否成环"],
            "不擅长",
            ["列出集合所有成员", "删除一条关系", "直接维护集合内复杂信息"],
        )),
        Slide("并查集", "并查集识别信号", "bullets", [
            "朋友的朋友也是朋友。",
            "连通块合并。",
            "判断两个点是否已经在同一集合。",
            "Kruskal 加边前判断是否成环。",
            "等价关系具有传递性。",
        ]),
        Slide("区间结构", "区间结构：批量信息维护", "section", "区间结构解决的是数组上大量查询和修改的矛盾。"),
        Slide("区间结构", "区间问题的基本矛盾", "compare", (
            "原数组",
            ["单点修改快", "区间查询慢", "每次可能扫 O(n)"],
            "前缀和",
            ["区间查询快", "单点修改慢", "修改会影响很多前缀"],
        ), "树状数组和线段树就是在这两端之间折中。"),
        Slide("区间结构", "前缀和：无修改区间和", "pseudo", """prefix[i] = a[1] + ... + a[i]

range_sum(l, r):
    return prefix[r] - prefix[l - 1]""", "依赖可减性：区间和能由两个前缀相减。"),
        Slide("区间结构", "差分：只记录变化边界", "pseudo", """add(l, r, c):
    diff[l] += c
    diff[r + 1] -= c

restore:
    a[i] = diff[1] + ... + diff[i]""", "适合离线区间加，最后一次性输出。"),
        Slide("区间结构", "树状数组存什么", "bullets", [
            "c[i] 存以 i 为右端点、长度为 lowbit(i) 的一段和。",
            "prefix(7) 可以拆成 c[7] + c[6] + c[4]。",
            "查询时不断 i -= lowbit(i)。",
            "单点加时，所有包含这个点的块都要更新：i += lowbit(i)。",
        ]),
        Slide("区间结构", "lowbit 不是玄学", "table", (
            ["i", "lowbit(i)", "c[i] 管辖区间"],
            [
                ["1", "1", "[1, 1]"],
                ["2", "2", "[1, 2]"],
                ["3", "1", "[3, 3]"],
                ["4", "4", "[1, 4]"],
                ["6", "2", "[5, 6]"],
                ["8", "8", "[1, 8]"],
            ],
        )),
        Slide("区间结构", "树状数组伪代码", "pseudo", """add(i, v):
    while i <= n:
        c[i] += v
        i += lowbit(i)

prefix(i):
    ans = 0
    while i > 0:
        ans += c[i]
        i -= lowbit(i)
    return ans"""),
        Slide("区间结构", "ST 表：静态区间最值", "bullets", [
            "最大值没有可减性，不能像前缀和那样相减。",
            "但最大值有幂等性：重复覆盖一段不会影响答案。",
            "f[k][i] 表示从 i 开始、长度为 2^k 的区间最值。",
            "适合无修改、多次 RMQ 查询。",
        ]),
        Slide("区间结构", "ST 表不适合有修改", "compare", (
            "适合",
            ["数组静态不变", "查询最大值、最小值、gcd", "预处理后 O(1) 查询"],
            "不适合",
            ["中途单点修改", "中途区间修改", "需要动态维护答案"],
        )),
        Slide("区间结构", "线段树：递归二分维护信息", "bullets", [
            "根节点维护整个区间。",
            "左右儿子分别维护左右半段。",
            "父节点信息由两个儿子合并。",
            "任意查询区间可以拆成少量线段树节点。",
        ]),
        Slide("区间结构", "线段树和二叉树的关系", "bullets", [
            "线段树的每个节点代表一个区间。",
            "不是叶子的区间被分成左半和右半。",
            "所以它天然形成一棵二叉树。",
            "理解二叉树后，线段树就只是“节点里存区间信息”。",
        ]),
        Slide("区间结构", "线段树查询三情况", "bullets", [
            "当前节点完全在查询区间内：直接返回节点信息。",
            "当前节点完全在查询区间外：忽略。",
            "部分相交：递归左右儿子，再合并结果。",
            "单点修改时，改叶子，然后一路回溯更新父亲。",
        ]),
        Slide("区间结构", "懒标记：延迟更新", "bullets", [
            "区间修改如果直接改所有叶子，可能退化成 O(n)。",
            "完全覆盖一个节点时，先把这个节点的信息改正确。",
            "再打一个标记：孩子以后被访问时要补上这次修改。",
            "当前节点对外必须正确；孩子可以暂时旧，但访问前必须下传。",
        ]),
        Slide("区间结构", "区间结构选择地图", "table", (
            ["问题形态", "推荐结构", "原因"],
            [
                ["无修改区间和", "前缀和", "可减，查询 O(1)"],
                ["离线区间加", "差分", "只记变化边界"],
                ["单点改区间和", "树状数组", "轻量 O(log n)"],
                ["静态区间最值", "ST 表", "幂等，查询 O(1)"],
                ["区间改区间查", "线段树", "通用但代码更重"],
            ],
        )),
        Slide("总结", "常见翻车点", "bullets", [
            "只背 STL，不知道结构维护的状态含义。",
            "二叉树遍历顺序混乱，不知道什么时候先根、什么时候后根。",
            "堆误以为能保持完整有序，其实只保证堆顶极值。",
            "BST 忘记普通树会退化，需要平衡树或 STL。",
            "并查集以为能删除关系或列出全体成员。",
            "树状数组把 lowbit 当咒语，不知道 c[i] 管哪一段。",
            "ST 表拿去做有修改的题。",
            "线段树懒标记下传漏清空、漏改儿子信息。",
        ]),
        Slide("总结", "最后的话", "bullets", [
            "数据结构题的第一步是分类操作，不是猜模板。",
            "每个结构都要问：存什么、管哪段、怎么更新、怎么查询。",
            "线性结构解决顺序，树结构解决分叉与层级，集合结构解决归属，区间结构解决批量信息维护。",
            ("把查询类型、修改类型、操作次数、候选结构写出来。别偷懒。", "green"),
        ]),
    ]
    return sections, slides


def build_deck(filename: str, title: str, subtitle: str, deck_factory) -> str:
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    sections, slides = deck_factory()
    path = os.path.join(OUTPUT_DIR, filename)
    renderer = DeckRenderer(path, title, subtitle, sections, slides)
    renderer.render()
    return path


def main() -> None:
    register_fonts()
    outputs = [
        build_deck(
            "XJTU_ACM_Day4_DP_supplement_slides.pdf",
            "动态规划入门补充讲义",
            "XJTU ACM 2026 Day4 补充讲义",
            dp_slides,
        ),
        build_deck(
            "XJTU_ACM_Day6_data_structures_supplement_slides.pdf",
            "数据结构入门补充讲义",
            "XJTU ACM 2026 Day6 补充讲义",
            ds_slides,
        ),
    ]
    for output in outputs:
        print(output)


if __name__ == "__main__":
    main()
