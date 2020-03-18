import os
fd = "/opt/limi/hello-opencv/hello/python/callpython3/main.cpp"

# popen() is similar to open()
# file = open(fd, 'w')
# file.write("Hello")
# file.close()
file = open(fd, 'r')
text = file.read()
print(text)

# popen() provides a pipe/gateway and accesses the file directly
# file = os.popen(fd, 'w')
# file.write("Hello")
# File not closed, shown in next function.