# INFO-H417

This project tests different implementations for I/Os interactions. 4 implementations of InputStream and OutputStream are made. 

The 3 first experiments are done respectively in :
- Experiment1.cpp
- randjump.cpp
- rrmerge.cpp

The last experiment is done in "extsort.cpp".

The "GraphFileGenerator.cpp" is used to generate graphs using the notebook GraphsGenerator.ipynb.

Usages :

    Experiment1 : ./Experiment1 inputfile
        - inputFile     inputFile
        Exemple : ./Experiment1 keyword.csv

    randjump : ./ranjump j inputfile [inputfile2, ...]
        - j             amount of randjump
        - inputfile     input file
        - inputfile2    as many inputfiles as will
        Exemple : ./randjump 4000 keyword.csv


    rrmerge : ./rrmerge inputfile(s)
        - inputfile(s)   as many inputfiles as will
        Exemple : ./rrmerge keyword.csv cast_info.csv

    extsort : ./extsort inputfile k M d
        - inputfile     input file
        - k             column chosen for the sort
        - M             Size of the buffer
        - d             number of files to merge at the same time for the merge algorithm
        Exemple : ./extsort keyword.csv 0 1024 4 
