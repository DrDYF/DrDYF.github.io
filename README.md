# DrDYF.github.io

# 一些有用的代码
* 图片转Webp
```python
import os
from PIL import Image

# 定义图片目录
image_dir = ""

# 遍历目录中的所有文件
for filename in os.listdir(image_dir):
    if filename.endswith(".png"):
        # 构建完整的文件路径
        png_path = os.path.join(image_dir, filename)
        
        # 打开PNG图片
        with Image.open(png_path) as img:
            # 构建WebP文件的路径
            webp_path = os.path.join(image_dir, filename.replace(".png", ".webp"))
            
            # 转换为WebP格式并保存
            img.save(webp_path, "WEBP")
            print(f"转换完成: {png_path} -> {webp_path}")

print("所有PNG图片已转换为WebP格式。")
```
