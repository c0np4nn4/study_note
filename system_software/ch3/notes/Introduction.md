# 서문
- 컴퓨터는 `기계어`를 실행한다.
- 이  `기계어`는 low-level operation을 인코딩한 bytes의 연속이다.
- 컴파일러는 일련의 과정을 통해 이 `기계어`를 생성한다.
- 일련의 과정은 아래의 단계들을 기반으로 진행된다.
	- 프로그래밍 언어 규칙
	- 컴퓨터 시스템의 Instruction Set
	- 운영체제의 convention
- `GCC` 컴파일러는 *assembly code* 의 형태의 결과물을 생성한다.
- 이번 장에서는 이 `기계어`와 `assembly-code`에 대해 자세히 살펴본다.

---

- high-level language 에서 코딩을 하게 되면, machine code와 같은 low-level과는 거리를 갖게 된다.
- 반대로, assembly-code 와 같은 low-level 에서 코딩을 하게 되면 low-level instruction을 잘 알아야 한다.
- *생산성*에 있어서는 High-Level Language 를 이용하는 것이 압도적으로 좋다.
- 또, *이식성*에 있어서도 machine specific assembly-code 의 경우는 압도적으로 불리하다.

---

- 따라서, 이번 장은 **코딩**하는 것이 아니라 **이해**할 줄 아는 것이 목표로 두는 것이 바람직하다.
- 컴파일러를 적절한 parameter 와 함께 실행하면 assembly-code 형태의 결과물을 확인할 수 있다.
- 이 코드를 보고 분석함으로써, 프로그램의 비효율적인 부분을 파악할 수도 있다.
- 프로그램의 퍼포먼스를 극대화하고자 할 때, 이러한 방법을 활용할 수도 있다.
- 또, High-Level 에서 가리고(hide) 있는 컴퓨터의 동작 과정을 확인할 수도 있다.
- concurrent programming 의 경우처럼 low-level 에서 다뤄지는 데이터를 파악하는 것이 중요한 순간에 이러한 능력은 요긴하게 쓰일 것이다.
- 또, Vulnerability exploiting 에 관해서도 low-level 에 관한 지식이 없다면 이를 이해하기가 힘들다.

---

- 상기했듯이, 이번 장에서는 Assembly-code 를 **읽는** 것에 중점을 둔다.
- 또, assembly-code 와 연관된 `C`언어를 통해 컴파일러가 어떻게 machine code 를 만드는지 살펴본다.
- `reverse engineering` 을 하듯이 학습이 진행될 예정이다.
- 또, `x86-64` 기계어를 기반으로 학습을 진행한다.
