# Technical Specifications #

  * **Title** A software tool for combining search queries to design efficient search strategies
  * **Version** 2.0.X
  * **Depends** None
  * **Author** Mohsen Mesgarpour <mohsen.mesgarpour@gmail.com>
  * **Contributors** Bita Mesgarpour, Harald Herkner
  * **Date** 2015-02-12
  * **Description** Development of Highly Sensitive Search Strategies, Sensitivity and precision analysis for “OR” combination of search queries
  * **Supported OSs** Windows (6.0 or above) or Mac (10.4 or above) or Linux (Fedora 17 or above)
  * **License** Apache License 2.0
  * **Input and Output Encoding** UTF-8
  * **3rd Party Software Needs** MS Office, Apache OpenOffice
  * **Repository** Google Code
  * **Available for download at:** [Google.Code](https://code.google.com/p/sens-prec-optimizer/)



---

# 1. Overview #
SensPrecOptimizer is a freeware software to implement profiling of Highly Sensitive Search Strategies (HSSS) by combining the search queries. HSSS refers to the two strategies recommended by the Cochrane Handbook for Systematic Reviews of Interventions: a sensitivity-maximizing version and a sensitivity- and precision-maximizing version [[1](1.md)]. This software may also be used for developing search filters or hedges.



---

## 1.1. Why it was important to develop this software? ##
Before answering this question, there are two terms that must be defined: search strategy, and search query. A search strategy is consisted of a number of search queries connected with Boolean operators. A search query is a text string that usually contains the exact sequence of words and/or characters, and may include Boolean or proximity operators.

To develop a HSSS, particularly a sensitivity-maximizing version, a comprehensive set of possible search queries should be constructed. However, obtaining the combination of queries with the best retrieval performance is troublesome in practice, particularly when the number of queries is getting larger (Fig. 1) or when the retrieval records of queries have considerable overlap.

![https://lh4.googleusercontent.com/--cZcIbtkLSE/Um2j-yDCsMI/AAAAAAAAC1g/YiKcAPZkvAI/w1686-h1200-no/technical_1.png](https://lh4.googleusercontent.com/--cZcIbtkLSE/Um2j-yDCsMI/AAAAAAAAC1g/YiKcAPZkvAI/w1686-h1200-no/technical_1.png)

_Fig. 1. The exponential growth of the number of combinations as search queries are being added to the search strategies_

SensPrecOptimizer analyses the “OR” combination of search queries to construct the best performing search strategies or HSSS.



---

## 1.2. History ##
A need for such a software has been realized during the study on developing search strategies for identifying off-label drug use in MEDLINE and EMBASE [2, 3]. The first version of SensPrecOptimizer presented as a poster in the 19th Cochrane Colloquium in Madrid in 2011 [[4](4.md)].



---

## 2. Simple Explanation of Analysis Process ##
The programme initially read and validates configurations, and then read the input file. Afterward, it calculates, filter and output the statistics for the combinations with different length. There are five main iterations in calculating the statistics, based on the combination length of search queries, and each iteration can consist of one or more steps. The step calculates the retrieval performance for search strategies of one particular length. The derived ‘maximum sensitivity’ in each step is the main condition that can interrupt the further progress of the iteration. The iterations are presented in below:
  * **Iteration 1:** Calculate the performance of the Individual search queries
  * **Iteration 2:** Calculate the performance of the combination length that is defined in the configuration as _the starting point_ (Combinations Iteration - The Starting Point).
  * **Iteration 3:** Calculate the larger combinations from _the starting point_. The combination length increases stepwise up to the point that the sensitivity does not improve.
  * **Iteration 4:** Calculate the smaller combinations from _the starting point_. The combination length decreases up to the point that the sensitivity becomes less than the maximum sensitivity.
  * **Iteration 5:** Calculate additional smaller combinations from the stopping point.
Finally, the programme filters and outputs the statistics.

For example, if the input file consists of 15 search queries and SensPrecOptimizer is set with _the starting point_ of 80% and The Number of Additional Smaller Neighbours 3:
  * **Iteration 1:** Calculate the performance of each 15 search queries
  * **Iteration 2:** Calculate the performance of the combination of search queries of length 12, resulted in calculation of 455 combinations (COMB(12,15))
  * **Iteration 3:** Calculate the performance of the combinations of length 13 and higher up to the point that the sensitivity does not improve (assume the highest sensitivity in combinations of length 14 is 90.05% and do not increase comparing to combinations of length 13)
  * **Iteration 4:** Calculate the combinations from length 11 down to the point that the sensitivity becomes less than the maximum sensitivity (90.05%).
  * **Iteration 5:** Calculate three additional smaller combinations from the stopping point with no other stopping condition (It is obvious that combining all search queries achieve the highest sensitivity, but it is desirable to obtain the highest sensitivity with as less and shortest combination of queries as possible.). For instance, if the stopping point was length 10, then it is going to calculate down to length 8.


## 2.1 Internal Flow of the Programme ##
Below figure represents the internal workflow of SensPrecOptimizer using the sequence diagram UML.

![https://lh5.googleusercontent.com/-Z6yCLZxqTn8/Um2kEV7vHaI/AAAAAAAAC14/QkhKzcqG4Iw/w1668-h1200-no/technical_2.png](https://lh5.googleusercontent.com/-Z6yCLZxqTn8/Um2kEV7vHaI/AAAAAAAAC14/QkhKzcqG4Iw/w1668-h1200-no/technical_2.png)

_Fig. 2. An abstract sequence-diagram UML of the SensPrecOptimizer_



---

# 3. Development #
SensPrecOptimizer is available under a free software license, allowing free access, distribution, modification and distribution of its modified versions, under the terms of the license. It can be installed on the major Operating Systems (see the user manual) and the source code and installation versions (binaries) are available for download at Google Code.


## 3.1. Setting up a Development Environment ##
The supported Operating Systems (OS) for developments are:
  * MS Windows OS (6.0 and above)
  * Apple Mac OS (10.4 and above)
  * Linux OS (Fedora 17 and above)


## 3.1.1. MS Windows OS (6.0 and above) ##
On a PC with Windows OS the following packages and libraries must be installed and any other versions or service pack might interfere with the compilation of the programme:
  * MS Windows .Net Framework 4.0 (32bit)
  * MS Windows SDK (32bit) + SP1
  * MS Visual Studio Express, C++ 2010 (32bit) + SP1
  * QT 5.x (library and creator), the MSVS 2010 binary (32bit)
  * C++ Boost libraries, the MSVS 2010 binary (32bit)


### 3.1.2. Apple Mac OS (10.4 and above) ###
On an Apple machine the following packages and libraries must be installed:
  * XCode with command line tools from the Mac App Store.
  * MacPorts, which is a package management system for Mac OS:
    1. Download the source files (not the binary versions).
    1. Compile, install and update using the following commands:
      * ./configure && make && sudo make install && sudo port -v selfupdate
    1. Add the folders to the path:
      * $ export PATH=/opt/local/bin:/opt/local/sbin:


---

# 3. Future Improvement Path #
  * Using 'eigen3' instead of 'ubblas' library for vector opoperations​. Theoretically, it will optimise the performance with multiple of magnitudes. It has been estimated that the algorithm normally needs ~19 TFLOPs for 2 to 16 sub-combinations out of 20 search queries and 16K documents. The 'ublas' library reduces it down to about ~10 TFLOPs.
  * Adding statistics of difference between the matched articles for different search queries to the output.
  * Cache the combinations' indices for the next runs.