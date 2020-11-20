#' ---
#' title: Solvers and Solutions
#' ---

#' **Originally Contributed by**: Arpit Bhatia

#' The purpose of this part of the tutorial is to introduce you to solvers and how to use them with JuMP. We'll also learn
#' what to do with a problem after the solver has finished optimizing it.

#' ## What is a Solver?
#' A solver is a software package that incorporates algorithms for finding solutions to one or more classes of problem.
#' For example, GLPK, which we used in the previous tutorials is a solver for linear programming (LP) and mixed integer
#' programming (MIP) problems. It incorporates algorithms such as the simplex method, interior-point method etc. JuMP
#' currently supports a number of open-source and commercial solvers which can be viewed
#' [here](http://www.juliaopt.org/JuMP.jl/v0.19.1/installation/#Getting-Solvers-1).

#' ## What is MathOptInterface?
#' Each mathematical optimization solver API has its own concepts and data structures for representing optimization models
#' and obtaining results. However, it is often desirable to represent an instance of an optimization problem at a higher
#' level so that it is easy to try using different solvers. MathOptInterface (MOI) is an abstraction layer designed to provide
#' an interface to mathematical optimization solvers so that users do not need to understand multiple solver-specific
#' APIs. MOI can be used directly, or through a higher-level modeling interface like JuMP.

#' Note that JuMP reexports MathOptInterface and
#' you can use the shortcut MOI to refer to MathOptInterface in your code.

#' ## Interacting with solvers
#' JuMP models can be created in three different modes: `AUTOMATIC`, `MANUAL` and `DIRECT`.
#' We'll use the following LP to illustrate them.

#' $$
#' \begin{align*}
#' & \max_{x,y} & x + 2y \\
#' & \;\;\text{s.t.} & x + y &\leq 1 \\
#' & & 0\leq x, y &\leq 1 \\
#' \end{align*}
#' $$

using JuMP
using GLPK

#' ### `AUTOMATIC` Mode
#' #### With Optimizer
#' This is the easiest method to use a solver in JuMP. In order to do so, we simply set the solver inside the Model constructor.

model_auto = Model(GLPK.Optimizer)
@variable(model_auto, 0 <= x <= 1)
@variable(model_auto, 0 <= y <= 1)
@constraint(model_auto, x + y <= 1)
@objective(model_auto, Max, x + 2y)
optimize!(model_auto)
objective_value(model_auto)

#' #### No Optimizer (at first)
#' It is also possible to create a JuMP model with no optimizer attached. After the model object is initialized empty
#' and all its variables, constraints and objective are set, then we can attach the solver at `optimize!` time.

model_auto_no = Model()
@variable(model_auto_no, 0 <= x <= 1)
@variable(model_auto_no, 0 <= y <= 1)
@constraint(model_auto_no, x + y <= 1)
@objective(model_auto_no, Max, x + 2y)
set_optimizer(model_auto_no, GLPK.Optimizer)
optimize!(model_auto_no)
objective_value(model_auto_no)

#' Note that we can also enforce the automatic mode by passing `caching_mode = MOIU.AUTOMATIC` in the Model function call.
#' ### `MANUAL` Mode
#' This mode is similar to the `AUTOMATIC` mode, but there are less protections from the user getting errors from the solver
#' API. On the other side, nothing happens silently, which might give the user more control. It requires attaching the solver
#' before the solve step using the `MOIU.attach_optimizer()` function.

model_manual = Model(GLPK.Optimizer, caching_mode = MOIU.MANUAL)
@variable(model_manual, 0 <= x <= 1)
@variable(model_manual, 0 <= y <= 1)
@constraint(model_manual, x + y <= 1)
@objective(model_manual, Max, x + 2y)
MOIU.attach_optimizer(model_manual)
optimize!(model_manual)
objective_value(model_manual)

#' ### `DIRECT` Mode
#' Some solvers are able to handle the problem data directly. This is common for LP/MIP solver but not very common for
#' open-source conic solvers. In this case we do not set a optimizer, we set a backend which is more generic and is able
#' to hold data and not only solving a model.

model_direct = direct_model(GLPK.Optimizer())
@variable(model_direct, 0 <= x <= 1)
@variable(model_direct, 0 <= y <= 1)
@constraint(model_direct, x + y <= 1)
@objective(model_direct, Max, x + 2y)
optimize!(model_direct)
objective_value(model_direct)

#' ### Solver Options
#' Many of the solvers also allow options to be passed in. However, these options are solver-specific. To find out the various
#' options available, please check out the individual solver packages. Some examples for the CBC solver are given below.

using Cbc

#' To turn off printing (i.e. silence the solver),

model = Model(optimizer_with_attributes(Cbc.Optimizer, "logLevel" => 0));

#' To increase the maximum number of iterations

model = Model(optimizer_with_attributes(Cbc.Optimizer, "max_iters" => 10000));

#' To set the solution timeout limit

model = Model(optimizer_with_attributes(Cbc.Optimizer, "seconds" => 5));

#' ## Querying Solutions
#' So far we have seen all the elements and constructs related to writing a JuMP optimization model. In this section we
#' reach the point of what to do with a solved problem. JuMP follows closely the concepts defined in MathOptInterface to
#' answer user questions about a finished call to `optimize!(model)`. The three main steps in querying a solution are
#' given below. We'll use the model we created in `AUTOMATIC` mode with an optimizer attached in this section.
#' ### Termination Statuses
#' Termination statuses are meant to explain the reason why the optimizer stopped executing in the most recent call
#' to `optimize!`.

termination_status(model_auto)

#' You can view the different termination status codes by referring to the docs or though checking the possible types using
#' the below command.

display(typeof(MOI.OPTIMAL))

#' ### Solution Statuses
#' These statuses indicate what kind of result is available to be queried from the model. It's possible that no result is
#' available to be queried. We shall discuss more on the dual status and solutions in the Duality tutorial.

primal_status(model_auto)

#+

dual_status(model_auto)

#' As we saw before, the result (solution) status codes can be viewed directly from Julia.

display(typeof(MOI.FEASIBLE_POINT))

#' ### Obtaining Solutions
#' Provided the primal status is not `MOI.NO_SOLUTION`, we can inspect the solution values and optimal cost.

@show value(x)
@show value(y)
@show objective_value(model_auto)

#' Since it is possible that no solution is available to be queried from the model, calls to `value` may throw errors.
#' Hence, it is recommended to check for the presence of solutions.
#+ tangle = false

model_no_solution = Model(GLPK.Optimizer)
@variable(model_no_solution, 0 <= x <= 1)
@variable(model_no_solution, 0 <= y <= 1)
@constraint(model_no_solution, x + y >= 3)
@objective(model_no_solution, Max, x + 2y)

optimize!(model_no_solution)

if termination_status(model_no_solution) == MOI.OPTIMAL
    optimal_solution = value(x)
    optimal_objective = objective_value(model_no_solution)
elseif termination_status(model_no_solution) == MOI.TIME_LIMIT && has_values(model_no_solution)
    suboptimal_solution = value(x)
    suboptimal_objective = objective_value(model_no_solution)
else
    error("The model was not solved correctly.")
end
