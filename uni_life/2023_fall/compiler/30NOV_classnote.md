$\text{First} \subset (T \cup \epsilon)$

$\text{Follow} \subset (T \cup <span>$</span>)$

---

# LL(1) Grammar
- LL(1) Condition
  - 표 만들 때, 충돌이 일어나지 않을 조건
  - $A \Rightarrow \alpha | \beta$
  - $FIRST(\alpha) \cap FIRST(\beta) = 0$
  - $\beta$가 $\epsilon$으로 유도 된다면, $FIRST(\alpha) \cap FOLLOW(A) = 0$
