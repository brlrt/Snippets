from PIL import Image, ImageOps

thumbsize = 100
image = Image.open('picture.jpg')
width = image.width
height = image.height
if width > height:
    box = width
else:
    box = height

factor = thumbsize / box
width = width * factor
height = height * factor

print("{0} / {1}", width, height)

size = (width, height)
image.thumbnail(size, Image.ANTIALIAS)
background = Image.new('RGBA', (thumbsize, thumbsize), (255, 255, 255, 0))
x = (int)((thumbsize - width) / 2)
y = (int)((thumbsize - height) / 2)
background.paste(image, (x, y))
background.save("thumb.png")





"""
thumb = ImageOps.fit(image, size, Image.ANTIALIAS)
thumb.save('thump.png')
"""
