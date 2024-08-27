# 1. Introduction

`zk-SNARK` 는 "정보를 공개하지 않고도 주장을 증명할 수 있는" 기발한 방법입니다. 하지만, 왜 이 방법이 기발한 것일까요?
예를 들어, 해밀턴 그래프를 증명하는 문제가 있다고 해봅시다.

![Pasted image 20240620152400.png](https://prod-files-secure.s3.us-west-2.amazonaws.com/bd650911-35d0-4322-9e7b-947249b08ae8/115002c1-d46d-4f4f-80ca-888394b069dd/Pasted_image_20240620152400.png)

해밀턴 그래프를 증명하기 위해서는 해밀턴 경로가 존재함을 보여야 합니다. 하지만, 이는 해밀턴 그래프인지 여부 증명 외에 '해밀턴 경로' 정보도 함께 드러내야 함을 의미합니다. 만약 이러한 정보가 노출 시 가치를 잃게 되는 정보라면, 정보 노출 없이 이를 증명하는 방법이 필요합니다.
영지식 증명은 이러한 경우에 아주 적합한 방법이 될 수 있습니다. 다음은 영지식 증명이 유용하게 쓰일 수 있는 또 다른 네 가지 분야입니다.

- ***프라이빗 데이터에 대한 증명***
    - 데이터를 보여주지 않고도 소유를 증명할 수 있습니다.
- ***익명 사용자에 대한 인증***
    - 신원정보 없이도 접근 권한 등을 인증할 수 있습니다.
- ***익명 지불***
    - 신원정보 등이 없어도 적법한 지불임을 증명할 수 있습니다.
- ***연산 아웃소싱***
    - 많은 자원이 필요한 연산을 수행할 때, 외부 자원에 위임하면서도 올바르게 수행되었음을 증명할 수 있습니다.
- "수행되었음"을 다시 수행해보지 않고서도 증명할 수 있습니다.

이처럼 굉장히 유용해보이는 이 암호학적 기술은 깊은 수준의 수학적, 암호학적 이론을 바탕으로 합니다. 1985년에 처음으로 [[GMR85](https://people.csail.mit.edu/silvio/Selected%20Scientific%20Papers/Proof%20Systems/The_Knowledge_Complexity_Of_Interactive_Proof_Systems.pdf)] 논문에서 개념이 소개되었으며, 이후 `non-interactive`, `succinct` 등의 개념이 추가되며 발전해왔습니다.
*zero-knowledge proof* 시스템에서는 아래 그림과 같이 두 종류의 주체가 등장합니다.

![Pasted image 20240620152720.png](https://prod-files-secure.s3.us-west-2.amazonaws.com/bd650911-35d0-4322-9e7b-947249b08ae8/a3c323da-6ed1-4292-be11-39a5db14154c/Pasted_image_20240620152720.png)

그림의 정보들을 정리하면 아래와 같습니다.

- Prover
    - Verifier 에게 정보에 대한 statement 를 납득시키려는 주체
- Verifier
    - Prover 의 statement 를 검증하는 주체
    또한 모든 ZKP 프로토콜은 아래 세 성질(property)을 만족해야 합니다.
- Completeness
    - Statement 가 True 라면, Prover는 Verifier를 납득시킬 수 있습니다.
- Soundness
    - 잘못된 statement로는 verifier를 납득시킬 수 없습니다. 즉, 속임이 불가능합니다.
- Zero-Knowledge
    - 두 주체 간의 상호작용에서, statement의 진위여부 외에는 알 수 있는 정보가 없습니다.

# 2. The Medium of a Proof

어떠한 정보를 알고 있다는 사실을 증명하는 방법은 가장 손쉬운 방법은 $A$ 를 보여주는 것입니다. 그러나, `zero-knowledge proof` 에서는 오직 **증명**만으로 **정보에 대한 주장**을 검증해야 합니다.

## 2-1. Array

정보를 드러내지 않으면서도 주장을 검증하는 아주 간단한 예를 하나 들어보겠습니다. 아래 그림과 같이 길이가 $10$인 배열(*array*)이 하나 있다고 해보겠습니다. 이 배열은 바이너리 값을 원소로 가집니다. 즉, 원소 $e$ 는 $e \in \{0,1\}$ 입니다.
![[Pasted image 20240620153047.png]]
이제 Prover가 아래의 주장을 한다고 가정해보겠습니다.

> 배열의 모든 원소는 1이다.
> 

배열을 드러내지 않으면서도 이 주장을 검증하는 방법으로는 어떤 것이 있을까요? 단순한 방법은 `Verifier`가 $10$ 개의 원소 중 임의로 하나를 선택하여 확인해보는 것입니다. $k$ 번째 원소를 선택하고 확인된 값이 $1$이었다고 해보겠습니다. 이는 `Verifier` 가 `Prover`의 주장에 대해 $\frac{1}{10} = 10\%$  의 `확신`을 할 수 있음을 의미합니다.
만약 이러한 `확신`이 $50\%$ 이상일 때만 `Prover`의 주장을 **참**으로 검증한다면, 이러한 검증을 5번 해야 합니다. 만약 $95\%$ 이상이 요구된다면, $10$개의 원소 모두에 대한 검사가 이루어져야 합니다. 직관적으로 이러한 검증 방식은 배열의 크기가 $N$ 일 때 $O(N)$ 의 복잡도를 갖게 됩니다. 따라서, 이보다 나은 방법이 필요합니다.

## 2-2. Polynomial

다항식을 활용하는 방식은 배열보다 훨씬 효율적입니다. 예를 들어, 아래와 같은 다항식 $f(x)$ 가 있다고 해보겠습니다.
![[Pasted image 20240620153309.png]]
$$f(x)=x^3-6x^2+11x-6$$
다항식 $f(x)$ 는 $x=1, 2, 3$ 일 때 $y=0$ 임을 확인할 수 있습니다. 또한, 점 $(1,0), (2,0), (3,0)$ 을 제외하면 그 어디서도 $y=0$ 일 수 없습니다.
조금 더 일반적으로 생각해보면, *대수학의 기본정리* 에 따라 최고차항의 차수(degree)가 $d$ 인 다항식 $f(x)$는 최대 $d$ 개의 해를 갖습니다. 임의의 상수 $k$에 대하여, 다항식 $g(x)=f(x)-k$ 도 역시 최대 $d$개의 해를 갖는다는 것을 쉽게 알 수 있습니다. 따라서, $f(x)=k$ 를 만족하는 $x$의 값은 최대 $d$ 개가 있습니다.
이제 Prover 가 아래와 같은 주장을 한다고 해보겠습니다.

> 다항식 $f(x)$를 알고 있다.
> 

아래 그림에서 실제 다항식 $f(x)$와 구별하기 위해 Prover가 실제로 알고 있는 다항식을 $f'(x)$ 로 달리 표기합니다.
앞서 살펴본 다항식의 성질을 이용하면 아래와 같이 단순한 형태의 프로토콜을 생각할 수 있습니다.
![[Pasted image 20240620153709.png]]

|  |  | 방향 |  | 설명 |
| --- | --- | --- | --- | --- |
| 1 |  |  | Verifier | Verifier 는 임의의 값 $t$ 에 대하여, $f(t) = v$ 를 미리 계산합니다. |
| 2 | Prover | $\leftarrow$ | Verifier | Verifier 는 Prover 에게 값 $t$를 보냅니다. |
| 3 | Prover |  |  | Prover 는 $f'(t)=v'$ 를 계산합니다. |
| 4 | Prover | $\rightarrow$ | Verifier | Prover 는 Verifier 에게 계산된 값 $v'$ 를 보냅니다. |
| 5 |  |  | Verifier | Verifier 는 $v = v'$ 임을 검사하여 주장의 진위여부를 검증합니다. |

이렇게 다항식(*polynomial*)을 이용한 방식은 배열을 이용했을 때보다 훨씬 간단하게 `높은 확신`을 줄 수 있습니다.
임의의 정수 $t$ 값을 $1$ 부터 $10^{77}$ 사이에서 고르고, `Verifier` 가 계산한 값 $v$ 에 대하여 다항식 $g(x)$ 가 아래와 같을 때,
$$g(x) = f(x) - v  \qquad (\text{where} \quad f(t) = v)$$
$g(t) = g(x') = 0$ 이 되도록 하는 $x'$ 은 최대 $d$ 개 존재합니다.
따라서, `Prover` 가 제시하는 $v'$ 가 유효할 확률은 $\frac{d}{10^{77}}$ 입니다.
이는 상당히 낮은 확률로써, 충분히 신뢰할만한 수치입니다.

# 3. Non-Interactive Zero-Knowledge of a Polynomial

## 3-1. Proving Knowledge of a Polynomial

## 개요

우리는 why and how zkp 3장 내용을 학습하면서 단일 다항식에 대해서 영지식 증명을 할 수 있습니다. 3장까지 학습한 영지식 프로토콜은 다음과 같습니다.

간결하게 하기 위해 $\{s^i\}_{i \in [d]}$는 집합 $s^1, s^2, \ldots, s^d$를 나타냅니다.

타겟 다항식 $t(x)$와 증명자의 다항식의 차수 $d$에 대해 동의한 후:

### 설정(신뢰기관)

- 무작위 값 s, $\alpha$ 샘플링
- $g^\alpha$와 $\left\{g^{s^i}\right\}{i \in [d]}, \left\{g^{\alpha s^i}\right\}{i \in \{0, \ldots, d\}}$의 암호화 계산(CRS)
- 증명 키: $\left(\left\{g^{s^i}\right\}{i \in [d]}, \left\{g^{\alpha s^i}\right\}{i \in \{0, \ldots, d\}}\right)$
- 검증 키: $\left(g^\alpha, g^{t(s)}\right)$

### 증명(증명자)

- 계수 \{c_i\}_{i \in \{0, \ldots, d\}} 할당 (즉, 지식), p(x) = c_d x^d + \cdots + c_1 x + c_0
- 다항식 h(x) = \frac{p(x)}{t(x)} 계산
- \left\{g^{s^i}\right\}_{i \in [d]}를 사용하여 암호화된 다항식 g^{p(s)}와 g^{h(s)} 계산
- \left\{g^{\alpha s^i}\right\}_{i \in \{0, \ldots, d\}}를 사용하여 암호화 시프트된 다항식 g^{\alpha p(s)} 계산
- 무작위 \delta 샘플링
- 무작위화된 증명 \pi = \left(g^{\delta p(s)}, g^{\delta h(s)}, g^{\delta \alpha p(s)}\right) 설정

### 검증(검증자)

- 증명 \pi를 \left(g^{p}, g^{h}, g^{p'}\right)로 해석
- 다항식 제한 체크: e\left(g^p, g^\alpha\right) = e\left(g^{p'}, g\right)
- 다항식 공비 체크: e\left(g^p, g\right) = e\left(g^{t}, g^h\right)

<!-- **Remark 3.3** 만약 또 다른 곱셈을 위해 페어링 결과를 재사용할 수 있다면, 증명자가 g^{p'} = e\left(g^p, g^\alpha\right)로 설정할 수 있기 때문에 프로토콜은 완전히 불안전해질 것입니다. 이는 "다항식 제한" 체크를 통과할 것입니다:
e\left(e\left(g^p, g^\alpha\right), g\right) = e\left(g^p, g^\alpha\right)  -->

## 4장

우리는 이제 단일 다항식에서 더 나아가 일반적인 프로그램에 대한 영지식 증명을 실행하고자 합니다.

### 4.1 프로그램을 산술화 하는법

아래와 같은 프로그램이 있다고 가정합니다.
우리는 다항식을 영지식 증명하는 방법을 알고있기 때문에, 프로그램을 다항식으로 변환하면 영지식 증명을 할 수 있습니다.

![image.png](image.png)

이를 어떻게 다항식화 할 수 있을까요? 먼저 우리는 이 알고리즘을 수학적으로 표현해야 합니다. 간단하게 우리는 다음과 같이 표현할 수 있습니다.

f(w, a, b) = w(a×b)+(1−w)(a+b)

우리는 어떤 유한 프로그램도 위와 같은 방식으로 표현할 수 있습니다.

### 4.2 단일연산

우리는 이제 일반적인 계산(프로그램)을 수학적인 언어로 표현했으며, 우린 이제 이걸 다항식으로 변환해야 합니다.

일반적으로 "계산" 은 다음과 같이 표현됩니다.

\text{left operand} \quad \textbf{operator} \quad \text{right operand} \quad = \quad \text{output}

두 피연산자(operand)가 중앙의 연산자(operator)에 의해 연산됩니다. 복잡한 프로그램은 이러한 연산들의 집합이기 때문에, 우리는 이러한 단일 연산을 먼저 다항식으로 어떻게 표현하는 지에 대해서 살펴봅니다.

### 4.2.1 다항식의 산술적 성질

먼저 우리는 다항식이 산술 연산과 어떻게 관련됬는지 살펴봅니다.

다항식을 사용하여 피연산자 값을 표현할 수 있다면, 산술 속성을 통해 피연산자가 적용된 연산의 결과를 얻을 수 있습니다.

예를 들어, 두 다항식 f(x) = 2x^2 - 9x + 10 과 g(x) = -4x^2 + 15x - 9 이 있다고 가정해봅시다.

우리는 이 다항식들을 곱하여 새로운 다항식 h(x) = f(x) \times g(x) 를 만들 수 있습니다.

두 다항식의 곱은 다음과 같이 계산됩니다:

h(x) = f(x) \times g(x) = (2x^2 - 9x + 10) \times (-4x^2 + 15x - 9)

![image-2.png](image-2.png)

결론적으로 우리는 다항식을 피연산자로 사용해 산술 연산을 수행할 수 있음을 알았습니다.

### 4.3 연산 검증

우리는 이제 증명자가 두 수를 곱하는 곱셈 결과를 가지고 있다고 주장하는 상황을 가정합니다.

검증자는 이를 어떻게 검증할 수 있을까요? 우리는 피연산자에 다항식을 사용할 수 있음을 4.2에서 알게 되었으므로 다음과 같은 연산 다항식으로 표현할 수 있습니다:

l(x) \, \text{operator} \, r(x) = o(x)

여기서 특정한 a 에 대해:

- l(x) - a 에서 왼쪽 피연산자의 값을 나타냅니다.
- r(x) - a 에서 오른쪽 피연산자의 값을 나타냅니다.
- o(x) - a 에서 연산 결과(출력)를 나타냅니다.

이는 x = a에서 성립하므로, l(a) \, \text{operator} \, r(a) - o(a) = 0 로 표현되며 결과적으로 (x-a)를 인수로 가집니다. 이는 3장에서의 타겟 다항식 t(x) = x-a 의 의미와 동일합니다!

예를 들어, 다음 연산을 고려해 봅시다:
3 \times 2 = 6

이는 다음과 같이 간단한 다항식으로 표현될 수 있습니다:  l(x) = 3x ,  r(x) = 2x ,  o(x) = 6x ,

이 다항식들은  a = 1 일 때 기존 연산과 같은 값으로 계산됩니다. 즉,  l(1) = 3 ;  r(1) = 2 ;  o(1) = 6 .

![image-3.png](image-3.png)

이 연산의 다항식은 다음과 같습니다.

l(x) \times r(x) = o(x)

3x \times 2x = 6x

6x^2 - 6x = 6x(x − 1) = 0

이는 아래와 같이 시각화되고, t(x) = (x-1)을 인수로 가집니다.

![image-4.png](image-4.png)

따라서 이는 기존 3장의 p(x) 같은 방법으로 다항식 l(x),r(x),o(x)가 작동함을 의미합니다. 증명자가 속이고자 한다면 연산 다항식은 (x-1)을 인수로 가지지 않을 것입니다.

따라서 검증자는 연산의 결과를 속이지 않았다는 것을 검증할 수 있습니다.

### 4.4 연산 증명

이제 우리는 연산 증명을 지원하도록 3장의 프로토콜을 수정합니다. 기존에는  p(x)에 대한 지식을 증명했다면, 이제는  l(x),r(x),o(x) 세 다항식을 증명해야 합니다. 우리는 쉽게 p(x) = l(x) \times r(x) - o(x)로 정의하는 방법을 생각할 수도 있지만, 여기에는 문제가 되는 부분이 있습니다.

1. 우리는 암호화된 값의 곱셈(l(x) \times r(x))을 증명 단계에서 진행할 수 있습니다. 암호학적 페어링은 한 번만 사용할 수 있으며, 이는 다항식 제한 검사를 위해 사용해야 하기 때문입니다.
2. 이 경우 t(x) = x-a 를 인수로 가지는 다른 p(x)가 있을 수 있습니다. 예를 들어 p(x) = l(x) − r(x) 와 같은 p(a) = 0 를 가지는 다른 다항식을 증명자가 전달할 수 있습니다. 이는 지금까지의 우리의 상태(명제)와 다르므로 이는 부적합 합니다.

따라서 우리는 각 다항식 l(x),r(x),o(x)의 값을 증명자가 별도로 제공하게 끔 합니다.

검증자는 l(s)×r(s)−o(s)=t(s)h(s) 를 확인해야 하며, 계산의 편리함을 위해 우리는 뺄셈을 덧셈으로 변경합니다.

l(s)×r(s)=t(s)h(s)+ o(s)

수정된 프로토콜은 다음과 같습니다.

### 설정 단계(변경되지 않음)

- 무작위 값 s, \alpha 샘플링
- g^\alpha와 \left\{g^{s^i}\right\}*{i \in [d]}, \left\{g^{\alpha s^i}\right\}*{i \in \{0, \ldots, d\}}의 암호화 계산(CRS)
- 증명 키: \left(\left\{g^{s^i}\right\}*{i \in [d]}, \left\{g^{\alpha s^i}\right\}*{i \in \{0, \ldots, d\}}\right)
- 검증 키: \left(g^\alpha, g^{t(s)}\right)

### 증명 단계

- l(x) , r(x) , o(x) 에 해당하는 계수를 할당합니다.
- 다항식 h(x) = \frac{l(x) \times r(x) - o(x)}{t(x)} 를 계산합니다.
- \left\{ g^{s^i} \right\}_{i \in [d]} 를 사용하여 암호화 다항식 g^{l(s)}, g^{r(s)}, g^{o(s)} 및 g^{h(s)} 를 계산합니다.
- \left\{ g^{\alpha s^i} \right\}_{i \in \{0, \ldots, d\}} 를 사용하여 시프트된 암호화 다항식 g^{\alpha l(s)}, g^{\alpha r(s)}, g^{\alpha o(s)} 를 계산합니다.
- 증명 \pi 를 \left( g^{l(s)}, g^{r(s)}, g^{o(s)}, g^{h(s)}, g^{\alpha l(s)}, g^{\alpha r(s)}, g^{\alpha o(s)} \right) 로 설정합니다.

### 검증 단계

- 증명 \pi 를 \left( g^l, g^r, g^o, g^h, g^{l'}, g^{r'}, g^{o'} \right) 로 해석합니다.
- 다항식 제한 검사:
    
    e(g^{l'}, g) = e(g^l, g^\alpha) \\
    e(g^{r'}, g) = e(g^r, g^\alpha) \\
    e(g^{o'}, g) = e(g^o, g^\alpha)
    
- 유효한 연산 검사: e(g^l, g^r) = e(g^{t(s)}, g^h) \cdot e(g^o, g)

이러한 프로토콜은 두 값의 곱셈 결과가 올바르게 계산되었음을 증명할 수 있게 합니다. 프로토콜의 변화를 간단하게 표현하기 위해 무작위 \delta 를 사용했던 영지식 요소는 제외되었습니다. 이는 검증 가능한 연산 프로토콜입니다.

### 4.5 여러 연산

우리는 이제 단일 연산에 대한 검증가능한 프로토콜을 구현했습니다. 그러나 대부분의 프로그램은 여러 연산들의 모음입니다. 우리는 이제 여러 연산을 다루는 방법에 대해서 알아봅니다.

먼저 하나의 연산을 추가합니다. a × b × c 우리는 이를 두 연산으로 분리합니다.

\textcolor{green}{a} \times \textcolor{blue}{b} = \textcolor{red}{r_1}

\textcolor{red}{r_1} \times \textcolor{blue}{c} = \textcolor{red}{r_2}

4.3의 방법과 같이, 피연산자 다항식들이 임의의 x 값(예를 들어 1)에서 대응하는 값으로 계산되도록 하여 하나의 연산을 표현할 수 있습니다.

![image-5.png](image-5.png)

![image-6.png](image-6.png)

2개의 곱셈의 경우 곡선을 찾는것이 어렵지는 않습니다. 그러면 3개의 곱셈의 경우는 어떻게 해야할까요?

### 4.5.1 다항식 보간법

연산자의 수가 늘어남에 따라 수학적 방법을 통해 다항식을 구성해야 합니다. 이를 보간법이라고 하는데, 다양한 방법이 있지만 여기서는 가장 간단한 방법인 연립방정식을 통해서 이를 계산해봅니다.

ax^2 + bx + c = y

\textcolor{green}{2} \times \textcolor{blue}{1} = \textcolor{red}{2}

\textcolor{green}{2} \times \textcolor{blue}{3} = \textcolor{red}{6}

\textcolor{green}{6} \times \textcolor{blue}{2} = \textcolor{red}{12}

\begin{cases}
l(1) = 2 \\
l(2) = 2 \\
l(3) = 6
\end{cases}
\implies
\begin{cases}
a(1)^2 + b \cdot 1 + c = 2 \\
a(2)^2 + b \cdot 2 + c = 2 \\
a(3)^2 + b \cdot 3 + c = 6
\end{cases}
\implies
\begin{cases}
a + b + c = 2 \\
4a + 2b + c = 2 \\
9a + 3b + c = 6
\end{cases}

\begin{cases}
a = 2 - b - c \\
4a + 2b + c = 2 \implies 2b = 2 - 4(2 - b - c) - c \\
c = 6 - 9(2 - b - c) - 3b
\end{cases}
\implies
\begin{cases}
a = 2 - b - c \\
b = \frac{6 - 3c}{2} \\
c = -12 + 6b + 9c
\end{cases}

\begin{cases}
a = 2 - b - c \\
b = \frac{6 - 3c}{2} \\
c = -12 + 6\left(\frac{6 - 3c}{2}\right) + 9c
\end{cases}
\implies
\begin{cases}
a = 2 \\
b = -6 \\
c = 6
\end{cases}

다음과 같은 다항식으로 나타납니다.
l(x) = 2x^2 - 6x + 6

![image-7.png](image-7.png)

다른 다항식들도 위와 같이 구할 수 있습니다.

\textcolor{blue}{r(x)} = \frac{-3x^2 + 13x - 8}{2}

\textcolor{red}{o(x)} = x^2 + x

### 4.5.2 Multi-Operation Polynomials

이제 세 가지 연산을 나타내는 피연산자 다항식을 가지게 되었으므로, 각 연산의 정확성을 단계별로 어떻게 검증하는지 알아봅니다.

마찬가지로 다항식은 이제 1에서만이 아닌 1,2,3 에서 표현됩니다. 따라서 t(x)는 1,2,3 의 근을 가져야 합니다.

t(x) = (x − 1)(x − 2)(x − 3)

![image-9.png](image-9.png)

우린 l(x) 와 r(x)의 값도 곱하여 구할 수 있습니다.

![image-10.png](image-10.png)

마지막으로 위에서 o(x)를 뺀 h(x)t(x) 도 구할 수 있습니다.

![image-11.png](image-11.png)

이를 t(x) 로 나누어 h(x) 를 구합니다.

h(x) = \frac{l(x) \times r(x) - o(x)}{t(x)} = \frac{-3x^4 + 22x^3 - 57x^2 + 62x - 24}{(x - 1)(x - 2)(x - 3)} = −3x + 4

![image-12.png](image-12.png)

잘 작동합니다!

## 4.6 변수 다항식

우리는 이제 많은 연산의 경우에도 검증 가능합니다! 그러나 이 방법에는 중요한 단점이 있습니다.

동일한 변수를 피연산자나 출력으로 사용하는 경우 문제가 될 수 있습니다.

a \times b = r1
a \times c = r2

이는 아마 아래 그래프와 같이 표현될 것입니다.

![image-13.png](image-13.png)

그럼에도 우리의 프로토콜은 변수가 모든 연산에서 단일 값을 갖도록 제약하지 않기 때문에 이러한 조건을 보장하도록 해야 합니다.

### 4.6.1 단일 변수 피연산자 다항식

우리는 먼저 위 예제와 같이 왼쪽 다항식(l(x))에 하나의 연산자만 있는 경우를 다룹니다. 이는 아래 그림과 같이 나타납니다.

![image-14.png](image-14.png)

증명자가 각  x 의 지수에 대한 계수를 다르게 설정할 수 있다면, 변수의 값이 달라질 수 있습니다. 따라서 이러한 계수가 상수가 되어 모든 지수에 동일하게 끔 해야 합니다. 이러한 계수는  s 에서의  l(x) 의 암호화된 값  g^{l(s)} 으로 표현되며 우리는 이 계수 값을 증명자가 제공하는 방법을 사용합니다.

우리가 알파 시프트를 사용해 단일 지수를 제한하는 것과 마찬가지로, 검증자는 알파 시프트를 사용해 전체 다항식을 한 번에 제한할 수 있습니다. 개별 암호화  g^{s_1}, g^{s_2}, \ldots, g^{s_d} 와 그들의 α-쉬프트  g^{\alpha s_1}, g^{\alpha s_2}, \ldots, g^{\alpha s_d} 를 제공하는 대신, 프로토콜은 다음과 같이 진행됩니다:

- **설정**
    - 해당 계수로 *피연산자 다항식* l(x) 를 구성합니다.
    - 임의의 \alpha 와 s 를 샘플링합니다.
    - 암호화된 l(s) 와 그 "쉬프트된" 쌍 (g^{l(s)}, g^{\alpha l(s)}) 로 증명 키를 설정합니다.
    - 검증 키를 설정합니다: (g^{\alpha})
- **증명**
    - 피연산자의 값 v 를 가지고
        - *피연산자 다항식*을 곱합니다: (g^{l(s)})^v
        - 쉬프트된 *피연산자 다항식*을 곱합니다: (g^{\alpha l(s)})^v
    - *피연산자 다항식* 곱셈 증명을 제공합니다: (g^{v l(s)}, g^{v \alpha l(s)})
- **검증**
    - 증명을 (g^l, g^{l'}) 로 해석합니다.
    - 비율을 검증합니다: e(g^{l'}, g) = e(g^l, g^{\alpha})

### 4.6.2 멀티 변수 피연산자 다항식

우리는 이제 같은 변수를 포함하면서도 다른 변수를 포함한 다항식도 고려해야 합니다. 우린 아래와 같은 경우를 고려합니다.

a × b = r_1

a × c = r_2

d × c = r_3

![image-15.png](image-15.png)

다항식은 더하면 해당 다항식들의 개별 값이 합쳐진다는 점을 이용해 우리는  피연산자 다항식  l(x) 를 피연산자 변수 다항식  l_a(x) 와  l_d(x) 로 분리할 수 있습니다.

![image-16.png](image-16.png)

이는 변수  a 와  d 가 이전 섹션에서와 유사하게 별도로 할당되고 제한됩니다.

산술적 속성을 사용하여 각 피연산자 변수 다항식을 구성할 수 있습니다. 해당 변수가 해당 연산에서 피연산자로 사용되면 1로 계산되고, 그렇지 않으면 0으로 결정되도록 합니다. 예를 들어  l_a(x) 는  l_a(1) = 1 ,  l_a(2) = 1 ,  l_a(3) = 0 을 만족해야 하며,  l_d(x) 는  x = 1 과  x = 2 에서 0이고  x = 3 에서 1이어야 합니다.

따라서 각 변수의 값을 별도로 설정하고 이를 함께 더하여 피연산자 다항식을 만들 수 있습니다. 예를 들어  a = 3 이고  d = 2 라면 다음과 같이 피연산자 다항식을 만들 수 있습니다. :

![image-17.png](image-17.png)

이러한 복합 피연산자 다항식을 우리는 대문자로 나타냅니다.,  L(x) = a l_a(x) + d l_d(x) 프로토콜은 다음과 같이 변경됩니다.

- **Setup**
    - l_a(x) , l_d(x) 를 구성하여 해당 변수가 사용되는 "연산 x "에서 1을 통과하고 다른 모든 연산에서는 0을 통과하도록 합니다.
    - 무작위 s , \alpha 를 샘플링합니다.
    - 할당되지 않은 변수 다항식을 계산하고 암호화합니다: g^{l_a(s)}, g^{l_d(s)}
    - 이러한 다항식의 쉬프트를 계산합니다: g^{\alpha l_a(s)}, g^{\alpha l_d(s)}
    - 증명 키를 설정합니다: (g^{l_a(s)}, g^{l_d(s)}, g^{\alpha l_a(s)}, g^{\alpha l_d(s)})
    - 검증 키를 설정합니다: (g^{\alpha})
- **Proving**
    - 변수 다항식에 a 와 d 값을 할당합니다: (g^{l_a(s)})^a, (g^{l_d(s)})^d
    - 쉬프트된 다항식에 동일한 값을 할당합니다: (g^{\alpha l_a(s)})^a, (g^{\alpha l_d(s)})^d
    - 할당된 모든 변수 다항식을 더하여 피연산자 다항식을 형성합니다:
    g^L(s) = g^{a l_a(s)} \cdot g^{d l_d(s)} = g^{a l_a(s) + d l_d(s)}
    - 할당된 쉬프트된 변수 다항식을 더하여 쉬프트된 피연산자 다항식을 형성합니다:
    g^{\alpha L(s)} = g^{\alpha a l_a(s)} \cdot g^{\alpha d l_d(s)} = g^{\alpha (a l_a(s) + d l_d(s))}
    - 유효한 왼쪽 피연산자 할당의 증명을 제공합니다:
    (g^L(s), g^{\alpha L(s)})
- **Verification**
    - 증명을 (g^L, g^{L'}) 로 해석합니다.
    - 제공된 다항식이 원래 제공된 할당되지 않은 변수 다항식의 곱의 합인지를 확인합니다:
    e(g^{L'}, g) = e(g^L, g^{\alpha})
    이는 다음을 확인합니다:
    \alpha a l_a(s) + \alpha d l_d(s) = \alpha \times (a l_a(s) + d l_d(s))

### 4.7 구성 속성

우리는 이제 여러 연산을 다항식으로 표현하고, 이를 검증가능하게 하는 프로토콜이 있습니다.

이러한 수정의 부수적인 효과로 얻어지는 여러 가지 유용한 속성이 있습니다.

### 4.7.1 Constant Coefficients

우리는 다항식을 변수 다항식으로 분해하면서 0과 1로 사용되는 여부만을 표현했습니다. 그러나 우리는 다른 계수를 사용하는 것도 가능합니다.

2a × 1b = 3r

−3a × 1b = −2r

### 4.7.2 Addition for Free

우린 이제 피연산자 다항식을 변수 다항식의 합으로 나타냅니다. 우린 변수 다항식을 이용해 각 연산에서 필요한 변수를 원하는 만큼 추가할 수 있습니다. 예를 들어 첫 번째 연산에서 𝑎 + 𝑐를 먼저 더한 후 다른 피연산자와 곱할 수 있습니다. 예를 들어, (𝑎+𝑐)×𝑏=𝑟은 다음과 같이 표현할 수 있습니다:

![image-19.png](image-19.png)

따라서 각 피연산자의 연산에서 필요한 만큼의 변수를 계수로 하여 피연산자를 생성할 수 있습니다.

(c_{l,a} \cdot a + c_{l,b} \cdot b + \ldots) \times (c_{r,a} \cdot a + c_{r,b} \cdot b + \ldots) = (c_{o,a} \cdot a + c_{o,b} \cdot b + \ldots)

이를 정리하면 다음과 같이 정리됩니다. 변수 v_i \in \{v_1, v_2, \ldots, v_n\} 와 피연산자 변수 계수 c_{l,i} \in \{c_{l,1}, c_{l,2}, \ldots, c_{l,n}\}, c_{r,i} \in \{c_{r,1}, c_{r,2}, \ldots, c_{r,n}\}, c_{o,i} \in \{c_{o,1}, c_{o,2}, \ldots, c_{o,n}\}에 대해 피연산자는 다음과 같습니다. :

\sum_{i=1}^{n} \textcolor{green}{c_{l,i} \cdot v_i} \times \sum_{i=1}^{n} \textcolor{blue}{c_{r,i} \cdot v_i} = \sum_{i=1}^{n} \textcolor{red}{c_{o,i} \cdot v_i}

### 4.7.3 덧셈, 뺄셈 및 나눗셈

### 덧셈

이전 섹션에서 단일 피연산자의 다항식 내에서 변수를 더할 수 있음을 확인했습니다. 이를 다른 피연산자와 곱할 수 있습니다. 예를 들어 a + b를 계산하려면 다음과 같이 표현할 수 있습니다:

(a + b) \times 1 = r

참고: 각 피연산자에 대해 상수 계수와 변수를 필요로 하므로, 1의 값은 c_{one} \cdot v_{one}로 표현됩니다. 여기서 c_{one} = 1은 다항식에 고정될 수 있으며, v_{one}은 변수로 어떤 값이든 할당될 수 있습니다. 따라서 v_{one}의 값을 강제해야 합니다.

### 뺄셈

뺄셈은 덧셈과 거의 동일하며, 차이점은 음수 계수를 사용하는 것입니다. 예를 들어, a - b의 경우:

(a + (-1) \cdot b) \times 1 = r

### 나눗셈

우리는 나눗셈을 곱셈으로 표현할 수 있습니다: 예를 들어,  \frac{a}{b} = r 를 증명하려면 다음과 같이 표현할 수 있습니다:

b \times r = a

### 4.8 예제

![image-20.png](image-20.png)

위 알고리즘은 아래와 같이 분해할 수 있습니다.

w × (a × b) + (1 − w) × (a + b) = v

이를 단순화합니다.

w × (a × b − a − b) = v − a − b

우리는 이제 두번의 곱셈으로 식을 게산할 수 있습니다.

1:
1 \cdot a \times 1 \cdot b = 1 \cdot m

2:
1 \cdot w \times 1 \cdot m + -1 \cdot a + -1 \cdot b = 1 \cdot v + -1 \cdot a + -1 \cdot b

우리는 또한  w가 바이너리어야 한다는 제약조건을 추가합니다.

3:
1 \cdot w \times 1 \cdot w = 1 \cdot w

총 5개의 변수가 있으면 2개의 변수가 좌 피연산자 4개의 변수가 우 피연산자 그리고 출력에 5개에 변수가 들어 있습니다. 피연산자 다항식은 다음과 같습니다.

L(x) = a \cdot l_a(x) + w \cdot l_w(x)

R(x) = m \cdot r_m(x) + a \cdot r_a(x) + b \cdot r_b(x) + w \cdot r_w(x)

O(x) = m \cdot o_m(x) + v \cdot o_v(x) + a \cdot o_a(x) + b \cdot o_b(x) + w \cdot o_w(x)

인수 다항식을 t(x) = (x − 1)(x − 2)(x − 3) 라고 하면 우리는 다음과 같이 각 변수 다항식을 표현할 수 있습니다.

![image-21.png](image-21.png)

우리는 이제 계산을 증명하기 위한 준비를 마쳤습니다.
예를 들어 입력을 w=1, 𝑎=3, 𝑏=2로 설정합니다. 중간 변수 m과 v는 다음과 같이 계산됩니다.

m = a × b = 6

v = w(m − a − b) + a + b = 6

그 후 이 값들을 변수 다항식에 할당하고, 피연산자 및 출력 다항식을 생성합니다.

L(x) = 3 \cdot l_a(x) + 1 \cdot l_w(x) = x^2 - 5x + 7

R(x) = 6 \cdot r_m(x) + 3 \cdot r_a(x) + 2 \cdot r_b(x) + 1 \cdot r_w(x) = \frac{1}{2} x^2 - 2 \frac{1}{2} x + 4

O(x) = 6 \cdot o_m(x) + 6 \cdot o_v(x) + 3 \cdot o_a(x) + 2 \cdot o_b(x) + 1 \cdot o_w(x) = 2 \frac{1}{2} x^2 - 12 \frac{1}{2} x + 16

![image-22.png](image-22.png)

![image-23.png](image-23.png)

이제 우리는  L(x) × R(x) − O(x) = t(x) h(x) 를 증명하고, h(x)를 찾을 수 있습니다.

h(x) = \frac{L(x) \times R(x) - O(x)}{t(x)} = \frac{\frac{1}{2}x^4 - 5x^3 + \frac{35}{2}x^2 - 25x + 12}{(x - 1)(x - 2)(x - 3)} = \frac{1}{2}x - 2

![image-24.png](image-24.png)

다항식  L(x) \times R(x) - O(x) 가  x = 1 ,  x = 2 ,  x = 3 에서 해를 가지는 것이 보입니다. 따라서  t(x) 는 그 인수(cofactor)이며, 변수가 일관되지 않은 값을 사용했다면 그렇지 않았을 것입니다.
이렇게 해서 올바른 계산 실행을 위한 변수 값의 지식이 다항식 수준에서 증명됩니다. 이후 증명자는 프로토콜의 암호학적 부분을 진행하게 됩니다.

### 4.9 Verifiable Computation Protocol

우리는 이제 지금까지 업데이트된 내용이 어떻게 정의되는지 살펴보겠습니다. 증명의 대상이 되는 계산 결과를 제공하는 함수  f(*) 에 동의했다고 가정하고, 연산의 수  d , 변수의 수  n  및 이에 대응하는 계수 \{c_{l,i,j}, c_{r,i,j}, c_{o,i,j}\}_{i \in \{1, \ldots, n\}, j \in \{1, \ldots, d\}}와 함께:

- **설정**
    - 왼쪽 피연산자 \{l_i(x)\}*{i \in \{1, \ldots, n\}}를 위한 변수 다항식을 구성합니다. 모든 연산 j \in \{1, \ldots, d\}에 대해 이 다항식은 해당 계수로 계산 됩니다. 즉, l_i(j) = c*{l,i,j}이고, 오른쪽 피연산자와 출력도 마찬가지입니다.
    - 무작위 s, \alpha를 샘플링합니다.
    - t(x) = (x - 1)(x - 2) \cdots (x - d)와 암호화된 값 g^{t(s)}를 계산합니다.
    - 증명 키를 계산합니다: \left( \left\{ g^{s^k} \right\}*{k \in [d]}, \left\{ g^{l_i(s)}, g^{r_i(s)}, g^{o_i(s)}, g^{\alpha l_i(s)}, g^{\alpha r_i(s)}, g^{\alpha o_i(s)} \right\}*{i \in \{1, \ldots, n\}} \right)
    - 검증 키를 계산합니다: \left(g^{t(s)}, g^{\alpha}\right)
- **증명**
    - 함수 f(*) 를 계산하고 이에 해당하는 변수 값 \{v_i\}_{i \in \{1, \ldots, n\}}를 계산합니다.
    - h(x) = \frac{L(x) \times R(x) - O(x)}{t(x)} 를 계산합니다. 여기서 L(x) = \sum_{i=1}^{n} v_i \cdot l_i(x) , R(x) , O(x) 도 유사하게 계산합니다.
    - 변수 값을 할당하고 피연산자 다항식을 합산합니다:
        
        g^L(s) = \left(g^{l_1(s)}\right)^{v_1} \cdots \left(g^{l_n(s)}\right)^{v_n}, \quad g^R(s) = \prod_{i=1}^{n} \left(g^{r_i(s)}\right)^{v_i}, \quad g^O(s) = \prod_{i=1}^{n} \left(g^{o_i(s)}\right)^{v_i}
        
    - 쉬프트된 다항식에 변수 값을 할당합니다:
        
        g^{\alpha L(s)} = \prod_{i=1}^{n} \left(g^{\alpha l_i(s)}\right)^{v_i}, \quad g^{\alpha R(s)} = \prod_{i=1}^{n} \left(g^{\alpha r_i(s)}\right)^{v_i}, \quad g^{\alpha O(s)} = \prod_{i=1}^{n} \left(g^{\alpha o_i(s)}\right)^{v_i}
        
    - 제공된 s 의 거듭제곱을 사용하여 암호화된 값 g^{h(s)} 를 계산합니다: \left\{ g^{s^k} \right\}_{k \in [d]}
    - 증명을 설정합니다: \left(g^L(s), g^R(s), g^O(s), g^{\alpha L(s)}, g^{\alpha R(s)}, g^{\alpha O(s)}, g^h(s)\right)
- **검증**
    - 증명을 \left(g^L, g^R, g^O, g^{L'}, g^{R'}, g^{O'}, g^h\right)로 해석합니다.
    - 변수 다항식 제한 검사:
        
        e(g^L, g^\alpha) = e(g^{L'}, g), \quad e(g^R, g^\alpha) = e(g^{R'}, g), \quad e(g^O, g^\alpha) = e(g^{O'}, g)
        
    - 유효한 연산 검사:
        
        e(g^L, g^R) = e(g^{t(s)}, g^h) \cdot e(g^O, g)
        

모든 변수 다항식 \{l_i(x), r_i(x), o_i(x)\}_{i \in \{1, \ldots, n\}}와 타겟 다항식 t(x)의 집합을 **2차 산술 프로그램**(quadratic arithmetic program, QAP)이라고 합니다.

우리는 이제 대부분의 일반 계산을 검증할 수 있는 프로토콜을 갖췄습니다! 그러나 해결해야 할 두 가지 추가적인 보안 고려 사항이 있습니다. 이는 다음 시간에 다룹니다.

### 4.9.1 피연산자 및 출력의 상호 교환 불가능성

변수 다항식의 제한에 대해 동일한 α를 모든 피연산자에 사용하기 때문에 증명자는 다음과 같은 방식으로 행동할 수 있습니다:

- 다른 피연산자의 변수 다항식을 사용하는 것, 예를 들어 L'(s) = o1(s) + r1(s) + r5(s) + ...
- 피연산자 다항식을 완전히 교환하는 것, 예를 들어 O(s)와 L(s)를 교환하여 O(s) × R(s) = L(s)와 같은 연산을 수행하는 것
- 동일한 피연산자 다항식을 재사용하는 것, 예를 들어 L(s) × L(s) = O(s)

이러한 상호 교환 가능성은 증명자가 실행을 변경하고 실제로 다른 계산을 증명할 수 있게 합니다. 이러한 행동을 방지하는 명백한 방법은 각 피연산자에 대해 다른 α를 사용하는 것입니다. 구체적으로 우리는 다음과 같이 수정합니다:

- **설정**
    - α 대신 무작위로 αl, αr, αo를 샘플링
    - 해당 "이동"을 계산 \{g^{\alpha_l} l_i(s), g^{\alpha_r} r_i(s), g^{\alpha_o} o_i(s)\} \ i ∈ \{1...n\}
    - 증명 키:
        
        \left(
        \{ g^{sk} \} \ k ∈ [d], \{ g^{l_i(s)}, g^{r_i(s)}, g^{o_i(s)}, g^{\alpha_l l_i(s)}, g^{\alpha_r r_i(s)}, g^{\alpha_o o_i(s)} \} \ i ∈ \{1...n\}
        \right)
        
    - 검증 키:
        
        (g^{t(s)}, g^{\alpha_l}, g^{\alpha_r}, g^{\alpha_o})
        
- **증명**
    - "이동된" 다항식에 변수를 할당
        
        g^{\alpha_l L(s)} = \prod_{i=1}^{n} (g^{\alpha_l l_i(s)})^{v_i}, \quad g^{\alpha_r R(s)} = \prod_{i=1}^{n} (g^{\alpha_r r_i(s)})^{v_i}, \quad g^{\alpha_o O(s)} = \prod_{i=1}^{n} (g^{\alpha_o o_i(s)})^{v_i}
        
    - 증명 세트:
        
        (g^{L(s)}, g^{R(s)}, g^{O(s)}, g^{\alpha_l L(s)}, g^{\alpha_r R(s)}, g^{\alpha_o O(s)}, g^{h(s)})
        
- **검증**
    - 변수 다항식 제한 확인:
        
        e(g^L, g^{\alpha_l}) = e(g^{L'}, g), \quad e(g^R, g^{\alpha_r}) = e(g^{R'}, g), \quad e(g^O, g^{\alpha_o}) = e(g^{O'}, g)
        

이제 αl, αr, αo를 증명자가 알지 못하므로 다른 피연산자의 변수 다항식을 사용하는 것이 불가능합니다.

### 4.9.2 피연산자 간의 변수 일관성

어떤 변수 v_i에 대해 우리는 해당 피연산자의 변수 다항식에 값을 할당해야 합니다. 즉, (g^{l_i(s)})^{v_i}, (g^{r_i(s)})^{v_i}, (g^{o_i(s)})^{v_i}와 같이 할당해야 합니다. 각 피연산자 다항식의 유효성이 개별적으로 확인되기 때문에, 대응하는 변수 다항식에서 동일한 변수 값을 사용하도록 강제할 필요는 없습니다. 이는 왼쪽 피연산자에서 변수 v_1의 값이 오른쪽 피연산자 또는 출력에서의 변수 v_1의 값과 다를 수 있음을 의미합니다.

우리는 이미 변수 다항식에서와 같이 다항식을 제한하는 익숙한 접근 방식을 통해 피연산자 간 변수 값의 일관성을 강제할 수 있습니다. 만약 모든 피연산자에 걸쳐 "이동된 체크섬" 변수 다항식을 만들 수 있다면, 증명자는 동일한 값을 할당하도록 제약을 받게 됩니다. 검증자는 각 변수에 대한 다항식을 하나로 결합하여 (g^{l_i(s)} + r_i(s) + o_i(s))로 만들고, 이를 다른 무작위 값 \beta로 이동시키면 (g^{\beta(l_i(s) + r_i(s) + o_i(s))})가 됩니다. 이 이동된 다항식들은 변수 다항식과 함께 변수 값 할당을 위해 증명자에게 제공됩니다:

(g^{l_i(s)})^{v_{l,i}}, (g^{r_i(s)})^{v_{r,i}}, (g^{o_i(s)})^{v_{o,i}}, (g^{\beta(l_i(s) + r_i(s) + o_i(s))})^{v_{\beta,i}}

그리고 \beta는 암호화되어 검증 키 g^{\beta}에 추가됩니다. 이제 모든 v_i의 값이 동일하다면 (즉, v_{l,i} = v_{r,i} = v_{o,i} = v_{\beta,i}이고 i ∈ \{1, . . . , n\}), 방정식이 성립합니다:

e(g^{v_{l,i} \cdot l_i(s)} \cdot g^{v_{r,i} \cdot r_i(s)} \cdot g^{v_{o,i} \cdot o_i(s)}, g^{\beta}) = e(g^{v_{\beta,i} \cdot \beta(l_i(s) + r_i(s) + o_i(s))}, g)

이것은 유용한 일관성 검사이지만, l(s), r(s), o(s) 중 적어도 두 개가 동일한 평가 값을 갖거나 한 다항식이 다른 다항식으로 나누어질 가능성이 무시할 수 없으므로, 증명자가 v_{l,i}, v_{r,i}, v_{o,i}, v_{\beta,i} 값을 조작하여 방정식을 성립시키면서 최소 두 개의 값이 다를 수 있습니다. 예를 들어, 단일 연산에서 l(x) = r(x)인 경우를 고려해 보겠습니다. 이 두 평가를 w = l(s) = r(s) 및 y = o(x)라고 합니다. 방정식은 다음과 같이 나타납니다:

\beta(v_l w + v_r w + v_o y) = v_{\beta} \cdot \beta(w + w + y)

이러한 형태는 임의의 v_r와 v_o에 대해 v_{\beta} = v_o, v_l = 2v_o - v_r로 설정할 수 있으며, 이는 다음과 같이 변환됩니다:

\beta(2v_o w - v_r w + v_r w + v_o y) = v_o \cdot \beta(2w + y)

따라서 이러한 일관성 전략은 효과적이지 않습니다. 이를 완화하는 방법은 각 피연산자에 대해 다른 \beta를 사용하여 피연산자의 변수 다항식이 예측할 수 없는 값을 갖도록 하는 것입니다. 다음은 프로토콜 수정 사항입니다:

- **설정**
    - 무작위로 \beta_l, \beta_r, \beta_o 샘플링
    - 변수 일관성 다항식을 계산, 암호화하여 증명 키에 추가:
        
        \{g^{\beta_l l_i(s) + \beta_r r_i(s) + \beta_o o_i(s)}\}_{i∈{1,...,n}}
        
    - \beta를 암호화하여 검증 키에 추가: g^{\beta_l}, g^{\beta_r}, g^{\beta_o}
- **증명**
    - 변수 일관성 다항식에 변수 값을 할당:
        
        g^{z_i(s)} = (g^{\beta_l l_i(s) + \beta_r r_i(s) + \beta_o o_i(s)})^{v_i} \quad \text{for } i ∈ \{1, . . . , n\}
        
    - 암호화된 공간에서 할당된 다항식을 추가:
        
        g^{Z(s)} = \prod_{i=1}^{n} g^{z_i(s)} = g^{\beta_l L(s) + \beta_r R(s) + \beta_o O(s)}
        
    - 증명에 추가: g^{Z(s)}
- **검증**
    - 제공된 피연산자 다항식과 "체크섬" 다항식 간의 일관성을 확인:
        
        e(g^{L}, g^{\beta_l}) \cdot e(g^{R}, g^{\beta_r}) \cdot e(g^{O}, g^{\beta_o}) = e(g^{Z}, g)
        
    - 이는 다음과 동일합니다:
        
        e(g, g)^{\beta_l L + \beta_r R + \beta_o O} = e(g, g)^{Z}
        

같은 변수 값 변경 기술은 이러한 구성에서는 실패할 것입니다. 왜냐하면 다른 \beta들이 동일한 다항식을 조작하기에는 호환되지 않기 때문입니다. 그러나 공개된 g^{\beta_l}, g^{\beta_r}, g^{\beta_o} 때문에 제로 인덱스 계수를 변경할 수 있는 유사한 결함이 있습니다. 구체적으로 변수 다항식의 제로 인덱스 계수는 s에 의존하지 않습니다. 즉, g^{\beta_l s_0} = g^{\beta_l}입니다.

### 4.9.3 변수 및 변수 일관성 다항식의 비변조성

### 변수 다항식의 변조 가능성

다음 두 연산을 예로 들어 4.1 항목을 설명하겠습니다:

- a \times 1 = b
- 3a \times 1 = c

기대되는 결과는  b = a 와  c = 3a 이며, 명확한 관계는  c = 3b 입니다. 이는 왼쪽 피연산자의 변수 다항식이  l_a(1) = 1 과  l_a(2) = 3 의 평가값을 가진다는 것을 의미합니다.  l_a(x) 의 형태와 관계없이 증명자는 수정된 다항식  l'_a(x) = a \cdot l_a(x) + 1 을 제공함으로써 불균형하게  a 의 값을 할당할 수 있습니다. 따라서 평가값은  l'_a(1) = a + 1 과  l'_a(2) = 3a + 1 이 되어, 결과는  b = a + 1 과  c = 3a + 1 이며,  c \neq 3b 가 되어 서로 다른 연산에 대해  a 의 값이 다르다는 의미가 됩니다.

증명자는  g^{\alpha_l} 와  g^{\beta_l} 에 접근할 수 있으므로, 올바른 피연산자 다항식과 변수 값 일관성 검사를 모두 만족시킬 수 있습니다:

- **증명**:
    - 변수를 불균형하게 할당하여 왼쪽 피연산자 다항식을 형성:
        
        L(x) = a \cdot l_a(x) + 1
        
    - 오른쪽 피연산자와 출력 다항식은 일반적으로 형성:
        
        R(x) = r_1(x), \quad O(x) = b \cdot o_b(x) + c \cdot o_c(x)
        
    - 나머지 h(x) 계산:
        
        h(x) = \frac{L(x) \cdot R(x) - O(x)}{t(x)}
        
    - 암호화 계산:
        
        g^{L(s)} = (g^{l_a(s)})^a \cdot g^1
        
        오른쪽 피연산자와 출력에 대해서는 일반적으로:
        
        g^{R(s)}, \quad g^{O(s)}
        
    - α-시프트 계산:
        
        g^{\alpha L(s)} = (g^{\alpha l_a(s)})^a \cdot g^{\alpha}
        
        오른쪽 피연산자와 출력에 대해서는 일반적으로:
        
        g^{\alpha R(s)}, \quad g^{\alpha O(s)}
        
    - 변수 일관성 다항식 계산:
        
        g^{Z(s)} = \prod_{i \in \{1,a,b,c\}} (g^{\beta_l l_i(s) + \beta_r r_i(s) + \beta_o o_i(s)})^i \cdot g^{\beta_l} = g^{\beta_l (L(s) + 1) + \beta_r R(s) + \beta_o O(s)}
        
        여기서 첨자  i 는 해당 변수의 기호를 나타내고, 지수  i 는 변수의 값을 나타냅니다. 또한 정의되지 않은 변수 다항식은 0과 같습니다.
        
    - 증명 세트 설정:
        
        (g^{L(s)}, g^{R(s)}, g^{O(s)}, g^{\alpha_l L(s)}, g^{\alpha_r R(s)}, g^{\alpha_o O(s)}, g^{Z(s)} g^{h(s)})
        
- **검증**:
    - 변수 다항식 제한 검사:
        
        e(g^{L'}, g) = e(g^{L}, g^{\alpha}) \Rightarrow e(g^{\alpha a \cdot l_a(s) + \alpha}, g) = e(g^{a l_a(s) + 1}, g^{\alpha})
        
        오른쪽 피연산자와 출력에 대해서는 일반적으로:
        
        g^{R'}, \quad g^{O'}
        
    - 변수 값 일관성 검사:
        
        e(g^{L}, g^{\beta_l}) \cdot e(g^{R}, g^{\beta_r}) \cdot e(g^{O}, g^{\beta_o}) = e(g^{Z}, g) \Rightarrow e(g, g)^{(a \cdot l_a + 1) \beta_l + R \beta_r + O \beta_o} = e(g, g)^{\beta_l (L + 1) + \beta_r R + \beta_o O}
        
    - 유효한 연산 검사:
        
        e(g^{L}, g^{R}) = e(g^{t}, g^{h}) \cdot e(g^{O}, g)
        

### 비변조성

변조 문제를 해결하는 한 가지 방법은 설정 단계에서 무작위 비밀 \gamma를 곱하여 검증 키의 g^{\beta_l}, g^{\beta_r}, g^{\beta_o}를 g^{Z(s)}와 호환되지 않도록 만드는 것입니다: g^{\beta_l \gamma}, g^{\beta_r \gamma}, g^{\beta_o \gamma}. 이렇게 마스킹된 암호화는 Z(s)가 \gamma의 배수가 아니기 때문에 gZ(s)를 의미 있는 방식으로 수정하는 것이 불가능하게 합니다. 예를 들어, gZ(s) \cdot gv' \cdot \beta_l \gamma = g^{\beta_l(L(s) + v'\gamma) + \beta_r R(s) + \beta_o O(s)}. 증명자는 \gamma를 모르기 때문에 수정은 무작위로 이루어집니다.

이 수정은 프로토콜에서 변수 값 일관성 검사 방정식을 조정하여 Z(s)에 \gamma를 곱해야 합니다:

- **설정**
    - 무작위로 \beta_l, \beta_r, \beta_o, \gamma를 샘플링
    - 검증 키 설정: \ldots, g^{\beta_l \gamma}, g^{\beta_r \gamma}, g^{\beta_o \gamma}, g^{\gamma}
- **증명**
    - \ldots
- **검증**
    - 변수 값 일관성 검사가 성립해야 합니다:
        
        e(g^L, g^{\beta_l \gamma}) \cdot e(g^R, g^{\beta_r \gamma}) \cdot e(g^O, g^{\beta_o \gamma}) = e(g^Z, g^{\gamma})
        

변수 다항식이 0차 다항식인 경우는 제외해야 합니다 (예: l_1(x) = 1x^0). 그렇지 않으면 증명 키의 변수 일관성 다항식 \{g^{\beta_l l_i(s) + \beta_r r_i(s) + \beta_o o_i(s)}\}_{i \in \{1, \ldots, n\}}에서 \beta의 암호화를 노출할 수 있습니다. 예를 들어 l_1(x) = 1, r_1(s) = 0, o_1(s) = 0인 경우 g^{\beta_l l_1(s) + \beta_r r_1(s) + \beta_o o_1(s)} = g^{\beta_l}이 됩니다.

유사하게 \alpha를 마스킹하여 변수 다항식의 변조 가능성을 해결할 수도 있습니다. 그러나 이는 필요하지 않습니다. 왜냐하면 변수 다항식의 어떤 수정도 변수 일관성 다항식에 반영되어야 하며, 이는 수정할 수 없기 때문입니다.

### 4.9.4 변수 값 일관성 검사의 최적화

변수 값 일관성 검사는 이제 효과적이지만, 이는 4개의 비용이 많이 드는 페어링 연산과 검증 키에 4개의 새로운 항을 추가합니다. Pinocchio 프로토콜 [Par+13]은 각 피연산자에 대한 생성기를 선택하여 "이동"을 내재화하는 영리한 방법을 사용합니다:

- **설정**
    - 무작위로 \beta, \gamma, \rho_l, \rho_r를 샘플링하고 \rho_o = \rho_l \cdot \rho_r로 설정
    - 생성기를 설정:
        
        g_l = g^{\rho_l}, \quad g_r = g^{\rho_r}, \quad g_o = g^{\rho_o}
        
    - 증명 키 설정:
        
        \left( \{ g^{sk} \}_{k \in [d]}, \{ g^{l_i(s)}_l, g^{r_i(s)}_r, g^{o_i(s)}_o, g^{\alpha_l l_i(s)}_l, g^{\alpha_r r_i(s)}_r, g^{\alpha_o o_i(s)}_o, g^{\beta l_i(s)}_l \cdot g^{\beta r_i(s)}_r \cdot g^{\beta o_i(s)}_o \} \right)
        
    - 검증 키 설정:
        
        (g^{t(s)}_o, g^{\alpha_l}, g^{\alpha_r}, g^{\alpha_o}, g^{\beta \gamma}, g^{\gamma})
        
- **증명**
    - 변수 값을 할당:
        
        g^{Z(s)} = \prod_{i=1}^{n} (g^{\beta l_i(s)}_l \cdot g^{\beta r_i(s)}_r \cdot g^{\beta o_i(s)}_o)^{v_i}
        
- **검증**
    - 변수 다항식 제한 검사:
        
        e(g^{L'}_l, g) = e(g^{L}_l, g^{\alpha_l}), \quad \text{유사하게 } g^{R}_r, g^{O}_o \text{에 대해서도}
        
    - 변수 값 일관성 검사:
        
        e(g^{L}_l \cdot g^{R}_r \cdot g^{O}_o, g^{\beta \gamma}) = e(g^{Z}, g^{\gamma})
        
    - 유효한 연산 검사:
        
        e(g^{L}_l \cdot g^{R}_r) = e(g^{t}_o, g^{h}) \cdot e(g^{O}_o, g)
        
        이는 다음과 같습니다:
        
        e(g, g)^{\rho_l \rho_r LR} = e(g, g)^{\rho_l \rho_r th + \rho_l \rho_r O}
        

이러한 생성기의 무작위화는 보안을 추가로 강화하여 변수 다항식의 변조 가능성(4.1 항목에 설명됨)을 비효과적으로 만듭니다. 의도된 변경은 \rho_l, \rho_r 또는 \rho_o의 배수여야 하지만, 원시 버전이나 암호화된 버전은 사용 불가능합니다 (이전과 같이 0차 변수 다항식을 다루지 않는다고 가정합니다. 이는 암호화된 버전을 노출할 수 있습니다).

이 최적화는 검증 키에서 두 요소를 줄이고, 검증 단계에서 두 개의 페어링 연산을 제거합니다.

**참고**: Jens Groth의 2016년 논문 [Gro16]에는 추가적인 프로토콜 개선이 있습니다.

### 4.10 제약조건

우리의 분석은 주로 연산의 개념에 중점을 두고 있습니다. 그러나 프로토콜은 실제로 "계산"을 하는 것이 아니라, 계산 결과가 올바른지 확인만 할 뿐입니다. 그래서 우리는 이러한 수식을 제약 조건이라고 부릅니다. 이는 증명자가 검증자가 정의한 "프로그램"의 유효한 값을 제공하도록 증명자를 제한하는 것입니다. 다수의 제약 조건이 모여 제약 조건 시스템을 형성하며 우리의 경우 순위 1 제약 조건 시스템 또는 R1CS을 사용합니다.

따라서 우리는 다른 관계를 보장하기 위해 제약 조건을 사용할 수도 있습니다. 예를 들어, 변수 a의 값이 0 또는 1(즉, 이진수)만 될 수 있도록 하려면 다음과 같은 간단한 제약 조건을 사용할 수 있습니다:

a \times a = a

또한 a의 값을 2로만 제약할 수도 있습니다:

(a - 2) \times 1 = 0

더 복잡한 예로, 숫자 a가 4비트 숫자인지 보장하도록 제약 조건을 걸 수 있습니다. 즉, a를 4비트로 표현할 수 있어야 합니다. 4비트 숫자는 2^4가지 조합을 나타낼 수 있으며, 따라서 0에서 15까지의 16개의 숫자를 나타낼 수 있습니다. 이진수는 2의 거듭제곱의 합으로 나타낼 수 있습니다. 예를 들어, 1011(이진수)는 1 \cdot 2^3 + 0 \cdot 2^2 + 1 \cdot 2^1 + 1 \cdot 2^0 = 11 (십진수)입니다.

따라서 a가 4비트 숫자라면, a = b_3 \cdot 2^3 + b_2 \cdot 2^2 + b_1 \cdot 2^1 + b_0 \cdot 2^0이 되어야 하며, 여기서 b_0, b_1, b_2, b_3는 이진 값입니다. 제약 조건은 다음과 같을 수 있습니다:

1 : a \times 1 = 8 \cdot b_3 + 4 \cdot b_2 + 2 \cdot b_1 + 1 \cdot b_0

그리고 b_0, b_1, b_2, b_3가 이진 값일 수 있도록 하기 위해 다음을 추가해야 합니다:

2 : b_0 \times b_0 = b_0

3 : b_1 \times b_1 = b_1

4 : b_2 \times b_2 = b_2

5 : b_3 \times b_3 = b_3

이와 같이 정교한 제약 조건을 적용하여 사용되는 변수 값이 규칙을 준수하도록 할 수 있습니다. 중요한 점은 위의 제약 조건 1이 현재 연산의 구성에서는 가능하지 않다는 것입니다:

\sum_{i=1}^{n} c_{l,i} \cdot v_i \times \sum_{i=1}^{n} c_{r,i} \cdot v_i = \sum_{i=1}^{n} c_{o,i} \cdot v_i

값 1(및 이전 제약 조건의 2)은 c \cdot v_{1}을 통해 표현되어야 하기 때문입니다. 여기서 c는 증명 키에 포함될 수 있지만, v_{1}은 증명자가 제공하는 값일 수 있습니다. 우리는 c = 0으로 설정하여 c \cdot v를 0으로 강제할 수 있지만, 현재 우리가 제한된 구성에서는 v_{1}을 1로 강제할 제약 조건을 찾기가 어렵습니다. 따라서 검증자가 v_{1}의 값을 설정할 수 있는 방법이 있어야 합니다.

### 4.11 공용 입력과 하나의 값

증명은 검증자의 입력값과 대조할 수 없으면 그 활용성이 제한될 것입니다. 예를 들어, 증명자가 두 값을 곱한 결과를 알고 싶지만 그 결과나 값을 모른다면 의미가 없기 때문입니다. 곱셈 결과가 항상 12가 되어야 한다는 식으로 값을 검증 키에 "하드코딩"하는 것이 가능하지만, 이렇게 하면 각 검증자의 입력값에 대해 별도의 키 쌍을 생성해야 합니다.

따라서 증명자가 아닌 검증자가 일부 값(입력 또는 출력 포함)을 지정할 수 있다면 더 보편적일 것입니다. 여기에는 v_{1} 값도 포함됩니다.

먼저, 증명 값 g^L(s), g^R(s), g^O(s)를 고려해봅시다. 우리는 동형 암호화를 사용하고 있기 때문에 이 값들을 보강할 수 있습니다. 예를 들어, 다음과 같은 암호화된 다항식을 추가할 수 있습니다: g^{L(s)} \cdot g^{l_v(s)} = g^{L(s) + l_v(s)}, 이는 검증자가 이미 제공된 변수 다항식에 다른 변수 l_v(s)를 추가할 수 있음을 의미합니다. 따라서 필요한 변수 다항식을 증명자가 사용할 수 있는 것에서 제외할 수 있다면, 검증자는 이러한 변수에 자신의 값을 설정할 수 있고, 계산 검사는 여전히 일치해야 합니다.

이것은 쉽게 달성할 수 있습니다. 왜냐하면 검증자는 이미 \alpha-시프트를 사용하여 증명자가 사용할 수 있는 다항식의 선택을 제한하고 있기 때문입니다. 따라서 이러한 변수 다항식은 증명 키에서 검증 키로 이동할 수 있으며, 그에 해당하는 \alpha 및 \beta 체크섬도 제거할 수 있습니다.

필요한 프로토콜 업데이트는 다음과 같습니다:

### 설정

- 모든 n개의 변수 다항식을 두 그룹으로 분리합니다:
    - 검증자의 m + 1:
        
        L_v(x) = l_0(x) + l_1(x) + \ldots + l_m(x),
        
        R_v(x)와 O_v(x)도 동일하게,
        여기서 인덱스 0은 v_{one} = 1의 값으로 예약됩니다.
        
    - 증명자의 n − m:
        
        L_p(x) = l_{m+1}(x) + \ldots + l_n(x),
        
        이며, R_p(x)와 O_p(x)도 동일합니다.
        
- 증명 키 설정:
    
    \left(
    \{ g^{s^k} \}*{k \in [d]},
    \{ g_l^{l_i}(s), g_r^{r_i}(s), g_o^{o_i}(s), g_l^{\alpha_l l_i(s)} , g_r^{\alpha_r r_i(s)} , g_o^{\alpha_o o_i(s)}, g_l^{\beta_l l_i(s)}  \cdot g_r^{\beta_r r_i(s)}  \cdot g_o^{\beta_o o_i(s)}  \}*{i \in \{ m+1, \ldots, n \}}
    \right)
    
- 검증 키에 추가:
    
    \left(
    \ldots,
    \{ g_l^{l_i(s)}, g_r^{r_i(s)}, g_o^{o_i(s)} \}_{i \in \{ 0, \ldots, m \}}
    \right)
    

### 증명

- 검증자의 다항식을 고려하여 h(x)를 계산합니다:
    
    h(x) = \frac{L(x) \cdot R(x) - O(x)}{t(x)},
    
    여기서 L(x) = L_v(x) + L_p(x), R(x)와 O(x)도 동일하게
    
- 증명 제공:
    
    \left(
    g_l^{L_p(s)}, g_r^{R_p(s)}, g_o^{O_p(s)}, g_l^{\alpha_l Lp(s)}, g_r^{\alpha_r Rp(s)}, g_o^{\alpha_o Op(s)}, g^{Z(s)}, g^{h(s)}
    \right)
    

### 검증

- 검증자의 변수 다항식 값을 할당하고 1을 추가합니다:
    
    g_l^{L_v(s)} = g_l^{l_0(s)} \cdot \prod_{i=1}^{m} (g_l^{l_i(s)})^{v_i}
    
    g_r^{R_v(s)}와 g_o^{O_v}(s)도 동일하게
    
- 변수 다항식 제한 검사:
    
    e(g_l^{L_p}, g^{\alpha_l}) = e(g_l^{L'_p}, g)
    
    g_r^{R_p}와 g_o^{O_p}도 동일하게
    
- 변수 값 일관성 검사:
    
    e(g_l^{L_p} g_r^{R_p} g_o^{O_p}, g^{\beta \gamma}) = e(g^Z, g^{\gamma})
    
- 유효 연산 검사:
    
    e(g_l^{L_v(s)} g_l^{L_p}, g_r^{R_v(s)} g_r^{R_p}) = e(g_o^{t}, g_h) \cdot e(g_o^{O_v}(s) g_o^{O_p}, g)
    

이는 증명자의 일부 변수를 검증자에게 넘기면서도 방정식의 균형을 유지하는 것입니다. 따라서 유효 연산 검사는 여전히 성립해야 하지만, 이는 증명자가 검증자가 입력으로 사용한 동일한 값을 사용했을 때만 가능합니다.

값 1은 본질적으로 중요하며, 이를 상수 항을 곱하여 어떤 숫자라도 도출할 수 있습니다. 예를 들어, a에 123을 곱하려면:

1 \cdot a \times 123 \cdot v_{1} = 1 \cdot r

### 4.12 영지식 계산 증명

범용 계산 프로토콜(섹션 4.4 연산 증명)의 도입 이후, 전환을 더 단순하게 하기 위해 영지식(zero-knowledge) 속성을 포기해야 했습니다. 지금까지 우리는 검증 가능한 계산 프로토콜을 구축했습니다.

이전에 다항식 영지식 증명을 만들기 위해 우리는 무작위 \delta-시프트를 사용했습니다. 이는 증명을 무작위와 구별할 수 없게 만듭니다(섹션 3.5):

\delta p(s) = t(s) \cdot \delta h(s)

우리가 증명하고 있는 계산으로는 위 식 대신에 다음 아래 식을 사용합니다:

L(s) \cdot R(s) - O(s) = t(s) h(s)

우리는 동일한 \delta를 사용하여 다항식을 무작위 화된 값 \delta L(s), \delta R(s), \delta O(s), \delta h^2(s)를 공급함으로써 여러 다항식에 이 접근 방식을 적용할 수 있습니다. 이는 쌍을 통해 유효한 연산 검사를 충족시킬 수 있습니다:

e(g, g) g^{\delta^2 L(s) R(s)} = e(g, g)^{\delta^2( t(s) h(s) + O(s))}

우리는 이 값들을 증명에 별도로 제공하기 때문에 동일한 \delta를 사용하면 보안이 저해된다는 문제가 있습니다.:

- 두 개의 다른 암호화된 다항식이 동일한 값을 가지는지 쉽게 식별할 수 있습니다 (예: g^{\delta L(s)} = g^{\delta R(s)} 등), 즉 일부 지식을 학습하는 것입니다.
- L(s)와 R(s) 사이의 값 차이의 잠재적 무의미성은 무차별 대입을 통해 그 차이를 인수분해할 수 있게 할 수 있습니다. 예를 들어 L(s) = 5R(s)이면 g^{L(s)} = (g^{R(s)})^i for i \in \{1,...,N\}로 반복하여 계산하면 단 5단계 만에 5배의 차이를 나타낼 수 있습니다. 동일한 무차별 대입이 암호화된 덧셈 연산에서도 수행될 수 있습니다. 예: g^{L(s)} = g^{R(s) + 5}
- 증명의 요소 간의 다른 상관 관계가 발견될 수 있습니다. 예를 들어, e(g^{\delta L(s)}, g^{\delta R(s)}) = e(g^{\delta^2 O(s)}, g)이면 L(x) \cdot R(x) = O(x) 등.

결과적으로, 각 다항식마다 다른 무작위성(\delta-s)을 가져야 합니다. 예:

\delta_l L(s) \cdot \delta_r R(s) - \delta_o O(s) = t(s) \cdot (\Delta ?  h(s))

불평등을 해결하기 위해 우리는 프로토콜을 변경하지 않고 증명 값 h(s)만 수정할 수 있습니다. 델타(\Delta)는무작위성을 상쇄하기 위해 h(s)에 적용될 수 있는 차이를 의미합니다. ?는 아무 연산자를 의미합니다. \Delta를 곱셈을 통해 적용하는 것을 선택하면(? = \times), \Delta를 찾는 것은 거의 불가능합니다. ?가 곱셈인경우 아래와 같이 표현이 가능합니다.

\Delta = \frac{\delta_l L(s) \cdot \delta_r R(s) - \delta_o O(s)}{t(s) h(s)}

우리는 \delta = \delta_l \cdot \delta_r로 설정할 수 있으며, 이는 다음과 같이 변환됩니다:

\Delta = \frac{\delta_l \delta_r (L(s) \cdot R(s) - O(s))}{t(s) h(s)} = \delta_l \delta_r

그러나, 앞서 언급했듯이, 이것은 영지식 속성을 방해합니다. 더욱 중요한 것은, 이러한 구성 방식은 검증자의 입력 다항식을 수용할 수 없다는 점입니다. 왜냐하면 입력 다항식이 해당
𝛿-s 값의 배수여야 하므로 상호작용이 필요하기 때문입니다.

우리는 평가에 무작위성을 더하는 방법을 시도 할 수 있습니다:

(L(s) + \delta_l) \cdot (R(s) + \delta_r) - (O(s) + \delta_o) = t(s) \cdot (\Delta \times h(s))

\Delta = \frac{\overbrace{L(s)R(s) - O(s)}^{t(s)h(s)} + \delta_r L(s) + \delta_l R(s) + \delta_l \delta_r - \delta_o}{t(s)h(s)} = 1 + \frac{\delta_r L(s) + \delta_l R(s) + \delta_l \delta_r - \delta_o}{t(s)h(s)}

그러나 무작위성으로 인해 \Delta는 나눌 수 없습니다. t(s)h(s)로 각 \delta 를  곱하더라도, \Delta를 곱셈으로 적용하기 때문에, \Delta는 암호화된 값(예: g^{L(s)} 등)으로 구성되므로, 쌍 없이는 g^{\Delta h(s)}를 계산할 수 없습니다.

마찬가지로 암호화된 덧셈 연산 \{g^{s^i}\}_{k \in [d]}를 사용하여 \Delta h(x)의 암호화된 평가를 계산할 수 없습니다. h(x)와 \Delta의 차수는 d 이므로, \Delta h(x)의 차수는 2d로 증가합니다. 동일한 이유로 무작위화된 피연산자 다항식 평가 g^{L(x)+ \delta_l t(x)h(x)} 또한  계산할 수 없습니다. 따라서 곱셈 연산은 불가능하므로, 덧셈 연산(? = +)을 시도해야 합니다.

(L(s) + \delta_l) \cdot (R(s) + \delta_r) - (O(s) + \delta_o) = t(s) \cdot (\Delta + h(s))

\Delta = \frac{L(s)R(s) - O(s) + \delta_r L(s) + \delta_l R(s) + \delta_l \delta_r - \delta_o - t(s)h(s)}{t(s)} \implies

\Delta = \frac{\delta_r L(s) + \delta_l R(s) + \delta_l \delta_r - \delta_o}{t(s)}

분자의 모든 항은 \delta의 배수이므로, t(s)로 곱하여 나눌 수 있도록 할 수 있습니다.

(L(s) + \delta_l t(s)) \cdot (R(s) + \delta_r t(s)) - (O(s) + \delta_o t(s)) = t(s) \cdot (\Delta + h(s))

\cancel{L(s) R(s)- O(s)}  + t(s)(\delta_r L(s) + \delta_l R(s) + \delta_l \delta_r t(s) - \delta_o) = t(s) \Delta + \cancel{t(s) h(s)}

\Delta = \delta_r L(s) + \delta_l R(s) + \delta_l \delta_r t(s) - \delta_o

이를 암호화된 공간에서 효율적으로 계산할 수 있습니다.

g^{L(s) + \delta_l t(s)} = g^{L(s)} \cdot \left( g^{t(s)} \right)^{\delta_l}, \quad \text{etc.}

g^{\Delta} = \left( g^{L(s)} \right)^{\delta_r} \cdot \left( g^{R(s)} \right)^{\delta_l} \cdot \left( g^{t(s)} \right)^{\delta_l \delta_r} g^{-\delta_o}

이는 암호화된 값을 숨기면서 유효한 연산 검사를 통과하도록 합니다.

L \cdot R - O + \textcolor{magenta}{t (\delta_r L + \delta_l R + \delta_l \delta_r t - \delta_o}) = t(s) h +\textcolor{magenta}{ t(s) (\delta_r L + \delta_l R + \delta_l \delta_r t - \delta_o})

이 구조는 균일한 무작위 \delta_l, \delta_r, \delta_o를 추가하여 통계적으로 영지식입니다.

참고: 이 접근법은 검증자의 피연산자와도 일치합니다.
g_{l}^{L_{rp} + \delta_l t} \cdot g_{l}^{L_{rv}} = g_{l}^{L_{rp} + L_{rv} + \delta_l t}  등. 따라서 유효한 연산 검사는 증명자의 다항식의 변경을 사용할 수 있지만 검증자의 값을 사용하여 관계를 찾을 수 있습니다. \Delta = \delta_r (L_p + L_v) + \delta_l (R_p + R_v) + \delta_l \delta_r t - \delta_o를 구성하는 데 필요한 추가 매개변수는 다음 섹션에서 설명합니다.

이제 "변수 다항식 제한" 및 "변수 값 일관성" 검사를 영지식 변경과 일치시키기 위해, 다음 매개변수를 증명키에 추가해야 합니다.

g_{l}^{t(s)}, \, g_{r}^{t(s)}, \, g_{O}^{t(s)}, \, g_{l}^{\alpha_l t(s)}, \, g_{r}^{\alpha_r t(s)}, \, g_{O}^{\alpha_O t(s)}, \, g_{l}^{\beta_l t(s)}, \, g_{r}^{\beta_r t(s)}, \, g_{O}^{\beta_O t(s)}

원래 피노키오 프로토콜은 주로 검증 가능한 계산에 중점을 두었으며, 영지식 속성은 덜 중요하게 다루었음을 알 수 있습니다. 이는 사소한 수정을 통해 구현이 가능합니다.

## 4.13 zk-SNARK 프로토콜

모든 점진적인 개선을 고려하여 최종 영지식 간결 비대화 논증 프로토콜의 구성 요소는 다음과 같습니다 (영지식 구성 요소는 선택 사항이며 다른 색으로 강조 표시되어 있습니다):

### 설정

- 생성자 g와 암호학적 쌍 e 선택
- f(u) = y 함수에 대해, 총 n개의 변수 중 m개가 입력/출력 변수인 경우, 다항식 형태로 변환:
    
    \{(l_i(x), r_i(x), o_i(x))\}_{i \in \{0,...,n\}}, t(x)\ \text{차수 } d \ \text{크기 } n+1
    
- 무작위 s, \rho_l, \rho_r, \alpha_l, \alpha_r, \alpha_o, \beta, \gamma 샘플링
- \rho = \rho_l \cdot \rho_r 설정 및 피연산자 생성기 설정:
    
    g_l = g^{\rho_l}, g_r = g^{\rho_r}, g_o = g^{\rho}, g = g^{\rho}
    
- 증명 키 설정:

\left(
\left\{ g^{s^k} \right\}*{k \in [d]}, \,
\left\{ g*{l_i}(s), g_{r_i}(s), g_{o_i}(s) \right\}*{i \in \{0, \ldots, n\}}, \,
\left\{ g*{l}^{\alpha_l i(s)}, g_{r}^{\alpha_r i(s)}, g_{o}^{\alpha_o i(s)}, g_{l}^{\beta_l i(s)}, g_{r}^{\beta_r i(s)}, g_{o}^{\beta_o i(s)} \right\}*{i \in \{m+1, \ldots, n\}}, \,
\textcolor{magenta}{
g*{l}^{t(s)}, g_{r}^{t(s)}, g_{o}^{t(s)}, g_{l}^{\alpha_l t(s)}, g_{r}^{\alpha_r t(s)}, g_{o}^{\alpha_o t(s)}, g_{l}^{\beta_l t(s)}, g_{r}^{\beta_r t(s)}, g_{o}^{\beta_o t(s)}
}
\right)

- 검증 키에 추가:

\left(
g_{l}^{1}, g_{o}^{t(s)}, \,
\left\{ g_{l_i}(s), g_{r_i}(s), g_{o_i}(s) \right\}_{i \in \{0, \ldots, m\}}, \,
g^{\alpha_l}, g^{\alpha_r}, g^{\alpha_o}, g^{\gamma}, g^{\beta \gamma}
\right)

### 증명

- 입력 u에 대해 f(u)의 계산을 실행하여 중간 변수들에 대한 값 \{v_i\}_{i \in \{m+1,...,n\}} 얻기
- 모든 값을 암호화되지 않은 변수 다항식 L(x) = l_0(x) + \sum_{i=1}^{n} u_i \cdot l_i(x)에 할당, R(x)와 O(x)도 동일하게
- 무작위 \delta_l, \delta_r, \delta_o 샘플링
- h(x) 찾기:
    
    h(x) = \frac{L(x)R(x) - O(x)}{t(x)} + \delta_l L(x) + \delta_r R(x) + \delta_r \delta_l t(x) - \delta_o
    
- 증명자의 변수 값을 암호화된 변수 다항식에 할당하고 영지식 \delta-시프트를 적용합니다:

g_{l}^{L_p(s)} = \left( \textcolor{magenta}{g_{l}^{t(s)}} \right)^{\delta_l} \cdot \prod_{i=m+1}^{n} \left( g_{l_i(s)} \right)^{v_i} \quad \text{and similarly} \quad g_{r}^{R_p(s)}, \, g_{o}^{O_p(s)}

- \alpha-시프트 쌍을 할당합니다:

g_{l}^{L_p'(s)} = \left( \textcolor{magenta}{g_{l}^{\alpha_l t(s)}} \right)^{\delta_l} \cdot \prod_{i=m+1}^{n} \left( g_{l_i(s)}^{\alpha_l} \right)^{v_i} \quad \text{and similarly} \quad g_{r}^{R_p'(s)}, \, g_{o}^{O_p'(s)}

- 변수 값 일관성 다항식을 할당합니다:

g^{Z(s)} = \left( \textcolor{magenta}{g_{l}^{\beta t(s)}} \right)^{\delta_l} \left( \textcolor{magenta}{g_{r}^{\beta t(s)}} \right)^{\delta_r} \left( \textcolor{magenta}{g_{o}^{\beta t(s)}} \right)^{\delta_o} \cdot \prod_{i=m+1}^{n} \left( g_{l_i(s)}^{\beta} g_{r_i(s)}^{\beta} g_{o_i(s)}^{\beta} \right)^{v_i}

- 증명을 계산합니다:

\left( g_{l}^{L_p(s)}, g_{r}^{R_p(s)}, g_{o}^{O_p(s)}, g_{o}^{h(s)}, g_{l}^{L_p'(s)}, g_{r}^{R_p'(s)}, g_{o}^{O_p'(s)}, g^{Z(s)} \right)

### 검증

- 제공된 증명을 다음과 같이 파싱합니다:

\left( g_{l}^{L_p}, g_{r}^{R_p}, g_{o}^{O_p}, g^{h}, g_{l}^{L_p'}, g_{r}^{R_p'}, g_{o}^{O_p'}, g^{Z} \right)

- 검증자의 암호화된 다항식에 입력/출력 값을 할당하고 1을 추가합니다:

g_{l}^{L_v(s)} = g_{l_0(s)} \cdot \prod_{i=1}^{m} \left( g_{l_i(s)} \right)^{v_i} \quad \text{and similarly for} \quad g_{r}^{R_v(s)} \quad \text{and} \quad g_{o}^{O_v(s)}

- 변수 다항식 제한 검사:

e\left( g_{l}^{L_p}, g^{\alpha_l} \right) = e\left( g_{l}^{L_p'}, g \right) \quad \text{and similarly for} \quad g_{r}^{R_p} \quad \text{and} \quad g_{o}^{O_p}

- 변수 값 일관성 검사:

e\left( g_{l}^{L_p} g_{r}^{R_p} g_{o}^{O_p}, g^{\beta \gamma} \right) = e\left( g^{Z}, g^{\gamma} \right)

- 유효 연산 검사:

e\left( g_{l}^{L_p} g_{l}^{L_v(s)}, g_{r}^{R_p} g_{r}^{R_v(s)} \right) = e\left( g_{o}^{t(s)}, g^{h} \right) \cdot e\left( g_{o}^{O_p} g_{o}^{O_v(s)}, g \right)
