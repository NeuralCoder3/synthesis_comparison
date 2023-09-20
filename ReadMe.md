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

<table>
    <tr>
        <th>Technique</th>
        <th>Domain</th>
        <th>Requirements</th>
        <th>Result</th>
        <th>Guarantees</th>
        <th>Tools</th>
        <th>Examples (Applications)</th>
    </tr>
    <tr>
        <td>Reinforcement Learning</td>
        <td>Observations (Input) and Actions (Output)</td>
        <td>Score function, non-standard encoding of problem</td>
        <td>Action-plan(s)</td>
        <td>None, but optimizes for score (can encode speed-requirement)</td>
        <td>Gym, Torch</td>
        <td>AlphaDev, AlphaTensor</td>
    </tr>
    <tr>
        <td>AI Planning</td>
        <td>Facts about states and actions</td>
        <td>Encoding as facts</td>
        <td>Action Sequence</td>
        <td>Correctness, optionally Optimality (if exists)</td>
        <td>PDDL-solver</td>
        <td></td>
    </tr>
    <tr>
        <td>Genetic Programming</td>
        <td>Genes</td>
        <td>Fitness function</td>
        <td>Genes</td>
        <td>None, but good fitness</td>
        <td>PyGad</td>
        <td></td>
    </tr>
    <tr>
        <td>Generative NN</td>
        <td>Text queries</td>
        <td>pre-trained model</td>
        <td>program code</td>
        <td>None</td>
        <td>LLMs</td>
        <td>GPT, CoPilot</td>
    </tr>
    <tr>
        <td>Constraint Programming</td>
        <td>restrictive Constraint</td>
        <td>specific encoding</td>
        <td>Solution</td>
        <td>satisfy all constraints</td>
        <td>Prolog, Z3</td>
        <td></td>
    </tr>
    <tr>
        <td>SMT</td>
        <td>FOL</td>
        <td>encoding</td>
        <td>Solution</td>
        <td>Correctness</td>
        <td>Z3, CVC5</td>
        <td></td>
    </tr>
</table>


### Experiments

https://docs.google.com/spreadsheets/d/18pV_AFn8EqWnFsXg6lTkTJtPIPQgOTxlhqvPVEM_P6M/edit?usp=sharing

For MetaLift (Rosette), we converted the imperative code in a functional way by changing a world state with each instruction.

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

Sort Experiment: Not applicable.
The commands needs to be (encoded in) the actions.
The state needs to encode a superposition/unknown register entry (otherwise, we would sort concrete elements).
Actions need to be deterministic depending on facts.
Together, we can not conditionally transform the state set without fully exponentially unrolling the permutations of the progra state and actions.

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

These techniques work quite well.
Language models, usually based on natural language, generate code.

A prime example is the recent development in large language models.

The query is usually given as completion problem or using natural language queries.
Using prompting techniques, the accuracy can be increased and certain errors (e.g. syntax errors) can be mostly avoided.

However, there are no guarantees about the resulting code.
It might be slow or even wrong.


### Constraint Programming

This general field (which also subsumes SMT) is concerned with solvers that given a domain and constraints of a problem
find a solution satisfying all constraints.

These methods can encode arbitrarily complex problems spanning a multitude of complexity classes (NP, PSpace, 2ExpTime, undecidable).

The theorical principles behind the solvers are often similar as outlined with the reductions.
However, certain problems are easier encoded in some domains than in others.
Additionally, the formulation and encoding can greatly influence how feasible the synthesis becomes.

These techniques are not developed for program synthesis and often require ingenuity and tedious rewrites to be applied.

### SMT

SMT is a generalization of SAT (formula satisfiability) with theories.
Complex semantics (especially loop-free fragments) can be encoded in SMT. Loops are non-straightforward and usually require approximations.

Subcategories include synthesis where concrete instantiations (e.g. of program code fragments) are generated that do not violate assertions.

- [Suslik](http://comcom.csail.mit.edu/comcom/#SuSLik) (Separation Logic) -- not applicable <!-- 13 -->
- [Synquid](http://comcom.csail.mit.edu/comcom/#Synquid) (Refinement Types) -- not imperative <!--  -->
- [ReSyn](http://comcom.csail.mit.edu/comcom/#ReSyn) (Resource Types) -- not applicable <!--  -->
- [Dafny](https://github.com/dafny-lang/dafny) (Hoare) -- no synthesis; focus on verification <!-- 12 -->
- [EUSolver](https://github.com/yuntongzhang/eusolver) (SyGUS) <!-- 3 --> -- functional
- [Euphony](https://github.com/wslee/euphony) (needs training, SyGUS) <!-- 4 -->
- [BlinkFill](https://www.microsoft.com/en-us/research/publication/blinkfill-semi-supervised-programming-by-example-for-syntactic-string-transformations/) (semi-supervised; FlashFill + structure from inputs) <!-- 5 -->
- [Brahma](https://github.com/wx-csy/python-brahma) (loop-free, counterexample-guided refinement) <!-- 8 -->
- [Sketch](https://people.csail.mit.edu/asolar/papers/Solar-Lezama09.pdf) <!-- 4 -->
- [Regae](https://sites.google.com/site/asergrp/projects/reggae) (Test generation, regex) <!-- 14 -->
- [Stoke](https://github.com/StanfordPL/stoke) (heuristic search) <!-- 6 -->
- [PROSE](https://www.microsoft.com/en-us/research/project/prose-framework/) (sketch, input-outpu) <!-- 4 -->
- [Rosette](https://emina.github.io/rosette/) <!-- 4 -->


## Related Repositories
- [Program Transpilation Overview](https://github.com/NeuralCoder3/transpilation)
- [Reinforcement Learning for Assembly Synthesis](https://github.com/NeuralCoder3/reinf_asm_synth)
- [Stoke for Assembly Synthesis](https://github.com/NeuralCoder3/stoke-sort)
- [SMT Synthesis of BitArithmetic](https://github.com/shack/synth)
- [SMT Synthesis using MetaLift (Rosette)](https://github.com/NeuralCoder3/smt_synthesis)

Notes:
- [Lecture about program synthesis](https://github.com/nadia-polikarpova/cse291-program-synthesis/tree/master)
- [Sketch Synthesis](https://homes.cs.washington.edu/~bodik/ucb/Files/2012/CAV-2012.pdf)

Papers:
- ¹Program Synthesis, Gulwani et. al, 2017