# -*- coding: utf-8 -*-
import os

html_path = "/home/user/TrainerCode/web_preview/public/index.html"
with open(html_path, "rb") as f:
    html_bytes = f.read()

lessons_path = "/home/user/TrainerCode/web_preview/public/lessons.json"
with open(lessons_path, "rb") as f:
    lessons_bytes = f.read()

out_path = "/home/user/TrainerCode/src_win32/embedded_web.hpp"
with open(out_path, "w", encoding="utf-8") as f:
    f.write("#pragma once\n")
    f.write("#include <cstddef>\n\n")
    
    f.write(f"const size_t EMBEDDED_HTML_LEN = {len(html_bytes)};\n")
    f.write("const unsigned char EMBEDDED_HTML[] = {\n")
    for i, b in enumerate(html_bytes):
        f.write(f"{b}, ")
        if (i + 1) % 24 == 0:
            f.write("\n")
    f.write("\n0};\n\n")

    f.write(f"const size_t EMBEDDED_LESSONS_LEN = {len(lessons_bytes)};\n")
    f.write("const unsigned char EMBEDDED_LESSONS[] = {\n")
    for i, b in enumerate(lessons_bytes):
        f.write(f"{b}, ")
        if (i + 1) % 24 == 0:
            f.write("\n")
    f.write("\n0};\n")

print(f"Generated {out_path} (HTML: {len(html_bytes)} bytes, Lessons: {len(lessons_bytes)} bytes)")
