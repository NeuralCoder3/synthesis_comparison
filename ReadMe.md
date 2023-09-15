# Synthesis

Synthesis is complicated.
Solving ILP and SMT queries is NP-complete.
Unbounded cases (as are necessary for more complicated logics or when involving loops/recursion) are undecidable.

Synthesis can be seen as a search problem in an enormous search space with (usually) bad heuristics.

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
- Genetic Programming (evolutionary algorithms)
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

<div style="width: 100%;">
  <img src="Overview.svg" style="width: 100%;" alt="Click to see the source">
</div>

### Reinforcement Learning

<img src="https://miro.medium.com/v2/resize:fit:4800/format:webp/1*k8OcINrYG_r5Vss5i27r_Q.png" width="400px" />

Encodes the problems as environment and actor.
The actor is learned and performs actions that change the environment.

In the setting of synthesis, the actions are the synthesized program
and the environment is data aiding the generation.

To decouple the actor from the synthesized program, the environment state has to be universal
and independent from concrete instances.

To guide the search, scores (rewards) can be provided after each action (or just at the end).
The score should reward a correct (and fast) solution. 
The more informative the score is (points for partial solution, intermediate feedback),
the better the search works.
However, a too detailed search function might lead the agent to a pre-defined path.
Additionally, domain-knowledge and expert-knowledge is needed to craft suited score functions.

The score allows to optimize for arbitrary criterias.
The agent can be modelled arbitrarily complex (with networks, LLM, MCTS, ...).
There are many hyperparameter tunable for training.

See [Reinforcement Learning for Assembly Synthesis](https://github.com/NeuralCoder3/reinf_asm_synth) for examples and more details.

Reinforcement learning can be seen as quite similar to genetic programming.
The score function is similar to the fitness of genetic algorithms.
The updating and learning however is quite different.
Genetic algorithms learn in a less focused way but are more generally applicable.
See https://medium.com/xrpractices/reinforcement-learning-vs-genetic-algorithm-ai-for-simulations-f1f484969c56 for a comparison.

### AI Planning

In planning, the problem is defined by actions and an environment.
The environment consists of facts that are true.
Actions depend on these facts and can change them.

The problem is a search in a given state for a goal state.
One does not need to define custom heuristics.

Like Reinforcement learning, an action sequence is learned for a given state (in an environment).
Unlike RL, the model knows the environment and action semantics completely.
Hence, planning is more restricted in the choice of environment.

You usually define the problem in PDDL.

### Genetic Programming

<img src="https://miro.medium.com/v2/resize:fit:4800/format:webp/1*zF3DzW57qD_LOGO1jQwdcg.png" width="400px" />

In genetic programming, you define a set of genes and ways to operate on them.
The fitness of individuals is computes, and the most fit are selected, cross breeded, and mutated.

Gentic algorithms are widely applicable.
You can use weights of networks as genes, use genes and simulate complex behaviour on top of them, or directly operate on genes for the fitness function.

GAs can solve search and optimization problems.

In combination with neural networks, GA can be applied to learn the weights as well as the hyperparameters.
The topic of neuroevolution including the NEAT algorithm focuses on GA for hyperparameters.
It can also be combined with reinforcement learning.

### Generative Networks


### Constraint Programming


### SMT


## Related Repositories
- [Program Transpilation Overview](https://github.com/NeuralCoder3/transpilation)
- [Reinforcement Learning for Assembly Synthesis](https://github.com/NeuralCoder3/reinf_asm_synth)
- [Stoke for Assembly Synthesis](https://github.com/NeuralCoder3/stoke-sort)
- [SMT Synthesis of BitArithmetic](https://github.com/shack/synth)
- [SMT Synthesis using MetaLift (Rosette)](https://github.com/NeuralCoder3/smt_synthesis)

Papers:
- ¹Program Synthesis, Gulwani et. al, 2017