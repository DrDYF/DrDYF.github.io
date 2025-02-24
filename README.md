# DrDYF.github.io

一些有用的代码
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

* 图片转ICO
```python
from PIL import Image

def convert_png_to_ico(png_path, ico_path, sizes=None):
    if sizes is None:
        sizes = [(16, 16), (32, 32), (48, 48), (256, 256)]  # 默认尺寸

    # 打开 PNG 文件
    with Image.open(png_path) as img:
        # 保存为 ICO 文件，支持多尺寸
        img.save(ico_path, format="ICO", sizes=sizes)

    print(f"转换成功：{ico_path}")

# 示例调用
convert_png_to_ico("/storage/emulated/0/我的/123.png", "/storage/emulated/0/我的/123.ico")
```

* 图片转gif
```python
from PIL import Image
import os

# 所有图片所在的目录
image_folder = ''

# 输出的GIF文件名
output_gif = '.gif'

# 获取所有.png文件并按名称排序
images = [img for img in os.listdir(image_folder) if img.endswith('.png')]
images.sort()

# 打开所有图片并调整大小为64x64
frames = []
for img in images:
    img_path = os.path.join(image_folder, img)
    with Image.open(img_path) as im:
        # 调整图片大小为64x64，使用抗锯齿（Image.Resampling.LANCZOS）
        resized_im = im.resize((64, 64), Image.Resampling.LANCZOS) #64*64可以改，如果不用，就把这一行删去，把下面的resized_im换成im
        frames.append(resized_im)

# 将图片保存为GIF duration代表持续期间，loop代表重复
frames[0].save(output_gif, format='GIF', append_images=frames[1:], save_all=True, duration=100, loop=0)

print(f"GIF已保存到 {output_gif}")
```

* 
```python
```
