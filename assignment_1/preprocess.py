import cv2
filename = input("Enter filename: ")
img = cv2.imread('./imgsource/'+ str(filename)+".png" ,0)
if img.shape != [28,28]:
    img2 = cv2.resize(img,(28,28))
    img = img2.reshape(28,28,-1);
else:
    img = img.reshape(28,28,-1);
#revert the image,and normalize it to 0-1 range

#print(img)
ti = -1
tj = -1
for i in img:
    ti = ti + 1
    tj = -1
    for j in img[0]:
        tj = tj +1
        print(img[ti][tj][0]);