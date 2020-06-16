import numpy as np


def first_derivative(xf_d, yf_d):
    h = xf_d[1] - xf_d[0]
    f = [(yf_d[1] - yf_d[0]) / h]
    for i in range(1, len(xf_d) - 1):
        f.append(float(((yf_d[i + 1] - yf_d[i - 1]) / 2) / h))
    f.append((yf_d[len(xf_d) - 1] - yf_d[len(xf_d) - 2]) / h)
    return f


def second_derivative(xs_d, ys_d):
    h = xs_d[1] - xs_d[0]
    first_der = first_derivative(xs_d, ys_d)
    f = [(ys_d[1] - ys_d[0]) / h]
    for i in range(1, len(xs_d) - 1):
        f.append((first_der[i + 1] - first_der[i - 1]) / 2 / h)
    f.append((first_der[len(xs_d) - 1] - first_der[len(xs_d) - 2]) / h)
    return f


def spline(x_s, y_s):
    h = []
    a = []
    b = []
    c = []
    d = []
    result = []
    answer = []
    temp = []
    temp_row = []
    matrix = []
    matrix_row = []
    for i in range(0, len(x_s) - 1):
        h.append(x_s[i + 1] - x_s[i])
        a.append(y_s[i])
        c.append(1)
    c[0] = 0
    c.append(0)
    for i in range(0, len(x_s) - 2):
        matrix_row.clear()
        for j in range(0, len(x_s) - 2):
            matrix_row.append(0)
        matrix.append(list(matrix_row))
    for i in range(0, len(x_s) - 2):
        answer.append(0)
        temp_row.clear()
        for j in range(0, len(x_s)):
            temp_row.append(0)
        temp.append(list(temp_row))
    for i in range(0, len(x_s) - 2):
        temp[i][i] = h[i] * c[i]
        temp[i][i + 1] = 4 * h[i] * c[i + 1]
        temp[i][i + 2] = h[i] * c[i + 2]
    for i in range(0, len(x_s) - 2):
        for j in range(0, len(x_s) - 2):
            matrix[i][j] = temp[i][j + 1]
    for i in range(0, len(x_s) - 2):
        answer[i] = 3 * (y[i + 2] - 2 * y[i + 1] + y[i]) / h[i]
    temp_c = np.linalg.solve(matrix, answer) #  Решение системы уравнений с помощью готовой библиотеки NumPy
    for i in range(0, len(x_s) - 2):
        c[i + 1] = temp_c[i]
    for i in range(0, len(x_s) - 2):
        delta = y[i + 1] - y[i]
        b.append((delta / h[i]) - ((2 * c[i] + c[i + 1]) * h[i] / 3))
        d.append((c[i + 1] - c[i]) / 3 / h[i])
    d.append(-c[len(x_s) - 2] / (3 * h[len(x_s) - 2]))
    b.append((y[len(x_s) - 1] - y[len(x_s) - 2]) / h[len(x_s) - 2] - (c[len(x_s) - 2] / 3 * h[len(x_s) - 2] * 2))
    for i in range(0, len(x_s) - 1):
        result.append(str(a[i]) + '+' +
                      str(b[i]) + "(x-" +
                      str(x[i]) + ")+" +
                      str(c[i]) + "(x-" +
                      str(x[i]) + ")^2+" +
                      str(d[i]) + "(x-" +
                      str(x[i]) + ")^3")
    return result


check = True
print("\nВведите массив чисел х через пробел: \n")
x = list(map(int, input().split()))
while check:
    print("\nВведите массив чисел y(y = x) через пробел: \n")
    y = list(map(int, input().split()))
    if len(y) == len(x):
        check = False
    else:
        print("\nx != y, введите", len(x), "значений y!\n")
print("xi:", *x, "yi:", *y,)
flag = True
while flag:
    print("Выберите метод:\n1 - Кубический сплайн\n2 - Первая производная\n3 - Вторая производная")
    selector = int(input())
    if selector == 1:
        result = spline(x, y)
        for i in range(0, len(result)):
            print(result[i], x[i], "<=x<=", x[i + 1], end='\n\n')
    elif selector == 2:
        result = first_derivative(x, y)
        print("f'(x) =", *result)
    elif selector == 3:
        result = second_derivative(x, y)
        print("f''(x) =", *result)
    elif selector == 0:
        flag = False
