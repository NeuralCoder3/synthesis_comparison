# Synthesis

Synthesis is complicated.
Solving ILP and SMT queries is NP-complete.
Unbounded cases (as are necessary for more complicated logics or when involving loops/recursion) are undecidable.

However, there are many tools working surprisingly well for many cases.
Currently, synthesis remains an open problem.
Most tools only generate tiny programs/fragments with the desired properties.

We take a look at the current state of tooling with their domain of operation,
results and guarantees on these results, description of the technique, requirements,
implementations, and maximal instance size on example problems.

We inspect the following techniques:
- Reinforcement Learning
    - with LLM
    - MCTS
- AI Planning
- Genetic Programming
    - Genetic Neural Networks
- Generative Networks
    - Large Language Models
- Constraint Programming
    - Constraint Satisfaction Networks
    - WFC / Model Synthesis
    - generalized Integer Linear Programming
    - Declarative/Inductive Programming
    - Linear Temporal Logic (Reactive synthesis)
- SMT
    - Angelic Execution
    - Hole Filling
    - Inductive programming

## Techniques

Many techniques are already discussed (at their back-then state) by Gulwani¹.
We will focus on the special task of low-level complete program synthesis, the new techniques, and 
give a short summary/table to compare the techniques especially with respect to the requirements and guarantees.

### Summary



### Reinforcement Learning


### AI Planning


### Genetic Programming


### Generative Networks


### Constraint Programming


### SMT


## Related Repositories
- [Program Transpilation Overview](https://github.com/NeuralCoder3/transpilation)
- [Reinforcement Learning for Assembly Synthesis](https://github.com/NeuralCoder3/reinf_asm_synth)
- [Stoke for Assembly Synthesis](https://github.com/NeuralCoder3/stoke-sort)
- [SMT Synthesis of BitArithmetic](https://github.com/shack/synth)

Papers:
- ¹Program Synthesis, Gulwani et. al, 2017