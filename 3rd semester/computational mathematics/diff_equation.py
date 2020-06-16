import math
from math import exp
import matplotlib.pyplot as plt
import numpy as np


def function(x, y):
    return x * (y - (y * y))


def exact(xn):
    return 1/(1-(2/3)*exp(-(1/2)*xn**2))


def euler(x, y, xn, e):
    while abs(x - xn) > e:
        y += e * function(x, y)
        x += e
    return y


def runge_kutta_merson(x, y, xn, e):
    k = []
    h = e
    r = 0
    while x <= xn:
        h3 = h/3
        k.clear()
        k.append(h3 * function(x, y))
        k.append(h3 * function(x + h3, y + k[0]))
        k.append(h * function(x + h3, y + (k[0] + k[1]) / 2))
        k.append(k[0] + h3 * function(x + h / 2, y + 0.375 * (k[0] + k[2])))
        k.append(h3 * function(x + h, y + 1.5 * (k[3] - k[2])))
        sigma = 0.1 * (2 * k[3] - 3 * k[2] - k[4])
        if math.fabs(sigma) >= math.fabs(e):
            h /= 2
        else:
            y += k[3] + k[4]
            if math.fabs(sigma) * 32 < e:
                h *= 2
            x += h
    return y


def mod_euler(x, y, xn, e):
    while abs(x - xn) > e:
        y += e * function(x + e / 2, y + (e / 2) * function(x, y))
        x += e
    return y


def adams_second(x, y, xn, e):
    f = []
    for i in range(0, 2):
        f.append(function(x + e * i, runge_kutta_merson(x, y, x + e * i, e)))
    while math.fabs(x - xn) > e:
        y += e / 2 * (3 * f[1] - f[0])
        x += e
        f[0] = f[1]
        f[1] = function(x, y)
    return y


print("Введите х0:")
x = float(input())
print("Введите y0:")
y = float(input())
print("Введите хn:")
xn = float(input())
print("Введите погрешность:")
e = float(input())
print("Введите шаг графика:")
h = float(input())
print("Точное значение:", exact(xn))

flag = True
result = []
result1 = []
result2 = []
result3 = []
result4 = []
result5 = []
step = x

while flag:
    plt.clf()
    print("Выберите метод:\n1 - Метод Эйлера"
          "\n2 - Метод Рунге-Кутта Мерсона"
          "\n3 - Модифицированный метод Эйлера"
          "\n4 - Метод Адамса 2-го порядка"
          "\n5 - Все методы и точный график"
          "\n0 - Выход")
    selector = int(input())
    if selector == 1:
        print(euler(x, y, xn, e))
        result.clear()
        for i in np.arange(x, xn, h):
            result.append(euler(x, y, i, e))
        plt.plot(np.arange(x, xn, h), result, label=u'Метод Эйлера')
        plt.grid(True)
        plt.legend()
        plt.show()
    elif selector == 2:
        print(runge_kutta_merson(x, y, xn, e))
        result.clear()
        for i in np.arange(x, xn, h):
            result.append(runge_kutta_merson(x, y, i, e))
        plt.plot(np.arange(x, xn, h), result, label=u'Метод Рунге–Кутты Мерсона')
        plt.grid(True)
        plt.legend()
        plt.show()
    if selector == 3:
        print(mod_euler(x, y, xn, e))
        result.clear()
        for i in np.arange(x, xn, h):
            result.append(mod_euler(x, y, i, e))
        plt.plot(np.arange(x, xn, h), result, label=u'Модифицированный метод Эйлера')
        plt.grid(True)
        plt.legend()
        plt.show()
    if selector == 4:
        print(adams_second(x, y, xn, e))
        result.clear()
        for i in np.arange(x, xn, h):
            result.append(adams_second(x, y, i, e))
        plt.plot(np.arange(x, xn, h), result, label=u'Метод Адамса второго порядка')
        plt.grid(True)
        plt.legend()
        plt.show()
    elif selector == 5:
        for i in np.arange(x, xn + h, h):
            result1.append(euler(x, y, i, e))
            result2.append(runge_kutta_merson(x, y, i, e))
            result3.append(mod_euler(x, y, i, e))
            result4.append(adams_second(x, y, i, e))
            result5.append(exact(i))
        plt.plot(np.arange(x, xn + h, h), result1, label=u'Метод Эйлера')
        plt.scatter(np.arange(x, xn + h, h), result2, label=u'Метод Рунге–Кутты Мерсона')
        plt.plot(np.arange(x, xn + h, h), result3, label=u'Модифицированный метод Эйлера')
        plt.plot(np.arange(x, xn + h, h), result4, label=u'Метод Адамса второго порядка')
        plt.plot(np.arange(x, xn + h, h), result5, label=u'Точный')
        plt.grid(True)
        plt.legend()
        plt.show()
    if selector == 0:
        flag = False
