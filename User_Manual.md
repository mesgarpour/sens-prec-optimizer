# User Manual #

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

# Description #
SensPrecOptimizer is a freeware software to implement profiling of Highly Sensitive Search Strategies (HSSS) by combining the search queries. HSSS refers to the two strategies recommended by the Cochrane Handbook for Systematic Reviews of Interventions: a sensitivity-maximizing version and a sensitivity- and precision-maximizing version [[1](1.md)]. This software may also be used for developing search filters or hedges.




---

# 1. Download and Setup #

## 1.1. Hardware and Software Requirements ##
The minimum required hardware settings are 1GB of RAM and 1GB of free memory storage, and the desired requirements are 2GBs of RAM, 3GBs of free memory storage and a multi-core processor. SensPrecOptimizer needs 80 MB free storage for installation.

The supported Operating Systems (OS) are:
  * MS Windows OS (6.0 and above)
  * Apple Mac OS (10.4 and above)
  * Linux OS (Fedora 17 and above)


## 1.2. Setup ##
Please follow the below instructions to install the SensPrecOptimizer. If your OS is not listed in below, the SensPrecOptimizer may not be compatible.


### 1.2.1. MS Windows OS (6.0 and above) ###
  1. Download and decompress the Windows’ version of the package;
  1. Open the directory;
  1. Double-click on the SensPrecOptimizer shortcut to execute the programme.


### 1.2.2. Apple Mac OS (10.4 and above) ###
  1. Download and decompress the Mac’s version of the package;
  1. Download and install the Xcode from the Mac App Store (it is a must for the Alpha version)
  1. Download and install the QT Creator (it is a must for the Alpha version)
  1. Double-click on the SensPrecOptimizer shortcut to execute the programme.


### 1.2.3. Linux OS (Fedora 17 and above) ###
The source code is ready for Linux environment; however, it needs additional resources for test and compile.



---

# 2. Graphical User Interface #
The Graphical User Interface (GUI) consists of (Fig. 1) the following entities:


