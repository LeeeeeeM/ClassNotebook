#' ---
#' title: Working with Data Files
#' ---

#' **Originally Contributed by**: Arpit Bhatia

#' In many cases we might need to read data available in an external file rather than type it into Julia ourselves.
#' This tutorial is concerned with reading tabular data into Julia and using it for a JuMP model. 
#' We'll be reading data using the DataFrames.jl package and some other packages specific to file types.

#' Note: There are multiple ways to read the same kind of data intto Julia.
#' However, this tutorial only focuses on DataFrames.jl as
#' it provides the ecosystem to work with most of the required file types in a straightforward manner.

#' ### DataFrames.jl

#' The DataFrames package provides a set of tools for working with tabular data. 
#' It is available through the Julia package system.
#+ tangle = false

using Pkg
Pkg.add("DataFrames")

#' ### What is a DataFrame?

#' A DataFrame is a data structure like a table or spreadsheet. You can use it for storing and exploring a set of related data values. 
#' Think of it as a smarter array for holding tabular data.

#' ## Reading Tabular Data into a DataFrame
#' We will begin by reading data from different file formats into a DataFrame object.
#' The example files that we will be reading are present in the data folder.

#' ### Excel Sheets
#' Excel files can be read using the ExcelFiles.jl package.
#+ tangle = false

Pkg.add("XLSX")

#' To read a Excel file into a DataFrame, we use the following julia code. 
#' The first arguement to the `readtable` function is the file to be read and the second arguement is the name of the sheet.

using DataFrames
using XLSX

#+

data_dir = joinpath(@__DIR__, "data")
excel_df = DataFrame(XLSX.readtable(joinpath(data_dir, "SalesData.xlsx"), "SalesOrders")...)

#' ### CSV Files
#' CSV and other delimited text files can be read the CSV.jl package.
#+ tangle = false

Pkg.add("CSV")

#' To read a CSV file into a DataFrame, we use the `CSV.read` function. 

using CSV
csv_df = CSV.read(joinpath(data_dir, "StarWars.csv"))

#' ### Other Delimited Files
#' We can also use the CSV.jl package to read any other delimited text file format. 
#' By default, CSV.File will try to detect a file's delimiter from the first 10 lines of the file.
#' Candidate delimiters include `','`, `'\t'`, `' '`, `'|'`, `';'`, and `':'`. If it can't auto-detect the delimiter, it will assume `','`.
#' Let's take the example of space separated data.

ss_df = CSV.read(joinpath(data_dir, "Cereal.txt"))

#' We can also specify the delimiter by passing the `delim` arguement.

delim_df = CSV.read(joinpath(data_dir, "Soccer.txt"), delim = "::")

#' Note that by default, are read-only. If we wish to make changes to the data read, we pass the `copycols = true` arguement in the function call.
#+ tangle = false

ss_df = CSV.read(joinpath(data_dir, "Cereal.txt"), copycols = true)


#' ## Working with DataFrames
#' Now that we have read the required data into a DataFrame, let us look at some basic operations we can perform on it.

#' ### Querying Basic Information
#' The `size` function gets us the dimensions of the DataFrame.

size(ss_df)

#' We can also us the `nrow` and `ncol` functions to get the number of rows and columns respectively.

nrow(ss_df), ncol(ss_df)

#' The `describe` function gives basic summary statistics of data in a DataFrame.

describe(ss_df)

#' Names of every column can be obtained by the `names` function.

names(ss_df)

#' Corresponding data types are obtained using the broadcasted `eltype` function.

eltype.(ss_df)

#' ### Accessing the Data
#' Similar to regular arrays, we use numerical indexing to access elements of a DataFrame.

csv_df[1,1]

#' The following are different ways to access a column.

csv_df[!, 1]

#+

csv_df[!, :Name]

#+

csv_df.Name

#+

csv_df[:, 1] # note that this creates a copy

#' The following are different ways to access a row.

csv_df[1:1, :]

#+

csv_df[1, :] # this produces a DataFrameRow

#' We can change the values just as we normally assign values.

#' Assign a range to scalar.

excel_df[1:3, 5] .= 1

#' Vector to equal length vector.

excel_df[4:6, 5] = [4, 5, 6]

#' Subset of the DataFrame to another data frame of matching size.

excel_df[1:2, 6:7] =  DataFrame([-2 -2; -2 -2], [Symbol("Unit Cost"), :Total])

#+

excel_df

#' There are a lot more things which can be done with a DataFrame. 
#' See the [docs](https://juliadata.github.io/DataFrames.jl/stable/) for more information.

#' ## A Complete Modelling Example - Passport Problem

#' Let's now apply what we have learnt to solve a real modelling problem.

#' The [Passport Index Dataset](https://github.com/ilyankou/passport-index-dataset) 
#' lists travel visa requirements for 199 countries, in .csv format.
#' Our task is to find out the minimum number of passports required to visit all countries.

#' In this dataset, the first column represents a passport (=from) and each remaining column represents a foreign country (=to). 
#' The values in each cell are as follows:
#' * 3 = visa-free travel
#' * 2 = eTA is required
#' * 1 = visa can be obtained on arrival
#' * 0 = visa is required
#' * -1 is for all instances where passport and destination are the same

#' Our task is to find out the minimum number of passports needed to visit every country without requiring a visa.
#' Thus, the values we are interested in are -1 and 3. Let us modify the data in the following manner -

passportdata = CSV.read(joinpath(data_dir, "passport-index-matrix.csv"), copycols = true)

for i in 1:nrow(passportdata)
    for j in 2:ncol(passportdata)
        if passportdata[i,j] == -1 || passportdata[i,j] == 3
            passportdata[i,j] = 1
        else
            passportdata[i,j] = 0
        end
    end
end

#' The values in the cells now represent:
#' * 1 = no visa required for travel
#' * 0 = visa required for travel

#' Let us assossciate each passport with a decision variable $pass_{cntr}$ for each country. 
#' We want to minize the sum $\sum pass_{cntr}$ over all countries. 

#' Since we wish to visit all the countries, for every country, 
#' we should own atleast one passport that lets us travel to that country visa free. 
#' For one destination, this can be mathematically represented as $\sum_{cntr \in world} passportdata_{cntr,dest} \cdot pass_{cntr} \geq 1$.

#' Thus, we can represent this problem using the following model:

#' $$
#' \begin{align*}
#' \min && \sum_{cntr \in World} pass_{cntr} \\
#' \text{s.t.} && \sum_{cntr \in World} passportdata_{cntr,dest} \cdot pass_{cntr} \geq 1 && \forall dest \in World \\
#' && pass_{cntr} \in \{0,1\} && \forall cntr \in World
#' \end{align*}
#' $$

#' We'll now solve the problem using JuMP.

using JuMP, GLPK

# Finding number of countries
n = ncol(passportdata) - 1 # Subtract 1 for column representing country of passport

model = Model(GLPK.Optimizer)
@variable(model, pass[1:n], Bin)
@constraint(model, [j = 2:n], sum(passportdata[i,j] * pass[i] for i in 1:n) >= 1)
@objective(model, Min, sum(pass))
optimize!(model)

println("Minimum number of passports needed: ", objective_value(model))

#+

countryindex = findall(value.(pass) .== 1 )

print("Countries: ")
for i in countryindex
    print(names(passportdata)[i+1], " ")
end