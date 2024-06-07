from PIL import Image

img = Image.open('online0.jpg')

img = img.convert("RGB")

img.save('online0.jpg')

print("Done")