![https://lh6.googleusercontent.com/-8g_IGjAMc_U/Um2jkyVuOWI/AAAAAAAAC04/RHLW64FOIHQ/w1200-h1244-no/manual_1.png](https://lh6.googleusercontent.com/-8g_IGjAMc_U/Um2jkyVuOWI/AAAAAAAAC04/RHLW64FOIHQ/w1200-h1244-no/manual_1.png)

_Fig. 1. A screen shot of the SensPrecOptimizer’s User Interface_


  1. Specify the absolute path to the input file.
  1. Specify the absolute path to the output.
  1. Set the total number of relevant documents. By default, it is summing up the number of relevant documents (the second row) in the input file.
  1. Set a combination length (percentage) for the algorithm to start with. It is recommended to be set to a value below 40% or above 60%.
  1. Set the number of additional smaller combinations to be calculated by the algorithm. By default, the algorithm stops when the sensitivity drops below the maximum sensitivity in the current iteration. It is recommended to be set to a value between 0 and 5.
  1. In order to optimise the memory usage, specify a narrow sensitivity range for the algorithm. By default, it is set to the maximum sensitivity value of the search queries. It is especially important to set a narrow value for search queries that are longer than 21.
  1. It filters down longer search strategies with similar sensitivity and precision, resulted in the shortest strategy with the highest sensitivity and precision.
  1. In order to minimize the outputted strategies for long search strategies (more than 21 queries), specify the acceptable sensitivity range for output filter. The range is the distance from the maximum sensitivity.
  1. Run the algorithm.
  1. Abort the execution of the algorithm.



---

> # 3. Input File #
To construct a compatible input file, an Excel or Access file with a matrix of search queries and documents (or records) is demanded. By searching a query (one column for each query), a set of documents (one row for each document) will retrieve which should be recorded with all necessary characteristics and an assigned ID code. The relevancy of each document should be identified and recorded in a separate column (preferably the second column). Therefore, the ID, relevancy and queries form the consecutive columns in the input file (Fig. 2). The retrieval status of the records retrieved by a search query should be specified as ‘‘one’’ and the rest of records as ‘‘zero’’ in a column (the values must be numerical).

![https://lh4.googleusercontent.com/-9kIi_yGzHYo/Um2jwr9lw1I/AAAAAAAAC1Q/rEFY2La0XR8/w2728-h870-no/manual_4.png](https://lh4.googleusercontent.com/-9kIi_yGzHYo/Um2jwr9lw1I/AAAAAAAAC1Q/rEFY2La0XR8/w2728-h870-no/manual_4.png)

_Fig. 2. Left picture is a sample of recording datasheet; Right picture is the transposed datasheet (input file)_


Since it is generally expected that number of retrieved documents is much more than the number of search queries, it is suggested to assign columns to queries and rows to documents. However, the input file must follow the following criteria, which needs [transposing](http://www.howtogeek.com/howto/12366/) the matrix of queries and documents (Fig 1- the right picture):
  * The file format must be in a comma separated values (CSV) format and with ‘csv’ extension.
  * The columns represent the documents and the rows represent the search queries. Also, a header must be defined for each column and row.
  * The first row represents the documents’ IDs which must be numerical and unique across the columns.
  * The second row is designated for the relevancy of documents. The values must be numerical and can be either ‘0’ or ‘1’.
  * The third row and any row below that hold the search-queries match for each specific document. The values must be numerical and can be either ‘0’ or ‘1’.
  * The first column of the first two rows is the title and being ignored by the programme
  * The first column from the third row onward represent the search-queries’ IDs (Fig. 1- the right picture).

You can download a sample input file [here](https://sens-prec-optimizer.googlecode.com/git/Documentations/Sample%20Files/Inputfile%20for%20Guide.csv).



---

# 4. Output File #
The programme produces two types of outputs: log and statistical summaries. Firstly, there is only one log output file to save settings and runtime logs. Secondly, there are one or more statistical summaries in a comma-separated values (CSV) format. The CSV files hold the optimized ranked list of search strategies based on the sensitivity (Fig. 3). The CSV files are suited to open in Microsoft Excel and record the combinations of search queries with their ‘length’, ‘Sensitivity’ and ‘Precision’.

![https://lh3.googleusercontent.com/-O-lelu3AWl0/Um2kACv2DXI/AAAAAAAAC1o/s74IiaGedsE/w2728-h768-no/manual_5.png](https://lh3.googleusercontent.com/-O-lelu3AWl0/Um2kACv2DXI/AAAAAAAAC1o/s74IiaGedsE/w2728-h768-no/manual_5.png)

_Fig. 3.  A sample output file (when the minimize search strategies' length filter is off). The third row demonstrates the shortest highly sensitive search strategy, the maximizing version._


HSSS, sensitivity- and precision-maximizing version, can be formulated from the search queries presented in the second row or any row below that (when there is more than one combination of queries with the highest sensitivity) of a CSV file.

The best balance of sensitivity and precision, sensitivity- and precision-maximizing version of HSSS, can be obtained by finding the best-fit line on the [scatter plot](http://www.addictivetips.com/microsoft-office/excel-2010-scatter-trendline/) of sensitivity versus precision (see Fig.2 in references 2 and 3). It is recommended to make the scatter plot from the output in the spreadsheet program like MS Excel, while it has been filtered on “Report within Sensitivity Range of 100%” (Fig. 4).

![https://lh5.googleusercontent.com/-MxkrWJhMtb4/Um7RkQhakAI/AAAAAAAAC5M/uKJ63YzTEQg/w1050-h800-no/guide_4_s.png](https://lh5.googleusercontent.com/-MxkrWJhMtb4/Um7RkQhakAI/AAAAAAAAC5M/uKJ63YzTEQg/w1050-h800-no/guide_4_s.png)

_Fig. 4. Plot of sensitivity versus precision for different combinations of search queries from the sample output file; the intersection of trend line in the upper right hand of the plot and precision-sensitivity curve can be calculated as the optimization data points (as demonstrated for example)._



---

# 5. Configuration #
Before running the application, you must configure the application settings. The setting fields are as below:
Input File: The full path of the input file
Output Path: The full path of the directory that is going to be used for saving the outputs.


## 5.1. Data Configuration ##
  * **5.1.1. Default**: By choosing this option, SensPrecOptimizer calculates the sensitivity based on available number of documents and search queries in the input file.

  * **5.1.2. Custom**: Total number of relevant documents can be set when there is an external gold standard. For example, assume the input file consists of relevancy and retrieval status of 20 search queries within MEDLINE (4000 total documents and 2030 relevant documents) and there is a pool of known relevant documents retrieved by MEDLINE and EMBASE (4100 relevant documents). By choosing the DEFAULT option, the denominator of sensitivity formula (see the definition of sensitivity in Glossary) is 2030 and by customising this option, the denominator can manually be set as 4100.


## 5.2. Algorithm Configuration ##
The following options allow the user to modify the analysis process in a timely manner. It is recommended to set the algorithm configuration when the number of queries is more than 20.
  * **5.2.1. Combinations Iterations - The Starting Point (%)**: The starting point is set to save the runtime and its memory usage, particularly when the number of search queries are larger than 20. It is recommended that the starting point set to a value below 40% or above 60%, because combination sizes close to 50% are memory and process intensive. For example, if our input file has 20 search queries and we chose 75%, it means that SensPrecOptimizer initialised by 15 combinations.

  * **5.2.2. Combinations Iterations - The Number of Additional Smaller Neighbours**: The number of additional smaller combinations to be calculated after processing the smaller combinations (see Iteration 5 in the Technical Specification).



## 5.3. Runtime Filtering of Output ##
  * **5.3.1. Default**: The default minimum sensitivity sets to the maximum sensitivity of individual search queries.

  * **5.3.2. Custom**: The acceptable minimum sensitivity can manually be set to optimise the memory usage.


## 5.4. Configure Output Filter ##
The following options allow the user to customize the output.

  * **5.4.1. Short Report by Minimizing Search Strategies’ Length**: It performs two types of filtering. Firstly, filter keeps the shortest search strategy within a set of queries combinations with similar sensitivity and precision. Secondly, it retains the strategy with the highest precision. For example, if combinations of 15, 16, 17 and 18 out of 20 queries have the same sensitivity and precision, choosing this option yields combinations of 15 queries only. It also filters the 15 queries combinations with the highest precision when there is different precision with the same sensitivity (Fig. 5).


![https://lh4.googleusercontent.com/-zVV3HEov3Lk/Um2kC5pmZ0I/AAAAAAAAC10/PwySwZsKv7s/w2728-h908-no/manual_7.png](https://lh4.googleusercontent.com/-zVV3HEov3Lk/Um2kC5pmZ0I/AAAAAAAAC10/PwySwZsKv7s/w2728-h908-no/manual_7.png)

_Fig. 5.  A sample output file filtered by minimizing search strategies’ length_


  * **5.4.2. Report within Sensitivity Range of (%)**: The sensitivity range that is going to filter the outputs before outputting. It is recommended to set to a narrow range for the large search query sizes. It has been set by default to the range of 100%, which means a comprehensive report with no filter.

After you have set the configuration fields, you may click on the ‘Run’ button to execute the applications.


---

# 6. Error Messages and Troubleshooting #
The table in below summarise the error messages and their diagnostics.

![https://lh4.googleusercontent.com/-ltFJ8ncWwqA/Um2j5TwbuRI/AAAAAAAAC1Y/Dv93J4mjkj8/w1200-h958-no/manual_8.png](https://lh4.googleusercontent.com/-ltFJ8ncWwqA/Um2j5TwbuRI/AAAAAAAAC1Y/Dv93J4mjkj8/w1200-h958-no/manual_8.png)


---

> # References #
[[1](1.md)] Lefebvre C, Manheimer E, Glanville J. Chapter 6: Searching for studies. In: Higgins JPT, Green S (editors). Cochrane Handbook for Systematic Reviews of Interventions Version 5.1.0 (updated March 2011). The Cochrane Collaboration, 2011. Available from www.cochrane-handbook.org.

[[2](2.md)] Mesgarpour B, Müller M, Herkner H. Search strategies-identified reports on ‘‘off-label’’ drug use in MEDLINE. J Clin Epidemiol 2012; 65: 827-834.

[[3](3.md)] Mesgarpour B, Müller M, Herkner H. Search strategies to identify reports on “off-label” drug use in EMBASE. BMC Med Res Methodol 2012; 12:190.

[[4](4.md)] Mesgarpour B, Mesgarpour M, Müller M, Herkner H. Developing software for combining search queries to design efficient search strategies. The Cochrane Library: Abstracts of the 19th Cochrane Colloquium 2011(supplement): 58.


> 
---

# Glossary #
    * **Boolean operators:** Simple words used as conjunctions to combine or exclude keywords in a search, resulting in more focused and productive results. The most commonly Boolean operators used in search queries are “AND”, “OR” and “NOT”.
    * **Controlled vocabulary:** Consistent collection of terms chosen for specific purposes with explicit, logical constraints on intended meanings and relationships in a database. “Subject headings” make up the controlled vocabulary of a bibliographic database. For example, Medical Subject Headings (MeSH) in MEDLINE and EMTREE in EMBASE.
    * **Free text:** Words, phrases, or terms sought in title, abstract, or full text of document
    * **Highly Sensitive Search Strategies (HSSS):**  The Cochrane Handbook for Systematic Reviews of Interventions offered two HSSS strategies for searching trials for inclusion in a Cochrane reviews: a sensitivity-maximizing version and a sensitivity- and precision-maximizing version [[1](1.md)].
    * **Precision:** The number of relevant identified reports divided by the total number of identified reports. Precision is equivalent to positive predictive value in diagnostic test method.
    * **Proximity operators:** They are used to improve the search queries by instructing the query to look for words that are within a short distance of each other in a document. Proximity operators and their functions vary by system and include “ADJ” and “NEAR”. Also called “adjacency operators”.
    * **Retrieval performance:** In this manual, used as a measure of sensitivity, precision or both.
    * **Search filters:** Filters are described as predefined strategies to improve recall and retrieve maximum recall of primary research of gold standard studies i.e. randomized trials (RCTs), systematic reviews, meta-analysis etc. and clinical queries such as diagnosis, prognosis, etiology and therapy. Filters are also referred to as hedges, PubMed Clinical Queries, or optimal search strategies.
    * **Search query:** One line in electronic search strategy. It is usually a text string containing the exact sequence of words and/or characters, and may include Boolean or proximity operators.
    * **Search strategy:** Several search queries connected with Boolean operators make up a search strategy.
    * **Sensitivity:** the number of relevant reports identified divided by the total number of relevant reports in existence. Sensitivity is also called “recall”.