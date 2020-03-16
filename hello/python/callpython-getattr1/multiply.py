import Module1
import numpy as np

def multiply(a,b):
    print("Will compute", a, "times", b)
    c = 0
    for i in range(0, a):
        c = c + b
    return c

def testModule1():
    print("Module1.gcd(110, 30) <330> = ",Module1.gcd(5, 6))
    print("Module1.in_mandel(6.6, 4.4, 2) <7.04> = ",Module1.in_mandel(6.6, 4.4, 2))
    print("Module1.divide(6, 4) <48, 10> = ",Module1.divide(6, 4))

testModule1()

# 例如我们要解一个这样的二元一次方程组：•
# x + 2y = 3
# 4x ＋ 5y = 6
def testNumpySolve1():
    print('...testSolve1')

    def solve11():
        print('...solve11')
        A = np.mat('1,2; 4,5')  # 构造系数矩阵 A
        b = np.mat('3,6').T  # 构造转置矩阵 b （这里必须为列向量）
        r = np.linalg.solve(A, b)  # 调用 solve 函数求解
        print(r)
        print('---solve11')
    solve11()

    print('---testSolve1')

testNumpySolve1()