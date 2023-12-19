# 데이터셋
x = [1, 3, 6, 8]
y = [5, 1, 3, 9]

# 초기화
w1 = 0
w0 = 0
alpha = 0.01  # 학습률

# 반복 횟수
epochs = 10000

# Gradient Descent
for epoch in range(epochs):
    print()
    # Gradient 계산
    grad_w1 = -2 * sum(x[i] * (y[i] - (w1 * x[i] + w0)) for i in range(4))
    grad_w0 = -2 * sum(y[i] - (w1 * x[i] + w0) for i in range(4))

    # 파라미터 업데이트
    w1 = w1 - alpha * grad_w1
    w0 = w0 - alpha * grad_w0

    print("- w1:", w1)
    print("- w0:", w0)

# 최종 결과 출력
print("Final w1:", w1)
print("Final w0:", w0)

