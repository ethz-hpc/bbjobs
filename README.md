bbjobs
======

A better 'bjobs' command for IBM Platform LSF (http://www-03.ibm.com/systems/technicalcomputing/platformcomputing/products/lsf/)

bbjobs provides a cleaner overview of the job information, resources and history. 
It relies on LSF API functions to extract the data from a job.

Installation from code
======

Download the project from https://github.com/pousa/bbjobs

or check the out codes from git://github.com/pousa/bbjobs.git

1. To build bbjobs
        make
2. To clean the built objects and binary
        make clean
3. To install bbjobs 
        make install
        
Build Dependencies
------------------
bbjobs requires the follwoing libraries from lsf

1. liblsf
2. libbat

LSF Requirement
------------------
bbjobs requires LSF API.
        



