from math import sqrt, log


def function(x):
    return ((x+1)**2)/sqrt(log(x))


def left_rect_integral(func, a, b, n):
    total = 0
    h = (b-a)/float(n)
    for i in range(0, n):
        total += func((a + (i * h)))
    result = h * total
    return result


def middle_rect_integral(func, a, b, n):
    total = 0
    h = (b - a) / float(n)
    for i in range(0, n):
        total += func(((a + h / 2) + (i * h)))
    result = h * total
    return result


def newton_cotes_third(func, a, b, n, k):
    total = 0
    c0 = 3/8
    omega = (1, 3, 3, 1)
    h = (b - a) / k
    for i in range(0, k + 1):
        total += omega[i] * func((a + (i * h)))
    result = c0 * h * total
    return result


print("Интегрируемая функция: f(x) = (x+1)^2)/sqrt(log(x)")
print("\nЛевая граница: ")
left_side = float(input())
print("\nПравая граница: ")
right_side = float(input())
print("\nТочность: ")
eps = float(input())

method = 1

while method:
    n = 1
    a1 = 100
    a2 = 1
    k = 3  # Порядок метода Ньютона-Кортеса
    print("\nМетод левых прямоугольников - 1"
          "\nМетод средних прямоугольников - 2"
          "\nМетод Ньютона-Котеса 3 порядка - 3"
          "\nВыход - 0")
    method = int(input())
    if method == 1:
        while abs(a1 - a2) > eps:
            n *= 2
            a1 = left_rect_integral(function, left_side, right_side, n)
            n *= 2
            a2 = left_rect_integral(function, left_side, right_side, n)
        print("\nОтвет:", a2, "\nКоличество разбиений:", n)
    elif method == 2:
        while abs(a1 - a2) > eps:
            n *= 2
            a1 = middle_rect_integral(function, left_side, right_side, n)
            n *= 2
            a2 = middle_rect_integral(function, left_side, right_side, n)
        print("\nОтвет:", a2, "\nКоличество разбиений:", n)
    elif method == 3:
        while abs(a1 - a2) > eps:
            n *= k
            a1 = newton_cotes_third(function, left_side, right_side, n, k)
            n *= k
            a2 = newton_cotes_third(function, left_side, right_side, n, k)
        print("\nОтвет:", a2, "\nКоличество разбиений:", n)