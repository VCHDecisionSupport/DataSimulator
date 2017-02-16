# Data Simulator
Uses a statistical profile of ODBC source data to parameterize a generic probability model. Then generate a structurally equivalent random data set by sampling from the probability model.

## Privacy considerations
Simulated data does not contain patient data. 
Simulation is one way-there is *no-way to reproduce source data from simulated data*. 

## Requirements
ODBC compatible source data (eg MS SQL Database, Denodo)

## Statistical Profile
### input: 
connection string ODBC compliant DSN of source system
### output:
- rerunnable DDL scripts to create empty structures
- rerunnable DML scripts to populate non-private data
- collection of C++ objects repersenting source schema objects
  - database, 
  - schema, 
  - table, 
  - column 
    - parameterized multinomal probability model (ie collection of distinct column values (aka outcome values) and there respective probabilties)
### Logical Flow
1. Extract meta data from source schema
   A. generate rerunnable DDL scripts
1. Instantiate c++ object model of schema from meta data
1. C++ column class decorated to add odbc connectivity for querying source system
1. Generate and execute queries against source data that determines pairwise functional dependency between columns within each table
1. Functional dependency hierarchies are modelled as a tree of column values. 
   a. Only leaf level columns are simulated 
   2. value of parent columns is determined from functional dependency tree
1. Generate and execute queries against source data that return table row counts, column distinct counts, and column column value histograms
1. Assume columns and rows are pairwise statistically independent (within and between tables). 
   a. Thus fk constraints are broken. 
1. Simulate primary keys columns with increasing sequence of values
1. Model non unique columns as multinomial probability distribution and estimate parameters with column value histogram

## Data Simulation
### input: 
- *[output of Statistical Profile](##Statistical-Profile)*
- desired row counts for simulated tables
### output:
- Fake data
### Logical Flow
1. Execute DDL creation scripts
1. Execute DML insertion scripts
1. populate destination tables by sampling from column probility models