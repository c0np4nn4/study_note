# Simple-Rust 언어 사용자 가이드
Simple-Rust는 Rust 프로그래밍 언어를 모델로 한 간소화된 언어입니다. 
이 언어는 사칙연산 계산, 형식화된 문자열 출력, 그리고 Rust의 핵심 개념 중 하나인 소유권 시스템을 구현합니다.

## 기능
- **사칙연산**: Simple-Rust는 기본적인 사칙연산을 지원합니다. 변수에 저장된 값을 사용하여 연산을 수행할 수 있습니다.
- **형식화된 출력**: `println` 매크로를 사용하여 형식화된 문자열을 출력할 수 있습니다. 이는 여러 개의 `{}` 플레이스홀더를 포함한 문자열에 대응할 수 있도록 만들어졌습니다.
- **소유권**: Simple-Rust는 Rust의 소유권 개념을 구현합니다. 이를 통해 메모리 안전성과 데이터 레이스 방지를 위한 규칙을 적용할 수 있습니다.

## 사용 방법

### 사칙연산

변수에 값을 할당하고 이를 사용하여 사칙연산을 수행할 수 있습니다:

```srs
let a: i32 = 10;
let b: i32 = 5;
let summ: i32 = a + b;  // 15
let diff: i32 = a - b;  // 5
let prdt: i32 = a * b;  // 50
let qtnt: i32 = a / b;  // 2
```

### 형식화된 출력

`println` 매크로를 사용하여 변수를 포함한 문자열을 출력할 수 있습니다:

```srs
let str_1: str = "Hello";
let str_2: str = "World";
let str_3: str = ", ";
println!("msg: {}{}{}!", str_1, str_3, str_2); // Hello, World!
```

### 소유권

Simple-Rust에서는 변수가 값을 소유합니다. 값의 소유권을 다른 변수로 이전할 수 있습니다:

```srs
let old_owner: i32 = 10000;
let new_owner: i32 = old_owner;

// below code will be panic!
// println!("old_owner: {}", old_owner);

println!("new_owner: {}", new_owner);
```

## 빌드 및 실행

소스 코드를 컴파일하고 실행하는 방법은 다음과 같습니다:

1. 소스 파일을 작성합니다: `example.srs`.
2. 인터프리터를 이용해 파일을 실행합니다: 

### windows
`simple_rs example.srs`.

### linux
`./simple_rs example.srs`.

### 예시 코드

예시 코드를 examples 폴더 아래에서 확인할 수 있습니다.

### windows
`simple_rs .\example\example.srs`.

### linux
`./simple_rs ./example/example.srs`.
