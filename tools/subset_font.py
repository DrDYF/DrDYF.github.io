"""重新生成像素字体子集。

原字体是 7.2MB 的全量中文像素字体（22,237 字形），页面实际只用到一百多个字。
这里按「页面实际用字 + ASCII + GB2312 符号区 + GB2312 一级汉字」重新打包，
结果覆盖 CuteImagine/Resources/Font.ttf。

用法：python tools/subset_font.py
原文件：_src/Font.ttf（被 .gitignore 排除，不进仓库）
"""

import os
import re
import sys
from pathlib import Path

from fontTools import subset
from fontTools.ttLib import TTFont

ROOT = Path(__file__).resolve().parent.parent
SRC = ROOT / "_src" / "Font.ttf"
TARGET = ROOT / "CuteImagine" / "Resources" / "Font.ttf"
FONT_REF = "Font.ttf"


def page_chars() -> set[str]:
    """收集所有引用这个字体的页面里的可见文字。"""
    chars: set[str] = set()
    pages = [p for p in ROOT.glob("*.html") if FONT_REF in p.read_text(encoding="utf-8")]
    if not pages:
        sys.exit(f"没有页面引用 {FONT_REF}，检查是不是改了字体路径")
    for page in pages:
        html = page.read_text(encoding="utf-8")
        body = html.split("<body>", 1)[-1]
        body = re.sub(r"<(script|style).*?</\1>", "", body, flags=re.S)
        chars |= set(re.sub(r"<[^>]+>", "", body))
    return chars


def gb2312_chars() -> set[str]:
    """GB2312 符号区(A1-A9) + 一级汉字(B0-D7)。"""
    chars: set[str] = set()
    rows = [(0xA1, 0xAA), (0xB0, 0xD8)]  # 右上开区间
    for lo_hi, hi_hi in rows:
        for hi in range(lo_hi, hi_hi):
            for lo in range(0xA1, 0xFF):
                try:
                    chars.add(bytes([hi, lo]).decode("gb2312"))
                except UnicodeDecodeError:
                    pass
    return chars


def main() -> None:
    if not SRC.exists():
        sys.exit(f"找不到原字体 {SRC}")

    wanted = page_chars() | {chr(c) for c in range(0x20, 0x7F)} | gb2312_chars()
    # 制表符这类空白字符字体里本来就没有，别计入缺字
    visible = {c for c in page_chars() if not c.isspace()}

    opts = subset.Options()
    opts.layout_features = ["*"]
    opts.name_IDs = ["*"]
    opts.notdef_outline = True
    opts.recalc_bounds = True

    font = subset.load_font(str(SRC), opts)
    subsetter = subset.Subsetter(options=opts)
    subsetter.populate(text="".join(sorted(wanted)))
    subsetter.subset(font)
    subset.save_font(font, str(TARGET), opts)

    cmap = TTFont(str(TARGET), lazy=True).getBestCmap()
    missing = sorted(c for c in visible if ord(c) not in cmap)
    assert not missing, f"子集缺字：{''.join(missing)}（往 gb2312_chars 或页面文案里补）"

    src_kb = SRC.stat().st_size / 1024
    out_kb = TARGET.stat().st_size / 1024
    print(f"字符数 {len(wanted)}（页面用字 {len(visible)}）")
    print(f"{src_kb:,.0f} KB -> {out_kb:,.0f} KB（-{100 - out_kb / src_kb * 100:.1f}%）")
    print(f"写入 {TARGET.relative_to(ROOT)}，缺字检查通过")


if __name__ == "__main__":
    main()
